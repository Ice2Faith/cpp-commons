#include<stdio.h>
#include"i2f\commons\base\Base.hpp"
#include"i2f\commons\container\MultiList.h"
#include"i2f\commons\container\ArrayList.hpp"
#include"i2f\commons\interface\IExecutor.h"
#include"i2f\commons\container\LinkList.hpp"
#include"i2f\commons\container\Array.hpp"
#include"i2f\commons\interface\impl\PrintExecutor.hpp"
#include"i2f\commons\algorithm\Function.hpp"
#include"i2f\commons\interface\impl\DefaultComparator.hpp"
#include"i2f\commons\container\Matrix2.hpp"
#include"i2f\commons\graphics\g2d\g2d.hpp"
#include"i2f\commons\graphics\g3d\g3d.hpp"
#include"i2f\commons\algorithm\Route.hpp"
#include"i2f\commons\codec\Codec.h"
#include"i2f\commons\base\String.hpp"
#include"i2f\commons\container\HashSet.hpp"
#include"i2f\commons\container\HashMap.h"
#include"i2f\commons\encode\Basex.hpp"
#include"i2f\commons\encode\Hexx.hpp"
#include"i2f\commons\io\FileInputStream.hpp"
#include"i2f\commons\io\FileOutputStream.hpp"
#include"i2f\commons\io\IoUtil.hpp"
#include"i2f\commons\io\ByteArrayInputStream.hpp"
#include"i2f\commons\io\ByteArrayOutputStream.hpp"
#include"i2f\commons\date\Date.hpp"
#include"i2f\commons\codec\StringCodec.h"
#include"i2f\commons\base\Memory.hpp"
#include"i2f\commons\io\StreamReader.h"
#include"i2f\commons\io\StreamWriter.h"
#include"i2f\commons\codec\UcodeStringCodeConverter.hpp"
#include"i2f\commons\codec\UricodeStringCodeConverter.hpp"
#include"i2f\commons\codec\HexcodeStringCodeConverter.hpp"
#include"i2f\commons\encode\UriByteDataConverter.hpp"
#include"i2f\commons\encode\HexByteDataConverter.hpp"
#include"i2f\commons\base\Chs.hpp"

void showList(IIterable<Base<int>>& list)
{
	list.each(PrintExecutor<Base<int>>(",%d"));
	printf("\n");
}

LinkList<Base<int>> getList()
{
	LinkList<Base<int>> ret;
	for (int i = 1; i < 20; i += i){
		ret.add((Base<int>)i);
	}
	return ret;
}

void showHashMap(IIterator<Entry<Base<int>, Base<int>>>* it){
	printf("{");
	while (it->hasNext()){
		Entry<Base<int>, Base<int>> e = it->next();
		printf("%d??%d,", (int)e.gkey(), (int)e.gval());
	}
	printf("}\n"); 
	delete it;
}

void showHashMap2(IIterator<Entry<AString, Integer>>* it){
	printf("{");
	while (it->hasNext()){
		Entry<AString, Integer> e = it->next();
		printf("%s??%d,", e.gkey().data(), (int)e.gval());
	}
	printf("}\n");
	delete it;
}

void testHashMap2()
{
	HashMap<AString, Integer> map;
	map.put(AString("jack"), Integer(1));
	map.put(AString("tom"), Integer(2));
	map.put(AString("aimy"), Integer(3));
	map.put(AString("alise"), Integer(4));
	map.put(AString("tom"), Integer(1));
	Integer val = map.get(AString("tom"));
	map.remove(AString("tom"));
	bool ex = map.contains(AString("tom"));
	showHashMap2(map.iterator());
}

