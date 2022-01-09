#include"StringCodec.h"
#include"../io/InputStream.h"
#include"../base/String.hpp"
#include"Codec.h"
#include"../container/ArrayList.hpp"


Array<UniChar32> StringCodec::stringOf(InputStream& is, Charset charset)
{
	ArrayList<UniChar32> ret;
	Array<byte> buf(12);
	int len = 0;
	int idx = 0;
	int from = 0;
	while ((len = is.read(buf,idx,buf.size()-idx)) > 0){
		len += idx;
		from = 0;
		UniChar32 ch = 0;
		while (from < len){
			if (charset == ASCII){
				ch = 0;
				ch = buf[from++];
				ret.add(ch);
			}
			else if (charset == GBK){
				ch = 0;
				int ok = Codec::readNextGbkChar2UniChar32(buf.data(),len, &from, &ch);
				if (ok==1){
					ret.add(ch);
				}
				else if (ok == 0){
					break;
				}
				else{
					ch = buf[from++];
					ret.add(ch);
				}
			}
			else if (charset == UTF8){
				ch = 0;
				int ok = Codec::readNextUtf8Char2UniChar32(buf.data(),len, &from, &ch);
				if (ok==1){
					ret.add(ch);
				}
				else if (ok == 0){
					break;
				}
				else{
					ch = buf[from++];
					ret.add(ch);
				}
			}
		}
		if (from < len){
			int leftLen = len - from;
			for (int i = 0; i < leftLen; i++){
				buf[i] = buf[from+i];
			}
			idx = leftLen;
		}
		else{
			idx = 0;
		}
		for (int i = idx; i < buf.size(); i++){
			buf[i] = 0;
		}
	}
	Array<UniChar32> arr(ret.size());
	for (int i = 0; i < arr.size(); i++){
		arr[i] = ret.get(i);
	}
	return arr;
}

Array<byte> StringCodec::stringTo(Array<UniChar32>& str, Charset charset)
{
	ArrayList<byte> list(str.size());
	for (int i = 0; i < str.size(); i++){
		UniChar32 ch = str.get(i);
		if (charset == ASCII){
			if (ch < 0x80){
				list.add((byte)ch);
			}
			else if (ch < 0xff){
				list.add((byte)ch);
			}
			else if (ch < 0xffff){
				list.add((byte)((ch>>8)&0xff));
				list.add((byte)((ch ) & 0xff));
			}
			else if (ch <= 0xffffff){
				list.add((byte)((ch >> 16) & 0xff));
				list.add((byte)((ch >> 8) & 0xff));
				list.add((byte)((ch)& 0xff));
			}
			else{
				list.add((byte)((ch >> 24) & 0xff));
				list.add((byte)((ch >> 16) & 0xff));
				list.add((byte)((ch >> 8) & 0xff));
				list.add((byte)((ch)& 0xff));
			}
		}
		else if (charset == GBK){
			Array<byte> arr=Codec::writeUniChar32AsGbkChars(ch);
			list.addAll(arr.data(), arr.size());
		}
		else if (charset == UTF8){
			Array<byte> arr = Codec::writeUniChar32AsUtf8Chars(ch);
			list.addAll(arr.data(), arr.size());
		}
	}
	Array<byte> ret(list.size());
	for (int i = 0; i < ret.size(); i++){
		ret[i] = list.get(i);
	}
	return ret;
}


