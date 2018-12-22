/*
Author  :   Ravi Shankar
Email   :   shankar.ravi.awesome@gmail.com
*/

#ifndef _MyStack_H
#define _MyStack_H
#include "MyVector.h"
template<class T>
class MyStack
{
    public:
    // data Member
        MyVector<T> m_data;
    // Member function

        MyStack();
        ~MyStack();
        void clear() ;
        bool empty() const;
        int size() const;
        T& top() ;
        void push(T value);
        void pop();
};
#endif


template<class T>
MyStack<T>:: MyStack()
{

}

template<class T>
MyStack<T>:: ~ MyStack()
{

}

template<class T>
void MyStack<T>:: clear()
{
    m_data.clear();
}

template<class T>
int MyStack<T>:: size() const
{
    return m_data.size();
}

template<class T>
bool MyStack<T>:: empty() const
{
    return (m_data.size()==0);
}

template<class T>
T& MyStack<T>:: top()
{
    if(!empty())
        return m_data[m_data.size()-1];
}

template<class T>
void MyStack<T>:: pop()
{
    if(! empty())
    {
        m_data.remove(m_data.size()-1);
    }
}
template<class T>
void MyStack<T>:: push(T value)
{
    m_data.push_back(value);
}
