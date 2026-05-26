#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>

// ─────────────────────────────────────────
//  Structures
// ─────────────────────────────────────────

struct Book {
    std::string bookId;
    std::string title;
    std::string author;
    int totalQuantity;
    int availableQuantity;

    Book(std::string id, std::string t, std::string a, int qty)
        : bookId(id), title(t), author(a),
          totalQuantity(qty), availableQuantity(qty) {}

    void display() const;
};

struct Member {
    std::string memberId;
    std::string name;
    std::string email;
    std::vector<std::string> borrowedBookIds;

    Member(std::string id, std::string n, std::string e)
        : memberId(id), name(n), email(e) {}

    void display() const;
};

struct BorrowRecord {
    std::string memberId;
    std::string bookId;

    BorrowRecord(std::string mid, std::string bid)
        : memberId(mid), bookId(bid) {}
};

// ─────────────────────────────────────────
//  Library Class
// ─────────────────────────────────────────

class Library {
private:
    std::vector<Book>         books;
    std::vector<Member>       members;
    std::vector<BorrowRecord> borrowRecords;

    Book*   findBook(const std::string& bookId);
    Member* findMember(const std::string& memberId);

public:
    void addBook(const Book& book);
    void addMember(const Member& member);

    void issueBook(const std::string& memberId, const std::string& bookId);
    void returnBook(const std::string& memberId, const std::string& bookId);

    void searchByTitle(const std::string& title) const;
    void searchByAuthor(const std::string& author) const;

    void displayAllBooks()   const;
    void displayAllMembers() const;
};

#endif // LIBRARY_H
