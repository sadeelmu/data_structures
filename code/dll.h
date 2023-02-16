#pragma once

#include <iostream>
using std::cout;
using std::string;

template <class T>
class Node
{
public:
    int val;
    Node *next;

    Node(int val, Node *next)
    {
        this->val = val;
        this->next = next;
    }
};

// template<class TYPE>
// or
template <class T>
// for templates we have to use <T> next to Node and List

class List
{
public:
    List();
    ~List();

    Node *head_node() const;
    Node *tail_node() const;
    bool is_empty() const;

    bool contains(int val) const;
    int get_at(int index) const;

    void add_to_head(int val);
    void add_to_tail(int val);

    void remove_head();
    void remove_tail();
    bool remove(int val);

    void print() const;

private:
    Node *head;
    Node *tail;
};

List<int> myList;

List::List() // O(1)
{
    head = nullptr;
    tail = nullptr;
}

List::~List() // O(n)
{
    Node *curr = head;
    Node *del_node;

    while (curr != nullptr)
    {
        del_node = curr;
        curr = curr->next;
        delete del_node;
    }
}

bool List::is_empty() const // O(1)
{
    return head == nullptr;
}

Node *List::head_node() const // O(1)
{
    return head;
}

Node *List::tail_node() const // O(1)
{
    return tail;
}

void List::add_to_head(int val)
// O(1)
// became better
{
    Node *new_node = new Node(val, head);

    head = new_node;
    if (tail == nullptr)
        tail = new_node;
}

void List::add_to_tail(int val) // O(1)
{
    Node *new_node = new Node(val, nullptr);

    if (tail == nullptr)
        head = new_node;
    else
        tail->next = new_node;

    tail = new_node;
}

void List::remove_head() // O(1)
{
    if (is_empty())
        return;

    Node *temp = head;
    head = head->next;
    delete temp;

    if (head == nullptr)
        tail = nullptr;
}

void List::remove_tail()
// O(n)
// became worse
{
    if (head == tail)
    {
        remove_head();
        return;
    }

    Node *prev = head;
    while (prev->next != tail)
        prev = prev->next;

    delete tail;
    tail = prev;
    tail->next = nullptr;
}

bool List::remove(int val) // O(n) worst case
{
    if (is_empty())
        return false;

    if (val == head->val)
    {
        remove_head();
        return true;
    }

    if (val == tail->val)
    {
        remove_tail();
        return true;
    }

    Node *node = head->next;
    Node *pred = head;

    while (node != nullptr)
    {
        if (node->val == val)
        {
            pred->next = node->next;
            delete node;
            return true;
        }

        node = node->next;
        pred = pred->next;
    }

    return false;
}

bool List::contains(int val) const // O(n) worst case
{
    for (Node *curr = head; curr != nullptr; curr = curr->next)
        if (curr->val == val)
            return true;

    return false;
}

// int List::get_at(int index) const
// {
//     if (is_empty() || index < 0)
//         throw string("ERROR: Invalid argument in function get_at(int)");

//     int count = 0;
//     Node *curr = head;

//     while (count != index && curr != nullptr)
//     {
//         curr = curr->next;
//         count++;
//     }

//     if (curr != nullptr)
//         return curr->val;
//     else
//         throw string("ERROR: Invalid argument in function get_at(int)");
// }

// Document:
// Note that this function throws a string exception if the index is negative

int List::get_at(int index) const
// ***O(n) worst case
// Became worse
{
    if (index < 0 || is_empty())
    {
        // return -1 would not work as it would return an inaccurate integer
        // return would not work as we have to return an integer
        // return null would just return 0 and would be inaccurate
        // return nullptr would return a pointer to an int function

        // exit(0) would exit the whole program
        // cout << "Invalid Index"; would just print a message

        // Excpetional errors like this must be thrown
        // in C++ you can throw any data type
        throw string("Error: Invalid index in function get_at");
    }

    Node curr = head;
    int count = 0;
    while (curr != nullptr)
    {
        if (index == count)
            return curr->val;
        curr = curr->next;
        count++;
    }

    // if it reaches after the loop
    throw string("Invalid Index!");
}
void List::print() const // O(n)
{
    cout << "[";

    Node *curr = head;
    while (curr != nullptr)
    {
        cout << curr->val;

        if (curr->next != nullptr)
            cout << ", ";

        curr = curr->next;
    }

    cout << "]";
}

int main()
{
    List myList;
    for (int i = 0; i < 10; i++)
        myList.add_to_tail(i);

    // as role 2 u catch the error that is thrown from role 1
    //  try{
    //      myList.get_at(-1);
    //  }
    // for example catch(out_of_range)
    //  catch (string e){
    //
    // }
}

/*
Roles to adopt while coding
1. Programmer of the Data Structure
2. Programmer of an application using the Data Structure
3. User of the program
*/
