#include "List.h"

List::List(List&& thisList) noexcept
    : head_(thisList.head_), tail_(thisList.tail_)
{
    thisList.head_ = nullptr;
    thisList.tail_ = nullptr;
}

void List::operator+=(int data)
{
    if (!head_)
    {
        insertHead(data);
        return;
        //return true;
    }

    Node* current = head_;

    while (current)
    {
        if (data > current->data_)
        {
            if (current == tail_)
            {
                insertTail(data);
                return;
                //return true;
            }
            current = current->next_;
        }

        if (data < current->data_)
        {
            if (!current->next_)
            {
                std::swap(current->data_, data);
                current->next_ = new Node(data, current->next_);
                tail_ = current->next_;
            }
            else {
                std::swap(current->data_, data);
                current->next_ = new Node(data, current->next_);
            }
            return;
        }

        if (data == current->data_)
            return;
    }
}

bool List::operator==(const List& other) const
{
    if (this->head_ == nullptr && other.head_ == nullptr)
        return true;
    else if ((!this->head_ && other.head_)
        || (this->head_ && !other.head_))
        return false;
    else
    {
        Node* thisList;
        Node* otherList;

        for (thisList = this->head_, otherList = other.head_;
            thisList && otherList;
            thisList = thisList->next_, otherList = otherList->next_)
        {
            if (thisList->data_ != otherList->data_)
                return false;
        }

        return !((!thisList && otherList) || (thisList && !otherList));
    }
}

List List::operator&(const List& other) const
{
    List current;

    if (!this->head_ && !other.head_)
        return current;

    if ((!this->head_ && other.head_) || (this->head_ && !other.head_))
        return current;

    Node* thisList;
    Node* otherList;

    for (thisList = this->head_, otherList = other.head_;
        thisList && otherList;
        thisList = thisList->next_, otherList = otherList->next_)
    {
        while (thisList->data_ < otherList->data_)
            if (thisList->next_)
                thisList = thisList->next_;
            else break;

        while (thisList->data_ > otherList->data_)
            if (otherList->next_)
                otherList = otherList->next_;
            else break;

        if (thisList->data_ == otherList->data_)
        {
            current.insertTail(thisList->data_);
        }
    }
    return current;
}

List List::operator|(const List& other) const
{
    List current;

    if (!this->head_ && !other.head_)
        return current;

    if (!this->head_ && other.head_)
    {
        current.head_ = other.head_;
        current.tail_ = other.tail_;
        return current;
    }

    if (this->head_ && !other.head_)
    {
        current.head_ = this->head_;
        current.tail_ = this->tail_;
        return current;
    }

    else
    {
        current.head_ = this->head_;
        current.tail_ = this->tail_;

        Node* curr = current.head_;

        for (Node* temp = other.head_; 
             temp; 
             temp = temp->next_)
            current += temp->data_;
    }
    return current;
}

void List::merge(List& other)
{
    if (!head_ && !other.head_ || head_ && !other.head_)
        return;

    if (!head_ && other.head_)
    {
        head_ = other.head_;
        tail_ = other.tail_;
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }

    if(head_ && other.head_)
    {
        Node* thisList = this->head_;
        Node* otherList = other.head_;

        while (otherList)
        {
            if (!thisList)
            {
                insertHead(otherList->data_);
                otherList = otherList->next_;
            }

            else if (!thisList->next_) 
            {
                *this += otherList->data_;
                otherList = otherList->next_;
            }

            else
            {
                if (otherList->data_ == thisList->data_)
                    otherList = otherList->next_;

                else if (otherList->data_ > thisList->data_)
                    thisList = thisList->next_;

                else if (otherList->data_ < thisList->data_)
                {
                    Node* temp = otherList;
                    std::swap(thisList->data_, otherList->data_);
                    otherList = temp->next_;

                    if (thisList->next_)
                        temp->next_ = thisList->next_;

                    else temp->next_ = otherList;

                    thisList->next_ = temp;
                    thisList = thisList->next_;
                }
            }
        }
        other.head_ = nullptr;
        other.tail_ = nullptr;
    }
}

void List::insertHead(int data)
{
    if (!head_)
    {
        head_ = new Node(data, nullptr);
        tail_ = head_;
    }
    else
    {
        Node* temp = head_;
        head_ = new Node(data, temp);
    }
}

void List::insertTail(int data)
{
    if (!tail_)
        insertHead(data);

    else
    {
        Node* temp = tail_;
        tail_ = new Node(data, nullptr);
        temp->next_ = tail_;
    }
}

std::ostream& operator<<(std::ostream& out, const List& list) {
    if (!list.head_)
    {
        out << "{Empty List}";
        return out;
    }
    std::cout << "{";
    for (List::Node* n = list.head_; n; n = n->next_)
    {
        out << n->data_;
        if (n->next_)
            std::cout << ", ";
    }
    std::cout << "}";
    return out;
}
//
//List::~List() 
//{
//    Node* current = head_;
//
//    while (head_)
//    {
//        head_ = head_->next_;
//        std::cout << current->data_ << " ";
//        delete current;
//        current = head_;
//    }
//}