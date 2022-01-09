#ifndef _I2F_GBK_DICT_H_
#define _I2F_GBK_DICT_H_
/*  */
//GBK是GB2312的拓展，也就是在GB2312的基础上增加了不少字符编码，同样是两个字节存储中文，包含【简繁体，大多数符号】，兼容GB2312
//而GB18030是最大最全的中文编码，和Unicode大小进行匹配，采用2-4字节混合编码，2字节部分兼容GBK，4字节部分为拓展码

//映射表，包含23988个映射，仅包含汉字部分，不包含ASCII字符，
//也就是不包含<0x80部分，由一些范围也不难看出，第一个字节为负使的ASCII串，就是汉字
//一下表中，例如GBK码：0xc4e3 表汉字【你】 对应在ASCII串中表现为：0xc4 0xe3
//因此具体代码：
//gb-->unicode : unicode=codeMapGbk2Unicode[值下标][1];值=(gb[i]<<8)|gb[i+1];
//unicode in 0x00a4-0xfffd
//gbk in 0x8140-0xfeff

//外部调用：
unsigned short gbk2unicode(unsigned short gbkCode,unsigned short defVal);

unsigned short unicode2gbk(unsigned short unicodeCode,unsigned short defVal);


#endif // _I2F_GBK_DICT_H_