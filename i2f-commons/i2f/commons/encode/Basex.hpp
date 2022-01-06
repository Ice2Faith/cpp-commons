#ifndef _I2F_BASEX_H_
#define _I2F_BASEX_H_

#include"../base/Base.hpp"
#include"../container/Array.hpp"
#include"../container/ArrayList.hpp"

class Basex
{
public:
	
	/*
	������data����bitCountλ��bit���Ϊһ���µ������鷵��
	��bitCountֵΪ6ʱ��Ҳ����base64������򣬵�bitCountΪ8ʱ(��С��0�����8)���򲻴���ֱ�ӷ���
	���Ҫ�任Ϊbase64,��Խ�������ַ�ӳ�䣬�ٴ���һ�鼴��
	����bitCount=6
	��������ת����ϵ
	һ���ֽ�8bit
	3*8bit=4*6bit
	Ҳ����˵��3���ֽ�ת��Ϊ4���ֽ����
	ʾ����
	���룺1111-0000 1100-1100 0000-1111
	�����00-11-1100 00-00-1100 00-11-0000 00-00-1111
	���2bit��ԶΪ0��ʣ�µİ�˳����
	*/
	static Array<byte> encode( Array<byte>& data, int bitCount){
		ArrayList<byte> list;
		if (bitCount<=0 || bitCount>8){
			bitCount = 8;
		}
		if (bitCount == 8){
			return data;
		}
		int nbCount = 0;
		int pbCount = 0;
		for (int i = 1; i <= 8; i++){
			if ((bitCount*i) % 8 == 0){
				nbCount = i;
				break;
			}
		}
		pbCount = (bitCount*nbCount) / 8;
		//nbCount*bitCount=8*pbCount
		//һ�ε���pbCount�����ݣ�ת��ΪnbCount������
		int bitMask = 0;
		for (int i = 0; i < bitCount; i++){
			bitMask <<= 1;
			bitMask |= 1;
		}
		Array<byte> inBuf(pbCount);
		Array<byte> outBuf(nbCount);
		int idx = 0;
		while (idx < data.size()){
			for (int i = 0; i < outBuf.size(); i++){
				outBuf[i] = 0;
			}
			int rlen = 0;
			for (; rlen < inBuf.size() && idx+rlen<data.size(); rlen++){
				inBuf[rlen] = data[idx+rlen];
			}
			int trueLen = rlen;
			idx += rlen;
			if (rlen != inBuf.size())
			{
				for (; rlen < inBuf.size(); rlen++){
					inBuf[rlen] = 0;
				}
			}
			int rdIdx = 0;
			int wtIdx = 0;
			int rdUseBitCount = 0;

			while (rdIdx < inBuf.size()){
				byte bt = inBuf[rdIdx];
				int rdLeftBitCount = 8 - rdUseBitCount;
				if (rdLeftBitCount < bitCount){
					rdUseBitCount = bitCount - rdLeftBitCount;
					int rdMvBitCount = 8 - rdUseBitCount;
					byte bbt = inBuf[rdIdx];
					byte abt = inBuf[++rdIdx];
					int bfMask = 0;
					for (int i = 0; i < rdLeftBitCount; i++){
						bfMask <<= 1;
						bfMask |= 1;
					}
					int afMask = 0;
					for (int i = 0; i < rdUseBitCount; i++){
						afMask <<= 1;
						afMask |= 1;
					}

					byte sb = ((bbt&bfMask) << rdUseBitCount) | ((abt >> rdMvBitCount)&afMask);
					outBuf[wtIdx++]=sb;
				}
				else{
					int rmCount = rdLeftBitCount - bitCount;
					byte pt = bt;
					if (rmCount>0){
						pt = bt >> rmCount;
					}
					rdUseBitCount += bitCount;
					if (rdUseBitCount >= 8){
						rdIdx++;
						rdUseBitCount -= 8;
					}
					byte sb = pt&bitMask;
					outBuf[wtIdx++] = sb;
				}
			}
			for (int i = 0; i < outBuf.size(); i++){
				list.add(outBuf[i]);
			}
		}
		Array<byte> ret(list.size());
		for (int i = 0; i < list.size(); i++){
			ret[i] = list.get(i);
		}
		return ret;
	}

