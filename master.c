#include <stdio.h>
#include <mysql/mysql.h>
#include "master.h"
#include <stdlib.h>


static void refresh() {
    system("clear");
}

void addItem(MYSQL *conn) {
    char name[100], category[50], description[200];
    char query[512];

    printf("Enter Item Name: ");
    scanf(" %[^\n]", name); // Read input with spaces
    printf("Enter Item Category: ");
    scanf(" %[^\n]", category);
    printf("Enter Item Description: ");
    scanf(" %[^\n]", description);


    sprintf(query, "INSERT INTO Master (name, category, description) VALUES ('%s', '%s', '%s')", name, category, description);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error adding item: %s\n", mysql_error(conn));
    } else {
        printf("Item added successfully.\n");
    }
}

void displayItems(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;


    if (mysql_query(conn, "SELECT * FROM Master")) {
        fprintf(stderr, "Error fetching items: %s\n", mysql_error(conn));
        return;
    }


    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return;
    }


    printf("\n--- Items in Inventory ---\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-20s %-50s\n", "|Item ID", "|Name", "|Category", "|Description");
    printf("----------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-10s %-20s %-20s %-50s\n", row[0], row[1], row[2], row[3]);
    }
    printf("----------------------------------------------------------------------------\n");
    mysql_free_result(res);
}

void updateItem(MYSQL *conn) {
    int item_id;
    char name[100], category[50], description[200];
    char query[512];

    printf("Enter Item ID to Update: ");
    scanf("%d", &item_id);
    printf("Enter New Name (Leave empty to keep current): ");
    scanf(" %[^\n]", name);
    printf("Enter New Category (Leave empty to keep current): ");
    scanf(" %[^\n]", category);
    printf("Enter New Description (Leave empty to keep current): ");
    scanf(" %[^\n]", description);


    sprintf(query,
            "UPDATE Master SET name = '%s', category = '%s', description = '%s' WHERE item_id = %d",
            *name ? name : "name",
            *category ? category : "category",
            *description ? description : "description",
            item_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error updating item: %s\n", mysql_error(conn));
    } else {
        printf("Item updated successfully.\n");
    }
}


int checkItemQuantity(MYSQL *conn, int item_id) {
    char query[256];
    snprintf(query, sizeof(query),
             "SELECT SUM(quantity) FROM Transaction WHERE item_id = %d", item_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error checking quantity: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int total_quantity = atoi(row[0]);
    mysql_free_result(res);

    return total_quantity;
}


void deleteItem(MYSQL *conn) {
    int item_id;
    printf("Enter Item ID to delete: ");
    scanf("%d", &item_id);


    int total_quantity = checkItemQuantity(conn, item_id);
    if (total_quantity == -1) {
        printf("Error occurred while checking item quantity.\n");
        return;
    } else if (total_quantity != 0) {
        printf("Item has non-zero quantity (%d). Cannot delete item.\n", total_quantity);
        return;
    }


    printf("Item has zero quantity. Proceeding with deletion...\n");


    char deleteCustomerQuery[256];
    snprintf(deleteCustomerQuery, sizeof(deleteCustomerQuery),
             "DELETE FROM Customer_Order WHERE item_id = %d", item_id);

    if (mysql_query(conn, deleteCustomerQuery)) {
        fprintf(stderr, "Error deleting from Customer_Order: %s\n", mysql_error(conn));
    }


    char deleteTransactionQuery[256];
    snprintf(deleteTransactionQuery, sizeof(deleteTransactionQuery),
             "DELETE FROM Transaction WHERE item_id = %d", item_id);

    if (mysql_query(conn, deleteTransactionQuery)) {
        fprintf(stderr, "Error deleting from Transaction: %s\n", mysql_error(conn));
    }


    char deletePurchaseQuery[256];
    snprintf(deletePurchaseQuery, sizeof(deletePurchaseQuery),
             "DELETE FROM Purchase_Manufacture WHERE item_id = %d", item_id);

    if (mysql_query(conn, deletePurchaseQuery)) {
        fprintf(stderr, "Error deleting from Purchase_Manufacture: %s\n", mysql_error(conn));
    }


    char deleteMasterQuery[256];
    snprintf(deleteMasterQuery, sizeof(deleteMasterQuery),
             "DELETE FROM Master WHERE item_id = %d", item_id);

    if (mysql_query(conn, deleteMasterQuery)) {
        fprintf(stderr, "Error deleting from Master: %s\n", mysql_error(conn));
    } else {
        printf("Item with ID %d deleted successfully from all tables.\n", item_id);
    }
}


void manageItems(MYSQL *conn) {
    int choice;
    do {
        printf("\n\033[1;34m--- Manage Items ---\033[0m\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Update Item\n");
        printf("4. Delete Item\n");
        printf("\033[31m5. Back to Main Menu\033[0m\n");
        printf("\033[1;32mEnter your choice: \033[0m ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                refresh();
                addItem(conn);
                break;
            case 2:
                refresh();
                displayItems(conn);
                break;
            case 3:
                refresh();
                updateItem(conn);
                break;
            case 4:
                refresh();
                deleteItem(conn);
            break;
            case 5:
                printf("Returning to Main Menu...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}


