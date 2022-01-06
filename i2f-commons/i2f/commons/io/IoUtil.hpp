#ifndef _I2F_IO_UTIL_H_
#define _I2F_IO_UTIL_H_

#include"InputStream.h"
#include"OutputStream.h"

class IoUtil
{
public:
	static void copyStream(InputStream& is, OutputStream& os){
		IoUtil::copyStream(is, os, 0, -1, true, true);
	}
	static void copyStream(InputStream& is, OutputStream& os,bool closeStream){
		IoUtil::copyStream(is, os, 0, -1,closeStream,closeStream);
	}
	static void copyStream(InputStream& is, OutputStream& os, long offset, long size,bool closeIs,bool closeOs){
		if (offset < 0){
			offset = 0;
		}
		Array<byte> buf(4096);
		int len = 0;
		while ((len = is.read(buf))>0){
			os.write(buf, 0, len);
		}

		if (closeIs){
			is.close();
		}
		if (closeOs){
			os.close();
		}
	}
};

#endif // _I2F_IO_UTIL_H_

