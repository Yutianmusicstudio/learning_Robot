#!/usr/bin/env python3
"""
Phase 1 上位机：读 MIDI 文件 -> 通过串口驱动 8 键钢琴机器人

用法:
    pip install mido python-rtmidi pyserial

    python play_midi.py --list                       # 列出可用串口
    python play_midi.py --port /dev/ttyUSB0 --test   # 依次敲 8 个键，检查接线
    python play_midi.py --port COM3 twinkle.mid      # 演奏
    python play_midi.py --dry-run twinkle.mid        # 不接硬件，只打印将要发送的指令

协议见 code/phase1_eight_keys/phase1_eight_keys.ino
"""

import argparse
import sys
import time

# ---- 通道映射：8 个白键 C4~C5 ----
# MIDI note number: 中央 C(C4) = 60，每 +1 半音
NOTE_TO_CH = {
    60: 0,  # C4  do
    62: 1,  # D4  re
    64: 2,  # E4  mi
    65: 3,  # F4  fa
    67: 4,  # G4  sol
    69: 5,  # A4  la
    71: 6,  # B4  si
    72: 7,  # C5  do
}
CH_NAMES = ["C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5"]

PANIC = 0xFF


class Link:
    """串口连接的薄封装，dry-run 时只打印不发送。"""

    def __init__(self, port, baud=115200, dry_run=False):
        self.dry_run = dry_run
        self.ser = None
        if not dry_run:
            import serial  # 延迟导入，dry-run 不需要装 pyserial
            self.ser = serial.Serial(port, baud, timeout=0.1)
            time.sleep(2.0)  # Arduino 打开串口会自动复位，必须等它启动完

    def _write(self, data: bytes):
        if self.dry_run:
            print("  TX", " ".join(f"{b:02X}" for b in data))
        else:
            self.ser.write(data)

    def note_on(self, ch: int, velocity: int):
        self._write(bytes([0x80 | (ch & 0x07), velocity & 0x7F]))

    def note_off(self, ch: int):
        self._write(bytes([ch & 0x07]))

    def panic(self):
        self._write(bytes([PANIC]))

    def close(self):
        if self.ser:
            self.panic()
            self.ser.flush()
            time.sleep(0.1)
            self.ser.close()


def list_ports():
    try:
        from serial.tools import list_ports
    except ImportError:
        print("需要先安装 pyserial:  pip install pyserial")
        return
    ports = list(list_ports.comports())
    if not ports:
        print("没有检测到串口设备。检查 USB 线和驱动。")
    for p in ports:
        print(f"{p.device:20s} {p.description}")


def run_test(link: Link, hold_ms=150, gap_ms=250):
    """依次敲 8 个键 —— 用来确认接线顺序和每个键都能响。"""
    print("逐键测试：应当从左到右依次响起 C4 D4 E4 F4 G4 A4 B4 C5")
    for ch in range(8):
        print(f"  ch{ch} -> {CH_NAMES[ch]}")
        link.note_on(ch, 100)
        time.sleep(hold_ms / 1000)
        link.note_off(ch)
        time.sleep(gap_ms / 1000)


def play(link: Link, path: str, transpose: int = 0, verbose: bool = False):
    """按 MIDI 文件的真实时间轴演奏。

    mido 的 MidiFile.play() 会替我们处理 tempo 换算和延时，
    每次迭代返回的消息都是"已经等到该发的时刻"。
    """
    import mido

    mid = mido.MidiFile(path)
    print(f"曲目: {path}  时长 {mid.length:.1f}s")

    skipped = set()
    active = set()
    t0 = time.perf_counter()

    try:
        for msg in mid.play():
            if msg.type not in ("note_on", "note_off"):
                continue

            note = msg.note + transpose
            ch = NOTE_TO_CH.get(note)
            if ch is None:
                skipped.add(note)
                continue

            # MIDI 约定：note_on 且 velocity==0 等价于 note_off
            is_on = (msg.type == "note_on" and msg.velocity > 0)

            if is_on:
                link.note_on(ch, msg.velocity)
                active.add(ch)
                if verbose:
                    print(f"{time.perf_counter()-t0:6.2f}s  ON  {CH_NAMES[ch]} v={msg.velocity}")
            else:
                link.note_off(ch)
                active.discard(ch)
                if verbose:
                    print(f"{time.perf_counter()-t0:6.2f}s  OFF {CH_NAMES[ch]}")
    except KeyboardInterrupt:
        print("\n中断，全部断电。")
    finally:
        for ch in list(active):
            link.note_off(ch)
        link.panic()

    if skipped:
        lo, hi = min(skipped), max(skipped)
        print(f"\n有 {len(skipped)} 个音高不在 8 键范围内被跳过 (note {lo}~{hi})。")
        print("试试 --transpose 把它们移进 C4~C5，或者换一首只用白键的曲子。")


def main():
    ap = argparse.ArgumentParser(description="MIDI -> 8 键钢琴机器人")
    ap.add_argument("midi", nargs="?", help="MIDI 文件路径")
    ap.add_argument("--port", help="串口，如 COM3 或 /dev/ttyUSB0")
    ap.add_argument("--baud", type=int, default=115200)
    ap.add_argument("--list", action="store_true", help="列出串口后退出")
    ap.add_argument("--test", action="store_true", help="逐键测试")
    ap.add_argument("--dry-run", action="store_true", help="不连硬件，只打印")
    ap.add_argument("--transpose", type=int, default=0, help="整体移调半音数")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    if args.list:
        list_ports()
        return 0

    if not args.dry_run and not args.port:
        ap.error("需要 --port，或者用 --dry-run 空跑")
    if not args.test and not args.midi:
        ap.error("需要一个 MIDI 文件，或者用 --test")

    link = Link(args.port, args.baud, dry_run=args.dry_run)
    try:
        if args.test:
            run_test(link)
        else:
            play(link, args.midi, args.transpose, args.verbose)
    finally:
        link.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
