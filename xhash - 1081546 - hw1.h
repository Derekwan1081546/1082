// xhash internal header

#ifndef XHASH
#define XHASH

#include <list>
using std::list;

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
    using value_type = ValueType;
    using pointer = value_type*;

    VectorVal()
        : myFirst(),
        myLast(),
        myEnd()
    {
    }

    pointer myFirst; // pointer to beginning of array
    pointer myLast;  // pointer to current end of sequence
    pointer myEnd;   // pointer to end of array
};

template< typename Iter >
struct HashVec
{
    using value_type = Iter;
    using size_type = size_t;

    HashVec()
        : myData()
    {
    }

    // set the elements stored here to cells copies of val
    void assignGrow(const size_type cells, const value_type val)
    {
        /*value_type* array = new value_type[cells]();
        myData.myFirst = array;
        myData.myLast = array + cells;
        myData.myEnd = array + cells;
        for (int i = 0; i < cells; i++) {
            myData.myFirst[i] = val;
        }*/
        if (myData.myFirst) delete[] myData.myFirst;
        size_type s = myData.myLast - myData.myFirst;
        myData.myFirst = new value_type[cells]();
        myData.myLast = myData.myFirst + cells;
        myData.myEnd = myData.myLast;
        for (int i = 0; i < cells; i++)
        {
            myData.myFirst[i] = val;
        }
    }

    ~HashVec()
    {
        if (myData.myFirst != nullptr)
            delete[] myData.myFirst;
    }

    VectorVal< value_type > myData;
};

// CLASS TEMPLATE Hash
template< typename Traits >
class Hash // hash table -- list with vector of iterators for quick access
{
protected:
    using MyList = list< typename Traits::value_type >;
    using KeyCompare = typename Traits::key_compare;

public:
    using key_type = typename Traits::key_type;
    using value_type = typename MyList::value_type;
    using size_type = typename MyList::size_type;

    using iterator = typename MyList::const_iterator;
    using const_iterator = typename MyList::const_iterator;

    static const size_type MinBuckets = 8; // must be a positive power of 2

protected:
    Hash(const KeyCompare& parg) // construct empty hash table
        : traitsObj(parg),
        myList(),
        myVec(),
        mask(MinBuckets - 1),
        maxidx(MinBuckets)
    {
        myVec.assignGrow(MinBuckets * 2, myList.end());
    }

public:
    // Returns the number of elements in the unordered_set container.
    size_type size() const
    {
        return myList.size();
    }

    // Returns the number of buckets in the unordered_set container.
    size_type bucket_count() const
    {
        return maxidx;
    }

    // Returns the bucket number where the element with value keyVal is located.
    size_type bucket(const key_type& keyVal) const
    {
        return traitsObj(keyVal) & mask;
        //    return traitsObj.operator()( keyVal ) & mask;
        //    return traitsObj( keyVal ) % maxidx;
    }

    // Returns the number of elements in bucket n.
    size_type bucket_size(size_type n) const
    {
        /*int count;
        iterator it1 = myVec.myData.myFirst[n * 2];
        iterator it2 = myVec.myData.myFirst[n * 2 + 1];
        if ((myVec.myData.myFirst[n * 2]) == myList.end())
            return 0;
        for (count = 1; it1 != it2; count++, it1++) {}
        return count;*/

        /*int count = 1;
        iterator it1 = myVec.myData.myFirst[n * 2];
        iterator it2 = myVec.myData.myFirst[n * 2 + 1];
        if (it1 == myList.end())
            return 0;
        for(;it1!=it2;count++,it1++){ }
        return count;*/

        size_type count = 1;
        iterator it1 = myVec.myData.myFirst[n * 2];
        iterator it2 = myVec.myData.myFirst[n * 2 + 1];
        if (it1 == myList.end())
            return 0;
        for(;it1!=it2;count++,it1++){}
        return count;
    }

