/*----------------------------------------------------------------------------
Note: the code in this file is not to be shared with anyone or posted online.
(c) Rida Bazzi, 2014
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "syntax.h"
#define TRUE 1
#define FALSE 0

/* ------------------------------------------------------- */
/* -------------------- LEXER SECTION -------------------- */
/* ------------------------------------------------------- */

#define KEYWORDS  7

enum TokenTypes
{
	VAR = 1, WHILE, INT, REAL, STRING, BOOLEAN, TYPE,
	PLUS, MINUS, DIV, MULT, EQUAL,
	COLON, COMMA, SEMICOLON,
	LBRAC, RBRAC, LPAREN, RPAREN, LBRACE, RBRACE,
	NOTEQUAL, GREATER, LESS, LTEQ, GTEQ, DOT,
	ID, NUM, REALNUM,
	ERROR
};

char *reserved[] = { "",
"VAR", "WHILE", "INT", "REAL", "STRING", "BOOLEAN", "TYPE",
"+", "-", "/", "*", "=",
":", ",", ";",
"[", "]", "(", ")", "{", "}",
"<>", ">", "<", "<=", ">=", ".",
"ID", "NUM", "REALNUM",
"ERROR"
};

// Global Variables associated with the next input token
#define MAX_TOKEN_LENGTH 100
char token[MAX_TOKEN_LENGTH]; // token string
int ttype; // token type
int activeToken = FALSE;
int tokenLength;
int line_no = 1;

int MaxTypeInt = BOOLEAN + 1;
int ImplicitCount = 0;
int typeCount = 0;
int varCount = 0;
int prefix = 0; 


void skipSpace()
{
	char c;

	c = getchar();
	line_no += (c == '\n');
	while (!feof(stdin) && isspace(c)) {
		c = getchar();
		line_no += (c == '\n');
	}
	ungetc(c, stdin);
}

int isKeyword(char *s)
{
	int i;

	for (i = 1; i <= KEYWORDS; i++)
		if (strcmp(reserved[i], s) == 0)
			return i;
	return FALSE;
}

void ungetToken()
{
	activeToken = TRUE;
}

int scan_number()
{
	char c;

	c = getchar();
	if (isdigit(c))
	{
		// First collect leading digits before dot
		// 0 is a nNUM by itself
		if (c == '0')
		{
			token[tokenLength] = c;
			tokenLength++;
			token[tokenLength] = '\0';
		}
		else
		{
			while (isdigit(c))
			{
				token[tokenLength] = c;
				tokenLength++;
				c = getchar();
			}
			ungetc(c, stdin);
			token[tokenLength] = '\0';
		}
		// Check if leading digits are integer part of a REALNUM
		c = getchar();
		if (c == '.')
		{
			c = getchar();
			if (isdigit(c))
			{
				token[tokenLength] = '.';
				tokenLength++;
				while (isdigit(c))
				{
					token[tokenLength] = c;
					tokenLength++;
					c = getchar();
				}
				token[tokenLength] = '\0';
				if (!feof(stdin))
					ungetc(c, stdin);
				return REALNUM;
			}
			else
			{
				ungetc(c, stdin);
				c = '.';
				ungetc(c, stdin);
				return NUM;
			}
		}
		else
		{
			ungetc(c, stdin);
			return NUM;
		}
	}
	else
		return ERROR;
}

int scan_id_or_keyword()
{
	int ttype;
	char c;

	c = getchar();
	if (isalpha(c))
	{
		while (isalnum(c))
		{
			token[tokenLength] = c;
			tokenLength++;
			c = getchar();
		}
		if (!feof(stdin))
			ungetc(c, stdin);
		token[tokenLength] = '\0';
		ttype = isKeyword(token);
		if (ttype == 0)
			ttype = ID;
		return ttype;
	}
	else
		return ERROR;
}

