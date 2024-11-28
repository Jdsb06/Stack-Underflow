
#include <stdio.h>
#include <stdlib.h>
#include "statistics.h"
static void refresh() {
    system("clear");
}

// Option 1: Total Items Overview
void viewTotalItems(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT COUNT(*) AS total_items FROM Master")) {
        fprintf(stderr, "Failed to fetch total items: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res && (row = mysql_fetch_row(res))) {
        printf("\nTotal Items in Inventory: %s\n", row[0]);
    }
    mysql_free_result(res);
}

// Option 2: Inventory Stock Levels
void displayInventoryStock(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *query =
        "SELECT t.item_id, m.name, "
        "SUM(CASE WHEN t.type = 'purchase' THEN t.quantity ELSE 0 END) - "
        "SUM(CASE WHEN t.type = 'sale customer' THEN t.quantity ELSE 0 END) AS current_stock "
        "FROM Transaction t "
        "JOIN Master m ON t.item_id = m.item_id "
        "GROUP BY t.item_id, m.name";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to fetch inventory stock levels: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return;
    }

    printf("\n--- Inventory Stock Levels ---\n");
    printf("%-10s | %-20s | %-10s\n", "Item ID", "Item Name", "Stock");
    printf("--------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-10s | %-20s | %-10s\n", row[0], row[1], row[2]);
    }
    printf("--------------------------------------------\n");

    mysql_free_result(res);
}

// Option 3: Inventory Trends (Graph)
// void generateInventoryTrendsGraph(MYSQL *conn) {
//     printf("\nGenerating Inventory Trends Graph...\n");
//     system("python3 ../generate_inventory_trends.py");
//     printf("Graph saved as 'inventory_trends.png'.\n");
// }

void generateInventoryTrendsGraph(int item_id) {
    char command[256];
    snprintf(command, sizeof(command), "python3 /home/jdsb/Desktop/Stack\\ Underflow/Code/generate_inventory_trends.py %d", item_id);
    printf("\nGenerating Inventory Trends Graph for Item ID: %d...\n", item_id);
    system(command);
    //printf("Graph saved as 'inventory_trends.png'.\n");
}

// Option 4: Top-Selling Items (Graph)
void generateTopSellingGraph() {
    printf("\nGenerating Top-Selling Items Graph...\n");
    system("python3 /home/jdsb/Desktop/Stack\\ Underflow/Code/generate_top_selling.py");
    // printf("Graph saved as 'top_selling_items.png'.\n");
}

// Option 5: Transactions by Type (Pie Chart)
void generateTransactionsByTypeGraph() {
    printf("\nGenerating Transactions by Type Graph...\n");
    system("python3 /home/jdsb/Desktop/Stack\\ Underflow/Code/generate_transactions_type.py");
    // printf("Graph saved as 'transactions_by_type.png'.\n");
}

// Option 6: Low Stock Alerts
void viewLowStockAlerts(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *query =
        "SELECT m.item_id, m.name, "
        "SUM(CASE WHEN t.type = 'purchase' THEN t.quantity ELSE 0 END) - "
        "SUM(CASE WHEN t.type = 'customer' THEN t.quantity ELSE 0 END) AS current_stock "
        "FROM Transaction t "
        "JOIN Master m ON t.item_id = m.item_id "
        "GROUP BY m.item_id, m.name "
        "HAVING current_stock < 10";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to fetch low stock alerts: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error storing result: %s\n", mysql_error(conn));
        return;
    }

    printf("\n--- Low Stock Alerts (Stock < 10) ---\n");
    printf("%-10s | %-20s | %-10s\n", "Item ID", "Item Name", "Stock");
    printf("--------------------------------------------\n");

    while ((row = mysql_fetch_row(res))) {
        printf("%-10s | %-20s | %-10s\n", row[0], row[1], row[2]);
    }
    printf("--------------------------------------------\n");

    mysql_free_result(res);
}

// Manage Statistics Menu
void manageStatistics(MYSQL *conn) {
    int choice;
    do {
        printf("\n\033[1;34m--- Statistics Menu ---\033[0m\n");
        printf("1. Total Items Overview\n");
        printf("2. Inventory Stock Levels\n");
        printf("3. Inventory Trends (Graph)\n");
        printf("4. Top-Selling Items (Graph)\n");
        printf("5. Transactions by Type (Pie Chart)\n");
        printf("6. Low Stock Alerts\n");
        printf("\033[31m7. Return to Main Menu\033[0m\n");
        printf("\033[1;32mEnter your choice: \033[0m ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                refresh();
                viewTotalItems(conn);
                break;
            case 2:
                refresh();
                displayInventoryStock(conn);
                break;
            case 3:
                // refresh();
                int item_id;
                printf("Enter Item ID for Inventory Trends: ");
                scanf("%d", &item_id);
                generateInventoryTrendsGraph(item_id);
            break;
            case 4:
                refresh();
                generateTopSellingGraph(conn);
                break;
            case 5:
                refresh();
                generateTransactionsByTypeGraph(conn);
                break;
            case 6:
                refresh();
                viewLowStockAlerts(conn);
                break;
            case 7:
                printf("Returning to Main Menu...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
}
