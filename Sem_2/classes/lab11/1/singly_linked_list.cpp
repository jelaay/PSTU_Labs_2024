#include "singly_linked_list.h"

singly_linked_list::singly_linked_list(const int n) : head(nullptr), tail(nullptr), size(0), is_init(false) { init(n); }

void singly_linked_list::init(const int n)
{
    if (is_init)
    {
        std::cerr << "List has already been initialized !" << std::endl;
        return;
    }
    int data;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data;
        push_back(data);
    }
    is_init = true;
}

bool singly_linked_list::is_empty() const { return head == nullptr; }

void singly_linked_list::print()
{
    Node* node = head;
    while (node != nullptr)
    {
        std::cout << node->data << ' ';
        node = node->next;
    }
    std::cout << std::endl;
}

void singly_linked_list::push_front(const int& _data)
{
    Node* node = new Node(_data);
    if (is_empty())
    {
        head = tail = node;
    }
    else
    {
        node->next = head;
        head = node;
    }
    ++size;
}

void singly_linked_list::push_back(const int& _data)
{
    Node* node = new Node(_data);
    if (is_empty())
    {
        head = tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    ++size;
}

void singly_linked_list::remove_front()
{
    if (is_empty())
    {
        std::cerr << "List is empty. Cannot remove from front !" << std::endl;
        return;
    }
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node* node = head;
        head = node->next;
        delete node;
    }
    --size;
}

void singly_linked_list::remove_back()
{
    if (is_empty())
    {
        std::cerr << "List is empty. Cannot remove from back !" << std::endl;
        return;
    }
    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        Node* current = head;
        while (current->next != tail)
        {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    --size;
}

void singly_linked_list::insert(const int& _data, int pos)
{
    --pos;
    if (pos < 0 || pos > size)
    {
        std::cerr << "Invalid position !" << std::endl;
        return;
    }
    if (pos == 0)
    {
        push_front(_data);
        return;
    }
    if (pos == size)
    {
        push_back(_data);
        return;
    }
    Node* node = new Node(_data);
    Node* current = head;
    for (int i = 0; i < pos - 1; ++i)
    {
        current = current->next;
    }
    node->next = current->next;
    current->next = node;
    size++;
}

void singly_linked_list::multiple_insert(int pos, const int n)
{
    for (int i = 0; i < n; ++i)
    {
        int _data;
        std::cin >> _data;
        insert(_data, pos);
        ++pos;
    }
}

void singly_linked_list::remove(int pos)
{
    if (pos < 1 || pos > size)
    {
        std::cerr << "Invalid position !" << std::endl;
        return;
    }
    if (pos == 1)
    {
        remove_front();
        return;
    }
    if (pos == size)
    {
        remove_back();
        return;
    }
    Node* current = head;
    Node* previous = nullptr;
    for (int i = 1; i < pos; ++i)
    {
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
    delete current;
    current = nullptr;
    --size;
}

void singly_linked_list::multiple_remove(int pos, const int n)
{
    if (!is_empty())
    {
        for (int i = 0; i < n; ++i)
        {
            remove(pos);
        }
    }
}

const int& singly_linked_list::find_value(const int& _data)
{
    if (is_empty())
    {
        std::cerr << "List is empty. Cannot find value !" << std::endl;
        return ' ';
    }
    else
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->data == _data) { return current->data; }
            current = current->next;
        }
    }
    return ' ';
}

Node* singly_linked_list::find_value_ptr(const int& _data)
{
    if (is_empty())
    {
        std::cerr << "List is empty. Cannot find value !" << std::endl;
        return nullptr;
    }
    else
    {
        Node* current = head;
        while (current != nullptr)
        {
            if (current->data == _data) { return current; }
            current = current->next;
        }
    }
    return nullptr;
}

singly_linked_list::~singly_linked_list()
{
    while (!is_empty())
    {
        remove_front();
    }
}