int getToken()
{
	char c;

	if (activeToken)
	{
		activeToken = FALSE;
		return ttype;
	}
	skipSpace();
	tokenLength = 0;
	c = getchar();
	switch (c)
	{
	case '.': return DOT;
	case '+': return PLUS;
	case '-': return MINUS;
	case '/': return DIV;
	case '*': return MULT;
	case '=': return EQUAL;
	case ':': return COLON;
	case ',': return COMMA;
	case ';': return SEMICOLON;
	case '[': return LBRAC;
	case ']': return RBRAC;
	case '(': return LPAREN;
	case ')': return RPAREN;
	case '{': return LBRACE;
	case '}': return RBRACE;
	case '<':
		c = getchar();
		if (c == '=')
			return LTEQ;
		else if (c == '>')
			return NOTEQUAL;
		else
		{
			ungetc(c, stdin);
			return LESS;
		}
	case '>':
		c = getchar();
		if (c == '=')
			return GTEQ;
		else
		{
			ungetc(c, stdin);
			return GREATER;
		}
	default:
		if (isdigit(c))
		{
			ungetc(c, stdin);
			return scan_number();
		}
		else if (isalpha(c))
		{
			ungetc(c, stdin);
			return scan_id_or_keyword();
		}
		else if (c == EOF)
			return EOF;
		else
			return ERROR;
	}
}

/* ----------------------------------------------------------------- */
/* -------------------- SYNTAX ANALYSIS SECTION -------------------- */
/* ----------------------------------------------------------------- */

struct UserInput
{
	int t;			// type id for the user input
	char id[20];	// actual string for the user input
	int IorE;		// 0 for explicit 1 for implicit -1 for unknown
};


struct UserInput symbolTable[80];	// Type starts at 0 var starts at 40
struct UserInput implicitList[10];	// Implicit list 

int addType(char* id)
{
	strcpy(symbolTable[typeCount].id, id);
	symbolTable[typeCount].t = MaxTypeInt;
	typeCount++;
	int output = typeCount-1;
	return output;
}

int addVar(char* id)
{
	strcpy(symbolTable[40 + varCount].id, id);
	symbolTable[40 + varCount].t = MaxTypeInt;
	varCount++;
	int output = 40+varCount-1;
	return output ;
}

void testPrint() //for debugg purpses only 
{
	int i;
	printf("\nType");
	for (i = 0; i < typeCount; i++)
	{
		printf("\n%d:\t TYPE: %d  ID: %s", i, symbolTable[i].t, symbolTable[i].id);
	}
	printf("\nVariable");
	for (i = 0; i < varCount; i++)
	{
		printf("\n%d:\t TYPE: %d  ID: %s", 40+i, symbolTable[i+40].t, symbolTable[i+40].id);
	}
	printf("\n\nImplicit");
	for (i = 0; i < ImplicitCount; i++)
	{
		printf("\n%d:\t TYPE: %d  ID: %s", i, implicitList[i].t, implicitList[i].id);
	}
	printf("\n\n");
}

void setSymbolType(int i, int j)
{
	int k = 0;
	for (k; k < typeCount; k++)
	{
		if (symbolTable[k].t == i)
		{
			symbolTable[k].t = j;
		}
	}
	for (k = 0; k < varCount; k++)
	{
		if (symbolTable[40 + k].t == i)
		{
			symbolTable[40 + k].t = j;
		}
	}
}

int locateSymbol_By_Type(int i)
{
	int j = 0;
	for (j; j < typeCount; j++)
	{
		if (symbolTable[j].t == i)
		{
			return j;
		}
	}
	for (j = 0; j < varCount; j++)
	{
		if (symbolTable[40 + j].t == i)
		{
			return j + 40;
		}
	}
	return -1; 
}

int locateSymbol_By_ID(char* i)
{
	int j = 0; 
	for (j; j < typeCount; j++)
	{
		if (strcmp(i, symbolTable[j].id) == 0)
		{
			return j; 
		}
	}
	for (j = 0; j < varCount; j++)
	{
		if (strcmp(i, symbolTable[40 + j].id) == 0)
		{
			return 40 + j;
		}
	}
	return -1;
}
/*-------------------------parser methods for var and type --------------*/
void parseType(struct id_listNode* idList, struct type_nameNode* typeName)
{
	int l, r, j;
	l = addType(idList->id);
	if (typeName->type == ID)
	{
		r = locateSymbol_By_ID(typeName->id);
		if (r > -1){ setSymbolType(symbolTable[l].t, symbolTable[r].t); }

	}
	else
	{
		setSymbolType(symbolTable[l].t, typeName->type);
	}

	if (idList->id_list != NULL)
	{
		parseType(idList->id_list, typeName);
	}
	else{
		if (typeName->type == ID)
		{
			if (locateSymbol_By_ID(typeName->id) < 0){
				for (j = 0; j < ImplicitCount; j++)
				{
					if (strcmp(typeName->id, implicitList[j].id) == 0)
						break;
				}
				if (j == ImplicitCount)
				{
					strcpy(implicitList[ImplicitCount].id, typeName->id);
					implicitList[ImplicitCount].t = MaxTypeInt;
					ImplicitCount++;
					MaxTypeInt++;
				}
			}
		}
	}
}

