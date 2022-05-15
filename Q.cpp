#include "Q.h"

Q::Q(const double &in_dob) : sgn((in_dob < 0) ? -1 : 1) {
	string str = _2string(abs(in_dob));
	int len = str.length(), dotpos = str.find('.');
	string head = str.substr(0, dotpos), tail = str.substr(dotpos + 1, len);
	fz = _str2int(head + tail);
	fm = _str2int('1' + string(len - dotpos - 1, '0'));
	simply();
}

Q::Q(const int &in_fz, const int &in_fm) : fz(abs(in_fz)), fm(abs(in_fm)) {
	if( fm == 0 ) {
		cout << "divisor can't be 0 !" << endl;
		exit(1);
	}
	sgn = ((in_fz < 0) ^ (in_fm < 0)) ? -1 : 1;
	simply();
}

Q::Q(const Q &ra) :sgn(ra.sgn), fz(ra.fz), fm(ra.fm) {}

Q::Q(const Q &ra1, const Q &ra2) {
	if( ra2.fz == 0 ) {
		cout << "divisor can't be 0 !" << endl;
		exit(1);
	}
	else {
		sgn = ra1.sgn*ra2.sgn;
		fz = ra1.fz*ra2.fm;
		fm = ra2.fz*ra1.fm;
		simply();
	}
}
//====================  method  ======================//
void Q::simply() {
	int mod = fz%fm;
	if( mod == 0 ) { fz = fz / fm;	fm = 1; }
	else {
		int fenzi = fz, fenmu = fm;
		while( fenmu ) {
			mod = fenzi%fenmu;
			fenzi = fenmu;	fenmu = mod;
		}
		fz /= fenzi;	fm /= fenzi;
	}
}

Q operator + (const Q &ra1, const Q &ra2) {
	int fz1 = ra1.sgn*ra1.fz;
	int fz2 = ra2.sgn*ra2.fz;
	fz1 = fz1*ra2.fm + fz2*ra1.fm;
	fz2 = ra1.fm*ra2.fm;
	return Q(fz1, fz2);
}

Q operator - (const Q &ra1, const Q &ra2) {
	int fz1 = ra1.sgn*ra1.fz;
	int fz2 = (-1)*ra2.sgn*ra2.fz;
	fz1 = fz1*ra2.fm + fz2*ra1.fm;
	fz2 = ra1.fm*ra2.fm;
	return Q(fz1, fz2);
}

Q operator * (const Q &ra1, const Q &ra2) {
	int fz = ra1.sgn*ra1.fz*ra2.sgn*ra2.fz;
	int fm = ra1.fm*ra2.fm;
	return Q(fz, fm);
}

Q operator / (const Q &ra1, const Q &ra2) {
	if( ra2.fz == 0 ) {
		cout << "divisor cant be 0 !" << endl;
		exit(1);
	}
	int fz = ra1.sgn*ra1.fz*ra2.fm;
	int fm = ra2.sgn*ra2.fz*ra1.fm;
	return Q(fz, fm);
}

ostream &operator<<(ostream &out, Q &ra) {
	if( ra.sgn == -1 ) out << '-';
	out << ra.fz;
	if( ra.fm != 1 ) out << '/' << ra.fm;
	return out;
}
