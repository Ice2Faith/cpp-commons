#ifndef _I2F_STREAM_WRITER_H_
#define _I2F_STREAM_WRITER_H_
#include"Writer.hpp"
#include"OutputStream.h"
#include"../codec/StringCodec.h"


class StreamWriter : virtual public Writer
{
protected:
	OutputStream* m_os;
	StringCodec::Charset m_charset;
public:
	StreamWriter(OutputStream* is,StringCodec::Charset charset);
	StreamWriter(StreamWriter& writer);
	StreamWriter& operator=(StreamWriter& writer);
	virtual ~StreamWriter();
	virtual void write(int ch);
	virtual void write(String str);
	virtual void writeLine(String str);
	virtual void close();
};


#endif // _I2F_STREAM_WRITER_H_
