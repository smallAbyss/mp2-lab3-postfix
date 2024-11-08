#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
public:
    //TStack() : size(-1), top(-1), pMem(nullptr) {}

    TStack(int _size)
    {
        size = _size;
        top = -1;
        if ((size < 1) || (size > MaxStackSize))
            throw size;
        pMem = new T[size];
    }

    ~TStack()
    {
        delete[] pMem;
    }

    int Size()
    {
        return top - 1;
    }

    bool IsEmpty() const noexcept
    {
        return top == -1;
    }

    bool Full() const noexcept
    {
        return top == size - 1;
    }

    T Pop()
    {
        if (IsEmpty()) throw "Stack is empty";
        return pMem[top--];
    }

    void Push(const T& val) {
        if (Full()) throw "Stack is full";
        pMem[++top] = val;
    }

    int getsize() const {
        return top + 1;
    }
};

#endif
