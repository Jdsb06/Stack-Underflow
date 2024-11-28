import mysql.connector
import matplotlib.pyplot as plt
import sys
import os

def generate_transactions_by_type():
    script_directory = os.path.dirname(os.path.realpath(__file__))
    # Connect to MySQL
    conn = mysql.connector.connect(
        host="localhost",
        user="root",
        password="",
        database="StackUnderflow"
    )
    cursor = conn.cursor()

    # Fetch transactions by type
    query = """
        SELECT t.type, COUNT(*) AS transaction_count
        FROM Transaction t
        GROUP BY t.type
    """
    cursor.execute(query)
    data = cursor.fetchall()

    if not data:
        print("No transaction data found.")
        return

    # Prepare data for the graph
    types = [row[0] for row in data]
    counts = [row[1] for row in data]

    # Plot the graph
    plt.figure(figsize=(8, 8))
    plt.pie(counts, labels=types, autopct='%1.1f%%', startangle=140, colors=['blue', 'orange'])
    plt.title("Transactions by Type")
    graph_path = os.path.join(script_directory, "transaction_type.png")
    plt.savefig(graph_path)


    print("Graph saved as 'transactions_by_type.png'.")

generate_transactions_by_type()
