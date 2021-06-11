#ifndef _SORTED_LIST_H
#define _SORTED_LIST_H

#include <stdexcept>
#include <assert.h>

// Assuming class T has:
// Copy constructor, Destructor, operator<, 
//#define T int

namespace mtm
{
    template<class T>
    class SortedList
    {
    public:
        class const_iterator;
        SortedList();
        ~SortedList();
        SortedList(const SortedList& sorted_list);
        SortedList& operator=(const SortedList& list);
        void insert(T element);
        void remove(const_iterator iterator);
        int length();
        
        template<class S>
        SortedList filter(bool function(S));          // Make it reference?

        template<class S>
        SortedList apply(T function(S));              // Make it generic
        const_iterator begin();
        const_iterator end();

    private:
        class Node;
        
        int size;
        Node *first;
        //Node *last;

        Node* findPlacement(T element);
        Node* findPlacement(const_iterator iterator);
    };






    template<class T>
    class SortedList<T>::Node
    {
    public:
        Node(T element);
        Node(const Node& node) = default;
        Node& operator=(const Node& node);
        ~Node() = default;

        void setNext(Node* node);
        Node* getNext() const;
        const T& getData() const;
        void destroyNodeList();
        Node* copyNodeList() const;

    private:
        T data;
        SortedList<T>::Node *next;
    };




    //=========================================
    //========== Node implementation ==========
    //=========================================
    template<class T>
    SortedList<T>::Node::Node(T element) : data(T(element)), next(nullptr){}

    template<class T>
    void SortedList<T>::Node::setNext(SortedList<T>::Node* node)
    {
        this->next = node;
    }

    template<class T>
    typename SortedList<T>::Node* SortedList<T>::Node::getNext() const
    {
        return this->next;
    }

    template<class T>
    const T& SortedList<T>::Node::getData() const
    {
        return this->data;
    }

    template<class T>
    void SortedList<T>::Node::destroyNodeList()
    {
        Node* next_node = next;
        while (next_node != nullptr)
        {
            Node* temp_node = next_node->next;
            delete next_node;
            next_node = temp_node;
        }
        delete this;
    }

