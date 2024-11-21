#include <stdio.h>
#include "statistics.h"

void viewStatistics(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    printf("\n--- Statistics ---\n");

    // Total inventory count
    if (mysql_query(conn, "SELECT COUNT(*) AS total_items FROM Master")) {
        fprintf(stderr, "Failed to fetch inventory stats: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (res != NULL && (row = mysql_fetch_row(res))) {
        printf("Total Items in Inventory: %s\n", row[0]);
    }
    mysql_free_result(res);

    // Total completed purchase orders
    if (mysql_query(conn, "SELECT COUNT(*) AS completed_purchases FROM Purchase_Manufacture WHERE status='completed'")) {
        fprintf(stderr, "Failed to fetch completed purchases: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (res != NULL && (row = mysql_fetch_row(res))) {
        printf("Total Completed Purchase Orders: %s\n", row[0]);
    }
    mysql_free_result(res);

    // Total pending customer orders
    if (mysql_query(conn, "SELECT COUNT(*) AS pending_orders FROM Customer_Order WHERE status='pending'")) {
        fprintf(stderr, "Failed to fetch pending customer orders: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (res != NULL && (row = mysql_fetch_row(res))) {
        printf("Total Pending Customer Orders: %s\n", row[0]);
    }
    mysql_free_result(res);

    // Total transactions
    if (mysql_query(conn, "SELECT COUNT(*) AS total_transactions FROM Transaction")) {
        fprintf(stderr, "Failed to fetch total transactions: %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (res != NULL && (row = mysql_fetch_row(res))) {
        printf("Total Transactions Logged: %s\n", row[0]);
    }
    mysql_free_result(res);

    printf("\n--- End of Statistics ---\n");
}
