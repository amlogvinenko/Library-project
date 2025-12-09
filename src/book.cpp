#include "Book.h"
#include <iostream>
#include <stdexcept>
#include <ctime>

Book::Book(const std::string& title, const std::string& author, int year, const std::string& isbn)
    : title(title), author(author), year(year), isbn(isbn), isAvailable(true), borrowedBy("") {
    
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;
    
    if (year < 1450 || year > currentYear) {
        throw std::invalid_argument("Год должен быть между 1450 и " + std::to_string(currentYear));
    }
    
    if (isbn.empty()) {
        throw std::invalid_argument("ISBN не может быть пустым");
    }
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

std::string Book::getISBN() const {
    return isbn;
}

bool Book::getIsAvailable() const {
    return isAvailable;
}

std::string Book::getBorrowedBy() const {
    return borrowedBy;
}

void Book::borrowBook(const std::string& userName) {
    if (!isAvailable) {
        throw std::runtime_error("Книга уже взята");
    }
    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook() {
    if (isAvailable) {
        throw std::runtime_error("Книга не была взята");
    }
    isAvailable = true;
    borrowedBy = "";
}

void Book::displayInfo() const {
    std::cout << "Название: " << title << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Статус: " << (isAvailable ? "Доступна" : "Выдана") << std::endl;
    if (!isAvailable) {
        std::cout << "Взята пользователем: " << borrowedBy << std::endl;
    }
}
