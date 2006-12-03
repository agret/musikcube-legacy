// For compilers that support precompilation, includes "wx/wx.h".
//#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float REAL;
#define M 15

class paramlistelm {
public:
	class paramlistelm *next;

	char left,right;
	float lower,upper,gain,gain2;
	int sortindex;

	paramlistelm(void) {
		left = right = 1;
		lower = upper = gain = 0;
		next = NULL;
	};

	~paramlistelm() {
		delete next;
		next = NULL;
	};

	char *getString(void) {
		static char str[64];
		sprintf(str,"%gHz to %gHz, %gdB %c%c",
			(double)lower,(double)upper,(double)gain,left?'L':' ',right?'R':' ');
		return str;
	}
};

class paramlist {
public:
	class paramlistelm *elm;

	paramlist(void) {
		elm = NULL;
	}

	~paramlist() {
		delete elm;
		elm = NULL;
	}

	void copy(paramlist &src)
	{
		delete elm;
		elm = NULL;

		paramlistelm **p,*q;
		for(p=&elm,q=src.elm;q != NULL;q = q->next,p = &(*p)->next)
		{
			*p = new paramlistelm;
			(*p)->left  = q->left;
			(*p)->right = q->right;
			(*p)->lower = q->lower;
			(*p)->upper = q->upper;
			(*p)->gain  = q->gain;
		}
	}
		
	paramlistelm *newelm(void)
	{
		paramlistelm **e;
		for(e = &elm;*e != NULL;e = &(*e)->next) ;
		*e = new paramlistelm;

		return *e;
	}

	int getnelm(void)
	{
		int i;
		paramlistelm *e;

		for(e = elm,i = 0;e != NULL;e = e->next,i++) ;

		return i;
	}
	
	void delelm(paramlistelm *p)
	{
		paramlistelm **e;
		for(e = &elm;*e != NULL && p != *e;e = &(*e)->next) ;
		if (*e == NULL) return;
		*e = (*e)->next;
		p->next = NULL;
		delete p;
	}

	void sortelm(void)
	{
		int i=0;

		if (elm == NULL) return;

		for(paramlistelm *r = elm;r	!= NULL;r = r->next) r->sortindex = i++;

		paramlistelm **p,**q;

		for(p=&elm->next;*p != NULL;)
		{
			for(q=&elm;*q != *p;q = &(*q)->next)
				if ((*p)->lower < (*q)->lower ||
					((*p)->lower == (*q)->lower && (*p)->sortindex < (*q)->sortindex)) break;

			if (p == q) {p = &(*p)->next; continue;}

			paramlistelm **pn = p;
			paramlistelm *pp = *p;
			*p = (*p)->next;
			pp->next = *q;
			*q = pp;

			p = pn;
	    }
	}
};

class ShibatchEQ
{
public:

	ShibatchEQ();
	int equ_modifySamples(char *buf,int nsamples,int nch,int bps);
	void equ_clearbuf(int bps,int srate);
	void equ_quit(void);
	void equ_makeTable(REAL *lbc,REAL *rbc,paramlist *param,REAL fs);
	void equ_init(int wb);

private:

	REAL win(REAL n,int N);
	REAL alpha(REAL a);
	REAL izero(REAL x);

	REAL fact[M+1];
	REAL aa;
	REAL iza;
	REAL *lires,*lires1,*lires2,*rires,*rires1,*rires2,*irest;
	REAL *fsamples;
	REAL *ditherbuf;
	int ditherptr;
	volatile int chg_ires,cur_ires;
	int winlen,winlenbit,tabsize,nbufsamples;
	short *inbuf;
	REAL *outbuf;
	int enable;
	int dither;
};