    // Inserts a new element in the unordered_set.
    // The element is inserted only if it is not equivalent to any other element
    // already in the container ( elements in an unordered_set have unique values ).
    // This effectively increases the container size by one.
    void insert(const value_type& val)
    {
        //if (find(val) != myList.end())//insert過
        //    return;
        //
        //if (size() == bucket_count() /*&& (mask = (maxidx *= maxidx < 512 ? 8 : 2) - 1)*/)/*if (size() == bucket_count())*/
        //{
        //    //if (bucket_count() < 512) //same as (mask = (maxidx *= maxidx < 512 ? 8 : 2) - 1)
        //    //{
        //    //    maxidx *= 8;
        //    //    mask = maxidx - 1;
        //    //}
        //    //else 
        //    //{
        //    //    maxidx *= 2;
        //    //    mask = maxidx - 1;
        //    //}
        //    //delete[]myVec.myData.myFirst;
        //    
        //    MyList buffer = myList;
        //    iterator it1 = buffer.begin();

        //    myList.clear();
        //    myVec.assignGrow(maxidx * 2, myList.end());
        //    for (; it1 != buffer.end(); it1++)
        //        putIn(*it1);
        //}
        //putIn(val);

        //if (find(val) != myList.end())//insert過
        //    return;

        //if (size() == maxidx)
        //{
        //    if (maxidx < 512)
        //    {
        //        maxidx *= 8;
        //        mask = maxidx - 1;
        //    }
        //    else
        //    {
        //        maxidx *= 2;
        //        mask = maxidx - 1;
        //    }

        //    MyList buffer = myList;
        //    iterator it = buffer.begin();
        //    myList.clear();
        //    myVec.assignGrow(maxidx * 2, myList.end());
        //    for (; it != buffer.end(); it++)
        //        putIn(*it);

        //}
        //putIn(val);

        if (find(val) != myList.end())
            return;
        if (size() == maxidx)
        {
            if (maxidx < 512)
            {
                maxidx *= 8;
                mask = maxidx - 1;
            }
            else
            {
                maxidx *= 2;
                mask = maxidx - 1;
            }
            MyList buffer = myList;
            iterator it = buffer.begin();
            myList.clear();
            myVec.assignGrow(maxidx * 2, myList.end());
            for (; it != buffer.end(); it++)
                putIn(*it);
        }
        putIn(val);




    }

    // Removes from the unordered_set a single element.
    // This effectively reduces the container size by one.
    void erase(const key_type& keyVal)
    {
        /*size_type bucketVal = bucket(keyVal) % bucket_count();
        iterator del = find(keyVal);
        if (del == myList.end())
            return;
        iterator& it1 = myVec.myData.myFirst[bucketVal * 2];
        iterator& it2 = myVec.myData.myFirst[bucketVal * 2 + 1];
        if (del == it1) 
        {
            if (it1 == it2) 
            {
                it1 = myList.end();
                it2 = myList.end();
            }
            else
                it1++;
        }
        else if (del == it2)
            it2--;
        myList.erase(del);*/

        
        /*auto iter = find(keyVal);
        if (iter == myList.end()) return;

        auto head = &myVec.myData.myFirst[bucket(keyVal) * 2];
        if (*head == *(head + 1)) *head = *(head + 1) = myList.end();
        else if (*head == iter || *(head + 1) == iter) *head == iter ? ++ * head : -- * ++head;

        myList.erase(iter);*/

        //size_type val = bucket(keyVal) % bucket_count();
        //auto iter = find(keyVal);
        //if (iter == myList.end()) return;//沒insert過
        //iterator& it1 = myVec.myData.myFirst[val * 2];
        //iterator& it2 = myVec.myData.myFirst[val * 2 + 1];
        //if (iter == it1)
        //{
        //    if (it1 == it2)
        //    {
        //        it1 = it2 = myList.end();
        //    }
        //    else
        //        it1++;
        //}
        //else if (iter == it2)
        //    it2--;

        //myList.erase(iter);




        size_type val = bucket(keyVal) % bucket_count();
        auto iter = find(keyVal);
        if (iter == myList.end())
            return;
        iterator& it1 = myVec.myData.myFirst[val * 2];
        iterator& it2 = myVec.myData.myFirst[val * 2 + 1];
        if (iter == it1)
        {
            if (it1 == it2)
            {
                it1 = it2 = myList.end();
            }
            else
                it1++;
        }
        else if (iter == it2)
        {
            it2--;
        }
        myList.erase(iter);
    }

