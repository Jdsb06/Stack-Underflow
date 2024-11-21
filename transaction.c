#include <stdio.h>
#include "transaction.h"

void manageTransactions(MYSQL *conn) {
    int choice;
    printf("\n--- Manage Transactions ---\n");
    printf("1. View Transactions\n2. Return to Main Menu\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("View transactions functionality.\n");
        break;
        case 2:
            printf("\n");
        break;
        default:
            printf("Invalid choice.\n");
    }
}


