# 检索关键词与领域空白

> 用途：判断"钢琴版 mini Shimon"能不能作为研究提出，以及去哪里、用什么词检索。

---

## 一、这个领域的正式术语（先把词用对）

| 术语 | 含义 | 注意 |
|---|---|---|
| **Robotic Musicianship** | **musical mechatronics + machine musicianship**。包含 agency 与 robot persona | ★ Weinberg 的定义，也是 GTCMT 的旗号。**这是核心检索词** |
| **Musical Mechatronics** | 只做乐器的驱动与控制，**不涉及 agency 或 persona** | 一个纯电磁铁钢琴阵列属于这一类 |
| **Machine Musicianship** | 音乐感知、作曲、演奏的算法与认知模型（Rowe 的书名） | |

**这个区分对你很重要**：固定电磁铁阵列 = musical mechatronics；
**加上头、加上互动 = robotic musicianship**。你所在的实验室是后者的大本营。

---

## 二、发表的门槛长什么样

参考你们实验室自己的 **NIME 2020**：*Mechatronics-Driven Musical Expressivity for Robotic Percussionists*（arXiv:2007.14850）——把 Shimon 的执行器换成无刷电机。

它的结构就是这类论文的模板：

```
新的执行方案（BLDC 取代电磁铁）
  → 与现有方案的对照实验
  → 感知层面的量化结果（主观听测）
  → 结论：显著优于电磁铁方案，且与人类演奏者在统计上不可区分
```

**"我造了一台 X 的机器人"本身不是贡献。** 贡献 = 新机制 / 新交互 / 新评估 + 能量化的结果。

### ⚠️ 一条必须先知道的事

**那篇论文已经证明：在音乐表现力上，电磁铁方案显著劣于无刷电机方案。**

也就是说——**一个以电磁铁阵列为主体的钢琴机器人，等于在和你们实验室自己发表的结论唱反调。**
提之前必须准备好回答："为什么钢琴上还用电磁铁？"

（可回答的方向：钢琴需要同时按下多个键并**保持**，移动执行器做不到；
但这恰恰说明**混合架构本身需要论证**，而不是默认成立。）

---

## 三、四个真实的空白（按适合你的程度排序）

### ★ 1. BLDC 击键 —— 把你们实验室的结论迁移到键盘上
**空白**：NIME 2020 证明了 BLDC 在**打击**上优于电磁铁。**没有人做过键盘按压的对应实验。**

而钢琴与打击乐有本质差异：**擒纵机构**使琴槌在撞弦前脱离传动、自由飞行——
执行器无法"跟随到底"，它只能向一个杠杆输入一个冲量。
**所以那个结论会不会迁移，是一个真问题，不是显然的。**

- 贡献形态：新执行方案 + 对照 + 听测（**范式现成，直接复用那篇论文的方法**）
- 优势：**是对本实验室已发表工作的直接延伸**，最容易获得支持
- 检索词：`BLDC actuator keyboard` `direct-drive actuator musical` `key depression actuator`

### 2. 连续踏板控制（半踏板）
**空白**：文献明确指出——**MIDI 把延音踏板当成开关**，无法表达真实钢琴的连续踏板；
而半踏板、抖踏板、una corda 的层次是钢琴音乐性的核心。
（Godfried-Willem Raes 的 pedal robot 提到：要做渐进踏板动作，电磁铁需要 33–66V 过驱。）

- 贡献形态：力/位置闭环的踏板执行器 + 控制模型 + 感知评估
- 优势：小、独立、可单独成文
- 检索词：`half-pedaling` `sustain pedal depth` `continuous pedal control` `damper pedal actuation`

### 3. 用踏板换执行器数量
**空白**：延音踏板放松了"手指必须按住"这个约束 → 需要的手指更少。
**这个取舍曲线没人量化过。**

先例支持这类贡献：mechatronic chordophone 的研究中，
用夹持机构同时实现按弦与制音，**明确以"减少执行器数量"作为贡献**。

- 贡献形态：机构设计 + 调度算法 + 取舍曲线
- 检索词：`actuator count reduction` `mechatronic chordophone damping` `polyphony constraint robot`

### 4. 键盘乐器上的社会信号
**空白**：Shimon 用头部动作预告节拍与注意力——但马林巴的**臂部动作本身可见**。
钢琴上手部动作小且常被遮挡。**一个键盘机器人该如何传达预期与呼吸？**

- 贡献形态：具身交互设计 + 人因评估（偏 HRI/NIME 那一侧）
- 检索词：`anticipatory action` `embodied musical interaction` `robot gesture beat`

---

## 四、检索关键词总表

### 领域核心
```
robotic musicianship
musical mechatronics
machine musicianship
mechatronic musical instrument
robotic musical instrument
actuated instrument / augmented instrument
```

### 钢琴专门
```
player piano / reproducing piano
piano action / grand piano action
escapement / let-off
hammer velocity
key depression / keystroke dynamics
touch and tone
sustain pedal / damper pedal / half-pedaling / pedal depth
sostenuto
```

### 执行与控制
```
solenoid actuator / peak and hold driving
BLDC / brushless DC actuator / direct-drive actuator
voice coil actuator
series elastic actuator
impedance control / admittance control
actuator count reduction
```

### 算法侧
```
piano fingering / automatic fingering / fingering assignment
expressive performance rendering
anticipatory action
score following / musical accompaniment system
human-robot musical interaction
```

### 评估侧
```
perceived musical expressivity
subjective listening test
musical Turing test
```

### 组合式检索（可直接粘贴）
```
"robotic musicianship" piano
"musical mechatronics" keyboard actuator
"player piano" solenoid expressive control
piano robot "hammer velocity" actuator
"half-pedaling" OR "pedal depth" robot piano
"actuator count" musical robot polyphony
BLDC actuator musical expressivity listening test
```

---

## 五、去哪里搜

| 场所 | 说明 |
|---|---|
| ★ **nime.org/archives** | **NIME 全文可检索存档**。这个领域最高产的地方，先搜这里 |
| **GTCMT 发表列表** | ★★ **社交成本为零，且直接告诉你本地的标准**。任何提案都必须相对它定位 |
| ICMC · SMC · ISMIR | 计算机音乐/声音与音乐计算/音乐信息检索 |
| ACM/IEEE **HRI** | 社会信号、具身交互那一侧 |
| **JASA** · Acta Acustica | 击弦机与触键的物理 |
| Journal of New Music Research | 演奏科学、表现力 |
| Google Scholar 反向引用 | 找到一篇对的，看**引用它的**论文 |

**开工第一步：把 GTCMT 的发表列表整页扫一遍。** 零社交成本，而且它会告诉你——
哪些已经被做过、本地的门槛在哪、以及你的提案该挂在谁的哪篇后面。
