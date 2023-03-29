/*
 * this file is implement to linked list data structure in C++
 * this version is with head pointer only.
 * */

#ifndef LINKEDLIST_LINKEDLISTHEADONLY_H
#define LINKEDLIST_LINKEDLISTHEADONLY_H
#include <iostream>
template<class T>
struct Node{
    T value;
    Node * next;
    Node(){
        value = 0;
        next = nullptr;
    }
    Node(T val){
        value = val;
        next = nullptr;
    }
};

template<class T>
class LinkedList{
private:
    Node<T> * head;
    int Size;
    void deleteList();
    void copyList(const LinkedList<T> & list);
public:
    LinkedList();

    LinkedList(T value);

    // copy constructor
    LinkedList(const LinkedList<T> &list);

    void insertFirst(T value);

    void insertLast(T value);

    bool insert(T value, int pos);

    int size() const;

    bool deleteIndex(int pos);

    bool isEmptyList();

    Node<T> & front();

    Node<T> &back();

    LinkedList & operator=(const LinkedList & list);

    friend std::ostream &operator<<(std::ostream &out, const LinkedList<T> &list){
        if (list.head == nullptr){
            out << "[]";
            return out;
        }
        Node<T> *current;
        current = list.head;
        out << "[";
        while (current->next != nullptr){
            out << current->value << " -> ";
            current = current->next;
        }
        out << current->value << "]";
        return out;
    }

    ~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList(){
    Size = 0;
    head = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(T value){
    Node<T> * node = new Node<T>(value);
    head = node;
    Size = 1;
}

template<class T>
void LinkedList<T>::deleteList(){
    while (Size)
        deleteIndex(1);
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &list){
    // this default in any empty one
    this->Size = 0;
    head = nullptr;
    this->copyList(list);
}

template<class T>
void LinkedList<T>::insertFirst(T value){
    Node<T> * node = new Node<T>(value);
    if (head == nullptr){
        head = node;
    }else{
        node->next = head;
        head = node;
    }
    Size++;
}

template<class T>
void LinkedList<T>::insertLast(T value){
    Node<T> * node = new Node<T>(value);
    if (head == nullptr){
        head = node;
    }
    else {
        Node<T> *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
    Size++;
}

template<class T>
bool LinkedList<T>::insert(T value, int pos){
    Node<T> * current = head;
    if (pos > Size || pos <= 0){
        return false;
    }
    while (current->next != nullptr && pos > 1){
        current = current->next;
        pos--;
    }
    if (pos == 1){
        Node<T> * node = new Node<T>(value);
        node->next = current->next;
        current->next = node;
        Size++;
        return true;
    }else if (pos <= 0){
        return false;
    }
    return false;
}

template<class T>
int LinkedList<T>::size() const{
    return Size;
}

template<class T>
bool LinkedList<T>::deleteIndex(int pos){
    // if any invalid data will be out
    if (pos > Size || pos <= 0 || head == nullptr){
        return false;
    }

        // delete from first index
    else if (pos == 1){
        if (Size == 1){
            delete head;
            head = nullptr;
        }
        else{
            Node<T> * temp = head->next;
            delete head;
            head = temp;
            temp = nullptr;
        }
        Size--;
        return true;
    }

        // delete from last index
    else if (pos == Size){
        Node<T> * current = head;
        while (current != nullptr && pos > 2){
            current = current->next;
            pos--;
        }
        if (pos == 2){
            delete current->next;
            current->next = nullptr;
            Size--;
            return true;
        }
    }

        // delete from any position in size the list
    else{
        Node<T> * current = head;
        while (current != nullptr && pos > 1){
            current = current->next;
            pos--;
        }
        if (pos == 1){
            Node<T> * temp = current->next->next;
            delete current->next;
            current->next = temp;
            temp = nullptr;
            Size--;
            return true;
        }
    }
    return false;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list){
    // delete this list
    deleteList();
    this->copyList(list);
    return *this;
}

//template<class T>
//std::ostream &operator<<(std::ostream &out, const LinkedList<T> &list){
//    if (list.head == nullptr){
//        out << "[]";
//        return out;
//    }
//    Node<T> *current;
//    current = list.head;
//    out << "[";
//    while (current->next != nullptr){
//        out << current->value << " -> ";
//        current = current->next;
//    }
//    out << current->value << "]";
//    return out;
//}

template<class T>
LinkedList<T>::~LinkedList(){
    deleteList();
}

template<class T>
bool LinkedList<T>::isEmptyList(){
    return (Size == 0);
}

template<class T>
Node<T> &LinkedList<T>::front() {
    return *head;
}

template<class T>
Node<T> &LinkedList<T>::back() {
    Node<T> * current = head;
    if (head != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        return *current;
    }
    return *head;
}

template<class T>
void LinkedList<T>::copyList(const LinkedList<T> & list) {
    if (list.head != nullptr) {
// current element in the come in list
        Node<T> *current = list.head;
// the new element
        Node<T> *node = new Node<T>(current->value);
        this->head = node;
        this->Size++;

        Node<T> *thisCurrent = this->head;

        while (current->next != nullptr) {
            Node<T> *newNode = new Node<T>(current->next->value);
            thisCurrent->next = newNode;
            thisCurrent = newNode;
            this->Size++;
            current = current->next;
        }
    }
}

#endif //LINKEDLIST_LINKEDLISTHEADONLY_H
