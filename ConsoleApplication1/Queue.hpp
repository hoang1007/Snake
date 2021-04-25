#pragma once 

template <class Type>
struct Node
{
    Type data;
    Node* prev;
    Node();
    Node(Type value);
};

template <typename Type>
class ReverseQueue
{
    Node<Type>* head, * tail;
    int _size;
public:
    ReverseQueue();
    ~ReverseQueue();
    Node<Type>* begin();
    Node<Type>* end();
    void push(Type value);
    Type pop();
    Type at(int position);
    Type operator[] (int position);
    bool find(Type src);
    Type& front();
    Type& back();
    void clear();
    int size();


    //// iterator
    //class iterator;

    //iterator begin()
    //{
    //    return iterator(head);
    //}

    //iterator end()
    //{
    //    return iterator(tail);
    //}

    //class iterator
    //{
    //    const Node* currentNode;
    //public:
    //    iterator() : currentNode
    //};
};

#include <iostream>
using namespace std;

template <class Type>
Node<Type>::Node(Type value)
{
    data = value;
    prev = NULL;
}

template <class Type>
Node<Type>::Node()
{
    prev = nullptr;
}

template <class Type>
void ReverseQueue<Type>::push(Type value)
{
    Node<Type>* node = new Node<Type>(value);

    if (head == NULL)
        tail = node;
    else
        head->prev = node;

    head = node;
    _size++;
}

template <class Type>
Type ReverseQueue<Type>::pop()
{
    if (tail)
    {
        _size--;
        Node<Type>* temp = tail;
        tail = tail->prev;

        Type temp_data = temp->data;
        temp = NULL;
        delete temp;
        return temp_data;
    }
}

template <class Type>
Type ReverseQueue<Type>::at(int position)
{
    if (position >= 0 && position < _size)
    {
        if (position == 0) return head->data;

        Node<Type>* temp = tail;
        position = _size - position - 1;

        for (; position; position--)
            temp = temp->prev;

        if (temp)   return temp->data;
        else cout << "NULL Pointer\n";
    }
    else cerr << "Out of bound\n";
}

template <class Type>
Type ReverseQueue<Type>::operator[](int position)
{
    return at(position);
}

template <class Type>
bool ReverseQueue<Type>::find(Type src)
{
    Node<Type>* temp = tail;
    if (tail == NULL) return false;
    for (; temp; temp = temp->prev)
        if (temp->data == src) return true;
    return false;
}

template <class Type>
Type& ReverseQueue<Type>::front()
{
    if (head == NULL) cerr << "Head is NULL\n";
    else return head->data;
}

template <class Type>
Type& ReverseQueue<Type>::back()
{
    if (tail == NULL) cerr << "Tail is NULL\n";
    else return tail->data;
}

template <class Type>
void ReverseQueue<Type>::clear()
{
    while (tail)
        pop();
}

template <class Type>
int ReverseQueue<Type>::size()
{
    return _size;
}

template<typename Type>
ReverseQueue<Type>::ReverseQueue()
{
    head = tail = NULL;
    _size = 0;
}

template <class Type>
ReverseQueue<Type>::~ReverseQueue()
{
    clear();
}

template<typename Type>
inline Node<Type>* ReverseQueue<Type>::begin()
{
    return head;
}

template<typename Type>
inline Node<Type>* ReverseQueue<Type>::end()
{
    return tail;
}