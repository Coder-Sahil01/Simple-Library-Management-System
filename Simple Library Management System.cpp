#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isIssued = false;
    }

    void display() {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

class Node {
public:
    Book book;
    Node* next;

    Node(Book book) : book(book), next(nullptr) {}
};

class Library {
private:
    Node* head;

public:
    Library() : head(nullptr) {}

    void addBook(Book book) {
        Node* newNode = new Node(book);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    Book* searchBookById(int id) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->book.id == id) {
                return &(temp->book);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    Book* searchBookByTitle(string title) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->book.title == title) {
                return &(temp->book);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void issueBook(int id, string studentName) {
        Book* book = searchBookById(id);
        if (book && !book->isIssued) {
            book->isIssued = true;
            cout << "Book issued to " << studentName << endl;
        } else {
            cout << "Book not available or already issued." << endl;
        }
    }

    void returnBook(int id) {
        Book* book = searchBookById(id);
        if (book && book->isIssued) {
            book->isIssued = false;
            cout << "Book returned." << endl;
        } else {
            cout << "Book not found or not issued." << endl;
        }
    }

    void listAllBooks() {
        Node* temp = head;
        while (temp != nullptr) {
            temp->book.display();
            temp = temp->next;
        }
    }

    void deleteBook(int id) {
        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr && temp->book.id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Book not found." << endl;
            return;
        }

        cout << "Deleting the following book:" << endl;
        temp->book.display();

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Book deleted." << endl;
    }
};

int main() {
    Library library;
    int choice, id;
    string title, author, studentName;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore(); // to ignore newline character
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(Book(id, title, author));
                break;
            case 2:
                cout << "Enter book ID to search: ";
                cin >> id;
                {
                    Book* book = library.searchBookById(id);
                    if (book) book->display();
                    else cout << "Book not found." << endl;
                }
                break;
            case 3:
                cout << "Enter book title to search: ";
                cin.ignore();
                getline(cin, title);
                {
                    Book* book = library.searchBookByTitle(title);
                    if (book) book->display();
                    else cout << "Book not found." << endl;
                }
                break;
            case 4:
                cout << "Enter book ID to issue: ";
                cin >> id;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;
            case 5:
                cout << "Enter book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 6:
                library.listAllBooks();
                break;
            case 7:
                cout << "Enter book ID to delete: ";
                cin >> id;
                library.deleteBook(id);
                break;
            case 8:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
