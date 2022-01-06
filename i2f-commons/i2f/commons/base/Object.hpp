#ifndef _I2F_OBJECT_H_
#define _I2F_OBJECT_H_

#include"String.hpp"
#include"../interface/IEquals.h"
#include"../interface/IHashcode.h"

class Object : virtual public IEquals, virtual public IHashcode
{
private:
    const static char * className;
public:
	virtual ~Object(){};
	template<typename T>
	virtual TString<T> toString() = 0;
	virtual bool equals(const IEquals& val) =0;
	virtual int hashcode() =0;
	virtual bool instanceof(Object obj);
	virtual const char* getClassName();
};

const Object::className="i2f.commons.base.Object";

bool Object::instanceof(Object obj)
{
    const char * objClassName=obj.getClassName();
    const char * thisClassName=this->getClassName();
    if(strcmp(objClassName,Object::className)==0){
        return true;
    }
    if(strcmp(objClassName,thisClassName)==0){
        return true;
    }
    return false;

}
const char* Object::getClassName()
{
    return Object::className;
}

#endif // _I2F_OBJECT_H_

