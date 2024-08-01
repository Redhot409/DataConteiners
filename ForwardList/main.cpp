#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------\n"

class Element
{    // �� ���� �������� ������� ������
	int Data; //�������� ��������
	Element* pNext; // Pointer to Next - ��������� �� ����� ����. ��������
	static int count;
public:

	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext) // ��������� nullprt, ������ ��� ��� ����� ������ � ������������ �� ���������
																		   //: Data(Data), pNext(pNext) - ����� ���������� ����� ������ � ���������
	{
		count++;;
		cout <<" EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << " EDestructor:\t" << this << endl;
	}
	
	// ����� ������������ � ����������� ����, ����� �����������, ����� �������� � ����� �������� �������
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
	Element* Head;// ������ ������, ��������� �� ����� ���������� �������� ������
	int size; // ����������, ������� � ������������ �� ��������� ���������
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
		// ����������� �� ���������, ������� ������� ������ ������
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList(int size):ForwardList()// ����������� �� �������� ���-�� ��������� ������
	{
		while (size--)push_front(0);
	}

	ForwardList(const ForwardList& other) :ForwardList() // ����������� �����������. �� ������ ��������� ��� �������� � �������� � ����� ������
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
			*this = other;// �������� ���������� ��� Copyassignment
			cout<<"CopyConstructor: \t"<<this<<endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);// ������� std::move () ������������� �������� MoveAssignment ��� ������
		cout << "MoveConstructor:" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//il.
		for (const int* it = il.begin(); it != il.end(); it++)
			//it - ��������
			push_back(*it);
	}

	~ForwardList()
	{
		while (Head)pop_front();
		//while (Head)pop_back();// - ����� ����� ������� �������� ����� pop_back
		cout << "LDestructor:\t" << this << endl;
		// ��������� ������ ���� ������� Head is true (���� ������ ��������� �� ������������ ������� ������) � ������ ����� �� ������
		// ��� ������ Head ��������� �� nullptr, � ��� ����� �� ��������������� ���� pop_front()
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
		// 1- ������� ����� �������
		//Element* New = new Element(Data);// �������� New �������� ����������� ������,
		// � �� �������� � ���� ����������� �������� ��������

// 2 -�������������� ����� ������� � ������ ������
		//New->pNext = Head; // ���������� -> �� �������� ���������� � ����������-����� ������ Element
		// � ����� ���������� ������������ (get/set ������, ������� ���), ������� �������� friend ������
		// ����� � ���, ����� ��������� ��������� ������ ������ �������� New ��������� �� ����� � ������� pNext, ����������� � Head 
// 3 - ������ �������������� �� ����� �������.��������� �� ����� ������ �������� ������ � ������
		//Head = New; // ��� ��� � �� � ��- ���������

		Head = new Element(Data,Head);
		//New->pNext = Head; 
		//Head = New; 
		
		size++; //������ ����������� ������� ����� ������������ ���� size
	}
	
	  ///////            Operators:        /////////////   

	int& operator [](int index)// ���� ���������� ������ �� �������� int operator(��� ���������� &), ��
		// � ��� ������������ �������� ���������� ������, ������� ������� �������� ����������
		// �������, ��������� ������ list[i]=rand() % 100; � ������ (265) - ������ ��� �� ����� ������
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp=Temp->pNext;
		return Temp->Data;
	}

	const int& operator [](int index)const// ���� ���������� ������ �� �������� int operator(��� ���������� &), ��
		// � ��� ������������ �������� ���������� ������, ������� ������� �������� ����������
		// �������, ��������� ������ list[i]=rand() % 100; � ������ (265) - ������ ��� �� ����� ������
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	

	/////           Adding elements: push_back        //////////


	void push_back(int Data)
	{
		//��������� push_back �� �������� � ������ �������, �� ���������
		// ���� ������ ����, �������� ����� push_front, ������� ����� �������� � ������ �������
		if (Head == nullptr) return push_front(Data);
		//1) ������� ����� �������
		Element* New = new Element(Data);
		//2) ������� �� ����� ������
		Element* Temp = Head;//��������
		while (Temp->pNext)Temp = Temp->pNext;
		//3) ����� ����, ��� �� ��������� � ����� ������
		Temp == nullptr;
		//Temp->pNext = New;//����� ����, ��� ����� �� while, �� �������� � �������� �������, � �������� ��������� ����� nullptr
		Temp->pNext = new Element(Data);
		// ���� :Temp == nullptr - ��� �������� ��� ������� � ����� �� ������
		// push back �� ����� �������� � ������ �������
		size++;
	}

	void insert(int Index, int Data)
	{
		//�������� � ������� �������� ���������� ��������� � ����������� ���������� count:
		if (Index > size )//Head->count �� �������� �� size, ����� �� ����� � ��� ����� ������� ���������� ���������
		{
			cout << "Error: out of range" << endl;
			return;
		}
		//���� ������ ������������ �������� 0, �� ������ �������� � ���������� push_front:
		if (Index == 0)return push_front(Data);
		// 1 ������� �������
		//Element* New = new Element(Data);
		
		//2 ������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)// Index-1 - ������ �� ������� ������, ����� ������� ��� ��������� �� ����������� ����� �������  
		{
			if (Temp->pNext == nullptr)break;// ����� ���������� ����� break ������� Temp = Temp->pNext � ����� ������� ��������� � ����� ������ ->>>
				Temp = Temp->pNext; // �������� ������� �� ��������� �������
		}
		//3 ��������� ������� new � ������
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);

		size++;

	}

	/////// Removing elements :  pop_front ///////

	void pop_front()
	{
		// ��������, ���� ������ ����:
		if (Head == nullptr)return;// �.� ��� ����� ������� ����� ��������� ������ �-��� � void-�� (����� �� �������)
		// ������� ��������� Erased � ����������� ��� ����� ���������� ��������. ���������� ����� ���������� ��������:
		// ����� ���������� �������� ��������� � �������, �� ������� ��������� ������ Head.
		Element* Erased = Head;// ��� ������ � ��������: ������� ��������� �� ������� Erased � ��������� ��� ��������� Head 
		// ��������� ��������� ������� �� ������:
		Head = Head->pNext; // ������ ������� ������� ��������� �� ������ ������� �� ��������� ���������� �������� (pNext)
		//  ������� ������� �� ������:
		delete Erased;
		/*
		new - ������� ������ � ������������ ������
		new[] - ������� ������ �������� � ������������ ������

		delete - ������� 1 ������ � ������������ ������
		delete [] - ������� ������ �������� � ������������ ������

		���� new [], �� delete ���� ������ ���� � ����������� �������� (delete[] new....[....])
		� �������� delete new ....
		--------------
		�� � ��������� �++ ���� delete new ....[....] ; behaviour is undefined
		delete[] new...; behaviour is undefined
		� ���� ������� ��������� ����� ������������ ���������������� ���� ��� �� ��������, ���� ��� ���, ���� ������ ������
		--------------
		
		*/
		size--;
	}

	/////// Removing elements :  pop_back ///////

	void pop_back()
	{
		//���� Head = nullptr, �� ����� �����������
		//���� � ������ ���� �������, ��:
		if (Head->pNext == nullptr) return pop_front(); // ���� ������� ������� ������ ��������(Head->pNext == nullptr), �����
		// ��������� ������ ������� return-�� � ������� ������� pop_front()
		//1) ������� �� ��������������
		Element* Temp = Head;// � ��� ����� ������� �������� Temp � ����������� ��� ��� �� ���������, ��� � � Head
		// ��� ��� � ������ ���������� ����� ����� ������ ����� ������
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		// (Temp->pNext->pNext)������, ��� �� ���� �� �������������� ��������, � �������� pNext = 1 (True) � �� false (nullptr ��� � ���������� ��������) 
		
		// 2) ������� ��������� ������� �� ������
		delete Temp->pNext;
		// �������� ��������� �� ��������� �������
		Temp->pNext = nullptr;
		// ��� �������� ������ ����� ����� ����c��� Destructor ������ ������� ������ �������� ���� ������ ����� ���������
		// go to line 40 -------->>>>>>>>> line 40
		size--;
	}


	//////            Methods             //////////////

	void print()const
	{
		//Element* Temp = Head; // ����- ��� ��������. 
		 
		//��������- ��� ���������, � ������� �������� ����� �������� ������ � ��������� ��������� ������
		//while (Temp)
		//for (Element* Temp=Head;Temp;Temp=Temp->pNext)
		//{
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			//Temp = Temp->pNext;// ������� �� ��������� �������
		//}
		//cout << "���������� ��������� ������: " << Head->count; ����� ����� size ����� ����� �����
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ���������: " << Element::count << endl;// � ����������� ���������� ����� ���������� � ������
		// ����, ����� � ����� ����� ������ � ������
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
	//buffer - ��� ��������� ������, �������. ������ � �������� �-��� operator +
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
	cout << "������� ���������� ��������� ������: "; cin >> n;
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
	cout << " ������� ������ ������������ ��������: "; cin >> index;
	cout << " ������� �������� ������������ ��������: "; cin >> value;
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
	////Range- ��������. ����� �������� ���������
	////�.�. ���������� ������ �������� range
	//// �������������, Range - based for:- ��� ���� for ��� ����������� 
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

	