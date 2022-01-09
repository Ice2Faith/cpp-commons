#include"StreamReader.h"
#include"Reader.hpp"
#include"InputStream.h"
#include"../codec/StringCodec.h"
#include"../codec/GbkCodec.h"
#include"../codec/Utf8Codec.h"

StreamReader::StreamReader(InputStream* is, StringCodec::Charset charset)
{
	this->m_is = is;
	this->m_charset = charset;
}

StreamReader::StreamReader(StreamReader& reader)
{
	this->m_is = reader.m_is;
	this->m_charset = reader.m_charset;
}

StreamReader& StreamReader::operator=(StreamReader& reader)
{
	this->m_is = reader.m_is;
	this->m_charset = reader.m_charset;
	return *this;
}

StreamReader::~StreamReader()
{

}

int StreamReader::read()
{
	Array<byte> buf(32);
	if (this->m_charset == StringCodec::GBK){
		GbkCodec codec;
		int rdlen = 0;
		int from = 0;
		UniChar32 uch = 0;
		int retCode = 0;
		while (retCode == 0){
			int bt=this->m_is->read();
			buf[rdlen++] = (byte)(bt&0xff);
			uch = 0;
			retCode = 0;
			from = 0;
			retCode = codec.readUniChar32(buf.data(), rdlen, &from, &uch);
		}
		return (int)uch;
	}
	else if (this->m_charset == StringCodec::UTF8){
		Utf8Codec codec;
		int rdlen = 0;
		int from = 0;
		UniChar32 uch = 0;
		int retCode = 0;
		while (retCode == 0){
			int bt = this->m_is->read();
			buf[rdlen++] = (byte)(bt & 0xff);
			uch = 0;
			retCode = 0;
			from = 0;
			retCode = codec.readUniChar32(buf.data(), rdlen, &from, &uch);
		}
		return (int)uch;
	}
	else{
		int bt = this->m_is->read();
		return bt;
	}
}

String StreamReader::readLine()
{
	String ret;
	while (true){
		int ch = this->read();
		if (ch == '\r'){
			continue;
		}
		if (ch == '\n' || ch == -1){
			break;
		}
		ret.appendChar((UniChar16)ch);
	}
	return ret;
}

String StreamReader::readAll()
{
	Array<UniChar32> arr=StringCodec::stringOf(*(this->m_is), this->m_charset);
	Array<UniChar16> data(arr.size());
	for (int i = 0; i < arr.size(); i++){
		data[i] = (UniChar16)arr[i];
	}
	return String(data.data(), 0, data.size());
}

void StreamReader::close()
{
	if (this->m_is != NULL){
		this->m_is->close();
	}
	this->m_is = NULL;
}



