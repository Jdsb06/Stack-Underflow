#include <stdio.h>
#include "transaction.h"

void viewAllTransactions(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[] = "SELECT t.tran_id, t.item_id, m.name, t.type, t.quantity, t.tran_date "
                   "FROM Transaction t "
                   "JOIN Master m ON t.item_id = m.item_id";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("\n--- All Transactions ---\n");
    // printf("Tran ID | Item ID | Item Name | Type | Quantity | Date\n");
    // while ((row = mysql_fetch_row(res))) {
    //     printf("%s | %s | %s | %s | %s | %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    // }
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("\n%-10s | %-10s | %-20s | %-15s | %-10s | %-20s\n",
       "Tran ID", "Item ID", "Item Name", "Type", "Quantity", "Date-Time");
    printf("---------------------------------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("|%-10s | %-10s | %-20s | %-15s | %-10s | %-20s|\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }
    printf("---------------------------------------------------------------------------------------------------\n");

    mysql_free_result(res);
}

void searchTransactionsByDate(MYSQL *conn) {
    char date[11];
    printf("Enter the transaction date (YYYY-MM-DD): ");
    scanf("%s", date);

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT t.tran_id, t.item_id, m.name, t.type, t.quantity, t.tran_date "
             "FROM Transaction t "
             "JOIN Master m ON t.item_id = m.item_id "
             "WHERE DATE(t.tran_date) = '%s'", date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row;

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("\n--- Transactions on %s ---\n", date);

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("\n%-10s | %-10s | %-20s | %-15s | %-10s | %-20s\n",
       "Tran ID", "Item ID", "Item Name", "Type", "Quantity", "Date-Time");
    printf("---------------------------------------------------------------------------------------------------\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%-10s | %-10s | %-20s | %-15s | %-10s | %-20s\n",
               row[0], row[1], row[2], row[3], row[4], row[5]);
    }
    printf("---------------------------------------------------------------------------------------------------\n");


    mysql_free_result(res);
}



void manageTransactions(MYSQL *conn) {
    int choice;
    do {
        printf("\n--- Manage Transactions ---\n");
        printf("1. View Transactions\n2. Search Transactions by Date\n3. Return to Main Menu\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAllTransactions(conn);
            break;
            case 2:
                searchTransactionsByDate(conn);
            case 3:
                printf("\n");
            return;
            default:
                printf("Invalid choice.\n");
        }
    } while(1);
}


