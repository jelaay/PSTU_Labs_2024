#include <iostream>
#include <string>
using namespace std;

struct node {
    int data;
    node* next;
};

struct Stack {
    node* top = nullptr;

    void push(int Data) {
        node* newNode = new node;
        newNode->data = Data;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (top == nullptr) {
            cout << "Стэк пуст" << endl;
        }
        else {
            int element = top->data;
            node* temp = top;
            top = top->next;
            delete temp;
            return element;
        }
    }

    void print() {
        node* newNode = top;
        while (newNode != nullptr) {
            cout << newNode->data << " ";
            newNode = newNode->next;
        }
        cout << endl;
    }

    void del(int Data) {
        node* newNode = top;
        node* prev = nullptr;

        while (newNode != nullptr) {
            if (newNode->data == Data) {
                if (prev == nullptr) {
                    top == newNode->next;
                    delete newNode;
                    return;
                }
                else {
                    prev->next = newNode->next;
                    delete newNode;
                    return;
                }
            }
            prev = newNode;
            newNode = newNode->next;
        }
        cout << "Элемент не найден" << endl;
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    Stack stack;
    int count, element;
    string choice;

    cout << "Введите количество элементов: ";
    cin >> count;

    if (count >= 0) {
        for (int i = 0; i < count; i++) {
            cout << "Введите " << i + 1 << " элемент: ";
            cin >> element;
            stack.push(element);
        }
        stack.print();

        cout << "Хотите удалить что-нибудь? 1/0 ";
        cin >> choice;
        if (choice == "1") {
            cout << "Введите элемент для удаления: ";
            cin >> element;
            stack.del(element);
        }
        else if (choice == "0") {
            cout << "Ok" << endl;
        }
        else {
            cout << "Ошибка" << endl;
        }
        stack.print();

        cout << "Хотите добавить что-нибудь? 1/0 ";
        cin >> choice;
        if (choice == "1") {
            cout << "Введите элемент для добавления: ";
            cin >> element;
            stack.push(element);
        }
        else if (choice == "0") {
            cout << "Ok" << endl;
        }
        else {
            cout << "Ошибка" << endl;
        }
        stack.print();
    }
    else {
        cout << "Ошибка";
    }
    return 0;
}