void testHashMap1()
{
	HashMap<Base<int>, Base<int>> map;
	showHashMap(map.iterator());
	map.put(Base<int>(1), Base<int>(1));
	showHashMap(map.iterator());
	map.put(Base<int>(2), Base<int>(2));
	showHashMap(map.iterator());
	map.put(Base<int>(3), Base<int>(3));
	showHashMap(map.iterator());
	map.put(Base<int>(4), Base<int>(4));
	showHashMap(map.iterator());
	map.put(Base<int>(5), Base<int>(5));
	showHashMap(map.iterator());
	map.put(Base<int>(5), Base<int>(6));
	showHashMap(map.iterator());
	bool ex5 = map.contains(Base<int>(5));
	map.remove(Base<int>(5));
	showHashMap(map.iterator());
	ex5 = map.contains(Base<int>(5));
	bool ex6=map.contains(Base<int>(6));
	Base<int> b3=map.get(Base<int>(3));
	showHashMap(map.iterator());
}

void testBasex(){
	/*
	bitCount=6
	rv:11110000 11001100 00001111 01011010 10100101 00 00000000
	in:11110000 11001100 00001111 01011010 10100101
	ot:00111100 00001100 00110000 00001111 00010110 00101010 00010100 00000000
	bitCount=5
	rv:11110000 11001100 00001111 01011010 10100101
	in:11110000 11001100 00001111 01011010 10100101
	ot:00011110 00000011 00000110 00000000 00011110 00010110 00010101 00000101
	bitCount=3
	rv:11110000 11001100 00001111 01011010 10100101 00 000 000
	in:11110000 11001100 00001111 01011010 10100101
	ot:00000111 00000100 00000001 00000100 00000110 00000000 00000001 00000111 00000010 00000110 00000101 00000010 00000010 00000100 00000000 00000000
	*/
	Array<byte> in(5);
	in[0] = 0xf0;
	in[1] = 0xcc;
	in[2] = 0x0f;
	in[3] = 0x5a;
	in[4] = 0xa5;

	int bitCount = 5;

	Array<byte> out = Basex::encode(in, bitCount);

	ArrayList<char> vin=Memory::visualMemoryHex2(in.data(), in.size(), false);
	ArrayList<char> vout = Memory::visualMemoryHex2(out.data(), out.size(), false);

	

	Array<byte> rvo = Basex::decode(out, bitCount);
	ArrayList<char> vrvo = Memory::visualMemoryHex2(rvo.data(), rvo.size(), false);
	printf("rv:%s\n", vrvo.data());
	printf("in:%s\n", vin.data());
	printf("ot:%s\n", vout.data());

	Array<char> ech=Base64::encode(in);
	Array<byte> dch = Base64::decode(ech);
	printf("ech:%s\n", ech.data());
	ArrayList<char> vdch = Memory::visualMemoryHex2(dch.data(), dch.size(), false);
	printf("dch:%s\n", vdch.data());

}

void testHexx(){
	double num = (4.0/3);
	int base = 10;
	Array<char> hex = Hex36::toHex(num, base);
	printf("hx:%s\n", hex.data());
	double rnum = Hex36::ofHex(hex, base);
	printf("rn:%.10lf\n", rnum);
	printf("nm:%.10lf\n", num);

	getchar();
}

void testIo(){
	char * isFile = "D:\\01test\\io\\src.txt";
	char * osFile = "D:\\01test\\io\\dst.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	ByteArrayOutputStream bos;
	IoUtil::copyStream(fis, bos);

	ByteArrayInputStream bis(bos.toByteArray());

	IoUtil::copyStream(bis, fos);

	getchar();
}

void testDate()
{
	Date now;
	printf("%d-%d-%d %d:%d:%d week:%d\n", now.year(), now.month(), now.day(), now.hour(), now.minus(), now.second(), now.week());
	now.day(now.day() + 1);
	printf("%d-%d-%d %d:%d:%d week:%d\n", now.year(), now.month(), now.day(), now.hour(), now.minus(), now.second(), now.week());
	getchar();
}

