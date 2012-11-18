#include 	"othello.h" 
#include	"banmen.h" 

extern int	level;

extern char	ban[];
extern char	*aki[];
extern int	te;

extern CELL	*get_cell();

int	sekisa;

char	yuusen[] =
	{
		A1,H1,A8,H8,
		D3,E3,C4,C5,F4,F5,D6,E6,
		C3,F3,C6,F6,
		D2,E2,B4,B5,G4,G5,D7,E7,
		C1,F1,A3,A6,H3,H6,C8,F8,
		D1,E1,A4,A5,H4,H5,D8,E8,
		C2,F2,B3,B6,G3,G6,C7,F7,
		B1,G1,A2,A7,H2,H7,B8,G8,
		B2,G2,B7,G7,
		0
	};

struct	lvt
{
	int	hukasa;
	int kyoka;
	int hishou;
	int kanzen;
};

struct	lvt		lvtbl[] =
{
	{ 2,10,12,10 },
	{ 2,20,12,10 },
	{ 2,35,13,11 },
	{ 4,10,13,11 },
	{ 4,20,14,11 },
	{ 4,35,14,12 },
	{ 6,10,15,12 },
	{ 6,20,15,12 }
};

com()
{
	int i, kuusho, hukasa;
	int x, y;
	char **a;
	char *bp;
	CELL *p;

	joseki();
	if(te)
		return;  
	kuusho = 0;
	a = aki;

	for (i = 0; i < 60;  ) {
		bp = ban + yuusen[i++];
		if(*bp == BLANK) {
			*(a++) = bp;
			kuusho++;
		}
	}

	*a = 0;

	sekisa = 0;
	for(y = 1; y < 9; y++) {
		for(x = 1; x < 9; x++) {
			switch(ban[y*9+x]) {
				case BLACK:
					sekisa++;
					break;
				case WHITE:
					sekisa--;
			}
		}
	}

	init_cell();
	p = get_cell();
	p->child = NULL;
	p->cdr = NULL;

	if(kuusho <= lvtbl[level-1].kanzen) {
		p->h = -64;
		mr2(p, kuusho, 64);
	}
		else if(kuusho <= lvtbl[level-1].hishou) {
			p->h = -1;
			mr2(p, kuusho, 1);
		}
		else {
			hukasa = lvtbl[level-1].hukasa;
			if(kuusho <= lvtbl[level-1].kyoka) 
				hukasa += 2;

			p->h = -10000;
			mr1(p, hukasa, 10000);
		}

		te = p->t;
}
