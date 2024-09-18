#include "../../include/ir/opt/ArithOpt.hpp"
#include "CFG.hpp"
#include "LoopInfo.hpp"
#include "LoopSimplify.hpp"
#include "Singleton.hpp"
#include "dominant.hpp"
#include <iterator>

bool ArithOpt::Run() {
  auto m_dom = AM.get<dominance>(m_func);
  auto loops = AM.get<LoopAnalysis>(m_func, m_dom, DeleteLoop);
  for (auto loop : *loops) {
    auto head = loop->GetHeader();
    auto latch = loops->GetLatch(loop);
    if (head != latch)
      continue;
    bool tag = false;
    BasicBlock *nxt = nullptr;
    for (auto des : m_dom->GetNode(head->num).des) {
      auto desBB = m_dom->GetNode(des).thisBlock;
      if (desBB != head) {
        if (std::distance(m_dom->GetNode(des).rev.begin(),
                          m_dom->GetNode(des).rev.end()) > 1) {
          tag = true;
          break;
        }
        nxt = desBB;
      }
    }
    if (!nxt || tag)
      return false;
    LoopSimplify::CaculateLoopInfo(loop, loops);
    PhiInst *indvar = nullptr;
    for (auto iter = head->begin();
         iter != head->end() && dynamic_cast<PhiInst *>(*iter); ++iter) {
      if (!indvar)
        indvar = dynamic_cast<PhiInst *>(*iter);
      else {
        indvar = nullptr;
        break;
      }
    }
    if (!indvar || indvar != loop->trait.indvar)
      continue;
    int outside_user = 0;
    tag = false;
    for (auto inst : *head)
      for (auto use : inst->GetUserlist()) {
        if (use->GetUser()->GetParent() != head) {
          outside_user++;
          if (use->GetValue() == indvar)
            tag = true;
        }
        if (outside_user > 1)
          break;
      }
    if (outside_user > 1 || tag)
      continue;
    auto bound = loop->trait.boundary;
    loop->trait.indvar->RAUW(bound);
    delete loop->trait.indvar;
    delete head->back();
    auto uncond = new UnCondInst(nxt);
  }
  return false;
}
