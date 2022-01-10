#ifndef _I2F_URI_BYTE_DATA_CONVERTER_H_
#define _I2F_URI_BYTE_DATA_CONVERTER_H_
#include"IDataConverter.hpp"
#include"../base/String.hpp"
#include"../container/Array.hpp"
#include"../container/ArrayList.hpp"

template<typename T>
class UriByteDataConverter : virtual public IDataConverter<T>
{
public:
	virtual ~UriByteDataConverter(){}
	Array<byte> dataOf(TString<T> str);
	TString<T> dataTo(Array<byte> data);
};

template<typename T>
Array<byte> UriByteDataConverter<T>::dataOf(TString<T> str)
{
	int i=0;
	ArrayList<byte> list;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		if(pch=='%')
		{
			i++;
			byte sbt=0;
			for(int j=0;j<2;j++,i++)
			{
				T uch=str.charAt(i);
				if(uch=='%' || uch==0)
				{
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
			byte sbt=(byte)(pch&0xff);
			list.add(sbt);
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
TString<T> UriByteDataConverter<T>::dataTo(Array<byte> data)
{
	TString<T> ret;
	int i=0;
	while(i<data.size())
	{
		byte pbt=data[i++];
		if(pbt>='a'&& pbt<='z')
		{
			ret.appendChar((T)pbt);
		}else if(pbt>='A' && pbt<='Z')
		{
			ret.appendChar((T)pbt);
		}else if(pbt=='/' || pbt=='?' || pbt=='&' || pbt=='='){
			ret.appendChar((T)pbt);
		}else{
			ret.appendChar((T)'%');
			for(int i=0;i<2;i++){
				T sch=(T)((pbt>>(4*(i-1)))&0xff);
				ret.appendChar(sch);
			}
		}
	}
	return ret;
}


#endif // _I2F_HEX_BYTE_DATA_CONVERTER_H_
