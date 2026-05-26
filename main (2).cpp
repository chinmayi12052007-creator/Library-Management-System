#include <iostream>
#include "library.h"

int main() {
    Library lib;
    int choice;

    std::cout << "========================================\n";
    std::cout << "       LIBRARY MANAGEMENT SYSTEM        \n";
    std::cout << "========================================\n";

    do {
        std::cout << "\n--- MAIN MENU ---\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Add Member\n";
        std::cout << "3. Issue Book\n";
        std::cout << "4. Return Book\n";
        std::cout << "5. Search Book by Title\n";
        std::cout << "6. Search Book by Author\n";
        std::cout << "7. Display All Books\n";
        std::cout << "8. Display All Members\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string id, title, author;
                int qty;
                std::cout << "Enter Book ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Title: ";
                std::getline(std::cin, title);
                std::cout << "Enter Author: ";
                std::getline(std::cin, author);
                std::cout << "Enter Quantity: ";
                std::cin >> qty;
                std::cin.ignore();
                lib.addBook(Book(id, title, author, qty));
                std::cout << "Book added successfully!\n";
                break;
            }
            case 2: {
                std::string id, name, email;
                std::cout << "Enter Member ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Email: ";
                std::getline(std::cin, email);
                lib.addMember(Member(id, name, email));
                std::cout << "Member added successfully!\n";
                break;
            }
            case 3: {
                std::string memberId, bookId;
                std::cout << "Enter Member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter Book ID: ";
                std::getline(std::cin, bookId);
                lib.issueBook(memberId, bookId);
                break;
            }
            case 4: {
                std::string memberId, bookId;
                std::cout << "Enter Member ID: ";
                std::getline(std::cin, memberId);
                std::cout << "Enter Book ID: ";
                std::getline(std::cin, bookId);
                lib.returnBook(memberId, bookId);
                break;
            }
            case 5: {
                std::string title;
                std::cout << "Enter Title to search: ";
                std::getline(std::cin, title);
                lib.searchByTitle(title);
                break;
            }
            case 6: {
                std::string author;
                std::cout << "Enter Author to search: ";
                std::getline(std::cin, author);
                lib.searchByAuthor(author);
                break;
            }
            case 7:
                lib.displayAllBooks();
                break;
            case 8:
                lib.displayAllMembers();
                break;
            case 0:
                std::cout << "Exiting... Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
