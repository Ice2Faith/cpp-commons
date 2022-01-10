#include"Eviroment.h"
#include"../commons/base/Base.hpp"
#include"../commons/base/String.hpp"
#include<stdlib.h>
#include"../commons/codec/StringCodec.h"


int Eviroment::argc = 0;
char ** Eviroment::argv = NULL;
StringCodec::Charset Eviroment::charset = StringCodec::GBK;

void Eviroment::defaultCharset(StringCodec::Charset charset)
{
	Eviroment::charset = charset;
}

StringCodec::Charset Eviroment::defaultCharset()
{
	return Eviroment::charset;
}

void Eviroment::cmdArgs(int argc, char * argv[])
{
	Eviroment::argc = argc;
	Eviroment::argv = argv;
}

void Eviroment::exec(char * cmd)
{
	system(cmd);
}

