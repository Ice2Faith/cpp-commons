#ifndef _I2F_BYTEARRAY_INPUTSTREAM_H_
#define _I2F_BYTEARRAY_INPUTSTREAM_H_

#include"InputStream.h"

class ByteArrayInputStream : virtual public InputStream
{
private:
	Array<byte> m_data;
	int m_idx;
public:
	ByteArrayInputStream(const Array<byte>& data){
		this->m_data = data;
		this->m_idx = 0;
	}
	virtual ~ByteArrayInputStream(){
		this->m_idx = 0;
	};
	ByteArrayInputStream(const ByteArrayInputStream& is){
		this->m_data = is.m_data;
		this->m_idx = is.m_idx;
	}
	ByteArrayInputStream(ByteArrayInputStream&& is){
		this->m_data = is.m_data;
		this->m_idx = is.m_idx;
	}
	ByteArrayInputStream& operator=(const ByteArrayInputStream& is){
		this->m_data = is.m_data;
		this->m_idx = is.m_idx;
	}
	ByteArrayInputStream& operator=(ByteArrayInputStream && is){
		this->m_data = is.m_data;
		this->m_idx = is.m_idx;
	}
	virtual int read(){
		if (this->m_idx >= this->m_data.size()){
			return -1;
		}
		return this->m_data[this->m_idx++];
	}
	virtual int read(Array<byte>& buf)
	{
		int cnt = 0;
		while (this->m_idx < this->m_data.size() && cnt<buf.size()){
			buf[cnt] = this->m_data[this->m_idx++];
			cnt++;
		}
		return cnt;
	}
	virtual int read(Array<byte>& buf, int offset, int count)
	{
		int cnt = 0;
		while (this->m_idx < this->m_data.size() && cnt<count && (offset+cnt)<buf.size()){
			buf[offset+cnt] = this->m_data[this->m_idx++];
			cnt++;
		}
		return cnt;
	}
	virtual void skip(long len)
	{
		if (len>0){
			this->m_idx += len;
		}
	}
	virtual void reset(){
		this->m_idx = 0;
	}
	virtual bool avaliable(){
		return true;
	}
	virtual void close(){

	}
};

#endif // _I2F_BYTEARRAY_INPUTSTREAM_H_
