// list standard header

#ifndef LIST
#define LIST

//#include "XUtility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE ListConstIterator
template< typename MyList >
class ListConstIterator
{
public:
   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::const_pointer;
   using reference = const value_type &;

   ListConstIterator()
      : ptr()
   {
   }

   ListConstIterator( nodePtr pNode )
      : ptr( pNode )
   {
   }

   reference operator*() const
   {
      return ptr->myVal;
   }

   pointer operator->() const
   {
      return &( operator*() );
   }

   ListConstIterator& operator++()
   {
      ptr = ptr->next;
      return *this;
   }

   ListConstIterator operator++( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->next;
      return temp;
   }

   ListConstIterator& operator--()
   {
      ptr = ptr->prev;
      return *this;
   }

   ListConstIterator operator--( int )
   {
      ListConstIterator temp = *this;
      ptr = ptr->prev;
      return temp;
   }

   bool operator==( const ListConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const ListConstIterator &right ) const
   {
      return !( *this == right );
   }

   nodePtr ptr; // pointer to node
};


// CLASS TEMPLATE ListIterator
template< typename MyList >
class ListIterator : public ListConstIterator< MyList >
{
public:
   using MyBase = ListConstIterator< MyList >;

   using nodePtr = typename MyList::nodePtr;
   using value_type = typename MyList::value_type;
   using difference_type = typename MyList::difference_type;
   using pointer = typename MyList::pointer;
   using reference = value_type &;

   using MyBase::MyBase;

   reference operator*() const
   {

      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const
   {
      return const_cast< pointer >( MyBase::operator->() );
//      return &( operator*() );
   }

   ListIterator& operator++()
   {
      MyBase::operator++();
      return *this;
   }

   ListIterator operator++( int )
   {
      ListIterator temp = *this;
      MyBase::operator++();
      return temp;
   }

   ListIterator& operator--()
   {
      MyBase::operator--();
      return *this;
   }

   ListIterator operator--( int )
   {
      ListIterator temp = *this;
      MyBase::operator--();
      return temp;
   }
};

template< typename ValueType >
struct ListNode // list node
{
   using nodePtr = ListNode *;

   nodePtr next; // successor node, or first element if head
   nodePtr prev; // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = ListIterator< ScaryVal >;
   using const_iterator = ListConstIterator< ScaryVal >;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   list( const list &right )
      : myData()
   {
	   myData.myHead = new node;
	   myData.myHead->myVal = Ty();
	   myData.myHead->prev = myData.myHead->next = myData.myHead;

	   *this = right;
   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // The container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the list size by the amount of elements inserted.
   void insert( const_iterator where, const value_type &val ) // insert val at where
   {
	   nodePtr temp = new node;
	   nodePtr it1 = myData.myHead;//modify
	   nodePtr it2 = it1->next;
	   ListConstIterator<ListVal<Ty>> it = begin();
	   for (; it != where; ++it)
	   {
		   it1 = it1->next;
		   it2 = it2->next;
	   }
	   temp->prev = it1;
	   temp->next = it2;
	   it2->prev = temp;
	   it1->next = temp;

	   temp->myVal = val;
	   ++myData.mySize;


	   //unsigned int inserted = 0;
	   //if (myData.mySize == 0)
	   //{
		  // nodePtr temp = new node;
		  // temp->myVal = val;
		  // temp->prev = temp->next = temp;
	   //}
	   //else
	   //{
		  // if ( begin() <= where && where <= end())
		  // {
			 //  // all elements before where move forward
			 //  if (where <= begin() + myData.mySize / 2)
			 //  {
				//   nodePtr temp = new node;
				//   nodePtr it1 = myData.myHead->next;
				//   nodePtr it2 = myData.myHead->next->next;
				//   ListConstIterator<ListVal<Ty>> it = begin();
				//   for (; it != where; ++it)
				//   {
				//	   it1 = it1->next;
				//	   it2 = it2->next;
				//		   //it1->myVal = it2->myVal;
				//   }
				//   temp->prev = it1;
				//   temp->next = it1->next;
				//   it1->next->prev = temp;
				//   it1->next = temp;

				//   temp->myVal = val;
			 //  }
			 //  else  // all elements after (and at) where move backward
			 //  {
				//   nodePtr temp = new node;
				//   nodePtr it1 = myData.myHead;
				//   nodePtr it2 = myData.myHead->prev;
				//   ListConstIterator<ListVal<Ty>> it = end();
				//   for (; it != where; --it)
				//   {
				//	   it1 = it1->prev;
				//	   it2 = it2->prev;
				//	   //it1->myVal = it2->myVal;
				//   }
				//   temp->prev = it1->next;
				//   temp->next = it1;
				//   it1->prev->next = temp;
				//   it1->prev = temp;

				//   temp->myVal = val;
			 //  }
		  // }
	   //}

	   //++myData.mySize;
	   
   }

   // Removes from the list container the element at the specified position.
   // This effectively reduces the container size one, which is destroyed.
   void erase( const const_iterator where )
   {

	   nodePtr buf = myData.myHead->next;
	   ListConstIterator<ListVal<Ty>> it = begin();
	   for (; it != where; ++it)
	   {
		   buf = buf->next;
	   }
	   buf->prev->next = buf->next;
	   buf->next->prev = buf->prev;
	   delete[] buf;
	   --myData.mySize;


	   //if (myData.mySize > 0 && begin() <= where && where < end())
	   //{
		  // if (myData.mySize == 1 && begin() == where)
		  // {
			 //  myData.mySize = 0;
		  // }
		  // else
		  // {
			 //  // all elements before where move backward
			 //  if (where < begin() + myData.mySize / 2)
			 //  {
				//   nodePtr buf = myData.myHead->next;
				//   ListConstIterator<ListVal<Ty>> it = begin();
				//   for (; it != where; ++it)
				//   {
				//	   buf = buf->next;
				//   }
				//   buf->prev->next = buf->next;
				//   buf->next->prev = buf->prev;
				//   delete[] buf;
			 //  }
			 //  else // all elements after where move forward
			 //  {
				//   nodePtr buf = myData.myHead;
				//   ListConstIterator<ListVal<Ty>> it = end();
				//   for (--it; it != where; --it)
				//   {
				//	   buf = buf->prev;
				//   }
				//   buf->prev->next = buf->next;
				//   buf->next->prev = buf->prev;
				//   delete[] buf;
			 //  }

			 //  --myData.mySize;
		  // }
	   //}
	   
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
         while( myData.myHead->next != myData.myHead )
         {
            myData.myHead->next = myData.myHead->next->next;
            delete myData.myHead->next->prev;
         }

         myData.myHead->prev = myData.myHead;
         myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

#endif // LIST
