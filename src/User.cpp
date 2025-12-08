#include "User.h"
#include <iostream>
#include <algorithm>

User::User(const std::string& name, const std::string& userId, int maxBooksAllowed)
    : name(name), userId(userId), maxBooksAllowed(maxBooksAllowed) {}

std::string User::getName() const {
    return name;
}

std::string User::getUserId() const {
    return userId;
}

std::vector<std::string> User::getBorrowedBooks() const {
    return borrowedBooks;
}

int User::getMaxBooksAllowed() const {
    return maxBooksAllowed;
}

bool User::canBorrowMore() const {
    return borrowedBooks.size() < static_cast<size_t>(maxBooksAllowed);
}

void User::addBook(const std::string& isbn) {
    borrowedBooks.push_back(isbn);
}

void User::removeBook(const std::string& isbn) {
    auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
    }
}

void User::displayProfile() const {
    std::cout << "Фамилия: " << name << std::endl;
    std::cout << "ID: " << userId << std::endl;
    std::cout << "Взятых книг: " << borrowedBooks.size() << "/" << maxBooksAllowed << std::endl;
    if (!borrowedBooks.empty()) {
        std::cout << "ISBN взятых книг: ";
        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            std::cout << borrowedBooks[i];
            if (i < borrowedBooks.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}
