#ifndef _H_MATCH
#define _H_MATCH

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string tag,val;
	Sym(string,string); Sym(string);
	vector<Sym*> nest; void push(Sym*);
	map<string,Sym*> pars; void par(Sym*);
	virtual string head();
	string pad(int);
	virtual string dump(int=0);
	virtual Sym* eval();
	virtual Sym* eq(Sym*);
	virtual Sym* at(Sym*);
};

extern map<string,Sym*> env;
extern void env_init();

struct List: Sym { List(); };

struct Op: Sym { Op(string); Sym*eval(); };

struct Lambda: Sym { Lambda(); Sym*at(Sym*); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_MATCH
