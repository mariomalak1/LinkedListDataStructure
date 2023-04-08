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
    friend std::ostream & operator<<(std::ostream &out, const Node<T> & n){
        out << n.value;
        return out;
    }
};

template<class T>
class LinkedList{
private:
    Node<T> * head;
    Node<T> * tail;
    int Size;
    void deleteList();
    void copyList(const LinkedList<T> & list);
public:
    LinkedList();

    // copy constructor
    LinkedList(const LinkedList<T> &list);

    void insertFirst(T value);

    void insertLast(T value);

    bool insert(T value, int pos);

    int size() const;

    // delete from first and last and from any position else
    void removeAtHead();
    void removeAtTail();
    void removeAt(int pos);

    T retrieveAt (int index);

    void replaceAt (T newElement, int index);

    bool isExist (T element);

    bool isItemAtEqual (T element, int index);

    // swap two nodes without swapping data
    void swap (int firstItemIdx, int secondItemIdx);

    void clear();

    bool isEmptyList();

    Node<T> * front();

    Node<T> * back();

    LinkedList & operator=(const LinkedList & list);

    LinkedList & operator+(const LinkedList & list){
        Node<T> * listCurrent = list.head;
        while (listCurrent != nullptr){
            this->insertLast(listCurrent->value);
            listCurrent = listCurrent->next;
        }
        return *this;
    }

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


    // Handel Exceptions

    // if user enter invalid index
    class IndexErrorException{
    private:
        std::string errorMessage;
    public:
        IndexErrorException(){
            errorMessage = "Index Error Happen";
        }
        void pushError(){
            std::cerr << errorMessage << std::endl;
        }
    };

    // if user work with empty list
    class EmptyListException{
    private:
        std::string errorMessage;
    public:
        EmptyListException(){
            errorMessage = "List Is Empty .. Error Happen";
        }
        void pushError(){
            std::cerr << errorMessage << std::endl;
        }
    };
};

template<class T>
LinkedList<T>::LinkedList(){
    tail = nullptr;
    head = nullptr;
    Size = 0;
}

