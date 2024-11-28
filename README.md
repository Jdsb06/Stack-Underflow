# Warehouse Management System for Online Shopping

This Warehouse Management System (WMS) is designed for managing inventory, processing purchase and customer orders, and maintaining transaction history in an online shopping context. The system leverages a MySQL database for backend data management and provides functionality for order tracking, stock monitoring, and generating statistical insights.

---

## **Project Objectives**
- **Efficient Inventory Management**: Track inventory in real time, manage stock levels, and process orders seamlessly.
- **Order Handling**: Support for both purchase orders from suppliers and customer orders.
- **Data Integrity**: Ensure proper handling of dependencies using MySQL constraints and logical checks.
- **Comprehensive Statistics**: Generate insights into inventory trends, top-selling items, and transaction breakdowns.

---

## **Core Features**
- **User Management**: Admin users can log in and manage the system securely.
- **Inventory Management**:
  - Add, update, and delete items.
  - View current stock levels.
- **Order Processing**:
  - Manage purchase orders from suppliers.
  - Manage customer orders.
- **Transaction History**:
  - Maintain and view transaction details for inventory changes.
- **Statistics and Graphs**:
  - Generate inventory trends, top-selling items, and transaction type graphs.

---

## **Technical Details**
### **Programming Languages**
- **C**: Core logic and integration with MySQL database.
- **Python**: For generating graphs and visualizations using Matplotlib.

### **Database**
- **MySQL**: Backend database for managing inventory, orders, and transactions.

### **Libraries Used**
1. **MySQL Connector C Library** (`-lmysqlclient`)
2. **Matplotlib (Python)**
3. **Python MySQL Connector**

---

## **Key Deliverables**
1. **Functional Modules**:
   - `master.c`: Inventory management.
   - `user.c`: Admin login and user management.
   - `order_c.c` and `order_p.c`: Customer and purchase order handling.
   - `transaction.c`: Maintain transaction history.
   - `statistics.c`: Generate statistical insights with graphs.
2. **Python Scripts**:
   - `generate_inventory_trends.py`
   - `generate_top_selling.py`
   - `generate_transactions_type.py`

---

## **Roles**
- **BT2024154(Kkshiteej Tiwari) & BT2024217(Ridwan Umar)**:
  - Modules: `master.c`, `user.c`
- **BT2024186(Aadyant Neog) & BT2024098 (Srijan Gupta)**:
  - Modules: `order_c.c`, `order_p.c`
- **BT2024128 (Soham Banerjee)**:
  - Module: `transaction.c`
- **IMT2024022 (Jashandeep Singh Bedi)**:
  - Module: `statistics.c`

---

## **How to Run the Project**
Create table in mysql (commands are given in rdbms_StackUnderflow.sql)
Insert data in mysql (commands given in Data_Table.txt)
1. Download repository:
   ```bash
   git clone https://github.com/Jdsb06/Stack-Underflow/
2. Compile the Project:
   ```bash
   make
3. Run the Project:
   ```bash
   ./wms
4. Clean Build Files:
   ```bash
   make clean
