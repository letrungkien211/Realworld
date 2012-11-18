#include 	"othello.h"
#include 	"banmen.h"

#define		COM		1
#define		MAN		2

char	ban[91];
char	*aki[61];

int		stack[500];
int		*sp;

int		hukasa;
int		level;
int		player[3];
int		te;

main()
{
	int		i;
	int		teban;
	char	line[10];

	printf("\nMORITAN OTHELLO Ver 6.1\n");
	printf("Copyright (C) 1986 by K.Morita\n\n");
	printf("Typed by Hasegawa et. al.\n");
	printf("Edited and corrected  by Saishi IBA\n");
	printf("CONTACT Saishi if needed!!\n");

	do {
		printf("\n1.man-com 2.com-man 3.com-com\n");
		printf("select= ");
		/* gets --> fgets 2012/7/4 */
		/* gets(line,10); */
		fgets(line,10,stdin);
		sscanf(line, "%d", &i);
	}
	while(i<1 || i>3);

	player[0]=player[1]=COM;
	player[i-1]=MAN;

	do {
		printf("Level = ");
		/* gets --> fgets 2012/7/4 */
		/* gets(line,10); */
		fgets(line,10,stdin);
		sscanf(line, "%d", &level);
	}
	while(level<1 || level>8);

	set_ban();

	teban = 0;

	for(;;) {
		disp_ban();
		sp = stack;

		move(teban);
		if(te == -1)
			break;

		if(te)
			if(teban == 0)
				put1(te + ban);
			else
				put2(te + ban);
		teban = 1 - teban;
	}
}

move(teban)
int	teban;
{
	int st;
	if(teban)
		rev_ban();

	/* next is modified by Saishi 1989 6 14 */
	st = stat();
	if (st > 0)
		if(player[teban] == COM)
			com();
		else
			{
			if (st == 1) printf("\n Your move is FORCED!!!\n");
			man();
			}

	if(teban)
		printf("\nwhite:");
	else
		printf("\nblack:");

	if(te > 0)
		printf("%c%c", (te % 9) + 96, (te / 9) + 48);
	else
		printf(" PASS");

	if(teban)
		rev_ban();
}

man()
{
	int	x, y;
	char	line[10];

	for(;;) {
		printf("\nInput your move ? ");
		/* gets --> fgets 2012/7/4 */
		/* gets(line,10); */
		fgets(line,10,stdin);
		x = line[0] & 15;
		y = line[1] & 15;

		if(x<1 || x>8 || y<1 || y>8)
			continue;

		if(ban[y*9+x] != BLANK)
			continue;

		te = y*9+x;
		if(isable1(te + ban))
			return;
	}
}

stat()
{
	int	t;
	int	n1, n2;

	te = n1 = n2 = 0;

	for(t = A1; t <= H8; t++) {
		if(ban[t] != BLANK)
			continue;

		if(isable1(t + ban)) {
			te = t;
			n1++;
		}

		if(isable2(t + ban))
			n2++;
	}

	if(n1)
		return n1;
	else if(n2)
		return 0;
	else {
		te = -1;
		return -1;
	}
}

set_ban()
{
	int	i, x, y;

	for(i = 0; i < 91; )
		ban[i++] = WALL;

	for(y = 1; y < 9; y++)
		for(x = 1; x < 9; x++)
			ban[y*9+x] = BLANK;

	ban[D4] = WHITE;
	ban[E4] = BLACK;
	ban[D5] = BLACK;
	ban[E5] = WHITE;
}

disp_ban()
{
	int	x, y;
	int b, w;
	char	c;

	b = w = 0;

	printf("\n  a b c d e f g h");

	for(y = 1; y <= 8; y++) {
		printf("\n%1d", y);
		for(x = 1; x <= 8; x++) {
			c = ban[y*9+x];
			printf(" %c", c);
			if(c == BLACK)
				b++;
			else if(c == WHITE)
				w++;
		}
	}
	printf("\nblack=%2d white=%2d\n", b, w);
}

rev_ban()
{
	register char	*p;

	for(p = &ban[A1]; p <= &ban[H8]; p++) {
		switch(*p) {
			case BLACK:
				*p = WHITE;
				break;
			case WHITE:
				*p = BLACK;
		}
	}
}


