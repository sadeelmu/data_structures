#pragma once
// A Stack class based on an array implementation
// This is a bounded stack (has a fixed size).

template <class T>
class StackArray()
{
public:
    StackArray(int cap);
    StackArray(const StackArray &other);
    ~StackArray();

    void push(const T &val);
    T pop();
    T top() const;

    bool is_empty() const;
    bool is_full() const;

    void clear();
    StackArray &operator=(const StackArray &other);

private:
//dynamic array
    T *data;
    int cap;
    int last;
};

template <class T>
StackArray<T>::StackArray(int cap)
{
    if (cap <= 0)
        throw string("Invalid stack capacity");

    // why is last -1
    last = -1;
    this->cap = cap;
    data = new T[cap];
}
template <class T>
StackArray<T>::~StackArray()
{
    delete[] data;
}

template <class T>
T StackArray<T>::top()
{
    if (is_empty())
        throw string("ERROR: Attempting to retrieve an element from an empty stack!");

    return data[last];
}
template <class T>
T StackArray<T>::pop()
{
    if (is_empty())
        throw string("Stack underflow");

    last--;
    return data[last + 1];
}

template <class T>
bool StackArray<T>::is_full() const
{
    return last == capacity - 1;
}
template <class T>
bool StackArray<T>::is_empty()
{
    return last = -1;
}
template <class T>
void StackArray<T>::clear()
{
    last = -1;
}

template <class T>
void StackArray<T>::push(const T &val)
{
    if (is_full())
        throw string("Stack overflow");

    last++;
    data[last] = val;
}

template <class T>
StackArray<T>::StackArray(const StackArray<T> &other)
{
    last = other.last;
    cap = other.cap;
    data = new T[cap];
    for (int i = 0; i <= last; i++)
        data[i] = other.data[i];

    // if i want to use push
    //  last = -1;
    //  cap = other.cap;
    //  data=new T[cap];
    //  for(int i = 0;i<=other.last;i++)
    //      push(data[i] = other.data[i]);
}

template <class T>
StackArray<T> &StackArray<T>::operator=(const StackArray<T> &other)
{
    // if the same adress then same list return the object that list points to
    if (this == &other)
        return *this;

    // make s2 = s1 (where s1 is other)
    // deletes s2 data
    delete[] data;

    last = other.last;
    cap = other.cap;

    data = new T[cap];
    for (int i = 0; i <= last; i++)
        data[i] = other.data[i];

    return *this;
}
