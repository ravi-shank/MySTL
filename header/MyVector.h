/*
Author  :   Ravi Shankar
Email   :   shankar.ravi.awesome@gmail.com
*/

#ifndef _MyVector_H
#define _MyVector_H
using namespace std;

template<class T>
class MyVector
{
private:
    T *m_data;
    int capacity;
    int count;
    void expand_array();
    void deepcopy(const MyVector<T>&src);
public:
    MyVector();                                   // constructor to initialize the empty vector
    MyVector(int size , T value);                 // constructor to initialize the vector of size with each element as value
    ~ MyVector();                                 // destructor  to destuct the vector object
    void clear();                                 // to clear the vector object
    int size() const;                             // to get the size of the vector object
    void insert(int index, T value);              // insert element value to index of vector
    void add(T value);                            // to add value to the end of the vector
    void remove(int index);                       // remove element present at index "index"
    void push_back(T data);                       // to push a new element at the end of vector
    T& at(int index);                             // return reference to the element pesent at index "index" (0- based indexing)
    int get_capacity() const;                     // to get the capacity of the vecotor
    bool empty() const;                           // to check if vector is empty
    const T& operator[] (int) const;              // overloaded operator [] for constant vector
    T& operator[] (int);                          // overloaded operator [] for mutable vector
    MyVector<T>& operator+=(MyVector<T>&v1) ;     // overloaded operator +=
    MyVector<T>& operator=(MyVector<T>&v1) ;      // overloaded operator =
};
#endif // _MyVector_H


// Public member functions

// Constructor to initialize the empty vector
// Parameter:       None
// Return type:     None
template<class T>
MyVector<T>:: MyVector()
{
    m_data = NULL;
    capacity = 0;
    count = 0;
}

// Paramaterized constructor ot initialize the vector of size "size" with value "value"
// Parameter:
//          size:   the size of the vector
//          value:  the value with with each element of the vector is to be initialized
// Return type:     None
template<class T>
MyVector<T>:: MyVector(int size, T value)
{
    m_data = new T [size];
    capacity = size;
    count = size;
    for(int i=0;i<size;i++)
        m_data[i] = value;
}

// Destructor to destruct the vector object and resetting its capacity & size to zero
// Paraeter: None
// Return type: None
template<class T>
MyVector<T>:: ~MyVector()
{
    capacity = 0;
    count = 0;
    if(m_data)
        delete [] m_data;
    m_data = NULL;
}

// Method to clear the vector by destructing all its elements
// Parameter:       None
// Return type:     void
template<class T>
void MyVector<T>:: clear()
{
    capacity = 0;
    count = 0;
    if(m_data)
        delete [] m_data;
    m_data = NULL;
}


// Method to get the size of the vector
// Parameter:   None
// Return type: int
//
template<class T>
int MyVector<T>:: size() const
{
    return count;
}

// Method to get the current capacity of the vector
// parameter:   None
// Return type: int
template<class T>
int MyVector<T>::get_capacity () const
{
    return capacity;
}

// Method to insert a new elment in vector at the end of it
// Working Description: When the size of vector increases than its current capacity, it allocates new memory of size twice of its earlier capacity
// and copy all the existing element to its new memory location and deletes the old memory.
//Parameter:
//         value:  the new element to be inserted
// Return type:     void
template<class T>
void MyVector<T>:: push_back(T value)
{
    if(count == capacity)
        expand_array();
    insert(count, value);
}

// Mehtod to insert a element at position "index"
// Working description: It first checks if the size of the vector has increased its capcity . If yes then it expands the vector to twice of its
// previous capacity. Then it make space for the new elment at position index by shifting all the elements by one posiiton to its right.
// Parameter:
//        index: position at which element to be inserted
// Return type: void
template<class T>
void MyVector<T>:: insert( int index, T value )
{
    if(count == capacity)
        expand_array();
    for( int i=count; i>index; i-- )
        m_data[i]= m_data[i-1];
    m_data[index] = value;
    count ++;
}

// Mehtod to delete a element from position "index".
// It shifts all elements present to right of "index" position index,  by one position to its left, thereby decreasing size of vector by one.
// Parameter:
//        index: position from which element to be deleted.
// Return type: void
template<class T>
void MyVector<T>:: remove( int index )
{

    for( int i=index; i<count-1; i++)
        m_data[i]= m_data[i+1];
    count --;
}

// Method to add one element to the vector at the end of it.
// Parameter:
//          value: item to be addes to vector
// Return type:    void
template<class T>
void MyVector<T>:: add( T value )
{
    insert(count, value);
}

// Mehtod to return the element present at posiiton "index"
// Working description: It returns the reference to the element present at position "index"
// Parameter:
//          index: position for which reference to element is to be returned
// Return type: reference to data present at positon index
template<class T>
T& MyVector<T>:: at( int index )
{
    return m_data[index];
}

// Method to return True if vector is empty, else returns False
// Working descriptin:  It checks if the size of vector. If its zero then returns False, else returns True
// Parameter:   None
// Return type: Boolean
template<class T>
bool MyVector<T>::empty() const
{
    return (count==0);
}

// Operator overloading for operator[]
// Working description: returns a reference to the element present at position index for the constant immutable vector
// Parameters:
//       index:  position for which reference to be returned
// Return type:  reference to data present at positon index
template<class T>
const T& MyVector<T>::operator [] (int index ) const
{
    return m_data[index];
}

// Operator overloading for operator[]
// Working description: returns a reference to the element present at position index for the mutable vector
// Parameters:
//       index:  position for which reference to be returned
// Return type:  reference to data present at positon index
template<class T>
T& MyVector<T>::operator [] (int index )
{
    return m_data[index];
}

// Operator overloading for operator +=
// Working description: Add all the elements of one vector to the other vector
// Parameters:
//       MyVector: vector which is to be added to other vector
// Return type:  Pointer to the vector to which another vector is added
template<class T>
MyVector<T>& MyVector<T>::operator+=(MyVector<T>&v)
{
    for(int i=0;i<v.size();i++)
        this->insert(this->count, v[i]);
    return *this;
}

// Operator overloading for operator  ==
// Working description: content of one vector is copied to other vector
// Parameters:
//       MyVector: vector which is to be copied to other vector
// Return type:  Pointer to the vector to which another vector is copied
template<class T>
MyVector<T>&  MyVector<T>::operator=(MyVector<T>&src)
{
    if(this!= & src)            // check self assignment
    {
        if(m_data)
            delete []m_data;    // ensures that before assiging new vector, space already captured is freed up
        deepcopy(src);
    }
    return *this;

}

// A private member funciton to support deep copy
// Working description: It copies all the elements form src to the new memory
// Parameter:
//      MyVector: vector from which deep copy is to be performed
// Return type: void
template<class T>
void MyVector<T>::deepcopy(const MyVector<T>&src)
{
    count = src.count;
    capacity = src.capacity;
    if(capacity==0)
        m_data = NULL;
    else
        m_data = new T [capacity];
    for(int i=0;i<src.size();i++)
        m_data[i] = src.m_data[i];
}

// Private Member Function to expand the vector
// Working description: It doubles the capacity of a vector by allocating new memory of size equal to twice of that of previous capacity value
// Parameter:   None
// Return type: None
template<class T>
void MyVector<T>:: expand_array()
{
    if(capacity == 0)
        capacity = 1;
    else
        capacity = 2* capacity;
    T * array = new T [capacity];
    for( int i=0; i<count ;++i )
        array[i] = m_data[i];
    if(m_data)
        delete [] m_data;
    m_data = array;
}
