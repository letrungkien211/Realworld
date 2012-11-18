#include	"othello.h"
#include	"banmen.h"

#define	P0	6
#define	P1	3
#define	P2	6

extern	char	ban[];
extern	char	ban1[];
extern	char	ban2[];
extern	char	ban3[];
extern	char	ban4[];

extern	int	h1, h2, h3, h4, h5, h6;

pass1()
{
	register	int	p;
	register	int	is;
	int		n1, n2;
	int		t, t2;

	static	char	tbl[] =
	{
		0,0,0,0,0,0,0,0,0,
		0,0,6,4,5,5,4,6,0,
		0,6,6,5,5,5,5,6,6,
		0,4,5,5,4,4,5,5,4,
		0,5,5,4,4,4,4,5,5,
		0,5,5,4,4,4,4,5,5,
		0,4,5,5,4,4,5,5,4,
		0,6,6,5,5,5,5,6,6,
		0,0,6,4,5,5,4,6,0
	};

	for (p = A1; p <= H8; p++) {
		if ((is = ban[p]) == WALL)
			continue;

		n1 = ban1[p];
		n2 = ban2[p];

		if (is == BLANK) {
			if (n1) {
				t = P0 - n1;
				if (t > 0)
					t += P1;
				else
					t = P1;

				ban1[p] = t;

				t += P2;
				t2 = (t>>1) + t;

				ban3[p+VECT1] += t;
				ban3[p+VECT2] += t2;
				ban3[p+VECT3] += t;
				ban3[p+VECT4] += t2;
				ban3[p+VECT5] += t2;
				ban3[p+VECT6] += t;
				ban3[p+VECT7] += t2;
				ban3[p+VECT8] += t;
			}

			if (n2) {
				t = P0 - n2;
				if (t > 0)
					t += P1;
				else
					t = P1;

				ban2[p] = t;

				t += P2;
				t2 = (t>>1) + t;

				ban4[p+VECT1] += t;
				ban4[p+VECT2] += t2;
				ban4[p+VECT3] += t;
				ban4[p+VECT4] += t2;
				ban4[p+VECT5] += t2;
				ban4[p+VECT6] += t;
				ban4[p+VECT7] += t2;
				ban4[p+VECT8] += t;
			}
		}
		else {
			ban2[p] = 0;

			if (is == BLACK) {
				if ((n1 & 1) == 0) {
					h1++;
					continue;
				}

				if ((t = n1>>2) == 0)
					continue;

				if (n1)
					ban2[p] = n1 + tbl[p];
				else
					h2 -= (t>>1) + tbl[p];
			}
			else {
				if ((n1 & 1) == 0) {
					h1--;
					continue;
				}

				if ((t = n1>>2) == 0)
					continue;

				if (n1)
					ban2[p] = n1 + tbl[p];
				else
					h2 += (t>>1) + tbl[p];
			}
		}
	}
}

pass2()
{
	register	int	p, n;

	static	char	tbl[] =
	{
		0,0,0,0,0,0,0,0,0,
		0,7,0,7,6,6,7,0,7,
		0,0,0,5,6,6,5,0,0,
		0,7,5,6,7,7,6,5,7,
		0,6,6,7,7,7,7,6,6,
		0,6,6,7,7,7,7,6,6,
		0,7,5,6,7,7,6,5,7,
		0,0,0,5,6,6,5,0,0,
		0,7,0,7,6,6,7,0,7
	};

	for (p = A1; p <= H8; p++) {
		if (ban[p] != BLANK)
			continue;

		if (n = ban1[p]) {
			n *= 12;
			n -= ban3[p];
			if (n < 0)
				n = 0;

			h3 += n + tbl[p];
		}

		if (n = ban2[p]) {
			n *= 12;
			n -= ban4[p];
			if (n < 0)
				n = 0;
			
			h4 += n + tbl[p];
		}
	}
}

pass3()
{
	register	int	p, t1;
	int	t2;

	for (p = A1; p <= H8; p++) {
		ban3[p] = 0;
		ban4[p] = 0;
	}

	for (p = A1; p <= H8; p++) {
		switch(ban[p]) {
			case BLACK:
				if ((t1 = ban2[p]) == 0)
					break;

				t1 += 4;
				t2 = t1>>1;

				ban3[p+VECT1] += t2;
				ban3[p+VECT2] += t1;
				ban3[p+VECT3] += t2;
				ban3[p+VECT4] += t1;
				ban3[p+VECT5] += t1;
				ban3[p+VECT6] += t2;
				ban3[p+VECT7] += t1;
				ban3[p+VECT8] += t2;
				break;
			case WHITE:
				if((t1 = ban2[p]) == 0)
					break;

				t1 += 4;
				t2 = t1>>1;

				ban4[p+VECT1] += t2;
				ban4[p+VECT2] += t1;
				ban4[p+VECT3] += t2;
				ban4[p+VECT4] += t1;
				ban4[p+VECT5] += t1;
				ban4[p+VECT6] += t2;
				ban4[p+VECT7] += t1;
				ban4[p+VECT8] += t2;
		}
	}
}

pass4()
{
	register	int	p, n;

	static	char	tbl[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0,18,14,16,16,14,18, 0,
		0,18,20,16,14,14,16,20,18,
		0,14,16,16,14,14,16,16,14,
		0,16,14,14,14,14,14,14,16,
		0,16,14,14,14,14,14,14,16,
		0,14,16,16,14,14,16,16,14,
		0,18,20,16,14,14,16,20,18,
		0, 0,18,14,16,16,14,18, 0
	};

	for (p = A1; p <= H8; p++) {
		switch(ban[p]) {
			case BLACK:
				if ((n = ban2[p]) == 0)
					break;

				n = n * 10 - ban3[p];
				if (n < 0)
					n = 0;

				h5 += n + tbl[p] + 6;
				break;

			case WHITE:
				if ((n = ban2[p]) == 0)
					break;

				n = n * 10 - ban4[p];
				if (n < 0)
					n = 0;

				h6 += n + tbl[p] + 6;
		}
	}
}

