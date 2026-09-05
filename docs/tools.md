# 工具与软件清单（按阶段）

配套 `build-plan.md`。原则同 `resources.md`：每个用途只给一两个，选定就不换。

## P0–P3　机械与电子

| 用途 | 工具 | 说明 |
|---|---|---|
| CAD | **Fusion 360**（教育版免费）或 Onshape（教育版免费） | 支架、触键结构、分段机架。GT 大概率也有 SolidWorks 授权，问实验室 |
| 参数化 CAD（可选） | **CadQuery / build123d**（Python） | 用代码写零件。适合"同一个支架改 44 个尺寸变体"这类事，也是 AI 辅助最能用上的 CAD 路径 |
| 切片 | 实验室打印机对应的切片软件（PrusaSlicer / Bambu Studio / Cura） | 用哪台机器就用它的 |
| 电路仿真 | **LTspice**（免费） | peak-and-hold 驱动、续流二极管、MOSFET 开关波形。多路并发的电源峰值也在这里算 |
| 电磁铁选型 | 厂商力—行程曲线；自己绕线圈才用 **FEMM** | 优先买有曲线的成品 |
| PCB | **KiCad**（免费开源） | 第一块模块板。GT 若有 Altium 授权也可以，但 KiCad 够用且不绑定学校 |
| 固件 | Arduino IDE 起步 → **PlatformIO**（VS Code 插件）| 项目超过一个文件就换 PlatformIO。后期走 STM32 用 STM32CubeIDE |
| 测量 | 示波器（实验室）；**PulseView + 便宜的逻辑分析仪**；Audacity | 延迟测量：驱动信号一路、麦克风一路，读时间差 |

## P2 / P4　软件与合奏

| 用途 | 工具 | 说明 |
|---|---|---|
| MIDI 收发 | Python：**mido + python-rtmidi** | 键盘进、机器人出 |
| 符号乐谱 | **partitura**（CPJKU）；MuseScore 做谱面编辑并导出 MusicXML/MIDI | 提案里已引用 partitura |
| 乐谱跟随 | **ACCompanion**（CPJKU，开源）作为参照实现；CPJKU 的 **matchmaker** 库做实时对齐（待确认版本与接口）；自己写则用 DTW/HMM | 提案已声明不主张算法贡献，直接站在这些之上 |
| 虚拟 MIDI 端口 | macOS：IAC Driver；Windows：loopMIDI | 软件阶段把跟随器和音源接起来 |
| DAW（可选） | Reaper | 录人—人基线、录合奏对比 |

## P5–P8　感知与学习

| 用途 | 工具 | 说明 |
|---|---|---|
| 手部关键点 | **MediaPipe Hands**；OpenCV | 预备动作 → 音头预测的输入 |
| 相机 | 全局快门、≥120 fps 的 USB3 工业相机（Basler / FLIR 一类），或 OAK-D | 30 fps 的网络摄像头一帧就是 33 ms，做预判不够 |
| 深度学习 | PyTorch | |
| 光学识谱（P6 后期） | Audiveris（开源 OMR） | 见 `vision-omr-assessment.md` |

## 文献与写作

| 用途 | 工具 |
|---|---|
| 检索 | Semantic Scholar、Connected Papers（找一篇论文的邻居）|
| 管理 | Zotero（自动生成 BibTeX，和 Overleaf 联动）|
| 写作 | Overleaf |

## AI 辅助：哪里能用、哪里别信

**能放心用的**
- **写固件和 Python**（Claude Code / Cursor / Copilot）：状态机、MIDI 解析、串口协议、数据处理脚本。这是 AI 目前最强的地方。
- **写 CadQuery / OpenSCAD 代码**：因为 CAD 变成了代码，AI 能直接产出参数化零件。比"文字生成 CAD"那类产品靠谱得多。
- **读数据手册、解释电路、审查原理图描述**：例如"这个电磁铁驱动缺什么"，AI 能指出续流二极管、栅极电阻、共地这类遗漏。
- **文献初筛**：给关键词、给方向。

**必须自己核对的**
- **任何具体数值**：引脚号、电阻值、电流额定、时间常数。AI 给的数要对照数据手册。
- **任何"没人做过"**：本项目已经三次被打脸。每一条新颖性主张都要自己检索到原文。
- **文献元数据**：作者、年份、卷期页。AI 会编造看起来合理的引用。用 Zotero 从 DOI 抓，不手抄。

**基本别指望的**
- 文字直接生成机械 CAD（Zoo 一类产品）：对支架这种简单件，手画更快。
- PCB 自动布局：Flux.ai 有 AI 助手，但布局还是要自己做、自己审 DRC。
- 用 AI 替代实测：延迟、力度曲线、发热，这些数只能从台架上来。
