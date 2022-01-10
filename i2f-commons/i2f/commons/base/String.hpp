#ifndef _I2F_STRING_H_
#define _I2F_STRING_H_

#include"../container/Container.h"
#include"../codec/Codec.h"
#include"../interface/IHashcode.h"
#include"../interface/IEquals.h"
#include"IUString.h"
#include"../codec/StringCodec.h"
#include"../io/ByteArrayInputStream.hpp"
#include"../io/ByteArrayOutputStream.hpp"
#include"../algorithm/Arrays.hpp"

template<typename T>
class TBasicString
{
public:
	virtual ~TBasicString(){}
	virtual int slength(T* str);
	virtual int scompare(T * str1, T* str2);
	virtual void slower(T* str);
	virtual void supper(T* str);
	virtual int sfind(T* str, T* str1, int form);
	virtual void sconcat(T* str, int maxsize, T* str1);
	virtual void scopy(T* dst, int maxsize, T* src,int from,int count);
	virtual int shfind(T * str, T* str1, int from);
	virtual bool sequal(T* str1, T * str2, int size);
};

template<typename T>
int TBasicString<T>::slength(T* str)
{
	int i = 0;
	while (str[i] != 0){
		i++;
	}
	return i;
}

template<typename T>
int TBasicString<T>::scompare(T * str1, T* str2)
{
	int i = 0;
	while (str1[i] != 0 && str2[i] != 0){
		if (str1[i] < str2[i]){
			return -1;
		}
		if (str1[i]>str2[i]){
			return 1;
		}
		i++;
	}
	if (str1[i] != 0){
		return -1;
	}
	if (str2[i] != 0){
		return 1;
	}
	return 0;
}

template<typename T>
void TBasicString<T>::slower(T* str)
{
	int i = 0;
	while (str[i] != 0){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] += ('a' - 'A');
		}
		i++;
	}
}

template<typename T>
void TBasicString<T>::supper(T* str)
{
	int i = 0;
	while (str[i] != 0){
		if (str[i] >= 'a' && str[i] <= 'z'){
			str[i] -= ('a' - 'A');
		}
		i++;
	}
}

template<typename T>
int TBasicString<T>::sfind(T* str, T* str1,int from)
{
	int i = from;
	while (str[i] != 0){
		int j = 0;
		bool eq = true;
		while (str1[j] != 0){
			if (str[i + j] != str1[j]){
				eq = false;
				break;
			}
			if (str[i + j] == 0 ){
				eq = false;
				break;
			}
			j++;
		}
		if (eq){
			return i;
		}
		i++;
	}
	return -1;
}

template<typename T>
void TBasicString<T>::sconcat(T* str, int maxsize, T* str1)
{
	int i = 0;
	while (str[i] != 0){
		i++;
	}
	if (i >= maxsize){
		return;
	}
	int j = 0;
	while (str1[j] != 0 && i + j < maxsize-1)
	{
		str[i] = str1[j];
		j++;
		i++;
	}
	str[i] = 0;
}

template<typename T>
void TBasicString<T>::scopy(T* dst, int maxsize, T* src, int from, int count)
{
	int i = 0;
	while (src[from + i] != 0 && i<count && i<maxsize-1){
		dst[i] = src[from + i];
		i++;
	}
	dst[i] = 0;
}

template<typename T>
int TBasicString<T>::shfind(T * str, T* str1, int from)
{
	int len1 = this->slength(str);
	int len2 = this->slength(str1);
	int maxLen = len1 - len2;
	int i = from;
	while (i < maxLen){
		bool eq = this->sequal(&str[i], str1, len2);
		if (eq){
			return i;
		}
		i++;
	}
	return -1;
}

template<typename T>
bool TBasicString<T>::sequal(T* str1, T * str2, int size)
{
	Arrays<T> algo;
	return algo.equal(str1, str2, 0, size - 1);
}


