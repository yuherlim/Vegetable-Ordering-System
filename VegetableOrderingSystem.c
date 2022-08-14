#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#pragma warning(disable: 4996)

//constants for the price of packages.
#define PACK_A 24.50
#define PACK_B 26.00
#define PACK_C 27.50
#define PACK_D 29.00
//constant for the discount rate.
#define DISCOUNT_RATE 0.15
//constant for the delivery fee.
#define DELIVERY_FEE 5.00

//function declarations.
void StartingMessage(), PackageMenu(), SummaryReport(), EndMessage();
void CustomerList(char name[99][51], int customerNumber);
void TallyPackages(int numA[99], int numB[99], int numC[99], int numD[99], int customerNumber);
void StringInput(char passedString[], int lengthOfArray);
void TelNumInput(char telNum[16], int lengthOfArray);
void Invoice(char name[99][51], char telNum[99][16], char address1[99][51], char address2[99][51], char address3[99][51],\
	int numA[99], int numB[99], int numC[99], int numD[99], double totalA[99], double totalB[99], double totalC[99],\
	double totalD[99], double totalPackages[99], double deliveryFee[99], double subtotalBfRounding[99], double totalToPay[99],\
	double discountAmount[99], int customerNumber);
void ManageOrder(char name[99][51], char telNum[99][16], char address1[99][51], char address2[99][51], char address3[99][51],\
	int numA[99], int numB[99], int numC[99], int numD[99], double totalA[99], double totalB[99], double totalC[99],\
	double totalD[99], double totalPackages[99], double deliveryFee[99], double subtotalBfRounding[99], double totalToPay[99],\
	double discountAmount[99], int customerNumber, int deleteStatus[99]);
int MainMenu(), OrderManagementMenu(), IntInput();
char CharInput(), NextCustomer();
char YesNoValidation(char yesNoChar);
double RoundOff2Dp(double num);
double RoundOff1Dp(double num);


//GLOBAL VARIABLES
//VARIABLES FOR SUMMARY REPORT

//variable declarartion for final total quantity of package A, B, C and D used for the summary report, initialize to 0.
int finalA = 0, finalB = 0, finalC = 0, finalD = 0;
//variable declaration for the counter to keep track of the customer count, initialize to 0.
int customerQuantity = 0;
//variable declaration for the total earned today, total discounts given today, and total delivery fees charged today for the summary report, initialize to 0.
double totalEarned = 0, totalDiscounts = 0, totalDelivery = 0;

