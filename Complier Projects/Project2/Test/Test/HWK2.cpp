#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
//#define TEST
#ifdef TEST
#	define  D(format, arg...)   printf("[%s] " format, __func__, ##arg)
#else
#	define  D(format, arg...)   ((void)0)
#endif
//----------------------------- token types ------------------------------
#define ID	0
#define HASH 		1
#define DOUBLEHASH 	2
#define ARROW 		3
#define ERROR		4

#define FIRST  0
#define FOLLOW 1
#define nT  0
#define T 1

#define ERROR_CODE_0 0x001
#define ERROR_CODE_1 0x002
#define ERROR_CODE_2 0x004
#define ERROR_CODE_3 0x008
#define ERROR_CODE_4 0x010

// Global Variables associated with the next input token
// This implementation does not allow tokens that are more
// than 100 characters long
#define MAX_TOKEN_LENGTH 100
#define MAX_TOKEN_NUM 40
#define MAX_RULE_LINE 200
#define MAX_RULE_ELEMENT 80
char nT_T_name[2][MAX_TOKEN_NUM][MAX_TOKEN_LENGTH];//0 is nT, 1 is T
int map[2][MAX_TOKEN_NUM][MAX_TOKEN_NUM + 1];//0 is first, 1 is follow
int temp_map[MAX_TOKEN_NUM][MAX_TOKEN_NUM + 1];

int nT_token_num = 0;
int T_token_num = 0;
int rule_num = 0;
int rule_left[MAX_RULE_LINE];
int rule_right[MAX_RULE_LINE][MAX_RULE_ELEMENT];

char token[MAX_TOKEN_LENGTH]; // token string
int ret;


void readNextLine()
{
	if (!feof(stdin)){
		memset(token, 0, MAX_TOKEN_LENGTH);
		scanf("%s", token);
		//printf("'%s'\n", token);
	}
}

int is_id()
{
	int ttype = ID;
	int i;
	if (isalpha(token[0])){
		for (i = 0; i<MAX_TOKEN_LENGTH; i++){
			if (token[i] == 0)
				break;
			if (isalnum(token[i]) == 0)
				ttype = ERROR;
		}
	}
	else{
		ttype = ERROR;
	}
	return ttype;
}
int former_ttype = 0;
int ungettoken_flag = 0;
void ungetToken()
{
	ungettoken_flag = 1;
}
int getToken()
{
	if (ungettoken_flag == 0){
		int ttype = 0;
		readNextLine();
		if (strcmp(token, "#") == 0)
			ttype = HASH;//1
		else if (strcmp(token, "##") == 0)
			ttype = DOUBLEHASH;//2
		else if (strcmp(token, "->") == 0)
			ttype = ARROW;//3
		else{
			ttype = is_id();
		}
		former_ttype = ttype;
	}
	else{
		ungettoken_flag = 0;
	}
#if 0
	if (former_ttype == 0)D("ID '%s'\n", token);
	else if (former_ttype == 1)D("HASH\n");
	else if (former_ttype == 2)D("DOUBLEHASH\n");
	else if (former_ttype == 3)D("ARROW\n");
	else D("'%d'\n", former_ttype);
#endif
	return former_ttype;
}
void sort()
{
	D("\nNEW T order:");
	int i, j, k;
	char temp[MAX_TOKEN_LENGTH];
	for (i = 0; i<T_token_num; i++){
		for (j = 0; j<T_token_num - i - 1; j++){
			k = 0;
			while (nT_T_name[T][j][k] != 0){
				if ((nT_T_name[T][j][k]) >(nT_T_name[T][j + 1][k])){
					strcpy(temp, nT_T_name[1][j]);
					strcpy(nT_T_name[T][j], nT_T_name[T][j + 1]);
					strcpy(nT_T_name[T][j + 1], temp);
					break;
				}
				else if ((nT_T_name[T][j][k]) < (nT_T_name[T][j + 1][k]))
					break;
				else
					k++;
			}
		}
	}
	for (i = 0; i<T_token_num; i++)D("%s ", nT_T_name[T][i]);
	D("\n");
}
int get_nT_indx()
{
	int i;
	for (i = 0; i<nT_token_num; i++){
		if (strcmp(nT_T_name[nT][i], token) == 0){
			//D("Found %s\n",nT_T_name[nT][i]);
			return i;
		}
	}
	//D("not Found nT\n");
	return -1;
}
int get_T_indx()
{
	int i;
	for (i = 0; i<T_token_num; i++){
		if (strcmp(nT_T_name[T][i], token) == 0){
			//D("Found %s\n",nT_T_name[T][i]);
			return i;
		}
	}
	//D("not Found T\n");
	return T_token_num;//ERROR_CODE_3
}

