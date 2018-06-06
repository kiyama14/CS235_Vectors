/***********************************************************************
 * Header:
 *    vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef vector_H
#define vector_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{
    
    /************************************************
     * vector
     * A class that holds stuff
     ***********************************************/
    template <class T>
    class vector
    {
    public:
        // constructors and destructors
        
        //vector
        vector(): numElements(0), numCapacity(0), buffer(NULL) {}
        
        //vector(numElements: int)
        vector(int numElements)           throw (const char *); //???
        
        //vector(numElements: int, t T)
        vector(int numElements, T t);
        
        //vector(rhs: vector): vector
        vector(const vector & rhs)        throw (const char *);
        
        //~vector()
        ~vector()                         { delete [] buffer;   }
        
        //assign(rhs: vector): vector
        vector assign(vector rhs);
        
        //size(): integer
        int  size()     const { return numElements;                 }
        
        //capacity(): integer
        int capacity()  const { return numCapacity;                 }
        
        //empty(): Boolean
        bool empty()    const {
//            if (numElements == 0) {
//                return true;
//            } else {
//                return false;
//            }
            return !numElements;
        }
        
        //clear()
        void clear()                    { numElements = 0; }
        
        //push_back(t: T)
        void push_back(const T t)       throw (const char *) {
            
            if (numElements == numCapacity) {
                
                int adjustedCapacity = numCapacity == 0 ? 1 : numCapacity * 2;
                
                try
                {
                    T* adjustedBuffer = new T[adjustedCapacity];
                    
                    if (buffer == NULL) {
                        buffer = adjustedBuffer;

                    } else {
                        
                        for (int j = 0; j < numElements; j++) {
                            adjustedBuffer[j] = buffer[j];
                        }
            
                        delete [] buffer;
                        buffer = adjustedBuffer;
                        
                    }
                    
                    numCapacity = adjustedCapacity;
                }
                catch (std::bad_alloc)
                {
                    throw "ERROR: Unable to allocate buffer";
                }
            }

            buffer[numElements] = t;
            numElements++;
        }
        
        // iterator
        class iterator;
    
        //begin(): iterator
        iterator begin()      { return iterator (buffer); }
        
        //end(): iterator
        iterator end()        { return iterator (buffer + numElements);}
        
        //resize(numCapacity: integer) (private)
        
        
        
        vector & operator = (const vector & rhs) throw (const char *);
        
        
        // vector-specific interfaces
        // what would happen if I passed -1 or something greater than num?
        T & operator [] (int index)       throw (const char *)
        {
            return buffer[index];
        }
        const T & operator [] (int index) const throw (const char *)
        {
            return buffer[index];
        }
        
        
        // a debug utility to display the vector
        // this gets compiled to nothing if NDEBUG is defined
        void display() const;
        
    private:
        T * buffer;              // dynamically allocated vector of T
        int numElements;
        int numCapacity;
    };
    /**************************************************
     * vector ITERATOR
     * An iterator through vector
     *************************************************/
    template <class T>
    class vector <T> :: iterator
    {
    public:
        // constructors, destructors, and assignment operator
        iterator()      : p(NULL)      {              }
        iterator(T * p) : p(p)         {              }
        iterator(const iterator & rhs) { *this = rhs; }
        iterator & operator = (const iterator & rhs)
        {
            this->p = rhs.p;
            return *this;
        }
        
        // equals, not equals operator
        bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
        bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
        
        // dereference operator
        T & operator * ()       { return *p; }
        const T & operator * () const { return *p; }
        
        // prefix increment
        iterator & operator ++ ()
        {
            p++;
            return *this;
        }
        
        // postfix increment
        iterator operator ++ (int postfix)
        {
            iterator tmp(*this);
            p++;
            return tmp;
        }
        
    private:
        T * p;
    };
    
    /*******************************************
     * vector :: Assignment
     *******************************************/
    template <class T>
    vector <T> & vector <T> :: operator = (const vector <T> & rhs)
    throw (const char *)
    {
        
        assert(rhs.numElements >= 0);
        
        // do nothing if there is nothing to do
        if (rhs.numElements == 0)
        {
            numCapacity = 0;
            buffer = NULL;
        }
        
        // attempt to allocate
        try
        {
            buffer = new T[rhs.numCapacity];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }
        
        // copy over the capacity
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        
        
        for (int i = 0; i < numElements; i++)
            buffer[i] = rhs.buffer[i];
            
            return *this;
    }
    
    /*******************************************
     * vector :: COPY CONSTRUCTOR
     *******************************************/
    template <class T>
    vector <T> :: vector(const vector <T> & rhs) throw (const char *)
    {
        assert(rhs.numElements >= 0);
        
        // do nothing if there is nothing to do
        if (rhs.numElements == 0)
        {
            numCapacity = 0;
            buffer = NULL;
            return;
        }
        
        // attempt to allocate
        try
        {
            buffer = new T[rhs.numCapacity];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }
        
        // copy over the capacity
        numCapacity = rhs.numCapacity;
        numElements = rhs.numElements;
        
        // copy the items over one at a time using the assignment operator
        for (int i = 0; i < numElements; i++)
            buffer[i] = rhs.buffer[i];
            }
    
    /**********************************************
     * vector : NON-DEFAULT CONSTRUCTOR
     * Preallocate the vector to "capacity"
     **********************************************/
    template <class T>
    vector <T> :: vector(int numElements) throw (const char *)
    {
        assert(numElements >= 0);
        
        if (numElements == 0)
        {
            this->numElements = 0;
            this->buffer = NULL;
            return;
        }
        
        numCapacity = 1;
        
        do {
            numCapacity *= 2;
        }
        while(numCapacity < numElements);
        
        
        // attempt to allocate
        try
        {
            buffer = new T[numElements];
        }
        catch (std::bad_alloc)
        {
            throw "ERROR: Unable to allocate buffer";
        }
        
        
        // copy over the stuff
        this->numElements = numElements;
    }


    
}; // namespace custom

#endif // vector_H




