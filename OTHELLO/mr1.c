#include			"othello.h"

extern int			nc;
extern int			sekisa;
extern char			ban[];

#define	NMR			500
#define SMAX		  5
#define SMIN		  3

/* added 2012/7/4 */
static mr_max();
static mr_min();

mr1(p, tesu, beta)
CELL	*p;
int		tesu, beta;
{
	CELL	*son;
	int		hyo;

	mkchild1(p);

	for(son = p->child; son; son = son->cdr) {
		put1(son->t + ban);
		son->h = eval2();
		tup1();
	}

	sort(p);
	p->t = (p->child)->t;

	for(son = p->child; son; son = son->cdr)
		son->h = beta;

	while(son = p->child) {
		put1(son->t + ban);
		hyo = mr_min(son, tesu-1, p->h);
		tup1();

		if(hyo > p->h) {
			p->h = hyo;
			p->t = son->t;
		}

		sort_top(p);
		cut_low(p, p->h);
	}
}

static mr_max(p, tesu, beta)
CELL		*p;
int			tesu, beta;
{
	CELL 	*son;
	int		n, hyo;

	if(tesu <= 0) {
		hyo = eval1();
		p->h = hyo;
		return hyo;
	}

	if(p->child == NULL) {
		mkchild1(p);
		son = p->child;
		if((son->t == 0) && (p->t == 0)) {
			hyo = sekisa * 128;
			p->h = hyo;
			return hyo;
		}

		if((tesu >= SMAX) && son->cdr) {
			for(son = p->child; son; son = son->cdr) {
				put1(son->t + ban);
				son->h = eval2();
				tup1();
			}

			sort(p);
		}

		son = p->child;
		while(son) {
			son->h = beta;
			son = son->cdr;
		}
	}
	else
		cut_low(p, p->h);

	n = (tesu + 1) * NMR;

	while(son = p->child) {
		if((nc > n) && (son->h < beta))
			return son->h;

		if(son->t == 0)
			hyo = mr_min(son, tesu-1, p->h);
		else {
			put1(son->t + ban);
			hyo = mr_min(son, tesu-1, p->h);
			tup1();
		}

		if(hyo >p->h)
			p->h = hyo;

		sort_top(p);
		cut_low(p, p->h);
	}

	return p->h;
}

static mr_min(p, tesu, alpha)
CELL	*p;
int		tesu, alpha;
{
	CELL	*son;
	int		hyo, ret_flg;
	if(tesu <= 0) {
		hyo = eval2();
		p->h = hyo;
		return hyo;
	}

	if(p->child == NULL) {
		mkchild2(p);

		son = p->child;
		if((son->t == 0) && (p->t == 0)) {
			hyo = sekisa *128;
			p->h = hyo;
			return hyo;
		}

		if((tesu >= SMIN) && (son->cdr != 0)) {
			for(son = p->child; son; son = son->cdr) {
				put2(son->t + ban);
				son->h = -eval1();
				tup2();
			}

			sort(p);
		}

		son = p->child;
		son->h = alpha;
	}
	else {
		son = p->child;
		if(son->h < alpha)
			son->h = alpha;
	}

	ret_flg = 0;

	while(ret_flg == 0) {
		son = p->child;

		if(son->t == 0)
			hyo = mr_max(son, tesu-1, p->h);
		else {
			put2(son->t + ban);
			hyo = mr_max(son, tesu-1, p->h);
			tup2();
		}

		if(hyo < p->h) {
			p->h = hyo;
			ret_flg = 1;
		}

		if(son->h >= p->h) {
			p->child = son->cdr;
			son->cdr = NULL;
			cut_node(son);
			son = p->child;

			if(son)
				son->h = alpha;
			else
				return p->h;
		}
	}

	return alpha;
}
