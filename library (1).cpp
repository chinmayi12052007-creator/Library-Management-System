#include "library.h"
#include <iostream>
#include <algorithm>
#include <cctype>

// ─────────────────────────────────────────
//  Helper: case-insensitive substring check
// ─────────────────────────────────────────

static std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

// ─────────────────────────────────────────
//  Book display
// ─────────────────────────────────────────

void Book::display() const {
    std::cout << "  ID       : " << bookId          << "\n"
              << "  Title    : " << title            << "\n"
              << "  Author   : " << author           << "\n"
              << "  Total    : " << totalQuantity    << "\n"
              << "  Available: " << availableQuantity << "\n";
}

// ─────────────────────────────────────────
//  Member display
// ─────────────────────────────────────────

void Member::display() const {
    std::cout << "  ID    : " << memberId << "\n"
              << "  Name  : " << name     << "\n"
              << "  Email : " << email    << "\n"
              << "  Borrowed Books: ";
    if (borrowedBookIds.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& id : borrowedBookIds)
            std::cout << id << " ";
        std::cout << "\n";
    }
}

// ─────────────────────────────────────────
//  Private helpers
// ─────────────────────────────────────────

Book* Library::findBook(const std::string& bookId) {
    for (auto& b : books)
        if (b.bookId == bookId) return &b;
    return nullptr;
}

Member* Library::findMember(const std::string& memberId) {
    for (auto& m : members)
        if (m.memberId == memberId) return &m;
    return nullptr;
}

// ─────────────────────────────────────────
//  Add operations
// ─────────────────────────────────────────

void Library::addBook(const Book& book) {
    // If book already exists, increase quantity
    Book* existing = findBook(book.bookId);
    if (existing) {
        existing->totalQuantity     += book.totalQuantity;
        existing->availableQuantity += book.availableQuantity;
        std::cout << "Book already exists. Quantity updated.\n";
        return;
    }
    books.push_back(book);
}

void Library::addMember(const Member& member) {
    if (findMember(member.memberId)) {
        std::cout << "Member with ID " << member.memberId << " already exists.\n";
        return;
    }
    members.push_back(member);
}

// ─────────────────────────────────────────
//  Issue Book
// ─────────────────────────────────────────

void Library::issueBook(const std::string& memberId, const std::string& bookId) {
    Member* member = findMember(memberId);
    if (!member) {
        std::cout << "Error: Member ID '" << memberId << "' not found.\n";
        return;
    }

    Book* book = findBook(bookId);
    if (!book) {
        std::cout << "Error: Book ID '" << bookId << "' not found.\n";
        return;
    }

    if (book->availableQuantity <= 0) {
        std::cout << "Error: No copies of '" << book->title << "' are currently available.\n";
        return;
    }

    // Check if member already has this book
    for (const auto& id : member->borrowedBookIds) {
        if (id == bookId) {
            std::cout << "Error: Member already has this book issued.\n";
            return;
        }
    }

    book->availableQuantity--;
    member->borrowedBookIds.push_back(bookId);
    borrowRecords.emplace_back(memberId, bookId);

    std::cout << "Book '" << book->title << "' issued to " << member->name << " successfully.\n";
}

// ─────────────────────────────────────────
//  Return Book
// ─────────────────────────────────────────

void Library::returnBook(const std::string& memberId, const std::string& bookId) {
    Member* member = findMember(memberId);
    if (!member) {
        std::cout << "Error: Member ID '" << memberId << "' not found.\n";
        return;
    }

    Book* book = findBook(bookId);
    if (!book) {
        std::cout << "Error: Book ID '" << bookId << "' not found.\n";
        return;
    }

    // Remove from member's borrowed list
    auto it = std::find(member->borrowedBookIds.begin(),
                        member->borrowedBookIds.end(), bookId);
    if (it == member->borrowedBookIds.end()) {
        std::cout << "Error: This book was not issued to member " << member->name << ".\n";
        return;
    }

    member->borrowedBookIds.erase(it);
    book->availableQuantity++;

    // Remove borrow record
    borrowRecords.erase(
        std::remove_if(borrowRecords.begin(), borrowRecords.end(),
            [&](const BorrowRecord& r){
                return r.memberId == memberId && r.bookId == bookId;
            }),
        borrowRecords.end());

    std::cout << "Book '" << book->title << "' returned by " << member->name << " successfully.\n";
}

// ─────────────────────────────────────────
//  Search operations
// ─────────────────────────────────────────

void Library::searchByTitle(const std::string& title) const {
    std::string query = toLower(title);
    bool found = false;
    std::cout << "\n--- Search Results (Title: \"" << title << "\") ---\n";
    for (const auto& b : books) {
        if (toLower(b.title).find(query) != std::string::npos) {
            b.display();
            std::cout << "  --------------------------------\n";
            found = true;
        }
    }
    if (!found) std::cout << "No books found with that title.\n";
}

void Library::searchByAuthor(const std::string& author) const {
    std::string query = toLower(author);
    bool found = false;
    std::cout << "\n--- Search Results (Author: \"" << author << "\") ---\n";
    for (const auto& b : books) {
        if (toLower(b.author).find(query) != std::string::npos) {
            b.display();
            std::cout << "  --------------------------------\n";
            found = true;
        }
    }
    if (!found) std::cout << "No books found by that author.\n";
}

// ─────────────────────────────────────────
//  Display all
// ─────────────────────────────────────────

void Library::displayAllBooks() const {
    std::cout << "\n========== ALL BOOKS (" << books.size() << ") ==========\n";
    if (books.empty()) { std::cout << "No books in the library.\n"; return; }
    for (const auto& b : books) {
        b.display();
        std::cout << "  --------------------------------\n";
    }
}

void Library::displayAllMembers() const {
    std::cout << "\n========== ALL MEMBERS (" << members.size() << ") ==========\n";
    if (members.empty()) { std::cout << "No members registered.\n"; return; }
    for (const auto& m : members) {
        m.display();
        std::cout << "  --------------------------------\n";
    }
}
