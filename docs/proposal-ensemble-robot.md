# 方案基础：从"即兴伴奏"到"真正的合奏"

> 基于对 Wang, Zhang & Iida, *Human–Robot Cooperative Piano Playing With Learning-Based
> Real-Time Music Accompaniment*, **IEEE T-RO vol. 40, 2024**（arXiv:2409.11952）的全文阅读。
> 这是目前唯一一个经过"读原文 + 两轮外围检索"仍然站得住的候选。

---

## 一、剑桥到底做了什么（读原文，不看新闻）

| 项 | 原文事实 |
|---|---|
| **硬件** | UR5 机械臂 + 软硬混合拟人手（3D 打印骨架 + 硅胶皮），Kawai ES8 数字钢琴，MATLAB |
| **任务** | 人弹**旋律（右手）**，机器人弹**和弦伴奏（左手）**。论文自称 **homophony**（主调音乐） |
| **和弦库** | **共 7 个**：3 大三和弦、3 小三和弦、1 减三和弦 |
| **模型** | RNN，**训练于流行歌曲**，从旋律预测和弦，93% 准确率 |
| **输入通道** | **只有 MIDI**（"Our approach to human–robot communication relies on MIDI"） |
| **同步** | MPC 控制器调节横移速度，把换和弦塞进拍子里 |
| **评估** | 击键时序动力学；Shannon 熵 / 传递熵 / Granger 因果 |

### 论文自己写明的局限（逐条引用）

1. **和弦库被硬件砍成 7 个**
   > "Due to hardware limitations, we simplified the tuning system and focused on several specific chords."

2. **机械臂太慢**
   > "Due to the hardware limitation (UR5 is not agile/fast enough), the required motion speed … should be dynamically adjusted."
   最坏情况（G→F 换和弦）要从击键时间里偷时间去补横移。

3. **架构性的一拍延迟**
   > "Only when all 16 tokens of the melody have been fed into the RNN model can the model give a chord prediction.
   > This means that the robot cannot improvise on the current bar at the same time, **resulting in a lag**."
   ——因为**只靠 MIDI**，必须等整个小节弹完才能预测。

4. **"好不好听"被明确推迟**
   > "Evaluating whether a listener 'enjoys' the music involves psychological and subjective analysis."

5. **自己列的未来工作**
   > "Enhancing the dexterity of the end-effector is crucial … Future work can be developed by incorporating more chords."

6. **安全**：提出以后要给 UR5 加距离/力传感器，防止臂撞到人。

### 他们的自我定位
> "To the best of the authors' knowledge, this work marks the **first instance** of … a collaborative robot expressly
> engineered to work with humans in the artistic pursuit of piano playing."

**一个"first instance"，带着六条自述局限。这正是后续工作该长出来的地方。**

---

## 二、他们的六条局限，对应你的三样资产

| 剑桥的局限 | 对应资产 | 具体动作 |
|---|---|---|
| 7 个和弦 / UR5 太慢 / 端效器不够灵巧 / 臂的安全问题 | **实验室的执行机构经验** | **全键盘覆盖**：固定电磁铁阵列（GuitarBot 式）或轨道（Shimon 式）。固定阵列同时解决了安全问题——没有臂在人手边挥 |
| 只有 MIDI → 必须等整小节 → 一拍延迟 | **你的演奏者知识** | **视觉预判**：钢琴家的手在触键前 100–300ms 就在移动。你知道搭档在读什么线索 |
| "好不好听"是主观的，推迟 | **你的 EEG** | **人—机 hyperscanning**：不问听众评分，测两个大脑（人与机器人搭档）之间的耦合 |

**每一条对得上。这不是"钢琴 + 概念"的模板，这是"一篇已发表的 first instance + 我恰好有它缺的三样东西"。**

---

## 三、真正的贡献不是"做大"，是换了问题类别

| | 剑桥 | 提议 |
|---|---|---|
| 问题 | **即兴**：为未知旋律生成和弦 | **合奏**：演奏**写定的**四手联弹第二声部 |
| 曲目 | 流行歌，7 个和弦 | 柴可夫斯基 / 舒伯特 / 拉威尔的四手联弹 |
| 难点 | 弹**什么** | **何时、如何**与你一起弹——rubato、呼吸、句法 |
| 信息通道 | MIDI（事后） | MIDI + **视觉预判**（事前） |
| 评估 | 击键时序 | 时序 + **脑间同步** |

**"弹什么"是生成问题；"怎么跟你一起弹"是合奏问题。后者才是演奏者真正关心的，而且它需要一个演奏者来定义。**

---

## 三·五、修正（读过 GTCMT 自己的论文之后）

**"视觉预判"不是缺口。** GTCMT 的纲领（*Robotic Musicianship*，Springer 2020）五条原则之一就是
**"Watch and Learn"**；Shimon 自 2010 年起就有 anticipatory action 框架，并结合视觉与音频做实时节拍跟踪。
2024 年 *Music, body, and machine* 进一步证明了非演奏性手势对人机同步的贡献。
**多模态预判在本实验室是已建立的能力，不是待填的空白。**

