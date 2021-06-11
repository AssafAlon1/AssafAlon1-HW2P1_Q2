#include "SortedList.h"
#include <assert.h>
#include <iostream>

using std::cout;
using mtm::SortedList;


bool isEven(int num)
{
    return !(num % 2);
}

bool isOdd(int num)
{
    return !isEven(num);
}

bool isTreven(int num)
{
    return !(num % 3);
}

int addThree(int num)
{
    return num + 3;
}

int subtract3Multiply2(int num)
{
    return (num-3)*2;
}

int zero(int num)
{
    return 0;
}

int multiplyNegative1(int num)
{
    return -num;
}

int square(int num)
{
    return num*num;
}

void listTest1()
{
    SortedList list1 = SortedList();
    //int x = list1.length();
    //cout << x;
    list1.insert(0);
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(-4);
    list1.insert(5);
    list1.insert(11);
    list1.insert(6);
    list1.insert(7);
    list1.insert(8);
    list1.insert(3);
    list1.insert(9);
    list1.insert(10);


    int cnt = 0;
    for (SortedList::const_iterator iterator = list1.begin() ; !(iterator == list1.end()) ; iterator++)
    {
        cout << cnt++ ;
    }
    cout << std::endl;
    mtm::printList(list1);
    cout << std::endl;
}

void listTest2()
{
    // List creation
    SortedList list1 = SortedList();
    list1.insert(1);
    list1.insert(2);
    list1.insert(5);
    list1.insert(5);
    list1.insert(4);
    list1.insert(3);
    list1.insert(3);
    list1.insert(3);
    list1.insert(3);
    list1.insert(9);
    list1.insert(8);

    // Check insert and iterator
    SortedList::const_iterator iter = list1.begin();
    assert(*(iter++) == 1);
    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 8);
    assert(*(iter++) == 9);
    assert(iter == list1.end());
    assert(list1.length() == 11);

    // Check copy constructor
    SortedList list2 = list1;
    iter = list2.begin();
    assert(*(iter++) == 1);
    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 8);
    assert(*(iter++) == 9);
    assert(iter == list2.end());
    assert(list2.length() == 11);

    // Check remove function - delete from start
    iter = list2.begin();
    list2.remove(iter);
    iter = list2.begin();

    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 8);
    assert(*(iter++) == 9);
    assert(iter == list2.end());
    assert(list2.length() == 10);

    // Check remove function - delete from mid
    iter = list2.begin();
    iter++;
    iter++;
    iter++;
    list2.remove(iter);
    iter = list2.begin();

    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 8);
    assert(*(iter++) == 9);
    assert(iter == list2.end());
    assert(list2.length() == 9);


    // Check remove function - delete from mid
    iter = list2.begin();
    iter++; iter++; iter++; iter++; iter++; iter++; iter++;
    list2.remove(iter);
    iter = list2.begin();

    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 9);
    assert(iter == list2.end());
    assert(list2.length() == 8);


    // Check remove function - delete from end
    iter = list2.begin();
    iter++; iter++; iter++; iter++; iter++; iter++; iter++;
    list2.remove(iter);
    iter = list2.begin();

    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(iter == list2.end());
    assert(list2.length() == 7);


    // Check the original list is unchanged
    iter = list1.begin();
    assert(*(iter++) == 1);
    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 8);
    assert(*(iter++) == 9);
    assert(iter == list1.end());

    // Check other operator++
    iter = list1.begin();
    assert(*(++iter) == 2);
    assert(*(++iter) == 3);
    assert(*(++iter) == 3);
    assert(*(++iter) == 3);
    assert(*(++iter) == 3);
    assert(*(++iter) == 4);
    assert(*(++iter) == 5);
    assert(*(++iter) == 5);
    assert(*(++iter) == 8);
    assert(*(++iter) == 9);
    assert(++iter == list1.end());

    // Check assignment operator
    SortedList list3;
    list3 = list2;
    iter = list3.begin();

    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(iter == list3.end());

    try { iter++; }
    catch(std::out_of_range& err) {}

    list3 = list1;
    iter = list3.begin();
    assert(*(iter++) == 1);
    assert(*(iter++) == 2);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 3);
    assert(*(iter++) == 4);
    assert(*(iter++) == 5);
    assert(*(iter++) == 5);
    assert(*(iter++) == 8);
    assert(*(iter++) == 9);
    assert(iter == list3.end());
    return;
}


