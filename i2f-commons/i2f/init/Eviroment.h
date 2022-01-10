#ifndef _I2F_ENVIROMENT_H_
#define _I2F_ENVIROMENT_H_
#include"../commons/codec/StringCodec.h"

class Eviroment
{
private:
	static int argc;
	static char ** argv;
	static StringCodec::Charset charset;
public:
	virtual ~Eviroment(){}
	Eviroment(){}
	static void defaultCharset(StringCodec::Charset charset);
	static StringCodec::Charset defaultCharset();
	static void cmdArgs(int argc, char * argv[]);
	static void exec(char * cmd);
};

#endif // _I2F_IUSTRING_H_