template<typename T>
class TString : virtual TBasicString<T>, virtual public Container, virtual public IEquals, virtual public IHashCode,  virtual public IUString
{
protected:
	T* m_data;
	int m_size;
	int m_capital;
	void refreshSizeWhenAppend();
	void autoCapital(int requireSize);
	TString<T>& recapital(int capital);
public:
	TString();
	TString(const T* str);
	TString(const T * str, int from, int count);
	TString(const TString<T>& str);
	TString(const TString<T>& str,int from,int count);
	TString(TString<T> && str);
	virtual ~TString();
	virtual TString<T>& operator=(const T* str);
	virtual TString<T>& operator=(const TString<T> & str);
	virtual TString<T>& operator=(TString<T> && str);
	virtual bool equals(const IEquals& val);
	virtual int hashcode();
	virtual operator T*();
	virtual T* data();
	virtual int size();
	virtual int capital();
	virtual bool isEmpty();
	virtual TString<T>& fresh();
	virtual TString<T>& clear();
	virtual T& operator[](int index);
	virtual T& charAt(int index);
	virtual TString<T> operator+(const T* str);
	virtual TString<T> operator+(const TString<T>& str);
	virtual TString<T> operator+(int num);
	virtual TString<T> operator+(long num);
	virtual TString<T> operator+(long long num);
	virtual TString<T> operator+(short num);
	virtual TString<T> operator+(char ch);
	virtual TString<T> operator+(byte bt);
	virtual TString<T> operator+(float num);
	virtual TString<T> operator+(double num);
	virtual TString<T> operator+(bool val);
	friend TString<T> operator+(const T* str1, const TString<T>& str2)
	{
		TString<T> ret(str1);
		ret.append(str2);
		return ret;
	}
	friend TString<T> operator+(int num, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%d", num);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(long num, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%ld", num);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(long long num, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%lld", num);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(short num, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%d", num);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(char ch, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%c", ch);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(byte bt, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%02x", bt);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(float num, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%f", num);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(double num, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%lf", num);
		return TString<T>::formatAsciiLink(buf, str);
	}
	friend TString<T> operator+(bool val, const TString<T>& str)
	{
		char buf[300] = { 0 };
		sprintf(buf, "%s", (val ? "true" : "false"));
		return TString<T>::formatAsciiLink(buf, str2);
	}
	static TString<T> formatAsciiLink(char * buf, const TString<T>& str);
	virtual TString<T> substring(int from, int count);
	virtual TString<T>& appendChar(T ch);
	virtual TString<T>& appendChars(T* chs, int from, int count);
	virtual TString<T>& append(int num);
	virtual TString<T>& append(long num);
	virtual TString<T>& append(long long num);
	virtual TString<T>& append(short num);
	virtual TString<T>& append(char num);
	virtual TString<T>& append(byte num);
	virtual TString<T>& append(float num);
	virtual TString<T>& append(double num);
	virtual TString<T>& append(bool num);
	virtual TString<T>& append(const T* str);
	virtual TString<T>& appendAsciiFormat(char * buf);
	virtual TString<T>& append(const T* str, int from, int count);
	virtual TString<T>& append(const TString<T>& str);
	virtual TString<T>& append(const TString<T>& str,int from, int count);
	virtual TString<T>& appends(const TString<T>& str, int repeat);
	friend TString<T> operator*(int num, const TString<T>& str){
		TString<T> ret(*this);
		ret.repeat(num);
		return num;
	}
	virtual TString<T> operator*(int num);
	virtual TString<T>& repeat(int num);
	virtual int indexOf(T ch);
	virtual int indexOf(T ch, int from);
	virtual int lastIndexOf(T ch);
	virtual int lastIndexOf(T ch, int from);
	virtual int indexOf(const T* str);
	virtual int indexOf(const TString<T>& str);
	virtual int indexOf(const T* str,int from);
	virtual int indexOf(const TString<T>& str,int from);
	virtual int lastIndexOf(const T* ch);
	virtual int lastIndexOf(const TString<T>& str);
	virtual bool startWith(const TString<T>& str);
	virtual bool endWith(const TString<T>& str);
	virtual TString<T> toLower() const;
	virtual TString<T> toUpper() const;
	virtual TString<T> fitstToLower();
	virtual TString<T> firstToUpper();
	virtual TString<T> trim();
	virtual TString<T> trimStart();
	virtual TString<T> trimEnd();
	virtual int compareTo(const TString<T>& str);
	virtual bool equals(const TString<T>& str);
	virtual bool equalsIgnoreCase(const TString<T>& str);
	virtual bool operator==(const TString<T>& str);
	virtual bool operator!=(const TString<T>& str);
	virtual bool operator>(const TString<T>& str);
	virtual bool operator>=(const TString<T>& str);
	virtual bool operator<(const TString<T>& str);
	virtual bool operator<=(const TString<T>& str);
	virtual TString<T>& of(int num);
	virtual TString<T>& of(long num);
	virtual TString<T>& of(long long num);
	virtual TString<T>& of(short num);
	virtual TString<T>& of(char num);
	virtual TString<T>& of(byte num);
	virtual TString<T>& of(float num);
	virtual TString<T>& of(double num);
	virtual TString<T>& of(bool val);
	virtual TString<T>& ofAsciiFormat(char * buf);
	virtual TString<T> replace(const TString<T>& src, const TString<T> dst);
	virtual TString<T> replaceAll(const TString<T>& src, const TString<T>& dst);

	virtual void ofBytes(Array<byte>& bts, StringCodec::Charset charset);
	virtual Array<byte> toBytes(StringCodec::Charset charset);
	
};

