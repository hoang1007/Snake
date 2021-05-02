/*
* Cấu trúc dữ liệu hàng đợi 
* Sử dụng danh sách liên kết ngược để thêm vào đầu và bỏ đi phần tử cuối chỉ mất O(1)
*/
#pragma once 

#include <iostream>
using namespace std;

template <typename Type>
class ReverseQueue
{
protected:
    // định nghĩa cấu trúc node là mỗi mắt xích của danh sách liên kết
    struct Node
    {
        Type data;
        Node* prev;
        Node();
        Node(Type value);
    };
private:
    Node* head; // lưu node đầu của hàng đợi
    Node* tail; // lưu node cuối của hàng đợi
    int _size;  // chiều dài của hàng đợi
public:
    ReverseQueue();
    ~ReverseQueue();

    // thêm một node vào đầu hàng đợi
    void push(Type value);
    // xóa một node ở cuối hàng đợi và trả về giá trị của nó
    Type pop();
    // lấy giá trị của một node ở vị trí cho trước (position)
    Type at(int position);
    // lấy giá trị của một node ở vị trí cho trước (position)
    Type operator[] (int position);
    // tìm kiếm trong hàng đợi
    bool find(Type src);
    // trả về giá trị của node đầu tiên trong hàng đợi
    Type& front();
    // trả về giá trị của node cuối cùng trong hàng đợi
    Type& back();
    // xóa tất cả các node của hàng đợi
    void clear();
    // trả về chiều dài của hàng đợi
    int size();
    // trả về true nếu hàng đợi rỗng 
    bool empty();
    // duyệt hàng đợi và truy cập dữ liệu
    class iterator;

    iterator begin()
    {
        return iterator(head);
    }

    // trả về iterator phía trước của phần tử đầu 
    iterator pbegin()
    {
        return iterator(nullptr);
    }

    iterator end()
    {
        return iterator(tail);
    }

    iterator secondlast()
    {
        return iterator(tail->prev);
    }

    class iterator
    {
        Node* currentNode;
    public:
        iterator()
        {
            currentNode = nullptr;
        };
        iterator(Node* node)
        {
            currentNode = node;
        };

        iterator& operator=(Node* node)
        {
            this->currentNode = node;
            return *this;
        }
        iterator& operator--()
        {
            if (currentNode)
                currentNode = currentNode->prev;
            return *this;
        }
        iterator operator--(int)
        {
            iterator i = *this;
            --* this;
            return i;
        }
        bool operator!=(const iterator& src)
        {
            return currentNode != src.currentNode;
        }
        Type& operator*()
        {
            return currentNode->data;
        }
        Type* operator->()
        {
            return &currentNode->data;
        }
    };
};

template <class Type>
void ReverseQueue<Type>::push(Type value)
{
    Node* node = new Node(value);
    // nếu hàng đợi rỗng gán cả head và tail bằng node
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
    if (head)
    {
        _size--;
        if (head == tail)
        {
            Type temp_data = tail->data;
            head = tail = nullptr;
            delete head;
            delete tail;
            return temp_data;
        }

        Node* temp = tail;
        tail = tail->prev;  // dịch tail lên một node

        Type temp_data = temp->data;    // lưu lại giá trị của node cần xóa
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

        Node* temp = tail;
        position = _size - position - 1;    // fix lại vị trí vì duyệt hàng đợi từ cuối lên đầu

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
    Node* temp = tail;
    if (tail == NULL) return false;
    for (; temp; temp = temp->prev)
        if (temp->data == src) return true;
    return false;
}

template <class Type>
Type& ReverseQueue<Type>::front()
{
    if (head == NULL) cerr << "Head is NULL\n";
    return head->data;
}

template <class Type>
Type& ReverseQueue<Type>::back()
{
    if (tail == NULL) cerr << "Tail is NULL\n";
    return tail->data;
}

template <class Type>
void ReverseQueue<Type>::clear()
{
    while (tail)    // khi hàng đợi không rỗng thì tiếp tục pop
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
    cerr << "Queue destructor called!" << endl;
    clear();
}

template<typename Type>
inline ReverseQueue<Type>::Node::Node()
{
    prev = nullptr;
}

template<typename Type>
inline ReverseQueue<Type>::Node::Node(Type value)
{
    this->data = value;
    prev = nullptr;
}

template<typename Type>
bool ReverseQueue<Type>::empty()
{
    return _size == 0;
}