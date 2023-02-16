#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::string;

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

class List
{
    // constructor
    List();
    // destructors
    ~List();

    // getters
    Node *getHead() const;
    Node *getTail() const;

    bool is_empty() const;
    bool contain(int val) const;
    bool get_at(int index) const;

    void remove_tail();
    void remove_head();
    bool remove(int val);

    void add_head(int val);
    void add_tail(int val);

    void print() const;

private:
    Node *head;
    Node *last;
};

List::List()
{
    // initiate the values
    head = nullptr;
    last = nullptr;
}

Node *List::getHead()
{
    return head;
}

Node *List::getTail()
{
    return tail;
}

bool List::is_empty() const
{
    if (head == nullptr)
        return true;
}

void add_head(int val)
{

    Node *new_node = new Node(val, head);
    head = new_node;

    // if(is_empty==true){
    //     tail=new_node;
    // }

    if (tail == nullptr)
        tail = new_node;
}

void add_tail(int val)
{
    // if(head==nullptr)
    //     add_head(val);

    Node *new_node = new Node(val, tail);
    if (tail == nullptr)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->next = new_node;
        tail = new_node;
    }
}

void remove_head()
{
    if (is_empty() == true)
    {
        return;
    }
    Node *temp = head;
    head = head->next;
    delete temp;

    // * If there is only one node in the list, moving the head
    //      forward makes it nullptr. In this case, the tail also
    //      must become nullptr.

    if (head == nullptr)
    {
        tail == nullptr;
    }
   
}

void remove_tail()
{
    // if (is_empty() == true)
    //     return;
    if (head == tail)
    {
        remove_head();
        return;
    }

    Node *temp = tail;
    Node *curr = head;
    while (curr->next!=tail)
    {
        curr = curr->next;
    }
    tail = curr;
    delete temp;
    //next is now pointing at garabge so we must fix it
    tail->next=nullptr;
}


bool List::remove(int val){
    if(is_empty()==true){
        return false;
    }

    if(val==head->val){
        remove_head();
        return true;
    }
    if(val==tail->val){
        remove_tail();
        return true;
    }

    Node *curr=head->next;
    Node *prev=head;

    while(curr!=nullptr){
        if(curr->val=val){
            prev->next=curr->next;
            delete curr;
            return true;
        }
        curr=curr->next;
        prev=prev->next;
    }
    return false;

}
