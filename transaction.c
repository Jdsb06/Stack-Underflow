
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"
static void refresh() {
    system("clear");
}
// Helper function to create a new Transaction node
Transaction *createTransactionNode(int tran_id, int item_id, const char *item_name, const char *type, int quantity, const char *tran_date) {
    Transaction *newNode = (Transaction *)malloc(sizeof(Transaction));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    newNode->tran_id = tran_id;
    newNode->item_id = item_id;
    strncpy(newNode->item_name, item_name, sizeof(newNode->item_name) - 1);
    strncpy(newNode->type, type, sizeof(newNode->type) - 1);
    newNode->quantity = quantity;
    strncpy(newNode->tran_date, tran_date, sizeof(newNode->tran_date) - 1);
    newNode->next = NULL;
    return newNode;
}

// Helper function to free the linked list
void freeTransactionList(Transaction *head) {
    Transaction *current = head;
    while (current) {
        Transaction *temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to fetch all transactions into a linked list
Transaction *fetchTransactions(MYSQL *conn, const char *query) {
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "Result storage failed: %s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_ROW row;
    Transaction *head = NULL, *tail = NULL;

    while ((row = mysql_fetch_row(res))) {
        Transaction *newNode = createTransactionNode(
            atoi(row[0]), // tran_id
            atoi(row[1]), // item_id
            row[2],       // item_name
            row[3],       // type
            atoi(row[4]), // quantity
            row[5]        // tran_date
        );

        if (!head) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    mysql_free_result(res);
    return head;
}

// Function to display the transactions from a linked list
void displayTransactions(Transaction *head) {
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("\n%-10s | %-10s | %-20s | %-15s | %-10s | %-20s\n",
           "Tran ID", "Item ID", "Item Name", "Type", "Quantity", "Date-Time");
    printf("---------------------------------------------------------------------------------------------------\n");

    Transaction *current = head;
    while (current) {
        printf("%-10d | %-10d | %-20s | %-15s | %-10d | %-20s\n",
               current->tran_id, current->item_id, current->item_name,
               current->type, current->quantity, current->tran_date);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------------------------\n");
}

// View all transactions
void viewAllTransactions(MYSQL *conn) {
    char query[] =
        "SELECT t.tran_id, t.item_id, m.name, t.type, t.quantity, t.tran_date "
        "FROM Transaction t "
        "JOIN Master m ON t.item_id = m.item_id";

    Transaction *transactions = fetchTransactions(conn, query);
    if (transactions) {
        printf("\n--- All Transactions ---\n");
        displayTransactions(transactions);
        freeTransactionList(transactions);
    } else {
        printf("No transactions found.\n");
    }
}

// Search transactions by date
void searchTransactionsByDate(MYSQL *conn) {
    char date[11];
    printf("Enter the transaction date (YYYY-MM-DD): ");
    scanf("%s", date);

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT t.tran_id, t.item_id, m.name, t.type, t.quantity, t.tran_date "
             "FROM Transaction t "
             "JOIN Master m ON t.item_id = m.item_id "
             "WHERE DATE(t.tran_date) = '%s'", date);

    Transaction *transactions = fetchTransactions(conn, query);
    if (transactions) {
        printf("\n--- Transactions on %s ---\n", date);
        displayTransactions(transactions);
        freeTransactionList(transactions);
    } else {
        printf("No transactions found for the specified date.\n");
    }
}

void manageTransactions(MYSQL *conn) {
    int choice;
    do {
        printf("\n\033[1;34m--- Manage Transactions ---\033[0m\n");
        printf("1. View Transactions\n2. Search Transactions by Date\n\033[31m3. Return to Main Menu\033[0m\n\033[1;32mEnter your choice: \033[0m ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                refresh();
                viewAllTransactions(conn);
            break;
            case 2:
                refresh();
                searchTransactionsByDate(conn);
            break;
            case 3:
                printf("\nReturning to Main Menu...\n");
            return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}
