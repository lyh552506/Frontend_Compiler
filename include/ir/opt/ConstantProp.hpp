#pragma once
#include "New_passManager.hpp"
#include "PassManagerBase.hpp"
class _AnalysisManager;
class ConstantProp : public _PassManagerBase<ConstantProp, Function>
{

  private:
    // TODO: 在 ConstantProp.cpp 文件中实现这个函数
    /*
     注意：在开始之前请你阅读 README.md
    */
    Value *ConstFoldInst(User *inst);
    Function *_func;
    _AnalysisManager &AM;

  public:
    ConstantProp(Function *func_, _AnalysisManager &AM) : _func(func_), AM(AM)
    {
    }
    // TODO : 请你在 DCE.cpp文件中实现这个函数
    /*
    注意：在开始之前请你阅读 README.md
    */
    bool Run();
};
