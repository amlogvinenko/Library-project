#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>

Library::Library(const std::string& dataFile) : dataFile(dataFile) {
    loadFromFile();
}

void Library::addBook(const Book& book) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getISBN() == book.getISBN()) {
            throw std::runtime_error("ISBN существует");
        }
    }
    books.push_back(book);
}

void Library::addUser(const User& user) {
    users.push_back(user);
}

void Library::borrowBook(const std::string& userName, const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    User* user = findUserByName(userName);
    
    if (book == nullptr) throw std::runtime_error("Книга не найдена");
    if (user == nullptr) throw std::runtime_error("Пользователь не найден");
    if (!user->canBorrowMore()) throw std::runtime_error("Лимит достигнут");
    
    book->borrowBook(userName);
    user->addBook(isbn);
}

void Library::returnBook(const std::string& isbn) {
    Book* book = findBookByISBN(isbn);
    if (book == nullptr) throw std::runtime_error("Книга не найдена");
    
    std::string userName = book->getBorrowedBy();
    User* user = findUserByName(userName);
    
    book->returnBook();
    if (user != nullptr) {
        user->removeBook(isbn);
    }
}

Book* Library::findBookByISBN(const std::string& isbn) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getISBN() == isbn) {
            return &books[i];
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return &users[i];
        }
    }
    return nullptr;
}

void Library::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "Каталог пуст" << std::endl;
        return;
    }
    
    std::cout << "\n=== КАТАЛОГ КНИГ ===" << std::endl;
    for (int i = 0; i < books.size(); i++) {
        std::cout << "\nКнига #" << (i + 1) << ":" << std::endl;
        books[i].displayInfo();
    }
}

void Library::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "Нет зарегистрированных пользователей" << std::endl;
        return;
    }
    
    std::cout << "\n=== СПИСОК ПОЛЬЗОВАТЕЛЕЙ ===" << std::endl;
    for (int i = 0; i < users.size(); i++) {
        std::cout << "\nПользователь #" << (i + 1) << ":" << std::endl;
        users[i].displayProfile();
    }
}

void Library::saveToFile() {
    std::ofstream file(dataFile);
    if (!file.is_open()) throw std::runtime_error("Ошибка записи");
    
    for (int i = 0; i < books.size(); i++) {
        file << "BOOK\n";
        file << "Title: " << books[i].getTitle() << "\n";
        file << "Author: " << books[i].getAuthor() << "\n";
        file << "Year: " << books[i].getYear() << "\n";
        file << "ISBN: " << books[i].getISBN() << "\n";
        file << "Available: " << (books[i].getIsAvailable() ? "yes" : "no") << "\n";
        file << "BorrowedBy: " << books[i].getBorrowedBy() << "\n\n";
    }
    
    file << "---USERS---\n\n";
    
    for (int i = 0; i < users.size(); i++) {
        file << "USER\n";
        file << "Name: " << users[i].getName() << "\n";
        file << "UserID: " << users[i].getUserId() << "\n";
        file << "BorrowedBooks: ";
        
        std::vector<std::string> borrowedBooks = users[i].getBorrowedBooks();
        for (int j = 0; j < borrowedBooks.size(); j++) {
            file << borrowedBooks[j];
            if (j < borrowedBooks.size() - 1) file << "|";
        }
        file << "\n";
        file << "MaxBooks: " << users[i].getMaxBooksAllowed() << "\n\n";
    }
    file.close();
}

void Library::loadFromFile() {
    std::ifstream file(dataFile);
    if (!file.is_open()) return;
    
    std::string line;
    bool inUserSection = false;
    
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        
        if (line == "---USERS---") {
            inUserSection = true;
            continue;
        }
        
        if (!inUserSection && line == "BOOK") {
            std::string title, author, isbn, borrowedBy;
            int year = 0;
            bool isAvailable = true;
            
            while (std::getline(file, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back();
                if (line.empty()) break;
                
                int pos = line.find(": ");
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 2);
                    
                    if (key == "Title") title = value;
                    else if (key == "Author") author = value;
                    else if (key == "Year") year = std::stoi(value);
                    else if (key == "ISBN") isbn = value;
                    else if (key == "Available") isAvailable = (value == "yes");
                    else if (key == "BorrowedBy") borrowedBy = value;
                }
            }
            
            try {
                Book book(title, author, year, isbn);
                if (!isAvailable && !borrowedBy.empty()) {
                    book.borrowBook(borrowedBy);
                }
                books.push_back(book);
            } catch (...) {}
        }
        
        if (inUserSection && line == "USER") {
            std::string name, userId, borrowedBooksStr;
            int maxBooks = 3;
            
            while (std::getline(file, line)) {
                if (!line.empty() && line.back() == '\r') line.pop_back();
                if (line.empty()) break;
                
                int pos = line.find(": ");
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 2);
                    
                    if (key == "Name") name = value;
                    else if (key == "UserID") userId = value;
                    else if (key == "BorrowedBooks") borrowedBooksStr = value;
                    else if (key == "MaxBooks") maxBooks = std::stoi(value);
                }
            }
            
            User user(name, userId, maxBooks);
            if (!borrowedBooksStr.empty()) {
                std::stringstream ss(borrowedBooksStr);
                std::string isbn;
                while (std::getline(ss, isbn, '|')) {
                    if (!isbn.empty()) user.addBook(isbn);
                }
            }
            users.push_back(user);
        }
    }
    file.close();
}
