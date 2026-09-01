/*
 * Phase 0 —— 单电磁铁 peak-and-hold 测试
 * ---------------------------------------------------------------
 * 目标：让一个电磁铁稳定敲响一个琴键，并且长时间工作不发烫。
 *
 * 【接线】
 *   Arduino D3 --[220Ω]--> MOSFET 栅极 G （栅极再用 10kΩ 下拉到 GND）
 *   MOSFET 漏极 D --> 电磁铁负极
 *   MOSFET 源极 S --> GND（必须与 12V 电源的 GND 连在一起！）
 *   12V+ --> 电磁铁正极
 *   电磁铁两端反并联 1N4007/1N5819，白环（阴极）朝 12V+ 那一端
 *   12V 电源两端并联 1000µF 电解电容
 *
 * 【核心概念：peak-and-hold（先冲后保）】
 *   电磁铁需要"大电流"才能快速吸合，但吸合之后只需要很小的电流就能保持。
 *   如果全程 100% 通电：
 *     - 线圈持续发热，几十秒就能到 80°C，会烧线圈、烤软 PLA 打印件
 *   所以分两个阶段：
 *     PEAK：100% 全功率，持续 PEAK_MS 毫秒 —— 负责"击打"
 *     HOLD：PWM 降到 HOLD_DUTY/255，直到松开 —— 只负责"按住"
 *   这是本项目最重要的一个技巧。
 *
 * 【为什么用 millis() 而不是 delay()】
 *   delay() 会卡住整个程序。Phase 1 要 8 个键各自独立计时，
 *   用 delay() 必然失败。所以从第一行代码起就用非阻塞状态机。
 */

const uint8_t  PIN_SOLENOID = 3;    // 必须是支持 PWM 的引脚（UNO: 3,5,6,9,10,11）

const uint16_t PEAK_MS    = 25;     // 全功率击打时长(ms)。太短敲不响，太长发热且没意义
const uint8_t  HOLD_DUTY  = 90;     // 保持阶段 PWM 占空比 0~255（90 ≈ 35%）
const uint16_t NOTE_MS    = 150;    // 这个音符总共按住多久
const uint16_t GAP_MS     = 350;    // 两次敲击之间的间隔

// ---- 一个键的状态机 ----
enum KeyState { IDLE, PEAK, HOLD };

KeyState state      = IDLE;
uint32_t stateStart = 0;   // 进入当前状态的时刻
uint32_t noteStart  = 0;   // 这个音符按下的时刻

void setup() {
  pinMode(PIN_SOLENOID, OUTPUT);
  digitalWrite(PIN_SOLENOID, LOW);   // 上电第一件事：确保是关的
  Serial.begin(115200);
  Serial.println(F("Phase0: 输入 'p' 敲一次；'a' 自动循环；'s' 停止"));
}

// 按下：进入 PEAK 阶段
void noteOn() {
  analogWrite(PIN_SOLENOID, 255);    // 全功率
  state      = PEAK;
  stateStart = millis();
  noteStart  = millis();
}

// 松开：彻底断电
void noteOff() {
  digitalWrite(PIN_SOLENOID, LOW);
  state = IDLE;
}

// 每次 loop 都调用，负责状态推进（非阻塞）
void updateKey() {
  uint32_t now = millis();

  switch (state) {
    case IDLE:
      break;

    case PEAK:
      if (now - stateStart >= PEAK_MS) {
        analogWrite(PIN_SOLENOID, HOLD_DUTY);   // 降到保持电流
        state      = HOLD;
        stateStart = now;
      }
      break;

    case HOLD:
      if (now - noteStart >= NOTE_MS) {         // 到时间了就松开
        noteOff();
      }
      break;
  }
}

bool autoMode = false;
uint32_t lastTrigger = 0;

void loop() {
  // --- 串口命令 ---
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'p' && state == IDLE) { noteOn(); }
    if (c == 'a') { autoMode = true;  Serial.println(F("自动模式")); }
    if (c == 's') { autoMode = false; noteOff(); Serial.println(F("停止")); }
  }

  // --- 自动循环敲击，用来做发热测试 ---
  if (autoMode && state == IDLE && millis() - lastTrigger >= (uint32_t)(NOTE_MS + GAP_MS)) {
    lastTrigger = millis();
    noteOn();
  }

  updateKey();   // 状态机推进，永远不要在这里加 delay()
}

/*
 * 【调试指引】
 * 敲不响？
 *   1) 电磁铁离琴键太远 —— 行程不够，把它压低，让铁芯静止时几乎贴着键
 *   2) PEAK_MS 太短 —— 试着加到 40
 *   3) 推力不足 —— 换更大推力型号，或在铁芯上加一点配重增大冲击动能
 *   4) 框架太软 —— 反作用力把支架顶起来了，用铝型材加固
 * 发烫？
 *   1) HOLD_DUTY 调低到 60 甚至 45（能保持住就行）
 *   2) 检查 analogWrite 用的引脚是不是 PWM 引脚（不是的话它只会输出高/低电平）
 * Arduino 一敲就重启？
 *   1) 电源功率不够 / 没并 1000µF 电容
 *   2) GND 线太细，换粗线
 * 有"咔咔"电流噪声？
 *   PWM 频率落在音频范围内。Phase 3 用 STM32 硬件定时器可以把频率提到 20kHz 以上。
 */
