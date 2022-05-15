#ifndef _TOOLS_H
#define _TOOLS_H

#include<sstream>
#include<cmath>
#include"Variables.h"

template<typename T>
inline string _2string(T i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

inline int _str2int(string s) {
	int num;
	stringstream ss(s);
	ss >> num;
	return num;
}

int *NumAnalysis(const int &n);

#endif
