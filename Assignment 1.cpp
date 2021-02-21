#include <iostream>
using std::cout;
using std::endl;

#include <unordered_set>
#include "unordered_set.h"

bool duplicate( unsigned int *values, unsigned int i )
{
   for( unsigned int j = 0; j < i; j++ )
      if( values[ j ] == values[ i ] )
         return true;
   return false;
}

void testUnorderedSet1( unsigned int numData );
void testUnorderedSet2();
bool equal( unordered_set< unsigned int > &left, std::unordered_set< unsigned int > &right );

int main()
{
   unsigned int numDatas[] = { 8, 64, 512, 1024 };
   for( unsigned int i = 0; i < 4; i++ )
   {
      srand( i );
      testUnorderedSet1( numDatas[ i ] );
   }

   cout << endl;

   for( unsigned int seed = 51; seed <= 60; seed++ )
   {
      srand( seed );
      testUnorderedSet1( rand() );
   }

   cout << endl;

   for( unsigned int seed = 1; seed <= 10; seed++ )
   {
      srand( seed );
      testUnorderedSet2();
   }

   cout << endl;

   system( "pause" );
}

void testUnorderedSet1( unsigned int numData )
{
   unordered_set< unsigned int > data1;
   std::unordered_set< unsigned int > data2;

   unsigned int numErrors = numData + 1;
   if( equal( data1, data2 ) )
      numErrors--;

   unsigned int *values = new unsigned int[ numData ];
   for( unsigned int i = 0; i < numData; i++ )
   {
      do values[ i ] = rand() % ( 5 * numData );
      while( duplicate( values, i ) );
   }

   for( unsigned int i = 0; i < numData; i++ )
   {
      data1.insert( values[ i ] );
      data2.insert( values[ i ] );

      if( equal( data1, data2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testUnorderedSet2()
{
   unordered_set< unsigned int > data1;
   std::unordered_set< unsigned int > data2;

   unsigned int maxValue = 99;
   unsigned int numErrors = 500;
   unsigned int value;
   for( unsigned int i = 0; i < 500; i++ )
   {
      value = 1 + rand() % maxValue;
      switch( rand() % 2 )
      {
      case 0:
         data1.insert( value );
         data2.insert( value );
         break;
      case 1:
         if( data1.size() > 0 )
         {
            data1.erase( value );
            data2.erase( value );
         }
         break;
      default:
         break;
      }

      if( equal( data1, data2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// Determines if two unordered_sets are equal.
bool equal( unordered_set< unsigned int > &left, std::unordered_set< unsigned int > &right )
{
   if( left.size() != right.size() )
      return false;

   if( left.bucket_count() != right.bucket_count() )
      return false;

   size_t *rightListHead = *( reinterpret_cast< size_t ** >( &right ) + 2 );

   typedef typename list< size_t >::iterator ListIt;
   ListIt *leftVecFirst = *( reinterpret_cast< ListIt ** >( &left ) + 4 );
   size_t *rightVecFirst = *( reinterpret_cast< size_t ** >( &right ) + 5 );
   for( size_t bucketNo = 0; bucketNo < right.bucket_count(); bucketNo++ )
   {
      if( left.bucket_size( bucketNo ) != right.bucket_size( bucketNo ) )
         return false;

      ListIt leftBucketFirst = leftVecFirst[ 2 * bucketNo ];
      ListIt leftBucketLast = leftVecFirst[ 2 * bucketNo + 1 ];
      size_t *rightBucketFirst = *( reinterpret_cast< size_t ** >( &rightVecFirst[ 2 * bucketNo ] ) );
      size_t *rightBucketLast = *( reinterpret_cast< size_t ** >( &rightVecFirst[ 2 * bucketNo + 1 ] ) );

      if( rightBucketFirst != rightListHead )
      {
         if( rightBucketFirst == rightBucketLast )
         {
            if( *leftBucketFirst != *( rightBucketFirst + 2 ) )
               return false;
         }
         else
         {
            ListIt leftIt = leftBucketFirst;
            size_t *rightPtr = rightBucketFirst;
            while( rightPtr != rightBucketLast )
            {
               if( *leftIt != *( rightPtr + 2 ) )
                  return false;

               ++leftIt;
               rightPtr = *( reinterpret_cast< size_t ** >( rightPtr ) );
            }

            if( *leftBucketLast != *( rightBucketLast + 2 ) )
               return false;
         }
      }
   }

   ListIt leftIt = *leftVecFirst;
   size_t *rightBucketFirst = *( reinterpret_cast< size_t ** >( rightVecFirst ) );
   size_t *rightPtr = rightBucketFirst;
   while( rightPtr != rightListHead )
   {
      if( *leftIt != *( rightPtr + 2 ) )
         return false;
      ++leftIt;
      rightPtr = *( reinterpret_cast< size_t ** >( rightPtr ) );
   }

   return true;
}