void testGbk()
{
	char ch[] = { "?@" };
	ArrayList<char> arr = Memory::visualMemoryHex16(ch, 2, false);
	printf("%s\n", arr.data());

	int from = 0;
	UniChar32 u32 = 0;
	int ret=Codec::readNextGbkChar2UniChar32((byte *)ch,3, &from, &u32);

	arr = Memory::visualMemoryHex16(&u32, 4, true);
	printf("%s\n", arr.data());

	Array<byte> data=Codec::writeUniChar32AsUtf8Chars(u32);

	FileOutputStream fos("D:\\01test\\io\\utf8.txt");
	fos.write(data);
	fos.close();

	Array<byte> data1 = Codec::writeUniChar32AsGbkChars(u32);

	FileOutputStream fos1("D:\\01test\\io\\gbk.txt");
	fos1.write(data1);
	fos1.close();

	getchar();
}

void testUnicodeString()
{
	char * isFile = "D:\\01test\\io\\src-gbk.txt";
	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	Array<UniChar32> ustr = StringCodec::stringOf(fis, StringCodec::GBK);
	Array<byte> data = StringCodec::stringTo(ustr, StringCodec::UTF8);

	fos.write(data);
	
	fis.close();
	fos.close();

	isFile = osFile;
	osFile = "D:\\01test\\io\\rec-gbk.txt";
	fis = FileInputStream(isFile);
	fos = FileOutputStream(osFile);

	system("cls");
	Array<UniChar32> ustr2 = StringCodec::stringOf(fis, StringCodec::UTF8);
	//bool eq = ustr2.equals(ustr);
	Array<byte> data2 = StringCodec::stringTo(ustr2, StringCodec::GBK);

	fos.write(data2);

	fis.close();
	fos.close();

	getchar();
}

void testString()
{
	char p[] = { "nihao,Hello,???ã?hello" };
	String str;

	Array<byte> arr((byte*)p,(sizeof(p)/sizeof(p[0])));
	str.ofBytes(arr, StringCodec::GBK);

	Array<byte> rarr=str.toBytes(StringCodec::UTF8);

	bool eq = true;
	int i = 0;
	while (i < arr.size() && i < rarr.size()){
		if (arr[i] != rarr[i]){
			eq = false;
			break;
		}
		i++;
	}
	getchar();
}

void testFastEq()
{
	char str1[] = {"hello,call me god"};
	char str2[] = {"hello,call me god" };
	TBasicString<char> ins;
	int len = ins.slength(str1);
	bool eq=ins.sequal(str1, str2, len);
	printf("%d:%s\n",len,(eq?"true":"false"));

	getchar();
	
}

void testAlgo()
{
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
}

void testReaderWriter()
{
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
}

void testStringCodeConvert()
{
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
}

void testUriHexEncodeDecode()
{
	char * isFile = "D:\\01test\\io\\src-hexcode.txt";
	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileInputStream fis(isFile);
	FileOutputStream fos(osFile);

	StreamReader reader(&fis, StringCodec::GBK);
	String str = reader.readAll();
	reader.close();

	//UriByteDataConverter<UniChar16> conv;
	HexByteDataConverter<UniChar16> conv;

	Array<byte> data=conv.dataOf(str);

	str.ofBytes(data, StringCodec::UTF8);

	StreamWriter writer(&fos, StringCodec::UTF8);
	writer.write(str);
	writer.close();

	getchar();
}

void testSimpleTextEnv()
{
	Chs chs;
	UniChar16 ch=chs.charOf("??", StringCodec::GBK);
	String str = chs.strOf("????ѽ??hello",StringCodec::GBK);

	int idx=str.indexOf(ch);

	int idx2 = str.indexOf(Chs::charOf("ѽ"));

	char * osFile = "D:\\01test\\io\\dst-utf8.txt";
	FileOutputStream fos(osFile);

	StreamWriter writer(&fos, StringCodec::UTF8);
	writer.writeLine(str);
	writer.write(ch);
	writer.close();

	getchar();
}

