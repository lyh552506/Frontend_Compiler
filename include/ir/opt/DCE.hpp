#pragma once
#include "New_passManager.hpp"
#include "PassManagerBase.hpp"
class _AnalysisManager;

class DCE : public _PassManagerBase<DCE, Function>
{
    // TODO: 请你在 DCE.cpp文件中实现这个函数
    /*
    注意：在开始之前请你阅读 README.md
    */
   bool HasSideEffect(User* inst);
   void RemoveInst(User* inst);
private:
    Function* func;
    _AnalysisManager &AM;
public:
    DCE(Function* func, _AnalysisManager &AM) : func(func), AM(AM) {}
    
    // TODO : 请你在 DCE.cpp文件中实现这个函数
    /*
    注意：在开始之前请你阅读 README.md
    */
    bool Run();
};