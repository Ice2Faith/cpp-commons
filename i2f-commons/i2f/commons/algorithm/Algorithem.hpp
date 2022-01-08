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
#include"../container/LinkList.hpp"
#include"../math/Math.h"
#include"../interface/IExecutor.h"

template<typename T>
class AlgoElem
{
public:
	/*
	交换元素
	*/
	void swapElem(IRandomAccessor<T>& data, int i, int j);
	void eachElem(IReadRandomAccessor<T>& data, int from, int count,IExecutor<T>& exec);
	bool isIn(T target, IReadRandomAccessor<T>& data, int from, int count, IExEquals<T> eqer);
	bool isIn(T target, int count, IExEquals<T> eqer, T data, ...);
	int countElem(T target, IReadRandomAccessor<T>& data, int from, int count, IExEquals<T> eqer);
};


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
	int quickNext(IRandomAccessor<T>& data, int head, int end, IComparator<T>& comp, bool asc);
	//将start-mid和mid-end两段有序数据合并为一个完整有序的数据
	void merge(IRandomAccessor<T>& srcData, int start, int mid, int end, IRandomAccessor<T>& drtData, IComparator<T>& comp, bool asc);
	void heapAdjust(IRandomAccessor<T>& data, int pIndex, int size, IComparator<T>& comp, bool asc);
public:
	/*
	选择排序
	把整个分成两部分，前半部分是排序好的，后半部分是乱序的
	首先前半部分没有数据，当然有序
	然后每次从后半部分找一个最小的放到前半部分的最后一个位置，
	也就是说，后半部分的第一个数据和后半部分的最小数据交换
	*/
	void selectSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	冒泡排序
	每次都比较相邻的两个数据，如果大小顺序不一样就调换
	那么一次扫描就能将一个数据放到最后面（假设升序排序）
	这样大的数据不断往后面冒，后面已经冒了的部分就已经有序了（可以不用冒了）
	*/
	void bubbleSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	插入排序
	从第一个数据开始，这个时候，第一个数据及之前的数据都是有序的，毕竟就一个数据
	然后，一次从后面拿一个数据，插入到前面有序的数据对应的位置，因此会设计到移动数据（插入导致的）
	*/
	void insertSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	快速排序
	每次递归，不断将区间一分为二，同时得到定位的数据的位置，这个位置将不会再改变
	直到递归区间为1为止，也就是开始下标》=结束下标
	*/
	void quickSort(IRandomAccessor<T>& data, int headIndex, int endIndex, IComparator<T>& comp, bool asc);
	/*
	二路归并排序
	把相邻的两个有序划分区域进行合并成为一个有序区域，直到划分区域大小达到最大排序大小
	那么，当划分区域一开始为1时，一个数据是绝对有序的
	那么一次翻倍区间大小进行归并即可
	*/
	void mergeSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	堆排序
	*/
	void heapSort(IRandomAccessor<T>& data,int size,IComparator<T>& comp,bool asc);
};

template<typename T>
class AlgoOrder
{
public:
	/*
	翻转顺序
	*/
	void reverseOrder(IRandomAccessor<T>& data, int startIndex, int endIndex);
	/*
	打乱顺序
	*/
	void shuffleOrder(IRandomAccessor<T>& data, int startIndex, int endIndex);
};


template<typename T>
void AlgoOrder<T>::reverseOrder(IRandomAccessor<T>& data, int startIndex, int endIndex)
{
	AlgoElem<T> algo;
	while (startIndex < endIndex)
	{
		algo.swapElem(data, startIndex, endIndex);
		startIndex++;
		endIndex--;
	}
}

template<typename T>
void AlgoOrder<T>::shuffleOrder(IRandomAccessor<T>& data, int startIndex, int endIndex)
{
	int count = endIndex - startIndex + 1;
	if (count>2)
		count = Math::randInt(count / 2) + (count / 2);
	int i = 0;
	AlgoElem<T> algo;
	while (i<count)
	{
		int bindex = rand() % count + startIndex;
		int eindex = rand() % count + startIndex;
		if (bindex != eindex){
			algo.swapElem(data, bindex, eindex);
		}
		i++;
	}
}

