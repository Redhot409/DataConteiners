#include"List.h"



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


template<typename T>typename List<T>::ConstIterator List<T>::begin()const
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



template<typename T>void List<T>::push_front(T Data)
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


template<typename T>void List<T>::push_back(T Data)
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


template<typename T>void List<T>::insert(T Data, int Index)
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


template<typename T>void List<T>::pop_front()
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

template<typename T>void List<T>::pop_back()
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

template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке:" << size << endl;
}
template<typename T>void List<T>::reverse_print()const
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
