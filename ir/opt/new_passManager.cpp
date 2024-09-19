#include "../../include/ir/opt/New_passManager.hpp"
void _PassManager::DecodeArgs(int argc, char *argv[]) {
  int optionIndex, option;
  while ((option = getopt_long(argc, argv, "", long_options, &optionIndex)) !=
         -1) {
    switch (option) {
    default:
      std::cerr << "No Such Opt!" << std::endl;
      exit(0);
    case mem2reg:
      AddPass(mem2reg);
      break;
    case constprop:
      AddPass(constprop);
      break;
    case dce:
      AddPass(dce);
      break;
    }
  }
}

bool _PassManager::Run() { return true; }

///@brief 执行Pass顺序会按照给定参数的顺序来
void _PassManager::RunOnTest() {
  _AnalysisManager AM;
  while (!EnablePass.empty()) {
    auto name = EnablePass.front();
    EnablePass.pop();
    for (int i = 0; i < module->GetFuncTion().size(); i++) {
      auto &func = module->GetFuncTion()[i];
      curfunc = func.get();
      // 维护bbs关系
      curfunc->bb_num = 0;
      curfunc->GetBasicBlock().clear();
      for (auto bb : *curfunc) {
        bb->num = curfunc->bb_num++;
        curfunc->GetBasicBlock().push_back(bb);
      }
      switch (name) {
      case mem2reg: {
        curfunc = func.get();
        // 维护bbs关系
        curfunc->bb_num = 0;
        curfunc->GetBasicBlock().clear();
        for (auto bb : *curfunc) {
          bb->num = curfunc->bb_num++;
          curfunc->GetBasicBlock().push_back(bb);
        }
        auto Mem2regRes = RunImpl<Mem2reg>(curfunc, AM);
        break;
      }
      case constprop: {
        // auto m_constprop = RunImpl<ConstantProp>(curfunc, AM);
        break;
      }
      case dce: {
        // ContinueRunPassOnTest(DCE, curfunc) break;
      }
      default: {
        assert(0);
      }
      }
    }
  }
}

void _PassManager::Init() { return; }