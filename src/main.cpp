#include <iostream>
#include <limits>
#include "Library.h"

void displayMenu() {
    std::cout << "\n=== БИБЛИОТЕКА ===" << std::endl;
    std::cout << "1. Просмотреть все книги" << std::endl;
    std::cout << "2. Просмотреть всех пользователей" << std::endl;
    std::cout << "3. Добавить новую книгу" << std::endl;
    std::cout << "4. Зарегистрировать пользователя" << std::endl;
    std::cout << "5. Выдать книгу пользователю" << std::endl;
    std::cout << "6. Принять книгу от пользователя" << std::endl;
    std::cout << "7. Поиск книги по ISBN" << std::endl;
    std::cout << "8. Просмотреть профиль пользователя" << std::endl;
    std::cout << "9. Сохранить данные в файл" << std::endl;
    std::cout << "10. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    #ifdef _WIN32 
        system("chcp 65001 > nul");
    #endif
    Library library("data/library_data.txt");
    
    while (true) {
        displayMenu();
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка: Введите число" << std::endl;
            clearInput();
            continue;
        }
        clearInput();
        
        try {
            if (choice == 1) {
                library.displayAllBooks();
            } else if (choice == 2) {
                library.displayAllUsers();
            } else if (choice == 3) {
                std::string title, author, isbn;
                int year;
                
                std::cout << "Введите название книги: ";
                std::getline(std::cin, title);
                std::cout << "Введите автора: ";
                std::getline(std::cin, author);
                std::cout << "Введите год издания: ";
                if (!(std::cin >> year)) {
                    std::cout << "Ошибка: Неверный формат года" << std::endl;
                    clearInput();
                    continue;
                }
                clearInput();
                std::cout << "Введите ISBN: ";
                std::getline(std::cin, isbn);
                
                Book book(title, author, year, isbn);
                library.addBook(book);
                std::cout << "Успешно: Книга добавлена" << std::endl;
            } else if (choice == 4) {
                std::string name, userId;
                int maxBooks;
                
                std::cout << "Введите фамилию пользователя: ";
                std::getline(std::cin, name);
                std::cout << "Введите ID пользователя (например, USR_001): ";
                std::getline(std::cin, userId);
                std::cout << "Введите максимум книг (по умолчанию 3): ";
                if (!(std::cin >> maxBooks)) {
                    maxBooks = 3;
                }
                clearInput();
                
                User user(name, userId, maxBooks);
                library.addUser(user);
                std::cout << "Успешно: Пользователь зарегистрирован" << std::endl;
            } else if (choice == 5) {
                std::string userName, isbn;
                
                std::cout << "Введите фамилию пользователя: ";
                std::getline(std::cin, userName);
                std::cout << "Введите ISBN книги: ";
                std::getline(std::cin, isbn);
                
                library.borrowBook(userName, isbn);
                std::cout << "Успешно: Книга выдана пользователю" << std::endl;
            } else if (choice == 6) {
                std::string isbn;
                
                std::cout << "Введите ISBN книги: ";
                std::getline(std::cin, isbn);
                
                library.returnBook(isbn);
                std::cout << "Успешно: Книга возвращена" << std::endl;
            } else if (choice == 7) {
                std::string isbn;
                
                std::cout << "Введите ISBN: ";
                std::getline(std::cin, isbn);
                
                Book* book = library.findBookByISBN(isbn);
                if (book != nullptr) {
                    std::cout << "\nНайдена книга:" << std::endl;
                    book->displayInfo();
                } else {
                    std::cout << "Ошибка: Книга не найдена" << std::endl;
                }
            } else if (choice == 8) {
                std::string name;
                
                std::cout << "Введите фамилию пользователя: ";
                std::getline(std::cin, name);
                
                User* user = library.findUserByName(name);
                if (user != nullptr) {
                    std::cout << "\nПрофиль пользователя:" << std::endl;
                    user->displayProfile();
                } else {
                    std::cout << "Ошибка: Пользователь не найден" << std::endl;
                }
            } else if (choice == 9) {
                library.saveToFile();
                std::cout << "Успешно: Данные сохранены" << std::endl;
            } else if (choice == 10) {
                std::cout << "Выход из программы" << std::endl;
                break;
            } else {
                std::cout << "Ошибка: Неверный выбор" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }
    
    return 0;
}
