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
    Node<T> * getNodeBefore(int index);
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
Node<T> *LinkedList<T>::getNodeBefore(int index) {
    if(head == nullptr && tail == nullptr){
        throw (EmptyListException());
    }
    else if (index > Size or index < 1){
        throw (IndexErrorException());
    }

    // no node before
    if (index == 1){
        return nullptr;
    }

        // before it the head node
    else if (index == 2){
        return head;
    }

    else if (index == Size){
        Node<T> * currentNode = head;
        int counter = 1;
        while (currentNode != nullptr && counter < Size - 1){
            currentNode = currentNode->next;
            counter++;
        }

        return currentNode;
    }

    else {
        Node<T> * currentNode = head;
        int counter = 1;
        while (currentNode != nullptr && counter < index - 1){
            currentNode = currentNode->next;
            counter++;
        }
        return currentNode;
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
void LinkedList<T>::clear() {
    deleteList();
    head = nullptr;
    tail = nullptr;
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

template<class T>
void LinkedList<T>::swap(int firstItemIdx, int secondItemIdx) {

    // check that the size is more than one element, as if it less than two, no swap will be done
    if (Size > 1) {

        // if first element he enters it after the second element we correct this to be done
        if (firstItemIdx > secondItemIdx) {
            int index = firstItemIdx;
            firstItemIdx = secondItemIdx;
            secondItemIdx = index;
        }


        // if they want to swap the same place, then nothing will happen
        if (firstItemIdx != secondItemIdx) {

            // get the node before the first node
            Node<T> *NodeBeforeFirst = getNodeBefore(firstItemIdx);

            // if index of the first node is 1 it will return nullptr, so this check on it
            // if he wants the node before the first element
            // it will create a new node before the first element,
            // and make (NodeBeforeFirst) pointer will point to the new Node
            if (NodeBeforeFirst == nullptr) {
                Node<T> *unRealNodeBeforeFirst = new Node<T>;
                unRealNodeBeforeFirst->next = head;
                NodeBeforeFirst = unRealNodeBeforeFirst;
            }

            // make pointer to the first node
            Node<T> *pointerFirstNode = NodeBeforeFirst->next;

            // to check that if They are consecutive or not
            if (secondItemIdx - firstItemIdx == 1) {
                // then the element before the second it also the same first element

                // make pointer to the second node
                Node<T> *pointerSecondNode = pointerFirstNode->next;

                // get what the second element arrow next point to it
                Node<T> *pointerToNextOfSecond = pointerSecondNode->next;

                // change the second element place
                // then make the node before the first point to the second
                NodeBeforeFirst->next = pointerSecondNode;
                // make the second arrow next point to the first pointer, as it become the first for now
                pointerSecondNode->next = pointerFirstNode;

                // change the first element place
                pointerFirstNode->next = pointerToNextOfSecond;

                if (secondItemIdx == Size) {
                    tail = pointerFirstNode;
                }
                if (firstItemIdx == 1) {
                    head = pointerSecondNode;
                }
                // set all pointers I used to nullptr
                pointerSecondNode = nullptr;
                pointerToNextOfSecond = nullptr;
                pointerFirstNode = nullptr;
            } else {

                // if index of the first node is 1 it will return nullptr, so this check on it
                // if he wants the node before the first element
                // it will create a new node before the first element,
                // and make (NodeBeforeFirst) pointer will point to the new Node
                if (NodeBeforeFirst == nullptr) {
                    Node<T> *unRealNodeBeforeFirst = new Node<T>;
                    unRealNodeBeforeFirst->next = head;
                    NodeBeforeFirst = unRealNodeBeforeFirst;
                }

                // get the node before the second node
                Node<T> *NodeBeforeSecond = getNodeBefore(secondItemIdx);

                // make pointer to the second node
                Node<T> *pointerSecondNode = NodeBeforeSecond->next;

                // hold the next node to the second element
                Node<T> *NextNodeSecond = pointerSecondNode->next;


                // move of the second element
                // make the second Node in place of first Node
                // it makes the node before the first element will point to the second element
                NodeBeforeFirst->next = pointerSecondNode;
                // it makes the second element arrow next will point to what the first node arrow next point to it
                pointerSecondNode->next = pointerFirstNode->next;


                // move of the first element
                // make the first Node in place of second Node
                // it makes the node before the second element will point to the first element
                NodeBeforeSecond->next = pointerFirstNode;
                // it makes the first element arrow next will point to what the second element was point
                pointerFirstNode->next = NextNodeSecond;

                // if we work with the first element
                // must make the head point to the second pointer, as it become the first element
                if (firstItemIdx == 1) {
                    head = pointerSecondNode;
                }


                // set all pointers to null
                NodeBeforeFirst = nullptr;
                NodeBeforeSecond = nullptr;
                pointerFirstNode = nullptr;
                pointerSecondNode = nullptr;
                NextNodeSecond = nullptr;
            }
        }
    }
    else{
        // to throw an exception
        throw (IndexErrorException());
    }
}

#endif //LINKEDLIST_LINKEDLISTHEADONLY_H
