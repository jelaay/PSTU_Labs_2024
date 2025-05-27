#pragma once

#include <iostream>

struct Node
{
	int data;
	Node* next;

	Node(const int& _data) : data(_data), next(nullptr) {}
};

struct singly_linked_list
{
	Node* head;
	Node* tail;
	int size;
	bool is_init;

	singly_linked_list(const int n);
	void init(const int n);
	bool is_empty() const;
	void print();
	void push_front(const int& _data);
	void push_back(const int& _data);
	void remove_front();
	void remove_back();
	void insert(const int& _data, int pos);
	void multiple_insert(int pos, const int n);
	void remove(int pos);
	void multiple_remove(int pos, const int n);
	const int& find_value(const int& _data);
	Node* find_value_ptr(const int& _data);
	~singly_linked_list();
};