    template<class T>
    typename SortedList<T>::Node* SortedList<T>::Node::copyNodeList() const
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
            catch (std::bad_alloc& err)
            {
                while (return_node != nullptr)
                {
                    Node* temp_node = return_node->next;
                    delete return_node;
                    return_node = temp_node;
                }
                throw;
            }
        }

        return return_node;
    }





    //=========================================
    //======== iterator implementation ========
    //=========================================
    template<class T>
    class SortedList<T>::const_iterator
    {
    public:
        
        const_iterator(const const_iterator& iterator) = default;
        ~const_iterator() = default;
        const_iterator& operator=(const const_iterator& iterator) = default;
        const_iterator& operator++();
        const_iterator operator++(int);
        bool operator==(const_iterator iterator) const;
        const T& operator*();
    private:
        const_iterator(const SortedList* list, Node* node);
        const SortedList* list;
        const Node* current_node;
        friend class SortedList;

    };
    
    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>* list, Node* node) : 
                                list(list), current_node(node) {}

    template<class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
    {
        if (current_node == nullptr)
        {
            throw std::out_of_range("SortedList const_iterator is out of bounds");
        }
        this->current_node = current_node->getNext();
        return *this;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
    {
        if (current_node == nullptr)
        {
            throw std::out_of_range("SortedList const_iterator is out of bounds");
        }
        const_iterator result = *this;
        this->current_node = current_node->getNext();
        return result;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(SortedList<T>::const_iterator iterator) const
    {
        assert(this->list == iterator.list);
        return current_node == iterator.current_node;
    }

    template<class T>
    const T& SortedList<T>::const_iterator::operator*()
    {
        return this->current_node->getData();
    }








    //=========================================
    //======= SortedList implementation =======
    //=========================================

    // Returns nullptr if the list is currently empty OR the placement is the first node
    // Otherwise returns the node that should be placed before a new node containing element in the list
    template<class T>
    typename SortedList<T>::Node* SortedList<T>::findPlacement(T element)
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

    template<class T>
    typename SortedList<T>::Node* SortedList<T>::findPlacement(const_iterator iterator)
    {
        if (size == 0 || iterator == this->end() || iterator.current_node == first)
        {
            return nullptr;
        }
        Node* current_node = first;
        while (current_node != nullptr && current_node->getNext() != nullptr)
        {
            if(iterator.current_node == current_node->getNext())
            {
                return current_node;
            }
            current_node = current_node->getNext();
        }
        return nullptr;
    }

    template<class T>
    SortedList<T>::SortedList()
    {
        size   = 0;
        first  = nullptr;
        //last   = nullptr;
    }

    template<class T>
    SortedList<T>::~SortedList()
    {
        first->destroyNodeList();
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList& sorted_list)
    {
        first = sorted_list.first->copyNodeList();
        size = sorted_list.size;

        SortedList::Node* current_node = first;
        while (current_node != nullptr && current_node->getNext() != nullptr)
        {
            current_node = current_node->getNext();
        }
        //last = current_node;
    }

    template<class T>
    void SortedList<T>::insert(T element)
    {
        Node *new_node = new Node(element);

        // Case: List is currently empty OR
        // Case: New element should be placed first in list
        if (size == 0 || element < first->getData())
        {
            new_node->setNext(first);
            first = new_node;
            // if (last == nullptr)
            // {
            //     last = new_node;
            // }
            size++;
            return;
        }

        // Case: New element should be placed somewhere in the middle / end
        Node* prev_node = findPlacement(element);
        new_node->setNext(prev_node->getNext());
        prev_node->setNext(new_node);
        size++;

        // if (last->getNext() == new_node)
        // {
        //     last = new_node;
        // }
    }
    
    template<class T>
    void SortedList<T>::remove(SortedList<T>::const_iterator iterator)
    {
        if (iterator == this->end() || size == 0)
        {
            return;
        }
        SortedList::Node* prev_node = findPlacement(iterator);
        
        // Case: the first node should be removed
        if(prev_node == nullptr)
        {
            first = iterator.current_node->getNext();
            delete iterator.current_node;               // Works?
            size--;
            return;
        }

        SortedList::Node* current_node = prev_node->getNext();
        prev_node->setNext(current_node->getNext());
        delete current_node;
        size--;


        // Case: the last node should be removed
        // if (prev_node == last)
        // {
        //     // Update the
        //     last = findPlacement(const_iterator(this, last));
        // }
    }

    template<class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& list)
    {
        // Self assignment handling
        if (this == &list)
        {
            return *this;
        }

        // Copy the nodes to temp var
        Node* coppied_list = list.first->copyNodeList();
        
        // CAN'T FAIL BEYONG THIS POINT
        // Make list point to the new nodes, update size, return list
        
        if (first) // If there were nodes in the list beforehand
        {
            first->destroyNodeList();
        }
        first = coppied_list;
        size  = list.size;
        return *this;
    }

    template<class T>
    int SortedList<T>::length()
    {
        return this->size;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin()
    {
        return SortedList::const_iterator(this, this->first);
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end()
    {
        //if (this->last == nullptr)
        //{
            return SortedList<T>::const_iterator(this, nullptr);
        //}
        //return SortedList::const_iterator(this, this->last->getNext());
    }

    template<class T>
    template<class S>
    SortedList<T> SortedList<T>::filter(bool function(S))
    {
        SortedList<T> list = SortedList<T>();
        for (const_iterator iterator = this->begin() ; !(iterator == this->end()) ; ++iterator)
        {
            if (function(*iterator))
            {
                list.insert(*iterator);
            }
        }
        return list;
    }

    template<class T>
    template<class S>
    SortedList<T> SortedList<T>::apply(T function(S))
    {
        SortedList list = SortedList<T>();
        for (const_iterator iterator = this->begin() ; !(iterator == this->end()) ; ++iterator)
        {
            list.insert(function(*iterator));
        }
        return list;
    }
}


#endif