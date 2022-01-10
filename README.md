# cpp-commons
cpp commons 
# what's this?
- a common package base on c++
- which try designed same as java to use c++ do develop
- but, more and more , you can learn c++ or java low level implement
# updae log
- 2022-01-10 18:25
	- complete Unicode Enviroment support
	- add Chs and Enviroment class support inline Unicode String
	- add DataCodeConverter to support byte data and form of String byte data transform
- 2022-01-10 11:26
	- add ucode(\u3306) uricode(%3306) hexcode(0x3306) types string and normal string convert
	- implements of UcodeStringCodeConverter,UricodeStringCodeConverter,HexcodeStringCodeConverter
- 2022-01-09 23:56
	- add Reader/Writer and implements of StreamReader/StreamWriter support
	- fuck c++, why need .h .hpp .cpp 
	- It's possibly complie error of something was defined in ohter .obj file while I want include a file
	- so,I undertand it that what's is define that two types of declare explicit type's variable,method,class or template define(and it's template implements)
- 2022-01-08 14:49
	- add sort algorithm and order relative algo.
	- add bits operate support
	- add memory operate support
	- modify File interface
- 2022-01-08 00:28
	- module use unicode16 string as String(U16String)
	- extends String support Charset
	- string and bytes transform according to the charset which you set
	- add some algorithm , such find,sort
- 2022-01-06 22:28
	- unicode,utf8,gbk tranform supported
	- and next, String will be base on unicode by UniChar32(unsigned int) instead of char*
	- at least,in this pkg , all string type will be u32
- more ...
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
## inline unicode string
```c++
	Chs chs;
	UniChar16 ch=chs.charOf("好", StringCodec::GBK);
	String str = chs.strOf("你好呀，hello",StringCodec::GBK);

	int idx=str.indexOf(ch);

	int idx2 = str.indexOf(Chs::charOf("呀"));

	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileOutputStream fos(osFile);

	StreamWriter writer(&fos, StringCodec::UTF8);
	writer.writeLine(str);
	writer.write(ch);
	writer.close();

	getchar();
```
## ucode hexcode uricode convert
```c++
	char * isFile = "D:\\01test\\io\\src-ucode.txt";
	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	StreamReader reader(&fis, StringCodec::GBK);
	String str = reader.readAll();
	reader.close();

	UcodeStringCodeConverter<UniChar16> converter;
	//UricodeStringCodeConverter<UniChar16> converter;
	//HexcodeStringCodeConverter<UniChar16> converter;
	str=converter.stringOf(str);


	StreamWriter writer(&fos, StringCodec::UTF8);
	writer.write(str);
	writer.close();

	getchar();
```
## reader/writer
```c++
	char * isFile = "D:\\01test\\io\\src-gbk.txt";
	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	StreamReader reader(&fis, StringCodec::GBK);
	String str=reader.readAll();
	reader.close();

	StreamWriter writer(&fos, StringCodec::UTF8);
	writer.write(str);
	writer.close();

	getchar();
```
## algorithm
```c++
	int arr[] = {5,3,1,4,0,2};
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	AlgoSort<int> sorter;
	ArrayRandomAccessor<int> accessor(arr, arrSize);
	DefaultComparator<int> comparator;
	//sorter.heapSort(accessor, accessor.size(), comparator, false);
	//sorter.mergeSort(accessor, accessor.size(), comparator, false);
	sorter.quickSort(accessor, 0, arrSize - 1, comparator, false);



	AlgoFind<int> finder;
	int fexrs = finder.halfFindArray(arr, 2, 0, arrSize - 1);
	int fnexrs = finder.halfFindArray(arr, 6, 0, arrSize - 1);

	getchar();
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

