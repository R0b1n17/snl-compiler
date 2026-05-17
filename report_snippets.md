# 课程设计报告摘录：关键源码片段

下面为可直接复制到课程设计报告正文的精简段落（A 级别），包含代码片段、中文说明与截图占位符。

---

## 1) 词法分析（文件：`snl.l`）

代码片段：
```c
%option noyywrap
%x COMMENT

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*
newline     \n
%%
"PROGRAM"       { return PROGRAM; }
...
{number} {
    errno = 0;
    long v = strtol(yytext, NULL, 10);
    if (errno == ERANGE || v < SNL_INT_MIN || v > SNL_INT_MAX) {
        fprintf(stderr, "Line %d: integer out of range [%ld,%ld]: %s\n", lineno, SNL_INT_MIN, SNL_INT_MAX, yytext);
        return ERROR;
    }
    yylval.val = (int)v;
    return NUM;
}
```

说明：词法阶段识别关键字、标识符、数值与字符常量，并对整数进行范围检查（-32768 ~ 32767）。建议截图并保存为 `images/scene1_tokens.png`（词法输出）。

---

## 2) 语法与 AST（文件：`snl.y`）

代码片段：
```c
callStm
    : CALL ID
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = CallK;
          $$->attr.name = $2;
      }
    | CALL ID LPAREN argListOpt RPAREN
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = CallK;
          $$->attr.name = $2;
          $$->addChild($4);
      }
    ;

argListOpt
    : /* empty */ { $$ = nullptr; }
    | argList { $$ = $1; }
    ;

argList
    : exp { $$ = $1; }
    | argList COMMA exp { $$ = appendSibling($1, $3); }
    ;
```

说明：在遇到过程调用时构造 `CallK` 节点，参数通过 sibling 链接组织为参数链。建议截图并保存为 `images/scene2_ast_call.png`（AST 局部视图）。

---

## 3) 主程序演示：词法打印（文件：`main.cpp`）

代码片段：
```cpp
static string tokenToString(int token) { ... }

static int dumpTokens() {
    int token = 0;
    while ((token = yylex()) != 0) {
        cout << "[Line " << lineno << "] " << tokenToString(token);
        if (token == ID) cout << "\t" << yylval.name;
        else if (token == NUM || token == CHARC) cout << "\t" << yylval.val;
        cout << endl;
        if (token == ERROR) return 1;
    }
    cout << "[Line " << lineno << "] EOF" << endl;
    return 0;
}
```

说明：`--tokens` 模式直接输出词法流，便于演示词法阶段。截图占位：`images/scene1_tokens.png`。

---

## 4) 语义检查（文件：`semantic.cpp`）

代码片段：
```cpp
void analyzeCall(TreeNode* stmt) {
    SymbolInfo* sym = findSymbol(stmt->attr.name);
    if (sym == nullptr) { /* 报错：未定义过程或是类型名 */ return; }
    if (sym->kind != SymbolKind::Procedure) { reportError(...); return; }

    std::vector<TreeNode*> actualArgs;
    for (TreeNode* a = stmt->firstChild; a != nullptr; a = a->sibling) actualArgs.push_back(a);

    if (actualArgs.size() != sym->params.size()) { reportError(...); return; }
    /* 检查类型、VAR 左值、别名警告等 */
}
```

说明：语义分析对过程调用进行个数、类型及 VAR 左值校验，并在必要时发出别名警告。截图占位：`images/scene3_semantic_errors.png`。

---

## 5) 代码生成（文件：`codegen.cpp`）

代码片段：
```cpp
void emitCall(TreeNode* s) {
    const ProcInfo& p = procTable_.at(s->attr.name);
    std::vector<TreeNode*> args;
    for (TreeNode* a = s->firstChild; a != nullptr; a = a->sibling) args.push_back(a);

    for (int i = (int)args.size() - 1; i >= 0; --i) {
        if (p.params[i].isVar) {
            AddrResult ar = emitLValueAddress(args[i]);
            emitText("addiu $sp, $sp, -4");
            emitText("sw " + ar.addrReg + ", 0($sp)");
            freeTemp();
        } else {
            std::string rv = emitExp(args[i]);
            emitText("addiu $sp, $sp, -4");
            emitText("sw " + rv + ", 0($sp)");
            freeTemp();
        }
    }
    emitText("jal " + p.label);
    if (!args.empty()) emitText("addiu $sp, $sp, " + std::to_string((int)args.size() * 4));
}
```

说明：参数右到左入栈，VAR 参数传地址，VALUE 参数传值，调用后清理栈空间。截图占位：`images/scene4_codegen.png`, `images/scene5_bubble.png`。

---

## 使用说明

- 该文件已格式化为可直接复制粘贴入课程设计报告正文或附录。
- 若需要 LaTeX 或 Word 格式，我可以把内容导出为 `.tex` 或 `.docx`（需确认格式偏好）。
- 若你上传实际截图，我可以把占位符替换为图片并生成完整页面预览。

---