void main() {
	//VARIABLES WITH ARRAYS

	//variable declarations to store customer's name, contact number and address.
	char name[99][51], telNum[99][16], address1[99][51], address2[99][51], address3[99][51];

	//variable declarations to store quantity of packages ordered per customer for package A, B, C, and D.
	int numA[99], numB[99], numC[99], numD[99];

	//variable declarations for delivery fee, subtotal price of package A, B, C, and D, subtotal price of all packages,
	//subtotal before rounding, and the total to pay.
	double deliveryFee[99], totalA[99], totalB[99], totalC[99], totalD[99], totalPackages[99], subtotalBfRounding[99], totalToPay[99];

	//variable declaration for discount amount given to customer.
	double discountAmount[99];

	//variable declaration for the delete status of the customer's order.
	int deleteStatus[99];

	//variable declaration that serves as an index for accesing customer details, initialized to 0.
	//Also represents customer's order number.
	int customerNumber = 0;
	//variable declaration to store the choice of the main menu selection.
	int mainMenuSelection;
	//variable declaration for storing the status of the program that determines whether to continue accepting new orders.
	char continueOrder;
	//Loop for the main menu of the vegetables ordering system.
	do {
		//Print the main menu and ask for user selection, storing it in mainMenuSelection.
		mainMenuSelection = MainMenu();
		switch (mainMenuSelection)
		{
		//This case is for adding new customer orders.
		case 1:
			//loop for entering orders of customers.
			do {
				system("cls");
				//Print the title for adding new orders selection.
				printf("<------------------------------------------------------------>\n\n");
				printf("\tAdding New orders :\n\n");
				printf("<------------------------------------------------------------>\n\n");
				//print the current customer order number.
				customerNumber++;
				printf("\tCustomer No: %d\n\n", customerNumber);

				//INPUT
				//prompt and get customer's name, contact number and address.
				printf("\t%20s : ", "Enter name");
				StringInput(name[customerNumber], 51);

				printf("\t%20s : ", "Enter phone number");
				TelNumInput(telNum[customerNumber], 16);

				printf("\t%20s : \n", "Enter address");
				printf("\t%20s : ", "address line 1");
				StringInput(address1[customerNumber], 51);

				printf("\t%20s : ", "address line 2");
				StringInput(address2[customerNumber], 51);

				printf("\t%20s : ", "address line 3");
				StringInput(address3[customerNumber], 51);

				system("cls");

				//Intializing the quantity of package A, B, C, and D for this customer to 0.
				numA[customerNumber] = 0;
				numB[customerNumber] = 0;
				numC[customerNumber] = 0;
				numD[customerNumber] = 0;

				//Print the menu of packages for reference.
				PackageMenu();

				//variable declaration to store the type of package chosen for the current customer.
				char packageType;
				//Loop that ask for type of package and their quantity until user chooses to exit.
				do {
					//Prompt and get type of package from user.
					printf("\n\tPlease select the one of the package above.\n");
					printf("\tSelection\n");
					printf("\t(Enter either 'A', 'B', 'C', 'D' (Enter 'X' to End Order) : ");
					packageType = CharInput();

					//Converts packageType to uppercase to accept lowercase input from user.
					packageType = toupper(packageType);

					//variable declaration that stores the quantity inputted for the current chosen package.
					int newQuantity;

					//Depending on the case, it will store the quantity of packages ordered for the chosen package 
					//or it will exit and calculate the invoice.
					//The package menu and the tally of packages ordered so far is shown after each valid quantity inputted, 
					//easy for user to see what customer has ordered so far.
					//The quantity of packages are also added to finalA, finalB, finalC and finalD to be used in summary report.
					switch (packageType)
					{
					case 'A':
						printf("\tQuantity : ");
						newQuantity = IntInput();
						numA[customerNumber] += newQuantity;
						finalA += newQuantity;
						break;
					case 'B':
						printf("\tQuantity : ");
						newQuantity = IntInput();
						numB[customerNumber] += newQuantity;
						finalB += newQuantity;
						break;
					case 'C':
						printf("\tQuantity : ");
						newQuantity = IntInput();
						numC[customerNumber] += newQuantity;
						finalC += newQuantity;
						break;
					case 'D':
						printf("\tQuantity : ");
						newQuantity = IntInput();
						numD[customerNumber] += newQuantity;
						finalD += newQuantity;
						break;
					case 'X':
						//If any of the quantity of packages are left in negative values it will let the user know, prompting them to correct it.
						if (numA[customerNumber] < 0 || numB[customerNumber] < 0 || numC[customerNumber] < 0 || numD[customerNumber] < 0) {
							printf("\n\tERROR:\n");
							printf("\tNegative quantity of packages detected,\n");
							printf("\tplease ensure that there are no negative quantity of packages.\n");
							printf("\tThis can be done by adding new packages until\n");
							printf("\tthere is no longer a negative quantity of package.\n");
							//To prevent the loop from exiting, packageType is assigned a space character.
							packageType = ' ';
							system("pause");
						}
						break;
					//if user did not enter any of the above cases:
					default:
						printf("\n\tInvalid input detected, please enter one of the following :\n");
						printf("\t'A', 'B', 'C', 'D' ('X' to End Order)\n");
						system("pause");
						break;
					}
					system("cls");
					PackageMenu();
					TallyPackages(numA, numB, numC, numD, customerNumber);
				} while (packageType != 'X');

				//if no quantity of packages are inputted, cancel the current order, 
				//reset the customer number to the value before, and ask the user if they want to accept next customer.
				if (numA[customerNumber] == 0 && numB[customerNumber] == 0 && numC[customerNumber] == 0 && numD[customerNumber] == 0) {
					printf("\n\tNo quantity of packages inputted for package A, B, C, or D.\n");
					printf("\tCancelling order now...\n\n");
					system("pause");
					continueOrder = NextCustomer();
					customerNumber--;
					continue;
				}

				system("cls");

				printf("\n\tCalculating invoice now...\n");

				//PROCESS
				//Initialize delivery fee according to the DELIVERY_FEE constant for this customer.
				deliveryFee[customerNumber] = DELIVERY_FEE;
				//Calculate the subtotal price of package A, B, C, D, and the subtotal price of all packages for this customer.
				totalA[customerNumber] = PACK_A * numA[customerNumber];
				totalB[customerNumber] = PACK_B * numB[customerNumber];
				totalC[customerNumber] = PACK_C * numC[customerNumber];
				totalD[customerNumber] = PACK_D * numD[customerNumber];
				totalPackages[customerNumber] = totalA[customerNumber] + totalB[customerNumber] + totalC[customerNumber] + totalD[customerNumber];

				//Initialize discount amount for this customer to 0;
				discountAmount[customerNumber] = 0.00;

				//Incentives for customers, if they satisfy any of the following conditions.
				// No delivery fees if purchase amount is RM 80.00 or more.
				if (totalPackages[customerNumber] >= 80.00) {
					deliveryFee[customerNumber] = 0.00;
				}
				// 15% discount if purchase amount is RM 100.00 or more.
				if (totalPackages[customerNumber] >= 100.00) {
					discountAmount[customerNumber] = totalPackages[customerNumber] * DISCOUNT_RATE;
					//Round off discountAmount to 2 decimal places for more consistent calculation.
					discountAmount[customerNumber] = RoundOff2Dp(discountAmount[customerNumber]);
				}

				//Calculate the subtotal before rounding for this customer.
				subtotalBfRounding[customerNumber] = totalPackages[customerNumber] + deliveryFee[customerNumber] - discountAmount[customerNumber];

				//Round off subtotal to 1 decimal place for easier accounting and payment for cash on deliveries.
				//Assign the rounded off value as the total amount to be paid by this customer.
				totalToPay[customerNumber] = RoundOff1Dp(subtotalBfRounding[customerNumber]);

				//Add the total money, total delivery fee paid by this customer, and total discounts given to this customer to
				//totalEarned, totalDelivery and totalDiscounts respectively to be used in the summary report.
				totalEarned += totalToPay[customerNumber];
				totalDelivery += deliveryFee[customerNumber];
				totalDiscounts += discountAmount[customerNumber];

				//Add customer quantity by 1 for every sucessful order for usage in summary report.
				customerQuantity++;

				//OUTPUT
				//Output the invoice.
				Invoice(name, telNum, address1, address2, address3, numA, numB, numC, numD, totalA, totalB, totalC, totalD, totalPackages,\
					deliveryFee, subtotalBfRounding, totalToPay, discountAmount, customerNumber);
				//Thank you message.
				printf("\n\n\t%5sTHANK YOU, HAVE A NICE DAY!!\n\n", "");

				system("pause");

				//Ask whether user want to continue to take more customer orders.
				continueOrder = NextCustomer();

			} while (continueOrder == 'Y');
			break;
		//This case is for managing customer orders, user can choose either to view, delete/undo cancelled orders, or return to main menu.
		case 2:
			//Check if customer number is zero, if so print this statement, and return back to main menu.
			if (customerNumber == 0) {
				system("cls");
				printf("\n\n\tThere are no customers for today.\n\n");
				system("pause");
			}
			else {
				//Enter the order management system
				ManageOrder(name, telNum, address1, address2, address3, numA, numB, numC, numD, totalA, totalB, totalC, totalD, totalPackages,\
					deliveryFee, subtotalBfRounding, totalToPay, discountAmount, customerNumber, deleteStatus);
			}
			break;
		//This case is for viewing the daily sales summary report.
		case 3:
			//Print the summary report for the total sales.
			SummaryReport();
			system("pause");
			break;
		}
	} while (mainMenuSelection != 4);
	//Print the summary report for the total sales.
	SummaryReport();
	//Print the ending message.
	EndMessage();
	system("pause");
}

