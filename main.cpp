#include "SortedList.h"
#include <assert.h>
#include <iostream>

using std::cout;
using mtm::SortedList;


// void nodeTests()
// {
//     Node n1 = Node(3);
//     Node n2 = Node(6);
//     Node n3 = Node(4);
//     Node n4 = Node(13);
//     n1.setNext(&n2);
//     n2.setNext(&n3);
//     n3.setNext(&n4);

//     assert(n1.getData() == 3);
//     assert(n2.getData() == 6);
//     assert(n3.getData() == 4);
//     assert(n4.getData() == 13);

//     assert(n1.getNext()->getData() == 6);
//     assert(n1.getNext()->getData() == 4);
//     assert(n1.getNext()->getData() == 13);

//     n1.setNext(&n4);
//     n4.setNext(&n2);
//     n3.setNext(&n1);

//     assert(n1.getNext()->getData() == 13);
//     assert(n1.getNext()->getNext()->getData() == 6);
//     assert(n2.getNext()->getNext()->getNext()->getData() == 4);
//     assert(n1.getNext()->getNext()->getNext()->getNext()->getData() == 6);
// }

void listTest1()
{
    SortedList list1 = SortedList();
    int x = list1.length();
    cout << x;
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(4);
    list1.insert(5);
    list1.insert(6);
    list1.insert(7);
    list1.insert(8);
    list1.insert(9);
    list1.insert(10);
    mtm::printList(list1);
}

int main ()
{
    listTest1();
    return 0;
}