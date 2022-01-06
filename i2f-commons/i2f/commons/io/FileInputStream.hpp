#ifndef _I2F_FILE_INPUTSTREAM_H_
#define _I2F_FILE_INPUTSTREAM_H_

#include"InputStream.h"
#include<stdio.h>

class FileInputStream : virtual public InputStream
{
private:
	FILE * m_file;
public:
	FileInputStream(char * fileName)
	{
		this->m_file = NULL;
		this->m_file = fopen(fileName, "rb");
	}
	FileInputStream(FILE * pfile)
	{
		this->m_file = NULL;
		this->m_file = pfile;
	}
	FileInputStream(const FileInputStream& is)
	{
		this->close();
		this->m_file = is.m_file;
	}
	FileInputStream(FileInputStream&& is)
	{
		this->close();
		this->m_file = is.m_file;
		is.m_file = NULL;
	}
	FileInputStream& operator=(const FileInputStream & is)
	{
		this->close();
		this->m_file = is.m_file;
		return *this;
	}
	FileInputStream& operator=(FileInputStream && is)
	{
		this->close();
		this->m_file = is.m_file;
		is.m_file = NULL;
		return *this;
	}
	virtual ~FileInputStream()
	{

	}
	virtual int read()
	{
		byte bt = 0;
		int rdlen = fread(&bt, sizeof(bt), 1, this->m_file);
		if (rdlen <= 0){
			return -1;
		}
		return bt;
	}
	virtual int read(Array<byte>& buf)
	{
		int rdlen = fread(buf.data(), sizeof(byte), buf.size(), this->m_file);
		return rdlen;
	}
	virtual int read(Array<byte>& buf, int offset, int count)
	{
		int rdlen = fread(&buf[offset], sizeof(byte), count, this->m_file);
		return rdlen;
	}
	virtual void skip(long len)
	{
		for (long i = 0; i < len; i++){
			byte bt = 0;
			int rdlen = fread(&bt, sizeof(bt), 1, this->m_file);
			if (rdlen <= 0){
				break;
			}
		}
	}
	virtual void reset()
	{
		rewind(this->m_file);
	}
	virtual bool avaliable()
	{
		return this->m_file != NULL;
	}
	virtual void close()
	{
		if (this->m_file != NULL){
			fclose(this->m_file);
		}
		this->m_file = NULL;
	}
};

#endif // _I2F_FILE_INPUTSTREAM_H_
