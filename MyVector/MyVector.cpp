// MyVector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
//#include <vector>

using namespace std;
template <typename ElemType>

class MyVector{
	size_t _size;
	size_t _capacity;
	ElemType *vectorElem;
	
public:
	//??
	//typedef MyVector<ElemType>* iterator;
	typedef ElemType* iterator;
	//typedef const MyVector<ElemType>* const_iterator;

	MyVector();
	MyVector(size_t capactity);
	MyVector(const ElemType& ele, size_t n);
	MyVector(const MyVector<ElemType>& other);
	 ~MyVector();

	ElemType& operator[](const size_t idx);
	MyVector<ElemType> & operator=(const MyVector<ElemType>& other);
	size_t capacity() const;
	size_t size() const;
	void reserve(size_t n);
	bool isEmpty();	
	void pushBack(const ElemType& ele);
	void popBack();
	//
	iterator begin(){ return iterator(&vectorElem[0]); };
	iterator end(){ return iterator(&vectorElem[_size]); };
	void insert(size_t index, ElemType &ele);
	void insertByIterator(iterator position, ElemType &ele);

	void erase(size_t index);
	void eraseByIterator(iterator position);
};

template <typename ElemType>
MyVector<ElemType>::MyVector(size_t size):_size(size),_capacity(2*_size+1),vectorElem(new ElemType[2*_size+1]){
	//_size = size;
	//_capacity = 2 * _size + 1;
	//vectorElem = new ElemType[_capacity];
}

template <typename ElemType>
MyVector<ElemType>::MyVector(const ElemType& ele, size_t n) :_size(n), _capacity(2 * _size + 1), vectorElem(new ElemType[2*_size+1]){
	//_size = n;
	//_capacity = 2 * _size + 1;
	//vectorElem = new ElemType[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		vectorElem[i] = ele;
	}

}

template <typename ElemType>
MyVector<ElemType>::~MyVector(){
	delete[] vectorElem;
}

template <typename ElemType>
ElemType & MyVector<ElemType>::operator[](const size_t idx){
	return vectorElem[idx];
}

template <typename ElemType>
MyVector<ElemType>& MyVector<ElemType>::operator=(const MyVector<ElemType> &other){
	//delete[] this;
	_size = other._size;
	_capacity = other._capacity;
	
	vectorElem = new ElemType[_capacity];
	for (size_t i = 0; i < _size; ++i)
	{
		vectorElem[i] = other.vectorElem[i];
		
	}
	//vectorElem = other.vectorElem;
	return *this;
}

template <typename ElemType>
size_t MyVector<ElemType>::capacity() const{
	return _capacity;
}

template <typename ElemType>
size_t MyVector<ElemType>::size() const{
	return _size;
}

template <typename ElemType>
void MyVector<ElemType>::reserve(size_t n){
	if (n < _size)
	{
	    cout << "invalue" << endl;
    }
	else
	{
		ElemType *oldVectors = vectorElem;
		vectorElem = new ElemType[n];
		
		for (size_t i = 0; i < _size; ++i){
			vectorElem[i] = oldVectors[i];
		}	    		
		_capacity = n;
		delete[] oldVectors;
	}
}

template <typename ElemType>
bool MyVector<ElemType>::isEmpty(){
	if (_size == 0)
	{
		cout << "the vector is empty" << endl;
		return true;
	}		
	else
	{
		cout << "the vector is not empty" << endl;
		return false;
	}
}

template <typename ElemType>
void MyVector<ElemType>::pushBack(const ElemType& ele){
	if (_size >= _capacity){
		//cout << "the room is not enough!" << endl;
		size_t newcapacity = 2 * _size;
		reserve(newcapacity);
	}	
	vectorElem[_size] = ele;
	++ _size;
	
		
}

template <typename ElemType>
void MyVector<ElemType>::popBack(){
	if (_size <= 0){

		cout << "there is no elements in the vector!" << endl;
	}
	else
	{
		-- _size;
	}
	//return vectorElem[_size];
}

template <typename ElemType>
//index caculate from 0
void MyVector<ElemType>::insert(size_t index, ElemType &ele){
	if (index > _size+1)
	{
		cout << "invaild index!" << endl;
	}
	else
	{
		if (_size==_capacity)
		{
			//cout << "Please reserve the vector!";
			reserve(2 * _size);
		}
		
		for (size_t i = _size; i >= index; --i)
		{
			vectorElem[i + 1] = vectorElem[i];
		}
		vectorElem[index] = ele;
		++ _size;
		
	}

}

template <typename ElemType>
void MyVector<ElemType>::insertByIterator(iterator position, ElemType &ele){
	//? why size_t = MyVector<ElemType> - MyVector<Ele,Type>
	size_t index = position - begin();
	cout << "the index is:" << index << endl;
	insert(index, ele);

}

template <typename ElemType>
//index caculate from 0
void MyVector<ElemType>::erase(size_t index){
	if (index >= _size || index < 0)
	{
		cout << "invaild index!" << endl;
	}
	else
	{
		for (size_t i = index; i < _size-1; ++i)
		{
			vectorElem[i] = vectorElem[i + 1];
		}
		-- _size;
	}

}

template <typename ElemType>
void MyVector<ElemType>::eraseByIterator(iterator position){
	size_t index = position - begin();
	erase(index);
}

int _tmain(int argc, _TCHAR* argv[]){
	
	MyVector<size_t> myVector(99,2);
	MyVector<size_t> anotherVector(0);
	MyVector<size_t>::iterator itr;

	cout << myVector.capacity() << endl;
	cout << myVector.begin() << endl;
	myVector.reserve(20);
	
	myVector.isEmpty();
	myVector.pushBack(11);
	myVector.pushBack(22);
	myVector.pushBack(33);
	myVector.pushBack(44);	

	size_t value = 333;
	myVector.insert(6, value);

	itr = myVector.begin() + 3;
	myVector.insertByIterator(itr, value);
   
	myVector.erase(7);

	anotherVector = myVector;
	for (size_t i = 0; i < myVector.size(); ++i){
		cout << myVector[i] << endl;
		//cout << anotherVector[i] << endl;
	}
		
	cout << "the size before pop:" << myVector.size() << endl;
	myVector.popBack();
	cout << "the size after pop:" << myVector.size() << endl;
	//cout << "popback once:" << myVector.popBack() << endl;   
	

	MyVector<int> vec(0);
	
	for (int i = 0; i < 100; ++i){
		vec.pushBack(i);
	}
	cout << vec[0] <<" "<<vec[99] << endl;
	cin.get();
	return 0;
}

