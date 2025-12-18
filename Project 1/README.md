# Movie Theater Management System

## Overview

This project is a comprehensive, command-line-based Movie Theater Management System written in C++. It provides a dual-interface system for both standard users and administrators, allowing for a wide range of functionalities from booking tickets to managing the movie database. The system is built using Object-Oriented Programming (OOP) principles and uses local text files for data persistence.

## Features

The system offers a variety of features split between two main roles: User and Admin.

### User Features
- **View Movie List**: Browse the current list of movies showing at the theater.
- **Book Tickets**: Book a ticket for a specific movie, including an interactive seat selection map.
- **Submit Reviews**: Post a multi-word review and a rating (1-5) for a movie. Only users who have purchased a ticket can submit a review.
- **View All Reviews**: Read all reviews and ratings submitted by other users.
- **View Top-Rated Movies**: See a ranked list of movies based on their average user rating.
- **Search & Manage Tickets**:
  - Search for a booked ticket using a CNIC.
  - Cancel a previously booked ticket.
  - View a complete list of all tickets currently booked.
- **About Us**: Read a short description of the theater's mission.

### Admin Features
- **Secure Access**: Admin functionalities are protected by a password.
- **Movie Database Management**:
  - Add new movies to the theater's listings.
  - Remove existing movies.
  - The movie list is dynamically loaded, so changes are reflected in the user menu immediately.
- **View Customer Data**: Display a list of all customers who have booked tickets.
- **Revenue Reports**: Generate a simple revenue report based on the total number of tickets sold.

## System Design and Architecture

The application is architected around core OOP concepts to ensure modularity and scalability.

- **Class Structure**:
  - **`movie`**: A base class that holds static data common to all movies, such as the list of available films and ticket counts.
  - **`handlingFiles`**: A key class that inherits from `movie` and manages all file I/O operations, centralizing the logic for reading from and writing to data files.
  - **User-Facing Classes**: `BookTickets`, `FilmReviews`, `SearchTicket`, `CancelTicket`, and `ShowAllTickets` encapsulate specific user actions and inherit functionality from `handlingFiles`.
  - **`Admin`**: A powerful class that manages administrative tasks. It inherits from `movie` and implements the `motiveTheater` abstract class.
  - **Utility Classes (Composition)**: The system uses composition by integrating helper classes like `SeatManager`, `PaymentGateway`, `NotificationService`, `LoyaltyProgram`, and `AnalyticsDashboard` to handle specialized tasks such as seat mapping, payment simulation, and analytics.

- **Data Persistence**:
  The system uses simple tab-separated text files (`.txt`) to persist data:
  - `movies.txt`: Stores the list of available movies.
  - `tickets.txt`: A log of all tickets booked.
  - `reviews.txt`: Contains all user-submitted reviews and ratings.
  - `customers.txt`: Records information for users who have booked tickets.

## Recent Code Enhancements and Refinements

The codebase in `first.cpp` recently underwent significant refactoring and bug fixing to improve robustness, functionality, and maintainability.

1.  **Robust File Handling**: The file I/O logic was completely overhauled. The system now safely handles spaces and special characters in movie titles, customer names, and reviews by using `getline` and `stringstream` for parsing. This fixes critical bugs that caused data corruption when reading from files.

2.  **Dynamic Movie Management**: The previously hardcoded movie list was replaced with a dynamic system. Movies are now loaded from `movies.txt` at startup. This allows administrators to add or remove movies, with changes immediately available to all users without needing to recompile the program.

3.  **Full-Text Reviews**: The review system was upgraded to accept multi-word, full-sentence reviews, providing a more expressive and useful feedback mechanism.

4.  **Bug Fixes and Logic Correction**:
    - Corrected a logical error where the system would always show the total ticket capacity (100) instead of the actual number of *available* tickets.
    - Streamlined the class structure and dependencies for better code clarity.

5.  **Code Cleanup**: As requested, all comments were removed from the source code to provide a clean and unobstructed view of the implementation.

## How to Compile and Run

This is a C++ application and requires a C++ compiler. The use of `<conio.h>` makes it best suited for a Windows environment.

1.  **Compiler**: A C++ compiler like g++ (available via MinGW on Windows) or the MSVC compiler included with Visual Studio is required.

2.  **Compile**: Open a terminal or command prompt and navigate to the project directory. Run the following command to compile the code:
    ```sh
    g++ first.cpp -o theater_system.exe
    ```

3.  **Run**: Execute the compiled program from the terminal:
    ```sh
    ./theater_system.exe
    ```
    The application will start, and the main menu will be displayed.
