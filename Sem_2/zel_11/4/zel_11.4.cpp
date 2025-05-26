#include <iostream>
#include <string>
using namespace std;

struct node {
    int data;
    node* next;
};

struct Queue {
    node* front = nullptr;
    node* back = nullptr;

    void push(int Data) {
        node* newNode = new node;
        newNode->data = Data;
        newNode->next = nullptr;

        if (back == nullptr) {
            front = newNode;
            back = newNode;
        }
        else {
            back->next = newNode;
            back = newNode;
        }
    }

    int pop() {
        if (front == nullptr) {
            cout << "Очередь пуста" << endl;
            return -1; 
        }

        node* temp = front;
        int data = temp->data;
        front = front->next;

        if (front == nullptr) {
            back = nullptr;
        }

        delete temp;
        return data;
    }

    void print() {
        node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    Queue queue;
    int count, element;
    string choice;

    cout << "Введите количество элементов: ";
    cin >> count;

    if (count >= 0) {
        for (int i = 0; i < count; i++) {
            cout << "Введите " << i + 1 << " элемент: ";
            cin >> element;
            queue.push(element);
        }
        queue.print();

        cout << "Вы хотите удалить что-нибудь? 1/0  ";
        cin >> choice;
        if (choice == "1") {
            int removed = queue.pop();
            cout << "Удалённый элемент: " << removed << endl;
        }
        else if (choice == "0") {
            cout << "Ok" << endl;
        }
        else {
            cout << "Ошибка" << endl;
        }
        queue.print();

        cout << "Хотите добавить что-нибудь? 1/0 ";
        cin >> choice;
        if (choice == "1") {
            cout << "Введите элемент для добавления: ";
            cin >> element;
            queue.push(element);
        }
        else if (choice == "0") {
            cout << "Ok" << endl;
        }
        else {
            cout << "Ошибка" << endl;
        }
        queue.print();
    }
    else {
        cout << "Ошибка";
    }
    return 0;
}