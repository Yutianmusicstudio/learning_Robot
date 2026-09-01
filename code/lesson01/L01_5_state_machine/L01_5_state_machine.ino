/* 第一课 · 实验 5：状态机 —— 你的第一段"真正的"机器人代码
 *
 * 这段代码和 code/phase0_single_solenoid 里的几乎一模一样。
 * 区别只有一个：现在驱动的是 LED，等电磁铁到货，
 * 把 PIN 改一下、把 SLOW_MOTION 改成 1，就是真正的钢琴机器人固件。
 *
 * 接线：D9 --[220Ω]-- LED -- GND   （必须是 PWM 引脚）
 * 操作：打开串口监视器，波特率 115200，输入 p 回车
 */

const uint8_t  PIN_OUT = 9;

// ★ 教学用的"慢动作"倍率 ★
//   真实的击键只有几十毫秒，眼睛根本看不见。
//   先设成 20 倍慢放，把过程看清楚；看懂之后改回 1，感受真实速度。
const uint16_t SLOW_MOTION = 20;

const uint16_t PEAK_MS   = 25  * SLOW_MOTION;  // 全功率"击打"阶段
const uint8_t  HOLD_DUTY = 90;                 // 保持阶段占空比（约 35%）
const uint16_t NOTE_MS   = 150 * SLOW_MOTION;  // 这个音总共按住多久

// ---- 三个状态 ----
//   IDLE 空闲  →  PEAK 全力击打  →  HOLD 低功率保持  →  IDLE
enum KeyState { IDLE, PEAK, HOLD };

KeyState state     = IDLE;
uint32_t noteStart = 0;      // 这次按下的起始时刻

void setup() {
  pinMode(PIN_OUT, OUTPUT);
  digitalWrite(PIN_OUT, LOW);          // 上电第一件事：确保是关的
  Serial.begin(115200);
  Serial.println(F("输入 p 触发一次。观察：先全亮，再变暗，最后熄灭。"));
}

void noteOn() {
  analogWrite(PIN_OUT, 255);           // 进入 PEAK：全功率
  state     = PEAK;
  noteStart = millis();
  Serial.println(F("PEAK  全功率"));
}

void noteOff() {
  digitalWrite(PIN_OUT, LOW);
  state = IDLE;
  Serial.println(F("IDLE  断电\n"));
}

// 状态推进 —— 每次 loop 都调用，内部没有任何 delay()
void updateKey() {
  if (state == IDLE) return;

  uint32_t held = millis() - noteStart;      // 已经按下多久了

  if (state == PEAK && held >= PEAK_MS) {
    analogWrite(PIN_OUT, HOLD_DUTY);         // 降到保持功率
    state = HOLD;
    Serial.println(F("HOLD  降到 35%"));
  }
  else if (state == HOLD && held >= NOTE_MS) {
    noteOff();
  }
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'p' && state == IDLE) noteOn();
  }
  updateKey();       // 永远不要在这里加 delay()
}

/* 【你应该看到】
 *   输入 p → LED 猛地全亮 0.5 秒 → 明显变暗，持续约 2.5 秒 → 熄灭
 *
 * 【这三个阶段将来对应什么】
 *   PEAK：电磁铁全电流，铁芯被猛地推出去,把琴键砸下去 —— 负责"击打"
 *   HOLD：电流降到 35%，只够把键按住不弹回 —— 负责"按住"
 *   IDLE：彻底断电
 *
 *   为什么要分开？因为电磁铁全程满功率通电，几十秒就能到 80°C 以上,
 *   会烧线圈、烤软 3D 打印件。而吸合之后维持只需要很小的电流。
 *   ——这是整个项目最关键的一个技巧。
 *
 * 【三个练习】
 *   1) 把 SLOW_MOTION 改成 1。现在你几乎看不见 PEAK 阶段了 ——
 *      这才是真实的时间尺度。感受一下"25 毫秒"有多短。
 *   2) 把 HOLD_DUTY 改成 20 再改成 200，观察亮度差别。
 *      将来这个值就是"电磁铁烫不烫"的旋钮。
 *   3) ★ 难一点：把它改成同时驱动两个 LED（D9 和 D10），
 *      输入 p 触发第一个、q 触发第二个，两者完全独立、可以重叠。
 *      —— 做出来的话，你其实已经写出 Phase 1 的骨架了。
 */
