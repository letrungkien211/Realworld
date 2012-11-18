OTHELLO1 = othello.o com.o put.o joseki.o mr1.o mr2.o ab.o cell.o
OTHELLO2 = eval.o bstat.o ptn.o pass.o

othello : $(OTHELLO1) $(OTHELLO2) othello.h banmen.h
	cc $(OTHELLO1) $(OTHELLO2) -o othello -lm

othello.o : othello.c othello.h banmen.h
	cc  -g -c othello.c 

com.o : com.c othello.h banmen.h
	cc  -g -c com.c 

put.o : put.c banmen.h
	cc  -g -c put.c 

joseki.o : joseki.c othello.h banmen.h
	cc  -g -c joseki.c 

mr1.o : mr1.c othello.h
	cc  -g -c mr1.c 

mr2.o : mr2.c othello.h
	cc  -g -c mr2.c 

ab.o : ab.c othello.h
	cc  -g -c ab.c 

cell.o : cell.c othello.h
	cc  -g -c cell.c 

eval.o : eval.c othello.h
	cc  -g -c eval.c 

bstat.o : bstat.c othello.h banmen.h
	cc  -g -c bstat.c 

ptn.o : ptn.c othello.h banmen.h
	cc  -g -c ptn.c 

pass.o : pass.c othello.h banmen.h
	cc  -g -c pass.c 

