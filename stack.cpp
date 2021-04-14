#include "stack.h"

template <typename Object>
Stack<Object>::Stack()
{
}
template <typename Object>
Stack<Object>::StackNode::StackNode(Object* item)
    : item(item)
{
}
template <typename Object>
Object* Stack<Object>::StackNode::getItem()
{
    return item;
}
template <typename Object>
typename Stack<Object>::StackNode* Stack<Object>::StackNode::getTail()
{
    return tail;
}
template <typename Object>
void Stack<Object>::StackNode::setItem(Object* item)
{
    this->item = item;
}
template <typename Object>
void Stack<Object>::StackNode::setTail(Object* tail)
{
    this->tail = new StackNode(tail);
}
template <typename Object>
void Stack<Object>::StackNode::setTail(StackNode* tail)
{
    this->tail = tail;
}
template <typename Object>
void Stack<Object>::add(Object* obj)
{
    if(headNode == nullptr) {
        headNode = new StackNode(obj);
    }
    else {
        StackNode* currentNode = headNode;
        while(currentNode->getTail() != nullptr)
            currentNode = currentNode->getTail();
        currentNode->setTail(obj);
    }
    stackSize++;
}
template <typename Object>
void Stack<Object>::operator+=(Object* obj)
{
    add(obj);
}
template <typename Object>
typename Stack<Object>::StackNode* Stack<Object>::getNode(int pos)
{
    int posCounter = 0;
    StackNode* resNode = headNode;
    while(posCounter != pos)
    {
        resNode = resNode->getTail();
        posCounter++;
    }
    return resNode;
}
template <typename Object>
Object* Stack<Object>::remove()
{
    if(stackSize == 0)
        return nullptr;
    int pos = size() - 1;
    StackNode* searchingNode;
    if(stackSize == 1) {
        searchingNode = headNode;
        headNode = nullptr;
    }
    else {
        searchingNode = getNode(pos);
        StackNode* previousNode = getNode(pos - 1);
        if(searchingNode == headNode)
            headNode = searchingNode->getTail();
        else
            previousNode->setTail(searchingNode->getTail());
    }
    stackSize--;
    return searchingNode->getItem();
}
template <typename Object>
int Stack<Object>::size()
{
    if(headNode == nullptr)
        return 0;
    int res = 1;
    StackNode* currentNode = headNode;
    while(currentNode->getTail() != nullptr)
    {
        currentNode = currentNode->getTail();
        res++;
    }
    return res;
}
