#ifndef _MyArray_H
#define _MyArray_H
/*
Author  :   Ravi Shankar
Email   :   shankar.ravi.awesome@gmail.com
*/
template<class T, int p_size>
class MyArray
{

private:
    T* m_data;
    int m_size;
public:
    MyArray();                      // Constructor to create MyArray of size p_size
    ~ MyArray();                    // Destructor to delete MyArray of size p_size
    int size() const;               // Returns the size of MyArray
    T& operator[](int index);       // operator to get the element at position index
    T& at (int index) const;        // function to get element at position index
    T& back() const;                // function to get element at last
    T& front() const;               // function to get element at front
    T* begin();                     // returns pointer to the first element
    T* end();                       // returns pointer to the last element
    T* data();
    bool empty();                   // returns true if MyArray is empty
    void fill(T value);             // function to fill MyArray with value
    int& max_size();                // function to return the size of MyArray

};
#endif // _MyArray_H


template<class T, int p_size>
MyArray<T, p_size>:: MyArray()
    {
        m_size = p_size;
        m_data = new T [p_size];
    }


template<class T, int p_size>
MyArray<T, p_size>:: ~ MyArray()
    {
        if(m_data)
            delete [] m_data;
        m_data = NULL;
    }


template<class T, int p_size>
 int MyArray<T, p_size>:: size() const
     {
        return m_size;
     }


 template<class T, int p_size>
 T& MyArray<T, p_size>:: operator[] (int index)
     {
        return m_data[index];
     }


 template<class T, int p_size>
 T& MyArray<T, p_size>:: at (int index) const
     {
        return m_data[index];
     }


template<class T, int p_size>
T& MyArray<T, p_size>:: back() const
    {
        return m_data[m_size-1];
    }


template<class T, int p_size>
T& MyArray<T, p_size>:: front() const
    {
        return m_data[0];
    }


template<class T, int  p_size >
    T* MyArray<T, p_size>:: begin()
    {
        return &m_data[0];
    }


template<class T, int  p_size>
    T* MyArray<T, p_size>:: end()
    {
        return &m_data[m_size-1];
    }


template<class T,int p_size>
    T* MyArray<T, p_size>:: data()
    {
        return &m_data[0];
    }


template<class T, int p_size>
    bool MyArray<T, p_size>:: empty()
    {
        return (m_size==0);
    }


template<class T, int p_size>
    void MyArray<T, p_size>:: fill(T value)
    {
        for(int i=0;i<m_size;i++)
            m_data[i]=value;
    }


template<class T, int p_size>
    int& MyArray<T, p_size>:: max_size()
    {
        return m_size;
    }
