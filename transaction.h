// #ifndef TRANSACTION_H
// #define TRANSACTION_H

// #include <mysql/mysql.h>

// void manageTransactions(MYSQL *conn);

// #endif
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <mysql/mysql.h>


void manageTransactions(MYSQL *conn);


void viewAllTransactions(MYSQL *conn);


void searchTransactionsByDate(MYSQL *conn);


void addTransaction(MYSQL *conn);

#endif 

