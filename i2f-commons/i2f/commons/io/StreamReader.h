#ifndef _I2F_STREAM_READER_H_
#define _I2F_STREAM_READER_H_
#include"Reader.hpp"
#include"InputStream.h"
#include"../codec/StringCodec.h"


class StreamReader : virtual public Reader
{
protected:
	InputStream* m_is;
	StringCodec::Charset m_charset;
public:
	StreamReader(InputStream* is,StringCodec::Charset charset);
	StreamReader(StreamReader& reader);
	StreamReader& operator=(StreamReader& reader);
	virtual ~StreamReader();
	virtual int read();
	virtual String readLine();
	virtual String readAll();
	virtual void close();
};


#endif // _I2F_STREAM_READER_H_
