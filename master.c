#include <stdio.h>
#include "master.h"

void manageItems(MYSQL *conn) {
    int choice;
    printf("\n--- Master Data Management ---\n");
    printf("1. Add Item\n2. Display Items\n3. Update & Delete Item\n4. Return to Main Menu\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Implementation for adding item
                printf("Add item functionality.\n");
        break;
        case 2:
            // Implementation for displaying items
                printf("Display items functionality.\n");
        break;
        case 3:
            // Implementation for updating item
                printf("Update item functionality.\n");
        break;
        case 4:
            printf("\n");
        break;
        default:
            printf("Invalid choice.\n");
    }
}
