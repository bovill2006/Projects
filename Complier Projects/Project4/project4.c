#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"

#define ALLOC(t, i) (t*) calloc(i, sizeof(t))

extern char token[MAX_TOKEN_LENGTH];
extern int ttype;
extern int line_no;
extern int tokenLength;

int varCount = 0;
struct varNode* variables;
struct varNode* switchVar;
struct statementNode* parseBody();
struct statementNode* parseStatementList(); 
struct varList
{
	char * n;
	struct varList * var;
};


void parseVar()
{
	struct varList* p;
	struct varList* temp = ALLOC(struct varList, 1);
	int flag = 1;

	p = temp;

	while (flag == 1)
	{
		ttype = getToken();
		if (ttype == SEMICOLON){ flag = 0; }
		else if (ttype == ID){
			p->n = ALLOC(char, tokenLength + 1);
			strcpy(p->n, token);
			varCount++;
		}
		else if (ttype == COMMA){
			p->var = ALLOC(struct varList, 1);
			p = p->var;
		}
		else {
			printf("error at line: %d\n", line_no);
			exit(0);
		}
	}
	variables = ALLOC(struct varNode, varCount);
	int i;
	p = temp;
	for (i = 0; i < varCount; i++){
		variables[i].name = ALLOC(char, strlen(p->n) + 1);
		strcpy(variables[i].name, p->n);
		p = p->var;
	}
}

int getIndex(char* name)
{
	int j;
	for (j = 0; j < varCount; j++){
		if (strcmp(variables[j].name, name) == 0){
			return j;
		}
	}
	return -1;
}
struct assignmentStatement* parseAssign()
{
	
	int index;
	struct assignmentStatement* assign = ALLOC(struct assignmentStatement, 1);
	getToken();
	index = getIndex(token);
	assign->lhs = &variables[index];
	getToken();

	ttype = getToken();
	if (ttype == ID){
		index = getIndex(token);
		assign->op1 = &variables[index];
	}
	else{
		assign->op1 = ALLOC(struct varNode, 1);
		assign->op1->value = atoi(token);
	}

	ttype = getToken();
	if (ttype == SEMICOLON){
		return assign;
	}
	else{
		assign->op = ttype;
	}

	ttype = getToken();
	if (ttype == ID){
		index = getIndex(token);
		assign->op2 = &variables[index];
	}
	else{
		assign->op2 = ALLOC(struct varNode, 1);
		assign->op2->value = atoi(token);
	}
	getToken();
	return assign;
}
struct ifStatement* parseCond()
{
	int index;
	struct ifStatement* statement = ALLOC(struct ifStatement, 1);

	ttype = getToken();
	if (ttype == ID){
		index = getIndex(token);
		statement->op1 = &variables[index];
	}
	if (ttype == NUM){
		statement->op1 = ALLOC(struct varNode, 1);
		statement->op1->value = atoi(token);
	}

	ttype = getToken();
	if (ttype == GREATER || ttype == LESS || ttype == NOTEQUAL){
		statement->relop = ttype;
	}

	ttype = getToken();
	if (ttype == ID){
		index = getIndex(token);
		statement->op2 = &variables[index];
	}
	if (ttype == NUM){
		statement->op2 = ALLOC(struct varNode, 1);
		statement->op2->value = atoi(token);
	}

	return statement;
}
struct ifStatement* parseCase(struct varNode* switchVar)
{
	int index;
	struct ifStatement* statement = ALLOC(struct ifStatement, 1);
	ttype = getToken();
	//if (ttype == CASE){ getToken(); }
	statement->op1 = ALLOC(struct varNode, 1);
	statement->op2 = ALLOC(struct varNode, 1);
	statement->op1 = switchVar;
	statement->relop = NOTEQUAL;
	statement->op2 ->value = atoi(token);
	getToken();
	return statement;
}


struct statementNode* parseStatement()
{
	int index;
	
