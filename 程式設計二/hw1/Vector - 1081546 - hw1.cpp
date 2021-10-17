#include "Vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
    myFirst = new value_type[count]();
    myLast = myFirst + count;
    myEnd = myLast;
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    int s = right.myLast - right.myFirst, c = right.myEnd - right.myFirst;
    myFirst = new value_type[s]();
    myLast = myFirst + s;
    myEnd = myLast;
    for (int i = 0; i < s; i++)
        myFirst[i] = right.myFirst[i];
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
   size_type originalSize = size();
   resize( originalSize + 1 );
   myFirst[ originalSize ] = val;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
       int c = right.myEnd - right.myFirst, s = right.myLast - right.myFirst;
       if (capacity() < s)
           resize(s);


       myLast = myFirst + s;
       for (int i = 0; i < s; i++)
           myFirst[i] = right.myFirst[i];
   }

   return *this; // enables x = y = z, for example
}

// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize( const size_type newSize )
{
	int s = 0;
	if (size() > 0)
		s = size();
	while (newSize < s)
	{
		--myLast;
		--s;
	}

	while (newSize > s&& myLast != myEnd)
	{
		myFirst[s] = 0;
		++myLast;
		++s;
	}
	if (newSize > s)
	{
		int n = capacity(), b = capacity();
		if (n < newSize && n < 90)//判斷新的size是否大於capacity和小於90
			n = newSize;//把capacity改為新的size
		if (n < newSize &&n >= 90)//判斷新的size是否大於capacity和大於90
		{
			n += n / 2;
			while (n < newSize)
				n *= 2;
		}

		pointer buf = new value_type[n]();//再創一個動態陣列
		for (int i = 0; i < b; i++)
			buf[i] = myFirst[i];//把原本的資料放到新的陣列裡
		delete[] myFirst;//刪掉原本的陣列
		this->myFirst = buf;
		myLast = myFirst + newSize;//指向有用到size的位置
		myEnd = myFirst + n;//指向最後一項
	}
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
      --myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::pointer vector::begin()
{
   return myFirst;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return ( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return ( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::element( const size_type pos )
{
   return myFirst[ pos ];
}