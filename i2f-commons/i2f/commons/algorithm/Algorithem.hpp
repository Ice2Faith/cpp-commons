#ifndef _I2F_ALGORITHEM_H_
#define _I2F_ALGORITHEM_H_
#include"../interface/IReadRandomAccessor.h"
#include"../interface/IExEquals.h"
#include"../interface/impl/DefaultExEquals.hpp"
#include"../interface/impl/ArrayReadRandomAccessor.hpp"
#include"../interface/IComparator.h"
#include"../interface/impl/DefaultComparator.hpp"
#include"../interface/IRandomAccessor.h"
#include"../interface/impl/ArrayRandomAccessor.h"

template<typename T>
class AlgoEqual
{
public:
	/*
	数据比较算法
	比较两个随机访问的数据来源str1和str2的low到height部分是否完全相等（使用等值比较器eqer）
	因此算法前提是str1与str2应该都具有low到height区间的数据
	原理：
	使用归并算法的思想，每次探测low,mid,height是否相等
	下一步递归则分别探测low+1到mid-1,mid+1到height-1区间
	优缺点：
	此种方式相对顺序比较总体更加快速，针对少量情况，表现不如顺序
	例如第二个元素不同
	*/
	bool fastEqual(IReadRandomAccessor<T>& str1, IReadRandomAccessor<T>& str2, IExEquals<T>& eqer, int low, int height);
	bool fastEqualArray(T* str1, T* str2, int low, int height);
};

template<typename T>
class AlgoFind
{
public:
	/*
	顺序查找
	*/
	int orderFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height, bool reverse);
	/*
	二分查找
	每次将查找域减少一半，
	但是要求被查找域有序
	*/
	int halfFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height);
	int halfFindArray(T* data, T target, int low, int height);
	/*
	斐波那契查找--黄金分割查找
	每次将查找域减少一半，
	但是要求被查找域有序
	*/
	int fibonacciFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height);
};

template<typename T>
class AlgoNumberFind
{
public:
	/*
	插值查找
	仅仅适用于元素支持运算：相减，相除，乘以浮点数，得到浮点数
	那么就可以使用本查找算法

	否则就不适用

	此算法针对C语言中的基本数据类型均有效：int short byte long double float ...
	*/
	int insertFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height);
};

template<typename T>
class AlgoSort
{
protected:
	void heapAdjust(IRandomAccessor<T>& data, int pIndex, int size, IComparator<T>& comp, bool asc);
	//将start-mid和mid-end两段有序数据合并为一个完整有序的数据
	void merge(IRandomAccessor<T>& srcData, int start, int mid, int end, IRandomAccessor<T>& drtData, IComparator<T>& comp, bool asc);
public:
	/*
	堆排序
	*/
	void heapSort(IRandomAccessor<T>& data,int size,IComparator<T>& comp,bool asc);
	/*
	二路归并排序
	把相邻的两个有序划分区域进行合并成为一个有序区域，直到划分区域大小达到最大排序大小
	那么，当划分区域一开始为1时，一个数据是绝对有序的
	那么一次翻倍区间大小进行归并即可
	*/
	void mergeSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
};

template<typename T>
void AlgoSort<T>::mergeSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc)
{
	//初始化单一数据归并，绝对有序
	int len = 1;
	T * buff = new T[size];//保证空间是2n大小，这样才满足二路归并基本要求
	//size-1 对齐数据，采用下标进行归并
	int maxIndex = size - 1;

	IRandomAccessor<T>& buf=ArrayRandomAccessor<T>(buff,size);

	IRandomAccessor<T>* src = &data;
	IRandomAccessor<T>* drt = &buf;
	while (len < size)//直到每次的归并长度达到总长度也就归并完毕
	{
		//两次归并，第一次从源数据到缓存，第二次缓存回来
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				src = &data;
				drt = &buf;
			}
			else
			{
				src = &buf;
				drt = &data;
			}
			//依次归并每个完整子区间
			int j = 0;
			while (j + 2 * len < size)
			{
				this->merge(*src, j, j + len - 1, j + 2 * len - 1, *drt, comp, asc);
				j += 2 * len;
			}
			//归并剩余的不等长不完整区间
			if (j + len < size)
			{
				this->merge(*src, j, j + len - 1, maxIndex, *drt, comp, asc);
			}
			else
			{
				//拷贝剩余空间
				while (j < size)
				{
					(*drt).set(j, (*src).get(j));
					j++;
				}
			}

			len *= 2;
		}
	}
	delete[] buff;
}

