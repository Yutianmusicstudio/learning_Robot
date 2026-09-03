# 文献核实档案

**核实方式**：`untitled folder/` 下 12 篇 PDF 全文提取题名页，作者、卷期、页码、DOI 均从原文抄录。
**状态**：除文末三项外，不再有待补字段。

---

## ⚠️ 两处必须修正的引用错误

### 1. 弦乐四重奏的 24/28 ms 不是 Wing 等人的原始数据

Wing et al. (2014) 原文写的是：

> "(2014) reported figures for asynchrony SD of **24 and 28 ms (at 157 bpm)** for two string quartets
> (first and second violin, viola, and cello)."

**这是转引。** 24/28 ms 出自 Wing 所引的另一篇。直接引 Wing 会被指出引错源头。

**处理方式**：去 Wing 那篇的参考文献里找出被引原文，或改用转引写法
（"as reported in Wing et al. [ref]"）。

### 2. "40 ms" 的归属也需澄清

D'Amario et al. 原文三个数字并列：

> "the threshold for asynchrony perception is around **40 ms for complex sounds**;
> the threshold for the temporal order discrimination is around **30 ms for acoustic piano tones**;
> and, the threshold to detect differences in asynchronies in singing ensemble recordings is
> **between 10 and 38 ms**."

**只有最后一句（10–38 ms）是该文自身结果**，前两项亦为转引。

★ **30 ms（原声钢琴音的时序先后辨别阈）比 40 ms 更贴合本项目**，应优先使用。

同文另给出更严的一项：

> "The threshold of asynchrony to detect the temporal order of two asynchronous tones for
> **highly trained listeners is between 15 and 20 ms**."

---

## 已核实条目（12 条）

| key | 作者与出处 |
|---|---|
| `nime2020bldc` | **Yang, Ning; Savery, Richard; Sankaranarayanan, Raghavasimhan; Zahray, Lisa; Weinberg, Gil.** "Mechatronics-Driven Musical Expressivity for Robotic Percussionists." NIME 2020. arXiv:2007.14850. 全员 Georgia Tech Center for Music Technology |
| `partitura2022` | **Cancino-Chacón, Carlos; Foscarin, Francesco; Peter, Silvan David; Grachten, Maarten; Karystinaios, Emmanouil; Widmer, Gerhard.** "Partitura: A Python Package for Symbolic Music Processing." arXiv:2206.01071. JKU Linz. github.com/CPJKU/partitura |
| `zakka2023robopianist` | **Zakka, Kevin; Wu, Philipp; Smith, Laura; Gileadi, Nimrod; Howell, Taylor; Peng, Xue Bin; Singh, Sumeet; Tassa, Yuval; Florence, Pete; Zeng, Andy; Abbeel, Pieter.** "RoboPianist." arXiv:2304.04150, CoRL 2023 |
| `cancinochacon2023accompanion` | **Cancino-Chacón, Carlos; Peter, Silvan; Hu, Patricia; Karystinaios, Emmanouil; Henkel, Florian; Foscarin, Francesco; Varga, Nimrod; Widmer, Gerhard.** "The ACCompanion." arXiv:2304.12939. JKU Linz + SiriusXM/Pandora |
| `raphael2010musicplusone` | **Raphael, Christopher.** "Music Plus One and Machine Learning." Indiana University. 首页标注 "Invited Applications Paper" → ICML |
| `cont2008antescofo` | **Cont, Arshia.** "ANTESCOFO: Anticipatory Synchronization and Control of Interactive Parameters in Computer Music." ICMC, Aug 2008, Belfast, Ireland, **pp. 33–40**. HAL: hal-00694803 |
| `wang2024cooperative` | **Wang, Huijiang; Zhang, Xiaoping; Iida, Fumiya.** IEEE T-RO, Vol. 40, 2024, p. 4650–. DOI 10.1109/TRO.2024.3484633 |
| `singingsync2019` | **D'Amario, Sara; Daffern, Helena; Bailes, Freya.** "Perception of Synchronization in Singing Ensembles." PLOS ONE. DOI 10.1371/journal.pone.0218162. York + Leeds |
| `hyperscanning2021` | **Zamm, Anna; Palmer, Caroline; Bauer, Anna-Katharina R.; Bleichner, Martin G.; Demos, Alexander P.; Debener, Stefan.** Front. Hum. Neurosci. **15:717810**, 13 Sep 2021. DOI 10.3389/fnhum.2021.717810. McGill + Oldenburg |
| `quartetsync2014` | **Wing, Alan M.; Endo, Satoshi; Yates, Tim; Bradbury, Adrian.** "Perception of String Quartet Synchronization." Front. Psychol. **5:1115**, 14 Oct 2014. DOI 10.3389/fpsyg.2014.01115. Birmingham. 材料为 Haydn Op.74 No.1 的 48 音片段 |
| `nmpduet2021` | **Washburn, Auriel; Wright, Matthew J.; Chafe, Chris; Fujioka, Takako.** Front. Psychol. **12:707090**, 24 Sep 2021. DOI 10.3389/fpsyg.2021.707090. Stanford CCRMA |
| `predictivecoding2026` | **Zhang, Baoli; Yu, Jiarui; Liang, Pengfei.** Front. Psychol. **17:1808969**, 17 Aug 2026. DOI 10.3389/fpsyg.2026.1808969. ⚠️ **这是 Mini Review，不是原创研究**——引用措辞不可写成"实验发现" |

