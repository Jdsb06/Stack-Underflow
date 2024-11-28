import mysql.connector
import matplotlib.pyplot as plt
import os

def generate_top_selling():
    script_directory = os.path.dirname(os.path.realpath(__file__))
    # Connect to MySQL
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="StackUnderflow"
    )
    cursor = conn.cursor()

    # Fetch top-selling items dataCode
    query = """
        SELECT m.name, SUM(t.quantity) AS total_sales
        FROM Transaction t
        JOIN Master m ON t.item_id = m.item_id
        WHERE t.type = 'customer'
        GROUP BY m.name
        ORDER BY total_sales DESC
        LIMIT 5
    """
    cursor.execute(query)
    data = cursor.fetchall()

    if not data:
        print("No sales data found.")
        return

    # Prepare data for the graph
    item_names = [row[0] for row in data]
    total_sales = [row[1] for row in data]

    # Plot the graph
    plt.figure(figsize=(10, 6))
    plt.bar(item_names, total_sales, color='green')
    plt.title("Top-Selling Items")
    plt.xlabel("Item Name")
    plt.ylabel("Total Sales")
    graph_path = os.path.join(script_directory, "top_selling.png")
    plt.savefig(graph_path)

    print("Graph saved as 'top_selling_items.png'.")

generate_top_selling()