template<class T>
void LinkedList<T>::deleteList(){
    while (Size)
        removeAtHead();
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

template<class T>
LinkedList<T>::LinkedList(const LinkedList &list){
    // this default in any empty one
    this->Size = 0;
    head = nullptr;
    tail = nullptr;
    this->copyList(list);
}

template<class T>
void LinkedList<T>::insertFirst(T value){
    Node<T> *temp = new Node<T>();
    temp->value = value;
    if (tail == nullptr && head == nullptr){
        head = temp;
        tail = temp;
    }
    else {
        temp->next = head;
        head = temp;
    }
    Size++;
}

template<class T>
void LinkedList<T>::insertLast(T value){
    Node<T> * temp = new Node<T>();
    temp->value = value;

    if (tail == nullptr && head == nullptr){
        head = temp;
        tail = temp;
    }
    else {
        if (tail == nullptr) {
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }
    Size++;
}

template<class T>
bool LinkedList<T>::insert(T value, int pos){
    if (pos == 1){
        this->insertFirst(value);
        Size++;
        return true;
    }
    else if (pos == this->size()){
        this->insertLast(value);
        Size++;
        return true;
    }
    else if(pos > size() or pos <= 0){
        return false;
    }
    else {
        int counter = 1;
        Node<T> *current = head;
        while (current != tail && counter < pos - 1) {
            counter++;
            current = current->next;
        }
        if (counter < pos) {
            Node<T> *temp = new Node<T>();
            temp->value = value;
            temp->next = current->next;
            current->next = temp;
            Size++;
            return true;
        } else {
            return false;
        }
    }
}

template<class T>
int LinkedList<T>::size() const{
    return Size;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list){
    // delete this list
    deleteList();
    this->copyList(list);
    return *this;
}

template<class T>
LinkedList<T>::~LinkedList(){
    deleteList();
    head = nullptr;
}

template<class T>
bool LinkedList<T>::isEmptyList(){
    return (Size == 0);
}

template<class T>
Node<T> * LinkedList<T>::front() {
    if (head == nullptr){
        throw (EmptyListException());
    }
    return head;
}

template<class T>
Node<T> *LinkedList<T>::back() {
    if (tail == nullptr && head == nullptr){
        throw (EmptyListException());
    }else{
        return tail;
    }
}

template<class T>
T LinkedList<T>::retrieveAt(int index) {

    // if any of them is nullptr therefore it's empty list
    if (head == nullptr || tail == nullptr){
        throw (EmptyListException());
    }

    else if (index > Size or index < 1){
        throw (IndexErrorException());
    }

    else{
        // return value on head
        if (index == 1){
            return head->value;
        }

        // return value on tail
        else if (index == Size){
            return tail->value;
        }

        // return value on specific index else head and tail
        else{
            Node<T> * current = head;
            int counter = 1;
            while (current != nullptr and counter < index){
                current = current->next;
                counter++;
            }
            return current->value;
        }

    }
}

template<class T>
void LinkedList<T>::replaceAt(T newElement, int index) {
    // if any of them is nullptr therefore it's empty list
    if (head == nullptr || tail == nullptr){
        throw (EmptyListException());
    }

    else if (index > Size or index < 1){
        throw (IndexErrorException());
    }

    else{
        // in first element
        if (index == 1){
            head->value = newElement;
        }

        // in last element
        else if(index == Size){
            tail->value = newElement;
        }

        // in specific element
        else{
            Node<T> * current = head;
            int counter = 1;
            while (current != nullptr and counter < index){
                current = current->next;
                counter++;
            }
            current->value = newElement;
        }
    }
}

template<class T>
bool LinkedList<T>::isExist(T element) {
    Node<T> * current = head;
    while (current != nullptr){
        if (current->value == element){
            return true;
        }
        current = current->next;
    }
    return false;
}

template<class T>
bool LinkedList<T>::isItemAtEqual(T element, int index) {
    // if any of them is nullptr therefore it's empty list
    if (head == nullptr || tail == nullptr){
        return false;
    }

    else if (index > Size or index < 1){
        return false;
    }

    else{
        // in first element
        if (index == 1){
            if (head->value == element){
                return true;
            }
        }

        // in last element
        else if(index == Size){
            if (tail->value == element){
                return true;
            }
        }

        // in specific element
        else{
            Node<T> * current = head;
            int counter = 1;
            while (current != nullptr and counter < index){
                current = current->next;
                counter++;
            }
            if (current->value == element){
                return true;
            }
        }
    }
    return false;
}

template<class T>
void LinkedList<T>::swap(int firstItemIdx, int secondItemIdx) {
    // if any of them is nullptr therefore it's empty list
    if (head == nullptr || tail == nullptr){
        throw (EmptyListException());
    }

    else if (firstItemIdx > Size or firstItemIdx < 1 or secondItemIdx > Size or secondItemIdx < 1){
        throw (IndexErrorException());
    }

    // if first element he enters it after the second element we correct this to be done
    else if (firstItemIdx > secondItemIdx){
        int index = firstItemIdx;
        firstItemIdx = secondItemIdx;
        secondItemIdx = firstItemIdx;
    }

    else{
        // get the element before the first element

        // if the first index is the head
        if (firstItemIdx == 1){

        }

        // get the element after the second element

        // if the second element is the tail
        if (secondItemIdx == Size){

        }


        // make swap
    }
}

template<class T>
void LinkedList<T>::clear() {
    deleteList();
    head = nullptr;
}

template<class T>
void LinkedList<T>::removeAtHead() {
    if (head == nullptr){
        throw (EmptyListException());
    }
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
}

template<class T>
void LinkedList<T>::removeAtTail() {
    if (tail == nullptr){
        throw (EmptyListException());
    }
    Node<T> * current = head;
    int counter = 1;
    while (current != nullptr && counter < Size - 1){
        current = current->next;
        counter++;
    }
    if (current != nullptr) {
        tail = current;
        delete current->next;
        current->next = nullptr;
        Size--;
    }
}

template<class T>
void LinkedList<T>::removeAt(int pos){

    // if the list is empty, will throw an error exception
    if(head == nullptr || tail == nullptr){
        throw (EmptyListException());
    }

    // if enter any invalid position, will throw an error exception
    else if (pos > Size || pos <= 0){
        throw (IndexErrorException());
    }



    // delete from first index
    else if (pos == 1){
        removeAtHead();
    }

    // delete from last index
    else if (pos == Size){
        removeAtTail();
    }

    // delete from any position in size the list
    else{
        Node<T> * current = head;
        while (current != nullptr && pos > 2){
            current = current->next;
            pos--;
        }
        if (pos == 2){
            Node<T> * temp = current->next->next;
            delete current->next;
            current->next = temp;
            temp = nullptr;
            Size--;
        }
    }
}

#endif //LINKEDLIST_LINKEDLISTHEADONLY_H
