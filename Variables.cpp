#include"Variables.h"

string FuncArr[FUNC_MAX] = { "I","D","exp ","ln ","sin ","cos ","tan ","arcsin ","arccos " };//functions
int NumArr[NUM_MAX] = { 0,1,-1,2,3,5,7,11,13,17,19,23,29,31,37 };//num
string IrrArr[IRR_MAX] = { "e","pi","(pi/6)" ,"(pi/4)" ,"(pi/3)" ,"(pi/2)" };//irrational
string SingleArr[SINGLE_MAX] = { "x1","x2","x3","x4","x5" };//single
string PolyArr[POLY_MAX] = {};//polynomial
string PowerArr[POWER_MAX] = {};//power:x^y

int LenFuncArr = 9;
int LenNumArr = 15;
int LenIrrArr = 6;
int LenSingleArr = 2;
int LenPolyArr = 0;
int LenPowerArr = 0;

int HeadNumArr = 0;// [head, end]
int EndNumArr = HeadNumArr + LenNumArr - 1;
int HeadIrrArr = NUM_MAX;
int EndIrrArr = HeadIrrArr + LenIrrArr - 1;
int HeadSingleArr = NUM_MAX + IRR_MAX;
int EndSingleArr = HeadSingleArr + LenSingleArr - 1;
int HeadPolyArr = NUM_MAX + IRR_MAX + SINGLE_MAX;
int EndPolyArr = HeadPolyArr + LenPolyArr - 1;
int HeadPowerArr = NUM_MAX + IRR_MAX + SINGLE_MAX + POLY_MAX;
int EndPowerArr = HeadPowerArr + LenPowerArr - 1;
