#ifndef _SORTED_LIST_H
#define _SORTED_LIST_H

#include <stdexcept>
#include <assert.h>

// Assuming class T has:
// Copy constructor, Destructor, operator<, 

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
        void insert(const T& element);
        void remove(const_iterator iterator);
        int length() const;
        
        template<class S>
        SortedList filter(bool function(S)) const;

        template<class S>
        SortedList apply(T function(S)) const;

        const_iterator begin() const;
        const_iterator end() const;

    private:
        class Node;
        
        int size;
        Node *first;

        Node* findPreviousPlacement(const T& element) const;
        Node* findPreviousPlacement(const const_iterator iterator) const ;
    };


   

    //=========================================
    //========== Node implementation ==========
    //=========================================

     // Node class declaration
    template<class T>
    class SortedList<T>::Node
    {
    public:
        explicit Node(T element);
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

    //constructor
    template<class T>
    SortedList<T>::Node::Node(T element) : data(T(element)), next(nullptr)
    {
    }

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

    // Return the data stored in the node
    template<class T>
    const T& SortedList<T>::Node::getData() const
    {
        return this->data;
    }

    // Destroys a Node list
    template<class T>
    void SortedList<T>::Node::destroyNodeList()
    {
        // In case the given Node is nullptr
        if (this == nullptr)
        {
            return;
        }

        Node* next_node = next;
        while (next_node != nullptr)
        {
            Node* temp_node = next_node->next;
            delete next_node;
            next_node = temp_node;
        }
        delete this;
    }

    // Copies a Node list
    template<class T>
    typename SortedList<T>::Node* SortedList<T>::Node::copyNodeList() const
    {
        // In case of no node list
        if (this == nullptr)
        {
            return nullptr;
        }
        // Declare variables
        Node *return_node = new Node(data);
        Node *current_list_iterator = next;
        Node *new_list_iterator     = return_node;

        // Scan the whole node list
        while (current_list_iterator != nullptr)
        {
            // Try to copy the current node to a new node
            try
            {
                Node *new_node = new Node(current_list_iterator->data);
                new_list_iterator->next = new_node;
                current_list_iterator = current_list_iterator->next;
                new_list_iterator     = new_list_iterator->next;
            }
            // In case of failure, delete all allocated nodes so far
            catch (std::bad_alloc& error)
            {
                while (return_node != nullptr)
                {
                    Node* temp_node = return_node->next;
                    delete return_node;
                    return_node = temp_node;
                }
                throw; // Rethrow
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
        const_iterator(const SortedList* list, const Node* node);
        const SortedList* list;
        const Node* current_node;
        friend class SortedList;

    };
    
    // Constructor
    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList<T>* list, const Node* node) : 
                                list(list), current_node(node)
    {
    }


    template<class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
    {
        if (current_node == nullptr)
        {
            throw std::out_of_range(
                "Cannot perform action operator++ - const_iterator is out of range");
        }
        this->current_node = current_node->getNext();
        return *this;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
    {
        if (current_node == nullptr)
        {
            throw std::out_of_range(
                "Cannot perform action operator++ - const_iterator is out of range");
        }
        const_iterator result = *this;
        this->current_node = current_node->getNext();
        return result;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(SortedList<T>::const_iterator iterator) const
    {
        //assert(this->list == iterator.list);
        return current_node == iterator.current_node;
    }

    template<class T>
    const T& SortedList<T>::const_iterator::operator*()
    {
        if (this->current_node == nullptr)
        {
            throw std::out_of_range(
                "Cannot perform action operator* - const_iterator is out of range");
        }
        return this->current_node->getData();
    }






    //=========================================
    //======= SortedList implementation =======
    //=========================================

    // Finds placement of node that's located (or should be located) before a node containing element
    // Returns nullptr if the list is currently empty OR the placement is the first node
    // Otherwise returns the node that should be placed before a new node containing element in the list
    template<class T>
    typename SortedList<T>::Node* SortedList<T>::findPreviousPlacement(const T& element) const
    {
        // Case: Empty list / placement is before first node
        if (size == 0 || element < first->getData())
        {
            return nullptr;
        }

        // Case: general - find node that should appear before node that contains element
        Node* current_node = first;
        while (current_node != nullptr && current_node->getNext() != nullptr &&
               current_node->getNext()->getData() < element)
        {
            current_node = current_node->getNext();
        }
        
        return current_node;
    }

    // Finds placement of node that's located (or should be located) before a node pointed by the iterator
    // Returns nullptr if the list is currently empty OR the placement is the first node
    // Otherwise returns the node that is placed before iterator
    template<class T>
    typename SortedList<T>::Node* SortedList<T>::findPreviousPlacement(const const_iterator iterator) const
    {
        // Case: Empty list / iterator is first
        if (size == 0 || iterator == this->end() || iterator.current_node == first)
        {
            return nullptr;
        }

        // Case: general - find node that should appear before node pointed by iterator
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

    // Constructor
    template<class T>
    SortedList<T>::SortedList()
    {
        size   = 0;
        first  = nullptr;
    }

    // Destructor
    template<class T>
    SortedList<T>::~SortedList()
    {
        first->destroyNodeList();
    }

    // Copy constructor
    template<class T>
    SortedList<T>::SortedList(const SortedList& sorted_list)
    {
        first = sorted_list.first->copyNodeList();
        size = sorted_list.size;
    }

    // Adds a new element to the list
    template<class T>
    void SortedList<T>::insert(const T& element)
    {
        Node *new_node = new Node(element);

        // Case: New element should be placed first in list
        if (size == 0 || element < first->getData())
        {
            new_node->setNext(first);
            first = new_node;
            size++;
            return;
        }

        // Case: New element should be placed somewhere in the middle / end
        Node* previous_node = findPreviousPlacement(element);
        new_node->setNext(previous_node->getNext());
        previous_node->setNext(new_node);
        size++;

    }
    
    // Gets a SortedList<T> iterator and removes the relevant node from the list
    template<class T>
    void SortedList<T>::remove(SortedList<T>::const_iterator iterator)
    {
        assert(iterator.list == this);
        
        //Case: the iterator is invalid / the list is empty
        if (iterator == this->end())
        {
            throw std::out_of_range(
                "Cannot perform action remove - const_iterator is out of range");
        }

        // Finds node that appears in the list before the given node
        SortedList::Node* previous_node = findPreviousPlacement(iterator);
        
        // Case: the first node should be removed
        if(previous_node == nullptr)
        {
            first = iterator.current_node->getNext();
            delete iterator.current_node;
            size--;
            return;
        }

        // Case: general - connect previous node to next node and delete the current_node
        // updating the size in the process
        SortedList::Node* current_node = previous_node->getNext();
        previous_node->setNext(current_node->getNext());
        delete current_node;
        size--;
    }

    // Assignment operator
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
        
        // If there were nodes in the list beforehand, delete them
        if (first)
        {
            first->destroyNodeList();
        }

        // Assigns the values and return
        first = coppied_list;
        size  = list.size;
        return *this;
    }

    // Returns the length of the SortedList<T>
    template<class T>
    int SortedList<T>::length() const
    {
        return this->size;
    }

    // Returns const_iterator to the first node in the SortedList<T>
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const
    {
        return SortedList::const_iterator(this, this->first);
    }

    // Returns const_iterator to null_ptr, used to verify if
    // an iterator reached the end of the SortedList<T>
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const
    {
        return SortedList<T>::const_iterator(this, nullptr);

    }

    // Gets a bool function that filters SortedList<T> elements and returns
    // a new SortedList<T> containing only elements that were filtered
    template<class T>
    template<class S>
    SortedList<T> SortedList<T>::filter(bool filter_function(S)) const
    {
        SortedList<T> list = SortedList<T>();
        for (const_iterator iterator = this->begin() ; !(iterator == this->end()) ; ++iterator)
        {
            if (filter_function(*iterator))
            {
                // Adding only elements that passed the filter function
                list.insert(*iterator);
            }
        }
        return list;
    }

    // Applies function on each element in SortedList<T>, creating a new
    // list containing all elements generated by the function
    template<class T>
    template<class S>
    SortedList<T> SortedList<T>::apply(T apply_function(S)) const
    {
        SortedList list = SortedList<T>();
        for (const_iterator iterator = this->begin() ; !(iterator == this->end()) ; ++iterator)
        {
            // Adding elements after applying the cuntion
            list.insert(apply_function(*iterator));
        }
        return list;
    }
}


#endif