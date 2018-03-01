LEX=flex
YACC=bison

.PHONY: all
all: entry.tab.h entry.tab.c lex.yy.c

entry.tab.c entry.tab.h:entry.y
	$(YACC) -d entry.y
lex.yy.c:entry.l
	$(LEX) entry.l

clean:
	rm lex.yy.c *tab.* *.o
