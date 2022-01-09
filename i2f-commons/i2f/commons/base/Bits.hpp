#ifndef _I2F_BITS_H_
#define _I2F_BITS_H_

template<typename T>
class Bits
{
public:
	virtual ~Bits(){}
	/*
	强制取数据的Bit位,
	需要保证是无符号数传进来才能保证数据的可靠返回
	needKeep将会保留取数据的位置，不会自动归小到0Bit位
	*/
	T getBitData(T data, int beginBit, int endBit, bool needKeep);
	/*
	设置数据的Bit位，
	isAligned表示数据setData是否已经在替换位置，否则将会移动到指定Bit后再位置使用
	*/
	T setBitData(T data, int beginBit, int endBit, T setData, bool isAligned);

	/*
	获取bitCount位的掩码
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