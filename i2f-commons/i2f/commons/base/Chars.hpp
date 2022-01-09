#ifndef _I2F_CHARS_H_
#define _I2F_CHARS_H_
#include"Base.hpp"

template<typename T>
class TChars
{
public:
	virtual ~TChars(){}
	bool isNumber(T ch);
	bool isA2Z(T ch);
	bool isa2z(T ch);
	bool isA2Za2z(T ch);
	bool isAscii(T ch);
	T lower(T ch);
	T upper(T ch);
	bool isSpace(T ch);
	bool isVisibleAscii(T ch);
};

typedef TChars<UniChar16> Chars;

template<typename T>
bool TChars<T>::isNumber(T ch)
{
	return ch >= '0'&&ch <= '9';
}

template<typename T>
bool TChars<T>::isA2Z(T ch)
{
	return ch >= 'A'&&ch <= 'Z';
}

template<typename T>
bool TChars<T>::isa2z(T ch)
{
	return ch >= 'a'&&ch <= 'z';
}

template<typename T>
bool TChars<T>::isA2Za2z(T ch)
{
	return this->isA2Z(ch) || this->isa2z(ch);
}

template<typename T>
bool TChars<T>::isAscii(T ch)
{
	return ch >= 0 && ch < 0x80;
}

template<typename T>
T TChars<T>::lower(T ch)
{
	if (this->isA2Z(ch)){
		return ch | 32;
	}
	return ch;
}

template<typename T>
T TChars<T>::upper(T ch)
{
	if (this->isa2z(ch))
	{
		return ch & (~32);
	}
	return ch;
}

template<typename T>
bool TChars<T>::isSpace(T ch)
{
	return ch == 32 || ch == '\t' || ch == '\n' || ch == '\r';
}

template<typename T>
bool TChars<T>::isVisibleAscii(T ch)
{
	return ch >= 32 && ch <= 126;
}

#endif // _I2F_CHARS_H_