#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Struct for Book
struct Book {
    string title;
    string author;
    string isbn;
    int quantity;
};

// Struct for User
struct User {
    string name;
    string userID;
    vector<string> borrowedBooks;
};

// Book Inventory and User Records
vector<Book> books;
vector<User> users;

// Function to Preload Books
void preloadBooks() {
    books.push_back({"The Alchemist", "Paulo Coelho", "ISBN001", 5});
    books.push_back({"1984", "George Orwell", "ISBN002", 3});
    books.push_back({"To Kill a Mockingbird", "Harper Lee", "ISBN003", 4});
    books.push_back({"Pride and Prejudice", "Jane Austen", "ISBN004", 2});
    books.push_back({"The Great Gatsby", "F. Scott Fitzgerald", "ISBN005", 6});
    books.push_back({"Moby Dick", "Herman Melville", "ISBN006", 3});
}

// Utility Function to Find Book by ISBN
int findBookIndex(const string& isbn) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].isbn == isbn) return i;
    }
    return -1;
}

// Utility Function to Find User by ID
int findUserIndex(const string& userID) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].userID == userID) return i;
    }
    return -1;
}

// Add New Book to Inventory
void addBook() {
    Book newBook;
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter ISBN: ";
    getline(cin, newBook.isbn);
    cout << "Enter Quantity: ";
    cin >> newBook.quantity;
    books.push_back(newBook);
    cout << "Book added successfully!\n";
}

// View All Books
void viewBooks() {
    if (books.empty()) {
        cout << "No books in inventory.\n";
        return;
    }
    cout << "\n--- Book Inventory ---\n";
    for (const auto& book : books) {
        cout << "Title: " << book.title << ", Author: " << book.author
             << ", ISBN: " << book.isbn << ", Quantity: " << book.quantity << "\n";
    }
}

// Edit Book Details
void editBook() {
    string isbn;
    cout << "Enter ISBN of the book to edit: ";
    cin >> isbn;
    int index = findBookIndex(isbn);

    if (index != -1) {
        cout << "Enter New Title: ";
        cin.ignore();
        getline(cin, books[index].title);
        cout << "Enter New Author: ";
        getline(cin, books[index].author);
        cout << "Enter New Quantity: ";
        cin >> books[index].quantity;
        cout << "Book details updated successfully!\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Delete Book from Inventory
void deleteBook() {
    string isbn;
    cout << "Enter ISBN of the book to delete: ";
    cin >> isbn;
    int index = findBookIndex(isbn);

    if (index != -1) {
        books.erase(books.begin() + index);
        cout << "Book deleted successfully!\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Add New User
void addUser() {
    User newUser;
    cout << "Enter User Name: ";
    cin.ignore();
    getline(cin, newUser.name);
    cout << "Enter User ID: ";
    getline(cin, newUser.userID);
    users.push_back(newUser);
    cout << "User added successfully!\n";
}

// View All Users
void viewUsers() {
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    cout << "\n--- Registered Users ---\n";
    for (const auto& user : users) {
        cout << "Name: " << user.name << ", User ID: " << user.userID;
        if (!user.borrowedBooks.empty()) {
            cout << ", Borrowed Books: ";
            for (const auto& book : user.borrowedBooks) {
                cout << book << " ";
            }
        }
        cout << "\n";
    }
}

// Issue Book to User
void issueBook() {
    string userID, isbn;
    cout << "Enter User ID: ";
    cin >> userID;
    int userIndex = findUserIndex(userID);

    if (userIndex == -1) {
        cout << "User not found.\n";
        return;
    }

    cout << "Enter ISBN of the book to issue: ";
    cin >> isbn;
    int bookIndex = findBookIndex(isbn);

    if (bookIndex != -1 && books[bookIndex].quantity > 0) {
        books[bookIndex].quantity--;
        users[userIndex].borrowedBooks.push_back(books[bookIndex].title);
        cout << "Book issued successfully!\n";
    } else {
        cout << "Book not available.\n";
    }
}

// Return Book from User
void returnBook() {
    string userID, isbn;
    cout << "Enter User ID: ";
    cin >> userID;
    int userIndex = findUserIndex(userID);

    if (userIndex == -1) {
        cout << "User not found.\n";
        return;
    }

    cout << "Enter ISBN of the book to return: ";
    cin >> isbn;
    int bookIndex = findBookIndex(isbn);

    if (bookIndex != -1) {
        auto& borrowed = users[userIndex].borrowedBooks;
        auto it = find(borrowed.begin(), borrowed.end(), books[bookIndex].title);

        if (it != borrowed.end()) {
            books[bookIndex].quantity++;
            borrowed.erase(it);
            cout << "Book returned successfully!\n";
        } else {
            cout << "This user did not borrow this book.\n";
        }
    } else {
        cout << "Book not found.\n";
    }
}

// Main Menu
int main() {
    preloadBooks();  // Preload some books
    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Edit Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Add User\n";
        cout << "6. View Users\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: editBook(); break;
            case 4: deleteBook(); break;
            case 5: addUser(); break;
            case 6: viewUsers(); break;
            case 7: issueBook(); break;
            case 8: returnBook(); break;
            case 9: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
