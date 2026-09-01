/* 第一课 · 实验 4：非阻塞 —— 用 millis() 代替 delay()
 *
 * 同一个任务，这次真的能做到：A 每 500ms，B 每 300ms，互不干扰。
 * 接线同实验 3。
 *
 * 【核心思路的转变】
 *   delay 的思路：  "现在等 500 毫秒"        —— 命令时间
 *   millis 的思路： "现在几点了？到点了就做" —— 查看时间
 *
 *   millis() 返回单片机开机到现在的毫秒数，是一个一直在走的钟。
 *   你不去停住它，只是不停地问它"到点了吗"。
 */

const uint8_t LED_A = 8;
const uint8_t LED_B = 9;

const uint16_t PERIOD_A = 500;
const uint16_t PERIOD_B = 300;

uint32_t lastA = 0;        // A 上一次翻转的时刻
uint32_t lastB = 0;
bool stateA = false;
bool stateB = false;

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  uint32_t now = millis();   // 看一眼钟

  if (now - lastA >= PERIOD_A) {   // A 到点了吗？
    lastA = now;                   // 到了：记下这一刻
    stateA = !stateA;              //      翻转状态
    digitalWrite(LED_A, stateA);
  }

  if (now - lastB >= PERIOD_B) {   // B 到点了吗？（和 A 完全独立）
    lastB = now;
    stateB = !stateB;
    digitalWrite(LED_B, stateB);
  }

  // loop 在这里飞快地转圈，每秒几万次。
  // 它从不停下，所以任何时刻任何一个任务到点了都能被立刻处理。
}

/* 【要注意的两个细节】
 *
 * 1) 为什么写 `now - lastA >= PERIOD_A` 而不是 `now >= lastA + PERIOD_A`？
 *    millis() 大约 49.7 天会溢出归零。写成减法的形式，
 *    利用无符号数的回绕特性，溢出时依然正确；写成加法就会出错。
 *    这是嵌入式里的标准写法，照抄就对。
 *
 * 2) 变量必须是 uint32_t（不是 int）。
 *    int 在 UNO 上只有 16 位，最大 32767，32 秒就溢出了。
 *
 * 【验证你真的做到了非阻塞】
 *    加第三个 LED，周期 137ms。三个灯应该毫无关系地各闪各的。
 *    如果做得到 —— 你已经掌握了本项目最重要的编程概念。
 */