template<typename T>
void TString<T>::ofBytes(Array<byte>& bts, StringCodec::Charset charset)
{
	ByteArrayInputStream is(bts);
	Array<UniChar32> arr=StringCodec::stringOf(is, charset);
	if (this->m_data != NULL){
		delete[] this->m_data;
	}
	this->m_size = 0;
	this->m_data = NULL;
	this->m_capital = 0;
	this->recapital(arr.size()+1);
	this->m_data[0] = (T)0;
	for (int i = 0; i < arr.size(); i++){
		this->m_data[i] = (T)arr[i];
	}
	this->m_data[arr.size()] = (T)0;
	this->m_size = arr.size();
}

template<typename T>
Array<byte> TString<T>::toBytes(StringCodec::Charset charset)
{
	Array<UniChar32> arr(this->m_size);
	for (int i = 0; i < arr.size(); i++){
		arr[i] = (UniChar32)(this->m_data[i]);
	}
	Array<byte> bts=StringCodec::stringTo(arr, charset);
	return bts;
}

typedef TString<char> AString;
typedef TString<UniChar16> U16String;
typedef TString<UniChar32> U32String;
typedef U16String UString;
typedef U16String String;


template<typename T>
TString<T>::TString()
{
	this->m_size = 0;
	this->m_data = NULL;
	this->m_capital = 0;
	this->recapital(32);
	this->m_data[0] = (T)0;
}

template<typename T>
TString<T>::TString(const T* str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	this->m_size = 0;
	this->m_data = NULL;
	this->m_capital = 0;
	this->autoCapital(i+1);
	this->m_size = i;
	this->m_data[i] = (T)0;
	i--;
	while (i >= 0){
		this->m_data[i] = str[i];
		i--;
	}
}

template<typename T>
TString<T>::TString(const T * str, int from, int count)
{
	int i = 0;
	while (str[from+i] && i!=count)
	{
		i++;
	}
	this->m_size = 0;
	this->m_data = NULL;
	this->m_capital = 0;
	this->autoCapital(i+1);
	this->m_size = i;
	this->m_data[i] = (T)0;
	i--;
	while (i >= 0){
		this->m_data[i] = str[from+i];
		i--;
	}
}

template<typename T>
TString<T>::TString(const TString<T>& str)
{
	this->m_size = 0;
	int size = str.m_size;
	this->m_data = NULL;
	this->m_capital = 0;
	this->autoCapital(size+1);
	this->m_data[size] = (T)0;
	for (int i = 0; i < size; i++){
		this->m_data[i] = str.m_data[i];
	}
	this->m_data[size] = (T)0;
	this->m_size = size;
}

