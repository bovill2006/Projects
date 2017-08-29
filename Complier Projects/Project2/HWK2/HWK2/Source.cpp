#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctype.h>

using namespace std;

#define ARROW 0
#define DOUBLEHASH 1 
#define HASH 2
#define ID 3
#define Term 0
#define NTerm 1


char inputToken[200];
int activeToken = 0; // its' equall to 1 or 0 used in for token varif

char sortedList[50][50][200];
char storeNTer[50][200]; // stores all the non terminals 
char storeTer[50][200]; // stores all the terminals 
int firstTable[50][51];// first binary table 
int followTable[50][51];//follow binary table 
int temp[50][51];
int stringTest[50];
bool gen_a_string[50]; // 0 is false 1 is true 
int ttype = 0;
int ruleCount = 0;
int terminalAmount = 0; 
int nonTerminalAmount = 0;
int leftRule[300]; 
int rigthRule[300][100];

void sortList(int choice) // 0 for First 1 for Follow 
{
	int i, j, k = 0, l;
	//copy into new array 
	char temp [200];
	if (choice ==0){
		for (i = 0; i < nonTerminalAmount; i++){
			for (j = 0; j < terminalAmount; j++){
				if (firstTable[i][j] == 1){
					strcpy(sortedList[i][k], storeTer[j]);
					k++;
				}
			}
			k = 0;
		}
	}
	if (choice == 1){
		for (i = 0; i < nonTerminalAmount; i++){
			for (j = 0; j < terminalAmount; j++){
				if (followTable[i][j] == 1){
					strcpy(sortedList[i][k], storeTer[j]);
					k++;
				}
			}
			k = 0;
		}
	}
	//sort the new array 
	for (l = 0; l < 10 ; l++){
		for (i = 0; i < nonTerminalAmount; i++){
			for (j = 0; j < terminalAmount; j++){
				if (j > 0){
					if (strcmp(sortedList[i][j], sortedList[i][j - 1]) < 0 && sortedList[i][j][0] != '\0'){
						strcpy(temp, sortedList[i][j]);
						strcpy(sortedList[i][j], sortedList[i][j - 1]);
						strcpy(sortedList[i][j - 1], temp);
					}
				}
			}
		}
	}
}
void ifID()
{ 
	int i;
		for (i = 0; i < 200; i++)
		{
			if (inputToken[i] == 0)
				break;
		}
}
int getToken()
{
	int type = 0;

	if (activeToken == 0)
	{
		if (!feof(stdin)){ // read line 
			memset(inputToken, 0, 200);
			scanf("%s", inputToken);
		}
		if (strcmp(inputToken, "->") == 0)
			type = ARROW;
		else if (strcmp(inputToken, "##") == 0)
				type = DOUBLEHASH;
			else if (strcmp(inputToken, "#") == 0)
					type = HASH;
				else
				{
					ifID();
					type = ID;
				}
		ttype = type; 
	}
	else
		activeToken = 0; 

	return ttype; 
}
void ungetToken()
{
	activeToken = 1;
}
int getNT()
{
	int i; 
	for (i = 0; i < nonTerminalAmount; i++)
	{
		if (strcmp(storeNTer[i], inputToken)==0)
		{
			return i;
		}
	}
	return nonTerminalAmount; 
}
int getT()
{
	int i;
	for (i = 0; i < terminalAmount; i++)
	{
		if (strcmp(storeTer[i], inputToken) == 0)
		{
			return i;
		}
	}
	return -1;
}
void storeRule()
{
	int i = 0;
	int j = 0;
	int nonTerminalIndex, index;
	int type = getToken();

	nonTerminalIndex = getNT();
	type = getToken();
	if (type == ARROW)
	{
		leftRule[ruleCount] = nonTerminalIndex;

		while (i == 0)
		{
			type = getToken();
			if (type == ID)
			{
				index = getT();
				if (index < 0){
					index = getNT();
					rigthRule[ruleCount][j] = index + terminalAmount + 1;
					// total of terminal = empty string 
				}
				else
				{
					rigthRule[ruleCount][j] = index;
				}
				j++;
			}
			if (type == HASH)
			{
				if (j == 0)// if there is no ID on right side then empty string
					rigthRule[ruleCount][j] = terminalAmount;
				i = 1;
			}
		}
	}
}
void nonTerminal()
{
	int i = 0; // loops until the all the nonterms are stored 
	int type; 
	while (i == 0)
	{
		type = getToken();
		if (type == ID)
		{
			strcpy(storeNTer[nonTerminalAmount], inputToken);
			nonTerminalAmount++;
		}
		else if (type == HASH )
			i = 1;
	}
}
void terminal()
{
	int i = 0;
	int type; 
	
	do{
		type = getToken();
		if (type == ID)
		{
			strcpy(storeTer[terminalAmount], inputToken);
			terminalAmount++;
		}
		if (type == HASH)
			i = 1;
	} while (i == 0);
}
void parse()
{
	int i = 0;
	int type = getToken();
	if (type == ID){ // store terminals
		ungetToken();
		terminal();
		type = getToken();
	}
	if (type == ID){//store non terms 
		ungetToken();
		nonTerminal();
	}
	while (i == 0) // store rules 
	{
		type = getToken();
		if (type == ID)
		{
			ungetToken();
			storeRule();
			ruleCount++;
		}
		if (type == DOUBLEHASH)
		{
				i = 1;//stops the loop 
		}
	}
}
// For testing purposes 
void printMap()
{
	int i, j, n, m; 
	printf("First[] Map \n");
	for (i = 0; i < nonTerminalAmount; i++)
	{
		printf("%s: ", storeNTer[i]);
		for (j = 0; j <= terminalAmount; j++)
		{
			printf("%d", firstTable[i][j]);
		}
		printf("\n");
	 }
	printf("\n");

	printf("Follow[] Map \n");
	for (i = 0; i < nonTerminalAmount; i++)
	{
		printf("%s: ", storeNTer[i]);
		for (j = 0; j <= terminalAmount; j++)
		{
			printf("%d", followTable[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	for (m = 0; m<300; m++){
		if (leftRule[m] >= 0){
			printf("%d ->", leftRule[m]);
			for (n = 0; n<100; n++){
				if (rigthRule[m][n] >= 0)
					printf(" %d", rigthRule[m][n]);
			}
			printf("\n");
		}
	}
}// for testing purposes
//only works when sortList is called before 
void printFirst()
{
	int l, k = 0;
	for (l = 0; l < nonTerminalAmount; l++)
	{
		int firstEl = 1;
		printf("FIRST(%s) = {", storeNTer[l]);

		if (firstTable[l][terminalAmount]){
			firstEl = 0;
			printf(" #");
		}
		while (sortedList[l][k][0] != '\0'){
			if (firstEl){
				printf(" %s", sortedList[l][k]);
				firstEl = 0;
			}
			else{
				printf(", %s", sortedList[l][k]);
			}
			k++;
		}
		printf(" }\n");
		k = 0;
	}
}
// only works when sortList is called before 
void printFollow()
{
	int i,  k=0;

	for (i = 0; i < nonTerminalAmount; i++)
	{
		int firstEl = 1;
		printf("FOLLOW(%s) = {", storeNTer[i]);
		if (followTable[i][terminalAmount]){
			firstEl = 0;
			printf(" $");
		}
		while (sortedList[i][k][0] != '\0'){
			if (firstEl){
				printf(" %s", sortedList[i][k]);
				firstEl = 0;
				k++;
			}
			else{
				printf(", %s", sortedList[i][k]);
				k++;
			}	
		}
		printf(" }\n");
		k = 0;
	}
}//
// store location of all first sets according a binary table 
void findFirst()
{
	//stores into binary array if the first is a terimnal 
	//except for epsilon then use that terinmal to determine two more layers of FIRST 
	int i, j, k;
	for (i = 0; i < ruleCount; i++)
	{
		if (rigthRule[i][0] < terminalAmount)
		{
			firstTable[leftRule[i]][rigthRule[i][0]] = 1;
			for (j = 0; j < ruleCount; j++)
			{
				if (leftRule[i] == rigthRule[j][0] - terminalAmount-1)
				{
					firstTable[leftRule[j]][rigthRule[i][0]] = 1;
					
					for (k = 0; k < ruleCount; k++)
					{
						if (leftRule[j]  == rigthRule[k][0]- terminalAmount -1)
						{
							firstTable[leftRule[k]][rigthRule[i][0]] = 1;
						}
					}
				}
			}
		}
	}
	//printf("\nTerm: %d  NTerm: %d \n", terminalAmount, nonTerminalAmount);
	//printMap();
	//printf("\n");

	//used to find epsilon and use epsilon to determine other layered FIRST
	for (i = 0; i < ruleCount; i++)
	{
		if (rigthRule[i][0] == terminalAmount)
		{
			firstTable[leftRule[i]][terminalAmount] = 1;
			for (j = 0; j < ruleCount; j++)
			{
				if (rigthRule[j][0] == (leftRule[i]+nonTerminalAmount))
				{
					if (rigthRule[j][1] < terminalAmount)
					{
						firstTable[leftRule[j]][rigthRule[j][1]] = 1;
						
					}
				}
			}
		}
	}
	//printMap();	
}
// store location of all Follow sets according to binary table 
void findFollow()
{
	followTable[0][terminalAmount] = 1; // the starting always have $ as a follow
	int i, j, k,l;

	// check for nonterminal's first set and terminals after a nonterminal if true add to follow  
	for (i = 0; i < ruleCount; i++){
		j = 0;
		do{
			if (rigthRule[i][j] > terminalAmount){
				if (rigthRule[i][(j + 1)] < terminalAmount && rigthRule[i][(j + 1)] >= 0)
					followTable[(rigthRule[i][j] - (terminalAmount + 1))][rigthRule[i][(j + 1)]] = 1;
				if (rigthRule[i][(j + 1)] > terminalAmount){
					for (k = 0; k < terminalAmount; k++){
						if (firstTable[(rigthRule[i][j + 1]) - (terminalAmount + 1)][k] == 1){
							followTable[rigthRule[i][j] - (terminalAmount + 1)][k] = 1;
						}
					}
				}
			}
			j++;
		} while (rigthRule[i][j] != -1);
	}
	
	for (i = 0; i < ruleCount; i++){
		j=0;
		while (rigthRule[i][j] != -1){

			if (rigthRule[i][(j + 1)] == -1){

				if (rigthRule[i][j] > terminalAmount){

					for (k = 0; k <= terminalAmount; k++){

						if ((followTable[leftRule[i]][k]) == 1)// add FOLLOW(A) to FOLLOW(Ai)
							followTable[(rigthRule[i][j] - (terminalAmount + 1))][k] = 1;
						if (firstTable[(rigthRule[i][j] - (terminalAmount + 1))][terminalAmount] == 1){ // if epslion in First(Ai) and (Ai-1)) is non ter then add 
							if (rigthRule[i][(j - 1)] > terminalAmount){
								if ((followTable[leftRule[i]][k]) == 1){
									followTable[(rigthRule[i][(j - 1)]) - (terminalAmount + 1)][k] = 1;
								}
								if (firstTable[(rigthRule[i][(j - 1)]) - (terminalAmount + 1)][terminalAmount] == 1){ // if  epslion in First(AI and Ai -1) and  (Ai -2) is non term  then add  
									if (rigthRule[i][(j - 2)] > terminalAmount){
										if ((followTable[leftRule[i]][k]) == 1){
											followTable[(rigthRule[i][(j - 2)]) - (terminalAmount + 1)][k] = 1;
										}
									}
									if (firstTable[(rigthRule[i][(j - 2)]) - (terminalAmount + 1)][terminalAmount] == 1){
										if (rigthRule[i][(j - 3)] > terminalAmount)
										{
											if ((followTable[leftRule[i]][k]) == 1)
											{
												followTable[(rigthRule[i][(j - 3)]) - (terminalAmount + 1)][k] = 1;
											}
										}
									}
								}
							}
						}
					}
				}
			} j++;
		}
	}
}
int determineT(int left)// determine if the rigth hand side is terminal 
{
	int i,j;
	int flag;
	for (i = 0; i < ruleCount; i++){
		if (left == leftRule[i]){
			flag = 1;
			j = 0;
			while (rigthRule[i][j] != -1){
			}
			if (flag == 1)
				return 1;
		}
	}
	return 0;
}
void genString()
{
	int i, j;
	for ( i = 0; i < terminalAmount; i++)
	{
		gen_a_string[i] = true;
	}
		gen_a_string[terminalAmount] = true;		
	for ( j = 0; j < nonTerminalAmount; j++)
	{
		gen_a_string[terminalAmount + j +1] = false; 
	}
		gen_a_string[i+j+1] = true;
}
void test()
{
	findFirst();
	findFollow();
	bool c = true;
	int j, k, l, m;
	bool change = true;
	while (c==true){
		change = false;
		for (j = 0; j < ruleCount; j++)
		{
			c = gen_a_string[leftRule[j] + terminalAmount + 1];

			if (c == false){
				gen_a_string[leftRule[j]+terminalAmount+1]==true;
				k = 0;
				while (rigthRule[j][k] != -1){
					if ((leftRule[j]+terminalAmount+1) == rigthRule[j][k]){
						gen_a_string[leftRule[j]+terminalAmount+1] = false;
						printf("%d -> %d\n", leftRule[j] + terminalAmount + 1, rigthRule[j][k]);
						
						if (gen_a_string[leftRule[j] + terminalAmount + 1]){
							printf("true \n");
						}
						else{
							printf("false\n");
						}
					}
					else
					{
						if (rigthRule[j][k] > terminalAmount && firstTable[rigthRule[j][k] - (terminalAmount + 1)][terminalAmount] == 1)
						{
							gen_a_string[leftRule[j] + terminalAmount + 1] = true; 
						}
						gen_a_string[leftRule[j] + terminalAmount + 1] = gen_a_string[leftRule[j] + terminalAmount + 1] &= gen_a_string[rigthRule[j][k]];
						printf("%d -> %d\n", leftRule[j] + terminalAmount + 1, rigthRule[j][k]);
						if (gen_a_string[leftRule[j] + terminalAmount + 1]){
							printf("true \n");
						}
						else{
							printf("false\n");
						}
					}
					k++;
				}
			}
			if (gen_a_string[leftRule[j]+terminalAmount+1] != c)
			{
				c = true;
			}

		}
	}

	findFirst();
	for (int i = 0; i < nonTerminalAmount; i++){
	
		if (gen_a_string[(terminalAmount + i + 1)]){
			printf("%s: YES\n", storeNTer[i]);
		}
		else
			printf("%s: NO\n", storeNTer[i]);

	}

	/*memset(stringTest, -1, sizeof(stringTest)); 
	int i;
	for (i = 0; i < nonTerminalAmount; i++)
	{
		stringTest[i] = determineT(i);
	}
		for (int a = 0; a < nonTerminalAmount; a++){
			printf("\n%d ", stringTest[a]);
		}
		printf("\n");
		printMap();*/
}


int main(int argc, char* argv[])
{

	int task;
	memset(rigthRule, -1, sizeof(rigthRule));
	memset(leftRule, -1, sizeof(leftRule));

	if (argc < 2)
	{
		printf("Error: missing argument\\n");
		return 1;
	}

	task = atoi(argv[1]);

	switch (task)
	{
	case 1:
		parse();
		printMap();
		genString();
		test();
		for (int i = 0; i < (terminalAmount + nonTerminalAmount + 2 ); i++){
			if (gen_a_string[i] == true)
				printf("%d: true \n",i);
			if (gen_a_string[i] == false)
				printf("%d: false \n", i);
		}
		printf("\nterm: %d", terminalAmount);
		printf("\nNterm: %d", nonTerminalAmount);
		printf("\n");
		break;

	case 2:
		parse();
		findFirst();
		sortList(0);
		printFirst();
			break;

	case 3:
		parse();
		findFirst();
		findFollow();
		sortList(1);
		printFollow();
		break;

	default:
		printf("Error: unrecognized task number %d\n", task);
		break;
		}
		return 0;
}