#include"StreamWriter.h"
#include"Writer.hpp"
#include"OutputStream.h"
#include"../codec/StringCodec.h"
#include"../codec/ICodec.h"
#include"../codec/GbkCodec.h"
#include"../codec/Utf8Codec.h"



StreamWriter::StreamWriter(OutputStream* os, StringCodec::Charset charset)
{
	this->m_os = os;
	this->m_charset = charset;
}

StreamWriter::StreamWriter(StreamWriter& writer)
{
	this->m_os = writer.m_os;
	this->m_charset = writer.m_charset;
}

StreamWriter& StreamWriter::operator=(StreamWriter& writer)
{
	this->m_os = writer.m_os;
	this->m_charset = writer.m_charset;
	return *this;
}

StreamWriter::~StreamWriter()
{

}

void StreamWriter::write(int ch)
{
	if (this->m_charset == StringCodec::GBK){
		GbkCodec codec;
		Array<byte> bts=codec.writeUniChar32((UniChar32)ch);
		this->m_os->write(bts);
	}
	else if (this->m_charset == StringCodec::UTF8){
		Utf8Codec codec;
		Array<byte> bts = codec.writeUniChar32((UniChar32)ch);
		this->m_os->write(bts);
	}
	else{
		this->m_os->write(ch);
	}
	this->m_os->flush();
}

void StreamWriter::write(String str)
{
	Array<byte> bts=str.toBytes(this->m_charset);
	this->m_os->write(bts);
	this->m_os->flush();
}

void StreamWriter::writeLine(String str)
{
	this->write(str);
	this->write((int)'\n');
}

void StreamWriter::close()
{
	if (this->m_os != NULL){
		this->m_os->close();
	}
	this->m_os = NULL;
}

