#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------\n"

class Element
{    // Из чего строится элемент списка
	int Data; //значение элемента
	Element* pNext; // Pointer to Next - указатель на адрес след. элемента
	static int count;
public:

	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext) // Присвоили nullprt, потому что так проще задать в конструкторе по умолчанию
																		   //: Data(Data), pNext(pNext) - пишем переменные члены класса в заголовке
	{
		count++;;
		cout <<" EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << " EDestructor:\t" << this << endl;
	}
	
	// Вывод конструктора и деструктора выше, чтобы отслеживать, когда создался и когда удалился элемент
	friend class Iterator;
	friend class ForwardList;
};
int Element::count = 0;


class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "IConstructor:\t" << endl;
	}
	~Iterator()
	{
		cout << "IDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}

};

class ForwardList
{
	Element* Head;// Голова списка, указывает на адрес начального элемента списка
	int size; // Переменная, которая в конструкторе по умолчанию обуняется
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	int get_size()const
	{
		return size;
	}
	ForwardList()
	{
		//count++;
		// Конструктор по умолчанию, который создает пустой список
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size):ForwardList()// Конструктор на заданное кол-во элементов списка
	{
		while (size--)push_front(0);
	}

	ForwardList(const ForwardList& other) :ForwardList() // конструктор копирования. Он должен перебрать все элементы и записать в новый список
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
			*this = other;// повторно используем код Copyassignment
			cout<<"CopyConstructor: \t"<<this<<endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);// Функция std::move () принудительно вызывает MoveAssignment для класса
		cout << "MoveConstructor:" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//il.
		for (const int* it = il.begin(); it != il.end(); it++)
			//it - итератор
			push_back(*it);
	}

	~ForwardList()
	{
		while (Head)pop_front();
		//while (Head)pop_back();// - можно также удалять элементы через pop_back
		cout << "LDestructor:\t" << this << endl;
		// Очищается список пока условие Head is true (пока голова указывает на существующий элемент списка) и список будет не пустой
		// как только Head указывает на nullptr, у нас сразу же останавливается цикл pop_front()
	}

	///////            Operators:        /////////////   

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		//while (Head)pop_front();
		this->~ForwardList();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyConstructor: \t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment: \t" << this << endl;
	}
		
	/////           Adding elements:  push_front      //////////


	void push_front(int Data)
	{
		// 1- создаем новый элемент
		//Element* New = new Element(Data);// Оператор New вызывает конструктор класса,
		// и мы передаем в этот конструктор значение элемента

// 2 -Пристыковываем новый элемент к началу списка
		//New->pNext = Head; // стрелочкой -> мы пытаемся обратиться к переменной-члену класса Element
		// и здесь включается инкапсуляция (get/set методы, которых нет), поэтому включаем friend классы
		// Смысл в том, чтобы присвоить указателю адреса нового элемента New указатель на адрес в прошлом pNext, находящийся в Head 
// 3 - Голову перенаправляем на новый элемент.Указатель на Адрес нового элемента кладем в голову
		//Head = New; // так как и то и то- указатели

		Head = new Element(Data,Head);
		//New->pNext = Head; 
		//Head = New; 
		
		size++; //Каждый добавляемый элемент будет инкрементить этот size
	}
	
	  ///////            Operators:        /////////////   

	int& operator [](int index)// Если возвращать просто по значению int operator(без амперсанда &), то
		// у нас возвращается временно безымянный объект, который априори является константой
		// поэтому, возникает ошибка list[i]=rand() % 100; в вызове (265) - меняем как бы конст объект
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp=Temp->pNext;
		return Temp->Data;
	}

	const int& operator [](int index)const// Если возвращать просто по значению int operator(без амперсанда &), то
		// у нас возвращается временно безымянный объект, который априори является константой
		// поэтому, возникает ошибка list[i]=rand() % 100; в вызове (265) - меняем как бы конст объект
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	

	/////           Adding elements: push_back        //////////


	void push_back(int Data)
	{
		//Поскольку push_back не работает с пустым списком, мы проверяем
		// если список пуст, вызываем метод push_front, который умеет работать с пустым списком
		if (Head == nullptr) return push_front(Data);
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		//2) Доходим до донца списка
		Element* Temp = Head;//итератор
		while (Temp->pNext)Temp = Temp->pNext;
		//3) После того, как мы оказались в конце списка
		Temp == nullptr;
		//Temp->pNext = New;//После того, как пошли по while, мы уперлись в конечный элемент, у которого указатель будет nullptr
		Temp->pNext = new Element(Data);
		// Выше :Temp == nullptr - это показано для справки и можно не писать
		// push back не умеет работать с пустым списком
		size++;
	}

	void insert(int Index, int Data)
	{
		//Проверка с помощью подсчета количества элементов и статической переменной count:
		if (Index > size )//Head->count мы заменили на size, когда ее ввели и она стала считать количество элементов
		{
			cout << "Error: out of range" << endl;
			return;
		}
		//Если индекс добавляемого элемента 0, то делаем проверку и используем push_front:
		if (Index == 0)return push_front(Data);
		// 1 Создаем элемент
		//Element* New = new Element(Data);
		
		//2 Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)// Index-1 - делаем на переход меньше, чтобы элемент мог указывать на вставляемый новый элемент  
		{
			if (Temp->pNext == nullptr)break;// тогда прерывание после break вызовет Temp = Temp->pNext и новый элемент добавится в конец списка ->>>
				Temp = Temp->pNext; // означает переход на следующий элемент
		}
		//3 Вставляем элемент new в список
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);

		size++;

	}

	/////// Removing elements :  pop_front ///////

	void pop_front()
	{
		// Проверка, если список пуст:
		if (Head == nullptr)return;// т.е при таком условии сразу прерываем работу ф-ции с void-ом (выход из функции)
		// Создаем указатель Erased и присваиваем ему адрес удаляемого элемента. Запоминаем адрес удаляемого элемента:
		// адрес удаляемого элемента совпадает с адресом, на который указывает голова Head.
		Element* Erased = Head;// Эта запись и означает: Создать указатель на элемент Erased и присвоить ему указатель Head 
		// Исключаем удаляемый элемент из списка:
		Head = Head->pNext; // Просто смещаем текущий указатель на первый элемент на указатель следующего элемента (pNext)
		//  Удаляем элемент из памяти:
		delete Erased;
		/*
		new - создает объект в динамической памяти
		new[] - создает массив объектов в динамической памяти

		delete - удаляет 1 объект в динамической памяти
		delete [] - удаляет массив объектов в динамической памяти

		если new [], то delete тоже должен быть с квадратными скобками (delete[] new....[....])
		и наоборот delete new ....
		--------------
		но в стандарте с++ есть delete new ....[....] ; behaviour is undefined
		delete[] new...; behaviour is undefined
		в этих случаях программа будет отрабатывать непредсказуемого либо как со скобками, либо без них, либо упадет вообще
		--------------
		
		*/
		size--;
	}

	/////// Removing elements :  pop_back ///////

	void pop_back()
	{
		//Если Head = nullptr, то сразу заканчиваем
		//если в списке один элемент, то:
		if (Head->pNext == nullptr) return pop_front(); // если условие наличие одного элемента(Head->pNext == nullptr), тогда
		// прерываем работу функции return-ом с вызовом функции pop_front()
		//1) Доходим до предпоследнего
		Element* Temp = Head;// и для этого Создаем итератор Temp и присваиваем ему тот же указатель, что и у Head
		// так как в список итератором можно зайти только через голову
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		// (Temp->pNext->pNext)значит, что мы идем до предпоследнего элемента, у которого pNext = 1 (True) а не false (nullptr как у последнего элемента) 
		
		// 2) Удаляем последний элемент из памяти
		delete Temp->pNext;
		// Обнуляем указатель на последний элемент
		Temp->pNext = nullptr;
		// Для проверки работы проще всего напиcать Destructor списка который должен очистить весь список перед удалением
		// go to line 40 -------->>>>>>>>> line 40
		size--;
	}


	//////            Methods             //////////////

	void print()const
	{
		//Element* Temp = Head; // Темп- это итератор. 
		 
		//Итератор- это указатель, с помощью которого можно получить доступ к элементам структуры данных
		//while (Temp)
		//for (Element* Temp=Head;Temp;Temp=Temp->pNext)
		//{
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			//Temp = Temp->pNext;// Переход на следующий элемент
		//}
		//cout << "Количество элементов списка: " << Head->count; после ввода size вывод будет таким
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;// К статической переменной лучше обращаться в классе
		// хотя, можно и через любой объект в классе
	}
};
//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define OPERATOR_PLUS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	//ForwardList buffer;
	//buffer - это локальный объект, существ. только в пределах ф-ции operator +
	ForwardList buffer=left;
	//for (int i=0;i<left.get_size();buffer.push_back(left[i]));
	for (int i=0;i<right.get_size();buffer.push_back(right[i]));
	return buffer;
}

void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	for (int i=0;i<sizeof(arr)/ sizeof(arr[0]);i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}
void main()
{
	setlocale(LC_ALL, "");


#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	/*list.push_back(123);
	list.print();
	list.pop_front();
	list.print();*/

	int index;
	int value;
	cout << " Введите индекс добавляемого элемента: "; cin >> index;
	cout << " Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK
	
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimeter << endl;
	//ForwardList list3 = list1 + list2;// copyConstructor
	cout << delimeter << endl;
	ForwardList list3;
	cout << delimeter << endl;
	list3 = list1 + list2;//CopyAssignmen
	cout << delimeter << endl;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef INITIALIZER_LIST_CONSTRUCTOR_CHECK
	ForwardList list1 = { 3,5,8,13,21 };
	list1.print();
#endif // INITIALIZER_LIST_CONSTRUCTOR_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	//int* arr = new int[5] {3, 5, 8, 13, 21};
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	/// Range - based for:
	////Range- диапазон. Здесь понимают контейнер
	////т.е. контейнеры иногда называют range
	//// Следовательно, Range - based for:- это цикл for для контейнеров 
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << typeid(arr).name() << endl;
	Print(arr);
	delete[] arr;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	//list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}
#endif // RANGE_BASED_FOR_LIST

	