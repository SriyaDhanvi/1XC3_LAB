//ATM bank part c: includes multiple accounts
#include <stdio.h>
#include <math.h>
#define MAX_ACCOUNTS 10

int main(){

	float balances[MAX_ACCOUNTS];
	int numOfAccounts;
	int currentAccount;
	int operation;
	float amount;
	float interestRate;
	int time;

	printf("\nWelcome to the Simple Banking System!\n\n");

	printf("Please enter the number of accounts: ");
	scanf("%d", &numOfAccounts);

	//Using the for loop to add the balances of each account
	for (int i = 0; i < numOfAccounts; i++){
		printf("\nPlease enter the balance for acoount number %d: ", i + 1);
		scanf("%f",&balances[i]);
	}

	//Choosing the current account
	printf("\n\nCurrent Account: ");
	scanf("%d", &currentAccount);

	// Using a do loop to keep selecting an operation as long as it is not exit
	do{

		printf("Select an operation:\n");
		printf("1. Deposit\n");
		printf("2. Withdraw\n");
		printf("3. Check Balance\n");
		printf("4. Future Balance Using Interest Rate\n");
		printf("5. Switch Account\n");
		printf("6. Display All Balances\n");
		printf("0. exit\n");

		// Asking the user to enter their preferred operation
		printf("\nPlease enter your operation: ");
		scanf("%d", &operation);

		switch (operation){
		// Deposit
		case 1:
			printf("\nEnter the amount to be deposited: ");
			scanf("%f", &amount);

			// making sure the user cannot deposit negative amount
			if (amount < 0){
				printf("\nInvalid amount. Please enter a positive value.");
			}
			balances[currentAccount] += amount;
			printf("\nDeposit was successful\n\n");
			break;

		// Withdraw
		case 2:
			printf("\nEnter the amount to be withdrawn: ");
			scanf("%f", &amount);

			// making sure the user cannot withdraw negative amount
			if (amount < 0){
					printf("\nInvalid amount. Please enter a positive value.");
			}
			
			// when the amount to be withdrawn is greater than the balance available
			if (amount > balances[currentAccount]){
				printf("\nInsufficient balance. Withdrawl was unsuccessful\n\n");
			}
			else{
				balances[currentAccount] -= amount;
				printf("\nWithdrawl was successful\n\n");
			}
			break;

		// Checking Balance
		case 3:
			printf("\nCurrent Balance: %f\n\n", balances[currentAccount]);
			break;

		// Future Balance after interest
		case 4:
			printf("\nPlease enter your desired interest rate: ");
			scanf("%f", &interestRate);
			
			// making sure the user does not enter negative interest rate
			if (interestRate < 0){
				printf("\nInvalid interest rate. Please enter a positive value.\n");
				break;
			}
			
			printf("Please enter the number of time: ");
			scanf("%d", &time);
			// making sure the user does not enter negative time
	
			if (time< 0){
				printf("\nInvalid number of time. Please enter a positive value.\n");
				break;
			}

			float futureBalance = balances[currentAccount] * pow((1 + interestRate), time);
			printf("\nFuture balance after %d time: %f\n\n", time, futureBalance);
			break;

		// Switching account
		case 5:
			printf("Please enter the account number to switch to (1-%d) : ", numOfAccounts);
			scanf("%d", &currentAccount);
			currentAccount--; 
			if (currentAccount < 0 || currentAccount >= numOfAccounts){
				printf("\nInvalid account number\n");
				currentAccount = 0;
			}
			break;
		
		//Display all balances
		case 6:
			printf("Account Balances: \n");
			for (int i = 0; i < numOfAccounts; i++){
				printf("Account %d: %f\n", i + 1, balances[i]);
			}
			break;

		// Exit
		case 0:
			printf("\nExiting...\n");
			printf("Thank you for using the Simple Banking System\n\n");

		// for every invalid operation
		default:
			if (operation != 0)
			{
				printf("\nInvalid operation. Please try again.\n\n");
			}
			break;
		}
	}

	while (operation != 0);

	return 0;
}
