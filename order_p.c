#include <stdio.h>
#include "order_p.h"

void manageOrders_p(MYSQL *conn) {
    int choice;
    printf("\n--- Purchase Management ---\n");
    printf("1. Add Purchase Order\n"
           "2. View Pending Orders\n"
           "3. Mark Purchase as Completed\n"
           "4. View Completed Purchase\n"
           "5. Return to Main Menu\n"
           "Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Add Purchase Order functionality.\n");
        break;
        case 2:
            printf("View pending orders functionality.\n");
        break;
        case 3:
            printf("Mark order as completed functionality.\n");
        break;
        case 4:
            printf("View completed orders functionality.\n");
        break;
        case 5:
            printf("\n");
        break;
        default:
            printf("Invalid choice.\n");
    }
}