void parse_rule()
{
	//D("ret=%d\n",ret);
	int ttype;
	int break_loop = 0;
	int nT_indx, element_indx;
	ttype = getToken();
	if (ttype == ID){
		nT_indx = get_nT_indx();
		if (nT_indx<0){
			nT_indx = get_T_indx() + nT_token_num + 1;//ERROR_CODE_3
		}
		ttype = getToken();
		if (ttype == ARROW){
			rule_left[rule_num] = nT_indx;
			int i = 0;
			do{
				ttype = getToken();
				if (ttype == ID){
					element_indx = get_nT_indx();
					if (element_indx < 0){//not a nT element
						element_indx = get_T_indx();
						if (element_indx >= 0){//Found T element
							rule_right[rule_num][i] = element_indx + nT_token_num + 1;
							//nT_T_in_rule[T][element_indx]=1;//For ERROR_CODE_4
						}/*else{
						 ret |= ERROR_CODE_2;
						 }*/
					}
					else{//Found nT element
						rule_right[rule_num][i] = element_indx;
					}
					i++;
				}
				else if (ttype == HASH){
					if (i == 0)
						rule_right[rule_num][i] = nT_token_num;
					break_loop = 1;
				}
				else{
					ret |= ERROR_CODE_0;
					break_loop = 1;
				}
			} while (!break_loop);
		}
		else
			ret |= ERROR_CODE_0;
	}
	else{
		ret |= ERROR_CODE_0;
	}

}
void parse_T()
{
	D("\n");
	int break_loop = 0;
	do{
		int ttype = getToken();
		if (ttype == ID){
			strcpy(nT_T_name[T][T_token_num], token);
			T_token_num++;
		}
		else if (ttype == HASH){
			break_loop = 1;
		}
		else{
			ret |= ERROR_CODE_0;
			break_loop = 1;
		}
	} while (!break_loop);
	sort();
}
void parse_nT()
{
	D("\n");
	int break_loop = 0;
	while (!break_loop){
		int ttype = getToken();
		if (ttype == ID){
			strcpy(nT_T_name[nT][nT_token_num], token);
			nT_token_num++;
		}
		else if (ttype == HASH){
			break_loop = 1;
		}
		else{
			ret |= ERROR_CODE_0;
			break_loop = 1;
		}
	}
}
void parse_grammer()
{
	D("\n");
	int break_loop = 0;
	int ttype = getToken();
	if (ttype == ID){
		ungetToken();
		parse_nT();
		ttype = getToken();
		if (ttype == ID){
			ungetToken();
			parse_T();
			do{
				ttype = getToken();
				if (ttype == ID){
					ungetToken();
					parse_rule();
					rule_num++;
				}
				else if (ttype == DOUBLEHASH){
					if (rule_num == 0)
						ret |= ERROR_CODE_0;
					break_loop = 1;
				}
				else{
					ret |= ERROR_CODE_0;
					break_loop = 1;
				}
			} while (!break_loop);
		}
	}
	else
		ret |= ERROR_CODE_0;
}

