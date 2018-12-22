/*
Author  :   Ravi Shankar
Email   :   shankar.ravi.awesome@gmail.com
*/

#ifndef _MyQueue_H
#define _MyQueue_H
#include "MyVector.h"

template<class T>
class MyQueue
{
    private:
        MyVector<T>m_data;

    public:
        MyQueue();
        ~MyQueue();
        int size() const;
        void clear();
        bool empty() const;
        T& front() ;
        void pop();
        void push(T value);
        T& back() ;
};

#endif


template<class T>
MyQueue<T>::MyQueue()
{

}

template<class T>
MyQueue<T>:: ~MyQueue()
{

}

template<class T>
void MyQueue<T>:: clear()
{
    m_data.clear();
}


template<class T>
bool MyQueue<T>::empty() const
{
    return (m_data.size() == 0);
}

template<class T>
int MyQueue<T>:: size() const
{
    return m_data.size();
}

template<class T>
T& MyQueue<T>:: front()
{
    if(!m_data.empty())
        return m_data[0];
}

template<class T>
T& MyQueue<T>:: back()
{
    if(!m_data.empty())
        return m_data[ m_data. size() - 1];
}

template<class T>
void MyQueue<T>:: push(T  value)
{
    m_data.add(value);
}

template<class T>
void MyQueue<T>:: pop()
{
    if(!m_data.empty())
        m_data.remove(0);
}
