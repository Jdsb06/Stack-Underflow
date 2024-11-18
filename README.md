# Stack-Underflow
# Warehouse Management System for Online Shopping

The **Warehouse Management System (WMS)** is a software application designed to streamline and optimize warehouse operations for online shopping platforms. It ensures efficient management of inventory, labour, and order processing, facilitating seamless integration between warehouse activities and customer orders.

## Project Objectives
- Create a robust and user-friendly menu-driven system using C programming.
- Maintain data persistence through file handling for long-term storage and retrieval.
- Implement a structured and modular database for managing inventory, orders, and labour.
- Enhance operational efficiency by automating repetitive tasks and providing real-time insights.

## Core Features
### 1. User Management
- Login and registration system for admins and users.
- Role-based access control for secure operations.

### 2. Inventory Management
- Add, update, and delete item records.
- View inventory details, including item categories, quantities, and pricing.
- Track stock levels with statistics for effective decision-making.

### 3. Order Processing
- Place and record customer orders.
- Maintain order history with item and user details.

### 4. Labour Management
- Maintain a database of labour records, including roles, shifts, and contact details.
- Track labour attendance and assign tasks.
- Generate reports for attendance and task completion.

### 5. Statistics and Reporting
- Provide insights into inventory usage and order trends.
- Generate reports to analyze operational efficiency.

## Technical Details
- **Programming Language:** C
- **Database:** MySQL for relational data storage and management.
- **Data Structures:** Use of structures and linked lists for efficient in-memory data management.
- **File Handling:** Persistent storage using `.txt` files for backup and retrieval.
- **Foreign Key Relations:** Ensure data consistency between tables for users, items, orders, and labour.
- **Interface:** Command-line interface for menu-driven interactions.

## Key Deliverables
- A functional WMS program with at least 10 menu options.
- Database schema with minimum tables linked through foreign keys.
- Modular codebase with a Makefile for compilation.
- README file with usage instructions and documentation.

## How to Run the Program
1. Clone the repository to your local machine.
2. Compile the program using the provided `Makefile`:
   ```bash
   make