另：书中列有 **Skywalker Piano Hand**（可穿戴钢琴机器手，"Wear It" 线）——实验室从假肢方向碰过钢琴。

### 提案核心因此转移：共享乐器约束

Shimon 的全部同步工作——含 2024 那篇——建立在**"人与机器人各有各的乐器"**这一前提上。钢琴把它拿掉了：

| Shimon 的前提 | 钢琴打破了它 |
|---|---|
| 各有各的乐器 | **同一个键盘、同一块音板**，声音物理上不可分离 |
| 敲完槌即自由 | **手指必须按住**，一个四音和弦锁死四个执行器 |
| 没有共享的表达参数 | **踏板**——不可分割的连续参数，影响双方 |
| 执行器直接触碰发声体 | **隔着击弦机与擒纵**，间接执行 |

**提案不是 "Shimon for piano"，而是："Shimon 的同步框架在共享乐器约束下会发生什么？"**

最硬的一个具体问题：2024 那篇证明手势通道帮助同步——**但那是隔着两件乐器。当两双手在同一个键盘上相距 30 厘米，
手势通道会被什么替代？触觉？共享音板的振动？还是不再需要？** Shimon 答不了，因为它永远坐在自己的马林巴后面。

### 判据
**能否说出一条 Shimon 的现有结论在钢琴上会失效的具体理由？** 能 → 提案；不能 → 只是换机器人。

## 四、外围证据

- **视觉预判的"缺口"有人点名了**：Tipiano（arXiv:2604.09692，2026）请职业钢琴家评估后，
  **"identified anticipatory motion as the key remaining gap"**——但那是针对手部动作**合成**，不是用于实时驱动共演者。
- **训练数据已经存在**：FürElise（SIGGRAPH Asia 2024）——15 位精英钢琴家、153 首、约 10 小时多视角无标记动捕 + 高分辨率 MIDI；
  SKY-Piano（2026.07）；PianoVAM（2025.09）。**从手部视频学预判模型，数据是现成的。**
- **脑间同步的基线是钢琴**：Frontiers Hum Neurosci 2021，20 对钢琴家，无线 EEG hyperscanning，
  二重奏搭档的脑振荡相关性显著高于伪配对。**人—人已建立；人—机未见。**
- **手势同步的 HRI 工作**：*Music, body, and machine: gesture-based synchronization in human-robot musical interaction*（2024）——
  相邻工作，需读，确认没有覆盖"从手部动作预判击键"。
- **到目前为止未发现对剑桥系统的直接延伸**（2025–2026）。

---

## 五、诚实的风险

| 风险 | 程度 | 说明 |
|---|---|---|
| **跟谱算法是成熟领域** | 高 | Raphael 的 Music Plus One、IRCAM 的 Antescofo。**贡献必须定位为集成与物理约束，不能声称算法新** |
| 有人先一步延伸剑桥 | 中 | 论文 2024 年末，到 2027 出后续很正常。**每季度重查** |
| 视觉预判用于共演是否真空白 | 中 | 相邻工作密集（Tipiano、FürElise、手势同步 HRI）。**需再查一轮** |
| 人—机 hyperscanning 是否有人做 | 中 | 非音乐 HRI 里可能有。**你自己去查** `human-robot hyperscanning` |
| 规模 | 高 | 三条线各是一个项目。**必须分阶段，且允许任何一条单独成文** |
| 我的命中率 | — | 本对话里"没人做过"已错多次。**默认 50% 已被做过，直到你自己确认** |

---

## 六、分阶段（每一段可独立成文）

```
阶段 I   合奏跟随（软件）
         Disklavier 或实验室现有机器人 + 跟谱 + 写定的四手联弹曲目
         产出：一台能跟着你 rubato 的第二声部机器人
         ↑ 不需要新硬件，可以最快出结果

阶段 II  视觉预判
         手部视频 → 触键前 100–300ms 的预测 → 消除剑桥的一拍延迟
         数据：FürElise / SKY-Piano 预训练 + 你自己的录制微调
         产出：延迟对比实验（MIDI-only vs MIDI+vision）

阶段 III 全键盘覆盖执行器
         固定阵列 + 踏板 + 表情性提手（"呼吸"）
         产出：一台能弹整个第二声部、且在人手边安全的机器
         ↑ 你的硬件训练在这里落地

阶段 IV  脑间同步评估
         solo / 人-人二重奏 / 人-机二重奏 三条件 hyperscanning
         操纵变量：有无视觉预判、有无提手呼吸、有无速度自适应
         产出：哪些机器特性让"同步"回来——直接指导设计
```

**阶段 I 是最先该做的，因为它不依赖任何新硬件，而且它本身就把问题从"即兴"换成了"合奏"。**

---

## 七、给 Gil 的一句话版本

> 剑桥 2024 年在 T-RO 上发了第一台人机协作钢琴机器人，
> 但它只会 7 个流行和弦、只靠 MIDI 所以慢一拍、而且他们自己说"好不好听"没法评估。
> 我们组有全键盘执行机构的经验，我有演奏者对合奏线索的理解和 EEG，
> 这三样正好对上它的三条局限——把它从"即兴伴奏"推到"真正的四手联弹"。
