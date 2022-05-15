#include"Rtab.h"

Tab::Tab(const Q &ra) {
	head = new Tri; head->hp = head->tp = head;
	if( ra == 0 ) head->i = head->j = 0, head->val = 1, zero();
	else if( ra == 1 ) {}
	else if( ra == -1 ) append(Tri(1, 0, 1));
	else {
		if( ra.getsgn() == -1 ) append(Tri(1, 0, 1));
		int i, *fz = NumAnalysis(ra.getfz());
		for( i = 2; i < LenNumArr; i++ ) {
			if( fz[i] ) append(Tri(i, 0, fz[i]));
		}
		if( ra.getfm() ) {
			int *fm = NumAnalysis(ra.getfm());
			for( i = 2; i < LenNumArr; i++ ) {
				if( fm[i] ) append(Tri(i, 0, -fm[i]));
			}
		}
	}
}

Tab::Tab(Tab &t) {
	head = new Tri;
	head->insert(*t.head);
	simply();
}

Tab::~Tab() {
	Tri *del, *p = head->tp;
	while( p != head ) { del = p; p = p->tp; delete del; }//delete others
	delete p;//delete p
}

Tab &Tab::operator=(Tab &t) {
	Tab *p = new Tab; p->head->val = t.head->val;
	if( t.head->tp == t.head ) { p->tsort(); }//if t.len=1
	else {
		Tri *q = t.head->tp;
		while( q != t.head ) { p->append(*q); q = q->tp; }
	}
	return *p;
}

void Tab::append(Tri &tri) {//there Tri maybe Tris 
	if( tri.i == 1 && tri.hp == &tri ) {}//times 1
	else {
		Tri *p, *h0, *h = &tri, *t = head; h0 = h;
		while( t->tp != head ) { t = t->tp; }//t to Tab'tail
		if( !(p = new Tri(*h)) ) exit(1);
		t->tp = p;	p->hp = t;
		t = t->tp, h = h->tp;
		while( h != h0 ) {//h back to h0
			if( !(p = new Tri(*h)) ) exit(1);
			t->tp = p;	p->hp = t;
			t = t->tp, h = h->tp;
		}
		t->tp = head, head->hp = t;
		simply();
	}
}

void Tab::zero() {//if head==0  then delete others
	if( head->i == 0 ) {//i == j ==0
		head->val = 1;	head->hp = head->tp = head;
		Tri *del, *p = head->tp;
		while( p != head ) { del = p; p = p->tp; delete del; }
	}
}

void Tab::tsort() {//bubble sort & merge similar terms
	Tri *t = head, *p = head->hp; int tag, sum = 0;	p->check();
	while( t != head->hp ) {//t :from head to tail
		for( p = head->hp; p != t;) {
			tag = *p->hp < *p;
			if( tag == 0 ) {//merge
				Tri *del = p; p = p->hp;
				p->val = p->val + del->val;
				p->check();//cause val's change
				p->tp = del->tp;
				p->tp->hp = p;
				delete del;
			}
			else if( tag < 0 ) {//exchange
				Tri *ex = p->hp;
				if( p->hp == head ) head = p;//if head->p->head
				else {
					ex->tp = p->tp;
					p->tp->hp = ex;
					ex->hp->tp = p;
					p->hp = ex->hp;
					ex->hp = p;
					p->tp = ex;
					if( ex == t ) t = p;//special
					sum++;
				}
			}
			else p = p->hp;
		}
		if( sum == 0 ) break;//have down
		else sum = 0, t = t->tp;
	}
}

Tab &operator*(Tab &ta1, Tab &ta2) {
	Tab *the = new Tab(ta1);
	the->head->hp->insert(*ta2.head);
	the->simply();
	return *the;
}

