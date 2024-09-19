#pragma once
#include "../Analysis/dominant.hpp"
#include "PassManagerBase.hpp"
#include "mem2reg.hpp"
#include <any>
#include <getopt.h>
#include <memory>
#include <unordered_map>
#include <vector>
class FunctionPassManager;
class ModulePassManager;
enum OptLevel { O0 = 0, O1 = 1, O2 = 2, O3 = 3 };
enum PassName {
  mem2reg = 4,
  constprop,
  dce
};

static struct option long_options[] = {
    {"mem2reg", no_argument, 0, 4},
    {"constprop", no_argument, 0, 5},
    {"dce", no_argument, 0, 6},
    {0, 0, 0, 0}};

class _AnalysisManager
    : public _AnalysisManagerBase<_AnalysisManager, Function> {
private:
  std::vector<std::any> Contain;
public:
  _AnalysisManager() = default;
  virtual ~_AnalysisManager() = default;
  template <typename Pass, typename... Args,
            typename name = std::enable_if_t<
                std::is_base_of_v<_AnalysisManagerBase<Pass, Function>, Pass>>>
  Pass *get(Function *func, Args &&...args) {
    auto it =
        std::find_if(Contain.begin(), Contain.end(), [&](const std::any &ele) {
          return ele.type() == typeid(Pass *);
        });
    if (it != Contain.end()) {
      delete std::any_cast<Pass *>(*it);
      Contain.erase(it);
    }
    auto pass = new Pass(func, std::forward<Args>(args)...);
    auto *result = pass->GetResult(func);
    Contain.emplace_back(pass);
    return static_cast<Pass *>(result);
  }


  template <typename Pass, typename... Args,
            typename name = std::enable_if_t<
                std::is_base_of_v<_AnalysisManagerBase<Pass, Module>, Pass>>>
  Pass *get(Module *mod, Args &&...args) {
    auto pass = new Pass(mod, std::forward<Args>(args)...);
    auto *result = pass->GetResult();
    Contain.emplace_back(pass);
    return static_cast<Pass *>(result);
  }
};

class _PassManager : public _PassManagerBase<_PassManager, Function> {
public:
  _PassManager() { module = &Singleton<Module>(); }
  virtual ~_PassManager() = default;
  bool Run();
  void RunOnLevel();
  void RunOnTest();
  template <typename Pass, typename name = std::enable_if_t<std::is_base_of_v<
                               _PassManagerBase<Pass, Function>, Pass>>>
  bool RunImpl(Function *func, _AnalysisManager &AM) {
    auto pass = std::make_unique<Pass>(func, AM);
    return pass->Run();
  }
  template <typename Pass, typename name = std::enable_if_t<std::is_base_of_v<
                               _PassManagerBase<Pass, Module>, Pass>>>
  bool RunImpl(Module *mod, _AnalysisManager &AM) {
    auto pass = std::make_unique<Pass>(mod, AM);
    return pass->Run();
  }
  void DecodeArgs(int argc, char *argv[]);

  bool CommonPass(_AnalysisManager &AM);

private:
  void Init();
  OptLevel level;
  void AddPass(PassName pass) { EnablePass.push(pass); }
  std::queue<PassName> EnablePass;
  Module *module;
  Function *curfunc;
  bool modified = true;
};