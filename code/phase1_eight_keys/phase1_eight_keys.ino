/*
 * Phase 1 —— 8 键钢琴机器人固件（Arduino UNO/Nano）
 * ---------------------------------------------------------------
 * 功能：
 *   - 8 路独立的 peak-and-hold 状态机（每个键各自计时，互不干扰）
 *   - 8 路软件 PWM，相位错开，降低电源峰值电流
 *   - 简单串口协议，由电脑上的 play_midi.py 驱动
 *   - 力度（velocity）→ 击打强度映射
 *   - 同时导通数限制 + 看门狗式安全断电
 *
 * 【接线】D2~D9 分别接 8 路 MOSFET 驱动的输入端（其余同 Phase 0）
 *
 * 【串口协议】115200 8N1
 *   Note On :  0x80 | ch , velocity(0~127)     —— 两字节
 *   Note Off:  0x00 | ch                       —— 一字节
 *   Panic   :  0xFF                            —— 全部立刻断电
 *   ch = 0~7，对应从左到右 8 个白键（C4 D4 E4 F4 G4 A4 B4 C5）
 *
 * 【为什么不用 analogWrite】
 *   UNO 只有 6 路硬件 PWM，不够 8 路。所以自己写软件 PWM：
 *   在 loop 里高速轮询，按"当前相位 < 占空比"决定引脚高低。
 *   这要求 loop 必须跑得极快 —— 所以这里没有任何 delay()，
 *   串口也只做非阻塞读取。
 */

// ================== 配置 ==================
const uint8_t  NUM_CH = 8;
const uint8_t  PIN[NUM_CH] = {2, 3, 4, 5, 6, 7, 8, 9};

const uint16_t PEAK_MS_MIN   = 12;   // 最弱力度的击打时长
const uint16_t PEAK_MS_MAX   = 35;   // 最强力度的击打时长
const uint8_t  HOLD_DUTY     = 90;   // 保持占空比 0~255（约 35%），发烫就调低
const uint16_t PWM_PERIOD_US = 2000; // 软件 PWM 周期 → 500Hz
const uint8_t  MAX_ON        = 6;    // 允许同时导通的最大通道数（保护电源）
const uint32_t SAFETY_MS     = 3000; // 单个键最长按住时间，超时强制松开（防卡死冒烟）

// ================== 状态 ==================
enum KeyState : uint8_t { IDLE, PEAK, HOLD };

KeyState state[NUM_CH];
uint32_t noteStartMs[NUM_CH];   // 按下的时刻
uint16_t peakMs[NUM_CH];        // 本次击打的 PEAK 时长（由 velocity 决定）
uint8_t  duty[NUM_CH];          // 当前目标占空比 0~255

uint8_t  pendingCh = 0xFF;      // 协议解析：已收到 Note On 首字节，等待 velocity

void setup() {
  for (uint8_t i = 0; i < NUM_CH; i++) {
    pinMode(PIN[i], OUTPUT);
    digitalWrite(PIN[i], LOW);   // 上电立刻全关，这一步很重要
    state[i] = IDLE;
    duty[i]  = 0;
  }
  Serial.begin(115200);
}

// ---------- 计数当前有多少通道在导通 ----------
uint8_t activeCount() {
  uint8_t n = 0;
  for (uint8_t i = 0; i < NUM_CH; i++) if (state[i] != IDLE) n++;
  return n;
}

// ---------- 按下 ----------
void noteOn(uint8_t ch, uint8_t velocity) {
  if (ch >= NUM_CH) return;
  if (state[ch] == IDLE && activeCount() >= MAX_ON) return;  // 超过并发上限就丢弃

  // velocity(1~127) → PEAK 时长：越用力，全功率冲击的时间越长
  uint16_t p = PEAK_MS_MIN +
               ((uint32_t)(PEAK_MS_MAX - PEAK_MS_MIN) * velocity) / 127;

  peakMs[ch]      = p;
  duty[ch]        = 255;         // PEAK 阶段全功率
  state[ch]       = PEAK;
  noteStartMs[ch] = millis();
}

// ---------- 松开 ----------
void noteOff(uint8_t ch) {
  if (ch >= NUM_CH) return;
  duty[ch]  = 0;
  state[ch] = IDLE;
  digitalWrite(PIN[ch], LOW);
}

void panic() {
  for (uint8_t i = 0; i < NUM_CH; i++) noteOff(i);
}

// ---------- 状态机推进 ----------
void updateStates() {
  uint32_t now = millis();
  for (uint8_t i = 0; i < NUM_CH; i++) {
    if (state[i] == IDLE) continue;

    uint32_t held = now - noteStartMs[i];

    if (held >= SAFETY_MS) {     // 安全兜底：上位机崩了也不会一直通电
      noteOff(i);
      continue;
    }
    if (state[i] == PEAK && held >= peakMs[i]) {
      duty[i]  = HOLD_DUTY;      // 冲击结束，降到保持电流
      state[i] = HOLD;
    }
  }
}

// ---------- 软件 PWM ----------
void servicePwm() {
  uint32_t now = micros();
  for (uint8_t i = 0; i < NUM_CH; i++) {
    if (duty[i] == 0)   { digitalWrite(PIN[i], LOW);  continue; }
    if (duty[i] == 255) { digitalWrite(PIN[i], HIGH); continue; }

    // 每个通道的 PWM 相位错开 1/8 周期：
    // 避免 8 路在同一瞬间一起导通，把电源的峰值电流削掉一大半
    uint16_t phase = (now + (uint32_t)i * (PWM_PERIOD_US / NUM_CH)) % PWM_PERIOD_US;
    uint8_t  level = (uint32_t)phase * 256UL / PWM_PERIOD_US;   // 0~255
    digitalWrite(PIN[i], duty[i] > level ? HIGH : LOW);
  }
  // 注：micros() 约 71 分钟溢出一次，取模会有一个周期的相位跳变，无害。
}

// ---------- 协议解析（非阻塞） ----------
void serviceSerial() {
  while (Serial.available()) {
    uint8_t b = Serial.read();

    if (pendingCh != 0xFF) {          // 正在等 velocity
      noteOn(pendingCh, b & 0x7F);
      pendingCh = 0xFF;
      continue;
    }
    if (b == 0xFF) { panic(); continue; }

    if (b & 0x80) pendingCh = b & 0x07;   // Note On 首字节，等下一个字节
    else          noteOff(b & 0x07);      // Note Off
  }
}

void loop() {
  serviceSerial();
  updateStates();
  servicePwm();     // 必须每次 loop 都跑，且 loop 要足够快（当前约几十 µs）
}

/*
 * 【调试指引】
 * 和弦时某些键敲不响 → 电源掉压。加大电源、加大电容，或调低 MAX_ON。
 * 声音有 500Hz 蜂鸣 → 软件 PWM 的频率，属正常。Phase 3 换硬件定时器提到 20kHz 以上可消除。
 * 音符时序不准 → digitalWrite 较慢，通道多了 loop 会变慢。这正是 Phase 3 要迁移到 STM32 的原因。
 * 上位机崩溃后有键卡住 → SAFETY_MS 会在 3 秒内自动松开；也可以手动发 0xFF。
 */
