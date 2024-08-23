#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "--------------------------" 


//////////////////////////////////////////////////////////////////////////////////// 
/////////         Class declaration (Объявление класса) :         ////////////////

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
	}*Head,*Tail;

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
	class ConstIterator:public ConstBaseIterator
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
	class ConstReverseIterator:public ConstBaseIterator
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
/////////         Class declaration end (Объявление класса конец) :         ////////////////
     //////////////////////////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////////////////////////////////
/////////         Class definition (Определение класса) :         ////////////////

/////////////////////////////////////////////////////////////////////////////////////
//////////               Element Methods:              ////////////
template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T> List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}

//////////              Element Methods:              ////////////
/////////////////////////////////////////////////////////////////////////////////////



////					Const base Iterator				////////////

template<typename T>bool List<T>::ConstBaseIterator:: operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}

template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::ConstBaseIterator:: operator*()const
{
	return Temp->Data;
}


///                        ConstIterator:                          ///
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator:: operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator:: operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator:: operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator List<T>::ConstIterator:: operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

////////////               Const reverse iterators       ////////////

template<typename T>typename  List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename  List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;

}
template<typename T>typename  List<T>::ConstReverseIterator& List<T>::ConstReverseIterator:: operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

///                        Iterator:                          ///
template<typename T>T& List<T>::Iterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;

}
///                        ReverseIterator:                          ///
template<typename T>T& List<T>::ReverseIterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;
}


//////////               Iterators Methods:              ////////////
//////////////////////////////////////////////////////////////////////////////////////
  


//////////////////////////////////////////////////////////////////////////////////////
  //////////               List Methods:              ////////////


template<typename T>typename List<T>::ConstIterator List<T>:: begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}


template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		//push_back(*it);
		push_front(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "CopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();//- проверка, что pop_front удаляет элементы (на выводе будет список деструкторов внизу)
	//while (Head)pop_front();//- проверка, что pop_front удаляет элементы (на выводе будет список деструкторов внизу)
	cout << "LDestructor:\t" << this << endl;
}

////            Operators:            //////

template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment:\t " << this << endl;
	return *this;
}

///         Adding elements:           /////



template<typename T>void List<T>:: push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		//// Создаем новый элемент
		//	Element* New = new Element(Data);

		////Привязываем новый элемент к началу списка
		//	New->pNext = Head;

		////Привязываем головной элемент списка к новому элементу
		//	Head->pPrev = New;

		////Смещаем голову на новый элемент
		//	Head = New;

		Head = Head->pPrev = new Element(Data, Head);
		//Head = Head->pPrev = New;

	}
	size++;
}


template<typename T>void List<T>:: push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		////create new element
		//	Element* New = new Element(Data);
		//	//Include new element to the list
		//	New->pPrev = Tail;
		//	Tail->pNext = New;
		//	//Move Tail to the new element
		//	Tail = New;

		Tail = Tail->pNext = new Element(Data, nullptr, Tail);

	}
	size++;
}


template<typename T>void List<T>:: insert(T Data, int Index)
{
	if (Index > size)return;
	if (Index == 0)return push_front(Data);
	if (Index == size)return push_back(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pNext;//	'size - Index-1' количество переходов
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	/*Element* New = new Element(Data);
	New->pNext=Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	//Temp->pPrev = Temp->pPrev->pNext=New;

	size++;
}

///         Removing elements:           /////


template<typename T>void List<T>:: pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;//В случае пустого списка
	if (Head == Tail) //В случае наличия единственного элемента в списке, на который указывают и голова и хвост
	{
		delete Head;
		Head = Tail = nullptr;
	}
	else
	{
		//1 Смещаем голову на след. элемент
		Head = Head->pNext;
		//2 Удаляем нач. элемент 'Head->pPrev' из памяти
		delete Head->pPrev;
		//Зануляем указатель 'Head->pPrev'
		Head->pPrev = nullptr;
	}
	size--;
}

template<typename T>void List<T>:: pop_back()
{
	if (Head == nullptr && Tail == nullptr)return;//В случае пустого списка
	if (Head == Tail) //В случае наличия единственного элемента в списке, на который указывают и голова и хвост
	{
		delete Head;
		Head = Tail = nullptr;
	}
	//if (Head == Tail)return pop_front();// Вместо первой части можно просто так написать и заставить работать pop_front при этом условии
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}

////         Methods:    //////

template<typename T>void List<T>:: print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке:" << size << endl;
}
template<typename T>void List<T>:: reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке:" << size << endl;
}

//////////               List Methods:              ////////////
/////////////////////////////////////////////////////////////////////////////////////
  



template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		*it *= 10;
	}
	return buffer;
}
/////////         Class definition end (Конец Определения класса ) :         ////////////////
/////////////////////////////////////////////////////////////////////////////////////////


//#define BASE_CHECK
//#define ITERATORS_CHECK
//#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;

	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
		//list.pop_front(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите index добавляемого элемента: "; cin >> index;
	cout << "Введите value добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	//list.print();
	for (int i : list)cout << i << tab; cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	/*for (List::Iterator it = list.end(); it != list.begin(); --it)
	{
		cout << *it << tab;
	}
	cout << endl;*/

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (List::ConstIterator it = list3.begin(); it != list3.end(); ++it)

	{
		*it *= 100;
	}
	for (int i : list3) cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

	List<int> i_list = { 3,5,8,13,21 };
	for (int i : i_list)cout << i << tab; cout << endl;
	for (List<int>::Iterator it = i_list.begin(); it != i_list.end(); ++it)
		cout << *it << tab;
	cout << endl;
	for(List<int>::ReverseIterator it=i_list.rbegin(); it != i_list.rend(); ++it)
		cout << *it << tab;
	cout << endl;

	cout << delimiter<<endl;
	///////////////////////////////////////////////////////////////////

	List<double> d_list = { 2.7,3.14,5.5,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::Iterator it = d_list.begin(); it != d_list.end(); ++it)
		cout << *it << tab;	cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it != d_list.rend(); ++it)
		cout << *it << tab;	cout << endl;
	cout << delimiter << endl;

	List<std::string> s_list = {"Хорошо","Живет","На","Свете","Винни","Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::Iterator it = s_list.begin(); it != s_list.end(); ++it)
		cout << *it << tab;	cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << tab;	cout << endl;

	cout << delimiter << endl;
}