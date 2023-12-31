// C program to calculate electricity bill and print it to a text file
// This program also reads another text file which records due amounts
// which is indexed with having multiple records of different customers
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Function to calculate the bill amount based on the units consumed
float calculate_bill(int units)
{
    float amount;
    if (units <= 100)
    {
        amount = units * 2.9;
        amount =amount+70; //fixed charges
    }
    else if (units <= 300)
    {
        amount = 290 + ((units - 100) * 4.85);
        amount = amount + 110;
    }
    else if (units <= 500)
    {
        amount = 1260 + ((units - 300) * 6.65);
        amount = amount + 110;
    }
    else
    {
        amount = 2590 + ((units - 500) * 7.80);
        amount = amount + 135;
    }
    return amount;
}

// Function to read the due amount from a text file
// This function takes the customer ID as a parameter
// and searches for the corresponding due amount in the file
float read_due_amount(int id)
{
    FILE *fp;
    int cid;
    float due;
    // Open the file in read mode
    fp = fopen("DUE.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n","DUE.txt");
        exit(1);
    }
    // Read the customer ID and due amount from the file
    // until the end of file or a match is found
    while (fscanf(fp, "%d %f", &cid, &due) != EOF)
    {
        // If the customer ID matches, return the due amount
        if (cid == id)
        {
            fclose(fp);
            return due;
        }
    }
    // If no match is found, return zero
    fclose(fp);
    return 0;
}

// Function to write the bill details to a text file
void write_bill(char *filename, int id, int units, float amount, float due, float total)
{
    FILE *fp;
    // Open the file in write mode
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }
    // Write the bill details to the file
    fprintf(fp, "Customer ID: %d\n", id);
    fprintf(fp, "Units consumed: %d\n", units);
    fprintf(fp, "Bill amount: %.2f\n", amount);
    fprintf(fp, "Due amount: %.2f\n", due);
    printf("Total amount: %.2f\n", total);
    printf("Customer ID: %d\n", id);
    printf("Units consumed: %d\n", units);
    printf("Bill amount: %.2f\n", amount);
    printf("Due amount: %.2f\n", due);
    printf("Total amount: %.2f\n", total);
    // Close the file
    fclose(fp);
}

// Main function
int main()
{
    int id, units;
    float amount, due, total;
    char  bill_file[20];
    // Input the customer ID, units consumed, and the file name for due amount
    printf("Enter customer ID: ");
    scanf("%d", &id);
    printf("Enter units consumed: ");
    scanf("%d", &units);
    // Calculate the bill amount
    amount = calculate_bill(units);
    // Read the due amount from the file
    // Pass the customer ID as a parameter
    due = read_due_amount(id);
    // Calculate the total amount
    total = amount + due;
    // Input the file name for bill details
    printf("Enter file name for bill details to be saved in:\n ");
    scanf("%s", bill_file);
    // Write the bill details to the file
    write_bill(bill_file, id, units, amount, due, total);
    // Print a confirmation message
    printf("Bill details written to file %s\n", bill_file);
    printf("press any key to exit\n");
    getch();
    return 0;
}