void parseVar(struct id_listNode* idList, struct type_nameNode* typeName)
{

	int l, r;
	l = addVar(idList->id);
	if (typeName->type == ID)
	{
		r = locateSymbol_By_ID(typeName->id);
		if (r > -1){ setSymbolType(symbolTable[l].t, symbolTable[r].t); }
	}
	else{ setSymbolType(symbolTable[l].t, typeName->type); }

	if (idList->id_list == NULL)
	{
		if (typeName->type == ID && locateSymbol_By_ID(typeName->id) == -1)
		{
			r = addType(typeName->id);
			MaxTypeInt++;
		}
	}
	else{ parseVar(idList->id_list, typeName); }
}

/*-----------------ERROR CHECKING METHODS-------------------------------*/
int error0()// check for type 0 error if true will return 0 else 1
{
	int i, j;
	for (i = 0; i < typeCount; i++){
		for (j = 0; j < typeCount; j++){
			if (strcmp(symbolTable[i].id, symbolTable[j].id) == 0 && i != j){
				return 1; 
			}
		}
	}
	return 0; 
}
int error1() // checks for type 1 error if true will return 0 else 1
{
	int i, j; 
	for (i = 0; i < typeCount; i++){
		for (j = 0; j < varCount; j++){
			if (strcmp(symbolTable[i].id, symbolTable[40+j].id)==0){ 
				return 1; 
			}
		}
	}
	return 0; 
}
int error2()
{
	int i, j;
	for (i = 0; i < varCount; i++){
		for (j = 0; j < varCount; j++){
			if (strcmp(symbolTable[40+i].id, symbolTable[40+j].id) == 0 && i != j){
				return 1;
			}
		}
	}
	return 0;
}

//error3 checker is emmbedded 
//within the while stmt assign 
//stmt and etc instead of a method 
//It is much more effective this way 
//for error3 to work and much less coding

int error4()
{
	int i, j;
	for (i = 0; i < varCount; i++){
		for (j = 0; j < typeCount; j++){
			if (strcmp(symbolTable[40+i].id, symbolTable[j].id) == 0){
				return 1;
			}
		}
	}
	return 0;
}
/* -------------------- PRINTING PARSE TREE -------------------- */
void syntax_error(const char* msg)
{
	printf("Syntax error while parsing %s line %d\n", msg, line_no);
	exit(1);
}

void parse_parse_tree(struct programNode* program)
{
	parse_decl(program->decl);
	parse_body(program->body);
}

void parse_decl(struct declNode* dec)
{
	if (dec->type_decl_section != NULL)
	{
		parse_type_decl_section(dec->type_decl_section);
	}
	int count;
	for (count = 0; count < ImplicitCount; count++)
	{
		strcpy(symbolTable[typeCount].id, implicitList[count].id);
		symbolTable[typeCount].t = implicitList[count].t;
		typeCount++;
	}
	if (dec->var_decl_section != NULL)
	{
		parse_var_decl_section(dec->var_decl_section);
	}
}

void parse_body(struct bodyNode* body)
{
	parse_stmt_list(body->stmt_list);
}

void parse_var_decl_section(struct var_decl_sectionNode* varDeclSection)
{
	if (varDeclSection->var_decl_list != NULL)
		parse_var_decl_list(varDeclSection->var_decl_list);
}

void parse_var_decl_list(struct var_decl_listNode* varDeclList)
{
	parse_var_decl(varDeclList->var_decl);
	if (varDeclList->var_decl_list != NULL)
		parse_var_decl_list(varDeclList->var_decl_list);
}

void parse_var_decl(struct var_declNode* varDecl)
{
	parse_id_list(varDecl->id_list);
	parse_type_name(varDecl->type_name);
	parseVar(varDecl->id_list, varDecl->type_name);
}

void parse_type_decl_section(struct type_decl_sectionNode* typeDeclSection)
{
	
	if (typeDeclSection->type_decl_list != NULL)
		parse_type_decl_list(typeDeclSection->type_decl_list);
}

void parse_type_decl_list(struct type_decl_listNode* typeDeclList)
{
	parse_type_decl(typeDeclList->type_decl);
	if (typeDeclList->type_decl_list != NULL)
		parse_type_decl_list(typeDeclList->type_decl_list);
}