	struct statementNode* noop = ALLOC(struct statementNode, 1);
	noop->stmt_type = NOOPSTMT;
	struct statementNode* p;
	struct statementNode* statement = ALLOC(struct statementNode, 1);
	ttype = getToken();
	if (ttype == ID)
	{
		ungetToken();
		statement->stmt_type = ASSIGNSTMT;
		statement->assign_stmt = parseAssign();
	}
	else if (ttype == WHILE) {
		statement->stmt_type = IFSTMT;
		statement->if_stmt = parseCond();
		statement->next = ALLOC(struct statementNode, 1);
		statement->next->stmt_type = NOOPSTMT;
		statement->if_stmt->true_branch = parseBody();

		p = statement->if_stmt->true_branch;
		while (p->next != NULL){ p = p->next; }
		p->next = ALLOC(struct statementNode, 1);
		p->next->stmt_type = GOTOSTMT;
		p->next->goto_stmt = ALLOC(struct gotoStatement, 1);
		p->next->goto_stmt->target = statement;
		statement->if_stmt->false_branch = statement->next;
	}
	else if (ttype == IF){
		statement->stmt_type = IFSTMT;
		statement->if_stmt = parseCond();
		statement->next = ALLOC(struct statementNode, 1);
		statement->next->stmt_type = NOOPSTMT;
		statement->if_stmt->true_branch = parseBody();

		p = statement->if_stmt->true_branch;
		while (p->next != NULL){ p = p->next; }
		p->next = ALLOC(struct statementNode, 1);
		p->next->stmt_type = NOOPSTMT;
		p->next->next = statement->next;
		statement->if_stmt->false_branch = statement->next;
	}
	else if (ttype == SWITCH || ttype == CASE || ttype == DEFAULT){
		
		if (ttype == SWITCH){
			ttype == getToken();
			//switchVar = ALLOC(struct varNode, 1);
			index = getIndex(token);
			switchVar = &variables[index];
			statement = parseBody();
		}
		if (ttype == CASE){

			statement->stmt_type = IFSTMT;
			statement->if_stmt = parseCase(switchVar);
			statement->next = ALLOC(struct statementNode, 1);
			statement->next->stmt_type = NOOPSTMT;
			statement->if_stmt->false_branch = ALLOC(struct statementNode, 1);
			statement->if_stmt->false_branch = parseBody();

			p = statement->if_stmt->false_branch;
			while (p->next != NULL){ p = p->next; }
			p->next = ALLOC(struct statementNode, 1);
			p->next->stmt_type = GOTOSTMT;
			p->next->goto_stmt = ALLOC(struct gotoStatement, 1);
			p->next->goto_stmt->target = ALLOC(struct statementNode, 1);
			p->next->goto_stmt->target = noop;
			statement->if_stmt->true_branch = statement ->next;
		}
		if (ttype == DEFAULT)
		{
			getToken();
			statement = parseBody();
			statement->next = ALLOC(struct statementNode, 1);
			statement->next = noop;

		}
	}
	else if (ttype == PRINT)
	{
		statement->stmt_type = PRINTSTMT;
		statement->print_stmt = ALLOC(struct printStatement, 1);
		ttype = getToken();
		if (ttype == ID)
		{
			int index = getIndex(token);
			statement->print_stmt->id = &variables[index];
		}
		ttype = getToken();
	}
	else{
		free(statement);
		ungetToken();
	}
	return statement;
}

struct statementNode* parseStatementList()
{
	struct statementNode* statementList = ALLOC(struct statementNode, 1);
	struct statementNode* p;
	ttype = getToken();
	if (ttype == WHILE || ttype == IF || ttype == ID || ttype == PRINT || ttype == CASE || ttype == SWITCH || ttype == DEFAULT){
		ungetToken();
		statementList = parseStatement();
		ttype = getToken();
		if (ttype == WHILE || ttype == IF || ttype == ID || ttype == PRINT|| ttype == CASE || ttype == SWITCH || ttype == DEFAULT){
			ungetToken();
			p = statementList;
			while (p->next != NULL){ p = p->next; }
			p->next = parseStatementList();

		}
		else { ungetToken(); }
	}
	else { ungetToken(); }

	return statementList;
}

struct statementNode* parseBody()
{
	struct statementNode* body;
	ttype = getToken();
	if (ttype == LBRACE){
		body = parseStatementList();
		ttype = getToken();
		if (ttype == RBRACE){
			return body;
		}
	}
}

struct statementNode*  parse_program_and_generate_intermediate_representation()
{
	struct statementNode* program;
	parseVar();
	program = parseBody();
	return program;
}
