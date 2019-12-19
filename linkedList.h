#ifndef DATA_STRUCTURES_SINGLY_LINKED_LIST_TEMPLATED_ELANAFELSI_LINKEDLIST_H
#define DATA_STRUCTURES_SINGLY_LINKED_LIST_TEMPLATED_ELANAFELSI_LINKEDLIST_H


#include <iostream>

template <typename T>
class List
{
public:

    struct Node
    {
        Node(T data, Node* next);

        T m_data;
        Node *m_next;
    };

    class Iterator
    {
    public:

        explicit Iterator(Node *node);

        T operator*();

        Node* operator->();

        Iterator& operator++();

        Iterator& operator++(int);

        bool operator!=(const Node *node);
        bool operator==(const Node *node);

        bool operator!=(const Iterator &other);
        bool operator==(const Iterator &other);

    private:
        Node *m_node;
    };

    List();
    ~List();

    void insert(T data);
    void remove(Node* node);
    bool isEmpty();

    Iterator begin() const;
    Iterator end() const ;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const List<U> &lst);

private:
    Node *m_head;
    Node *m_tail;
};

template<typename T>
inline List<T>::List()
        :m_head(NULL), m_tail(NULL){}

template<typename T>
inline bool List<T>::isEmpty() {
    return (m_head->m_next == &m_tail);
}

template<typename T>
inline typename List<T>::Iterator List<T>::begin() const {
    return Iterator(m_head);
}

template<typename T>
inline typename List<T>::Iterator List<T>::end() const{
    return Iterator(NULL);
}

template<typename T>
inline List<T>::~List()
{
    Node *temp = m_head;
    while(temp)
    {
        temp = temp->m_next;
        delete(m_head);
        m_head = temp;
    }
}

template<typename T>
inline List<T>::Node::Node(T data, List::Node *next):
        m_data(data), m_next(next){}

template<typename T>
inline List<T>::Iterator::Iterator(List::Node *node):
        m_node(node){}

template<typename T>
inline T List<T>::Iterator::operator*() {
    return m_node->m_data;
}

template<typename T>
inline typename List<T>::Node *List<T>::Iterator::operator->() {
    return m_node;
}

template<typename T>
inline typename List<T>::Iterator &List<T>::Iterator::operator++() {
    m_node = m_node->m_next;
    return *this;
}

template<typename T>
inline typename List<T>::Iterator &List<T>::Iterator::operator++(int){
    Iterator it(*this);
    m_node = m_node->m_next;
    return it;
}

template<typename T>
bool List<T>::Iterator::operator!=(const List::Node *node) {
    return m_node != node;
}

template<typename T>
bool List<T>::Iterator::operator==(const List::Node *node) {
    return m_node == node;
}

template<typename T>
bool List<T>::Iterator::operator!=(const List::Iterator &other) {
    return *this != other.m_node;
}

template<typename T>
bool List<T>::Iterator::operator==(const List::Iterator &other) {
    return *this == other.m_node;
}


template<typename T>
inline void List<T>::insert(T data)
{

    Node *node = new Node(data, m_tail);
    Node* cur = m_head;

    if (cur != NULL)
    {
        while (cur->m_next != NULL)
        {
            cur = cur->m_next;
        }

        cur->m_next = node;
    }
    else
    {
        m_head = node;
    }

}

template<typename T>
inline void List<T>::remove(List::Node *node)
{
    Node *cur = m_head;
    if (node == m_head) {
        m_head = cur->m_next;
        delete node;
    }

    while (cur) {
        if (cur->m_next == node) {
            cur->m_next = node->m_next;
            delete node;
        }
        cur = cur->m_next;
    }
}

template<typename U>
inline std::ostream &operator<<(std::ostream &os, const List<U> &list) {
    for (typename List<U>::Iterator it = list.begin();
         it != list.end(); ++it) {
        if (it->m_next == list.m_tail)
            os << *it<< std::endl;
        else
            os << *it << " -> ";
    }
    return os;
}
#endif //DATA_STRUCTURES_SINGLY_LINKED_LIST_TEMPLATED_ELANAFELSI_LINKEDLIST_H
