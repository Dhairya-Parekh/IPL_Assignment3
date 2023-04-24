CXX = g++-8
EXE = iplC
CXXDEBUG = -g -Wall
CXXSTD = -std=c++11


.PHONY: all

all: parser lexer type_generator symbtab_generator rstack_generator ast_generator
	$(CXX) $(CXXSTD) $(CXXDEBUG) -o iplC driver.cpp parser.o scanner.o symbtab.o type.o ast.o rstack.o

parser: parser.yy scanner.hh
	bison -d -v $<
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c parser.tab.cc -o parser.o

type_generator: type.hh
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c type.cpp -o type.o

symbtab_generator: symbtab.hh type.hh
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c symbtab.cpp -o symbtab.o

rstack_generator: rstack.hh
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c rstack.cpp -o rstack.o

ast_generator: ast.hh type.hh rstack.hh
	$(CXX) $(CXXSTD) $(CXXDEBUG) -c ast.cpp -o ast.o

lexer: scanner.l scanner.hh parser.tab.hh parser.tab.cc
	flex++ --outfile=scanner.yy.cc $<
		$(CXX) $(CXXSTD) $(CXXDEBUG) -c scanner.yy.cc -o scanner.o

clean:
	rm parser.o scanner.o symbtab.o ast.o rstack.o type.o iplC parser.tab.hh parser.tab.cc scanner.yy.cc stack.hh parser.output location.hh position.hh 