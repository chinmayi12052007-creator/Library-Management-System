# 📚 Library Management System

A console-based Library Management System written in **C++** using structures and classes to efficiently manage books, members, and borrowing records.

---

## Features

- **Add Books** – Register books with ID, title, author, and quantity
- **Add Members** – Register library members with ID, name, and email
- **Issue Book** – Issue a book to a member (tracks availability)
- **Return Book** – Process book returns and update availability
- **Search by Title** – Case-insensitive partial title search
- **Search by Author** – Case-insensitive partial author search
- **Display All Books** – View all books with availability status
- **Display All Members** – View all members and their borrowed books

---

## Project Structure

```
library_management/
├── main.cpp       # Entry point – menu-driven interface
├── library.h      # Book, Member, BorrowRecord structs + Library class declaration
├── library.cpp    # Library class method implementations
├── Makefile       # Build configuration
└── README.md      # Project documentation
```

---

## How to Compile & Run

### Using Makefile (Linux/macOS)
```bash
make
./library_system
```

### Using g++ directly
```bash
g++ -std=c++17 -Wall -o library_system main.cpp library.cpp
./library_system
```

### On Windows (MinGW)
```bash
g++ -std=c++17 -Wall -o library_system.exe main.cpp library.cpp
library_system.exe
```

---

## Sample Usage

```
========================================
       LIBRARY MANAGEMENT SYSTEM
========================================

--- MAIN MENU ---
1. Add Book
2. Add Member
3. Issue Book
4. Return Book
5. Search Book by Title
6. Search Book by Author
7. Display All Books
8. Display All Members
0. Exit
Enter your choice: 1

Enter Book ID: B001
Enter Title: The Alchemist
Enter Author: Paulo Coelho
Enter Quantity: 3
Book added successfully!
```

---

## Concepts Used

| Concept | Usage |
|---|---|
| Structures (`struct`) | `Book`, `Member`, `BorrowRecord` data models |
| Classes (`class`) | `Library` encapsulates all operations |
| Vectors | Dynamic storage for books, members, records |
| OOP | Encapsulation, separation of interface/implementation |
| String search | Case-insensitive partial matching for search |

---

## Expected Outcome

A fully functional console application that enables:
- Book addition and inventory tracking
- Issue and return processing with availability updates
- Search by title or author for streamlined library operations
