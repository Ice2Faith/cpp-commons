# cpp-commons
cpp commons 
# what's this?
- a common package base on c++
- which try designed same as java to use c++ do develop
- but, more and more , you can learn c++ or java low level implement
# next step?
- try use unicode String instead all string
- design and implement multi-platform uniform interface
- try implement System.out System.in Scanner
- try implement Reader Writer
- powerful String with join,split format
- avoid diffirent platform differ, try add network,filesystem,thread
# features?
- InputStream,OutputStream
- FileInputStream,FileOutputStream
- ByteArrayInputStream,ByteArrayOutputStream
- Base64(Basex),Hex36(Hexx)
- Date
- List,ArrayList,LinkList
- Set,HashSet
- Map,HashMap
- Utf8,GBK,ASCII
- String
- Iterator,Iterable
- Closeable
- ...
# coding like?
- declare first
	- this demo code maybe will diffirent while new update was submitted.
## include like import
```c++
#include"i2f\commons\io\FileInputStream.hpp"
#include"i2f\commons\io\FileOutputStream.hpp"
#include"i2f\commons\io\IoUtil.hpp"
#include"i2f\commons\io\ByteArrayInputStream.hpp"
#include"i2f\commons\io\ByteArrayOutputStream.hpp"
#include"i2f\commons\date\Date.hpp"
#include"i2f\commons\codec\StringCodec.h"
```
## io stream
```c++
	char * isFile = "D:\\01test\\io\\src.txt";
	char * osFile = "D:\\01test\\io\\dst.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	ByteArrayOutputStream bos;
	IoUtil::copyStream(fis, bos);

	ByteArrayInputStream bis(bos.toByteArray());

	IoUtil::copyStream(bis, fos);
```
## charset & string & io stream
```c++
	char * isFile = "D:\\01test\\io\\src-gbk.txt";
	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	U32String ustr = StringCodec::stringOf(fis, StringCodec::GBK);
	Array<byte> data = StringCodec::stringTo(ustr, StringCodec::UTF8);

	fos.write(data);
	
	fis.close();
	fos.close();

	isFile = osFile;
	osFile = "D:\\01test\\io\\rec-gbk.txt";
	fis = FileInputStream(isFile);
	fos = FileOutputStream(osFile);

	system("cls");
	U32String ustr2 = StringCodec::stringOf(fis, StringCodec::UTF8);
	bool eq = ustr2.equals(ustr);
	Array<byte> data2 = StringCodec::stringTo(ustr2, StringCodec::GBK);

	fos.write(data2);

	fis.close();
	fos.close();
```
## date
```c++
	Date now;
	printf("%d-%d-%d %d:%d:%d week:%d\n", 
		now.year(), now.month(), now.day(), now.hour(), now.minus(), now.second(), now.week());
	now.day(now.day() + 1);
	printf("%d-%d-%d %d:%d:%d week:%d\n", 
		now.year(), now.month(), now.day(), now.hour(), now.minus(), now.second(), now.week());
```
# about me?
- I'm a develper , job with java
- but, some little tool perfer use c++
- however, I recoglized it's difficult for use c++, also it has STL
- maybe is my lazy
- so, I free time, this common package will be better
# updae log
- 2022-01-06 22:28
	- unicode,utf8,gbk tranform supported
	- and next, String will be base on unicode by UniChar32(unsigned int) instead of char*
	- at least,in this pkg , all string type will be u32
- more ...
