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
	����Ԫ��
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
	int quickNext(IRandomAccessor<T>& data, int head, int end, IComparator<T>& comp, bool asc);
	//��start-mid��mid-end�����������ݺϲ�Ϊһ���������������
	void merge(IRandomAccessor<T>& srcData, int start, int mid, int end, IRandomAccessor<T>& drtData, IComparator<T>& comp, bool asc);
	void heapAdjust(IRandomAccessor<T>& data, int pIndex, int size, IComparator<T>& comp, bool asc);
public:
	/*
	ѡ������
	�������ֳ������֣�ǰ�벿��������õģ���벿���������
	����ǰ�벿��û�����ݣ���Ȼ����
	Ȼ��ÿ�δӺ�벿����һ����С�ķŵ�ǰ�벿�ֵ����һ��λ�ã�
	Ҳ����˵����벿�ֵĵ�һ�����ݺͺ�벿�ֵ���С���ݽ���
	*/
	void selectSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	ð������
	ÿ�ζ��Ƚ����ڵ��������ݣ������С˳��һ���͵���
	��ôһ��ɨ����ܽ�һ�����ݷŵ�����棨������������
	����������ݲ���������ð�������Ѿ�ð�˵Ĳ��־��Ѿ������ˣ����Բ���ð�ˣ�
	*/
	void bubbleSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	��������
	�ӵ�һ�����ݿ�ʼ�����ʱ�򣬵�һ�����ݼ�֮ǰ�����ݶ�������ģ��Ͼ���һ������
	Ȼ��һ�δӺ�����һ�����ݣ����뵽ǰ����������ݶ�Ӧ��λ�ã���˻���Ƶ��ƶ����ݣ����뵼�µģ�
	*/
	void insertSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	��������
	ÿ�εݹ飬���Ͻ�����һ��Ϊ����ͬʱ�õ���λ�����ݵ�λ�ã����λ�ý������ٸı�
	ֱ���ݹ�����Ϊ1Ϊֹ��Ҳ���ǿ�ʼ�±꡷=�����±�
	*/
	void quickSort(IRandomAccessor<T>& data, int headIndex, int endIndex, IComparator<T>& comp, bool asc);
	/*
	��·�鲢����
	�����ڵ��������򻮷�������кϲ���Ϊһ����������ֱ�����������С�ﵽ��������С
	��ô������������һ��ʼΪ1ʱ��һ�������Ǿ��������
	��ôһ�η��������С���й鲢����
	*/
	void mergeSort(IRandomAccessor<T>& data, int size, IComparator<T>& comp, bool asc);
	/*
	������
	*/
	void heapSort(IRandomAccessor<T>& data,int size,IComparator<T>& comp,bool asc);
};

template<typename T>
class AlgoOrder
{
public:
	/*
	��ת˳��
	*/
	void reverseOrder(IRandomAccessor<T>& data, int startIndex, int endIndex);
	/*
	����˳��
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
		minIndex = i; //����Ŀǰ��С���ݾ��Ǻ�벿�ֵĵ�һ��
		for (int j = i; j < size; j++)
		{
			if ((comp.compare(data.get(j),data.get(minIndex)) < 0) == asc)//ɨ���벿�֣��õ�������С������
			{
				minIndex = j;
			}
		}
		//������С�ͺ�벿�ֵ�һ������
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
		//�ж��Ƿ����˽�����һ�������û�з����������Ǿ��Ѿ�������
		bool swap = false;
		for (int j = 0; j < size - 1 - i; j++)//ǰ��˵����һ�ξ��ܵõ�һ�����ģ����-i���ܱ��������õ����ţ����û��Ҫ
		{
			if ((comp.compare(data.get(j),data.get(j+1)) >0) == asc)//���ڵĴ�С������ͽ���
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
	//����ѭ��һ��
	for (int i = 1; i < size; i++)
	{
		//ȥ����Ĳ��������ڵ�������ݸ÷��õ�λ��
		for (int j = 0; j < i; j++)
		{
			if ((comp.compare(data.get(i),data.get(j)) <0) == asc)
			{
				//�ҵ�λ��֮�󣬰�ǰ�������Ų���һ��λ��
				T ti = data.get(i);
				for (int k = i; k >j; k--)
				{
					data.set(k, data.get(k - 1));
				}
				//�����ݲ���
				data.set(j, ti);
				break;
			}
		}
	}
}

template<typename T>
void AlgoSort<T>::quickSort(IRandomAccessor<T>& data, int headIndex, int endIndex, IComparator<T>& comp, bool asc)
{
#if 0	//���ﲻʹ�õݹ飬���������������ջ���������ʹ�ö���+ѭ�����д��������Ҫʹ�õݹ鴦���뽫�����0��Ϊ��0ֵ
	//��ʼ�±�С�ڽ���С���û����
	if (headIndex < endIndex)
	{
		//��λһ�����ݵ�λ��
		int mid = this->quickNext(data, headIndex, endIndex, comp, asc);
		//���ն�λ����λ�õ����˽��еݹ鶨λ
		if ((mid-1)>=headIndex && (mid-1)<=endIndex)
			this->quickSort(data, headIndex, mid - 1, comp, asc);
		if ((mid+1)>=headIndex && (mid+1)<=endIndex)
			this->quickSort(data, mid + 1, endIndex, comp, asc);
	}
	/*
	ʹ�õݹ�����1�������Ѿ�ջ���

	�ǵݹ�Ч��
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
		//��λһ�����ݵ�λ��
		int mid = this->quickNext(data, head, end, comp, asc);
		//���ն�λ����λ�õ����˽��еݹ鶨λ
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
	//���濪ʼ�±����ݣ���Ϊ�����ý����ķ�ʽ���ҵ�֮��͸�����һ�εĽŲ����������ڱ���ĸ������һ����ӡ���Ǿ�����������
	T phead = data.get(head);
	//�ֱ�������������򣬽����ں�С�ڿ�ʼ���ݵ����ݲ��Ϸ������ߣ�һ�ν���֮������λ�þ��ǿ�ʼλ�õ�����λ��
	//����һ��ѭ���������Ͱ����ݷ�Ϊ���ڵ�һ���С�ڵ�һ��
	do
	{
		//�����Ҵ��ڵģ���һ����
		while (i < j && (comp.compare(data.get(j),phead)>= 0) == asc)
			j--;
		if (i < j)
		{
			data.set(i, data.get(j));
			i++;
		}
		//������С�ڵ�
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
	//��Ҫע�⣬���ǵ�һ������data��λ�ã������һ�ε���va_arg�����Ѿ�ָ����һ��������
	//�������ͻᵼ�µ�һ������ȡ����
	//��˽�����������֣���һ�־��������ַ�������һ���������������ڶ��־���va_start�Ĳ���ȡ��ǰһ��cmp
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
