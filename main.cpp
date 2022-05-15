#include"Symbol.h"

int main() {

	Tab ta1, ta2;
	//ta1.append(Tri(_pid2, _cos, -1));//error
	//ta1.append(Tri(_pid2, _cos, 0));//cause 0^0=1
	ta2.append(Tri(_0, _arccos, 1));
	ta1.append(Tri(_pid6, 0, 1));
	//ta1.append(Tri(_3, _exp, .5));
	cout << ta1 << endl << ta2 << endl;
	cout << ta1*ta2 << endl;
	return 0;
}