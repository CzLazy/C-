#ifndef _RTAB_H
#define _RTAB_H

#include"Q.h"

struct Tri;//triplet (i,j,Q)

struct Tab {
	Tab();
	Tab(const Q &ra);
	Tab(Tri &t);
	Tab(Tab &t);//copy
	Tab &operator=(Tab &t);
	~Tab();//destruct
	//method
	void append(Tri &tri);
	//void reset();
	void zero();
	void tsort();//increasing but outset is tail 
	void simply() { tsort(); zero(); }
	friend Tab &operator*(Tab &ta1, Tab &ta2);
	//friend int operator<(Tab &ta1, Tab &ta2);
	friend ostream &operator<<(ostream &out, Tab &t);
	Tri *head;
};

struct Tri {
	//constructor
	Tri(const int i = 0, const int j = 0, Q val = 0);
	Tri(Tri &tri);
	Tri &operator=(Tri &t);
	//relation & out
	int operator<(const Tri &t);//1:<  0:=  -1:>  campare position
	bool operator==(const Tri &t) { return (((*this) < t) == 0) ? 1 : 0; }
	friend ostream &operator<<(ostream &out, Tri &tri);
	//=============== method =====================//
	void check();
	void insert(Tri &tri);
	//member
	int i, j;//line & column
	Q val;//value
	Tri *hp, *tp;
};

inline Tab::Tab() { head = new Tri; head->hp = head->tp = head; }

inline Tri::Tri(const int i, const int j, Q val)
	:i(i), j(j), val(val), hp(this), tp(this) {
	check();
}

inline int Tri::operator<(const Tri &t) {//1:<  0:=  -1:>
	return (j<t.j) ? 1 : ((j>t.j) ? -1 : ((i<t.i) ? 1 : ((i>t.i) ? -1 : 0)));
}

#endif
