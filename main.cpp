// MyVector.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <ctime>
#include <algorithm>
//#include <vector>

using namespace std;
template <typename ElemType>
class MyVector{
	size_t theSize;     // theSize ���������������ã��Ƽ� mSize m_size ���� _size
	size_t theCapacity;
	ElemType *vectors;  // vectors? Ϊʲô��������֣����ﱣ���˺ܶ�vectorô��

public:
	//??
	typedef MyVector<ElemType>* iterator;       // ����������ԡ� typedef ElemType* iterator ����ࡣ
	typedef const MyVector<ElemType>* const_iterator;

    // iterator��ָ��ķ������(�������)��Ҳ����һ�ֱ�ָ���ͨ�õĶ����������������iterator����node��
    // һ�������,iterator֧�ֵĶ�������:
    //    ++ iterator; ȡ��һ��Ԫ�ص�iterator
    //    -- iterator; ȡ��һ��Ԫ�ص�iterator
    //    * iterator; ȡ��ǰԪ�ص�����
    //    iterator + N; ȡ��N��Ԫ�ص�iterator
    // �����C++����iterator���������ʵ��java����Ҳ���ԡ���ʵ���ơ�

	MyVector(); // ���Ķ�����������ˣ�
	MyVector(size_t capactity);
	MyVector(const ElemType& ele, size_t n);


	MyVector(const MyVector<ElemType>& other);// ���Ķ�����������ˣ�
	~MyVector(); // ����������virtual

	ElemType& operator[](const size_t idx);
	// const ElemType& operator[](const size_t idx) const; // �������ҲҪʵ�֡�Ҫ��Ȼ����const������ͻ�ò������Vector��Ԫ���ˡ�

	MyVector<ElemType> & operator=(const MyVector<ElemType>& other);
	size_t capacity(); // const�� ���������const��!!!
	size_t size();    // const....
	void reserve(size_t n);
	bool isEmpty();
	void pushBack(const ElemType& ele);
	void popBack();
	//
	iterator begin(){ return iterator(&vectors[0]); };
	iterator end(){ return iterator(&vectors[theSize]); };
	void insert(size_t index, ElemType &ele);
	void insertByIterator(iterator position, ElemType &ele);

	void erase(size_t index);
	void eraseByIterator(iterator position);
};

/*
template <typename ElemType>
MyVector<ElemType>::MyVector(size_t size){
	theSize = size; // ���в��ԡ�����
	theCapacity = 2 * theSize + 1; // ����Ҳ���ԡ�C++�ĺ�����ʼ�������д���б����ע�͵����дһ������һ����ʵ��
	vectors = new ElemType[theCapacity];
}
*/
template <typename ElemType>
MyVector<ElemType>::MyVector(size_t sz) // ��ôʵ�֣������д��һ��������Ч�ʸ��ߣ���C++�����⣬��ôʵ�ֵ��߼�Ҳ���ԡ���һ���������capacity������size
    :theSize(sz), theCapacity(sz<<1+1), vectors(new ElemType[sz<<1+1])
{}

template <typename ElemType>
MyVector<ElemType>::MyVector(const ElemType& ele, size_t n) // ���ϸ����캯��һ������ôд���ԡ�
{
	theSize = n;
	theCapacity = 2 * theSize + 1;
	vectors = new ElemType[theCapacity];
	for (size_t i = 0; i < theSize; i++) // ++i , ����i++
	{
		vectors[i] = ele;
	}

}

template <typename ElemType>
MyVector<ElemType>::~MyVector(){
	delete[] vectors;
}

template <typename ElemType>
ElemType & MyVector<ElemType>::operator[](const size_t idx){
	return vectors[idx];
}

template <typename ElemType>
MyVector<ElemType>& MyVector<ElemType>::operator=(const MyVector<ElemType> &other){
	//delete[] this;
	theSize = other.theSize;
	theCapacity = other.theCapacity;

	vectors = new ElemType[theCapacity];
	for (size_t i = 0; i < theSize; i++) // ++i , ����i++
	{
		vectors[i] = other.vectors[i];

	}
	//vectors = other.vectors;
	return *this;
}

