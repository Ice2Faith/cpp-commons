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
	���ݱȽ��㷨
	�Ƚ�����������ʵ�������Դstr1��str2��low��height�����Ƿ���ȫ��ȣ�ʹ�õ�ֵ�Ƚ���eqer��
	����㷨ǰ����str1��str2Ӧ�ö�����low��height���������
	ԭ��
	ʹ�ù鲢�㷨��˼�룬ÿ��̽��low,mid,height�Ƿ����
	��һ���ݹ���ֱ�̽��low+1��mid-1,mid+1��height-1����
	��ȱ�㣺
	���ַ�ʽ���˳��Ƚ�������ӿ��٣����������������ֲ���˳��
	����ڶ���Ԫ�ز�ͬ
	*/
	bool fastEqual(IReadRandomAccessor<T>& str1, IReadRandomAccessor<T>& str2, IExEquals<T>& eqer, int low, int height);
	bool fastEqualArray(T* str1, T* str2, int low, int height);
};

template<typename T>
class AlgoFind
{
public:
	/*
	˳�����
	*/
	int orderFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height, bool reverse);
	/*
	���ֲ���
	ÿ�ν����������һ�룬
	����Ҫ�󱻲���������
	*/
	int halfFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height);
	int halfFindArray(T* data, T target, int low, int height);
	/*
	쳲���������--�ƽ�ָ����
	ÿ�ν����������һ�룬
	����Ҫ�󱻲���������
	*/
	int fibonacciFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height);
};

template<typename T>
class AlgoNumberFind
{
public:
	/*
	��ֵ����
	����������Ԫ��֧�����㣺�������������Ը��������õ�������
	��ô�Ϳ���ʹ�ñ������㷨

	����Ͳ�����

	���㷨���C�����еĻ����������;���Ч��int short byte long double float ...
	*/
	int insertFind(IReadRandomAccessor<T>& data, IComparator<T>& comp, T target, int low, int height);
};

template<typename T>
class AlgoSort
{
protected:
	void heapAdjust(IRandomAccessor<T>& data, int pIndex, int size, IComparator<T>& comp, bool asc);
	//��start-mid��mid-end�����������ݺϲ�Ϊһ���������������
	void merge(IRandomAccessor<T>& srcData, int start, int mid, int end, IRandomAccessor<T>& drtData, IComparator<T>& comp, bool asc);
public:
	/*
	������
	*/
	void heapSort(IRandomAccessor<T>& data,int size,IComparator<T>& comp,bool asc);
	/*
	��·�鲢����
	�����ڵ��������򻮷�������кϲ���Ϊһ����������ֱ�����������С�ﵽ��������С
	��ô������������һ��ʼΪ1ʱ��һ�������Ǿ��������
	��ôһ�η��������С���й鲢����
	*/
	void mergeSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
};

template<typename T>
void AlgoSort<T>::mergeSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc)
{
	//��ʼ����һ���ݹ鲢����������
	int len = 1;
	T * buff = new T[size];//��֤�ռ���2n��С�������������·�鲢����Ҫ��
	//size-1 �������ݣ������±���й鲢
	int maxIndex = size - 1;

	IRandomAccessor<T>& buf=ArrayRandomAccessor<T>(buff,size);

	IRandomAccessor<T>* src = &data;
	IRandomAccessor<T>* drt = &buf;
	while (len < size)//ֱ��ÿ�εĹ鲢���ȴﵽ�ܳ���Ҳ�͹鲢���
	{
		//���ι鲢����һ�δ�Դ���ݵ����棬�ڶ��λ������
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
			//���ι鲢ÿ������������
			int j = 0;
			while (j + 2 * len < size)
			{
				this->merge(*src, j, j + len - 1, j + 2 * len - 1, *drt, comp, asc);
				j += 2 * len;
			}
			//�鲢ʣ��Ĳ��ȳ�����������
			if (j + len < size)
			{
				this->merge(*src, j, j + len - 1, maxIndex, *drt, comp, asc);
			}
			else
			{
				//����ʣ��ռ�
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
	//�������ݣ�ֱ�������κ�һ�ν���
	while (i <= mid && j <= end)
	{
		//�Ƚ����ݣ�˭С˭����
		if ((comp.compare(srcData.get(i),srcData.get(j)) < 0) == asc)
		{
			drtData.set(k++, srcData.get(i++));
		}
		else
		{
			drtData.set(k++,srcData.get(j++));
		}
	}
	//��ʣ�����һ�ε����ݸ��ƹ�ȥ
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
		//쳲��������ң���Ϊ0.5����Ϊ0.618������//mid=low+0.618*(height-low);
		//��ֵ���ң������������������͵Ĳ��ң�Ҳ���Ǹ��ݲ���ֵ�Ĵ��±������𽥱ƽ����в��ң������м�ֵλ��=���λ��+Ԥ��λ�ñ���*�ܳ���//mid=low+	((target-selGet(data,low))/(selGet(data,height)-selGet(data,low)))	*(height-low);
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
		//쳲��������ң��ֳ�Ϊ�ƽ�ָ���ң���Ϊ0.5����Ϊ0.618������//mid=low+0.618*(height-low);
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
		//��ֵ���ң������������������͵Ĳ��ң�Ҳ���Ǹ��ݲ���ֵ�Ĵ��±������𽥱ƽ����в��ң������м�ֵλ��=���λ��+Ԥ��λ�ñ���*�ܳ���
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
