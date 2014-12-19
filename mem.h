/* 
 * File:   memory.h
 * Author: root
 *
 * Created on 2014年12月19日, 上午9:53
 */
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <iostream>
#include <string>
#ifndef MEMORY_H
#define	MEMORY_H
class Mnew
{
private:
    void *_ptr;
public:
    Mnew(int size)
    {
        std::cout<<"Mnew"<<std::endl;
        _ptr=calloc(1,size);
    }
    Mnew(int size,void *src)
    {
        _ptr=calloc(1,size);
        memcpy(_ptr,src,size);
    }
    void *getPtr()
    {
        return _ptr;
    }
    ~Mnew()
    {
        free(_ptr);
        std::cout<<"~Mnew()"<<std::endl;
    }
};

template <class T>
class S_ptr
{
    private:
            T *_ptr;
    public:
            S_ptr(T *p) : _ptr(p)  //构造函数
            {
            }
            T& operator *()        //重载*操作符
            {
                    return *_ptr;
            }
            T* operator ->()       //重载->操作符
            {
                    return _ptr;
            }
            ~S_ptr()        //析构函数
            {
                delete _ptr;
            }
};
#endif	/* MEMORY_H */

