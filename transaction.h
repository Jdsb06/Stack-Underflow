#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <mysql/mysql.h>

void manageTransactions(MYSQL *conn);
void viewAllTransactions(MYSQL *conn);
void searchTransactionsByDate(MYSQL *conn);

#endif
