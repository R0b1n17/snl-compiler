# 演示脚本与现场操作流程

说明：本文件用于老师现场检查答辩的演示，包含准备、命令、示例输入/输出、应急回退。优先保证能在 3–5 分钟内完成关键演示。

## 前置条件

- 已在工程根目录（含 `parser.exe`、`Mars for Compile 2022.jar`、测试用例）
- Windows PowerShell 环境
- 可用 Java（若使用 Mars），或已准备好 `out.s` 的预生成文件

## 关键文件

- 编译器：`parser.exe`（由 `main.cpp`/`semantic.cpp`/`codegen.cpp` 等编译生成）
- 测试用例：`test_codegen_ok.snl`、`test_sem_all12.snl`、`test_codegen_stress_bubble12.snl`
- 自动化脚本：`run_codegen_stress_tests.ps1`
- 说明文档：`README.md`、`defense_q_and_a.md`

## 演示顺序（建议总时长：3–5 分钟）

1. 开场 15–20 秒：一句话说明系统功能与你负责范围。
2. 词法演示（可选，30s）：展示 Token 输出（快速）
   - 命令：
     ```powershell
     .\parser.exe --tokens test_codegen_ok.snl
     ```
   - 预期：Token 列表输出

3. 语法+语义+代码生成（成功示例，60–90s）
   - 命令：
     ```powershell
     .\parser.exe test_codegen_ok.snl
     ```
   - 预期输出（简述）：
     - "--- Parse Success! ---"
     - "--- Semantic Check Passed ---"
     - "--- Codegen Success ---"
     - 生成 `out.s`
   - 运行（用 Mars）：
     ```powershell
     & "$env:JAVA_HOME\bin\java.exe" -jar 'Mars for Compile 2022.jar' nc out.s
     ```
   - 预期：程序按 README 给出的期望值输出（例如 `65`）

4. 语义错误示例（30–45s）
   - 命令：
     ```powershell
     .\parser.exe test_sem_all12.snl
     ```
   - 预期：输出多条 `Semantic error at line X: ...` 并显示汇总 “Semantic Check Failed”。
   - 用意：展示语义检查覆盖错误类型（未定义/重定义/类型错误/VAR 参数错误/用前未初始化等）。

5. 复杂程序/压力测试（演示可选，视时间而定）
   - 命令：
     ```powershell
     .\parser.exe test_codegen_stress_bubble12.snl
     & "$env:JAVA_HOME\bin\java.exe" -jar 'Mars for Compile 2022.jar' nc out.s
     ```
   - 预期：程序输出 0..11（或 README 中给出的正确序列），用于证明复杂控制流/数组访问正确。

## 现场应急与回退方案（必须准备）

- 现场可能失败的点：编译器未编译、Java/Mars 环境问题、权限（PowerShell ExecutionPolicy）、仿真器崩溃。
- 回退准备（放在 U 盘或项目根目录）：
  - 预生成的 `out.s`（对每个示例），以及对应的仿真输出文本（`test_codegen_ok.out.txt`、`bubble12.out.txt` 等）。
  - 屏幕截图：AST、语义错误输出、汇编片段（保存在 `images/` 文件夹或同级目录）。
  - 演示脚本文本文件（本文件）供直接粘贴命令。
- 发生执行错误时的现场流程：
  1. 简短说明错误原因（如果已知），并展示对应预生成的 `out.s` 与输出文本；
  2. 用 `defense_q_and_a.md` 中的标准答案解释为何会失败以及修复思路；
  3. 若时间允许，展示一个不依赖 Java 的示例（仅展示 `out.s` 内容及其关键汇编段落）。

## 推荐演示台词（每步 1–2 句）

- 开场："该编译器实现了 SNL 的词法、语法、语义检查与 MIPS 代码生成，我主要负责项目集成、测试与展示准备。"
- 成功示例开始语句："现在我用 `test_codegen_ok.snl` 演示完整编译流程并在 MIPS 仿真器中运行结果。"
- 语义错误示例开场语句："下面用一个负例展示语义检查会如何报告错误并阻止生成代码。"
- 应急语句："若现场运行失败，这里有预生成的汇编和输出，能证明编译器逻辑正确。"

## 快速检查清单（演示前请核对）

- `parser.exe` 存在且可执行
- `test_*.snl` 测试用例在项目根目录
- `Mars for Compile 2022.jar` 或等效 MIPS 仿真器可用
- 预生成 `out.s` 与输出文本已拷贝到项目根目录作为备份
- PowerShell 权限允许执行脚本（必要时运行 `Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass`）

---

文件生成时间：2026-05-17

如需，我可以：
- 把每个示例对应的 `out.s` 与期望输出追加到本文件（便于老师直接比对）；
- 将本文件导出为 PDF 供打印。