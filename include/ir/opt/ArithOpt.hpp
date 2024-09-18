#pragma once
#include "../../lib/BaseCFG.hpp"
#include "../../lib/CFG.hpp"
#include "../Analysis/dominant.hpp"
#include "New_passManager.hpp"
#include "PassManagerBase.hpp"
#include <vector>
class _AnalysisManager;
class ArithOpt : public _PassManagerBase<ArithOpt, Function> {
public:
  ArithOpt(Function *func, _AnalysisManager &_AM) : m_func(func), AM(_AM) {}
  bool Run();
  ~ArithOpt() {
    for (auto l : DeleteLoop)
      delete l;
  }

private:
  Function *m_func;
  _AnalysisManager &AM;
  std::vector<LoopInfo *> DeleteLoop;
};