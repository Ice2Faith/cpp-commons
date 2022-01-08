#ifndef _I2F_BITS_H_
#define _I2F_BITS_H_

template<typename T>
class Bits
{
public:
	virtual ~Bits(){}
	/*
	ǿ��ȡ���ݵ�Bitλ,
	��Ҫ��֤���޷��������������ܱ�֤���ݵĿɿ�����
	needKeep���ᱣ��ȡ���ݵ�λ�ã������Զ���С��0Bitλ
	*/
	T getBitData(T data, int beginBit, int endBit, bool needKeep);
	/*
	�������ݵ�Bitλ��
	isAligned��ʾ����setData�Ƿ��Ѿ����滻λ�ã����򽫻��ƶ���ָ��Bit����λ��ʹ��
	*/
	T setBitData(T data, int beginBit, int endBit, T setData, bool isAligned);

	/*
	��ȡbitCountλ������
	*/
	T getBitMask(int bitCount);
	
};

template<typename T>
T Bits<T>::getBitMask(int bitCount)
{
	T mask = 0;
	for (int i = 0; i < bitCount; i++){
		mask <<= 1;
		mask |= 1;
	}
	return mask;
}

template<typename T>
T Bits<T>::getBitData(T data, int beginBit, int endBit, bool needKeep)
{
	int db = endBit - beginBit + 1;
	T tp = 0;
	for (int i = 0; i < db; i++)
	{
		tp = (tp << 1) | 1;
	}
	tp = tp << beginBit;
	if (needKeep)
		return (T)(data&tp);
	return (T)((data&tp) >> beginBit);
}

template<typename T>
T Bits<T>::setBitData(T data, int beginBit, int endBit, T setData, bool isAligned)
{
	T tpv = 0, tpf = 0;
	int bitCount = sizeof(T)* 8;
	for (int i = bitCount - 1; i >= 0; i--)
	{
		if (i >= beginBit && i <= endBit)
		{
			tpv = (tpv << 1) | 0;
			tpf = (tpf << 1) | 1;
		}
		else
		{
			tpv = (tpv << 1) | 1;
			tpf = (tpf << 1) | 0;
		}
	}
	T td = tpv&data;
	T sd = isAligned ? setData : (setData << beginBit);
	sd = sd&tpf;
	return (T)(td | sd);
}

#endif // _I2F_BITS_H_