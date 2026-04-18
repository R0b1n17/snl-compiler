#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "globals.h"

struct SemanticResult {
    int errorCount;
    int warningCount;
};

SemanticResult analyzeSemantics(TreeNode* root);

#endif