//int operator<(Tab &ta1, Tab &ta2) {
//	//ta1.simply(),ta2.simply();
//	Tri *t1 = ta1.head, *t2 = ta2.head;
//	int ci, cj, cv;//compare i,j,val
//	if( t1->tp == t1 ) {
//		if( t2->tp == t2 ) return 0;
//	}
//	while( t1->i <= LenNumArr && t1->j == 0 && t1 != ta1.head ) t1 = t1->tp;
//	while( t2->i <= LenNumArr && t2->j == 0 && t2 != ta2.head ) t2 = t2->tp;//to unaddable part
//	if( t1 )
//		for( cv = ci = cj = 0; t1 != ta2.head && t2 != ta1.head; t1 = t1->tp, t2 = t2->tp ) {
//			ci = (t1->i < t2->i) ? 1 : ((t1->i = t2->i) ? 0 : -1);
//			cj = (t1->j < t2->j) ? 1 : ((t1->j = t2->j) ? 0 : -1);
//			cv = t1->val < t2->val;
//			return (ci != 0) ? ci : ((cj != 0) ? cj : ((cv != 0) ? cv : 0));
//		}
//}

ostream &operator<< (ostream &out, Tab &t) {
	Tri *p = t.head;
	while( p->tp != t.head ) {
		out << *p;
		p = p->tp;
	}
	out << *p;
	return out;
}

//=========== Tri method  =============//
Tri::Tri(Tri &tri) {
	Tri *t, *p, *h0, *h;
	h0 = h = &tri, p = NULL;
	i = h->i, j = h->j, val = h->val;//data copy
	h = h->tp; t = this;
	while( h != h0 ) {
		p = new Tri(h->i, h->j, h->val);
		//p->i = h->i, p->j = h->j, p->val = h->val;//data copy
		t->tp = p, p->hp = t;
		t = p, h = h->tp;
	}
	if( !p ) p = this;
	p->tp = this, hp = p;
}

Tri &Tri::operator=(Tri &t) {
	if( this != &t ) {//delete this
		Tri *p, *del; del = p = tp;
		while( p != this ) {
			p = p->tp;
			delete del;
			del = p;
		}
		val = j = 0, i = _1;
		insert(t);
	}
	return *this;
}

ostream &operator<<(ostream &out, Tri &tri) {
	//use this fun for Tri alone is unsuited, it is for cout<< Tab
	int i = tri.i, j = tri.j;
	//out << i << " " << j << " " << tri.val << endl;
	out << "["; if( !(tri.val == 1) )out << "(";
	if( j > 0 ) out << FuncArr[j];
	if( i <= EndNumArr ) out << NumArr[i];
	else if( i >= HeadIrrArr && i <= EndIrrArr ) out << IrrArr[i - HeadIrrArr];
	else if( i >= HeadSingleArr && i <= EndSingleArr ) out << SingleArr[i - HeadSingleArr];
	else if( i >= HeadPolyArr && i <= EndPolyArr ) out << PolyArr[i - HeadPolyArr];
	else  out << PowerArr[i - HeadPowerArr];
	if( !(tri.val == 1) )out << ")" << "^" << tri.val; out << "] ";
	return out;
}

