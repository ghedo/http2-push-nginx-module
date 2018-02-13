LEX=flex
YACC=bison
CXX=g++
CC=cc
INCLUDES += -I/home1/irteam/tmp/cJSON/
CXXFLAGS=-g -O0 $(INCLUDES)

main.exe: wapper.o ngx_http_v2_push_rule_dynamic_parse.o lex.yy.o entry.tab.o entry.o execute.o
	$(CXX) $(CXXFLAGS) wapper.o ngx_http_v2_push_rule_dynamic_parse.o lex.yy.o entry.tab.o entry.o execute.o -L/home1/irteam/tmp/cJSON/build/ -lcjson -o main.exe
	#$(CXX) $(CXXFLAGS) lex.yy.o entry.tab.o entry.o execute.o -o main.exe

wapper.o: wapper.c ngx_http_v2_push_rule_dynamic_parse.h
	$(CC) $(CXXFLAGS) -c wapper.c

ngx_http_v2_push_rule_dynamic_parse.o: ngx_http_v2_push_rule_dynamic_parse.cpp /home1/irteam/tmp/cJSON/cJSON.h entry.tab.h entry.hpp
	$(CXX) -I/home1/irteam/tmp/cJSON/ -c ngx_http_v2_push_rule_dynamic_parse.cpp -L/home1/irteam/tmp/cJSON/build/ -lcjson 

lex.yy.o:lex.yy.c entry.tab.h entry.hpp
	$(CXX) $(CXXFLAGS) -c lex.yy.c
entry.tab.o:entry.tab.c entry.hpp
	$(CXX) $(CXXFLAGS) -c entry.tab.c
execute.o:execute.cpp entry.hpp entry.tab.h
	$(CXX) $(CXXFLAGS) -c execute.cpp
entry.o:entry.cpp entry.hpp entry.tab.h
	$(CXX) $(CXXFLAGS) -c entry.cpp
entry.tab.c entry.tab.h:entry.y
	$(YACC) -d entry.y
lex.yy.c:entry.l
	$(LEX) entry.l
clean:
	rm lex.yy.c *tab.* *.o main.exe
