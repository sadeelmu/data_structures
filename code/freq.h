#include "queue_dll.h"
#include "node.h"
#include <string>
#include <iostream>
using namespace std;


template <class T>
class FreqTable
{
public:
    // Given functions.
    FreqTable();
    FreqTable(const FreqTable& other);
    ~FreqTable() { clear(); }
    Node<T>* get_root() const { return root; }
    bool is_empty() const { return root == nullptr; }
    int freq_of(const T& val) const;
    bool remove(const T& val);
    void clear();
    DLList<T> values() const;
    FreqTable& operator=(const FreqTable& other);

    // Required Functions.
    void insert(const T& val);
    T top() const;
    int freq_of(char c) const;
    void trim(int min_freq);

private:
    Node<T> *root;

    void copy_from(Node<T>* node);
    void values(DLList<T>& result, Node<T>* node) const;
    void remove_1(Node<T>* ptr, Node<T>* prev);
    void remove_2(Node<T>* node);
    void clear(Node<T>* node);

    //helper private variable
    Node<T> * max_freq; //node that stores the value which holds the highest frequency

    //helper private functions
    void trim(int min_freq, Node<T> *node); //reccursive function in order to preform trim
    void trimRemover(const T&val); //helper function that removes the value that trim sends
    int stringHelper(Node<string> *str, char c) const; //helper function for freq_of specialized for strings

};


// ------- REQUIRED FUNCTIONS --------- //
template <class T>
void FreqTable<T>::insert(const T& val)
{

if(is_empty()){
    root=new Node<T>(val, nullptr, nullptr);
    max_freq= root;
    return;
}

Node<T> * curr= root;
Node<T> * parent;

while(curr!=nullptr){
     if (val == curr->val){
            curr->freq++;
            int max = max_freq->freq;
            int current_freq = curr->freq;
            if(current_freq>max){
             max_freq=curr;
            }
            return;
     }
            

        parent = curr;
        if (val < curr->val)
            curr = curr->left;

        else // val>curr->val
             curr = curr->right;
}
Node<T> *new_node = new Node<T>(val, nullptr, nullptr);
    if (val < parent->val)
        parent->left = new_node;
    else
        parent->right = new_node;
}

template <class T>
T FreqTable<T>::top() const 
{
   if(is_empty())
     throw string("ERROR: Attempting to retrieve the value that has the highest frequency in an empty tree");

   return max_freq->val; //return the value stores inside the max_freq
    
/*
added a private variable Node<T> max_freq which stores the node that stores the value that has the highest frequency
added a condition to the insert function where if we create a root we make the root the max_freq
added a condition to the insert function where if the value has already been inserted to increase the frequency
then if the increased frequency is higher than the max_freq then we increase the max_freq
in the constructor i intializied the value of the max_freq to nullptr
*/

}

template <class T>
void FreqTable<T>::trim(int min_freq) 
{
    if(is_empty()) //check that the list isnt empty
    return;

    if(min_freq==0 || min_freq < 0) //checks that the min freq isnt zero or negative
    return;

    return trim (min_freq, root);

}

template <class T>
void FreqTable<T>::trim(int min_freq, Node<T> *node){
    //post order traveral is most suitable for this function
    if(node==nullptr)
    return;

    trim(min_freq, node->left);
    trim(min_freq, node->right);

    //Removes from the tree every node whose frequency is less than or equal to the given minimum frequency. 
    if(node->freq<=min_freq)
    trimRemover(node->val);
}

template <class T> 
void FreqTable<T>::trimRemover(const T&val){
    Node<T> *node = root;
    Node<T> *parent = nullptr;

    while (node != nullptr)
    {
        if (node->val == val)
            break;

        parent = node;
        if (val < node->val)
            node = node->left;
        else
            node = node->right;
    }

    if (node == nullptr)
        return;

    else if (node->left == nullptr || node->right == nullptr)
        remove_1(node, parent);
    else
        remove_2(node);
}