void Tri::check() {//  0 = (0,0,1)	 1 = (1,0,1)  -1 = (2,0,1)
	if( j == 0 ) {//f = Iden
		if( i == 0 ) {//x = 0  
			if( val < 0 )  cout << "some/0! ", exit(1);
			else if( val == 0 ) val = 1, i = _1;//defien 0^0 = 1
			else val = 1;//0^positive = 0
		}
		else if( i == _1 ) val = 1;
		else if( i == _ne1 ) {//x = -1
			if( val.getfm() % 2 == 0 )  cout << "-1 can't sqrt", exit(1);
			else {
				if( val.getfz() % 2 == 0 )  val = 0, i = 0;
				else { val = 1; }//(-1)^fz = (fz is odd) ? -1 : 1
			}
		}
		else if( i == _e ) {
			if( val == 0 ) i = _1, val = 1;
		}
		else if( i == _pid6 ) {
			insert(Tri(_pi, 0, val));
			i = _2, val = val*(-1);
			insert(Tri(_3, 0, val));
		}
		else if( i == _pid4 ) {
			insert(Tri(_pi, 0, val));
			i = _2, val = val*(-2);
		}
		else if( i == _pid3 ) {
			insert(Tri(_pi, 0, val));
			i = _3, val = val*(-1);
		}
		else if( i == _pid2 ) {
			insert(Tri(_pi, 0, val));
			i = _2, val = val*(-1);
		}

		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j == _differ ) {
		if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j == _exp ) {//f = exp
		if( i <= EndNumArr &&i >= 0 )  val = val *NumArr[i], i = _e, j = 0, check();
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j == _ln ) {//f = ln
		if( i == 0 || i == _ne1 ) cout << "lnx:x<=0 !!", exit(1);
		else if( i == 1 ) j = i = 0, check();
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
		//=========================TODO for pi/2...
		//else if(i=HeadIrrArr+2 ){}
	}
	else if( j == _sin ) {//f = sin
		if( i == 0 )  j = 0, check(); //sin 0 = 0
		else if( i == _pi )  i = j = 0, check(); //sin pi =0
		else if( i == _pid6 )  i = _2, j = 0, val = val*(-1); //sin pi/6 = .5
		else if( i == _pid4 )  i = _2, j = 0, val = val*(-.5); //sin pi/4 = 2^(-.5)
		else if( i == _pid3 ) {//sin pi/3 = 2^(-1) * 3^.5
			insert(Tri(_3, 0, val / 2));
			i = _2, j = 0, val = val*(-1);
			check();
		}
		else if( i == _pid2 )  i = _1, j = 0, val = 1;
		//sin pi/2 =1
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j == _cos ) {//f = cos
		if( i == 0 )  i = _1, j = 0, val = 1; //cos 0 = 1
		else if( i == _pi ) { i = _ne1, j = 0; check(); }//cos pi = -1
		else if( i == _pid6 )  i = _pid3, j = _sin, check(); //cos pi/6 = sin pi/3
		else if( i == _pid4 )  i = _2, j = 0, val = val*(-.5); //cos pi/4 = 2^(-.5)
		else if( i == _pid3 )  i = _2, j = 0, val = val*(-1); //cos pi/3=.5
		else if( i == _pid2 )  i = j = 0, check(); //cos pi/2 =0
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j == _tan ) {//tan
		if( i == 0 )  j = 0, check(); //tan 0 = 0
		else if( i == _pid2 ) cout << "tanx:x=pi/2 !!", exit(1);
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
		else { //tanx = sinx / cosx
			insert(Tri(i, _cos, val*(-1))); j = _sin; tp->check(); check();
		}
	}
	else if( j == _arcsin ) {//arcsin
		if( i == 0 )  j = 0, check(); //arcsin 0 = 0
		else if( i == _ne1 ) {// arcsin -1 = -pi/2
			insert(Tri(_pid2, 0, val)); tp->check(); j = 0, i = _ne1;   check();
		}
		else if( i == _1 ) i = _pid2, j = 0, check();//arcsin 1 = pi/2
		else if( i <= LenNumArr && i >= _2 ) cout << "arcsinx:x>1 !" << endl, exit(1);
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j == _arccos ) {//arccos
		if( i == 0 ) i = _pid2, j = 0; //arccos 0 = pi/2
		else if( i == _1 ) i = j = 0, check(); //arccos 1 = 0
		else if( i == _ne1 ) i = _pi, j = 0; //arccos -1 = pi
		else if( i <= LenNumArr ) cout << "arccosx:x>1 !" << endl, exit(1);
		//============= TODO for arccos....
		else if( i < 0 || (i > EndNumArr && i < HeadIrrArr) ||
			(i > EndIrrArr && i < HeadSingleArr) ||
			(i > EndSingleArr && i < HeadPolyArr) ||
			(i > EndPolyArr && i < HeadPowerArr) || i > EndPowerArr ) {
			cout << "undefined data!" << endl; exit(1);
		}//array overflow
	}
	else if( j < 0 || j >= LenFuncArr ) cout << "undefined data!" << endl, exit(1);
	if( val == 0 )  i = _1, j = 0;//influence legal i&j but val=0
}

void Tri::insert(Tri &tri) {//maybe Tris  such as tan(pi/6)
	Tri *p = hp, *h = new Tri(tri);
	p->tp = h;
	h->hp->tp = this;
	hp = h->hp;
	h->hp = p;
}
