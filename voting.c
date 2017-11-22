#include	<stdio.h>
#include	<string.h>

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
	
	printf("[0]	(0) Blank");
	printf("[1]	(A) Socialdemokraterne\n");
	printf("[2]	(B) Radikale Venstre\n");
	printf("[3]	(C) Det Konservative Folkeparti\n");
	printf("[4]	(F) Socialistisk Folkeparti\n");
	printf("[5]	(I) Liberal Alliance\n");
	printf("[6]	(K) Kristendemokraterne\n");
	printf("[7]	(O) Dansk Folkeparti\n");
	printf("[8]	(V) Venstre\n");
	printf("[9]	(Ø) Enhedslisten\n");
	printf("[10]	(Å) Alternativet\n");
	printf("Input the number representing the party you would like to vote for:    ");
	scanf("%d", &user_input);
	
	
	
	return(0);
}