	/*
	��encode������
	*/
	static Array<byte> decode(Array<byte>& data, int bitCount)
	{
		ArrayList<byte> list;
		if (bitCount <= 0 || bitCount>8){
			bitCount = 8;
		}
		if (bitCount == 8){
			return data;
		}
		int nbCount = 0;
		int pbCount = 0;
		for (int i = 1; i <= 8; i++){
			if ((bitCount*i) % 8 == 0){
				nbCount = i;
				break;
			}
		}
		pbCount = (bitCount*nbCount) / 8;
		//nbCount*bitCount=8*pbCount
		//һ�ε���pbCount�����ݣ�ת��ΪnbCount������
		int bitMask = 0;
		for (int i = 0; i < bitCount; i++){
			bitMask <<= 1;
			bitMask |= 1;
		}
		Array<byte> inBuf(nbCount);
		Array<byte> outBuf(pbCount);
		int idx = 0;
		while (idx < data.size()){
			for (int i = 0; i < outBuf.size(); i++){
				outBuf[i] = 0;
			}
			int rlen = 0;
			for (; rlen < inBuf.size() && idx + rlen<data.size(); rlen++){
				inBuf[rlen] = data[idx + rlen];
			}
			int trueLen = rlen;
			idx += rlen;
			if (rlen != inBuf.size())
			{
				for (; rlen < inBuf.size(); rlen++){
					inBuf[rlen] = 0;
				}
			}
			int rdIdx = 0;
			int wtIdx = 0;
			int rdBitCount = 0;
			int wtBitCount = 0;
			byte wtBt = 0;

			while (rdIdx < inBuf.size()){
				byte bt = inBuf[rdIdx];
				int rdLeftBitCount = bitCount - rdBitCount;
				int pkBitCount = 8 - wtBitCount;
				if (rdLeftBitCount >= pkBitCount){
					int diffBitCount = rdLeftBitCount - pkBitCount;
					int pikMask = 0;
					for (int i = 0; i < pkBitCount; i++){
						pikMask <<= 1;
						pikMask |= 1;
					}
					rdBitCount += pkBitCount;
					if (rdBitCount >= bitCount){
						rdIdx++;
						rdBitCount -= bitCount;
					}
					if (diffBitCount>0){
						bt >>= diffBitCount;
					}
					wtBt <<= pkBitCount;
					wtBt |= (bt&pikMask);
					outBuf[wtIdx++] = wtBt;
					wtBt = 0;
					wtBitCount = 0;
				}
				else{
					int leftMask = 0;
					for (int i = 0; i < rdLeftBitCount; i++){
						leftMask <<= 1;
						leftMask |= 1;
					}
					wtBt <<= rdLeftBitCount;
					wtBt |= (bt&leftMask);
					rdIdx++;
					rdBitCount = 0;
					wtBitCount += rdLeftBitCount;
				}
			}
			for (int i = 0; i < outBuf.size(); i++){
				list.add(outBuf[i]);
			}
		}
		Array<byte> ret(list.size());
		for (int i = 0; i < list.size(); i++){
			ret[i] = list.get(i);
		}
		return ret;
	}
};

class Base64
{
public:
	static Array<char> encode(Array<byte>& data){
		char * map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
		return Base64::encode(data, map);
	}
	static Array<char> encode(Array<byte>& data,char * map){
		Array<byte> enc = Basex::encode(data, 6);
		Array<char> ret(enc.size() + 1);
		//ĩβ�����ݵ����Ⱥ�
		ret[enc.size()] = 0;
		bool isZero = true;
		for (int i = enc.size()-1; i >=0; i--){
			if (enc[i] == 0){
				if (isZero){
					ret[i] = '=';
					continue;
				}
			}
			ret[i] = map[enc[i]];
			isZero = false;
		}
		return ret;
	}
	static Array<byte> decode(Array<char>& data){
		char * map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
		return Base64::decode(data, map);
	}
	static Array<byte> decode(Array<char>& data,char * map){
		//ȥ��ĩβ���ĵȺ�
		int trueSize = data.size();
		for (int i = data.size()-1; i >= 0; i--){
			if (data[i] != '='){
				trueSize = i + 1;
				break;
			}
		}
		Array<byte> dec(trueSize - 2);
		for (int i = 0; i < trueSize - 2; i++){
			for (int j = 0; j < 64; j++){
				if (data[i] == map[j]){
					dec[i] = (byte)j;
					break;
				}
			}
		}
		Array<byte> ret = Basex::decode(dec, 6);
		return ret;
	}
};


#endif // _I2F_BASEX_H_
