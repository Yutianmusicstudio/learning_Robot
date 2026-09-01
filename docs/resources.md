# 学习资源清单（精选，不求全）

原则：**每个方向只给 1~2 个**。资源太多本身就是拖延的借口。

---

## 电子

| 资源 | 说明 |
|---|---|
| **《Practical Electronics for Inventors》**（Paul Scherz） | 面向动手者的电子学，**只看第 2、4 章**（无源器件、晶体管/MOSFET）就够 Phase 0 用 |
| 《The Art of Electronics》 | 神书但太厚，当字典查，不要通读 |
| **B 站/YouTube 搜 "MOSFET 驱动 电磁铁"** | 30 分钟视频胜过 3 小时看书，重点看接线和续流二极管 |
| **万用表使用教程** | 任意一个 20 分钟视频，学会量电压/通断/电流 |

## Arduino / 嵌入式

| 资源 | 说明 |
|---|---|
| **Arduino 官方 Language Reference** | 只需要看 `millis()`、`analogWrite()`、`attachInterrupt()`、`Serial` 四页 |
| **本仓库 `code/` 目录** | 代码里的中文注释就是教程，逐行读懂比看视频有用 |
| **正点原子 / 野火 STM32 教程** | Phase 3 用。跟着 GPIO → 定时器 → PWM → 中断 → USART → USB 这条主线走，其余章节跳过 |
| **STM32CubeMX 官方入门** | 图形化配置引脚和时钟，是现代 STM32 开发的标准起点 |

## 机器人学（Phase 4 才看）

| 资源 | 说明 |
|---|---|
| **《Modern Robotics》**（Lynch & Park） | ⭐ **本领域最好的入门书，官网提供免费 PDF**，配套 Coursera 专项课（有中文字幕）和 Python 库。重点看第 3（刚体运动）、4（正运动学）、6（逆运动学）、9（轨迹生成）章 |
| **《Robotics, Vision and Control》**（Peter Corke） | 偏工程实践，配 MATLAB/Python 工具箱；作者的 Robot Academy 有免费短视频 |
| **PyBullet Quickstart Guide** | 官方文档，直接从例子改 |
| **MuJoCo 官方文档 + `mujoco_menagerie`** | menagerie 里有大量现成机器人模型可以拆解学习 |

## CAD / 3D 打印

| 资源 | 说明 |
|---|---|
| **Autodesk Fusion 360 官方学习中心** | 免费官方教程，按 Sketch → Extrude → Parameters → Assembly 顺序 |
| **Product Design Online**（YouTube） | "Learn Fusion 360 in 30 Days" 系列，本项目看前 10 天足够 |
| **B 站搜 "Fusion360 参数化建模"** | 中文，重点找讲 Parameters 和装配的 |
| **开源机械参考**：Voron 3D 打印机、AR4 机械臂、BCN3D Moveo | 直接下载工程文件看别人怎么设计连接结构，比教程有用 |

## MIDI / 音乐编程

| 资源 | 说明 |
|---|---|
| **`mido` 文档** | Python MIDI 库，本项目上位机就用它 |
| **MuseScore**（免费） | 打谱、查看/导出 MIDI、验证音符编号 |
| MIDI 1.0 规范摘要 | 只需要 Note On/Off、Velocity、Tempo 这几节 |

## 参考项目（直接看别人做过什么）

搜索关键词（英文效果好得多）：
- `solenoid piano robot` / `player piano MIDI solenoid`
- `Arduino MIDI solenoid controller`
- `robotic piano player hackaday`
- `peak and hold solenoid driver`（专门找驱动电路方案）
- 学术方向：`Robot pianist`、`Anthropomorphic robot hand piano`、丰田 Partner Robot 的钢琴演示、Shimon（Georgia Tech 音乐机器人）

Hackaday、Instructables、GitHub 上有大量完整的 solenoid piano 项目，**开工前花两小时看 5 个别人的成品**，能省下你一个月的弯路。

---

## 学习方法上的三条建议

1. **不要"学完再做"。** 每个 Phase 只学那个 Phase 需要的知识，做出东西再学下一块。机器人是典型的"做中学"领域。
2. **写工程日志。** 在这个仓库里开一个 `log/` 目录，每次调试记录：改了什么、现象是什么、结论是什么。三个月后你会感谢自己——尤其是硬件问题，很多"玄学 bug"靠日志才能定位。
3. **卡住超过 2 小时就去搜英文关键词。** 中文社区在机器人/电子领域的深度内容远少于英文。
