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
	size_t theSize;     // theSize 这种命名方法不好，推荐 mSize m_size 或者 _size
	size_t theCapacity;
	ElemType *vectors;  // vectors? 为什么是这个名字？这里保存了很多vector么？

public:
	//??
	typedef MyVector<ElemType>* iterator;       // 这个根本不对。 typedef ElemType* iterator 还差不多。
	typedef const MyVector<ElemType>* const_iterator;

    // iterator是指针的泛化结果(个人理解)。也就是一种比指针更通用的东西。例如在链表里，iterator就是node。
    // 一般情况下,iterator支持的东西包括:
    //    ++ iterator; 取下一个元素的iterator
    //    -- iterator; 取上一个元素的iterator
    //    * iterator; 取当前元素的引用
    //    iterator + N; 取下N个元素的iterator
    // 这个是C++风格的iterator，如果你想实现java风格的也可以。其实类似。

	MyVector(); // 在哪定义这个函数了？
	MyVector(size_t capactity);
	MyVector(const ElemType& ele, size_t n);


	MyVector(const MyVector<ElemType>& other);// 在哪定义这个函数了？
	~MyVector(); // 析构函数加virtual

	ElemType& operator[](const size_t idx);
	// const ElemType& operator[](const size_t idx) const; // 这个函数也要实现。要不然我在const环境里就获得不到这个Vector的元素了。

	MyVector<ElemType> & operator=(const MyVector<ElemType>& other);
	size_t capacity(); // const， 这个函数是const的!!!
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
	theSize = size; // 这行不对。。。
	theCapacity = 2 * theSize + 1; // 这行也不对。C++的函数初始化，最好写在列表里。我注释掉这里，写一个和你一样的实现
	vectors = new ElemType[theCapacity];
}
*/
template <typename ElemType>
MyVector<ElemType>::MyVector(size_t sz) // 这么实现，和你的写法一样。但是效率更高，更C++。另外，这么实现的逻辑也不对。。一般输入的是capacity，不是size
    :theSize(sz), theCapacity(sz<<1+1), vectors(new ElemType[sz<<1+1])
{}

template <typename ElemType>
MyVector<ElemType>::MyVector(const ElemType& ele, size_t n) // 和上个构造函数一样。这么写不对。
{
	theSize = n;
	theCapacity = 2 * theSize + 1;
	vectors = new ElemType[theCapacity];
	for (size_t i = 0; i < theSize; i++) // ++i , 不是i++
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
	for (size_t i = 0; i < theSize; i++) // ++i , 不是i++
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

		for (size_t i = 0; i < theSize; i++){  // ++i , 不是i++
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
//		cout << "the vector is empty" << endl;  // 为什么有输出？
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

		vectors[theSize] = ele;  // 这是什么缩进？？？？
		theSize++; // ++theSize; 不是theSize++;


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
//index caculate from 0  // 注释不是写在这里的。。你这行注释把上下两个相关的语义给分开了。
void MyVector<ElemType>::insert(size_t index, ElemType &ele)  // 不要混用代码风格。你这个括号风格在这个cpp里有好几种。
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

		for (size_t i = theSize; i >= index; i--) // ++i , 不是i++
		{
			vectors[i + 1] = vectors[i];
		}
		vectors[index] = ele;
		theSize++; // ++i , 不是i++

	}

}

template <typename ElemType>
void MyVector<ElemType>::insertByIterator(iterator position, ElemType &ele)
{
	//? why size_t = MyVector<ElemType> - MyVector<Ele,Type>
	size_t index = position - begin();  // 由于你的iterator定义的就不对。所以这根本就是错的。
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
//        MyVector<int> vec;  // 这个编译不过，你没定义这个构造函数
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

