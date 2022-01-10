#ifndef _I2F_URICODE_STRING_CODE_CONVERTER_H_
#define _I2F_URICODE_STRING_CODE_CONVERTER_H_
#include"IStringCodeConverter.hpp"

/*
针对UriCode进行转换
%56%34
一个%认为是一个字符
因此不是严格的1字节的%,对于中文则可能是%a256
*/
template<typename T>
class UricodeStringCodeConverter : virtual public IStringCodeConverter<T>
{
public:
	UricodeStringCodeConverter(){}
	virtual ~UricodeStringCodeConverter(){}
	virtual TString<T> stringOf(TString<T> str);
	virtual TString<T> stringTo(TString<T> str);
	
};

template<typename T>
TString<T> UricodeStringCodeConverter<T>::stringOf(TString<T> str)
{
	TString<T> ret;
	int i=0;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		if(pch=='%'){
			i++;
			T sch=0;
			while(str.charAt(i)!='%'){
				T uch=str.charAt(i);
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
		}else{
			i++;
		}
	}
	return ret;
}

template<typename T>
TString<T> UricodeStringCodeConverter<T>::stringTo(TString<T> str)
{
	TString<T> ret;
	int i=0;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		ret.appendChar((T)'%');
		if(pch>='a'&& pch<='z'){
			ret.appendChar(pch);
		}else if(pch>='A'&& pch<='Z'){
			ret.appendChar(pch);
		}else if(pch=='/' || pch=='?' || pch=='=' || pch=='&'){
			ret.appendChar(pch);
		}else{
			while(pch!=0){
				for(int j=0;j<2;j++){
					int val=((pch)>>(1-j))&0xf;
					T sch='0';
					if(val<10){
						sch=(T)('0'+val);
					}else{
						sch=(T)('A'+(val-10));
					}
					ret.appendChar(sch);
				}
				pch >>= 8;
			}
		}
		i++;
	}
	return ret;
}

#endif // _I2F_URICODE_STRING_CODE_CONVERTER_H_

