# 部分接口使用方式

## RAUW

RAUW (Replace All Uses With xx)，when you use this interface: `x->RAUW(y)`，means replace all x with y

```c++
Eg:
//sorce c
int ififElse() {
  int a;
  a = 5;
  int b;
  b = 10;
  if(a == 5)
    if (b == 10) 
      a = 25;
    else 
      a = a + 15;
    
  return (a);
}
//SSA IR
define dso_local i32 @ififElse() {
entry:
  %cmp = icmp eq i32 5, 5
  br i1 %cmp, label %if.then, label %if.end3

if.then:                                          ; preds = %entry
  %cmp1 = icmp eq i32 10, 10
  br i1 %cmp1, label %if.then2, label %if.else

if.then2:                                         ; preds = %if.then
  br label %if.end3

if.else:                                          ; preds = %if.then
  %add = add nsw i32 5, 15
  br label %if.end3

if.end3:                                          ; preds = %if.then2, %if.else, %entry
  %a.0 = phi i32 [ 25, %if.then2 ], [ %add, %if.else ], [ 5, %entry ]
  ret i32 %a.0
}
//After ConstProp We can find `%cmp = icmp eq i32 5, 5` can be translated to `true`, so we should Replace All `%cmp` with `True`,the we use RAUW(ConstIRBoolean::GetNewConstant(true))
//opted IR (only target on %cmp)
define dso_local i32 @ififElse() {
entry:
  %cmp = icmp eq i32 5, 5   //has no user, can be deleteted
  br i1 True, label %if.then, label %if.end3

if.then:                                          ; preds = %entry
  %cmp1 = icmp eq i32 10, 10
  br i1 %cmp1, label %if.then2, label %if.else

if.then2:                                         ; preds = %if.then
  br label %if.end3

if.else:                                          ; preds = %if.then
  %add = add nsw i32 5, 15
  br label %if.end3

if.end3:                                          ; preds = %if.then2, %if.else, %entry
  %a.0 = phi i32 [ 25, %if.then2 ], [ %add, %if.else ], [ 5, %entry ]
  ret i32 %a.0
}
```

## Delete(析构一个Value)

When you want to delete a Value, first **make sure it has no Users**, then use `delete xxx`

##  遍历Block、Inst

首先包含关系是这样的：Module包含多个Function，Function包含多个Block，Block包含多个Insts（User）

```c++
//获得当前Module的方式；
Singleton<Module>()
//获得所有的Function;
Singleton<Module>().GetFuncTion()
//遍历所有的function
for(auto &func:Singleton<Module>().GetFuncTion())
{...}
//遍历block
for(auto bb:(*func))
{...}
for(auto iter=func->begin();iter!=func->end();++iter)
{...}
//遍历inst
for(auto inst:(*block))
{...}
for(auto iter=block->begin();iter!=block->end();++iter)
{...}
```

## 遍历UserList、UseList

Every value has it's UserList, but only User (like Instruction can have UseList, Eg: a Const number do not have use)

```c++
//if "%a" is a BinaryInst: %a = add %1, %2; %b=sub %a,%2
//遍历Use
for(auto use:a->GetUselist){
   //记住use只是一个边的数据结构，我们需要从use中找到对应的Value
    auto x1=use->GetUser();//返回use边对应的user：%a
    auto x2=use->GetValue();//返回use边对应的value：%1或%2
}
//遍历User
for(auto use:a->Getuserlist()){
    //变量的user同样是通过边的关系承载
    auto x1=use->GetValue();//返回%a本身
    auto x2=use->GetUser(); //返回%a的user %b
}
```

