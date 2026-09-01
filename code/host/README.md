# 上位机（Phase 1）

## 安装

```bash
pip install -r requirements.txt
```

## 使用顺序

```bash
# 1. 找到串口
python play_midi.py --list

# 2. 不接硬件先空跑，确认 MIDI 解析正常
python play_midi.py --dry-run -v twinkle.mid

# 3. 接上硬件，逐键测试接线顺序（应从左到右依次响）
python play_midi.py --port /dev/ttyUSB0 --test

# 4. 演奏
python play_midi.py --port /dev/ttyUSB0 twinkle.mid
```

## 找测试用的 MIDI

- 用 **MuseScore**（免费）自己打一段只用 C4~C5 白键的旋律，导出 MIDI。
- 或搜 "twinkle twinkle little star midi"、"ode to joy midi"。
- 音高超出 8 键范围的音符会被自动跳过并在结束时提示，可用 `--transpose` 整体移调。

## 排查

| 现象 | 原因 |
|---|---|
| 打开串口后前 2 秒没反应 | Arduino 开串口会自动复位，脚本已 `sleep(2)` 等它启动 |
| 一个键响、其他不响 | 接线顺序或 MOSFET 通道问题，先跑 `--test` |
| 快速乐句丢音 | 固件 `MAX_ON` 并发上限拦掉了，或电源掉压 |
| 曲子结束后还有键按着 | 该 MIDI 用了 `note_on velocity=0` 表示松开——脚本已处理；若仍卡住，固件的 `SAFETY_MS` 会在 3 秒内强制断电 |
