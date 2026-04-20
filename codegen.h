#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>

#include "globals.h"

struct CodegenResult {
    bool success;
    int errorCount;
    std::string outputAsmPath;
};

CodegenResult generateMips32(TreeNode* root, const std::string& outputAsmPath);

#endif
