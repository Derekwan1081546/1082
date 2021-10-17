// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "Vector-1081546-hw5.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
   template< typename T >
   friend ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger );
public:
   HugeInteger( unsigned int n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

   // addition operator; HugeInteger + HugeInteger
   HugeInteger operator+( HugeInteger &op2 );

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   HugeInteger operator-( HugeInteger &op2 );

   // multiplication operator; HugeInteger * HugeInteger
   HugeInteger operator*( HugeInteger &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( HugeInteger &op2 );

   HugeInteger& operator++(); // prefix increment operator

   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger& operator--(); // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   void convert( vector< T > &v ); // convert a vector of decimal digits into a HugeInteger
   bool isZero() const;           // return true if and only if all digits are zero
private:
   vector< T > integer;

   void divideByTen();            // divides a HugeInteger by 10
   void helpIncrement();          // increments a HugeInteger by 1
   void helpDecrement();          // decrements a HugeInteger by 1
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

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
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
        if (integer.begin()[i] > right.integer.begin()[i])
            return false;
        else if (integer.begin()[i] < right.integer.begin()[i])
            return true;
    return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+( HugeInteger< T > &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   typename vector< T >::iterator it1 = integer.begin();
   typename vector< T >::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   typename vector< T >::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-( HugeInteger< T > &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
      return zero;

   HugeInteger difference( *this );

   typename vector< T >::iterator it1 = integer.begin();
   typename vector< T >::iterator it2 = op2.integer.begin();
   typename vector< T >::iterator it3 = difference.integer.begin();
   for (it3 = difference.integer.begin(); it3 != difference.integer.end() - 1; ++it3)
   {
       *it3 += 100;
   }
   for (it3 = difference.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
       *it3 -= *it2;

   for (it3 = difference.integer.begin(); it3 != difference.integer.end() - 1; ++it3)
       while (*it3 < 100)
       {
           (*it3) += 10;
           (*(it3 + 1))--;
       }
   for (it3 = difference.integer.begin(); it3 != difference.integer.end() - 1; ++it3)
   {
       *it3 -= 100;
   }

   while (*it3 == 0)
   {
       difference.integer.pop_back();
       it3 = difference.integer.end() - 1;
   }

   return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( isZero() || op2.isZero() )
      return zero;

	HugeInteger< T > product( integer.size() + op2.integer.size() );
    typename vector< T >::iterator it1 = integer.begin();
    typename vector< T >::iterator it2 = op2.integer.begin();
    typename vector< T >::iterator it3 = product.integer.begin();
    for (int i = 0; it1 != integer.end(); ++it1, ++i)
        for (it3 = product.integer.begin() + i, it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
            *it3 += (*it1) * (*it2);

    for (it3 = product.integer.begin(); it3 != product.integer.end() - 1; ++it3)
        while (*it3 > 9)
        {
            (*it3) -= 10;
            (*(it3 + 1))++;
        }
    while (*it3 == 0)
    {
        product.integer.pop_back();
        it3 = product.integer.end() - 1;
    }

   return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( *this < op2 )
      return zero;

   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int quotientSize = (op1Size - op2Size);

   HugeInteger quotient(integer.size() - op2.integer.size());
 /*  vector::iterator it1 = integer.begin();*/
   typename vector< T >::iterator it3 = quotient.integer.begin();
   typename vector< T >::iterator it2 = op2.integer.end() - 1;
   if (isZero())
       return zero;
   if (!(*this < op2))
   {
       HugeInteger buf(op1Size);
       typename vector< T >::iterator it4 = buf.integer.end() - 1;
       for (int i = 0; i < op2.integer.size(); it4--, it2--, i++)
       {
           *it4 = *it2;
       }

       if (*this < buf) {
           buf.divideByTen();
       }
       else
       {
           quotient.integer.resize(quotientSize + 1);
           it3 = quotient.integer.end() - 1;
           *it3 = 0;
       }

       //cout << quotient.integer.size()<<endl;
       HugeInteger buf2(*this);
       it3 = quotient.integer.begin();
       for (int k = quotient.integer.size() - 1; k >= 0; k--)
       {
           while (!(buf2<buf))
           {
               buf2.operator=(buf2.operator-(buf));
               it3[k]++;
           }
           buf.divideByTen();//let buffer to right
       }
   }
   it3 = quotient.integer.end() - 1;
   while (*it3 == 0)
   {
       quotient.integer.pop_back();//§R°£¹s
       it3 = quotient.integer.end() - 1;
   }

   return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger product = quotient * op2;
   HugeInteger remainder = ( *this ) - product;
   return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpIncrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
   helpDecrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpDecrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// convert a vector of decimal digits into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( vector< T > &v )
{
   integer.resize( v.size() );
   typename vector< T >::iterator it1 = integer.end() - 1;
   typename vector< T >::iterator it2 = v.begin();
   for( ; it2 != v.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
   typename vector< T >::const_iterator it = integer.begin();
   for( ; it != integer.end(); ++it )
      if( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   typename vector< T >::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename vector< T >::iterator it = integer.begin();
   ( *it )++;
   typename vector< T >::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.resize( integer.size() + 1 );
      it = integer.end();
      --it;
      *it = 1;
   }
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   typename vector< T >::iterator it = integer.begin();
   for( ; *it == 0; ++it )
      *it = 9;

   ( *it )--;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename vector< T >::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

#endif