void parse_type_decl(struct type_declNode* typeDecl)
{
	parse_id_list(typeDecl->id_list);	
	parse_type_name(typeDecl->type_name);
	parseType(typeDecl->id_list, typeDecl->type_name);
}

void parse_type_name(struct type_nameNode* typeName)
{
	/*if (typeName->type != ID)
		printf("%s ", reserved[typeName->type]);
	else
		printf("%s ", typeName->id);*/
}

void parse_id_list(struct id_listNode* idList)
{
	if (idList->id_list != NULL)
	{
		parse_id_list(idList->id_list);
	}
}

void parse_stmt_list(struct stmt_listNode* stmt_list)
{
	parse_stmt(stmt_list->stmt);
	if (stmt_list->stmt_list != NULL)
		parse_stmt_list(stmt_list->stmt_list);
}

void parse_assign_stmt(struct assign_stmtNode* assign_stmt)
{ 
	//testPrint();
	int HandL;
	HandL = locateSymbol_By_ID(assign_stmt -> id);

	if (HandL == -1){ 
		addVar(assign_stmt->id); 
	}
	parse_expression_prefix(assign_stmt->expr);

	if (HandL == -1)
	{
		MaxTypeInt++;
	}
	HandL = locateSymbol_By_ID(assign_stmt->id);
	//testPrint();
	
	if (prefix != symbolTable[HandL].t)
	{
		if (prefix < KEYWORDS && symbolTable[HandL].t < KEYWORDS)
		{
			printf("ERROR CODE 3\n\n");
			exit(0);
		}

		if (prefix >= KEYWORDS || symbolTable[HandL].t >= KEYWORDS) 
		{
			if (prefix > symbolTable[HandL].t){
				setSymbolType(prefix, symbolTable[HandL].t);
			}
			else { setSymbolType(symbolTable[HandL].t, prefix); }
		}	
	}	
	//testPrint();
}

void parse_stmt(struct stmtNode* stmt)
{
	if (stmt->stmtType == ASSIGN)
		parse_assign_stmt(stmt->assign_stmt);
	if (stmt->stmtType == WHILE)
		parse_while_stmt(stmt->while_stmt);
}

void parse_expression_prefix(struct exprNode* expr)
{
	//testPrint();
	prefix = -1;
	int l, r, location;
	 if (expr->tag == PRIMARY){
		if (expr->primary->tag == ID){
			location = locateSymbol_By_ID(expr->primary->id);
				if (location < 0)
			{
				location = addVar(expr->primary->id);
			}
			prefix = symbolTable[location].t;
		}
		if (expr->primary->tag == REALNUM){
			prefix = REAL;
		} 
		if (expr->primary->tag == NUM)
			{
			prefix = INT;
		}
	}
	if (expr->tag == EXPR){
		 parse_expression_prefix(expr->leftOperand);
		 l = prefix;
		 parse_expression_prefix(expr->rightOperand);
		 r = prefix;
		 prefix = l;
		 if (r != l)
		 {
			 if (l < KEYWORDS && r < KEYWORDS)
			 {
				 printf("ERROR CODE 3\n\n");
				 exit(0);
			 }
			 if (l >= KEYWORDS || r >= KEYWORDS)
			 {
				 if (l > r)
				 {
					 setSymbolType(l, r);
					 prefix = r;
				 }
				 else{
					 setSymbolType(r, l);
					 prefix = l;
				 }
			 }
		 }
	 }
}

