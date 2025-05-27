#include <iostream>

struct Node
{
    char data;
    Node* next;
    Node* prev;

    Node(const char& _data) : data(_data), next(nullptr), prev(nullptr) {}
};

struct doubly_linked_list
{
    Node* head;
    Node* tail;
    int size;
    bool is_init = false;

    doubly_linked_list(const int n) : head(nullptr), tail(nullptr), size(0), is_init(false) { init(n); }

    void init(const int n)
    {
        if (is_init)
        {
            std::cerr << "List has already been initialized !" << std::endl;
            return;
        }
        char data;
        for (int i = 0; i < n; ++i)
        {
            std::cin >> data;
            push_back(data);
        }
        is_init = true;
    }

    bool is_empty() const { return head == nullptr; }

    void print()
    {
        Node* node = head;
        while (node != nullptr)
        {
            std::cout << node->data << ' ';
            node = node->next;
        }
        std::cout << std::endl;
    }

    void push_front(const char& _data)
    {
        Node* node = new Node(_data);
        if (is_empty())
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }
        ++size;
    }

    void push_back(const char& _data)
    {
        Node* node = new Node(_data);
        if (is_empty())
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        ++size;
    }

    void remove_front()
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
            head->prev = nullptr;
            delete node;
        }
        --size;
    }

    void remove_back()
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
            Node* node = tail;
            tail = node->prev;
            tail->next = nullptr;
            delete node;
        }
        --size;
    }

    void insert(const char& _data, int pos)
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
        for (int i = 0; i < pos; ++i)
        {
            current = current->next;
        }
        node->next = current;
        node->prev = current->prev;
        if (current->prev)
        {
            current->prev->next = node;
        }
        current->prev = node;
        ++size;
    }

    void multiple_insert(int pos, const int n)
    {
        for (int i = 0; i < n; ++i)
        {
            char _data;
            std::cin >> _data;
            insert(_data, pos);
            ++pos;
        }
    }

    void remove(int pos)
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
        for (int i = 1; i < pos; ++i)
        {
            current = current->next;
        }
        if (current->prev)
        {
            current->prev->next;
            current->prev->next = current->next;
        }
        if (current->next)
        {
            current->next->prev = current->prev;
        }
        delete current;
        --size;
    }

    void multiple_remove(int pos, const int n)
    {
        if (!is_empty())
        {
            for (int i = 0; i < n; ++i)
            {
                remove(pos);
            }
        }
    }

    const char& find_value(const char& _data)
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
    }

    Node* find_value_ptr(const char& _data)
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
    }

    ~doubly_linked_list()
    {
        while (!is_empty())
        {
            remove_front();
        }
    }
};

int main()
{
    return 0;
}