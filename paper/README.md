# Overleaf 用的 research purpose

## 文件
- `proposal.tex` — ★ **当前主文档**：research proposal，约 2 页。
  目标锚定在"这台机器能不能做出来"——能与人合奏四手联弹曲目；
  rubato 的表达性协商与 EEG 评估明确移入 Future Work。
- `research_purpose.tex` — 更早的 research purpose 版本，保留备用
- `references.bib` — 参考文献

## 在 Overleaf 上
把 `proposal.tex`（或 `research_purpose.tex`）与 `references.bib` 上传到同一个项目，编译顺序 **pdfLaTeX → BibTeX → pdfLaTeX ×2**
（Overleaf 默认的 "Recompile" 会自动处理）。

## 文献核实
见 `references_verified.md`——12 篇 PDF 已全文提取题名页，作者/卷期/页码/DOI 均从原文抄录，
`references.bib` 中的 TODO 可据此补齐。**该文件同时记录了两处必须修正的引用错误**
（弦乐四重奏 24/28ms 系转引；40ms 亦为转引，30ms 更贴切），以及一项应从正文删除的无出处说法。

## ⚠️ 提交前必做
`.bib` 里标了 `TODO` 的条目**作者列表没有核实**——我是从检索摘要拿的元数据，
不是从出版页。**投出去之前把每个 TODO 逐条补齐**，尤其是：

- `musicbodymachine2024` — 这是你们组自己的论文，作者必须写对
- `hyperscanning2021` — 评估方案的基线
- `nime2020bldc` — 你们组的 NIME 论文
- `furelise2024` / `pianovam2025` / `zakka2023robopianist`

只有 `wang2024cooperative`（通读过全文）和 `weinberg2020robotic` 是我核实过的。

## 写作原则（改动时请保持）
1. **凡是断言都带引用**；凡是估算都明写为待测，不冒充定论——
   延迟表里只有感知容差三项有文献，链路各段标注 "estimates to be measured in M1--M2"。
2. **主动声明不主张跟谱算法的新意**（那是成熟领域），贡献在于共享乐器约束下的集成。
3. 未穷尽的检索结论用 hedge（"to our knowledge"）。

## 结构对应
`.tex` 的六节对应 `docs/four-hands-proposal.md`：
Motivation / 局限 (L1–L4) / RQ1–RQ3 / 方案 A-B-C / 计划 P1–P5 / 贡献。
中文详版在那份文档里，这份是给 Gil 看的英文精简版。
