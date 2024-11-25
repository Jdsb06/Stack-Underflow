// #include <stdio.h>
// #include "transaction.h"

// void manageTransactions(MYSQL *conn) {
//     int choice;
//     printf("\n--- Manage Transactions ---\n");
//     printf("1. View Transactions\n2. Return to Main Menu\nEnter your choice: ");
//     scanf("%d", &choice);

//     switch (choice) {
//         case 1:
//             printf("View transactions functionality.\n");
//         break;
//         case 2:
//             printf("\n");
//         break;
//         default:
//             printf("Invalid choice.\n");
//     }
// }
#include <stdio.h>
#include <mysql/mysql.h>
#include "master.h"
#include "transaction.h"

void manageTransactions(MYSQL *conn) {
    int choice;

    printf("\n--- Manage Transactions ---\n");
    printf("1. View All Transactions\n");
    printf("2. Search Transactions by Date\n");
    printf("3. Add Transaction\n");
    printf("4. Return to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        viewAllTransactions(conn);
    } else if (choice == 2) {
        searchTransactionsByDate(conn);
    } else if (choice == 3) {
        addTransaction(conn);
    } else if (choice == 4) {
        printf("Returning to Main Menu...\n");
    } else {
        printf("Invalid choice.\n");
    }
}

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
    printf("Tran ID | Item ID | Item Name | Type | Quantity | Date\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s | %s | %s | %s | %s | %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    }

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
             "WHERE t.tran_date = '%s'", date);

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
    printf("Tran ID | Item ID | Item Name | Type | Quantity | Date\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s | %s | %s | %s | %s | %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    }

    mysql_free_result(res);
}

void addTransaction(MYSQL *conn) {
    int item_id, quantity;
    char type[50]; 
    char query[512];

    printf("Enter Item ID: ");
    scanf("%d", &item_id);


    char validateQuery[256];
    snprintf(validateQuery, sizeof(validateQuery), "SELECT * FROM Master WHERE item_id = %d", item_id);
    if (mysql_query(conn, validateQuery)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (mysql_num_rows(res) == 0) {
        printf("Invalid Item ID. Please try again.\n");
        mysql_free_result(res);
        return;
    }
    mysql_free_result(res);

   
    printf("Enter Transaction Type (purchase/customer order): ");
    scanf("%s", type);
    printf("Enter Quantity: ");
    scanf("%d", &quantity);

    snprintf(query, sizeof(query),
             "INSERT INTO Transaction (item_id, type, quantity, tran_date) VALUES (%d, '%s', %d, NOW())",
             item_id, type, quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("Transaction added successfully!\n");
}


