#ifndef _Sym_H
#define _Sym_H

#include"Variables.h"
#include"Rtab.h"

class Sym {
public:
	Sym(Tab ta);
	~Sym();
	friend Sym &operator*(Sym &s1, Sym &s2);
	friend Sym &operator/(Sym &s1, Sym &s2);
	friend Sym &operator+(Sym &s1, Sym &s2);
	friend Sym &operator-(Sym &s1, Sym &s2);
	friend ostream &operator<<(ostream &out, Sym &s);
private:
	Tab id; Q ra;
};

inline Sym::Sym(Tab ta) {}

inline Sym::~Sym() {}
#endif