void print_mapping()
{
#ifdef TEST
	int i, j;
	D("\n");
	printf("FOLLOW map\n");
	for (i = 0; i<nT_token_num; i++){
		printf("%s: ", nT_T_name[nT][i]);
		for (j = 0; j <= T_token_num; j++){
			printf("%d", map[FOLLOW][i][j]);
			if (j % 10 == 9)
				printf(" ");
		}
		printf("\n");
	}
	printf("FIRST map\n");
	for (i = 0; i<nT_token_num; i++){
		printf("%s: ", nT_T_name[nT][i]);
		for (j = 0; j <= T_token_num; j++){
			printf("%d", map[FIRST][i][j]);
			if (j % 10 == 9)
				printf(" ");
		}
		printf("\n");
	}
#endif
}
void print_result(int indx)
{
	D("\n");
	int i, j;
	for (i = 0; i<nT_token_num; i++){

		//print result
		int is_first_element = 1;
		if (indx == FIRST){
			printf("FIRST(%s) = {", nT_T_name[nT][i]);
			if (map[FIRST][i][0]){
				is_first_element = 0;
				printf(" #");
			}
			for (j = 1; j <= T_token_num; j++){
				if (map[FIRST][i][j]){
					if (is_first_element){
						printf(" %s", nT_T_name[T][j - 1]);
						is_first_element = 0;
					}
					else
						printf(", %s", nT_T_name[T][j - 1]);
				}
			}

		}
		else if (indx == FOLLOW){
			printf("FOLLOW(%s) = {", nT_T_name[nT][i]);
			if (map[FOLLOW][i][0]){
				is_first_element = 0;
				printf(" $");
			}
			for (j = 1; j <= T_token_num; j++){
				if (map[FOLLOW][i][j]){
					if (is_first_element){
						printf(" %s", nT_T_name[T][j - 1]);
						is_first_element = 0;
					}
					else
						printf(", %s", nT_T_name[T][j - 1]);
				}
			}

		}
		printf(" }\n");
	}
}
int is_element(int element)
{
	if (element<0)
		return -1;//EOF
	else if (element<nT_token_num)
		return nT;//nT
	return T;//T
}
void copy_map(int indx)
{
	int i, j;
	for (i = 0; i<MAX_TOKEN_NUM; i++)
		for (j = 0; j <= MAX_TOKEN_NUM; j++){
		temp_map[i][j] = map[indx][i][j];
		}
}
int check_map(int indx)
{
	int i, j, ret = 1;
	for (i = 0; i<MAX_TOKEN_NUM; i++)
		for (j = 0; j <= MAX_TOKEN_NUM; j++){
		if (temp_map[i][j] != map[indx][i][j])ret = 0;
		}
	return ret;//1 same 0 not same
}
void handle_follow(){
	int i, j, k;

	map[FOLLOW][0][0] = 1;//Rule I //Set startpoint follow element to $

	memset(temp_map, 0, sizeof(temp_map));
	while (!check_map(FOLLOW)){
		copy_map(FOLLOW);
		for (i = 0; i<rule_num; i++){
			int keep_this_rule = 1;
			for (k = 0; rule_right[i][k] >= 0 && keep_this_rule; k++){
				D("cur%d next %d   %d\n", rule_right[i][k], rule_right[i][k + 1], is_element(rule_right[i][k]));
				if (is_element(rule_right[i][k]) == nT){//get T element
					if (is_element(rule_right[i][k + 1]) == T){//RULE IV
						map[FOLLOW][(rule_right[i][k])][(rule_right[i][k + 1] - nT_token_num)] = 1;
						int m = 0;
						for (m = k; is_element(rule_right[i][m]) == nT&&m>0; m--){
							if (is_element(rule_right[i][m - 1]) == nT && map[FIRST][(rule_right[i][m])][0] == 1){
								map[FOLLOW][(rule_right[i][m - 1])][j] = 1;
							}
							else
								break;
						}
					}
					else if (is_element(rule_right[i][k + 1]) == nT){//RULE IV & RULE V
						for (j = 1; j <= T_token_num; j++){
							map[FOLLOW][(rule_right[i][k])][j] |= map[FIRST][(rule_right[i][k + 1])][j];
						}
						int m;
						for (m = k; is_element(rule_right[i][m]) == nT; m++){
							if (is_element(rule_right[i][m]) == nT && map[FIRST][(rule_right[i][m])][0]){
								if (is_element(rule_right[i][m + 1]) == nT){
									for (j = 1; j <= T_token_num; j++){
										map[FOLLOW][(rule_right[i][k])][j] |= map[FIRST][(rule_right[i][m + 1])][j];
									}
								}
								else if (is_element(rule_right[i][m + 1]) == T)
									map[FOLLOW][(rule_right[i][k])][(rule_right[i][m + 1] - nT_token_num)] = 1;
							}
						}
					}
					else{
						for (j = 0; j <= T_token_num; j++){//RULE II
							map[FOLLOW][(rule_right[i][k])][j] |= map[FOLLOW][rule_left[i]][j];
						}
						//RULE III
						int m = 0;
						for (m = k; m>0; m--){
							if (map[FIRST][(rule_right[i][m])][0] == 1){
								for (j = 0; j <= T_token_num; j++){
									map[FOLLOW][(rule_right[i][m - 1])][j] |= map[FOLLOW][(rule_left[i])][j];
								}
							}
							else
								break;
						}
					}
				}
			}
		}
	}
}