template <>   
int FreqTable<string>::stringHelper(Node<string> *str, char c) const{
    if(str==nullptr)
    return 0;

    int sumChar = 0;
    if(str->val[0]==c)
    sumChar = str->freq;
    return sumChar + stringHelper(str->left, c) + stringHelper(str->right, c);
}

template <>
int FreqTable<string>::freq_of(char c) const 
{
    if(is_empty())
    return 0;

    return stringHelper(root, c);
}



// ------------------------------------------ //



template <class T>
FreqTable<T>::FreqTable()
{
    root = nullptr;
    max_freq= nullptr;
}

template <class T>
void FreqTable<T>::copy_from(Node<T>* node) 
{
    if (node == nullptr)
        return;
    
    insert(node->val);
    copy_from(node->left);
    copy_from(node->right);
}

template <class T>
FreqTable<T>::FreqTable(const FreqTable<T>& other) 
{
    root = nullptr;
    copy_from(other.root);
}

template <class T>
int FreqTable<T>::freq_of(const T& val) const
{
    Node<T>* node = root;
    
    while(node != nullptr) {
        if (val == node->val)   return node->freq;
        if (val < node->val)    node = node->left;
        else                    node = node->right;
    }

    return 0; 
}

template <class T>
DLList<T> FreqTable<T>::values() const
{
    DLList<T> result;
    values(result, root);
    return result;
}

template <class T>
void FreqTable<T>::values(DLList<T>& result, Node<T>* node) const
{
    if (node == nullptr) 
        return;

    values(result, node->left);
    result.add_to_tail(node->val);
    values(result, node->right);
}


template <class T>
bool FreqTable<T>::remove(const T& val)
{
    Node<T>* node = root;
    Node<T>* prev = nullptr;

    while (node != nullptr) {
        if (node->val == val)
            break;
        
        prev = node;
        if (val < node->val)
            node = node->left;
        else
            node = node->right;
    }
    
    if (node == nullptr)
        return false;

    if (node->freq > 1){
        node->freq--;
    }
        

    else if (node->left == nullptr || node->right == nullptr)
        remove_1(node, prev);
    else
        remove_2(node);
    
    return true;
}

template <class T>
void FreqTable<T>::remove_1(Node<T>* ptr, Node<T>* prev)
{
    if (ptr == root) {
        if (root->left != nullptr)  
            root = root->left;
        else 
            root = root->right;
    }
    else if (ptr == prev->left) {
        if (ptr->right != nullptr)  
            prev->left = ptr->right;
        else 
            prev->left = ptr->left;
    }  
    else {
        if (ptr->right != nullptr)  
            prev->right = ptr->right;
        else 
            prev->right = ptr->left;
    }
    
    delete ptr;
}

template <class T>
void FreqTable<T>::remove_2(Node<T>* node)
{
    Node<T>* rep = node->left; 
    Node<T>* prev = node;
    
    while (rep->right != nullptr) {
        prev = rep;
        rep = rep->right;
    }
    
    node->val = rep->val;
    node->freq = rep->freq;
    remove_1(rep, prev);
}


template <class T>
void FreqTable<T>::clear()
{
    clear(root);
    root = nullptr;
}
 
template <class T>
void FreqTable<T>::clear(Node<T>* node)
{
    if (node == nullptr) 
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

template <class T>
FreqTable<T>& FreqTable<T>::operator=(const FreqTable<T>& other)
{
    if (this == &other)
        return *this;
 
    clear();
    copy_from(other.root);
    return *this;
}

template <class T>
void print(ostream& out, Node<T>* node) {
    if (node == nullptr)
        return;
    print(out, node->get_left());
    out << node->get_val() << ": " << node->get_freq() << endl;
    print(out, node->get_right());
}

template <class T>
ostream& operator<<(ostream& out, const FreqTable<T>& table) {
    print(out, table.get_root());
    return out;
}

