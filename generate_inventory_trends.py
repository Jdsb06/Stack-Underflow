

import mysql.connector
import matplotlib.pyplot as plt
import sys
import os
def generate_inventory_trends(item_id):
    script_directory = os.path.dirname(os.path.realpath(__file__))
    # Connect to MySQL
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="StackUnderflow"
    )
    cursor = conn.cursor()

    # Fetch inventory trends data
    query = """
        SELECT DATE(tran_date) AS tran_date,
               SUM(CASE WHEN type = 'purchase' THEN quantity ELSE -quantity END) AS net_stock_change
        FROM Transaction
        WHERE item_id = %s
        GROUP BY DATE(tran_date)
        ORDER BY DATE(tran_date)
    """
    cursor.execute(query, (item_id,))
    data = cursor.fetchall()

    if not data:
        print(f"No trends found for Item ID {item_id}.")
        return

    # Prepare data for the graph
    dates = [row[0] for row in data]
    stock_changes = [row[1] for row in data]

    # Plot the graph
    plt.figure(figsize=(10, 6))
    plt.plot(dates, stock_changes, marker='o', linestyle='-', color='b')
    plt.title(f"Inventory Trends for Item ID {item_id}")
    plt.xlabel("Date")
    plt.ylabel("Net Stock Change")
    plt.grid(True)
    graph_path = os.path.join(script_directory, "inventory_trends.png")
    plt.savefig(graph_path)

    print("Graph saved as 'inventory_trends.png'.")

# Main script execution
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Error: Item ID is required as a command-line argument.")
        sys.exit(1)
    try:
        item_id = int(sys.argv[1])  # Get item_id from command-line arguments
        generate_inventory_trends(item_id)
    except ValueError:
        print("Error: Invalid Item ID. Please provide a valid integer.")
