#ifndef _SORTED_LIST_H
#define _SORTED_LIST_H

#include <stdexcept>
#include <assert.h>

// Assuming class T has:
// Copy constructor, Destructor, operator<,
#define T int

namespace mtm
{
    class SortedList
    {
    public:
        class const_iterator;
        SortedList();
        //~SortedList();
        //SortedList(const SortedList& sorted_list);
        SortedList& operator=(const SortedList& list);
        void insert(T element);
        //remove
        int length();
        //filter
        //apply
        const_iterator begin();
        const_iterator end();

        

        // REMOVE BEFORE SUBMITTION
        friend void printList(const SortedList& list);

    private:
        class Node;
        
        int size;
        Node *first;
        Node *last;

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
        Node* getNext() const;
        const T& getData() const;
        Node* copyNodeList() const;

    private:
        T data;
        SortedList::Node *next;
    };




    //=========================================
    //========== Node implementation ==========
    //=========================================
    SortedList::Node::Node(T element) : data(T(element)), next(nullptr){}

    void SortedList::Node::setNext(SortedList::Node* node)
    {
        this->next = node;
    }

    SortedList::Node* SortedList::Node::getNext() const
    {
        return this->next;
    }

    const T& SortedList::Node::getData() const
    {
        return this->data;
    }

    SortedList::Node* SortedList::Node::copyNodeList() const
    {
        Node *return_node = new Node(data);
        Node *current_list_iterator = next;
        Node *new_list_iterator     = return_node;
        while (current_list_iterator != nullptr)
        {
            try
            {
                Node *new_node = new Node(current_list_iterator->data);
                new_list_iterator->next = new_node;
                current_list_iterator = current_list_iterator->next;
                new_list_iterator     = new_list_iterator->next;
            }
            catch (std::bad_alloc)
            {
                while (return_node != nullptr)
                {
                    Node* temp_node = return_node->next;
                    delete return_node;
                    return_node = temp_node;
                }
            }
        }

        return return_node;
    }





    //=========================================
    //======== iterator implementation ========
    //=========================================

    class SortedList::const_iterator
    {
    public:
        
        const_iterator(const const_iterator& iterator) = default;
        ~const_iterator() = default;
        const_iterator& operator=(const const_iterator& iterator) = default;
        const_iterator& operator++(int);
        bool operator==(const_iterator iterator) const;
        const T& operator*();
    private:
        const_iterator(const SortedList* list, Node* node);
        const SortedList* list;
        const Node* current_node;
        friend class SortedList;

    };
    
    SortedList::const_iterator::const_iterator(const SortedList* list, Node* node) : 
                                list(list), current_node(node) {}

    SortedList::const_iterator& SortedList::const_iterator::operator++(int)
    {
        if (current_node == nullptr)
        {
            throw std::out_of_range("SortedList const_iterator is out of bounds");
        }
        this->current_node = current_node->getNext();
        return *this;
    }

    bool SortedList::const_iterator::operator==(SortedList::const_iterator iterator) const
    {
        assert(this->list == iterator.list);
        return current_node == iterator.current_node;
    }

    const T& SortedList::const_iterator::operator*()
    {
        return this->current_node->getData();
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

        Node* current_node = first;
        while (current_node != nullptr && current_node->getNext() != nullptr &&
               current_node->getNext()->getData() < element)
        {
            current_node = current_node->getNext();
        }
        
        return current_node;
    }


    SortedList::SortedList()
    {
        size   = 0;
        first  = nullptr;
        last   = nullptr;
    }

    void SortedList::insert(T element)
    {
        Node *new_node = new Node(element);

        // Case: List is currently empty OR
        // Case: New element should be placed first in list
        if (size == 0 || element < first->getData())
        {
            new_node->setNext(first);
            first = new_node;
            if (last == nullptr)
            {
                last = new_node;
            }
            size++;
            return;
        }

        // Case: New element should be placed somewhere in the middle / end
        Node* prev_node = findPlacement(element);
        new_node->setNext(prev_node->getNext());
        prev_node->setNext(new_node);
        size++;

        if (last->getNext() == new_node)
        {
            last = new_node;
        }
    }

    SortedList& SortedList::operator=(const SortedList& list)
    {
        // Self assignment handling
        if (this == &list)
        {
            return *this;
        }

        // Copy the nodes to temp var
        Node* coppied_list = list.first->copyNodeList();
        
        // Make list point to the new nodes, update size, return list
        first = coppied_list;
        size  = list.size;
        return *this;
    }

    int SortedList::length()
    {
        return this->size;
    }

    SortedList::const_iterator SortedList::begin()
    {
        return SortedList::const_iterator(this, this->first);
    }

    SortedList::const_iterator SortedList::end()
    {
        return SortedList::const_iterator(this, this->last->getNext());
    }

    // DELETE BEFORE SUBMITTION
    void printList(const SortedList& list)
    {
        SortedList::Node* node = list.first;
        while (node != nullptr)
        {
            printf("%d, ",node->getData());
            node = node->getNext();
        }
        printf("\n");
    }
}




#endif