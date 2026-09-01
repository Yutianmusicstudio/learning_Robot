/* 第一课 · 实验 3：delay() 的陷阱 —— 本课最重要的一个实验
 *
 * ★ 先自己试，失败了再看实验 4。不要跳过这一步。★
 *
 * 任务：LED_A 每 500ms 翻转一次，LED_B 每 300ms 翻转一次。
 *      两个各闪各的，互不影响。
 *
 * 接线：D8 --[220Ω]-- LED_A -- GND
 *      D9 --[220Ω]-- LED_B -- GND
 *
 * 下面是几乎所有新手会写出的第一版。烧进去，看着它，然后回答问题。
 */

const uint8_t LED_A = 8;
const uint8_t LED_B = 9;

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop() {
  digitalWrite(LED_A, HIGH);
  delay(500);
  digitalWrite(LED_A, LOW);
  delay(500);

  digitalWrite(LED_B, HIGH);
  delay(300);
  digitalWrite(LED_B, LOW);
  delay(300);
}

/* 【观察】它其实是这样跑的：
 *      A 亮 500ms → A 灭 500ms → B 亮 300ms → B 灭 300ms → 循环
 *   两个灯在"排队"，不是各闪各的。
 *   而且 A 的周期变成了 1600ms，完全不是你要的 1000ms。
 *
 * 【为什么】delay(500) 的含义是：
 *      "这颗 CPU 接下来 500ms 什么都不做，只是空转数数。"
 *   在这 500ms 里，B 不能被处理，串口不能被读取，什么都不能发生。
 *   delay() 不是"等待"，是"瘫痪"。
 *
 * 【自己动手改一改，你会发现改不出来】
 *   试试把两组 delay 拆细、交错……你能勉强凑出这个特例，
 *   但只要把周期改成 500ms 和 317ms，或者加到 8 个 LED，就彻底崩溃。
 *
 * 【这对钢琴机器人意味着什么】
 *   一个和弦 = 3 个键同时按下，各自有不同的击打时长和松开时刻。
 *   8 个键 = 8 套互相独立的计时。用 delay() 一个都做不到。
 *
 *   所以：**从今天起，你的代码里不再出现 delay()。**
 *   （实验 1、2 里用了，那是为了教学，从实验 4 开始就戒掉。）
 *
 * 现在去看实验 4。
 */
