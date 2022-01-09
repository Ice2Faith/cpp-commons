#ifndef _I2F_GBK_DICT_H_
#define _I2F_GBK_DICT_H_
/*  */
//GBK��GB2312����չ��Ҳ������GB2312�Ļ����������˲����ַ����룬ͬ���������ֽڴ洢���ģ����������壬��������š�������GB2312
//��GB18030�������ȫ�����ı��룬��Unicode��С����ƥ�䣬����2-4�ֽڻ�ϱ��룬2�ֽڲ��ּ���GBK��4�ֽڲ���Ϊ��չ��

//ӳ�������23988��ӳ�䣬���������ֲ��֣�������ASCII�ַ���
//Ҳ���ǲ�����<0x80���֣���һЩ��ΧҲ���ѿ�������һ���ֽ�Ϊ��ʹ��ASCII�������Ǻ���
//һ�±��У�����GBK�룺0xc4e3 ���֡��㡿 ��Ӧ��ASCII���б���Ϊ��0xc4 0xe3
//��˾�����룺
//gb-->unicode : unicode=codeMapGbk2Unicode[ֵ�±�][1];ֵ=(gb[i]<<8)|gb[i+1];
//unicode in 0x00a4-0xfffd
//gbk in 0x8140-0xfeff

//�ⲿ���ã�
unsigned short gbk2unicode(unsigned short gbkCode,unsigned short defVal);

unsigned short unicode2gbk(unsigned short unicodeCode,unsigned short defVal);


#endif // _I2F_GBK_DICT_H_