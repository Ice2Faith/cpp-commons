#ifndef _I2F_BASE_H_
#define _I2F_BASE_H_
#include"../interface/IHashCode.h"
#include"../interface/IEquals.h"

/*
基本数据类型的包装器
*/

template<typename T>
class Base : virtual public IHashCode, virtual public IEquals
{
private:
	T val;
public:
	Base(){}
	~Base(){}

	Base(T val){
		this->val = val;
	}
	Base(Base<T>& bval){
		this->val = bval.val;
	}
	Base& operator=(const Base<T>& bval){
		this->val = bval.val;
		return *this;
	}
	Base& operator=(T val){
		this->val = val;
		return *this;
	}
	operator T(){
		return this->val;
	}
	virtual int hashcode()
	{
		return (int)this->val;
	}
	virtual bool equals(const IEquals& val)
	{
		const Base<T>& tval = dynamic_cast<const Base<T>&>(val);
		//Base<T>* tval = (Base<T>*)(void*)&val;
		return this->val == tval.val;
	}
	Base<T>& operator++(){
		this->val++;
		return *this;
	}
	Base<T> operator++(int){
		Base<T> ret(this->val);
		this->val++;
		return ret;
	}
	Base<T>& operator--(){
		this->val--;
		return *this;
	}
	Base<T> operator--(int){
		Base<T> ret(this->val);
		this->val--;
		return ret;
	}

	friend T operator+(T val, Base<T> bval){
		return val + bval.val;
	}
	Base<T> operator+(Base<T> val){
		return Base<T>(this->val + val.val);
	}
	Base<T> operator+(T val){
		return Base<T>(this->val + val);
	}

	Base<T>& operator+=(T val){
		this->val += val;
		return *this;
	}
	Base<T>& operator+=(Base<T>& val){
		this->val += val.val;
		return *this;
	}

	friend T operator-(T val, Base<T> bval){
		return val - bval.val;
	}
	Base<T> operator-(Base<T> val){
		return Base<T>(this->val - val.val);
	}
	Base<T> operator-(T val){
		return Base<T>(this->val - val);
	}

	Base<T>& operator-=(T val){
		this->val -= val;
		return *this;
	}
	Base<T>& operator-=(Base<T>& val){
		this->val -= val.val;
		return *this;
	}

	friend T operator*(T val, Base<T> bval){
		return val * bval.val;
	}
	Base<T> operator*(Base<T> val){
		return Base<T>(this->val * val.val);
	}
	Base<T> operator*(T val){
		return Base<T>(this->val * val);
	}

	Base<T>& operator*=(T val){
		this->val *= val;
		return *this;
	}
	Base<T>& operator*=(Base<T>& val){
		this->val *= val.val;
		return *this;
	}

	friend T operator/(T val, Base<T> bval){
		return val / bval.val;
	}
	Base<T> operator/(Base<T> val){
		return Base<T>(this->val / val.val);
	}
	Base<T> operator/(T val){
		return Base<T>(this->val / val);
	}

	Base<T>& operator/=(T val){
		this->val /= val;
		return *this;
	}
	Base<T>& operator/=(Base<T>& val){
		this->val /= val.val;
		return *this;
	}

	friend T operator%(T val, Base<T> bval){
		return val % bval.val;
	}
	Base<T> operator%(Base<T> val){
		return Base<T>(this->val % val.val);
	}
	Base<T> operator%(T val){
		return Base<T>(this->val % val);
	}