template<typename T>
TString<T>::TString(const TString<T>& str, int from, int count)
{
	int i = 0;
	int size = str.m_size;
	while (i != count && (from + i) < size){
		i++;
	}
	this->m_size = 0;
	this->m_data = NULL;
	this->m_capital = 0;
	this->autoCapital(i+1);
	this->m_size = i;
	this->m_data[i] = (T)0;
	i -- ;
	while (i >= 0){
		this->m_data[i] = str.m_data[from + i];
		i++;
	}
}

template<typename T>
TString<T>::TString(TString<T> && str)
{
	this->m_size = str.m_size;
	this->m_capital = str.m_capital;
	this->m_data = str.m_data;
	str.m_data = NULL;
	str.m_size = 0;
	str.m_capital = 0;
}

template<typename T>
TString<T>::~TString()
{
	if (this->m_data != NULL){
		delete this->m_data;
	}
	this->m_data = NULL;
	this->m_size = 0;
	this->m_capital = 0;
}

template<typename T>
TString<T>& TString<T>::operator=(const T* str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	this->m_size = 0;
	this->autoCapital(i+1);
	this->m_size = i;
	this->m_data[i] = (T)0;
	i--;
	while (i >= 0){
		this->m_data[i] = str[i];
		i--;
	}
	return *this;
}

template<typename T>
TString<T>& TString<T>::operator=(const TString<T> & str)
{
	if (this == &str){
		return *this;
	}
	int size = str.m_size;
	this->m_size = size;
	this->autoCapital(size+1);
	this->m_data[size] = (T)0;
	for (int i = 0; i < size; i++){
		this->m_data[i] = str.m_data[i];
	}
	return *this;
}

template<typename T>
TString<T>& TString<T>::operator=(TString<T> && str)
{
	this->m_size = str.m_size;
	this->m_capital = str.m_capital;
	this->m_data = str.m_data;
	str.m_data = NULL;
	str.m_size = 0;
	str.m_capital = 0;
	return *this;
}

template<typename T>
bool TString<T>::equals(const IEquals& val)
{
	const TString<T>& str = dynamic_cast<const TString<T>&>(val);
    //TString<T>& str=(TString<T>&)val;
    return this->equals(str);
}

template<typename T>
int TString<T>::hashcode()
{
    int code=0;
    for(int i=0;i<this->m_size;i++){
		code += (int)((int)(this->m_data[i])*(31.0 / 7));
    }
    return code;
}

template<typename T>
TString<T>::operator T*()
{
	return this->m_data;
}

template<typename T>
T* TString<T>::data()
{
	return this->m_data;
}

template<typename T>
int TString<T>::size()
{
	return this->m_size;
}

template<typename T>
void TString<T>::autoCapital(int requireSize)
{
	if (requireSize > this->m_capital){
		int ncap = 2;
		while (ncap < requireSize){
			ncap <<= 1;
		}
		this->recapital(ncap);
	}
}

template<typename T>
TString<T>& TString<T>::recapital(int capital)
{
	if (capital >= 0){
		T * ndata = new T[capital];
		int size = 0;
		for (int i = 0; i < this->m_size && i < capital; i++, size++){
			ndata[i] = this->m_data[i];
		}
		if (this->m_data != NULL){
			delete[] this->m_data;
		}
		this->m_data = ndata;
		this->m_capital = capital;
		this->m_size = size;
		this->m_data[this->m_size ] = (T)0;
		if (this->m_capital > 0){
			this->m_data[this->m_capital - 1] = (T)0;
		}
	}
	return *this;
}

template<typename T>
int TString<T>::capital()
{
	return this->m_capital;
}

template<typename T>
bool TString<T>::isEmpty()
{
	return this->m_size == 0;
}

