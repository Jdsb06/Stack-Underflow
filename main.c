#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "master.h"
#include "order_p.h"
#include "transaction.h"
#include "user.h"
#include "order_c.h"
#include "statistics.h"

MYSQL *conn;

void displayMenu() {
    printf("\n--- Warehouse Management System ---\n");
    printf("1. Master Data Management\n");
    printf("2. Purchase Management\n");
    printf("3. Customer Order Management\n");
    printf("4. Transactions Management\n");
    printf("5. Reports & Statistics\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "StackUnderflow", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    userMenu(conn); // Display sign-in/sign-up menu

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                manageItems(conn);
            break;
            case 2:
                manageOrders_p(conn);
            break;
            case 3:
                manageOrders_c(conn);
            break;
            case 4:
                manageTransactions(conn);
            break;
            case 5:
                viewStatistics(conn);
            break;
            case 6:
                printf("Exiting...\n");
            break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    mysql_close(conn);
    return 0;
}
