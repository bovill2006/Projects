/*----------------------------------------------------------------------------
Note: the code in this file is not to be shared with anyone or posted online.
(c) Rida Bazzi, 2014
----------------------------------------------------------------------------*/

/* -------------------- PARSE TREE TYPES -------------------- */

#define PRIMARY 100
#define EXPR    101
#define NOOP    102
#define ASSIGN  103

struct programNode
{
	struct declNode* decl;
	struct bodyNode* body;
};

struct declNode
{
	// A NULL field means that the section is empty
	struct type_decl_sectionNode* type_decl_section;
	struct var_decl_sectionNode* var_decl_section;
};

struct type_decl_sectionNode
{
	struct type_decl_listNode* type_decl_list;
};

struct var_decl_sectionNode
{
	struct var_decl_listNode* var_decl_list;
};

struct type_decl_listNode
{
	struct type_declNode * type_decl;
	struct type_decl_listNode* type_decl_list;
};

struct var_decl_listNode
{
	struct var_declNode * var_decl;
	struct var_decl_listNode* var_decl_list;
};

struct type_declNode
{
	struct id_listNode* id_list;
	struct type_nameNode* type_name;
};

struct var_declNode
{
	struct id_listNode* id_list;
	struct type_nameNode* type_name;
};

struct type_nameNode
{
	int type; // INT, REAL, STRING, BOOLEAN, ID
	char* id; // actual string when type is ID
};

struct id_listNode
{
	char * id;
	struct id_listNode* id_list;
};

struct bodyNode
{
	struct stmt_listNode* stmt_list;
};

struct stmt_listNode
{
	struct stmtNode* stmt;
	struct stmt_listNode * stmt_list;
};

struct stmtNode
{
	int stmtType; // WHILE or ASSIGN

	union
	{
		struct while_stmtNode* while_stmt;
		struct assign_stmtNode* assign_stmt;
	};
};

struct conditionNode
{
	int relop;
	struct primaryNode* left_operand;
	struct primaryNode* right_operand;
};

struct while_stmtNode
{
	struct conditionNode* condition;
	struct bodyNode* body;
};

struct assign_stmtNode
{
	char* id;
	struct exprNode* expr;
};

struct exprNode
{
	int operator; // PLUS , MINUS, MULT, ...
	// or NOOP
	int tag; // PRIMARY or EXPR
	struct primaryNode* primary;
	struct exprNode * leftOperand;
	struct exprNode * rightOperand;
};

struct primaryNode
{
	int tag; // NUM, REALNUM or ID
	int ival;
	float fval;
	char *id;
};

/* -------------------- PARSE TREE FUNCTIONS -------------------- */

#define ALLOC(t) (t*) calloc(1, sizeof(t))

void parse_decl(struct declNode* dec);
void parse_body(struct bodyNode* body);

void parse_type_decl_section(struct type_decl_sectionNode* typeDeclSection);
void parse_type_decl_list(struct type_decl_listNode* typeDeclList);
void parse_type_decl(struct type_declNode* typeDecl);

void parse_var_decl_section(struct var_decl_sectionNode* varDeclSection);
void parse_var_decl_list(struct var_decl_listNode* varDeclList);
void parse_var_decl(struct var_declNode* varDecl);
void parse_type_name(struct type_nameNode* typeName);
void parse_id_list(struct id_listNode* idList);
void parse_id_list(struct id_listNode* idList);

void parse_stmt_list(struct stmt_listNode* stmt_list);
void parse_stmt(struct stmtNode* stmt);
void parse_assign_stmt(struct assign_stmtNode* assign_stmt);
void parse_expression_prefix(struct exprNode* expr);
void parse_while_stmt(struct while_stmtNode* while_stmt);
void parse_condition(struct conditionNode* condition);

/* -------------------- PARSING FUNCTIONS -------------------- */

struct programNode*           program();
struct declNode*              decl();
struct type_decl_sectionNode* type_decl_section();
struct var_decl_sectionNode*  var_decl_section();
struct type_decl_listNode*    type_decl_list();
struct var_decl_listNode*     var_decl_list();
struct var_declNode*          var_decl();
struct type_declNode*         type_decl();
struct id_listNode*           id_list();
struct type_nameNode*         type_name();
struct bodyNode*              body();
struct stmt_listNode*         stmt_list();
struct stmtNode*              stmt();
struct while_stmtNode*        while_stmt();
struct assign_stmtNode*       assign_stmt();
struct exprNode*              expr();
struct exprNode*              term();
struct exprNode*              factor();
struct conditionNode*         condition();
struct primaryNode*           primary();