//Function for printing the starting message.
void StartingMessage() {
	//printing logo with starting message and the title of the program.
	printf("<------------------------------------------------------------>\n\n");
	printf("\t  000000  0    0\n");
	printf("\t 00       0    0  GH Organic Vegetable Farm,\n");
	printf("\t00  0000  000000  where we provide the \n");
	printf("\t 00    0  0    0  FRESHEST vegetables in town!\n");
	printf("\t  000000  0    0\n\n");
	printf("<------------------------------------------------------------>\n\n");
	printf("\tVegetables Ordering System\n\n");
	printf("<------------------------------------------------------------>\n");
}

//function that scans for an integer and returns it if it is a valid integer.
int IntInput() {
	//variable declaration used to store the valid integer to be returned back to main function.
	int validInt;
	//variable declaration to store the return value of scanf to determine if the scanf was successful
	int numValidInput;
	//variable declaration to store the second character input to be used to check if it was a newline.
	char input2;

	//input validation loop for integer input.
	do {
		//get integer input from user.
		rewind(stdin);
		numValidInput = scanf("%d%c", &validInt, &input2);
		//if user did not enter an integer, print invalid input and ask for integer input again.
		if (numValidInput != 2 || input2 != '\n') {
			printf("\n\tInvalid input detected, enter an integer. Please try again. : ");
		}
	} while (numValidInput != 2 || input2 != '\n');
	return validInt;
}