void listTest3()
{
    SortedList list1 = SortedList();
    
    list1.insert(14);
    list1.insert(18);
    list1.insert(62);
    list1.insert(47);
    list1.insert(31);
    list1.insert(59);
    list1.insert(96);
    list1.insert(69);

    SortedList::const_iterator iter = list1.begin();
    assert(*(iter++) == 14);
    assert(*(iter++) == 18);
    assert(*(iter++) == 31);
    assert(*(iter++) == 47);
    assert(*(iter++) == 59);
    assert(*(iter++) == 62);
    assert(*(iter++) == 69);
    assert(*(iter++) == 96);
    assert(iter == list1.end());
    assert(list1.length() == 8);

    SortedList list2 = list1.filter(isEven);
    iter = list2.begin();
    assert(*(iter++) == 14);
    assert(*(iter++) == 18);
    assert(*(iter++) == 62);
    assert(*(iter++) == 96);
    assert(iter == list2.end());
    assert(list2.length() == 4);

    list2 = list1.filter(isOdd);
    iter = list2.begin();
    assert(*(iter++) == 31);
    assert(*(iter++) == 47);
    assert(*(iter++) == 59);
    assert(*(iter++) == 69);
    assert(iter == list2.end());
    assert(list2.length() == 4);

    list2 = list1.filter(isTreven);
    iter = list2.begin();
    assert(*(iter++) == 18);
    assert(*(iter++) == 69);
    assert(*(iter++) == 96);
    assert(iter == list2.end());
    assert(list2.length() == 3);

}


// void listTest4()
// {
//     SortedList list1 = SortedList();
//     list1.insert(6);
//     list1.insert(2);
//     list1.insert(4);
//     list1.insert(3);
//     list1.insert(9);
//     list1.insert(-3);
//     list1.insert(1);
//     list1.insert(-1);

//     SortedList::const_iterator iter = list1.begin();
//     //*iter = 5;   <-- Verify actually const

//     SortedList list2 = list1.apply(addThree());
//     iter = list2.begin();
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 2);
//     assert(*(iter++) == 4);
//     assert(*(iter++) == 5);
//     assert(*(iter++) == 6);
//     assert(*(iter++) == 7);
//     assert(*(iter++) == 9);
//     assert(*(iter++) == 12);
//     assert(iter == list1.end());
//     assert(list1.length() == 8);


//     list2 = list1.apply(subtract3Multiply2());
//     iter = list2.begin();
//     assert(*(iter++) == -12);
//     assert(*(iter++) == -8);
//     assert(*(iter++) == -4);
//     assert(*(iter++) == -2);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 2);
//     assert(*(iter++) == 6);
//     assert(*(iter++) == 12);
//     assert(iter == list1.end());
//     assert(list1.length() == 8);

    
//     list2 = list1.apply(zero());
//     iter = list2.begin();
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(*(iter++) == 0);
//     assert(iter == list1.end());
//     assert(list1.length() == 8);

//     list2 = list1.apply(multiplyNegative1());
//     iter = list2.begin();
//     assert(*(iter++) == -9);
//     assert(*(iter++) == -6);
//     assert(*(iter++) == -4);
//     assert(*(iter++) == -3);
//     assert(*(iter++) == -2);
//     assert(*(iter++) == -1);
//     assert(*(iter++) == 1);
//     assert(*(iter++) == 3);
//     assert(iter == list1.end());
//     assert(list1.length() == 8);


//     list2 = list1.apply(multiplyNegative1());
//     iter = list2.begin();
//     assert(*(iter++) == 1);
//     assert(*(iter++) == 1);
//     assert(*(iter++) == 4);
//     assert(*(iter++) == 9);
//     assert(*(iter++) == 9);
//     assert(*(iter++) == 16);
//     assert(*(iter++) == 36);
//     assert(*(iter++) == 81);
//     assert(iter == list1.end());
//     assert(list1.length() == 8);
// }

int main ()
{
    listTest1();
    listTest2();
    listTest3();
    //listTest4();
    return 0;
}