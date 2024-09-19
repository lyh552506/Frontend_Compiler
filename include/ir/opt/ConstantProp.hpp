#pragma once
#include "New_passManager.hpp"
#include "PassManagerBase.hpp"
class _AnalysisManager;
class ConstantProp : public _PassManagerBase<ConstantProp, Function> {

private:
  // TODO: 在 ConstantProp.cpp 文件中实现这个函数
  /*
   注意：在开始之前在 README.md 文档中阅读接口的使用方式
  */
  Value *ConstFoldInst(User *inst);
  Function *_func;
  _AnalysisManager &AM;

public:
  ConstantProp(Function *func_, _AnalysisManager &AM) : _func(func_), AM(AM) {}
  // TODO: 在 ConstantProp.cpp 文件中实现这个函数
  /*
   注意：在开始之前在 README.md 文档中阅读接口的使用方式
  */
  bool Run();
};
