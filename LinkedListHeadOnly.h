/*
 * this file is implement to linked list data structure in C++
 * this version is with head pointer only.
 * */

#ifndef LINKEDLIST_LINKEDLISTHEADONLY_H
#define LINKEDLIST_LINKEDLISTHEADONLY_H
#include <iostream>
struct Node{
    int value;
    Node * next;
    Node(){
        value = 0;
        next = nullptr;
    }
    Node(int val){
        value = val;
        next = nullptr;
    }
};

class LinkedList{
private:
    Node * head;
    int Size;
    void deleteList();
public:
    LinkedList();

    LinkedList(int value);

    // copy constructor
    LinkedList(const LinkedList &list);

    void insertFirst(int value);

    void insertLast(int value);

    bool insert(int value, int pos);

    int size() const;

    bool deleteIndex(int pos);

    bool isEmptyList();

    Node & front();

    Node &back();

    LinkedList & operator=(const LinkedList & list);

    friend std::ostream& operator<<(std::ostream& out,const LinkedList & list);

    ~LinkedList();
};

LinkedList::LinkedList(){
    Size = 0;
    head = nullptr;
}

LinkedList::LinkedList(int value){
    Node * node = new Node(value);
    head = node;
    Size = 1;
}

void LinkedList::deleteList(){
    while (Size)
        deleteIndex(1);
}

LinkedList::LinkedList(const LinkedList &list){
    // this default in any empty one
    this->Size = 0;
    head = nullptr;

    if (list.head != nullptr){
        // current element in the come in list
        Node * current = list.head;
        // the new element
        Node * node = new Node(current->value);
        this->head = node;
        this->Size++;

        Node * thisCurrent = this->head;

        while (current->next != nullptr){
            Node * newNode = new Node(current->next->value);
            thisCurrent->next = newNode;
            thisCurrent = newNode;
            this->Size++;
            current = current->next;
        }
    }
}

void LinkedList::insertFirst(int value){
    Node * node = new Node(value);
    if (head == nullptr){
        head = node;
    }else{
        node->next = head;
        head = node;
    }
    Size++;
}

void LinkedList::insertLast(int value){
    Node * node = new Node(value);
    if (head == nullptr){
        head = node;
    }
    else {
        Node *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
    Size++;
}

bool LinkedList::insert(int value, int pos){
    Node * current = head;
    if (pos > Size || pos <= 0){
        return false;
    }
    while (current->next != nullptr && pos > 1){
        current = current->next;
        pos--;
    }
    if (pos == 1){
        Node * node = new Node(value);
        node->next = current->next;
        current->next = node;
        Size++;
        return true;
    }else if (pos <= 0){
        return false;
    }
    return false;
}

int LinkedList::size() const{
    return Size;
}

bool LinkedList::deleteIndex(int pos){
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
            Node * temp = head->next;
            delete head;
            head = temp;
            temp = nullptr;
        }
        Size--;
        return true;
    }

        // delete from last index
    else if (pos == Size){
        Node * current = head;
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
        Node * current = head;
        while (current != nullptr && pos > 1){
            current = current->next;
            pos--;
        }
        if (pos == 1){
            Node * temp = current->next->next;
            delete current->next;
            current->next = temp;
            temp = nullptr;
            Size--;
            return true;
        }
    }
    return false;
}

LinkedList &LinkedList::operator=(const LinkedList &list){
    // delete this list
    deleteList();

    if (list.head != nullptr){
        // current element in the come in list
        Node * current = list.head;
        // the new element
        Node * node = new Node(current->value);
        this->head = node;
        this->Size++;

        Node * thisCurrent = this->head;

        while (current->next != nullptr){
            Node * newNode = new Node(current->next->value);
            thisCurrent->next = newNode;
            thisCurrent = newNode;
            this->Size++;
            current = current->next;
        }
    }

    return *this;
}

std::ostream &operator<<(std::ostream &out, const LinkedList &list){
    if (list.head == nullptr){
        out << "[]" << std::endl;
        return out;
    }
    Node *current;
    current = list.head;
    out << "[";
    while (current->next != nullptr){
        out << current->value << " -> ";
        current = current->next;
    }
    out << current->value << "]";
    return out;
}

LinkedList::~LinkedList(){
    deleteList();
}

bool LinkedList::isEmptyList(){
    return (Size == 0);
}

Node &LinkedList::front() {
    return *head;
}

Node &LinkedList::back() {
    Node * current = head;
    if (head != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        return *current;
    }
    return *head;
}

#endif //LINKEDLIST_LINKEDLISTHEADONLY_H
