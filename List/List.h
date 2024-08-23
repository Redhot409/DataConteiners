
#pragma once
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "--------------------------" 


//////////////////////////////////////////////////////////////////////////////////// 
/////////         Class declaration (ќбъ€вление класса) :         ////////////////

template <typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();

		friend class List;
	}*Head, * Tail;

	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "CBItConstructor\t" << this << endl;
		}

		~ConstBaseIterator()
		{
			cout << "CBItDestructor\t" << this << endl;
		}
		bool operator==(const ConstBaseIterator& other)const;

		bool operator!=(const ConstBaseIterator& other)const;

		const T& operator*()const;

	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		ConstIterator& operator++();
		ConstIterator& operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);

	};
	class ConstReverseIterator :public ConstBaseIterator
	{
		//Element* Temp;
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ConstReverseIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		//     Increment/Decrement :   //

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);

	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();

	};

	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	////            Operators:            //////

	List<T>& operator=(const List<T>& other);

	///         Adding elements:           /////

	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	///         Removing elements:           /////

	void pop_front();
	void pop_back();

	////         Methods:    //////

	void print()const;
	void reverse_print()const;

};
/////////         Class declaration end (ќбъ€вление класса конец) :         ////////////////
	 //////////////////////////////////////////////////////////////////////////////////// 