template<typename T>
void AlgoSort<T>::selectSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc)
{
	AlgoElem<T> algo;
	int minIndex = 0;
	for (int i = 0; i < size; i++)
	{
		minIndex = i; //假设目前最小数据就是后半部分的第一个
		for (int j = i; j < size; j++)
		{
			if ((comp.compare(data.get(j),data.get(minIndex)) < 0) == asc)//扫描后半部分，得到真正最小的数据
			{
				minIndex = j;
			}
		}
		//交换最小和后半部分第一个数据
		algo.swapElem(data, minIndex, i);
	}
}

template<typename T>
void AlgoSort<T>::bubbleSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc)
{
	if (size <= 1)
		return;
	AlgoElem<T> algo;
	for (int i = 0; i < size; i++)
	{
		//判断是否发生了交换，一遍结束，没有发生交换，那就已经有序了
		bool swap = false;
		for (int j = 0; j < size - 1 - i; j++)//前面说过，一次就能得到一个最大的，因此-i就能避免把排序好的再排，这个没必要
		{
			if ((comp.compare(data.get(j),data.get(j+1)) >0) == asc)//相邻的大小不满足就交换
			{
				algo.swapElem(data, j, j + 1);
				swap = true;
			}
		}
		if (swap == false)
		{
			break;
		}
	}
}

template<typename T>
void AlgoSort<T>::insertSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc)
{
	if (size <= 1)
		return;
	//总体循环一遍
	for (int i = 1; i < size; i++)
	{
		//去有序的部分找现在的这个数据该放置的位置
		for (int j = 0; j < i; j++)
		{
			if ((comp.compare(data.get(i),data.get(j)) <0) == asc)
			{
				//找到位置之后，把前面的数据挪向后一个位置
				T ti = data.get(i);
				for (int k = i; k >j; k--)
				{
					data.set(k, data.get(k - 1));
				}
				//将数据插入
				data.set(j, ti);
				break;
			}
		}
	}
}

template<typename T>
void AlgoSort<T>::quickSort(IRandomAccessor<T>& data, int headIndex, int endIndex, IComparator<T>& comp, bool asc)
{
#if 0	//这里不使用递归，否则数据量过多会栈溢出，这里使用队列+循环进行处理，如果需要使用递归处理，请将这里的0改为非0值
	//开始下标小于结束小标就没结束
	if (headIndex < endIndex)
	{
		//定位一个数据的位置
		int mid = this->quickNext(data, headIndex, endIndex, comp, asc);
		//按照定位数据位置的两端进行递归定位
		if ((mid-1)>=headIndex && (mid-1)<=endIndex)
			this->quickSort(data, headIndex, mid - 1, comp, asc);
		if ((mid+1)>=headIndex && (mid+1)<=endIndex)
			this->quickSort(data, mid + 1, endIndex, comp, asc);
	}
	/*
	使用递归排序1万数据已经栈溢出

	非递归效率
	listSize:10000
	shuffle time:0
	shuffled
	:1103 533 2 3422 1912 955 141 2937 3821 63 3969 4046 4734 2446 2331 733 16 1269 4648 4237
	sort time:74
	sorted
	:0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
	reverse time:0
	reversed
	:9999 9998 9997 9996 9995 9994 9993 9992 9991 9990 9989 9988 9987 9986 9985 9984 9983 9982 9981 9980
	*/
#else
	LinkList<int> lstQue;
	lstQue.enque(headIndex);
	lstQue.enque(endIndex);
	while (lstQue.size()>0)
	{
		int head=lstQue.deque();
		int end=lstQue.deque();
		//定位一个数据的位置
		int mid = this->quickNext(data, head, end, comp, asc);
		//按照定位数据位置的两端进行递归定位
		if ((mid-1)>=head && (mid-1)<=end)
		{
			lstQue.enque(head);
			lstQue.enque(mid - 1);
		}
		if ((mid+1)>=head && (mid+1)<=end)
		{
			lstQue.enque(mid + 1);
			lstQue.enque(end);
		}
	}
#endif
}

