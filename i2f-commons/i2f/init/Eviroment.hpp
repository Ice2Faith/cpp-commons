#ifndef _I2F_ENVIROMENT_H_
#define _I2F_ENVIROMENT_H_
#include"../commons/base/Base.hpp"
#include"../commons/base/String.hpp"
#include<stdlib.h>

class Eviroment
{
private:
	static int argc;
	static char ** argv;
public:
	virtual ~Eviroment(){}
	Eviroment(){}
	static void cmdArgs(int argc, char * argv[]);
	static void exec(char * cmd);
};

int Eviroment::argc = 0;
char ** Eviroment::argv = NULL;

void Eviroment::cmdArgs(int argc, char * argv[])
{
	Eviroment::argc = argc;
	Eviroment::argv = argv;
}

void Eviroment::exec(char * cmd)
{
	system(cmd);
}

#endif // _I2F_IUSTRING_H_