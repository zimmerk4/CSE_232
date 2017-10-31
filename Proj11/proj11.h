#ifndef PAL_H
#define PAL_H

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<utility>
using std::swap;
#include<sstream>
using std::ostringstream;
#include<string>
using std::string;
#include<utility>
using std::pair; using std::make_pair;
#include<algorithm>

// forward declaration so we can make Element a friend of PAL
template<typename T>
class PAL;

//node class
template <typename T>
class Element{
private:
	Element *next_ = nullptr;
	string name_ = "";
	T color_ = T();
  
public:
	Element()=default;
	Element(string name, T d) : next_(nullptr), name_(name), color_(d){};
	friend ostream& operator<<(ostream& out, Element& n)
	{/*
		Prints the elements name and color in format "name:color"
	 */
		out << n.name_ << ":" << n.color_;
		return out;
	}
	friend class PAL<T>;
};


template<typename T>
class PAL{
private:
	Element<T> *back_ = nullptr;
	Element<T> *front_ = nullptr;
	void print_list(ostream& out);  
public:
	PAL()=default;
	PAL(Element<T> n) : back_(&n), front_(&n) {};
	PAL(string n, T d);
	PAL(const PAL&);
	PAL& operator=(PAL);
	~PAL();
	void add(Element<T> &n);
	void add(string name, T dat);
	pair<Element<T>*, Element<T>*> find(string name);    
	pair<Element<T>*, Element<T>*> find(Element<T> &n);
	void move_forward1(Element<T> &n);
	void move_to_front(Element<T> &n);  
	void move_back1(Element<T> &n);
	void move_to_back(Element<T> &n);  

	friend ostream& operator<<(ostream& out, PAL<T>& sl)
	{
		sl.print_list(out);
		return out;
	};
};

// START REST OF THE CODE HERE

template<typename T>
void PAL<T>::print_list(ostream & out)
{/*
	Prints list of elements in PAL object. Relies on overloaded << operator in Element class
 */
	if (back_ == nullptr)
	{
		out << "List empty" << endl;
	}
	else
	{
		for (Element<T> *ptr = back_; ptr != front_; ptr = ptr->next_)
		{
			out << *ptr << ", ";
		}
		out << *front_; // Prints last object in list without comma following
	}
}

template<typename T>
PAL<T>::PAL(string n, T d)
{/*
	Creates node in linked list with name, n and color data, d.
 */
	Element<T>* node = new Element<T>(n, d);
	back_ = node;
	front_ = node;
}

template<typename T>
PAL<T>::PAL(const PAL & p)
{/*
	Copy constructor adapted from singlelink.h 18.3 example code. Copies linked list p onto calling list
 */
	if (p.back_ == nullptr) {
		front_ = nullptr;
		back_ = nullptr;
	}
	else {
		back_= new Element<T>(p.back_->name_, p.back_->color_);
		front_ = back_;
		Element<T>* p_ptr = p.back_->next_;
		Element<T>* new_node;
		while (p_ptr != nullptr) {
			new_node = new Element<T>(p_ptr->name_, p_ptr->color_);
			front_->next_ = new_node;
			p_ptr = p_ptr->next_;
			front_ = new_node;
		}
	}
}

template<typename T>
PAL<T>& PAL<T>::operator=(PAL p)
{/*
	Overloaded = operator, assigns p to calling list
 */
	std::swap(front_, p.front_);
	std::swap(back_, p.back_);
	return *this;
}

template<typename T>
PAL<T>::~PAL()
{/*
	Destructor. Deletes every element in the list and sets the list's front and back pointer to nullptr.
 */
	for (Element<T>* del_el = back_; del_el != nullptr; del_el = back_)
	{
		back_ = back_->next_;
		delete del_el;
	}
	back_ = nullptr;
	front_ = nullptr;
}

template<typename T>
void PAL<T>::add(Element<T>& n)
{/*
	Adds element n to the back of the list. If list empty, sets element to front and back of list.
 */
	if (back_ != nullptr)
	{
		n->next_ = back_->next_;
		back_ = &n;
	}
	else
	{
		back_ = n;
		front_ = n;
	}
}

