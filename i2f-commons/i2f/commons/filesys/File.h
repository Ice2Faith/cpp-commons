#ifndef _I2F_FILE_H_
#define _I2F_FILE_H_
#include"../container/Array.hpp"
#include"../container/ArrayList.hpp"
#include"../base/String.hpp"
#include"../date/Date.hpp"

class File
{
public:
    ~File(){};
	virtual File& of(String name) = 0;
    virtual bool exists() = 0;
    virtual bool isFile() = 0;
    virtual bool isDirectory() = 0;
    virtual Array<String> listFiles() = 0;
    virtual String name() = 0;
    virtual String path() = 0;
    virtual String absolutePath() = 0;
	virtual bool mkdir() = 0;
    virtual bool mkdirs() = 0;
    virtual String parent() = 0;
    virtual String extension() = 0;
	virtual bool renameTo(String name,bool overwrite) = 0;
	virtual bool remove() = 0;
	virtual bool copyTo(String name, bool overwrite) = 0;
	virtual long size() = 0;
	virtual bool create() = 0;
	virtual Date createTime() = 0;
	virtual Date lastModifyTime() = 0;
	virtual Date lastAccessTime() = 0;
}

#endif // _I2F_FILE_H_