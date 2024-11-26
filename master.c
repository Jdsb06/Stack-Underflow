#include <stdio.h>
#include <mysql/mysql.h>
#include "master.h"

void addItem(MYSQL *conn) {
    char name[100], category[50], description[200];
    char query[512];

    printf("Enter Item Name: ");
    scanf(" %[^\n]", name); // Read input with spaces
    printf("Enter Item Category: ");
    scanf(" %[^\n]", category);
    printf("Enter Item Description: ");
    scanf(" %[^\n]", description);

    // Prepare the SQL query
    sprintf(query, "INSERT INTO Master (name, category, description) VALUES ('%s', '%s', '%s')", name, category, description);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error adding item: %s\n", mysql_error(conn));
    } else {
        printf("Item added successfully.\n");
    }
}

void displayItems(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Execute the query
    if (mysql_query(conn, "SELECT * FROM Master")) {
        fprintf(stderr, "Error fetching items: %s\n", mysql_error(conn));
        return;
    }

    // Store the result
    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return;
    }

    // Display the items
    printf("\n--- Items in Inventory ---\n");
    printf("%-10s %-20s %-20s %-50s\n", "Item ID", "Name", "Category", "Description");
    while ((row = mysql_fetch_row(res))) {
        printf("%-10s %-20s %-20s %-50s\n", row[0], row[1], row[2], row[3]);
    }

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

    // Prepare the SQL query to update the item
    sprintf(query,
            "UPDATE Master SET name = '%s', category = '%s', description = '%s' WHERE item_id = %d",
            *name ? name : "name",
            *category ? category : "category",
            *description ? description : "description",
            item_id);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error updating item: %s\n", mysql_error(conn));
    } else {
        printf("Item updated successfully.\n");
    }
}

void deleteItem(MYSQL *conn) {
    int item_id;
    printf("Enter Item ID to delete: ");
    scanf("%d", &item_id);

    // Check for pending orders in Purchase_Manufacture table
    char checkPurchaseQuery[256];
    snprintf(checkPurchaseQuery, sizeof(checkPurchaseQuery),
             "SELECT COUNT(*) FROM Purchase_Manufacture WHERE item_id=%d AND status='pending'", item_id);

    if (mysql_query(conn, checkPurchaseQuery)) {
        fprintf(stderr, "Error checking pending purchase orders: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    int purchasePendingCount = atoi(row[0]);
    mysql_free_result(res);

    if (purchasePendingCount > 0) {
        printf("Cannot delete item. It has %d pending purchase orders.\n", purchasePendingCount);
        return;
    }

    // Check for pending orders in CustomerOrder table
    char checkCustomerQuery[256];
    snprintf(checkCustomerQuery, sizeof(checkCustomerQuery),
             "SELECT COUNT(*) FROM Customer_Order WHERE item_id=%d AND status='pending'", item_id);

    if (mysql_query(conn, checkCustomerQuery)) {
        fprintf(stderr, "Error checking pending customer orders: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    int customerPendingCount = atoi(row[0]);
    mysql_free_result(res);

    if (customerPendingCount > 0) {
        printf("Cannot delete item. It has %d pending customer orders.\n", customerPendingCount);
        return;
    }

    // Proceed to delete the item if no pending orders exist
    char deleteQuery[256];
    snprintf(deleteQuery, sizeof(deleteQuery), "DELETE FROM Master WHERE item_id=%d", item_id);

    if (mysql_query(conn, deleteQuery)) {
        fprintf(stderr, "Error deleting item: %s\n", mysql_error(conn));
    } else {
        printf("Item with ID %d deleted successfully.\n", item_id);
    }
}

void manageItems(MYSQL *conn) {
    int choice;
    do {
        printf("\n--- Manage Items ---\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Update Item\n");
        printf("4. Delete Item\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem(conn);
                break;
            case 2:
                displayItems(conn);
                break;
            case 3:
                updateItem(conn);
                break;
            case 4:
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