    // Searches the unordered_set for an element with keyVal as value and
    // returns an iterator to it if found, otherwise it returns myList.end()
    iterator find(const key_type& keyVal)
    {

        /*size_type val = bucket(keyVal) % bucket_count();
        iterator it1 = myVec.myData.myFirst[val * 2];
        iterator it2 = myVec.myData.myFirst[val * 2 + 1];
        if (it1 == myList.end())
            return myList.end();
        else
        {
            it2++;
            for (; it1 != it2; it1++)
                if (*it1 == keyVal)
                    return it1;
        }
        return myList.end();

        size_type hash = bucket(keyVal) % bucket_count();
        auto iter = myVec.myData.myFirst[hash * 2];
        while (iter != myVec.myData.myFirst[hash * 2 + 1] && *iter != keyVal) ++iter;
        return iter == myList.end() ? myList.end() : *iter == keyVal ? iter : myList.end();*/

        /*int val = bucket(keyVal) % bucket_count();
        iterator it = myVec.myData.myFirst[val * 2];
        while (it != myVec.myData.myFirst[val * 2 + 1] && *it != keyVal)
            ++it;
        return it == myList.end() ? myList.end() : *it == keyVal ? it : myList.end();*/






        int val = bucket(keyVal) % bucket_count();
        iterator it = myVec.myData.myFirst[val * 2];
        while (it != myVec.myData.myFirst[val * 2 + 1] && *it != keyVal) { it++; }
        return it == myList.end() ? myList.end() : *it == keyVal ? it : myList.end();
    }

private:
    // put a new element in the unordered_set when myVec is large enough
    void putIn(const value_type& val)
    {
        /*size_type bucketVal = bucket(val);

        if (bucket_size(bucketVal) == 0)
        {
            myList.push_back(val);
            iterator i = myList.end();
            i--;
            myVec.myData.myFirst[bucketVal * 2] = i;
            myVec.myData.myFirst[bucketVal * 2 + 1] = i;
        }
        else
        {
            iterator it = myList.insert(myVec.myData.myFirst[bucketVal * 2], val);

            myVec.myData.myFirst[bucketVal * 2] = it;
        }*/

        //auto head = &myVec.myData.myFirst[bucket(val) * 2];
        //myList.insert(*head, val);
        ////if ((*head)-- == myList.end())--* ++head;
        //*head == myList.end() ? -- * head, --* ++head : --* head; // also be fine

        //auto head = &myVec.myData.myFirst[bucket(val) * 2];
        //myList.insert(*head, val);
        ////if ((*head)-- == myList.end())--* ++head;
        //if (*head == myList.end())
        //{
        //    --* head;
        //    --* ++head;
        //}
        //else
        //    --* head;
            



        auto head = &myVec.myData.myFirst[bucket(val) * 2];
        myList.insert(*head, val);
        if (*head == myList.end())
        {
            --* head;
            --* ++head;
        }
        else
        {
            --* head;
        }
            

    }

protected:
    Traits traitsObj;          // traits to customize behavior
    MyList myList;             // list of elements, must initialize before myVec
    HashVec< iterator > myVec; // "vector" of list iterators for buckets:
                               // each bucket is 2 iterators denoting
                               // the closed range of elements in the bucket,
                               // or both iterators set to end() if the bucket is empty.
    size_type mask;            // the key mask, equals maxidx - 1
    size_type maxidx;          // current maximum key value, must be a power of 2
};

#endif // XHASH
