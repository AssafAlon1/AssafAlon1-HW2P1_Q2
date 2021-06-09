#ifndef _SORTED_LIST_H
#define _SORTED_LIST_H

// Assuming class T has:
// Copy constructor, Destructor, operator<,
#define T int

class SortedList
{
public:
    SortedList();
    //~SortedList();
    //SortedList(const SortedList& sorted_list);
    //operator=
    void insert(T element);
    //remove
    int length();
    //filter
    //apply
    //begin
    //end

    

private:
    class Node;
    
    int size;
    Node *first;
    //Node *last;

    Node* findPlacement(T element);
};


class SortedList::Node
{
public:
    Node(T element);
    Node(const Node& node) = default;
    Node& operator=(const Node& node);
    ~Node() = default;

    void setNext(Node* node);
    Node* getNext();
    T& getData();

private:
    T data;
    SortedList::Node *next;
};


//=========================================
//========== Node implementation ==========
//=========================================
SortedList::Node::Node(T element)
{
    data = T(element);
    next = nullptr;
}

void SortedList::Node::setNext(SortedList::Node* node)
{
    this->next = node;
}

SortedList::Node* SortedList::Node::getNext()
{
    return this->next;
}

T& SortedList::Node::getData()
{
    return this->data;
}




//=========================================
//======= SortedList implementation =======
//=========================================

// Returns nullptr if the list is currently empty OR the placement is the first node
// Otherwise returns the node that should be placed before a new node containing element in the list
SortedList::Node* SortedList::findPlacement(T element)
{
    if (size == 0 || element < first->getData())
    {
        return nullptr;
    }

    return nullptr; // <---- implement here
}


SortedList::SortedList()
{
    size   = 0;
    first  = nullptr;
    //last   = nullptr;
}

void SortedList::insert(T element)
{
    Node new_node = Node(element);

    // Case: List is currently empty
    if (size == 0)
    {
        first = &new_node;
        size++;
        return;
    }

    // Case: New element should be placed first in list
    if (element < first->getData())
    {
        new_node.setNext(first);
        first = &new_node;
    }

    // Case: New element should be placed somewhere in the middle / end
    Node* prev_node = findPlacement(element);
    new_node.setNext(prev_node->getNext());
    prev_node->setNext(&new_node);
    
}

int SortedList::length()
{
    return this->size;
}

#endif