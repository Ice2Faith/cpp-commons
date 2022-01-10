#ifndef _I2F_UCODE_STRING_CODE_CONVERTER_H_
#define _I2F_UCODE_STRING_CODE_CONVERTER_H_
#include"IStringCodeConverter.hpp"

/*
针对UCODE进行转换
\u5634
一个\u认为是一个字符
*/
template<typename T>
class UcodeStringCodeConverter : virtual public IStringCodeConverter<T>
{
public:
	UcodeStringCodeConverter(){}
	virtual ~UcodeStringCodeConverter(){}
	virtual TString<T> stringOf(TString<T> str);
	virtual TString<T> stringTo(TString<T> str);
};

template<typename T>
TString<T> UcodeStringCodeConverter<T>::stringOf(TString<T> str)
{
	TString<T> ret;
	int i=0;
	while(true)
	{
		T pch=str.charAt(i);
		if(pch==0)
		{
			break;
		}
		if(pch=='\\'){
			i++;
			T nch=str.charAt(i);
			if(nch==0){
				break;
			}
			i++;
			T sch=0;
			while(str.charAt(i)!='\\'){
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
TString<T> UcodeStringCodeConverter<T>::stringTo(TString<T> str)
{
	TString<T> ret;
	int i=0;
	while(str.charAt(i)!=0){
		T pch=str.charAt(i);
		ret.appendChar((T)'\\');
		ret.appendChar((T)'u');
		for(int j=0;i<4;j++){
			T pval=(pch>>(3-j))&0xf;
			T sch=(T)'0';
			if(pval<10){
				sch=(T)('0'+pval);
			}else{
				sch=(T)('A'+(pval-10));
			}
			ret.appendChar(sch);
		}
		i++;
	}
	return ret;
}

#endif // _I2F_UCODE_STRING_CODE_CONVERTER_H_

