#include <iostream>
//#include "LinkedListHeadOnly.h"
#include "LinkedList.h"

using namespace std;
int main() {
    LinkedList<int> listOne;
    listOne.insertFirst(2);
    listOne.insertFirst(1);
    listOne.insertFirst(0);
    listOne.insertFirst(-1);
    listOne.insertFirst(-2);
    listOne.insertLast(5);
    listOne.insertLast(6);
    listOne.insert(3, 5);
    listOne.insert(4, 6);
    cout << listOne << endl;

    cout << "size of list is : " << listOne.size() << endl;

    LinkedList<int> listTwo = listOne;

    cout << "list two : " << listTwo << endl;

    listOne.removeAtHead();
    listOne.removeAtTail();
    listOne.removeAt(4);

    cout << "after delete from list one : " << listOne << endl;

    cout << "size of list is : " << listOne.size() << endl;


    cout << "the value at index 1 : " << listOne.retrieveAt(1) << endl;
    cout << "the value at last element : " << listOne.retrieveAt(listOne.size()) << endl;
    cout << "the value at index 5 : " << listOne.retrieveAt(5) << endl;

    // will throw an error
//    cout << listOne.retrieveAt(255) << endl;

    listOne.replaceAt(555,5);

    // will throw an error
//    listOne.replaceAt(555,555);

    cout << "after replace in list one : " << listOne << endl;

    cout << "is at index 5 value 555 : " <<  listOne.isItemAtEqual(555,5) << endl;
    cout << "is at index 5 value 25 : " <<  listOne.isItemAtEqual(25,5) << endl;
    cout << "is at index 25 value 25 : " <<  listOne.isItemAtEqual(25,25) << endl;

    LinkedList<int> listFour;

    listFour = listOne + listTwo;

    cout << "list four : " << listFour << endl;

    listOne.clear();

    cout << listOne << endl;

    cout << "is empty list : " << listOne.isEmptyList() << endl;

    cout << "before swap in list two : " << listTwo << endl;

    listTwo.swap(1, 9);

    cout << "before swap in list two : " << listTwo << endl;


    listTwo.swap(2, 9);
    cout << "before swap in list two : " << listTwo << endl;

    listTwo.swap(1, 7);
    cout << "before swap in list two : " << listTwo << endl;

    listTwo.swap(5, 6);

    cout << "before swap in list two : " << listTwo << endl;

    listTwo.swap(7, 1);

    cout << "after swap in list two : " << listTwo << endl;

    // test swap between the last element and the element before it
    listTwo.swap(listTwo.size() - 1,listTwo.size());
    cout << "after swap in list two : " << listTwo << endl;

    listTwo.swap(1,2);
    cout << "after swap in list two : " << listTwo << endl;

    listOne.insertLast(0);
//    listOne.insertFirst(-1);

    cout << "listOne : "<< listOne << endl;

    // it will return error
//    listOne.swap(1,2);


    return 0;
}