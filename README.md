#  Bank Client Management & Transaction System (C++)

A robust, console-based banking management system built with modern C++ focusing on data integrity, efficient memory handling, and file persistence.

---

##  Key Features

* **Client Profile Management:** 
  * Add, delete, update, and search client records dynamically.
  * Real-time formatted client tabular view.
* **Transactions Module:**
  * **Deposit Operations:** Real-time balance updating using reference semantics without data mutation risks.
  * **Withdrawal Operations:** Secure withdrawal mechanism with boundary checking.
  * **Total Balances Screen:** Aggregate bank balance calculation and tabular summary.
* **State Management & Navigation:**
  * Resilient navigation between Main Menu and Transaction submenus.
  * Input stream validation (`cin.fail` handling) to prevent infinite loops on illegal characters.
* **File Persistence & Data Storage:**
  * Auto loading/saving mechanisms (`fstream`) with line-record serialization using custom delimiters (`#//#`).

---

##  Concepts & Technologies Applied

* **Language:** C++
* **Data Structures:** `std::vector`, Custom `struct` architectures.
* **Memory & Performance:** Pass-by-Reference semantics (`&`) to prevent unnecessary object duplication.
* **File Handling:** Input/Output file streaming (`std::fstream`) with atomic save patterns.
* **Defensive Programming:** Robust input verification and delimiter-based token parsing.

---

##  How to Run

1. Clone the repository:
   ```bash
   git clone [https://github.com/abdulkaremsuliman646-collab/Bank-Management-System-CPP.git](https://github.com/abdulkaremsuliman646-collab/Bank-Management-System-CPP.git)
   
