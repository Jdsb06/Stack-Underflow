#include <stdio.h>
#include <mysql/mysql.h>
#include "user.h"




void userMenu(MYSQL *conn) {
    int choice;
    do {
        printf("\n\033[1;34m--- Warehouse Management System ---\033[0m\n");
        printf("\n\033[1;34m---- User Menu ---\033[0m\n");
        printf("1. Sign In\n");
        printf("2. Sign Up\n");
        printf("\033[31m3. Exit\033[0m\n");
        printf("\033[1;32mEnter your choice: \033[0m ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (signIn(conn)) {
                    printf("Login successful!\n");
                    return; // Proceed to the main menu after successful login
                }
                break;
            case 2:
                signUp(conn);
                break;
            case 3:
                printf("Exiting...\n");
                mysql_close(conn);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (1); // Keep showing the menu until user signs in or exits
}

int signIn(MYSQL *conn) {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    char query[256];
    sprintf(query, "SELECT * FROM User WHERE user_name='%s' AND password='%s'", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL || mysql_num_rows(res) == 0) {
        printf("Invalid credentials.\n");
        mysql_free_result(res);
        return 0;
    }

    mysql_free_result(res);
    return 1; // Successful login
}

void signUp(MYSQL *conn) {
    char username[50], password[50];
    printf("Enter a new username: ");
    scanf("%s", username);
    printf("Enter a new password: ");
    scanf("%s", password);

    char query[256];
    sprintf(query, "INSERT INTO User (user_name, password) VALUES ('%s', '%s')", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Sign-up failed: %s\n", mysql_error(conn));
    } else {
        printf("Sign-up successful! You can now sign in.\n");
    }
}

