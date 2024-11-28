// #ifndef TRANSACTION_H
// #define TRANSACTION_H
//
// #include <mysql/mysql.h>
//
// void manageTransactions(MYSQL *conn);
// void viewAllTransactions(MYSQL *conn);
// void searchTransactionsByDate(MYSQL *conn);
//
// #endif


#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <mysql/mysql.h>

typedef struct Transaction {
    int tran_id;
    int item_id;
    char item_name[50];
    char type[20];
    int quantity;
    char tran_date[20];
    struct Transaction *next;
} Transaction;

Transaction *createTransactionNode(int tran_id, int item_id, const char *item_name, const char *type, int quantity, const char *tran_date);
void freeTransactionList(Transaction *head);
Transaction *fetchTransactions(MYSQL *conn, const char *query);
void displayTransactions(Transaction *head);
void viewAllTransactions(MYSQL *conn);
void searchTransactionsByDate(MYSQL *conn);
void manageTransactions(MYSQL *conn);

#endif
