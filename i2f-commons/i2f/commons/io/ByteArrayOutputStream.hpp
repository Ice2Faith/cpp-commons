#ifndef _I2F_BYTEARRAY_OUTPUTSTREAM_H_
#define _I2F_BYTEARRAY_OUTPUTSTREAM_H_

#include"OutputStream.h"
#include"../container/ArrayList.hpp"

class ByteArrayOutputStream : virtual public OutputStream
{
private:
	ArrayList<byte> m_data;
public:
	ByteArrayOutputStream()
	{

	}
	ByteArrayOutputStream(int capital){
		m_data = ArrayList<byte>(capital);
	}
	virtual ~ByteArrayOutputStream(){

	};
	ByteArrayOutputStream(const ByteArrayOutputStream& os){
		this->m_data = os.m_data;
	}
	ByteArrayOutputStream(ByteArrayOutputStream&& os){
		this->m_data = os.m_data;
	}
	ByteArrayOutputStream& operator=(const ByteArrayOutputStream& os){
		this->m_data = os.m_data;
		return *this;
	}
	ByteArrayOutputStream& operator=(ByteArrayOutputStream&& os){
		this->m_data = os.m_data;
		return *this;
	}
	virtual int write(int bt){
		byte wbt = (byte)bt;
		this->m_data.add(wbt);
		return 1;
	}
	virtual int write(Array<byte>& buf)
	{
		for (int i = 0; i < buf.size(); i++){
			this->m_data.add(buf[i]);
		}
		return buf.size();
	}
	virtual int write(Array<byte>& buf, int offset, int count)
	{
		int cnt = 0;
		for (int i = 0; i < count && (offset + i) < buf.size(); i++)
		{
			this->m_data.add(buf[offset + i]);
			cnt++;
		}
		return cnt;
	}
	virtual void flush()
	{

	}
	virtual bool avaliable(){
		return true;
	}
	virtual void close(){

	}
	virtual Array<byte> toByteArray(){
		Array<byte> ret(this->m_data.size());
		for (int i = 0; i < ret.size(); i++){
			ret[i] = this->m_data.get(i);
		}
		return ret;
	}
};

#endif // _I2F_BYTEARRAY_OUTPUTSTREAM_H_
