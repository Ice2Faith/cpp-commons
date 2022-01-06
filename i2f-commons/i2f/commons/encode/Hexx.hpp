#ifndef _I2F_HEXX_H_
#define _I2F_HEXX_H_

#include"../container/Array.hpp"
#include"../container/ArrayList.hpp"

class Hexx
{
public:
	/*
	转换为目标进制，short值为-1时，表示小数点
	第一位为-1时，表示是一个负数
	转换自后，自行根据字符映射关系映射为字符即可
	*/
	static Array<short> toHex(double num, int base,int decimal)
	{
		ArrayList<short> hex;
		if (num < 0){
			num = 0.0 - num;
			hex.add(-1);
		}
		long inum = (long)num;
		double dnum = num - inum;
		
		if (base < 2)
		{
			base = 2;
		}
		if (decimal < 0){
			decimal = 0;
		}

		short temp[128] = { 0 };
		int ilen = 0;
		while (inum != 0){
			short pnum = inum%base;
			temp[ilen++] = pnum;
			inum = inum / base;
		}
		for (int i = ilen - 1; i >= 0; i--){
			hex.add(temp[i]);
		}
		if (ilen == 0){
			hex.add(0);
		}

		if (dnum != 0.0 && decimal>0){
			hex.add(-1);

			int i = 0;
			while (dnum != 0.0 && i < decimal){
				short pnum = (short)(dnum*base);
				hex.add(pnum);
				dnum = dnum*base - pnum;
				i++;
			}
		}
		
		Array<short> ret(hex.size());
		for (int i = 0; i < ret.size(); i++){
			ret[i] = hex.get(i);
		}

		return ret;
	}
	static double ofHex(Array<short>& hex, int base){
		if (hex.size() == 0){
			return 0;
		}
		if (base < 2){
			base = 2;
		}
		int flag = 1;
		int idx = 0;
		long inum = 0;
		double dnum = 0;
		bool processInum = true;
		double lbit = 1;
		while (idx < hex.size()){
			short pnum = hex.get(idx);
			if (idx == 0){
				if (pnum == -1){
					flag = -1;
					idx++;
					continue;
				}
			}
			if (pnum == -1){
				processInum = false;
				idx++;
				continue;
			}
			if (processInum){
				inum *= base;
				inum += pnum;
			}
			else{
				lbit *= base;
				dnum += pnum / lbit;
			}
			idx++;
		}
		return flag*(inum+dnum);
	}
	static Array<short> transform(Array<short>& hex, int srcBase, int dstBase){
		double num = Hexx::ofHex(hex, srcBase);
		Array<short> ret = Hexx::toHex(num, dstBase,10);
		return ret;
	}
};

class Hex36
{
public:
	static Array<char> toHex(double num, int base)
	{
		Array<short> cdata = Hexx::toHex(num, base, 10);
		char * map = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		Array<char> ret(cdata.size());
		for (int i = 0; i < cdata.size(); i++){
			if (i == 0){
				if (cdata[i] == -1){
					ret[i] = '-';
				}
				else{
					ret[i] = map[cdata[i]];
				}
			}
			else{
				if (cdata[i] == -1){
					ret[i] = '.';
				}
				else{
					ret[i] = map[cdata[i]];
				}
			}
		}
		ret.expand(1);
		ret[ret.size() - 1] = 0;
		return ret;
	}
	static double ofHex(Array<char>& arr, int base){
		char * map = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		Array<short> cdata(arr.size() - 1);
		for (int i = 0; i < cdata.size(); i++){
			if (arr[i] == '-' || arr[i] == '.'){
				cdata[i] = -1;
			}
			else{
				for (int j = 0; j < 32; j++){
					if (map[j] == arr[i]){
						cdata[i] = j;
						break;
					}
				}
			}
		}
		double num=Hexx::ofHex(cdata, base);
		return num;
	}
};

#endif // _I2F_HEXX_H_
