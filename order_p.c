#include <stdio.h>
#include <mysql/mysql.h>
#include "order_p.h"

void addPurchaseOrder(MYSQL *conn) {
    int item_id, quantity;
    printf("Enter Item ID for purchase: ");
    scanf("%d", &item_id);
    printf("Enter Quantity to purchase: ");
    scanf("%d", &quantity);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO Purchase_Manufacture (item_id, quantity, status, order_date) VALUES (%d, %d, 'pending',NOW())", item_id, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to add purchase order: %s\n", mysql_error(conn));
    } else {
        printf("Purchase order added successfully.\n");
    }
}

void viewPurchaseOrders(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Purchase_Manufacture")) {
        fprintf(stderr, "Failed to fetch purchase orders: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("Purchase ID | Item ID | Quantity | Status    | Order Date          | Completed Order Date\n");
    printf("------------------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-11s | %-7s | %-8s | %-9s | %-19s | %-15s\n",
            row[0], row[1], row[2], row[3], row[4] ? row[4] : "NULL", row[5] ? row[5] : "NULL");
    }
    mysql_free_result(res);
}

void completePurchaseOrder(MYSQL *conn) {
    int purchase_id, item_id, quantity;
    printf("Enter Purchase Order ID to complete: ");
    scanf("%d", &purchase_id);

    char selectQuery[256];
    snprintf(selectQuery, sizeof(selectQuery),
             "SELECT item_id, quantity FROM Purchase_Manufacture WHERE purchase_id=%d AND status='pending'",
             purchase_id);

    if (mysql_query(conn, selectQuery)) {
        fprintf(stderr, "Failed to fetch purchase order details: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL || mysql_num_rows(res) == 0) {
        printf("No pending purchase order found with ID: %d\n", purchase_id);
        mysql_free_result(res);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    item_id = atoi(row[0]);
    quantity = atoi(row[1]);
    mysql_free_result(res);

    char query[256];
    snprintf(query, sizeof(query), "UPDATE Purchase_Manufacture SET status='completed' , completed_order = NOW() WHERE purchase_id=%d", purchase_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to complete purchase order: %s\n", mysql_error(conn));
        return;
    }

    char insertQuery[256];
    snprintf(insertQuery, sizeof(insertQuery),
             "INSERT INTO Transaction (item_id, type, quantity, tran_date) VALUES (%d, 'purchase', %d, NOW())",
             item_id, quantity);

    if (mysql_query(conn, insertQuery)) {
        fprintf(stderr, "Failed to insert transaction record: %s\n", mysql_error(conn));
    } else {
        printf("Purchase order completed and transaction record added successfully.\n");
    }

}


void manageOrders_p(MYSQL *conn) {
    int choice;
    do {
        printf("\n--- Purchase Orders Management ---\n");
        printf("1. Add Purchase Order\n");
        printf("2. View Purchase Orders\n");
        printf("3. Complete Purchase Order\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPurchaseOrder(conn);
            break;
            case 2:
                viewPurchaseOrders(conn);
            break;
            case 3:
                completePurchaseOrder(conn);
            break;
            case 4:
                printf("\nReturning to Main Menu.\n");
            return;
            default:
                printf("Invalid choice.\n");
        }
    } while(1);
}

