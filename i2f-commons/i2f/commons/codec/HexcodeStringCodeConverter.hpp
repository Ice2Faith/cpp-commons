#ifndef _I2F_HEXCODE_STRING_CODE_CONVERTER_H_
#define _I2F_HEXCODE_STRING_CODE_CONVERTER_H_
#include"IStringCodeConverter.hpp"

/*
针对HexCode进行转换
0x56,0x34
一个0x认为是一个字符
因此不是严格的1字节的0x,对于中文则可能是0xa256
*/
template<typename T>
class HexcodeStringCodeConverter : virtual public IStringCodeConverter<T>
{
public:
	HexcodeStringCodeConverter(){}
	virtual ~HexcodeStringCodeConverter(){}
	virtual TString<T> stringOf(TString<T> str);
	virtual TString<T> stringTo(TString<T> str);
	
};

template<typename T>
TString<T> HexcodeStringCodeConverter<T>::stringOf(TString<T> str)
{
	TString<T> ret;
	int i=0;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		if(pch==',' || i==0)
		{
			if (i != 0){
				i++;
			}
			if(str.charAt(i)=='0'){
				i++;
				if(str.charAt(i)=='x' || str.charAt(i)=='X'){
					i++;
					T sch=0;
					while(str.charAt(i)!=',')
					{
						T uch = str.charAt(i);
						if(uch==0){
							break;
						}
						int val=0;
						if(uch>='0' && uch<='9')
						{
							val=uch-'0';
						}else if(uch>='a' && uch<='z'){
							val=(uch-'a')+10;
						}else if(uch>='A' && uch<='Z'){
							val=(uch-'A')+10;
						}
						sch*=16;
						sch+=val;
						i++;
					}
					ret.appendChar(sch);
				}
			}else{
				i++;
			}
		}else{
			i++;
		}
	}
	return ret;
}

template<typename T>
TString<T> HexcodeStringCodeConverter<T>::stringTo(TString<T> str)
{
	TString<T> ret;
	T buf[12];
	int i=0;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		ret.appendChar((T)'0');
		ret.append((T)'x');
		int j=0;
		while(pch!=0){
			int val=pch&0xf;
			T sch='0';
			if(val<10){
				sch=(T)('0'+val);
			}else{
				sch=(T)('A'+(val-10));
			}
			buf[j]=sch;
			j++;
			pch >>= 4;
		}
		for(int k=j-1;k>=0;k--){
			ret.appendChar(buf[k]);
		}
		ret.append((T)',');
		i++;
	}
	return ret;
}

#endif // _I2F_HEXCODE_STRING_CODE_CONVERTER_H_

