#include"tools.h"

int *NumAnalysis(const int &n) {
	int *p = new int[LenNumArr]();
	if( n == 0 ) p[0] = 1;
	else {
		int m = n;
		for( int i = _2; i < LenNumArr; i++ ) {
			while( m%NumArr[i] == 0 && m != 1 ) {
				++p[i]; m /= NumArr[i];
			}
		}
		if( m != 1 ) { cout << "analysis fail !"; exit(1); }
	}
	return p;
}