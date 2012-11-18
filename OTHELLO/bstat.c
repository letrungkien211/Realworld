#include			"othello.h"
#include		    "banmen.h"


extern char			ban[];
extern char			ban1[];
extern char			ban2[];
extern char			ban3[];
extern char			ban4[];

bstat()
{
	register int		p;

	for(p = A1; p <= H8; p++) {
		ban1[p] = 0;
		ban2[p] = 0;
		ban3[p] = 0;
		ban4[p] = 0;
	}

	bscan(A1, VECT5, 2, 1, 8);
	bscan(A2, VECT5, 2, 1, 8);
	bscan(A3, VECT5, 2, 1, 8);
	bscan(A4, VECT5, 2, 1, 8);
	bscan(A5, VECT5, 2, 1, 8);
	bscan(A6, VECT5, 2, 1, 8);
	bscan(A7, VECT5, 2, 1, 8);
	bscan(A8, VECT5, 2, 1, 8);

	bscan(A1, VECT7, 2, 1, 8);
	bscan(B1, VECT7, 2, 1, 8);
	bscan(C1, VECT7, 2, 1, 8);
	bscan(D1, VECT7, 2, 1, 8);
	bscan(E1, VECT7, 2, 1, 8);
	bscan(F1, VECT7, 2, 1, 8);
	bscan(G1, VECT7, 2, 1, 8);
	bscan(H1, VECT7, 2, 1, 8);

	bscan(F1, VECT8, 1, 2, 4);
	bscan(E1, VECT8, 1, 2, 4);
	bscan(D1, VECT8, 1, 2, 4);
	bscan(C1, VECT8, 1, 2, 4);
	bscan(B1, VECT8, 1, 2, 4);
	bscan(A1, VECT8, 1, 2, 4);
	bscan(A2, VECT8, 1, 2, 4);
	bscan(A3, VECT8, 1, 2, 4);
	bscan(A4, VECT8, 1, 2, 4);
	bscan(A5, VECT8, 1, 2, 4);
	bscan(A6, VECT8, 1, 2, 4);

	bscan(C1, VECT6, 1, 2, 4);
	bscan(D1, VECT6, 1, 2, 4);
	bscan(E1, VECT6, 1, 2, 4);
	bscan(F1, VECT6, 1, 2, 4);
	bscan(G1, VECT6, 1, 2, 4);
	bscan(H1, VECT6, 1, 2, 4);
	bscan(H2, VECT6, 1, 2, 4);
	bscan(H3, VECT6, 1, 2, 4);
	bscan(H4, VECT6, 1, 2, 4);
	bscan(H5, VECT6, 1, 2, 4);
	bscan(H6, VECT6, 1, 2, 4);
}

bscan(p, vect, k, u, h)
register int 	p, vect;
int		k, u, h;
{
	int		p2;
	int		is1, is2;

	is1 = ban[p];
	if(is1 != BLANK) {
		while(ban[p+=vect] == is1)
			;

		is2 = is1;
		is1 = ban[p];
	}

	if(is1 == BLANK) {
		ban1[p-vect] += h;

		while(ban[p+=vect] == BLANK)
			;
		is2 = BLANK;
		is1 = ban[p];
		ban1[p] += h;
	}

	if (is1 == WALL)
		return;

	for(;;) {
		p2 = p;

		while(ban[p+=vect] == is1) ;

		if (ban[p] == WALL)
			return;

		if(is2 == BLANK) {
			is2 = is1;
			is1 = ban[p];

			if(is1 == BLANK)
				do
					ban1[p2] |= 1;
				while((p2+=vect) != p);
			else {
				ban2[p2] += k;

				if(is2 == WHITE)
					ban1[p2-vect] += u;
				else
					ban2[p2-vect] += u;

				do
					ban1[p2] |= 3;
				while((p2+=vect) != p);
			}
		}
		else {
			is2 = is1;
			is1 = ban[p];

			if(is1 == BLANK) {
				ban2[p-vect] += k;
			
				if(is2 == WHITE)
					ban1[p] += u;
				else
					ban2[p] += u;

				do
					ban1[p2] |= 3;
				while((p2+=vect) != p);
			}
		}

		if(is1 == BLANK) {
			ban1[p-vect] += h;
			while(ban[p+=vect] == BLANK)
				;

			is2 = BLANK;
			is1 = ban[p];

			if(is1 == WALL)
				return;

			ban1[p] += h;
		}
	}
}
