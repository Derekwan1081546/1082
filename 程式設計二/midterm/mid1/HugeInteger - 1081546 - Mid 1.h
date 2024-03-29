// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector-1081546-Mid - 1.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger );
public:
   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   // Constructs a HugeInteger with right.size() elements.
   // Each element is initialized as the correcponding element in right.
   HugeInteger( const T &right );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

   HugeInteger& operator++(); // prefix increment operator

   HugeInteger square(); // the square of HugeInteger
   HugeInteger squareRoot(); // the square root of HugeInteger

   bool isZero() const;           // return true if and only if all digits are zero
private:
   T integer;

   void helpIncrement();          // increments a HugeInteger by 1
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( unsigned int n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// Constructs a HugeInteger with right.size() elements.
// Each element is initialized as the correcponding element in right.
template< typename T >
HugeInteger< T >::HugeInteger( const T &right )
   : integer( right )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( const HugeInteger< T > &right ) const
{
	if (integer.size() > right.integer.size())
		return false;
	else if (integer.size() < right.integer.size())
		return true;
	for (int i = integer.size() - 1; i >= 0; i--)
	{
		if (integer[i] > right.integer[i])
			return false;
		else if (integer[i] < right.integer[i])
			return true;
	}
	return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square()
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   unsigned int squareSize = 2 * integer.size();
   HugeInteger< T > square( squareSize );
   typename T::const_iterator it1 = integer.begin();
   typename T::const_iterator it2 = integer.begin();
   typename T::iterator it3 = square.integer.begin();
   for (int i = 0; it1 != integer.end(); ++it1, ++i)
   {
       for (it3 = square.integer.begin() + i, it2 = integer.begin(); it2 != integer.end(); ++it2, ++it3)
       {
           *it3 += (*it1) * (*it2);
       }
   }
   for (it3 = square.integer.begin(); it3 != square.integer.end()-1; ++it3)//modify
   {
       while (*it3 > 9)
       {
           (*it3) = (*it3) - 10;
           (*(it3 + 1))++;
       }
   }
   //it3 = it3 = square.integer.end() - 1;delete
   if (*it3 == 0)
   {
       square.integer.erase(it3);
   }
   return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot()
{
   HugeInteger zero;
   if( isZero() )
      return zero;

   unsigned int sqrtSize = ( integer.size() + 1 ) / 2;
   HugeInteger< T > sqrt( sqrtSize );
   typename T::const_iterator it1 = integer.begin();
   typename T::iterator it2 = sqrt.integer.end()-1;
   /*for (it2 = sqrt.integer.begin(); it2 != sqrt.integer.end(); ++it2)
       *it2 = 0;delete*/

   for (; it2 >= sqrt.integer.begin(); it2--)
   {
       while (!(*this < sqrt.square()))//modify
       {
           (*it2)++;
       }
       (*it2)--;
   }

   return sqrt;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   typename T::const_iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename T::iterator it = integer.begin();
   ( *it )++;
   typename T::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.insert( integer.end(), 1 );
   }
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

#endif