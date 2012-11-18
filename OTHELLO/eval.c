#include		"othello.h"

extern char		ban[];

char	ban1[91];
char	ban2[91];
char	ban3[91];
char	ban4[91];

int		h1, h2, h3, h4, h5, h6, h7;

eval2()
{
	int	hyo;

	rev_ban();
	hyo = eval1();
	rev_ban();
	return -hyo;
}

eval1()
{
	int		hyo;

	h1=h2=h3=h4=h5=h6=h7=0;

	bstat();
	ptn();
	pass1();
	pass2();
	pass3();
	pass4();

	hyo = h3+h6-h4-h5;
	hyo += h1 * 100;
	hyo += h7 * 25;
	hyo += h2 / 2;
	return hyo;
}
