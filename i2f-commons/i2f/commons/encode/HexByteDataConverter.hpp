#ifndef _I2F_HEX_BYTE_DATA_CONVERTER_H_
#define _I2F_HEX_BYTE_DATA_CONVERTER_H_
#include"IDataConverter.hpp"
#include"../base/String.hpp"
#include"../container/Array.hpp"
#include"../container/ArrayList.hpp"

template<typename T>
class HexByteDataConverter : virtual public IDataConverter<T>
{
public:
	virtual ~HexByteDataConverter(){}
	Array<byte> dataOf(TString<T> str);
	TString<T> dataTo(Array<byte> data);
};

template<typename T>
Array<byte> HexByteDataConverter<T>::dataOf(TString<T> str)
{
	int i=0;
	ArrayList<byte> list;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		if(pch==',' || i==0){
			if(i!=0){
				i++;
			}
			if(str.charAt(i)=='0'){
				i++;
				if(str.charAt(i)=='x' || str.charAt(i)=='X'){
					i++;
					byte sbt=0;
					for(int k=0;k<2;k++,i++){
						T uch=str.charAt(i);
						if(uch==','||uch==0){
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
						sbt*=16;
						sbt+=val;
					}
					list.add(sbt);
				}else{
					i++;
				}
			}else{
				i++;
			}
		}else{
			i++;
		}
	}
	Array<byte> ret(list.size());
	for(int j=0;j<ret.size();j++)
	{
		ret[j]=list.get(j);
	}
	return ret;
}

template<typename T>
TString<T> HexByteDataConverter<T>::dataTo(Array<byte> data)
{
	TString<T> ret;
	int i=0;
	while(i<data.size())
	{
		byte pbt=data.get(i);
		if(i!=0){
			ret.appendChar((T)',');
		}
		ret.appendChar((T)'0');
		ret.appendChar((T)'x');
		for(int j=0;j<2;j++){
			int val=(pbt>>(4*(1-j)))&0xf;
			T sch='0';
			if(val<10){
				sch=(T)('0'+val);
			}else{
				sch=(T)('A'+(val-10));
			}
			ret.appendChar(sch);
		}
	}
	return ret;
}

#endif // _I2F_HEX_BYTE_DATA_CONVERTER_H_