template <typename ElemType>
size_t MyVector<ElemType>::capacity(){
	return theCapacity;
}

template <typename ElemType>
size_t MyVector<ElemType>::size(){
	return theSize;
}

template <typename ElemType>
void MyVector<ElemType>::reserve(size_t n){
	if (n < theSize)
	{
	    cout << "invalue" << endl;
    }
	else
	{
		ElemType *oldVectors = vectors;
		vectors = new ElemType[n];

		for (size_t i = 0; i < theSize; i++){  // ++i , ����i++
			vectors[i] = oldVectors[i];
		}

		theCapacity = n;
		delete[] oldVectors;
	}
}

template <typename ElemType>
bool MyVector<ElemType>::isEmpty(){
	if (theSize == 0)
	{
//		cout << "the vector is empty" << endl;  // Ϊʲô�������
		return true;
	}
	else
	{
//		cout << "the vector is not empty" << endl;
		return false;
	}
}

template <typename ElemType>
void MyVector<ElemType>::pushBack(const ElemType& ele){
	if (theSize >= theCapacity){
		//cout << "the room is not enough!" << endl;
		size_t newcapacity = 2 * theSize;
		reserve(newcapacity);
	}

		vectors[theSize] = ele;  // ����ʲô������������
		theSize++; // ++theSize; ����theSize++;


}

template <typename ElemType>
void MyVector<ElemType>::popBack(){
	if (theSize <= 0){

		cout << "there is no elements in the vector!" << endl;
	}
	else
	{
		theSize--;
	}
	//return vectors[theSize];
}

template <typename ElemType>
//index caculate from 0  // ע�Ͳ���д������ġ���������ע�Ͱ�����������ص�������ֿ��ˡ�
void MyVector<ElemType>::insert(size_t index, ElemType &ele)  // ��Ҫ���ô�������������ŷ�������cpp���кü��֡�
{
	if (index > theSize+1)
	{
		cout << "invaild index!" << endl;
	}
	else
	{
		if (theSize==theCapacity)
		{
			//cout << "Please reserve the vector!";
			reserve(2 * theSize);
		}

		for (size_t i = theSize; i >= index; i--) // ++i , ����i++
		{
			vectors[i + 1] = vectors[i];
		}
		vectors[index] = ele;
		theSize++; // ++i , ����i++

	}

}

template <typename ElemType>
void MyVector<ElemType>::insertByIterator(iterator position, ElemType &ele)
{
	//? why size_t = MyVector<ElemType> - MyVector<Ele,Type>
	size_t index = position - begin();  // �������iterator����ľͲ��ԡ�������������Ǵ�ġ�
	cout << "the index is:" << index << endl;
	insert(index, ele);

}

template <typename ElemType>
//index caculate from 0
void MyVector<ElemType>::erase(size_t index)
{
	if (index >= theSize || index < 0)
	{
		cout << "invaild index!" << endl;
	}
	else
	{
		for (size_t i = index; i < theSize-1; i++)
		{
			vectors[i] = vectors[i + 1];
		}
		theSize--; // -- theSize;
	}

}

template <typename ElemType>
void MyVector<ElemType>::eraseByIterator(iterator position)
{
	size_t index = position - begin();
	erase(index);
}

int main(int argc, char* argv[])
{
//    {// BUG 1
//        MyVector<int> vec;  // ������벻������û����������캯��
//        vec.pushBack(12);
//    }

//    {// BUG 2
//        MyVector<int> vec(0);
//        vec.pushBack(1);
//        vec.pushBack(2);
//        MyVector<int> vec2(vec);
//        assert(vec2[0] == 1);
//        assert(vec2[1] == 2);
//    }
//    { // BUG 3
//        srand(time(0));
//        MyVector<int> vec(0);
//        for(int i=0;i<32768;++i){
//            vec.pushBack(rand());
//            cout<<"PUSH BACK " << i<<endl;
//        }
//    }

//    { // BUG 4
//        srand(time(0));
//        MyVector<int> vec(1);
//        for(int i=0;i<32768;++i){
//            vec.pushBack(rand());
//        }
//        sort(vec.begin(), vec.end());
//    }

	system("pause");
	return 0;
}

