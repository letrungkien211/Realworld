#include 	"othello.h"

extern char		ban[];
extern char		*aki[];
extern int		sekisa;

ab_max(tesu, alpha, beta, nopass1)
int    tesu, alpha, beta, nopass1;

{
	int	hyo;
	int	nopass2;
	char	**ap;
	char	*bp;

	if(tesu <= 0)
		return sekisa;

	if(tesu == 1)
		return ab2_max();

	ap = aki;
	nopass2 = 0;

	while(bp = *(ap++)) {
		if(*bp != BLANK)
			continue;

		if(put1(bp) == 0)
			continue;

		hyo = ab_min(tesu-1, alpha, beta, 1);
		tup1();
		nopass2 = 1;

		if(hyo > alpha)
			alpha = hyo;

		if(alpha >= beta)
			return alpha;
	}

	if(nopass2)
		return alpha;

	if(nopass1) {
		hyo = ab_min(tesu, alpha, beta, 0);
		return hyo;
	}
	else
		return sekisa;
}

ab_min(tesu, alpha, beta, nopass1)
int    tesu, alpha, beta, nopass1;
{
	int hyo;
	int nopass2;
	char **ap;
	char *bp;

	if(tesu <= 0)
		return sekisa;

	if(tesu == 1)
		return ab2_min();

	ap = aki;
	nopass2 = 0;

	while(bp = *(ap++)) {
		if(*bp != BLANK)
			continue;

		if(put2(bp) == 0)
			continue;

		hyo = ab_max(tesu-1, alpha, beta, 1);
		tup2();
		nopass2 = 1;

		if(hyo < beta)
			beta = hyo;

		if(alpha >= beta)
			return beta;
	}

	if(nopass2)
		return beta;

	if(nopass1) {
		hyo = ab_max(tesu, alpha, beta, 0);
		return hyo;
	}
	else
		return sekisa;
}

ab2_max()
{
	register int	turn;
	register char	**ap;
	char	*bp;

	ap = aki -1;

	while(**(++ap) != BLANK)
		;

	bp = *ap;

	if(turn = put3(bp))
		return (sekisa + turn + turn + 1);

	if(turn = put4(bp))
		return (sekisa - turn - turn - 1);
	else
		return sekisa;
}

ab2_min()
{
	register int	turn;
	register char	**ap;
	char	*bp;

	ap = aki;

	while(**(ap) != BLANK)
		ap++;

	bp = *ap;

	if(turn = put4(bp))
		return (sekisa - turn - turn - 1);

	if(turn = put3(bp))
		return (sekisa + turn + turn + 1);
	else
		return sekisa;
}