void parse_condition(struct conditionNode* condition)
{

	if (condition->left_operand->tag== ID )
	{
		if (condition->right_operand == NULL){
			if (locateSymbol_By_ID(condition->left_operand->id) == -1)
			{
				int location = addVar(condition->left_operand->id);
				setSymbolType(symbolTable[location].t, BOOLEAN);
			}
			else if (symbolTable[locateSymbol_By_ID(condition->left_operand->id)].t != BOOLEAN)
			{
				printf("ERROR CODE 3\n\n");
				exit(0);
			}
		}
		else if (condition->right_operand-> tag == ID)
		{
			int right = locateSymbol_By_ID(condition->right_operand->id);
			int left = locateSymbol_By_ID(condition->left_operand->id);
			if (left == -1)
			{
				int location = addVar(condition->left_operand->id);
				if (right != -1){
					setSymbolType(symbolTable[location].t, symbolTable[right].t);
				}
			}
			
		}
		else if (condition->right_operand->tag == NUM)
		{
			if (locateSymbol_By_ID(condition->left_operand->id) == -1)
			{
				int location = addVar(condition->left_operand->id);
				setSymbolType(symbolTable[location].t, INT);
			}
			else if (locateSymbol_By_ID(condition->left_operand->id) > -1)
			{
				if (symbolTable[locateSymbol_By_ID(condition->left_operand->id)].t != INT)
				{
					printf("ERROR CODE 3\n\n");
					exit(0);
				}
			}
		}
		else if (condition->right_operand->tag == REALNUM)
		{
			if (locateSymbol_By_ID(condition->left_operand->id) == -1)
			{
				int location = addVar(condition->left_operand->id);
				setSymbolType(symbolTable[location].t, REAL);
			}
			else if (locateSymbol_By_ID(condition->left_operand->id) > -1)
			{
				if (symbolTable[locateSymbol_By_ID(condition->left_operand->id)].t != REAL)
				{
					printf("ERROR CODE 3\n\n");
					exit(0);
				}
			}
		}
	}

	if (condition->left_operand->tag == NUM || condition->left_operand->tag == REALNUM)
	{
		if (condition->right_operand->tag == ID)
		{
			int right = locateSymbol_By_ID(condition->right_operand->id);
			if (right == -1)
			{
				int location = addVar(condition->right_operand->id);
				if (condition->left_operand->tag == NUM)
				{
					setSymbolType(symbolTable[location].t, INT);
				}
				else if (condition->left_operand->tag == REALNUM)
				{
					setSymbolType(symbolTable[location].t, REAL);
				}
			}
		}
	}
	
	/*else{
		if (condition->right_operand->tag == ID)
		{
			if (condition->left_operand->tag == ID)
			{
			}
		}
	}*/
}


void parse_while_stmt(struct while_stmtNode* while_stmt)
{
		parse_condition(while_stmt->condition);
		parse_body(while_stmt->body);
}

/*----------------------PRINT METHOD/Error checking-------------------------------------------*/

void print()
{
	//testPrint();
	int check;
	int i; 
	int location;
	for (i = 0; i < MaxTypeInt; i++) // types are stored between 3 to .....
	{
		location = 0; 
		check = 0;
			if (i < KEYWORDS)// print out built in types 
			{
				location = locateSymbol_By_Type(i);
				if (location > -1)
				{
					printf("%s : ", reserved[i]);
					check = 1;
				}
			}
			else{							// print out user entered types 

				location = locateSymbol_By_Type(i);
				if (location > -1)
				{
					printf("%s : ", symbolTable[location].id);
					check = 1;
					location++;
				}
			}

			if (check == 1) // if checker is 1 then proceed to print out var for this the type above 
			{
				for (location; location < 80; location++)
				{
					if (symbolTable[location].t == i)
						if (symbolTable[location].t > INT - 1) /// print out variable corraspending to the type 
							printf("%s ", symbolTable[location].id);
				}
				printf("#\n");
			}
	}
	printf("\n");
}

/* -------------------- PARSING AND BUILDING PARSE TREE -------------------- */
struct primaryNode* primary()
{
	struct primaryNode* prime;
	ttype = getToken();
	prime = ALLOC(struct primaryNode);
	if (ttype == ID)
	{
		prime->id = (char*)malloc((tokenLength+1)*sizeof(char));
		prime->tag = ID;
		strcpy(prime->id, token);
	}
	else if (ttype == NUM)
	{
		prime->tag = NUM;
		prime->ival = atoi(token);
	}
	else if (ttype = REALNUM)
	{
		prime->tag = REALNUM;
		prime->fval = atof(token);
	}
	else
		syntax_error("primary. ID, NUM, or REALNUM, expected");
	return prime;
}

struct conditionNode* condition()
{
	struct conditionNode* con;
	con = ALLOC(struct conditionNode);
	ttype = getToken();
	if (ttype == ID || ttype == REALNUM || ttype == NUM)
	{
		ungetToken();
		int preToken = ttype;
		con->left_operand = primary();
		ttype = getToken();

		if (ttype == GREATER || ttype == GTEQ || ttype == LESS || ttype == LTEQ || ttype == NOTEQUAL)
		{
			con->relop = ttype;
			ttype = getToken();
			if (ttype == ID || ttype == REALNUM || ttype == NUM)
			{
				ungetToken();
				con->right_operand = primary();
			}
		}
		else
		{
			ungetToken();
			if (preToken != ID)
			{syntax_error("condition. ID expected");}
		}
	}
	else
	{
		syntax_error("condition. ID, NUM, or REALNUM expected");
	}

