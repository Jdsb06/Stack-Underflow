#ifndef STATISTICS_H
#define STATISTICS_H

#include <mysql/mysql.h>

void manageStatistics(MYSQL *conn);
void viewTotalItems(MYSQL *conn);
void displayInventoryStock(MYSQL *conn);
void generateInventoryTrendsGraph(int item_id);
void generateTopSellingGraph();
void generateTransactionsByTypeGraph();
void viewLowStockAlerts(MYSQL *conn);

#endif