int main()
{
	testSimpleTextEnv();

	testUriHexEncodeDecode();

	testStringCodeConvert();

	testReaderWriter();

	testAlgo();

	testFastEq();

	testString();

	testUnicodeString();

	testGbk();

	testDate();

	testIo();

	testHexx();

	testBasex();
	testHashMap2();
	testHashMap1();

	HashSet<Base<int>> set;
	set.put(Base<int>(1));
	set.put(Base<int>(2));
	set.put(Base<int>(3));
	set.put(Base<int>(4));
	set.put(Base<int>(3));
	set.put(Base<int>(3));
	set.put(Base<int>(1));

	bool ex1=set.contains(Base<int>(1));
	bool ex5 = set.contains(Base<int>(5));

	IIterator<Base<int>> * sit = set.iterator();
	while (sit->hasNext()){
		printf("%d->", (int)sit->get());
		sit->next();
	}
	delete sit;
	printf("\n");

	AString str("abc");
	AString rpstr = str * 3;
	 str = str + "bbb";
	AString tst = "aaa" + str;
	AString ist = 1788669 + tst;
	str=str.toUpper();
	str.append(str.isEmpty());
	str.append(str.size());
	str.append('A');
	str.append((byte)0x25);
	AString str3 = str + 12.125;
	printf("%s\n", (char*)str3);
	
	////11100100 10111000 10100101
	////100111000100101
	////100111000100101
	//byte buf[] = { 0xe4, 0xb8, 0xa5 };

	/*
	//????UTF???????ԣ??????????ѳ???32bit<6*6
	//11111110 10110101 10010101 10101010 10110000 10110011 10110111
	//               01   010101   101010   110000   110011   110111
	byte buf[] = {0xfe,0xb5,0x95,0xaa,0xb0,0xb3,0xb7};
	*/

	
	//??׼?UTF???????ԣ?????????31bit=5*6+1
	//11111101 10110101 10010101 10101010 10110000 10110011
	//      01   110101   010101   101010   110000   110011
	byte buf[] = {0xfd,0xb5,0x95,0xaa,0xb0,0xb3};
	
	int iti = 0x12345678;
	printf("%s\n", Memory::visualMemoryHex16(&iti, sizeof(iti), true).data());

	int idx = 0;
	UniChar32 c32=0;
	int ret = Codec::readNextUtf8Char2UniChar32(buf,sizeof(buf)/sizeof(buf[0]), &idx, &c32);

	UniChar32 pc32 = c32;
	for (int i = 0; i < 32; i++){
		printf("%d", (pc32 & 0x80000000) == 0 ? 0 : 1);
		pc32 <<= 1;
	}
	printf("\n");

	Array<byte> astr = Codec::writeUniChar32AsUtf8Chars(c32);
	for (int i = 0; i < astr.size(); i++){
		printf("%02x,", astr.get(i));
	}
	printf("\n");

	printf("isBigEndian:%d,isLittleEndian:%d\n", Memory::isBigEndian(), Memory::isLittleEndian());

	int map[][5] = {
		//a b c d e
		{ 0, 1, 0, 1, 0 }, //a
		{ 0, 0, 1, 0, 0 }, //b
		{ 0, 0, 0, 1, 1 }, //c
		{ 0, 1, 0, 0, 0 }, //d
		{ 0, 0, 1, 0, 0 }  //e
	};
	char* mapDict[] = { "A", "B", "C", "D", "E" };
	Matrix2<int> mtxp((int *)map, 5, 5);
	for (int i = 0; i < mtxp.height(); i++){
		for (int j = 0; j < mtxp.width(); j++){
			printf("%d,", mtxp.get(j, i));
		}
		printf("\n");
	}
	//A->E
	RouteResult result = Route::route(0, 4, mtxp);
	printf("A->E?ɴ??ԣ?%d\n" , result.isPass);
	if (result.isPass){
		printf("?ɴ????پ?????%d\n" , (result.route.size() - 2));
		printf("?ɴ?????·??Ϊ??");
		for (int i = 0; i < result.route.size(); i++)
		{
			int item = result.route.get(i);
			printf("->%s" ,mapDict[item]);
		}
	}

	PointI p21(1, 2);
	PointI p22(1, 7);
	PointD3 p31(1.0, 2.0, 3.0);
	PointD3 p32(4.0, 2.6, 7.0);

	LineI l2(p21, p22);
	LineD3 l3(p31, p32);

	int len2 = l2.distance();
	double len3 = l3.distance();

	Matrix2<int> mtx(10, 5);
	for (int i = 0; i < mtx.width(); i++){
		for (int j = 0; j < mtx.height(); j++){
			mtx.set(i,j, i*10+j);
		}
	}

	for (int i = 0; i < mtx.height(); i++){
		for (int j = 0; j < mtx.width(); j++){
			printf("%d,", mtx.get(j,i));
		}
		printf("\n");
	}

	Array<int> row = mtx.row(1);
	for (int i = 0; i < row.size(); i++){
		printf("%d,", row.get(i));
	}
	printf("\n");

	Array<int> col = mtx.col(1);
	for (int i = 0; i < col.size(); i++){
		printf("%d,", col.get(i));
	}
	printf("\n");


	Integer adv = 1 + Integer(2);
	adv = Integer(2) + 1;
	adv = 1 + 2;
	adv = Integer(1) + Base<int>(2);
	int i = 1;
	i += adv;

	bool rs = (1 == Integer(1)) && (Integer(1) == 1) && (Integer(1) == Integer(1));

	Byte ch = (byte)(int)(Integer)5<<2;

	LinkList<Base<int>> rcvlist = getList();
	showList(rcvlist);
	rcvlist.head2Tail();
	showList(rcvlist);
	rcvlist.tail2Head();
	showList(rcvlist);
	rcvlist.swapHeadTail();
	showList(rcvlist);

	int min=Function::min(rcvlist, DefaultComparator<Base<int>>());
	int max = Function::max(rcvlist, DefaultComparator<Base<int>>());
	int avg = Function::avg(rcvlist);
	int sum = Function::sum(rcvlist);

	Array<int> arr1(20);
	for (int i = 0; i < arr1.size(); i++){
		arr1[i] = i;
		arr1.set(i,i);
	}
	//showList(arr1);

	LinkList<Base<int>>& list = LinkList<Base<int>>();
	
	for (int i = 0; i < 10; i++){
		list.add((Base<int>)i);
	}

	LinkList<Base<int>> cplist = list;
	showList(cplist);

	ListIterator<Base<int>>* it = list.iterator();
	while (it->hasNext()){
		int val = it->get();
		printf("=>%d", val);
		if (val % 2){
			it->remove();
		}
		else{
			it->insert((Base<int>)99);
			it->next();
		}
		
	}
	printf("\n");

	showList(list);
	while (list.size()>5){
		int rv=list.remove(0);
		showList(list);
	}
	list.set(-1, (Base<int>)-1);
	showList(list);
	list.insert(0, (Base<int>)0);
	showList(list);
	list.clear();
	showList(list);

	Base<int> arr[] = { 1, 3, 5, 7, 9 };
	List<Base<int>>& list2 = LinkList<Base<int>>();
	list2.addAll(arr, sizeof(arr) / sizeof(arr[0]));
	showList(list2);

	list.addAll(list2, 2, -1);
	showList(list);

	int fst=list.removeFirst();
	showList(list);
	int lst=list.removeLast();
	showList(list);

	list.addFirst((Base<int>)11);
	showList(list);
	list.addLast((Base<int>)22);
	showList(list);

	list.enque((Base<int>)99);
	showList(list);
	int dq=list.deque();
	showList(list);

	int hd=list.head();
	showList(list);

	int tl=list.tail();
	showList(list);

	list.push((Base<int>)88);
	showList(list);
	int tp=list.top();
	showList(list);

	int pp=list.pop();
	showList(list);

	while (!list.isEmpty()){
		pp=list.pop();
		showList(list);
	}
	showList(list);
	getchar();
	return 0;
}