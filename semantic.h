#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "globals.h"

struct SemanticResult {
    int errorCount;
};

SemanticResult analyzeSemantics(TreeNode* root);

#endif
