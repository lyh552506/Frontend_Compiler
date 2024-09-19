#include "../../include/ir/opt/ConstantProp.hpp"
#include <cmath>
#include <set>

bool ConstantProp::Run() {
  /*
  要求：
  1. 顺序遍历function中的每个基本块,并顺序遍历基本块中的每个指令
  2. 如果一个指令是常量传播的结果，那么就将这个指令替换为常量，并删除这个指令
  */
  return true;
}

Value *ConstantProp::ConstFoldInst(User *inst) {
  /*
  要求：
  1. 考虑一条指令是否能进行常量折叠
  2. 如果能够进行常量折叠，那么返回折叠后的常量
  3. 正确判断指令的类型，对于不同的类型需要有不同的处理方法
  这个过程可以自行在 ConstantProp类中增加函数来实现功能
  */
  return nullptr;
}
