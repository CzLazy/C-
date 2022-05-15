#ifndef _VARIABLES_H
#define _VARIABLES_H

#include<string>
#include<iostream>
using namespace std;

#define FUNC_MAX 15
#define NUM_MAX 20
#define IRR_MAX  10//irrational
#define SINGLE_MAX 20//single
#define POLY_MAX 40//polynomial
#define POWER_MAX 40

enum _FUN { _iden, _differ, _exp, _ln, _sin, _cos, _tan, _arcsin, _arccos };
enum _NUM { _0, _1, _ne1, _2, _3, _5, _7, _9, _11, _13, _15, _17, _19 };
enum _IRR { _e = NUM_MAX, _pi, _pid6, _pid4, _pid3, _pid2 };
enum _SINGLE { _x1 = NUM_MAX + IRR_MAX, _x2, _x3, _x4, _x5 };

extern string FuncArr[];
extern int NumArr[];
extern string IrrArr[];
extern string SingleArr[];
extern string PolyArr[];
extern string PowerArr[];

extern int LenNumArr;
extern int LenFuncArr;
extern int LenNumArr;
extern int LenIrrArr;
extern int LenSingleArr;
extern int LenPolyArr;
extern int LenPowerArr;

extern int HeadNumArr;
extern int EndNumArr;
extern int HeadIrrArr;
extern int EndIrrArr;
extern int HeadSingleArr;
extern int EndSingleArr;
extern int HeadPolyArr;
extern int EndPolyArr;
extern int HeadPowerArr;
extern int EndPowerArr;

#endif
