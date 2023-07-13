// ATM Bank part a
#include <stdio.h>
int main(){

	float balance = 0.0;
	int operation;
	float amount;

	printf("\nWelcome to the Simple Banking System!\n\n");

	// Using a do loop to keep selecting an operation as long as it is not exit
	do{

		printf("Select an operation:\n");
		printf("1. Deposit\n");
		printf("2. Withdraw\n");
		printf("3. Check Balance\n");
		printf("0. exit\n");

		// Asking the user to enter their preferred operation
		printf("\nPlease enter your operation: ");
		scanf("%d", operation);

		switch(operation){
		// Deposit
		case 1:
			printf("\nEnter the amount to be deposited: ");
			scanf("%f", &amount);

			// making sure the user cannot deposit negative amount
			if (amount < 0){
				printf("\nInvalid amount. Please enter a positive value.");
			}
			balance += amount;
			printf("\nDeposit was successful\n\n");
			break;

		// Withdraw
		case 2:
			printf("\nEnter the amount to be withdrawn: ");
			scanf("%f", &amount);

			// making sure the user does not withdraw negative amount
			if (amount < 0){
				printf("\nInvalid amount. Please enter a positive value.");
			}

			// when the amount to be withdrawn is greater than the balance available
			if (amount > balance){
				printf("\nInsufficient balance. Withdrawl was unsuccessful\n\n");
			}
			else{
				balance -= amount;
				printf("\nWithdrawl was successful\n\n");
			}
			break;

		// Checking Balance
		case 3:
			printf("\nCurrent Balance: %f\n\n", balance);
			break;

		// Exit
		case 0:
			printf("\nExiting...\n");
			printf("Thank you for using the Simple Banking System\n\n");

		// for every invalid operation
		default:
			if (operation != 0){
				printf("\nInvalid operation. Please try again.\n\n");
			}
			break;
		}

	}

	while (operation != 0);

	return 0;
}
