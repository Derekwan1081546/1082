#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1, '0' )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1, '0' )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::operator=( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::operator==( const HugeInteger &right ) const
{
//   return operator==( integer, right.integer );
   return ( integer == right.integer );
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::operator<( const HugeInteger &right ) const
{
    if (integer.size() > right.integer.size())
        return false;
    else if (integer.size() < right.integer.size())
        return true;
    for (int i = integer.size() - 1; i >= 0; i--)
        if (integer.begin()[i] > right.integer.begin()[i])
            return false;
        else if (integer. begin()[i] < right.integer.begin()[i])
            return true;
    return false;
} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::operator<=( const HugeInteger &right ) const
{
   return ( *this == right || *this < right );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::operator+( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   string::iterator it1 = integer.begin();
   string::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   string::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 = ( *it3 - '0' ) + ( *it2 - '0' ) + '0';

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > '9' )
      {
         ( *it3 ) = ( *it3 - '0' ) - 10 + '0';
         ( *( it3 + 1 ) ) = ( *( it3 + 1 ) - '0' ) + 1 + '0';
      }

   if( *it3 == '0' )
      sum.integer.pop_back();

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::operator-( HugeInteger &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
      return zero;

   HugeInteger difference( *this );

   string::iterator it1 = integer.begin();
   string::iterator it2 = op2.integer.begin();
   string::iterator it3 = difference.integer.begin();
   for (it3 = difference.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
       (*it3) = ((*it3 - '0') - (*it2 - '0'))+'0';

   for (it3 = difference.integer.begin(); it3 != difference.integer.end() - 1; ++it3)
       while (*it3 < '0')
       {
           (*it3) = (*it3 - '0') + 10 + '0';
           (*(it3 + 1)) = (*(it3 + 1) - '0') - 1 + '0';
       }

   while (*it3 == '0')
   {
       difference.integer.pop_back();
       it3 = difference.integer.end() - 1;
   }

   return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::operator*( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );

   string::iterator it1 = integer.begin();
   string::iterator it2 = op2.integer.begin();
   string::iterator it3 = product.integer.begin();
   
   for (it3 = product.integer.begin(); it3 != product.integer.end() - 1; ++it3)
   {
       *it3 = '\0';
   }
   for (int i = 0; it1 != integer.end(); ++it1, ++i)
       for (it3 = product.integer.begin() + i, it2 = op2.integer.begin() ; it2 != op2.integer.end(); ++it2, ++it3)
       {
           (*it3) = (*it3 ) + ((*it1 - '0') * (*it2 - '0'));
           while (*it3 > 9)
           {
               (*it3) -= 10;
               (*(it3 + 1))++;
           }
       }

   for (it3 = product.integer.begin(); it3 != product.integer.end() - 1; ++it3)
   {
       (*it3) = *it3 + '0';

   }  //while (*it3 > '9')
       //{
           //(*it3) = (*it3 - '0') - 10 + '0';
           //(*(it3 + 1)) = (*(it3 + 1) - '0') + 1 + '0';
       //}
   while (*it3 == '0')
   {
       product.integer.pop_back();
       it3 = product.integer.end() - 1;
   }

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator/( HugeInteger &op2 )
{
   HugeInteger zero;
   if( *this < op2 )
      return zero;
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int quotientSize = (op1Size - op2Size);
   //cout << quotientSize << endl;
   HugeInteger quotient(integer.size() - op2.integer.size());
   //cout << quotient.integer.size() << endl;
 /*  vector::iterator it1 = integer.begin();*/
   string::iterator it3 = quotient.integer.begin();
   string::iterator it2 = op2.integer.end() - 1;
   if (isZero())
       return zero;
   if (!(*this < op2))
   {
       HugeInteger buf(op1Size);
       string::iterator it4 = buf.integer.end() - 1;
       for (int i=0; i < op2.integer.size(); it4--, it2--,i++)
       {
           *it4 = *it2;
       }

       if (*this < buf) {
           buf.divideByTen();
       }
       else {
           quotient.integer.resize(quotientSize + 1);
           it3 = quotient.integer.end() - 1;
           *it3 = '0';
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
   it3 = quotient.integer.end();

   while (*it3 == '0' )
   {
       // cout << "1"  << endl;
       quotient.integer.pop_back();//§R°£¹s
       it3 = quotient.integer.end() - 1;
   }

   return quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::operator%( HugeInteger &op2 )
{
   HugeInteger quotient = ( *this ) / op2;
   HugeInteger product = quotient * op2;
   HugeInteger remainder = ( *this ) - product;
   return remainder;
}

// convert a string of decimal digits into a HugeInteger
void HugeInteger::convert( string &str )
{
   integer.resize( str.size() );
   string::iterator it1 = integer.end() - 1;
   string::iterator it2 = str.begin();
   for( ; it2 != str.end(); --it1, ++it2 )
      *it1 = *it2;
} // end function convert

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( string::iterator it = integer.begin(); it != integer.end(); ++it )
      if( *it != '0' )
         return false;

   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   string::iterator it = integer.begin();
   string::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.pop_back();
}

// overloaded output operator
ostream& operator<<( ostream &output, const HugeInteger &hugeInteger )
{
   string::const_iterator it = hugeInteger.integer.end() - 1;

   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it <= '9' )
         output << *it;

   return output; // enables cout << x << y;
} // end function output