	Base<T>& operator%=(T val){
		this->val %= val;
		return *this;
	}
	Base<T>& operator%=(Base<T>& val){
		this->val %= val.val;
		return *this;
	}
	friend bool operator==(const T& val, const Base<T>& bval){
		return val == bval.val;
	}
	bool operator==(const Base<T>& bval){
		return this->val == bval.val;
	}
	bool operator==(const T& val){
		return this->val == val;
	}
	friend bool operator!=(const T& val, const Base<T>& bval){
		return val != bval.val;
	}
	bool operator!=(const Base<T>& bval){
		return this->val != bval.val;
	}
	bool operator!=(const T& val){
		return this->val != val;
	}
	friend bool operator>(const T& val, const Base<T>& bval){
		return val > bval.val;
	}
	bool operator>(const Base<T>& bval){
		return this->val > bval.val;
	}
	bool operator>(const T& val){
		return this->val > val;
	}
	friend bool operator<(const T& val, const Base<T>& bval){
		return val < bval.val;
	}
	bool operator<(const Base<T>& bval){
		return this->val < bval.val;
	}
	bool operator<(const T& val){
		return this->val < val;
	}
	friend bool operator>=(const T& val, const Base<T>& bval){
		return val >= bval.val;
	}
	bool operator>=(const Base<T>& bval){
		return this->val >= bval.val;
	}
	bool operator>=(const T& val){
		return this->val >= val;
	}
	friend bool operator<=(const T& val, const Base<T>& bval){
		return val <= bval.val;
	}
	bool operator<=(const Base<T>& bval){
		return this->val <= bval.val;
	}
	bool operator<=(const T& val){
		return this->val <= val;
	}
	friend T operator<<(T num, Base<T> bnum){
		return num << bnum.val;
	}
	Base<T> operator<<(int num){
		return Base<T>(this->val << num);
	}
	Base<T> operator<<(Base<T> num){
		return Base<T>(this->val << num.val);
	}
	friend T operator>>(T num, Base<T> bnum){
		return num >> bnum.val;
	}
	Base<T> operator>>(int num){
		return Base<T>(this->val >> num);
	}
	Base<T> operator>>(Base<T> num){
		return Base<T>(this->val >> num.val);
	}
	Base<T>& operator<<=(T num){
		this->val <<= num;
		return *this;
	}
	Base<T>& operator<<=(Base<T> num){
		this->val <<= num.val;
		return *this;
	}
	Base<T>& operator>>=(T num){
		this->val >>= num;
		return *this;
	}
	Base<T>& operator>>=(Base<T> num){
		this->val >>= num.val;
		return *this;
	}
	friend T operator&(T num, Base<T> bnum){
		return num & bnum.val;
	}
	Base<T> operator&(int num){
		return Base<T>(this->val & num);
	}
	Base<T> operator&(Base<T> num){
		return Base<T>(this->val & num.val);
	}
	friend T operator|(T num, Base<T> bnum){
		return num | bnum.val;
	}
	Base<T> operator|(int num){
		return Base<T>(this->val | num);
	}
	Base<T> operator|(Base<T> num){
		return Base<T>(this->val | num.val);
	}
	friend T operator^(T num, Base<T> bnum){
		return num ^ bnum.val;
	}
	Base<T> operator^(int num){
		return Base<T>(this->val ^ num);
	}
	Base<T> operator^(Base<T> num){
		return Base<T>(this->val ^ num.val);
	}
	Base<T>& operator&=(T num){
		this->val &= num;
		return *this;
	}
	Base<T>& operator&=(Base<T> num){
		this->val &= num.val;
		return *this;
	}
	Base<T>& operator|=(T num){
		this->val |= num;
		return *this;
	}
	Base<T>& operator|=(Base<T> num){
		this->val |= num.val;
		return *this;
	}
	Base<T>& operator^=(T num){
		this->val ^= num;
		return *this;
	}
	Base<T>& operator^=(Base<T> num){
		this->val ^= num.val;
		return *this;
	}
	Base<T> abs()
	{
		if (this->val < 0){
			return Base<T>(0 - this->val);
		}
		return *this;
	}
	Base<T> ops(){
		return Base<T>(0 - this->val);
	}
	
};

typedef Base<int> Integer;
typedef Base<long> Long;
typedef Base<short> Short;
typedef Base<char> Char;
typedef Base<float> Float;
typedef Base<double> Double;
typedef Base<long long> LLong;
typedef Base<unsigned int> UInteger;
typedef Base<unsigned long> ULong;
typedef Base<unsigned short> UShort;
typedef Base<unsigned char> UChar;
typedef Base<unsigned long long> ULLong;
typedef UChar Byte;
typedef unsigned char byte;

#endif // _I2F_BASE_H_