//function that scans for a string and returns the first character only if user inputted a character.
char CharInput() {
	//variable declaration to store the string input to check if user entered a character.
	char validChar[99];
	//input validation loop for character input.
	do {
		//get string input from user.
		fgets(validChar, 99, stdin);
		//if user did not enter a character, or first character is a space, or did not enter anything,
		//print invalid input and ask for character input again.
		if (validChar[0] == '\n' || validChar[0] == ' ' || validChar[1] != '\n') {
			printf("\n\tInvalid input detected, enter a character. Please try again. : ");
		}
	} while (validChar[0] == '\n' || validChar[0] == ' ' || validChar[1] != '\n');
	return validChar[0];
}

//Function that does input validation to check if the responses given are 'Y' or 'N', and returns the character if it is valid.
char YesNoValidation(char yesNoChar) {
	//Input validation: if user inputted anything other than 'Y' or 'N', ask again.
	while (yesNoChar != 'Y' && yesNoChar != 'N') {
		printf("\n\tPlease input 'Y' or 'N': ");
		yesNoChar = CharInput();
		//Convert status to uppercase to accept lowercase input from user.
		yesNoChar = toupper(yesNoChar);
	}
	//Return the character that has either 'Y' or 'N'.
	return yesNoChar;
}

//function that scans for a valid string, ensuring that there are no empty inputs.
void StringInput(char passedString[], int lengthOfArray) {
	do {
		//ask for string input from user.
		fgets(passedString, lengthOfArray, stdin);
		//replaces '\n' at the end of the string with '\0' character.
		passedString[strcspn(passedString, "\n")] = 0;
		//if user did not enter anything or the first character is a space, ask again.
		if (passedString[0] == '\0' || passedString[0] == ' ') {
			printf("\tYou did not enter anything for this field.\n");
			printf("\tPlease ensure that you have entered something.\n");
			printf("\tTry again: ");
		}
	} while (passedString[0] == '\0' || passedString[0] == ' ');
}

//Function that scans for a valid phone number.
void TelNumInput(char telNum[16], int lengthOfArray) {
	//variable declaration to store the status for the validity of the user input, initialized to 1.
	int invalid = 1;
	do {
		//Ensures that the string received is not an empty string.
		StringInput(telNum, lengthOfArray);
		//Check every character in the string to ensure that there are only numbers inputted.
		for (int i = 0; i < strlen(telNum); i++) {
			//if one of the character is not a number, print invalid input and ask again.
			if (isdigit(telNum[i]) == 0) {
				printf("\tInvalid phone number entered,\n");
				printf("\tplease ensure that only numbers are inputted.\n");
				printf("\tTry again: ");
				invalid = 1;
				break;
			}
			else {
				invalid = 0;
			}
		}
	} while (invalid == 1);
}

//Function that displays the main menu, asks for user selection and returns the selection.
int MainMenu() {
	system("cls");
	//variable declaration to store the choice of the main menu selection.
	int mainMenuSelection;
	//print the starting message.
	StartingMessage();
	//print the main menu.
	printf("\n\tTo Start using this program,\n");
	printf("\n\tPlease select a number from below : \n");
	printf("\n\t1. New Order\n");
	printf("\n\t2. Manage Orders\n");
	printf("\n\t3. View Summary Report\n");
	printf("\n\t4. Exit\n\n");
	//loop for input validation to ensure user inputted a valid selection.
	do {
		printf("\n\tSelection : ");
		//Scan for user selection and store it in mainMenuSelection.
		mainMenuSelection = IntInput();
		if (mainMenuSelection < 1 || mainMenuSelection > 4) {
			printf("\n\tInvalid input detected.\n");
			printf("\n\tPlease select one of the numbers above (1 - 4).\n");
		}
	} while (mainMenuSelection < 1 || mainMenuSelection > 4);
	return mainMenuSelection;
}

//function for printing the menu for the price of package A, B, C, and D as well as their contents.
void PackageMenu() {
	printf("\n\t\tMENU\n");
	printf("\t-----------------------------------------------\n");
	printf("\t| %-30s | %10s |\n", "Package", "Price (RM)");
	printf("\t-----------------------------------------------\n");
	printf("\t| %-30s | %10.2lf |\n", "A (kangkung, cabbage,", PACK_A);
	printf("\t| %-30s | %10s |\n", "  Ladies finger, banana)", "");
	printf("\t-----------------------------------------------\n");
	printf("\t| %-30s | %10.2lf |\n", "B (Yam leaves, long bean,", PACK_B);
	printf("\t| %-30s | %10s |\n", "  brinjal, guava)", "");
	printf("\t-----------------------------------------------\n");
	printf("\t| %-30s | %10.2lf |\n", "C (snake beans, broccoli,", PACK_C);
	printf("\t| %-30s | %10s |\n", "  spinach, papaya)", "");
	printf("\t-----------------------------------------------\n");
	printf("\t| %-30s | %10.2lf |\n", "D (bak choy, asparagus,", PACK_D);
	printf("\t| %-30s | %10s |\n", "  brinjal, dragon fruit)", "");
	printf("\t-----------------------------------------------\n");
}

