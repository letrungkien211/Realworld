#include		"othello.h"
#include		"banmen.h"

#include		"setjmp.h"
jmp_buf			env;

extern char ban[];
extern char ban1[];
extern char ban2[];
extern char ban3[];
extern char ban4[];

extern int	te;

struct jcell
{
	char	te;
	struct jcell *son;
};

typedef struct jcell		JCELL;

extern JCELL	jsktbl2[], naname[], tate[];
extern JCELL 	naname2[], naname3[], ushi[];
extern JCELL	usagi[], usagi2[];

JCELL	jsktbl[] =
{
	{F5, jsktbl2},
	{0, 0}
};

JCELL	jsktbl2[] =
{
	{F6, naname},
	{D6,tate},
	{0, 0}
};

JCELL	naname[] =
{
	{E6, naname2},
	{0, 0}
};

JCELL	naname2[] =
{
	{D6, naname3},
	{0, 0}
};

JCELL	naname3[] =
{
	{C5, ushi},
	{0, 0}
};

JCELL	ushi[] =
{
	{E3, 0},
	{0, 0}
};

JCELL	tate[] =
{
	{C5, usagi},
	{0, 0}
};

JCELL	usagi[] =
{
	{F4, usagi2},
	{0, 0}
};

JCELL	usagi2[] =
{
	{E3, 0},
	{0, 0}
};

joseki()
{
	int	i, x, y;

	for(i = A1; i <= H8; i++)
		ban1[i]=ban2[i]=ban3[i]=ban4[i]=WALL;

	for(y = 1; y <= 8; y++)
		for(x = 1; x <= 8; x++) {
			ban1[y*9+x] = ban[y*9+x];
			ban2[x*9+y] = ban[y*9+x];
			ban3[(9-y)*9+9-x] = ban[y*9+x];
			ban4[(9-x)*9+9-y] = ban[y*9+x];
		}

	set_ban();

	te = setjmp(env);
	if(te == 0)
		search(jsktbl);

	for(y = 1; y <= 8; y++)
		for(x= 1; x <= 8; x++)
			ban[y*9+x] = ban1[y*9+x];
}

search(p)
JCELL	*p;
{
	int	t, tx, ty;

	t = p->te;
	tx = t % 9;
	ty = t / 9;

	if(compare(&ban1[A1]))
		longjmp(env, t);
	if(compare(&ban2[A1]))
		longjmp(env, tx*9+ty);
	if(compare(&ban3[A1]))
		longjmp(env, (9-ty)*9+9-tx);
	if(compare(&ban4[A1]))
		longjmp(env, (9-tx)*9+9-ty);

	for(; p->te; p++) {
		if(p->son == 0)
			continue;

		put1(p->te + ban);
		rev_ban();
		search(p->son);
		rev_ban();
		tup1();
	}
}

compare(bp1)
char	*bp1;
{
	char	*bp2;

	for(bp2 = &ban[A1]; bp2 <= &ban[H8]; )
		if(*(bp1++) != *(bp2++))
			return 0;
	return 1;
}
