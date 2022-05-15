#ifndef _Q_H
#define _Q_H
#include"tools.h"

class Q {
public:
	Q(const int &in_fz = 0, const int &in_fm = 1);//default Q=0/1
	Q(const double &in_dob);
	Q(const Q &ra);
	Q(const Q &ra1, const Q &ra2);
	//member
	int getsgn() const { return sgn; }
	int getfz() const { return fz; }
	int getfm() const { return fm; }
	friend Q operator+(const Q &ra1, const Q &ra2);
	friend Q operator-(const Q &ra1, const Q &ra2);
	friend Q operator*(const Q &ra1, const Q &ra2);
	friend Q operator/(const Q &ra1, const Q &ra2);
	friend int cpr(const Q &ra1, const Q &ra2);
	friend bool operator<(const Q &ra1, const Q &ra2) { return (cpr(ra1, ra2) == 1) ? 1 : 0; }
	friend bool operator==(const Q &ra1, const Q &ra2) { return (cpr(ra1, ra2) == 0) ? 1 : 0; }
	//friend istream &operator>>(ostream &is, Q &ra);
	friend ostream &operator<<(ostream &out, Q &ra);
private:
	int sgn, fz, fm;
	void simply();
};

inline int cpr(const Q &ra1, const Q &ra2) {
	Q tmp = ra1 - ra2;
	return (tmp.sgn == -1) ? 1 : ((tmp.fz == 0) ? 0 : -1);
}

#endif