//function that shows the tally of the quantity of packages ordered so far for a customer.
void TallyPackages(int numA[99], int numB[99], int numC[99], int numD[99], int customerNumber) {
	//variable declaration to store the total quantity of packages ordered so far for a customer.
	int totalQuantity;
	//Calculate the total quantity of packages ordered so far for a customer by adding the quantity of package A, B, C, and D ordered.
	totalQuantity = numA[customerNumber] + numB[customerNumber] + numC[customerNumber] + numD[customerNumber];
	//display a table that shows the tally of the quantity of packages ordered so far for a customer.
	printf("\n\tOrders so far:\n");
	printf("\t-------------------------------------\n");
	printf("\t| %-10s | %-20s |\n", "Package", "Quantity Ordered");
	printf("\t-------------------------------------\n");
	printf("\t| %-10s | %-20d |\n", "A", numA[customerNumber]);
	printf("\t-------------------------------------\n");
	printf("\t| %-10s | %-20d |\n", "B", numB[customerNumber]);
	printf("\t-------------------------------------\n");
	printf("\t| %-10s | %-20d |\n", "C", numC[customerNumber]);
	printf("\t-------------------------------------\n");
	printf("\t| %-10s | %-20d |\n", "D", numD[customerNumber]);
	printf("\t-------------------------------------\n");
	printf("\t| %-10s | %-20d |\n", "Total", totalQuantity);
	printf("\t-------------------------------------\n");
}

//Function that rounds off a number to 2 decimal places and returns it.
double RoundOff2Dp(double num) {
	num = floor(num * 100 + 0.5) / 100;
	return num;
}

//Function that rounds off a number to 1 decimal place and returns it.
double RoundOff1Dp(double num) {
	num = floor(num * 10 + 0.5) / 10;
	return num;
}

//function for printing the invoice.
void Invoice(char name[99][51], char telNum[99][16], char address1[99][51], char address2[99][51], char address3[99][51], \
	int numA[99], int numB[99], int numC[99], int numD[99], double totalA[99], double totalB[99], double totalC[99], \
	double totalD[99], double totalPackages[99], double deliveryFee[99], double subtotalBfRounding[99], double totalToPay[99], \
	double discountAmount[99], int customerNumber) {
	//Output the customer details.
	printf("\n\t%14sINVOICE\n\n", "");
	printf("\t%-10s: Mr / Ms %s\n", "Name", name[customerNumber]);
	printf("\t%-10s: %s\n", "Telephone", telNum[customerNumber]);
	printf("\t%-10s: %s\n", "Address", address1[customerNumber]);
	printf("\t%-10s  %s\n", "", address2[customerNumber]);
	printf("\t%-10s  %s\n", "", address3[customerNumber]);

	//Output the customer orders.
	printf("\n\t%10sCUSTOMER ORDERS\n", "");
	printf("\tPACKAGE A %6d @ %.2lf = RM %10.2lf\n", numA[customerNumber], PACK_A, totalA[customerNumber]);
	printf("\tPACKAGE B %6d @ %.2lf = RM %10.2lf\n", numB[customerNumber], PACK_B, totalB[customerNumber]);
	printf("\tPACKAGE C %6d @ %.2lf = RM %10.2lf\n", numC[customerNumber], PACK_C, totalC[customerNumber]);
	printf("\tPACKAGE D %6d @ %.2lf = RM %10.2lf\n", numD[customerNumber], PACK_D, totalD[customerNumber]);

	//Output the total counts.
	printf("\n\t%-15s = RM %10.2lf\n", "PACKAGE Charges", totalPackages[customerNumber]);
	printf("\t%-15s = RM %10.2lf\n", "Delivery Fees", deliveryFee[customerNumber]);
	printf("\t%-15s = RM %10.2lf\n", "Discounts", discountAmount[customerNumber]);
	printf("\t%-15s = RM %10.2lf\n\n", "Subtotal", subtotalBfRounding[customerNumber]);
	printf("\t%-15s\n", "After Rounding :");
	printf("\t%-15s = RM %10.2lf\n", "Total to pay", totalToPay[customerNumber]);
}

