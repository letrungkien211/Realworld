/*======================================================*/
/*							*/
/*		ptn.c  					*/
/*======================================================*/

#include	"othello.h"
#include	"banmen.h"

extern	char	ban[];
extern	char	ban1[];
extern	char	ban2[];
extern 	char	ban3[];
extern	char	ban4[];

extern	int	h7,h8;

#define	STEN	10
#define	STEN2	10
#define	CTEN	10
#define	CTEN2	4

int	tf;

ptn()
{
	h7 = 0;
	pscan(A1,VECT5,VECT7);
	pscan(A8,VECT5,VECT2);
	pscan(H1,VECT4,VECT7);
	pscan(H8,VECT4,VECT2);
}

pscan(p,vect1,vect2)
int	p,vect1,vect2;
{
	int	is,hh;
	is = ban[p];

	if(is == BLACK){
		h7 += pscan1(p,vect1);
		h7 += pscan1(p,vect2);
		h7 += STEN2;
		return;
	}
	if( is == WHITE){
		h7 -= pscan2(p,vect1);
		h7 -= pscan2(p,vect2);
		h7 -= STEN2;
		return;
	}

	if( ban1[p]){
		h7 += pscan3(p,vect1);
		h7 += pscan3(p,vect2);
		h7 += 4;
		h7 += STEN2;
		return;
	}

	if(ban2[p]){
		tf = 0;
		if (ban[p+vect1+vect2] == BLACK)
			tf = 1;
		hh = pscan4(p, vect1);
		hh += pscan4(p,vect2);
		hh += 4;
		if(tf) {
			h7 -= hh;
			h7 -= STEN2;
			return;
		}

	}


	
	switch(ban[p+vect1+vect2]){
		case BLACK:
			h7 -= STEN;
			return;
		case WHITE:
			h7 += STEN;
			return;
	}

	
	is = ban[p+vect1];

	if(is == BLACK)
		h7 -= pscan5(p,vect1);
	if(is == WHITE)
		h7 += pscan6(p,vect1);
			
	is = ban[p+vect2];
	if(is == BLACK)
		h7 -= pscan5(p,vect2);
	if(is == WHITE)
		h7 += pscan6(p,vect2);
}

pscan1(p,vect)
register int p,vect;
{
	int	hyo;

	hyo = 0;
	while(ban[p+=vect] == BLACK)
		;
	
	if(ban[p] == WHITE)
		if(ban1[p] & 1){
			while(ban[p+=vect] == WHITE)
				hyo += 4;
			hyo += 4;
			p += vect;
		}
		else
			return (0);

	while(ban[p] != WALL){	
		if((ban[p] == BLANK) || (ban1[p] & 1))
			hyo += 2;
		else
			return(hyo);
		p += vect;
	}

	return (hyo);
}


pscan2(p,vect)
register int p,vect;
{
	int	hyo;
	int	n;

	hyo = 0;
	while (ban[p+= vect] == WHITE)
		;

	if(ban[p] == BLACK)
		if(ban1[p] & 1){
			while(ban[p+=vect] == BLACK)
				hyo += 4;
			hyo += 4;
			n = ban1[p];
			p += vect;
			if(n){
				switch(ban[p]){
					case BLACK:
						if((ban1[p] &3) == 1)
							break;
					case WHITE:
					case WALL:
						hyo = 0;
				}
			}
		}

		else
			return(0);

	while (ban[p] != WALL) {
		if((ban[p] == BLANK ) || (ban1[p] & 1))
			hyo += 2;
		else
			return (hyo);
		p += vect;
	}

	return (hyo);
}


pscan3(p,vect)
register int p,vect;
{
	int	hyo;
	int	n;

	hyo = 0;
	p += vect;
	if((ban[p] == WHITE ) && (ban1[p] & 2))
		while(ban[p+=vect] == WHITE)
			hyo += 4;

	if((ban[p] == BLACK ) && ((ban1[p] & 1 ) == 0)) {
		hyo += 4;
		while( ban[p+=vect] == BLACK)
			hyo += 4;
	}

	if(ban1[p] == WHITE)
		if(ban[p] & 1) {
			while(ban[p+=vect] == WHITE)
				hyo += 4;
			hyo += 4;
			n = ban1[p];
			p += vect;

			if(n){
				switch(ban[p]) {
					case WHITE:
						if((ban1[p] & 3)== 1)
							break;
					case BLACK:
					case WALL:
						hyo = 0;
				}
			}
		}
		else
			return(0);
	while (ban[p] != WALL ) {
		if((ban[p] == BLANK) || (ban1[p] & 1))
			hyo += 2;
		else
			return (hyo);
		p += vect;
	}

	return (hyo);
}



pscan4(p,vect)
register int	p,vect;
{
	int	hyo;
	int	n;

	hyo = 0;
	p += vect;
	if((ban[p] == BLACK) && (ban1 [p] & 2 )) {
		while(ban[p+=vect] == BLACK)
			hyo += 4;

		if((ban1[p] & 1) == 0 ) {
			tf = 1;
			return (hyo);
		}
	}

	if((ban[p] == WHITE ) && (ban1[p] & 1 )) {
		hyo += 4 ;
		while ( ban[p += vect] == WHITE )
			hyo += 4;
	}
	
	if(ban[p] == BLACK)
		if(ban1[p] & 1) {
			while(ban[p+=vect] == BLACK)
				hyo += 4;
			hyo += 4;
			n = ban1[p];
			p += vect;

			if(n)
				switch(ban[p]) {
					case BLACK:
						if((ban1[p] & 3) == 1)
							break;
					case WHITE:
					case WALL:
						hyo = 0;
				}
			}
			else 
				return (0);

		while(ban[p] != WALL) {
			if((ban[p] == BLANK) || (ban1[p] & 1))
				hyo += 2 ;
			else
				return (hyo);
				
			p += vect;
		}

		return ( hyo);
}

pscan5(p,vect)
register int p,vect;
{
	p += vect;
	if(( ban1[p] & 1) == 0 )
		return(0);
	
	if(ban1[p] & 2)
		return(CTEN);
	
	while(ban[p += vect] == BLACK)
		;

	if(ban2[2])
		return CTEN;
	else
		return CTEN2;
}

pscan6(p, vect)
register int p, vect;
{
	p += vect;
	if(( ban1[p] & 1) == 0)
		return(0);

	if(ban1[p] & 2 ) 
		return(CTEN);

	while(ban[p+=vect] == WHITE)
		;
	
	if(ban1[p])
		return CTEN;
	else
		return CTEN2;
}




								


						
