#include	<stdio.h>
#include	<string.h>


int voting_function(void);
int vote_or_decrypt(void);
int main (void){
	
	vote_or_decrypt();
	
	return(0);
}

int vote_or_decrypt(void){
	
	char user_choice[6];
	
	printf("Would you like to 'vote' or 'check' an existing vote?:    ");
	if (scanf("%s", &user_choice) != 1){
		printf("Invalid input!\n");
		return(1);
	}
	if (strcmp(user_choice, "vote") == 0 || strcmp(user_choice, "Vote") == 0){
		printf("You have chosen to vote\n");
		voting_function();
	}
	else if (strcmp(user_choice, "check") == 0 || strcmp(user_choice, "Check") == 0){
		printf("You have chosen to check an exisiting vote\n");
		//deencrypting_function();
	}
	else{
		printf("Invalid input!\n");
		return(1);
	}
	
	return(0);
}

int voting_function(void){
	
	int	user_input = 0;
	
	printf("[0]	(0) Blank\n");
	printf("[1]	(A) Socialdemokraterne\n");
	printf("[2]	(B) Radikale Venstre\n");
	printf("[3]	(C) Det Konservative Folkeparti\n");
	printf("[4]	(F) Socialistisk Folkeparti\n");
	printf("[5]	(I) Liberal Alliance\n");
	printf("[6]	(K) Kristendemokraterne\n");
	printf("[7]	(O) Dansk Folkeparti\n");
	printf("[8]	(V) Venstre\n");
	printf("[9]	(OE) Enhedslisten\n");
	printf("[10]	(AA) Alternativet\n");
	printf("Input the number representing the party you would like to vote for:    ");
	
	if (scanf("%d", &user_input) != 1){
		printf("Invalid input");
		return(1);
	}
	
	switch(user_input){
		case '1' :
			printf("Do you wish to vote for (A) Socialdemokraterne?\n");
			break;
		case '2' :
			printf("Do you wish to vote for (B) Radikale Venstre?\n");
			break;
		case '3' :
			printf("Do you wish to vote for (C) Det Konservative Folkeparti?\n");
			break;
		case '4' :
			printf("Do you wish to vote for (F) Socilistisk Folkeparti?\n");
			break;
		case '5' :
			printf("Do you wish to vote for (I) Liberal Alliance?\n");
			break;
		case '6' :
			printf("Do you wish to vote for (K) Kristendemokraterne?\n");
			break;
		case '7' :
			printf("Do you wish to vote for (O) Dansk Folkeparti?\n");
			break;
		case '8' :
			printf("Do you wish to vote for (V) Venstre?\n");
			break;
		case '9' :
			printf("Do you wish to vote for (OE) Enhedslisten\n");
			break;
		case '0' :
			printf("Do you wish to vote for (AA) Alternativet\n");
			break;
		default :
			printf("Do you wish to vote blank?\n");
			
	}
			
		
		
		/*
	(user_input == 1){
		printf("Do you wish to vote for (A) Socialdemokraterne?\n");
	}
	*/
	
	
	return(0);
}