template<typename T>
TString<T>& TString<T>::fresh()
{
	int size = 0;
	while (this->m_data[size] && size<this->m_capital){
		size++;
	}
	if (size == this->m_capital){
		size--;
		this->m_data[size] = (T)0;
	}
	this->m_size = size;
	return *this;
}

template<typename T>
TString<T>& TString<T>::clear()
{
	this->m_size = 0;
	this->m_data[0] = (T)0;
	return *this;
}

template<typename T>
T& TString<T>::operator[](int index)
{
	return this->m_data[index];
}

template<typename T>
T& TString<T>::charAt(int index)
{
	return this->m_data[index];
}

template<typename T>
TString<T> TString<T>::operator+(const T* str)
{
	TString<T> ret(*this);
	return ret.append(str);
}

template<typename T>
TString<T> TString<T>::operator+(const TString<T>& str)
{
	TString<T> ret(*this);
	return ret.append(str);
}

template<typename T>
TString<T> TString<T>::operator+(int num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%d", num);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(long num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%ld", num);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(long long num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%lld", num);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(short num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%d", num);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(char ch)
{
	char buf[300] = { 0 };
	sprintf(buf, "%c", ch);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(byte bt)
{
	char buf[300] = { 0 };
	sprintf(buf, "%02x", bt);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(float num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%f", num);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(double num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%lf", num);
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}

template<typename T>
TString<T> TString<T>::operator+(bool val)
{
	char buf[300] = { 0 };
	sprintf(buf, "%s", (val ? "true" : "false"));
	TString<T> ret(*this);
	return ret.appendAsciiFormat(buf);
}


template<typename T>
TString<T> TString<T>::formatAsciiLink(char * buf, const TString<T>& str)
{
	TString<T> ret;
	ret.ofAsciiFormat(buf);
	return ret.append(str);
}

template<typename T>
TString<T> TString<T>::operator*(int num)
{
	TString<T> ret(*this);
	ret.repeat(num);
	return ret;
}

template<typename T>
TString<T>& TString<T>::repeat(int num)
{
	if (num <= 0){
		return *this;
	}
	TString<T> str(*this);
	for (int i = 0; i < num; i++){
		this->append(str);
	}
	return *this;
}

template<typename T>
TString<T> TString<T>::substring(int from, int count)
{
	return TString<T>(*this,from,count);
}

template<typename T>
TString<T>& TString<T>::appendChar(T ch)
{
	this->autoCapital(this->m_size + 2);
	this->m_data[this->m_size] = ch;
	this->m_size++;
	this->m_data[this->m_size] = (T)0;
	return *this;
}

template<typename T>
TString<T>& TString<T>::appendChars(T* chs, int from, int count)
{
	for (int i = 0; i != count && chs[from + i] != 0; i++){
		this->appendChar(chs[from + i]);
	}
	return *this;
}

template<typename T>
TString<T>& TString<T>::append(int num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%d", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(long num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%ld", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(long long num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%lld", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(short num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%d", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(char num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%c", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(byte num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%02x", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(float num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%f", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(double num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%lf", num);
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(bool val)
{
	char buf[300] = { 0 };
	sprintf(buf, "%s", (val ? "true" : "false"));
	return this->appendAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::append(const T* str)
{
	int i = 0;
	while (str[i]){
		i++;
	}
	this->autoCapital(this->m_size + i+1);
	for (int j = 0; j < i; j++){
		this->m_data[this->m_size + j] = str[j];
	}
	this->m_size += i;
	this->m_data[this->m_size] = (T)0;
	return *this;
}

template<typename T>
TString<T>& TString<T>::appendAsciiFormat( char * buf)
{
	int i = 0;
	while (buf[i]){
		i++;
	}
	this->autoCapital(this->m_size + i+1);
	for (int j = 0; j < i; j++){
		this->m_data[this->m_size + j] = (T)buf[j];
	}
	this->m_size += i;
	this->m_data[this->m_size] = (T)0;
	return *this;
}

template<typename T>
TString<T>& TString<T>::append(const T* str, int from, int count)
{
	int i = 0;
	while (i!=count && str[from+i]){
		i++;
	}
	this->autoCapital(this->m_size + i+1);
	for (int j = 0; j < i; j++){
		this->m_data[this->m_size + j] = str[from+j];
	}
	this->m_size += i;
	this->m_data[this->m_size] = (T)0;
	return *this;
}

template<typename T>
TString<T>& TString<T>::append(const TString<T>& str)
{
	return this->append(str, 0, str.m_size);
}

template<typename T>
TString<T>& TString<T>::append(const TString<T>& str, int from, int count)
{
	int i = 0;
	int size = str.m_size;
	while (i != count && (from+i)<size){
		i++;
	}
	this->autoCapital(this->m_size + i+1);
	for (int j = 0; j < i; j++){
		this->m_data[this->m_size + j] = str.m_data[from + j];
	}
	this->m_size += i;
	this->m_data[this->m_size] = (T)0;
	return *this;
}

template<typename T>
TString<T>& TString<T>::appends(const TString<T>& str, int repeat)
{
	for (int i = 0; i < repeat; i++){
		this->append(str);
	}
	return *this;
}

template<typename T>
int TString<T>::indexOf(T ch)
{
	return this->indexOf(ch,0);
}

template<typename T>
int TString<T>::indexOf(T ch, int from)
{
	int ret = -1;
	for (int i = from; i < this->m_size; i++){
		if (this->m_data[i] == ch){
			ret = i;
			break;
		}
	}
	return ret;
}

template<typename T>
int TString<T>::lastIndexOf(T ch)
{
	return this->lastIndexOf(ch, -1);
}

template<typename T>
int TString<T>::lastIndexOf(T ch, int from)
{
	int ret = -1;
	for (int i = this->m_size-1-from; i >=0; i--){
		if (this->m_data[i] == ch){
			ret = i;
			break;
		}
	}
	return ret;
}

template<typename T>
int TString<T>::indexOf(const T* str)
{
	return this->indexOf(str, 0);
}

template<typename T>
int TString<T>::indexOf(const TString<T>& str)
{
	return this->indexOf(str, 0);
}

template<typename T>
int TString<T>::indexOf(const T* str, int from)
{
	int i = from;
	int tlen = 0;
	while (i < (this->m_size - tlen))
	{
		bool find = true;
		int j = 0;
		while (str[j] && (i + j) < this->m_size){
			if (str[i] != this->m_data[i + j]){
				find = false;
			}
			j++;
		}
		if (j>tlen){
			tlen = j;
		}
		if (find){
			if (!str[j] || (i + j) == this->m_size){
				find = false;
			}
		}
		if (find){
			return i;
		}
		i++;
	}
	return -1;
}

template<typename T>
int TString<T>::indexOf(const TString<T>& str, int from)
{
	int i = from;
	int tlen = str.m_size;
	while (i < (this->m_size - tlen))
	{
		bool find = true;
		int j = 0;
		while (str.m_data[j] && (i + j) < this->m_size){
			if (str.m_data[i] != this->m_data[i + j]){
				find = false;
			}
			j++;
		}

		if (find){
			if (!str.m_data[j] || (i + j) == this->m_size){
				find = false;
			}
		}
		if (find){
			return i;
		}
		i++;
	}
	return -1;
}

template<typename T>
int TString<T>::lastIndexOf(const T* str)
{
	int tlen = 0;
	while (str[tlen]){
		tlen++;
	}
	int i = this->m_size-1 - tlen;
	while (i >= 0){
		bool find = true;
		int j = 0;
		while (str[j] && (i + j) < this->m_size){
			if (str[i] != this->m_data[i + j]){
				find = false;
			}
			j++;
		}

		if (find){
			if (!str[j] || (i + j) == this->m_size){
				find = false;
			}
		}
		if (find){
			return i;
		}
		i--;
	}
	return -1;
}

template<typename T>
int TString<T>::lastIndexOf(const TString<T>& str)
{
	int tlen = str.m_size;
	int i = this->m_size-1 - tlen;
	while (i >= 0){
		bool find = true;
		int j = 0;
		while (str.m_data[j] && (i + j) < this->m_size){
			if (str.m_data[i] != this->m_data[i + j]){
				find = false;
			}
			j++;
		}

		if (find){
			if (!str.m_data[j] || (i + j) == this->m_size){
				find = false;
			}
		}
		if (find){
			return i;
		}
		i--;
	}
	return -1;
}

template<typename T>
bool TString<T>::startWith(const TString<T>& str)
{
	int tlen = str.m_size;
	if (tlen > this->m_size){
		return false;
	}
	for (int i = 0; i < tlen; i++){
		if (str.m_data[i] != this->m_data[i]){
			return false;
		}
	}
	return true;
}

template<typename T>
bool TString<T>::endWith(const TString<T>& str)
{
	int tlen = str.m_size;
	if (tlen > this->m_size){
		return false;
	}
	int clen = this->m_size;
	for (int i = 0; i < tlen; i++){
		if (str.m_data[tlen-1-i] != this->m_data[clen-1-i]){
			return false;
		}
	}
	return true;
}

template<typename T>
TString<T> TString<T>::toLower() const
{
	TString<T> ret(*this);
	for (int i = 0; i < ret.m_size; i++){
		if (ret.m_data[i] >= 'A' && ret.m_data[i] <= 'Z'){
			ret.m_data[i] += ('a'-'A');
		}
	}
	return ret;
}

template<typename T>
TString<T> TString<T>::toUpper() const
{
	TString<T> ret(*this);
	for (int i = 0; i < ret.m_size; i++){
		if (ret.m_data[i] >= 'a' && ret.m_data[i] <= 'z'){
			ret.m_data[i] -= ('a' - 'A');
		}
	}
	return ret;
}

template<typename T>
TString<T> TString<T>::fitstToLower()
{
	TString<T> ret(*this);
	if (ret.m_size > 0){
		int i = 0;
		if (ret.m_data[i] >= 'A' && ret.m_data[i] <= 'Z'){
			ret.m_data[i] += ('a' - 'A');
		}
	}
	return ret;
}

template<typename T>
TString<T> TString<T>::firstToUpper()
{
	TString<T> ret(*this);
	if (ret.m_size > 0){
		int i = 0;
		if (ret.m_data[i] >= 'a' && ret.m_data[i] <= 'z'){
			ret.m_data[i] -= ('a' - 'A');
		}
	}
	return ret;
}

template<typename T>
TString<T> TString<T>::trim()
{
	int sl = 0, el = this->m_size-1;
	bool esl = false, eel = false;
	while (sl < el){
		if (!esl){
			if (this->m_data[sl] == 0x20
				|| this->m_data[sl] == '\t'
				|| this->m_data[sl] == '\r'
				|| this->m_data[sl] == '\n'){
				sl++;
			}
			else{
				esl = true;
			}
		}
		if (!eel){
			if (this->m_data[el] == 0x20
				|| this->m_data[el] == '\t'
				|| this->m_data[el] == '\r'
				|| this->m_data[el] == '\n'){
				el--;
			}
			else{
				eel = true;
			}
		}
		if (esl && eel){
			break;
		}
	}
	return this->substring(sl, el - sl+1);
}

template<typename T>
TString<T> TString<T>::trimStart()
{
	int sl = 0;
	bool esl = false;
	while (sl<this->m_size){
		if (!esl){
			if (this->m_data[sl] == 0x20
				|| this->m_data[sl] == '\t'
				|| this->m_data[sl] == '\r'
				|| this->m_data[sl] == '\n'){
				sl++;
			}
			else{
				esl = true;
			}
		}
	
		if (esl ){
			break;
		}
	}
	return this->substring(sl, this->m_size-sl);
}

template<typename T>
TString<T> TString<T>::trimEnd()
{
	int el = this->m_size-1;
	bool eel = false;
	while (el>=0){
		if (!eel){
			if (this->m_data[el] == 0x20
				|| this->m_data[el] == '\t'
				|| this->m_data[el] == '\r'
				|| this->m_data[el] == '\n'){
				el--;
			}
			else{
				eel = true;
			}
		}
		if (eel){
			break;
		}
	}
	return this->substring(0, el + 1);
}

template<typename T>
int TString<T>::compareTo(const TString<T>& str)
{
	int i = 0;
	while (i < this->m_size && i < str.m_size)
	{
		if (this->m_data[i]>str.m_data[i]){
			return 1;
		}
		if (this->m_data[i] < str.m_data[i]){
			return -1;
		}
		i++;
	}
	if (i != str.m_size){
		return -1;
	}
	if (i != this->m_size){
		return 1;
	}
	return 0;
}

template<typename T>
bool TString<T>::equals(const TString<T>& str)
{
	return this->compareTo(str) == 0;
}

template<typename T>
bool TString<T>::equalsIgnoreCase(const TString<T>& str)
{
	TString<T> pthis = this->toLower();
	TString<T> pstr = str.toLower();
	return pthis.compareTo(pstr) == 0;
}

template<typename T>
bool TString<T>::operator==(const TString<T>& str)
{
	return this->compareTo(str) == 0;
}

template<typename T>
bool TString<T>::operator!=(const TString<T>& str)
{
	return this->compareTo(str) != 0;
}

template<typename T>
bool TString<T>::operator>(const TString<T>& str)
{
	return this->compareTo(str) > 0;
}

template<typename T>
bool TString<T>::operator>=(const TString<T>& str)
{
	return this->compareTo(str) >= 0;
}

template<typename T>
bool TString<T>::operator<(const TString<T>& str)
{
	return this->compareTo(str) < 0;
}

template<typename T>
bool TString<T>::operator<=(const TString<T>& str)
{
	return this->compareTo(str) <= 0;
}



template<typename T>
void TString<T>::refreshSizeWhenAppend()
{
	while (this->m_data[this->m_size] != 0 && this->m_size<this->m_capital){
		this->m_size++;
	}
	this->m_data[this->m_size - 1] = (T)0;
}

template<typename T>
TString<T>& TString<T>::of(int num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%d", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(long num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%ld", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(long long num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%lld", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(short num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%d", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(char num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%c", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(byte num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%02x", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(float num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%f", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(double num)
{
	char buf[300] = { 0 };
	sprintf(buf, "%lf", num);
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::of(bool val)
{
	char buf[300] = { 0 };
	sprintf(buf, "%s", (val ? "true" : "false"));
	return this->ofAsciiFormat(buf);
}

template<typename T>
TString<T>& TString<T>::ofAsciiFormat(char * buf)
{
	int tlen = 0;
	while (buf[tlen]){
		tlen++;
	}
	this->m_size = 0;
	this->autoCapital(tlen+1);
	this->m_size = tlen;
	tlen--;
	while (tlen >= 0){
		this->m_data[tlen] = (T)buf[tlen];
		tlen--;
	}
	this->m_data[this->m_size] = (T)0;
	return *this;
}

template<typename T>
TString<T> TString<T>::replace(const TString<T>& src, const TString<T> dst)
{
	int idx = this->indexOf(src);
	if (idx >= 0){
		return this->substring(0, idx) + dst + this->substring(idx + src.m_size, -1);
	}
	return TString<T>(*this);
}

template<typename T>
TString<T> TString<T>::replaceAll(const TString<T>& src, const TString<T>& dst)
{
	TString<T> ret;
	int lstIdx = 0;
	int idx = 0;
	bool isDo = false;
	while ((idx = this->indexOf(src, lstIdx)) >= 0){
		ret = ret + this->substring(lstIdx, idx-lstIdx)+dst;

		isDo = true;
		lstIdx = idx+src.m_size;
	}
	if (isDo){
		ret = ret + this->substring(lstIdx, -1);
		return ret;
	}
	return TString<T>(*this);
}


#endif // _I2F_STRING_H_

