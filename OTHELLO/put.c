#include	"othello.h"

#define		push(a) *(sp++)=(int)a
#define		pop(a) a = *(--sp)

extern char 	ban[];
extern int		sekisa;
extern int		*sp;

/* added 2012/7/4 */
static uscan1();
static uscan2();

put1(bp)
register char	*bp;
{
	register int	turn;

	turn  = uscan1(bp, VECT1);
	turn += uscan1(bp, VECT2);
	turn += uscan1(bp, VECT3);
	turn += uscan1(bp, VECT4);
	turn += uscan1(bp, VECT5);
	turn += uscan1(bp, VECT6);
	turn += uscan1(bp, VECT7);
	turn += uscan1(bp, VECT8);

	if(turn == 0)
		return 0;

	*bp = BLACK;

	sekisa += turn + turn + 1;
	push(bp);
	push(turn);
	return turn;
}

static uscan1(bp, vect)
register char *bp;
register int vect;
{
	int i, turn;

	for(i = 0; *(bp+=vect) == WHITE; i++)
		;
	
	if(i == 0 || *bp != BLACK)
		return 0;

		turn = i;

		while(i--) {
			*(bp-=vect) = BLACK;
			push(bp);
		}

		return turn;
}

put2(bp)
register char *bp;
{
	register int turn;

	turn  = uscan2(bp, VECT1);
	turn += uscan2(bp, VECT2);
	turn += uscan2(bp, VECT3);
	turn += uscan2(bp, VECT4);
	turn += uscan2(bp, VECT5);
	turn += uscan2(bp, VECT6);
	turn += uscan2(bp, VECT7);
	turn += uscan2(bp, VECT8);

	if (turn == 0)
		return 0;

	*bp = WHITE;

	sekisa -= turn + turn + 1;
	push(bp);
	push(turn);
	return turn;
}

static uscan2(bp, vect)
register char *bp;
register int vect;
{
	int i, turn;

	for(i = 0; *(bp+=vect) == BLACK; i++)
		;

	if(i == 0 || *bp != WHITE)
		return 0;

	turn = i;
	while(i--) {
		*(bp-=vect) = WHITE;
		push(bp);
	}

	return turn;
}

tup1()
{
	register int turn;
	register char *bp;

	pop(turn);
	pop(bp);

	sekisa -= turn + turn + 1;
	*bp = BLANK;

	while(turn--) {
		pop(bp);
		*bp = WHITE;
	}
}

tup2()
{
	register int turn;
	register char *bp;

	pop(turn);
	pop(bp);

	sekisa += turn + turn + 1;
	*bp = BLANK;

	while(turn--) {
		pop(bp);
		*bp = BLACK;
	}
}

put3(bp)
register char *bp;
{
	register int turn;

	turn  = uscan3(bp, VECT1);
	turn += uscan3(bp, VECT2);
	turn += uscan3(bp, VECT3);
	turn += uscan3(bp, VECT4);
	turn += uscan3(bp, VECT5);
	turn += uscan3(bp, VECT6);
	turn += uscan3(bp, VECT7);
	turn += uscan3(bp, VECT8);

	return turn;
}

uscan3(bp, vect)
register char *bp;
register int vect;
{
	int i;

	for(i = 0; *(bp+=vect) == WHITE; i++)
		;
	
	if(i && *bp == BLACK)
		return i;
	else
		return 0;
}

put4(bp)
register char *bp;
{
	register int turn;

	turn  = uscan4(bp, VECT1);
	turn += uscan4(bp, VECT2);
	turn += uscan4(bp, VECT3);
	turn += uscan4(bp, VECT4);
	turn += uscan4(bp, VECT5);
	turn += uscan4(bp, VECT6);
	turn += uscan4(bp, VECT7);
	turn += uscan4(bp, VECT8);

	return turn;
}
uscan4(bp, vect)
register char *bp;
register int vect;
{
	int i;

	for(i = 0; *(bp+=vect) == BLACK; i++)
		;
	if(i && *bp == WHITE)
		return i;
	else
		return 0;
}

isable1(bp)
register char *bp;
{
	if(uscan3(bp, VECT1))
		return 1;
	if(uscan3(bp, VECT2))
		return 1;
	if(uscan3(bp, VECT3))
		return 1;
	if(uscan3(bp, VECT4))
		return 1;
	if(uscan3(bp, VECT5))
		return 1;
	if(uscan3(bp, VECT6))
		return 1;
	if(uscan3(bp, VECT7))
		return 1;
	if(uscan3(bp, VECT8))
		return 1;
	return 0;
}

isable2(bp)
register char *bp;
{
	if(uscan4(bp, VECT1))
		return 1;
	if(uscan4(bp, VECT2))
		return 1;
	if(uscan4(bp, VECT3))
		return 1;
	if(uscan4(bp, VECT4))
		return 1;
	if(uscan4(bp, VECT5))
		return 1;
	if(uscan4(bp, VECT6))
		return 1;
	if(uscan4(bp, VECT7))
		return 1;
	if(uscan4(bp, VECT8))
		return 1;

	return 0;
}
