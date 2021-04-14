#ifndef STACK_H
#define STACK_H

template <typename Object>
class Stack
{
    class StackNode
    {
        Object* item;
        StackNode* tail = nullptr;
    public:
        StackNode(Object* item);

        Object* getItem();
        StackNode* getTail();

        void setItem(Object* item);
        void setTail(Object* tail);
        void setTail(StackNode* tail);
    };
    int stackSize = 0;
    StackNode* headNode = nullptr;

    StackNode* getNode(int pos);
public:

    Stack();

    void add(Object* obj);
    Object* remove();
    int size();

    void operator+=(Object* obj);

};


#endif // STACK_H
