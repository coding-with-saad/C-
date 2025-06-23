
# 🎬 Movie Theater Management System – C++ Console Project

This is a **C++ console-based Movie Theater Management System** that allows users to book tickets, submit reviews, and interact with a structured admin panel. The project demonstrates core Object-Oriented Programming principles along with file handling for data persistence.

---

## ✅ C++ Concepts Used in the Project

- **Classes & Objects**: Each component (e.g., booking, reviews, admin, users) is modeled using separate classes.
- **Inheritance**: Common file handling and movie-related functionality is inherited by multiple classes.
- **Polymorphism**: An abstract base class (`motiveTheater`) defines a virtual method to enforce implementation in derived classes.
- **Encapsulation**: Data members are kept private and accessed through public methods for secure data flow.
- **File Handling**: Uses `fstream` to read/write tickets, customer data, and reviews to `.txt` files.
- **Static Members**: Tracks total and available tickets using static variables.
- **STL Containers**: `vector` is used for seat layout management, `map` is used for the loyalty point system.
- **Switch Case Menus**: Interactive menus for user and admin navigation using switch-case logic.

---

This project serves as a hands-on demonstration of real-world system design using fundamental and advanced C++ programming concepts.
