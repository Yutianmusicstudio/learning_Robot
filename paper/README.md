# Overleaf 用的 research purpose

## 文件
- `research_purpose.tex` — 主文档，约 2 页，纯 `article` 类，无特殊宏包
- `references.bib` — 参考文献

## 在 Overleaf 上
把两个文件上传到同一个项目，编译顺序 **pdfLaTeX → BibTeX → pdfLaTeX ×2**
（Overleaf 默认的 "Recompile" 会自动处理）。

## ⚠️ 提交前必做
`.bib` 里标了 `TODO` 的条目**作者列表没有核实**——我是从检索摘要拿的元数据，
不是从出版页。**投出去之前把每个 TODO 逐条补齐**，尤其是：

- `musicbodymachine2024` — 这是你们组自己的论文，作者必须写对
- `hyperscanning2021` — 评估方案的基线
- `nime2020bldc` — 你们组的 NIME 论文
- `furelise2024` / `pianovam2025` / `zakka2023robopianist`

只有 `wang2024cooperative`（通读过全文）和 `weinberg2020robotic` 是我核实过的。

## 结构对应
`.tex` 的六节对应 `docs/four-hands-proposal.md`：
Motivation / 局限 (L1–L4) / RQ1–RQ3 / 方案 A-B-C / 计划 P1–P5 / 贡献。
中文详版在那份文档里，这份是给 Gil 看的英文精简版。