template<typename T>
void AlgoSort<T>::merge(IRandomAccessor<T>& srcData, int start, int mid, int end, IRandomAccessor<T>& drtData, IComparator<T>& comp, bool asc)
{
	int i = start, j = mid + 1, k = start;
	//复制数据，直到其中任何一段结束
	while (i <= mid && j <= end)
	{
		//比较数据，谁小谁先来
		if ((comp.compare(srcData.get(i),srcData.get(j)) < 0) == asc)
		{
			drtData.set(k++, srcData.get(i++));
		}
		else
		{
			drtData.set(k++,srcData.get(j++));
		}
	}
	//把剩余的那一段的数据复制过去
	while (i <= mid)
	{
		drtData.set(k++,srcData.get(i++));
	}
	while (j <= end)
	{
		drtData.set(k++, srcData.get(j++));
	}
}

template<typename T>
void AlgoSort<T>::heapSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc)
{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		this->heapAdjust(data, i, size, comp, asc);
	}

	for (int i = size - 1; i > 0; i--)
	{
		T tmp = data.get(0);
		data.set(0, data.get(i));
		data.set(i, tmp);
		this->heapAdjust(data, 0, i, comp,  asc);
	}
}

template<typename T>
void AlgoSort<T>::heapAdjust(IRandomAccessor<T>& data,int pIndex, int size, IComparator<T>& comp, bool asc)
{
	int j = 0;
	while (2 * pIndex + 1 < size)
	{
		j = 2 * pIndex + 1;
		if (j + 1 < size)
		{
			if ((comp.compare(data.get(j),data.get(j+1)) < 0) == asc)
			{
				j++;
			}
		}
		if ((comp.compare(data.get(pIndex), data.get(j)) < 0) == asc)
		{
			T tmp = data.get(pIndex);
			data.set(pIndex, data.get(j));
			data.set(j, tmp);
			pIndex = j;
		}
		else
			break;
	}
}

template<typename T>
int AlgoFind<T>::orderFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height, bool reverse)
{
	E begin = low, end = height+1, step = 1;
	if (reverse == false)
	{
		begin = height;
		end = -1;
		step = -1;
	}
	for (; begin != end; begin += step)
	{
		if (comp.compare(data.get(begin),target) == 0)
		{
			return begin;
		}
	}
	return -1;
}

template<typename T>
int AlgoFind<T>::halfFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height)
{
	int size = height - low + 1;
	if (size <= 0)
		return -1;
	int mid=0;
	bool isUpSort = true;
	if (comp.compare(data.get(0), data.get(height)) > 0)
	{
		isUpSort = false;
	}
	while (low < height)
	{
		mid = (low + height) / 2;
		//斐波那契查找，改为0.5比例为0.618，即：//mid=low+0.618*(height-low);
		//插值查找，仅仅适用于数字类型的查找，也就是根据查找值的大致比例，逐渐逼近进行查找，即：中间值位置=最低位置+预估位置比例*总长度//mid=low+	((target-selGet(data,low))/(selGet(data,height)-selGet(data,low)))	*(height-low);
		T md = data.get(mid);
		if (comp.compare(md, target) == 0)
		{
			return mid;
		}
		if (comp.compare(md, target) < 0)
		{
			if (isUpSort)
				low = mid + 1;
			else
				height = mid;
		}
		else
		{
			if (isUpSort)
				height = mid;
			else
				low = mid + 1;
		}
	}
	return -1;
}

