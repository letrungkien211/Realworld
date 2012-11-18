#include <stdio.h> 

#define BLANK ' '
#define BLACK 'X'
#define WHITE '0'
#define WALL  '|'

#define VECT1 -10
#define VECT2  -9
#define VECT3  -8
#define VECT4  -1
#define VECT5   1 
#define VECT6   8 
#define VECT7   9 
#define VECT8  10

/* commented 2012/7/4 */
/* #define NULL    0  */

struct cell
{
	struct cell	*child;
	struct cell *cdr;
	char	t;
	int		h;
};

typedef struct cell	CELL;