//Function for asking whether user wants to accept a next customer and returns the response.
char NextCustomer() {
	system("cls");
	//variable declaration for storing the status of the program that determines whether to continue accepting customers.
	char status;
	//Ask whether user want to continue to take more customer orders.
	printf("\n\n\tNext customer ? (Enter either 'Y' for yes or 'N' for no) : ");
	status = CharInput();
	//Convert status to uppercase to accept lowercase input from user.
	status = toupper(status);
	//Input validation: if user inputted anything other than 'Y' or 'N', ask again.
	status = YesNoValidation(status);
	return status;
}

//Function that displays the summary report of the sales on a particular day.
void SummaryReport() {
	system("cls");
	//variable declarations to store the total sales amount of package A, B, C, and D at the end of the day, 
	//as well as the total sales amount of all packages.
	double totalSalesA, totalSalesB, totalSalesC, totalSalesD, totalSales;
	//variable declaration for total quantity of packages ordered for the day.
	int totalQuantity;

	//Calculate the total quantity of packages ordered for the day.
	totalQuantity = finalA + finalB + finalC + finalD;
	//Calculate the total sales of package A, B, C, and D, as well as the total sales of all packages.
	totalSalesA = finalA * PACK_A;
	totalSalesB = finalB * PACK_B;
	totalSalesC = finalC * PACK_C;
	totalSalesD = finalD * PACK_D;
	totalSales = totalSalesA + totalSalesB + totalSalesC + totalSalesD;

	//print the daily sales summary report.
	printf("\n\tDAILY SALES SUMMARY REPORT\n");
	printf("\t-------------------------------------------------------\n");
	printf("\t| %-10s | %15s | %20s |\n", "Package", "Quantity Sold", "Sales Amount (RM)");
	printf("\t-------------------------------------------------------\n");
	printf("\t| %-10s | %15d | %20.2lf |\n", "A", finalA, totalSalesA);
	printf("\t-------------------------------------------------------\n");
	printf("\t| %-10s | %15d | %20.2lf |\n", "B", finalB, totalSalesB);
	printf("\t-------------------------------------------------------\n");
	printf("\t| %-10s | %15d | %20.2lf |\n", "C", finalC, totalSalesC);
	printf("\t-------------------------------------------------------\n");
	printf("\t| %-10s | %15d | %20.2lf |\n", "D", finalD, totalSalesD);
	printf("\t-------------------------------------------------------\n");
	printf("\t| %-10s | %15d | %20.2lf |\n", "Total", totalQuantity, totalSales);
	printf("\t-------------------------------------------------------\n");

	//print the total customer, total quantity of packages sold, total delivery fees, total discounts and total earned for today.
	printf("\n\tTOTAL:\n");
	printf("\t-----------------------------------------------\n");
	printf("\t| %-20s | %20d |\n", "Customers", customerQuantity);
	printf("\t-----------------------------------------------\n");
	printf("\t| %-20s | %20d |\n", "Packages Sold", totalQuantity);
	printf("\t-----------------------------------------------\n");
	printf("\t| %-20s | %20.2lf |\n", "Delivery Fees (RM)", totalDelivery);
	printf("\t-----------------------------------------------\n");
	printf("\t| %-20s | %20.2lf |\n", "Discounts (RM)", totalDiscounts);
	printf("\t-----------------------------------------------\n");
	printf("\t| %-20s | %20.2lf |\n", "Earned (RM)", totalEarned);
	printf("\t-----------------------------------------------\n");
}

//Function that displays the order management menu, asks for user selection and returns the selection.
int OrderManagementMenu() {
	system("cls");
	//variable declaration to store the choice of the selection for the order management menu.
	int selection;
	//print the title of the order management menu.
	printf("<------------------------------------------------------------>\n\n");
	printf("\tOrder Management Menu:\n\n");
	printf("<------------------------------------------------------------>\n");
	//print the order management menu.
	printf("\n\tThis is where you can choose to view");
	printf("\n\tyour orders or delete them.\n");
	printf("\n\tPlease select a number from below : \n");
	printf("\n\t1. View Orders\n");
	printf("\n\t2. Delete Orders / Undo cancelled orders\n");
	printf("\n\t3. Return to Main Menu\n\n");
	//loop for input validation to ensure user inputted a valid selection.
	do {
		printf("\n\tSelection : ");
		//Scan for user selection and store it in selection.
		selection = IntInput();
		if (selection < 1 || selection > 3) {
			printf("\n\tInvalid input detected.\n");
			printf("\n\tPlease select one of the numbers above (1 - 3).\n");
		}
	} while (selection < 1 || selection > 3);
	return selection;
}

