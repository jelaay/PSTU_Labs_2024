#include <iostream>
#include <string>
using namespace std;

struct node
{
    int data;
    node* next;
    node* prev;
};

struct DoubleList {
    node* head = nullptr;
    node* tail = nullptr;

    void push_back(int Data) {
        node* newNode = new node;
        newNode->data = Data;
        newNode->next = head;
        newNode->prev = nullptr;

        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
    }

    void print() {
        node* newNode = head;
        while (newNode) {
            cout << newNode->data << " ";
            newNode = newNode->next;
        }
        cout << endl;
    }

    void del(int Data) {
        node* newNode = head;
        while (newNode != nullptr) {
            if (newNode->data == Data) {
                if (newNode == head) {
                    head = newNode->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    }
                    else {
                        tail = nullptr;
                    }
                    delete newNode;
                    return;
                }
                else if (newNode == tail) {
                    tail = newNode->prev;
                    tail->next = nullptr;
                    delete newNode;
                    return;
                }
                else {
                    newNode->prev->next = newNode->next;
                    newNode->next->prev = newNode->prev;
                    delete newNode;
                    return;
                }
            }
            newNode = newNode->next;
        }
        cout << "Элемент не найден" << endl;
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    DoubleList list;
    int element, count;
    string choice;

    cout << "Введите количество элементов: ";
    cin >> count;

    if (count >= 0) {
        for (int i = 0; i < count; i++) {
            cout << "Введите " << i + 1 << " элемент: ";
            cin >> element;
            list.push_back(element);
        }
        list.print();

        cout << "Хотите удалить что-нибудь? 1/0 ";
        cin >> choice;
        if (choice == "1") {
            cout << "Введите элемент для удаления: ";
            cin >> element;
            list.del(element);
        }
        else if (choice == "0") {
            cout << "Ok" << endl;
        }
        else {
            cout << "Ошибка" << endl;
        }
        list.print();

        cout << "Хотите добавить что-нибудь? 1/0 ";
        cin >> choice;
        if (choice == "1") {
            cout << "Введите элемент для добавления: ";
            cin >> element;
            list.push_back(element);
        }
        else if (choice == "0") {
            cout << "Ok" << endl;
        }
        else {
            cout << "Ошибка" << endl;
        }
        list.print();
    }
    else {
        cout << "Ошибка";
    }
    return 0;
}

