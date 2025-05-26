#include <iostream>
#include <string>
using namespace std;

struct node
{
    int data;
    node* next;
};

struct LinkedList {
    node* head = nullptr;
    node* tail = nullptr;

    void push_back(int data) {
        node* newNode = new node;
        newNode->data = data;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        }
        else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    void print() {
        node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void delHead() {
        if (head == nullptr) {
            return;
        }
        node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void delTail() {
        if (head == nullptr) {
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        current->next = nullptr;
        delete tail;
        tail = current;
    }

    void del(int data) {
        if (head == nullptr) {
            return;
        }
        if (head->data == data) {
            delHead();
            return;
        }
        node* current = head;
        while (current->next != nullptr && current->next->data != data) {
            current = current->next;
        }
        if (current->next == nullptr) {
            cout << "Элемент не найден" << endl;
            return;
        }
        if (current->next == tail) {
            delTail();
        }
        else {
            node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    LinkedList list;
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

        cout << "Вы хотите удалить что-нибудь? 1/0 ";
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
            cout << "Ошибка выбора" << endl;
        }
        list.print();

        cout << "Хотите добавить что-ниубдь? 1/0 ";
        cin >> choice;
        if (choice == "1") {
            cout << "Введите элмент для добавления: ";
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
