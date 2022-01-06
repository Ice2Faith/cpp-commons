#ifndef _I2F_FILE_H_
#define _I2F_FILE_H_
#include"../container/Array.hpp"
#include"../container/ArrayList.hpp"
#include"../base/String.hpp"

class File
{
public:
    ~File(){};
    virtual bool exists() = 0;
    virtual bool isFile() = 0;
    virtual bool isDirectory() = 0;
    virtual Array<String> listFiles() = 0;
    virtual String name() = 0;
    virtual String path() = 0;
    virtual String absolutePath() = 0;
    virtual void mkdirs() = 0;
    virtual File parent() = 0;
    virtual String extension() = 0;
}

#endif // _I2F_FILE_H_