template<typename T>
int AlgoFind<T>::halfFindArray(T* data,T target, int low, int height)
{
	int size = height - low + 1;
	IReadRandomAccessor<T>& acs = ArrayReadRandomAccesor<T>(data, size);
	IComparator<T>& comp = DefaultComparator<T>();
	return this->halfFind(acs, comp, target, low, height);
}

template<typename T>
int AlgoFind<T>::fibonacciFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height)
{
	int size = height - low + 1;
	if (size <= 0)
		return -1;
	int mid = 0;
	bool isUpSort = true;
	if (comp.comapre(data.get(0),data.get(height)) > 0)
	{
		isUpSort = false;
	}
	bool isNag = false;
	while (low < height)
	{
		double rate = 0.61826;
		if (isNag)
		{
			rate = 1.0 - rate;
		}
		isNag = !isNag;

		mid = low + rate*(height - low);
		//斐波那契查找，又称为黄金分割查找，改为0.5比例为0.618，即：//mid=low+0.618*(height-low);
		T md = data.get(mid); 
		if (comp.compare(md, target) == 0)
		{
			return mid;
		}
		if (comp.compare(md, target) < 0)
		{
			if (isUpSort)
				low = mid + 1;
			else
				height = mid;
		}
		else
		{
			if (isUpSort)
				height = mid;
			else
				low = mid + 1;
		}
	}
	return -1;
}

template<typename T>
int AlgoNumberFind<T>::insertFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height)
{
	int size = height - low + 1;
	if (size <= 0)
		return -1;

	int mid = 0;
	bool isUpSort = true;
	if (comp.compare(data.get(0),data.get(height)) > 0)
	{
		isUpSort = false;
	}
	while (low < height)
	{
		double rate = ((target*1.0 - data.get(low)) / (data.get(height) -data.get(low)));
		if (rate<0.0 || rate>1.0)
			return -1;
		mid = low + rate*(height*1.0 - low);
		//插值查找，仅仅适用于数字类型的查找，也就是根据查找值的大致比例，逐渐逼近进行查找，即：中间值位置=最低位置+预估位置比例*总长度
		T md = data.get(mid);
		if (comp.compare(md, target) == 0)
		{
			return mid;
		}
		if (comp.compare(md, target) < 0)
		{
			if (isUpSort)
				low = mid + 1;
			else
				height = mid;
		}
		else
		{
			if (isUpSort)
				height = mid;
			else
				low = mid + 1;
		}
	}
	return -1;
}

template<typename T>
bool AlgoEqual<T>::fastEqual(IReadRandomAccessor<T>& str1, IReadRandomAccessor<T>& str2, IExEquals<T>& eqer, int low, int height)
{
	if (low > height){
		return true;
	}
	if (!eqer.equal(str1.get(low),str2.get(low))){
		return false;
	}
	if (low == height){
		return true;
	}
	if (!eqer.equal(str1.get(height), str2.get(height))){
		return false;
	}
	if ((height - low) == 1){
		return true;
	}
	int mid = (low + height) / 2;
	if (!eqer.equal(str1.get(mid), str2.get(mid))){
		return false;
	}
	if ((height - low) == 2){
		return true;
	}
	bool left = this->fastEqual(str1, str2, eqer, low + 1, mid - 1);
	if (!left){
		return false;
	}
	bool right = this->fastEqual(str1, str2, eqer, mid + 1, height - 1);
	if (!right){
		return false;
	}
	return true;
}

template<typename T>
bool AlgoEqual<T>::fastEqualArray(T* str1, T* str2, int low, int height){
	int size = height - low + 1;
	IReadRandomAccessor<T>& acs1 = ArrayReadRandomAccesor<T>(str1, size);
	IReadRandomAccessor<T>& acs2 = ArrayReadRandomAccesor<T>(str2, size);
	IExEquals<T>& eqer = DefaultExEquals<T>();
	return AlgoEqual<T>::fastEqual(acs1, acs2, eqer, low, height);
}

#endif // _I2F_ALGORITHEM_H_
