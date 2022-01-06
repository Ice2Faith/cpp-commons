#ifndef _I2F_FILE_OUTPUTSTREAM_H_
#define _I2F_FILE_OUTPUTSTREAM_H_

#include"OutputStream.h"
#include<stdio.h>

class FileOutputStream : virtual public OutputStream
{
private:
	FILE * m_file;
public:
	FileOutputStream(char * fileName)
	{
		this->m_file = NULL;
		this->m_file = fopen(fileName, "wb");
	}
	FileOutputStream(char * fileName,bool append)
	{
		this->m_file = NULL;
		if (append){
			this->m_file = fopen(fileName, "ab+");
		}
		else{
			this->m_file = fopen(fileName, "wb");
		}
	}
	FileOutputStream(FILE * pfile)
	{
		this->m_file = NULL;
		this->m_file = pfile;
	}
	FileOutputStream(const FileOutputStream & os)
	{
		this->close();
		this->m_file = os.m_file;
	}
	FileOutputStream(FileOutputStream&& os)
	{
		this->close();
		this->m_file = os.m_file;
		os.m_file = NULL;
	}
	FileOutputStream& operator=(const FileOutputStream & os)
	{
		this->close();
		this->m_file = os.m_file;
		return *this;
	}
	FileOutputStream& operator=(FileOutputStream && os)
	{
		this->close();
		this->m_file = os.m_file;
		os.m_file = NULL;
		return *this;
	}
	virtual ~FileOutputStream()
	{

	}
	virtual int write(int bt)
	{
		byte wbt = (byte)bt;
		int wtlen = fwrite(&wbt, sizeof(wbt), 1, this->m_file);
		return wtlen;
	}
	virtual int write(Array<byte>& buf)
	{
		int wtlen = fwrite(buf.data(), sizeof(byte), buf.size(), this->m_file);
		return wtlen;
	}
	virtual int write(Array<byte>& buf, int offset, int count)
	{
		int wtlen = fwrite(&buf[offset], sizeof(byte), count, this->m_file);
		return wtlen;
	}
	virtual void flush()
	{
		fflush(this->m_file);
	}
	virtual bool avaliable()
	{
		return this->m_file != NULL;
	}
	virtual void close()
	{
		if (this->m_file != NULL){
			fflush(this->m_file);
			fclose(this->m_file);
		}
		this->m_file = NULL;
	}
};

#endif // _I2F_FILE_OUTPUTSTREAM_H_