void handle_first()
{
	int i, j, k;
	//Parse T.
	for (i = 0; i<rule_num; i++){
		if (is_element(rule_right[i][0]) == T){//T
			map[FIRST][rule_left[i]][rule_right[i][0] - nT_token_num] = 1;
		}
	}

	//Parse NT
	while (!check_map(FIRST)){//Do Recurseve
		copy_map(FIRST);
		for (i = 0; i<rule_num; i++){
			int keep_this_rule = 1;
			for (k = 0; rule_right[i][k] >= 0 && keep_this_rule; k++){
				if (is_element(rule_right[i][k]) == nT){//nT
					for (j = 1; j <= T_token_num; j++){
						map[FIRST][(rule_left[i])][j] |= map[FIRST][(rule_right[i][k])][j];
					}
					if ((map[FIRST][rule_right[i][k]][0] == 1) && (rule_right[i][k] == rule_left[i])){
						keep_this_rule = 1;
					}
					else if (map[FIRST][rule_right[i][k]][0] == 0){
						keep_this_rule = 0;
					}
					else{//EOF of this rule and all element is epsilon
						if (rule_right[i][k + 1] == -1){
							map[FIRST][rule_left[i]][0] = 1;
						}
					}
				}
				else if (is_element(rule_right[i][k]) == T){//meet T to stop
					map[FIRST][(rule_left[i])][(rule_right[i][k] - nT_token_num)] = 1;
					keep_this_rule = 0;
				}
			}
		}
	}

}
int main()
{
	memset(rule_right, -1, sizeof(rule_right));
	memset(rule_left, -1, sizeof(rule_left));
	parse_grammer();
#ifdef TEST
	int m, n;
	for (m = 0; m<MAX_RULE_LINE; m++){
		if (rule_left[m] >= 0){
			printf("%d ->", rule_left[m]);
			for (n = 0; n<MAX_RULE_ELEMENT; n++){
				if (rule_right[m][n] >= 0)
					printf(" %d", rule_right[m][n]);
			}
			printf("\n");
		}
	}
#endif
	int i, j, k, found_token;
	for (i = 0, found_token = 0; i<nT_token_num; i++, found_token = 0){
		for (j = 0; j<rule_num; j++){
			if (rule_left[j] == i)
				found_token |= 1;
		}
		if (found_token != 1)
			ret |= ERROR_CODE_1;
	}

	for (j = 0, found_token = 0; j<rule_num; j++){
		for (i = 0; i <= nT_token_num + T_token_num; i++)
			if (rule_left[j] == nT_token_num + T_token_num + 1)
				found_token = 1;
		for (k = 0; rule_right[j][k] >= 0; k++){
			if (rule_right[j][k] == nT_token_num + T_token_num + 1)
				found_token = 1;
		}
		if (found_token == 1)
			ret |= ERROR_CODE_2;
	}

	for (i = nT_token_num + 1, found_token = 0; i <= nT_token_num + T_token_num; i++){
		for (j = 0; j<rule_num; j++){
			if (rule_left[j] == i)
				found_token = 1;
		}
		if (found_token == 1)
			ret |= ERROR_CODE_3;
	}

	for (i = nT_token_num + 1, found_token = 0; i <= T_token_num + nT_token_num; i++, found_token = 0){
		for (j = 0; j<rule_num; j++){
			for (k = 0; rule_right[j][k] >= 0; k++){
				if (rule_right[j][k] == i)
					found_token = 1;
			}
		}
		if (found_token != 1)
			ret |= ERROR_CODE_4;
	}

	//print error code
	if (ret & ERROR_CODE_0){
		printf("ERROR CODE 0\n");
	}
	else{
		if (ret & ERROR_CODE_1){
			printf("ERROR CODE 1\n");
		}
		if (ret & ERROR_CODE_2){
			printf("ERROR CODE 2\n");
		}
		if (ret & ERROR_CODE_3){
			printf("ERROR CODE 3\n");
		}
		if (ret & ERROR_CODE_4){
			printf("ERROR CODE 4\n");
		}
	}
	if (ret)
		return 0;
#if 1
	handle_first();
	handle_follow();
	print_result(FIRST);
	print_result(FOLLOW);
#endif
	return 0;

}

