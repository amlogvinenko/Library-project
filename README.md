 Система управления личной библиотекой

Консольное приложение на C++ для управления личной библиотекой: книги, пользователи, выдача и возврат, сохранение данных в файл.

## Требования

- C++17
- CMake 3.10+
- Компилятор (Visual Studio 2022 / MinGW / Clang и т.п.)

## Структура проекта

- `src/` — исходники (`Book.*`, `User.*`, `Library.*`, `main.cpp`)
- `data/library_data.txt` — файл с исходными данными
- `CMakeLists.txt` — файл конфигурации сборки
- `build/` — каталог для сборки (создаётся вручную)

## Сборка и запуск (Windows, PowerShell, Visual Studio)
mkdir build
cd build
cmake ..
cmake --build . --config Release
cd ..
.\build\Release\library.exe
## Формат файла данных

Файл `data/library_data.txt` должен иметь вид:

BOOK
Title: ...
Author: ...
Year: ...
ISBN: ...
Available: yes
BorrowedBy: ...

---USERS---

USER
Name: ...
UserID: USR_001
BorrowedBooks: ...
MaxBooks: 3
## Основные функции программы

- Просмотр всех книг и пользователей
- Добавление книги
- Регистрация пользователя
- Выдача и возврат книги
- Поиск книги по ISBN
- Просмотр профиля пользователя
- Сохранение текущего состояния в `data/library_data.txt`