---

## 仍待确认（PDF 首页未印）

1. **ACCompanion 的发表 venue**（此前标注 IJCAI 2023，待证）
2. **Raphael 那篇的确切年份**（ICML，年份待证）
3. **D'Amario 的年份**（据 DOI 应为 2019，待证）

## 一项应删除的说法

**"旋律声部通常提前约 20 ms 发声"** —— 这 12 篇里**没有出处**。该说法来自检索摘要，
不可直接写入 proposal。若要使用，须单独定位源头（可能在 Goebl 关于 melody lead 的工作中）；
否则讨论声部分配时不得引用该数字。

## 2026-09-03 追加核查：novelty 主张

原文写的 "To our knowledge no robotic system has been reported doing this" 经检索后**撤回**。检索发现的先例：

| 系统 | 年份 | 与本项目的关系 |
|---|---|---|
| Risset & Van Duyne, *Duet for One Pianist* (Disklavier, Max) | 1989 / CMJ 1996 | 机器与人**共用同一台钢琴**，机器实时演奏自己的声部。共用键盘这件事本身不新。 |
| Yamaha AI Music Ensemble Technology（Disklavier + Scharoun Ensemble，舒伯特《鳟鱼》五重奏） | 2016 | 实体钢琴机构按**写定谱面**与人类合奏，带实时跟随/预测。写定声部 + 跟随 + 实体钢琴，不新。 |
| Wang, Zhang & Iida, Harmony Robot (IEEE T-RO) | 2024 | 实体机器人 + 人，同一键盘，即兴和弦伴奏。 |
| Bradshaw et al., *The Ghost in the Keys* (Aria-Duet, arXiv 2511.01663) | 2025 | Disklavier 共用键盘，轮流接龙式生成续奏。 |
| PianoTalk (IoT-Based Piano Playing Robot) | 2024 | 可配置四只机械手做 97 键 "duet"——机器与机器，非人机。 |

尚未检索到的组合（提案现在只主张这一条）：**专门制作的执行器阵列演奏四手联弹写定的 secondo 声部 + 共用键盘上以乐谱跟随对齐人类 primo + 以人—人四手联弹为基线的不同步量评估**。措辞已改为 "What we have not found reported is..."，并明说不主张任何单个部件为新。

待确认字段：Risset & Van Duyne 1996 的页码（检索给出 62--71，另有 62--75 的说法，CCRMA 与 arXiv 均被网络策略拦截，无法核对原刊）。