//Function for printing the customer list that consists of customer's order number and their name.
void CustomerList(char name[99][51], int customerNumber) {
	//Display the header of the customer list.
	printf("\n\tCustomer list:\n");
	printf("\t--------------------------------------------------------------\n");
	printf("\t| %15s | %-40s |\n", "Customer Number", "Name");
	printf("\t--------------------------------------------------------------\n");
	//Loop for displaying the content of the customer list.
	for (int i = 1; i <= customerNumber; i++) {
		printf("\t| %15d | %-40s |\n", i, name[i]);
		printf("\t--------------------------------------------------------------\n");
	}
}

//Function to manage customer orders.
void ManageOrder(char name[99][51], char telNum[99][16], char address1[99][51], char address2[99][51], char address3[99][51], \
	int numA[99], int numB[99], int numC[99], int numD[99], double totalA[99], double totalB[99], double totalC[99], \
	double totalD[99], double totalPackages[99], double deliveryFee[99], double subtotalBfRounding[99], double totalToPay[99], \
	double discountAmount[99], int customerNumber, int deleteStatus[99]) {
	//variable declaration to store the order management menu selection.
	int manageOrderSelection;
	
	//Loop for the order management menu.
	do {
		//print the order management menu and ask for user selection, storing the selection in manageOrderSelection.
		manageOrderSelection = OrderManagementMenu();
		switch (manageOrderSelection)
		{
		//This case is to view customer orders.
		case 1:
			system("cls");
			//variable declaration to store the customer order number to view.
			int customerNumToView;
			//Loop for viewing customer orders.
			do {
				//Input validation loop that checks for negative values and invalid customer order numbers.
				do {
					//Display the customer list.
					CustomerList(name, customerNumber);

					//Ask user what is the customer order number for the order that they want to view.
					printf("\n\tEnter the customer number that you want to view");
					printf("\n\t(Enter '0' to return to order management menu) : ");
					customerNumToView = IntInput();
					if (customerNumToView < 0 || customerNumToView > customerNumber) {
						system("cls");
						printf("\n\tYou have either entered a negative number or a nonexistent customer number.\n");
						printf("\n\tTry again.\n");
					}
				} while (customerNumToView < 0 || customerNumToView > customerNumber);

				//break out of the loop for viewing customer orders if user input '0' to return to order management menu.
				if (customerNumToView == 0)
					break;

				system("cls");

				//If order has been deleted, mention it to user.
				if (deleteStatus[customerNumToView] == 1) {
					printf("\n\n\tThis customer order has been deleted.\n\n");
					system("pause");
					//Mention that the invoice displayed is for reference.
					printf("\n\n\tFOR REFERENCE : \n");
				}

				//Display the selected customer order number.
				printf("\n\tCustomer No: %d\n", customerNumToView);

				//Display the selected invoice.
				Invoice(name, telNum, address1, address2, address3, numA, numB, numC, numD, totalA, totalB, totalC, totalD, totalPackages, deliveryFee, subtotalBfRounding, totalToPay, discountAmount, customerNumToView);

				system("pause");
				system("cls");
			} while (customerNumToView != 0);
			break;
		//This case is to delete customer orders or undo the deletion of customer orders.
		case 2:
			system("cls");
			//variable declaration to store the customer order number to delete/undo deletion.
			int customerNumToDelete;
			//Loop for viewing customer orders that user want to delete/undo deletion.
			do {
				//Input validation loop that checks for negative values and invalid customer order numbers.
				do {
					//Display the customer list.
					CustomerList(name, customerNumber);

					//Ask user what is the customer order number for the order that they want to delete/undo deletion.
					printf("\n\tEnter the customer number that you want to delete.");
					printf("\n\n\tIf you want to undo a previous deletion,");
					printf("\n\tenter the customer number that has \"(Cancelled)\"");
					printf("\n\tat the back of their name.");
					printf("\n\n\t(Enter '0' to return to order management menu) : ");
					customerNumToDelete = IntInput();
					if (customerNumToDelete < 0 || customerNumToDelete > customerNumber) {
						system("cls");
						printf("\n\tYou have either entered a negative number or a nonexistent customer number.\n");
						printf("\n\tTry again.\n");
					}
				} while (customerNumToDelete < 0 || customerNumToDelete > customerNumber);

				//break out of the loop if user inputted '0', returning to order management menu.
				if (customerNumToDelete == 0)
					break;

				system("cls");
				//If the order of the chosen customer order number has been deleted before,
				//ask user if they want to undo the deletion of the order.
				if (deleteStatus[customerNumToDelete] == 1) {
					//variable declaration to store the decision to undo the deleted customer order.
					char undoDeletion;
					//variable declaration to store a copy of the customer name to be edited.
					char copyOfName[51];
					printf("\n\n\tThis customer order has been deleted before.\n\n");
					system("pause");
					printf("\n\n\tDo you want to undo the deletion?\n");
					printf("\t(Enter either 'Y' for yes or 'N' for no) : ");
					undoDeletion = CharInput();
					//Convert undoDeletion to uppercase to accept lowercase input from user.
					undoDeletion = toupper(undoDeletion);
					//Input validation: if user inputted anything other than 'Y' or 'N', ask again.
					undoDeletion = YesNoValidation(undoDeletion);
					if (undoDeletion == 'Y') {
						//add back the values of this customer order to the summary sales report.
						finalA += numA[customerNumToDelete];
						finalB += numB[customerNumToDelete];
						finalC += numC[customerNumToDelete];
						finalD += numD[customerNumToDelete];
						customerQuantity++;
						totalEarned += totalToPay[customerNumToDelete];
						totalDelivery += deliveryFee[customerNumToDelete];
						totalDiscounts += discountAmount[customerNumToDelete];

						//REVERTING CUSTOMER NAME TO ORIGINAL
						//Store a copy of the customer name into copyOfName.
						strcpy(copyOfName, name[customerNumToDelete]);
						//variable declaration to store the length of the customer name.
						int namelen;
						//Record the length of the customer name.
						namelen = strlen(name[customerNumToDelete]);
						//Assign null charcter at the end of customer name to remove the cancel status.
						copyOfName[namelen - strlen(" (Cancelled)")] = '\0';
						//Reassign the customer name without the cancel status back to the original name variable storing the customer's name.
						strcpy(name[customerNumToDelete], copyOfName);
						//update the customer's delete status to reflect that their order is now restored.
						deleteStatus[customerNumToDelete] = 0;
						//notify that the undo of deletion is successful.
						printf("\n\n\tSuccessfully undo cancellation of customer order no. %d .\n\n", customerNumToDelete);
						system("pause");
					}
					system("cls");
					//Return back to customer list and ask which order user want to delete/undo deletion.
					continue;
				}

				//Show the invoice of the chosen customer order number once.
				Invoice(name, telNum, address1, address2, address3, numA, numB, numC, numD, totalA, totalB, totalC, totalD, totalPackages, deliveryFee, subtotalBfRounding, totalToPay, discountAmount, customerNumToDelete);
				//variable declaration to store the response of user for delete confirmation.
				char deleteConfirmation;
				//Ask for confirmation of order deletion.
				printf("\n\tAre you sure you want to delete customer order no. %d\n", customerNumToDelete);
				printf("\t(Enter either 'Y' for yes or 'N' for no) : ");
				deleteConfirmation = CharInput();
				//Convert deleteConfirmation to uppercase to accept lowercase input from user.
				deleteConfirmation = toupper(deleteConfirmation);
				//Input validation: if user inputted anything other than 'Y' or 'N', ask again.
				deleteConfirmation = YesNoValidation(deleteConfirmation);

				if (deleteConfirmation == 'Y') {
					//minus the values of this customer order from the summary sales report.
					finalA -= numA[customerNumToDelete];
					finalB -= numB[customerNumToDelete];
					finalC -= numC[customerNumToDelete];
					finalD -= numD[customerNumToDelete];
					customerQuantity--;
					totalEarned -= totalToPay[customerNumToDelete];
					totalDelivery -= deliveryFee[customerNumToDelete];
					totalDiscounts -= discountAmount[customerNumToDelete];
					//Add the cancel status at the back of the customer's name.
					strcat(name[customerNumToDelete], " (Cancelled)");
					//update the customer's delete status to reflect that their order has been deleted
					deleteStatus[customerNumToDelete] = 1;
				}
				else {
					system("cls");
					//Return back to customer list and ask which order user want to delete/undo deletion.
					continue;
				}

				system("cls");
				//notify the user that customer's order has been deleted.
				printf("\n\tOrder for customer no. %d has been successfully deleted.\n", customerNumToDelete);
				//Display the customer order number for the deleted order.
				printf("\n\tCustomer No: %d\n", customerNumToDelete);

				//Display the invoice for the deleted order.
				Invoice(name, telNum, address1, address2, address3, numA, numB, numC, numD, totalA, totalB, totalC, totalD, totalPackages, deliveryFee, subtotalBfRounding, totalToPay, discountAmount, customerNumToDelete);
				system("pause");
				system("cls");
			} while (customerNumToDelete != 0);
			break;
		}
	} while (manageOrderSelection != 3);
}

//Prints the end message.
void EndMessage() {
	printf("\n\tSales for today has ended.\n\n");
	printf("\tClosing Vegetables Ordering System now...\n\n");
}