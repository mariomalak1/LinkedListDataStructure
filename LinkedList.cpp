#include <iostream>

template<typename T>
struct Node{
    T value;
    Node* next;
    Node(){
        value = T();
        next = nullptr;
    }
};

template<typename T>
class LinkedList{
    Node<T>* Head;
    Node<T>* Tail;
    int Size;
public:
    LinkedList(){
        Tail = nullptr;
        Head = nullptr;
        Size = 0;
    }

    void addFirst(int value){
        Node<T> *temp = new Node<T>();
        temp->value = value;
        if (Tail == nullptr && Head == nullptr){
            Head = temp;
            Tail = temp;
        }
        else {
            temp->next = Head;
            Head = temp;
        }
        Size++;
    }

    void addLast(int value){
        Node<T> * temp = new Node<T>();
        temp->value = value;

        if (Tail == nullptr && Head == nullptr){
            Head = temp;
            Tail = temp;
        }
        else {
            if (Tail == nullptr) {
                Tail = temp;
            } else {
                Tail->next = temp;
                Tail = temp;
            }
        }
        Size++;
    }

    int size() const{
        return this->Size;
    }

    bool insert(int value, int pos){
        if (pos == 1){
            this->addFirst(value);
            return true;
        }
        else if (pos == this->size()){
            this->addLast(value);
            return true;
        }
        else if(pos > size() or pos <= 0){
            return false;
        }
        else {
            int counter = 1;
            Node<T> *current = Head;
            while (current != Tail && counter < pos - 1) {
                counter++;
                current = current->next;
            }
            if (counter < pos) {
                Node<T> *temp = new Node<T>();
                temp->value = value;
                temp->next = current->next;
                current->next = temp;
                return true;
            } else {
                return false;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& out,const LinkedList & list){
        if (list.Head == nullptr && list.Tail == nullptr){
            out << "[]" << std::endl;
            return out;
        }
        Node<T> *current;
        current = list.Head;
        out << "[";
        while (current->next != nullptr){
            out << current->value << " -> ";
            current = current->next;
        }
        out << list.Tail->value << "]";
        return out;
    }
};