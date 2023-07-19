// ATM bank part b: includes interest rate calculation
#include <stdio.h>
#include <math.h>

int main(){

	// Assuming that the input values are not strings, but only are of float or int data type.
	float balance = 0.0;
	int operation;
	float amount;
	float futureBalance = 0.0;
	float interestRate;
	float time;

	printf("\nWelcome to the Simple Banking System!\n\n");

	// Using a do loop to keep selecting an operation as long as it is not exit
	do{

		printf("Select an operation:\n");
		printf("1. Deposit\n");
		printf("2. Withdraw\n");
		printf("3. Check Balance\n");
		printf("4. Future Balance Using Interest Rate\n");
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
				break;
			}
			balance += amount;
			printf("\nDeposit was successful\n\n");
			break;

			// Withdraw
		
		case 2:
			printf("\nEnter the amount to be withdrawn: ");
			scanf("%f", &amount);

			// making sure the user cannot withdraw negative amount
			if (amount < 0){
					printf("\nInvalid amount. Please enter a positive value.");
					break;
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
			scanf("%f", &time);
			// making sure the user does not enter negative time
			if (time < 0){
				printf("\nInvalid number of time. Please enter a positive value.\n");
				break;
			}

			futureBalance = balance * pow((1 + interestRate), time);
			printf("\nFuture balance after %f time: %f\n\n", time, futureBalance);
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

/*	- To compile the above code, I have used the command: gcc -Wformat -o atmbankb ATM_Bank_b.c -lm
I have used the flag "-lm" as we are using the "pow" fucntion which comes under the math header file.
	- I then used the command "./atmbankb" to run the code.*/