template<typename T>
void PAL<T>::add(string name, T dat)
{/*
	Creates element to add to back of list from name and color data. If list empty, element set to front 
	and back of list.
 */
	Element<T>* node = new Element<T>(name, dat);
	if (back_ != nullptr)
	{
		node->next_ = back_;
		back_ = node;
	}
	else
	{
		back_ = node;
		front_ = node;
	}
}

template<typename T>
pair<Element<T>*, Element<T>*> PAL<T>::find(string name)
{/*
	Finds element in list with name matching string name. If found, returns a pair with first being the 
	pointer to the found element and second being a pointer to the previous element in the list.
 */
	for (Element<T>* ptr = back_; ptr->next_ != nullptr; ptr = ptr->next_)
	{
		if (ptr->next_->name_ == name)
		{
			return make_pair(ptr->next_, ptr);
		}
	}
	return make_pair(nullptr, nullptr);
}

template<typename T>
pair<Element<T>*, Element<T>*> PAL<T>::find(Element<T>& n)
{/*
	Finds element in list with name matching element n's name. If found, returns a pair with first being 
	the pointer to the found element and second being a pointer to the previous element in the list.
 */
	for (Element<T>* ptr = back_; ptr->next_ != nullptr; ptr = ptr->next_)
	{
		if (ptr->next_->name_ == n.name_)
		{
			return make_pair(ptr->next_, ptr);
		}
	}
	return make_pair(nullptr, nullptr);
}

template<typename T>
void PAL<T>::move_forward1(Element<T>& n)
{/*
	Moves element forward in list towards front_. Calls find. If element not in list or already at front,
	method does nothing.
 */
	pair<Element<T>*, Element<T>*> ptrs = find(n);
	if (ptrs.first != nullptr)
	{
		if (ptrs.first->next_ != nullptr)
		{
			if (ptrs.first->next_ == front_)
			{
				ptrs.second->next_ = front_;
				ptrs.first->next_ = nullptr;
				front_->next_ = ptrs.first;
				front_ = ptrs.first;
			}
			else
			{
				ptrs.second->next_ = ptrs.first->next_;
				ptrs.first->next_ = ptrs.first->next_->next_;
				ptrs.second->next_->next_ = ptrs.first;
			}
		}
	}
}

template<typename T>
void PAL<T>::move_to_front(Element<T>& n)
{/*
	Moves element to front of list. Calls find. If element not in list or already at front, method does nothing.
 */
	pair<Element<T>*, Element<T>*> ptrs = find(n);
	if (ptrs.first != nullptr)
	{
		if (ptrs.first->next_ != nullptr)
		{
			ptrs.second->next_ = ptrs.first->next_;
			front_->next_ = ptrs.first;
			front_ = ptrs.first;
			front_->next_ = nullptr;
		}
	}
}

template<typename T>
void PAL<T>::move_back1(Element<T>& n)
{/*
	Moves element back in list towards back_. Calls find. If element not in list or already in back,
	method does nothing.
 */
	pair<Element<T>*, Element<T>*> ptrs = find(n);
	if (ptrs.first != nullptr)
	{
		if (ptrs.second != nullptr)
		{
			pair<Element<T>*, Element<T>*> prev_ptrs = find(*ptrs.second);  // Finds 2 nodes towards back from node n

			if (ptrs.second == back_)
			{
				ptrs.second->next_ = ptrs.first->next_;
				ptrs.first->next_ = ptrs.second;
				back_ = ptrs.first;
			}
			else
			{
				ptrs.second->next_ = ptrs.first->next_;
				ptrs.first->next_ = ptrs.second;
				prev_ptrs.second->next_ = ptrs.first;
			}
		}
	}
}

template<typename T>
void PAL<T>::move_to_back(Element<T>& n)
{/*
	Moves element to back of list. Calls find. If element not in list or already in back, method does nothing.
 */
	pair<Element<T>*, Element<T>*> ptrs = find(n);
	if (ptrs.first != nullptr)
	{
		if (ptrs.second != nullptr)
		{
			if (ptrs.first == front_)
			{
				ptrs.second->next_ = nullptr;
				front_ = ptrs.second;
				ptrs.first->next_ = back_;
				back_ = ptrs.first;
			}
			else
			{
				ptrs.second->next_ = ptrs.first->next_;
				ptrs.first->next_ = back_;
				back_ = ptrs.first;
			}
		}
	}
}

#endif
