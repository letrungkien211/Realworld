#include		"othello.h"

#define		MAXCELL		7000

extern	char	ban[];
extern	char	*aki[];
extern	int		hukasa;

static CELL		cell[MAXCELL];
static CELL		*free;
int		nc;

init_cell()
{
	CELL		*p;

	for(p = cell; p < &cell[MAXCELL-1]; p++)
		p->cdr = p + 1;

	p->cdr = 0;
	free = cell;
	nc = MAXCELL;
}

CELL	*get_cell()
{
	register CELL	*p;

	if(nc-- <= 0) {
		printf("cell over flow ");
		exit(1);
	}

	p = free;
	free = p->cdr;
	return p;
}

free_cell(p)
register CELL	*p;
{
	p->cdr = free;
	free = p;
	nc++;
}

mkchild1(p)
CELL	*p;
{
	char	**ap;
	register char	*bp;
	register CELL	*p1;
	CELL	ltop;

	p1 = &ltop;

	for(ap = aki; bp = *(ap++); ) {
		if(*bp != BLANK)
			continue;

		if(isable1(bp)) {
			p1 = p1->cdr = get_cell();
			p1->child = NULL;
			p1->t = bp - ban;
		}
	}

	p1->cdr = NULL;

	if(ltop.cdr)
		p->child = ltop.cdr;
	else {
		p1 = p->child = get_cell();
		p1->child = NULL;
		p1->cdr = NULL;
		p1->t = 0;
	}
}

mkchild2(p)
CELL	*p;
{
	char	**ap;

	register char	*bp;
	register CELL	*p1;
	CELL	ltop;

	p1 = &ltop;
	ap = aki;

	for(ap = aki; bp = *(ap++); ) {
		if(*bp != BLANK)
			continue;

		if(isable2(bp)) {
			p1 = p1->cdr = get_cell();
			p1->child = NULL;
			p1->t = bp - ban;
		}
	}

	p1->cdr = NULL;

	if (ltop.cdr)
		p->child = ltop.cdr;
	else {
		p1 = p->child = get_cell();
		p1->child = NULL;
		p1->cdr = NULL;
		p1->t = 0;
	}
}

cut_node(p)
register CELL	*p;
{
	if(p == 0)
		return;

	cut_node(p->child);
	cut_node(p->cdr);
	free_cell(p);
}

sort(p)
CELL	*p;
{
	CELL	*p1;
	register CELL	*p2, *p3;
	CELL	ltop;
	int		hyo;

	p1 = p->child;
	ltop.cdr = NULL;

	while(p1) {
		p2 = ltop.cdr;
		p3 = &ltop;
		hyo = p1->h;
		while(p2 && (hyo < p2->h)) {
			p3 = p2;
			p2 = p2->cdr;
		}

		p3->cdr = p1;
		p3 = p1;
		p1 = p1->cdr;
		p3->cdr = p2;
	}

	p->child = ltop.cdr;
}

sort_top(p)
CELL	*p;
{
	CELL	*p1;
	register CELL	*p2, *p3;
	CELL	ltop;
	int		hyo;

	p1 = p->child;
	p2 = p1->cdr;
	p3 = &ltop;
	ltop.cdr = p2;
	hyo = p1->h;

	while(p2 && (hyo < p2->h)) {
		p3 = p2;
		p2 = p2->cdr;
	}

	p3->cdr = p1;
	p1->cdr = p2;
	p->child = ltop.cdr;
}

cut_low(p, hyo)
CELL	*p;
int		hyo;
{
	register CELL	*p2, *p3;
	CELL	ltop;

	p2 = p->child;
	p3 = &ltop;
	ltop.cdr = p2;

	while(p2 && (hyo < p2->h)) {
		p3 = p2;
		p2 = p2->cdr;
	}

	p3->cdr = 0;
	cut_node(p2);
	p->child = ltop.cdr;
}