	return con;
}

struct while_stmtNode* while_stmt()
{
	struct while_stmtNode* whileStmt;
	ttype = getToken();
	whileStmt = ALLOC(struct while_stmtNode);
	
	if (ttype == WHILE)
	{
		whileStmt->condition = condition();
		ttype = getToken();
		if (ttype == LBRACE)
		{
			ungetToken();
			whileStmt->body = body();
		}
		else{
			syntax_error("while_stmt. LBRACE excpected");
		}
	}
	else{
		syntax_error("while_stmt. WHILE excpected");
	}
	return whileStmt;
}

struct exprNode* factor()
{
	struct exprNode* facto;

	ttype = getToken();
	if (ttype == LPAREN)
	{
		facto = expr();
		ttype = getToken();
		if (ttype == RPAREN)
			return facto;
		else
			syntax_error("factor. RPAREN expected");
	}
	else if (ttype == NUM)
	{
		facto = ALLOC(struct exprNode);
		facto->primary = ALLOC(struct primaryNode);
		facto->tag = PRIMARY;
		facto->operator = NOOP;
		facto->leftOperand = NULL;
		facto->rightOperand = NULL;
		facto->primary->tag = NUM;
		facto->primary->ival = atoi(token);
		return facto;
	}
	else if (ttype == REALNUM)
	{
		facto = ALLOC(struct exprNode);
		facto->primary = ALLOC(struct primaryNode);
		facto->tag = PRIMARY;
		facto->operator = NOOP;
		facto->leftOperand = NULL;
		facto->rightOperand = NULL;
		facto->primary->tag = REALNUM;
		facto->primary->fval = atof(token);
		return facto;
	}
	else if (ttype == ID)
	{
		facto = ALLOC(struct exprNode);
		facto->primary = ALLOC(struct primaryNode);
		facto->tag = PRIMARY;
		facto->operator = NOOP;
		facto->leftOperand = NULL;
		facto->rightOperand = NULL;
		facto->primary->tag = ID;
		facto->primary->id = strdup(token);
		return facto;
	}
	else
		syntax_error("factor. NUM, REALNUM, or ID, expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct exprNode* term()
{
	struct exprNode* ter;
	struct exprNode* f;

	ttype = getToken();
	if (ttype == ID || ttype == LPAREN || ttype == NUM || ttype == REALNUM)
	{
		ungetToken();
		f = factor();
		ttype = getToken();
		if (ttype == MULT || ttype == DIV)
		{
			ter = ALLOC(struct exprNode);
			ter->operator = ttype;
			ter->leftOperand = f;
			ter->rightOperand = term();
			ter->tag = EXPR;
			return ter;
		}
		else if (ttype == SEMICOLON || ttype == PLUS ||
			ttype == MINUS || ttype == RPAREN)
		{
			ungetToken();
			return f;
		}
		else
			syntax_error("term. MULT or DIV expected");
	}
	else
		syntax_error("term. ID, LPAREN, NUM, or REALNUM expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct exprNode* expr()
{
	struct exprNode* exp;
	struct exprNode* t;

	ttype = getToken();
	if (ttype == ID || ttype == LPAREN || ttype == NUM || ttype == REALNUM)
	{
		ungetToken();
		t = term();
		ttype = getToken();
		if (ttype == PLUS || ttype == MINUS)
		{
			exp = ALLOC(struct exprNode);
			exp->operator = ttype;
			exp->leftOperand = t;
			exp->rightOperand = expr();
			exp->tag = EXPR;
			return exp;
		}
		else if (ttype == SEMICOLON || ttype == MULT ||
			ttype == DIV || ttype == RPAREN)
		{
			ungetToken();
			return t;
		}
		else
			syntax_error("expr. PLUS, MINUS, or SEMICOLON expected");
	}
	else
		syntax_error("expr. ID, LPAREN, NUM, or REALNUM expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct assign_stmtNode* assign_stmt()
{
	struct assign_stmtNode* assignStmt;

	ttype = getToken();
	if (ttype == ID)
	{
		assignStmt = ALLOC(struct assign_stmtNode);
		assignStmt->id = strdup(token);
		ttype = getToken();
		if (ttype == EQUAL)
		{
			assignStmt->expr = expr();
			return assignStmt;
		}
		else
			syntax_error("assign_stmt. EQUAL expected");
	}
	else
		syntax_error("assign_stmt. ID expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct stmtNode* stmt()
{
	struct stmtNode* stm;

	stm = ALLOC(struct stmtNode);
	ttype = getToken();
	if (ttype == ID) // assign_stmt
	{
		ungetToken();
		stm->assign_stmt = assign_stmt();
		stm->stmtType = ASSIGN;
		ttype = getToken();
		if (ttype == SEMICOLON)
			return stm;
		else
			syntax_error("stmt. SEMICOLON expected");
	}
	else if (ttype == WHILE) // while_stmt
	{
		ungetToken();
		stm->while_stmt = while_stmt();
		stm->stmtType = WHILE;
		return stm;
	}
	else
		syntax_error("stmt. ID or WHILE expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct stmt_listNode* stmt_list()
{
	struct stmt_listNode* stmtList;

	ttype = getToken();
	if (ttype == ID || ttype == WHILE)
	{
		ungetToken();
		stmtList = ALLOC(struct stmt_listNode);
		stmtList->stmt = stmt();
		ttype = getToken();
		if (ttype == ID || ttype == WHILE)
		//sorry i added ttype == WHILE
	   // tooke me two days trying to figure 
		// why the parser wasn't working right
	   //so i had to modify your code sorry 
	   //DONT HATE ME....
		{
			ungetToken();
			stmtList->stmt_list = stmt_list();
			return stmtList;
		}
		else // If the next token is not in FOLLOW(stmt_list),
			// let the caller handle it.
		{
			ungetToken();
			stmtList->stmt_list = NULL;
			return stmtList;
		}
	}
	else
		syntax_error("stmt_list. ID or WHILE expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct bodyNode* body()
{
	struct bodyNode* bod;

	ttype = getToken();
	if (ttype == LBRACE)
	{
		bod = ALLOC(struct bodyNode);
		bod->stmt_list = stmt_list();
		ttype = getToken();
		if (ttype == RBRACE)
			return bod;
		else
			syntax_error("body. RBRACE expected");
	}
	else
		syntax_error("body. LBRACE expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct type_nameNode* type_name()
{
	struct type_nameNode* tName;

	tName = ALLOC(struct type_nameNode);
	ttype = getToken();
	if (ttype == ID || ttype == INT || ttype == REAL ||
		ttype == STRING || ttype == BOOLEAN)
	{
		tName->type = ttype;
		if (ttype == ID)
			tName->id = strdup(token);
		return tName;
	}
	else
		syntax_error("type_name. type name expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct id_listNode* id_list()
{
	struct id_listNode* idList;

	idList = ALLOC(struct id_listNode);
	ttype = getToken();
	if (ttype == ID)
	{
		idList->id = strdup(token);
		ttype = getToken();
		if (ttype == COMMA)
		{
			idList->id_list = id_list();
			return idList;
		}
		else if (ttype == COLON)
		{
			ungetToken();
			idList->id_list = NULL;
			return idList;
		}
		else
			syntax_error("id_list. COMMA or COLON expected");
	}
	else
		syntax_error("id_list. ID expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct type_declNode* type_decl()
{
	struct type_declNode* typeDecl;

	typeDecl = ALLOC(struct type_declNode);
	ttype = getToken();
	if (ttype == ID)
	{
		ungetToken();
		typeDecl->id_list = id_list();
		ttype = getToken();
		if (ttype == COLON)
		{
			typeDecl->type_name = type_name();
			ttype = getToken();
			if (ttype == SEMICOLON)
				return typeDecl;
			else
				syntax_error("type_decl. SEMICOLON expected");
		}
		else
			syntax_error("type_decl. COLON expected");
	}
	else
		syntax_error("type_decl. ID expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct var_declNode* var_decl()
{
	struct var_declNode* varDecl;

	varDecl = ALLOC(struct var_declNode);
	ttype = getToken();
	if (ttype == ID)
	{
		ungetToken();
		varDecl->id_list = id_list();
		ttype = getToken();
		if (ttype == COLON)
		{
			varDecl->type_name = type_name();
			ttype = getToken();
			if (ttype == SEMICOLON)
				return varDecl;
			else
				syntax_error("var_decl. SEMICOLON expected");
		}
		else
			syntax_error("var_decl. COLON expected");
	}
	else
		syntax_error("var_decl. ID expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct var_decl_listNode* var_decl_list()
{
	struct var_decl_listNode* varDeclList;

	varDeclList = ALLOC(struct var_decl_listNode);
	ttype = getToken();
	if (ttype == ID)
	{
		ungetToken();
		varDeclList->var_decl = var_decl();
		ttype = getToken();
		if (ttype == ID)
		{
			ungetToken();
			varDeclList->var_decl_list = var_decl_list();
			return varDeclList;
		}
		else
		{
			ungetToken();
			return varDeclList;
		}
	}
	else
		syntax_error("var_decl_list. ID expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct type_decl_listNode* type_decl_list()
{
	struct type_decl_listNode* typeDeclList;

	typeDeclList = ALLOC(struct type_decl_listNode);
	ttype = getToken();
	if (ttype == ID)
	{
		ungetToken();
		typeDeclList->type_decl = type_decl();
		ttype = getToken();
		if (ttype == ID)
		{
			ungetToken();
			typeDeclList->type_decl_list = type_decl_list();
			return typeDeclList;
		}
		else
		{
			ungetToken();
			return typeDeclList;
		}
	}
	else
		syntax_error("type_decl_list. ID expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct var_decl_sectionNode* var_decl_section()
{
	struct var_decl_sectionNode *varDeclSection;

	varDeclSection = ALLOC(struct var_decl_sectionNode);
	ttype = getToken();
	if (ttype == VAR)
	{
		// no need to ungetToken()
		varDeclSection->var_decl_list = var_decl_list();
		return varDeclSection;
	}
	else
		syntax_error("var_decl_section. VAR expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct type_decl_sectionNode* type_decl_section()
{
	struct type_decl_sectionNode *typeDeclSection;

	typeDeclSection = ALLOC(struct type_decl_sectionNode);
	ttype = getToken();
	if (ttype == TYPE)
	{
		typeDeclSection->type_decl_list = type_decl_list();
		return typeDeclSection;
	}
	else
		syntax_error("type_decl_section. TYPE expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct declNode* decl()
{
	struct declNode* dec;

	dec = ALLOC(struct declNode);
	ttype = getToken();
	if (ttype == TYPE)
	{
		ungetToken();
		dec->type_decl_section = type_decl_section();
		ttype = getToken();
		if (ttype == VAR)
		{
			// type_decl_list is epsilon
			// or type_decl already parsed and the
			// next token is checked
			ungetToken();
			dec->var_decl_section = var_decl_section();
		}
		else
		{
			ungetToken();
			dec->var_decl_section = NULL;
		}
		return dec;
	}
	else
	{
		dec->type_decl_section = NULL;
		if (ttype == VAR)
		{
			// type_decl_list is epsilon
			// or type_decl already parsed and the
			// next token is checked
			ungetToken();
			dec->var_decl_section = var_decl_section();
			return dec;
		}
		else
		{
			if (ttype == LBRACE)
			{
				ungetToken();
				dec->var_decl_section = NULL;
				return dec;
			}
			else
				syntax_error("decl. LBRACE expected");
		}
	}
	return NULL; // control never reaches here, this is just for the sake of GCC
}

struct programNode* program()
{
	struct programNode* prog;

	prog = ALLOC(struct programNode);
	ttype = getToken();
	if (ttype == TYPE || ttype == VAR || ttype == LBRACE)
	{
		ungetToken();
		prog->decl = decl();
		prog->body = body();
		return prog;
	}
	else
		syntax_error("program. TYPE or VAR or LBRACE expected");
	return NULL; // control never reaches here, this is just for the sake of GCC
}

int main()
{
	struct programNode* parseTree;
	parseTree = program();

	// parse_parse_tree(parseTree);

	// ***all print methods are changed to parse_ instead 
	// print_ since i have commented out all the 
	// printf with in them and deleted them 
	// the print methods within them were
	// used for testing purposes

	//calls the only declaration part of parsing
	parse_decl(parseTree->decl); 

	if (error0() == 1){
		printf("ERROR CODE 0\n\n");
		//testPrint();
		return 0;
	}
	if (error1() == 1){
		printf("ERROR CODE 1\n\n");
		//testPrint();
		return 0;
	}
	if (error2() == 1){
		printf("ERROR CODE 2\n\n");
		//testPrint();
		return 0; 
	}
	if (error4() == 1){
		printf("ERROR CODE 4\n\n");
		//testPrint();
		return 0;
	}
	
	parse_body(parseTree->body);

	//testPrint(); //<- is used for testing purposes only 

	print(); // prints out everything
	return 0;
}
