#ifndef CLASS_10
#define CLASS_10

#include <initializer_list>
#include <ostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class BiStack;
template<typename T>
std::ostream& operator<<(std::ostream& oss, BiStack<T>& b);

template<typename T>
class BiStack
{
private:
    T* ary_;
    size_t size_;
    size_t max_size_;
    size_t capacity_;
	long top1_;
	long top2_;
    void grow_and_copy();

public:
    BiStack(size_t capacity = 4, size_t max_size = 16);
    BiStack(std::initializer_list<T> vals, size_t max_size = 16);
    BiStack(BiStack& b);
    ~BiStack();
    BiStack& operator=(BiStack b);
    size_t capacity();
    size_t size();
    size_t max();
    void push1(T val);
    void push2(T val);
    T top1();
    T top2();
    void pop1();
    void pop2();
    bool empty1();
    bool empty2();
    friend std::ostream& operator<< <T>(std::ostream& oss, BiStack<T>& b);
};

template<typename T>
void BiStack<T>::grow_and_copy()
{/*
	Doubles the size of the underlying array if the new array will be under the maximum
	alloted size given by max_size. Throws overflow error if greater than max_size.
	Fills empty spots in the array with default value for T type. 
 */
	T fill_val = T();  // Default filler value for "empty" spots in ary_
	if (capacity_ * 2 <= max_size_)
	{
		top2_ += capacity_;
		capacity_ *= 2;
		T* new_ary = new T[capacity_];
		for (int i = 0; i < capacity_; ++i)
		{
			if (i <= top1_)
			{
				new_ary[i] = ary_[i];
			}
			else if (i > top1_ && i < top2_)
			{
				new_ary[i] = fill_val;
			}
			else if (i >= top2_)
			{
				new_ary[i] = ary_[i - (capacity_ / 2)];
			}
		}
		std::swap(ary_, new_ary);
		delete[] new_ary;
	}
	else
	{
		throw std::overflow_error("stack past max");
	}
}
template<typename T>
BiStack<T>::BiStack(size_t capacity, size_t max_size) : size_(0), max_size_(max_size), capacity_(capacity), ary_(new T[capacity]), top1_(-1), top2_(capacity){}

template<typename T>
BiStack<T>::BiStack(std::initializer_list <T> vals, size_t max_size) : size_(vals.size()), max_size_(max_size), capacity_(vals.size()), ary_(new T[vals.size()]), top1_(vals.size() - 1), top2_(vals.size())
{
	std::copy(vals.begin(), vals.end(), ary_);
}

template<typename T>
BiStack<T>::BiStack(BiStack& b)
{/*
	Copy constructor to make a copy of BiStack.
 */
	size_ = b.size_;
	capacity_ = b.capacity_;
	max_size_ = b.max_size_;
	top1_ = b.top1_;
	top2_ = b.top2_;
	ary_ = new T[b.capacity_];
	std::copy(b.ary_, b.ary_ + b.size_, ary_);
}

template<typename T>
BiStack<T>::~BiStack()  // Destructor
{
	delete[] ary_;
}

template<typename T>
BiStack<T>& BiStack<T>::operator=(BiStack b)
{/*
	Overloads assignment operator to assign one BiStack to another.
 */
	std::swap(this->size_, b.size_);
	std::swap(this->max_size_, b.max_size_);
	std::swap(this->capacity_, b.capacity_);
	std::swap(this->top1_, b.top1_);
	std::swap(this->top2_, b.top2_);
	std::swap(this->ary_, b.ary_);
	return *this;
}

template<typename T>
size_t BiStack<T>::capacity()
{/*
	Returns private value capacity_
 */
	return capacity_;

}

template<typename T>
size_t BiStack<T>::size()
{/*
	Returns private value size_
 */
	return size_;
}

template<typename T>
size_t BiStack<T>::max()
{/*
	Returns private value max_size
 */
	return max_size_;
}

template<typename T>
void BiStack<T>::push1(T val)
{/*
	Pushes value into stack1 if not full. Calls grow_and_copy() if full.
 */
	if (top1_ < top2_ - 1)
	{
		ary_[top1_ + 1] = val;
		++top1_;
		++size_;
	}
	else
	{
		grow_and_copy();
		ary_[top1_ + 1] = val;
		++top1_;
		++size_;
	}
}

template<typename T>
void BiStack<T>::push2(T val)
{/*
	Pushes value into stack2 if not full. Calls grow_and_copy() if full.
 */
	if (top1_ < top2_ - 1)
	{
		ary_[top2_ - 1] = val;
		--top2_;
		++size_;
	}
	else
	{
		grow_and_copy();
		ary_[top2_ - 1] = val;
		--top2_;
		++size_;
	}
}

template<typename T>
T BiStack<T>::top1()
{/*
	Returns value on top of stack1
 */
	if(empty1())
	{
		throw std::underflow_error("underflow stack 1");
	}
	else
	{
		return ary_[top1_];
	}
}

template<typename T>
T BiStack<T>::top2()
{/*
	Returns value on top of stack2
 */
	if (empty2())
	{
		throw std::underflow_error("underflow stack 2");
	}
	else
	{
		return ary_[top2_];
	}
}

template<typename T>
void BiStack<T>::pop1()
{/*
	Pops value on top of stack1. Returns nothing.
 */
	if (empty1())
	{
		throw std::underflow_error("underflow stack 1");
	}
	else
	{
		--top1_;  // "Removes" top value by decrimenting top. Value still in memory.
		--size_;
	}
}

template<typename T>
void BiStack<T>::pop2()
{/*
	Pops vlaue on top of stack2. Returns nothing.
 */
	if (empty2())
	{
		throw std::underflow_error("underflow stack 2");
	}
	else
	{
		++top2_;  // "Removes" top value by incrimenting top. Value still in memory.
		--size_;
	}
}


template<typename T>
bool BiStack<T>::empty1()
{/*
	Returns true if stack 1 empty
 */
	if (top1_ == -1)
	{
		return true;
	}
	return false;
}

template<typename T>
bool BiStack<T>::empty2()
{/*
	Returns true if stack 2 empty
 */
	if (top2_ == capacity_)
	{
		return true;
	}
	return false;
}

template<typename T>
std::ostream & operator<<(std::ostream & oss, BiStack<T>& b)
{/*
	Overloaded <<operator to print BiStack in logical manner. Prints index of top 1 & 2
	as well as the size, capacity, and elements in the BiStack.
 */
	if (b.empty1())
	{
		oss << "Top1 empty" << std::endl;
		if (b.empty2())
		{
			oss << "Top2 empty" << std::endl;
		}
		else
		{
			oss << "Top2 index:" << b.top2_ << std::endl;
		}
	}
	else
	{
		oss << "Top1 index:" << b.top1_ << std::endl;
		if (b.empty2())
		{
			oss << "Top2 empty" << std::endl;
		}
		else
		{
			oss << "Top2 index:" << b.top2_ << std::endl;
		}
	}
	oss << "Size:" << b.size_ << std::endl;
	oss << "Capacity:" << b.capacity_ << std::endl;
	for (int i = 0; i < b.capacity_ - 1; ++i)
	{
		oss << b.ary_[i] << ",";
	}
	oss << b.ary_[b.capacity_ - 1];
	return oss;
}
#endif //CLASS_10
