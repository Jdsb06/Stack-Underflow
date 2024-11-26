#include <stdio.h>
#include <mysql/mysql.h>
#include "order_c.h"

void viewCustomerOrders(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Customer_Order")) {
        fprintf(stderr, "Failed to fetch customer orders: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    printf("Customer ID | Item ID | Quantity | Status    | Order Date          | Completed Order Date\n");
    printf("------------------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-11s | %-7s | %-8s | %-9s | %-19s | %-15s\n",
        row[0], row[1], row[2], row[3], row[4] ? row[4] : "NULL", row[5] ? row[5] : "NULL");
    }
    mysql_free_result(res);
}

void completeCustomerOrder(MYSQL *conn) {
    int cust_order_id, item_id, quantity;
    printf("Enter Customer Order ID to complete: ");
    scanf("%d", &cust_order_id);

    char selectQuery[256];
    snprintf(selectQuery, sizeof(selectQuery),
             "SELECT item_id, quantity FROM Customer_Order WHERE cust_order_id=%d AND status='pending'",
             cust_order_id);

    if (mysql_query(conn, selectQuery)) {
        fprintf(stderr, "Failed to fetch purchase order details: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL || mysql_num_rows(res) == 0) {
        printf("No pending purchase order found with ID: %d\n", cust_order_id);
        mysql_free_result(res);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    item_id = atoi(row[0]);
    quantity = atoi(row[1]);
    mysql_free_result(res);

    char query[256];
    snprintf(query, sizeof(query), "UPDATE Customer_Order SET status='completed' , completed_order = NOW() WHERE cust_order_id=%d", cust_order_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to complete customer order: %s\n", mysql_error(conn));
        return;
    }

    char insertQuery[256];
    snprintf(insertQuery, sizeof(insertQuery),
             "INSERT INTO Transaction (item_id, type, quantity, tran_date) VALUES (%d, 'customer', %d, NOW())",
             item_id, quantity);

    if (mysql_query(conn, insertQuery)) {
        fprintf(stderr, "Failed to insert transaction record: %s\n", mysql_error(conn));
    } else {
        printf("Customer order completed and transaction record added successfully.\n");
    }
}


void manageOrders_c(MYSQL *conn) {
    int choice;
    do {
        printf("\n--- Customer Orders Management ---\n");
        printf("1. View Customer Orders\n");
        printf("2. Complete Customer Order\n");
        printf("3. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewCustomerOrders(conn);
            break;
            case 2:
                completeCustomerOrder(conn);
            break;
            case 3:
                printf("\nReturning to Main Menu.\n");
            return;
            default:
                printf("Invalid choice.\n");
        }
    } while(1);
}