template<typename T>
int AlgoSort<T>::quickNext(IRandomAccessor<T>& data, int head, int end, IComparator<T>& comp, bool asc)
{
	int i = head, j = end;
	//保存开始下标数据，因为不采用交换的方式，找到之后就覆盖上一次的脚步，最后把现在保存的覆盖最后一个脚印，那就是完整数据
	T phead = data.get(head);
	//分别从左右两个方向，将大于和小于开始数据的数据不断放置两边，一次结束之后，最后的位置就是开始位置的真正位置
	//这样一次循环结束，就把数据分为大于的一半和小于的一半
	do
	{
		//向左找大于的（第一个）
		while (i < j && (comp.compare(data.get(j),phead)>= 0) == asc)
			j--;
		if (i < j)
		{
			data.set(i, data.get(j));
			i++;
		}
		//向右找小于的
		while (i < j && (comp.compare(data.get(i),phead) <= 0) == asc)
			i++;
		if (i < j)
		{
			data.set(j, data.get(i));
			j--;
		}
	} while (i<j);
	data.set(j, phead);
	return i;
}

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
	AlgoElem<T> algo;
	for (int i = size - 1; i > 0; i--)
	{
		algo.swapElem(data,0, i);
		this->heapAdjust(data, 0, i, comp,  asc);
	}
}

template<typename T>
void AlgoSort<T>::heapAdjust(IRandomAccessor<T>& data,int pIndex, int size, IComparator<T>& comp, bool asc)
{
	AlgoElem<T> algo;
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
			algo.swapElem(data, pIndex, j);
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

template<typename T>
int AlgoElem<T>::countElem(T target, IReadRandomAccessor<T>& data, int from, int count, IExEquals<T> eqer)
{
	int ret = 0;
	int size = data.size();
	for (int i = 0; i < count && (from + i) < size; i++){
		if (eqer.equal(target, data.get(i))){
			ret++;
		}
	}
	return ret;
}

template<typename T>
bool AlgoElem<T>::isIn(T target, IReadRandomAccessor<T>& data, int from, int count, IExEquals<T> eqer)
{
	int size = data.size();
	for (int i = 0; i < count && (from + i) < size; i++){
		if (eqer.equal(target, data.get(i))){
			return true;
		}
	}
	return false;
}

template<typename T>
bool AlgoElem<T>::isIn(T target, int count, IExEquals<T> eqer, T data, ...)
{
	va_list varList;
	va_start(varList, data);
	//需要注意，这是第一个参数data的位置，后面第一次调用va_arg，就已经指向下一个参数了
	//处理不当就会导致第一个参数取不到
	//因此解决方法有两种，第一种就是我这种方案，第一个参数独立处理，第二种就是va_start的参数取向前一个cmp
	T arg = data;
	bool ret = false;
	int i = 0;
	while (i<count)
	{
		if (eqer.equal(target,arg))
		{
			ret = true;
			break;
		}
		arg = va_arg(varList, T);
		i++;
	}
	va_end(varList);
	return ret;
}

template<typename T>
void AlgoElem<T>::eachElem(IReadRandomAccessor<T>& data, int from, int count, IExecutor<T>& exec)
{
	int size = data.size();
	for (int i = 0; i < count && (i + form) < size; i++){
		exec.execute(data.get(from + i));
	}
}

template<typename T>
void AlgoElem<T>::swapElem(IRandomAccessor<T>& data, int i, int j)
{
	T tmp = data.get(i);
	data.set(i, data.get(j));
	data.set(j, tmp);
}


#endif // _I2F_ALGORITHEM_H_
