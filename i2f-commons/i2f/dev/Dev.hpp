#ifndef _I2F_DEV_H_
#define _I2F_DEV_H_
/*
���½����κ����ã�
��������C++�н��п���ʱ��������Ĺ�ܺ�ָ��
�����������˼��ٵĻ������ݣ������ʹ�ã����Բο�i2f/base/String.hpp��ʵ��
*/

/*
���c++ͷ�ļ��Ĺ淶
һ��Ҫʹ�ú궨���ж���������ͷ�ļ�����֤����ͷ�ļ������includeҲ���ᵼ���ظ����������
��ȷʾ����
#ifndef _I2F_DEV_H_
#define _I2F_DEV_H_

#endif // _I2F_DEV_H_

��ͨ��.hͷ�ļ��У�ֻ�������������������������ʵ�ַ���.cpp��
���������ģ�������ģ�巽��������ֱ�ӷ���ͷ�ļ��У�����ͷ�ļ���׺Ϊ.hpp
*/


/*
ģ������������������ģ��
�����1��������������ģ��
class Dev<T>{};
�����2����Ȼ��ȷʹ����ģ��ؼ���template,���ǻ���������������ģ��
template<typename T>
class Dev<T>{};
��ȷ1��
template<typename T>
class Dev{};
ͬʱ��������ģ�巽������ģ���࣬ģ�����Ϳ��Բ�ֹһ��
���磺
template<typename T,typename E>
T add(T v1,E v2);
*/
template<typename T>
class Dev
{
public:
	//������������һ����һ��������������������֤�ڶ�̬ʱ�ܹ���ȷ�ͷ��ڴ�
	virtual ~Dev();
	//�����������������д�ķ�����һ��ʹ���麯��
	virtual T* data();
	//Ҳ���Զ��崿�麯�����������麯������Ϊ�����࣬����ʵ����
	virtual int size() = 0;
	//����һ��ģ�巽��������ʵ��
	virtual Dev<T>& add(int num,const Dev<T>& p);

};

/*
ģ�巽��������ʵ��
��Ҫע��ĵ㣺
ģ�巽������Ҫָ��ģ������
template<typename T>
ʹ�õ���ģ�������Ҫ��ģ������
Dev<T>&
ģ�����޶�����Ҫ��ģ������
Dev<T>::
*/
template<typename T>
Dev<T>& Dev<T>::add(int num, const Dev<T>& p)
{
	return *this;
}

/*
������������ǰ
���������ڶ�����໥ʹ�õ�ʱ��֤�����˳������
�����ģ���࣬��Ҫ����ĩ������
���磺
template<typename T>
class DevImpl;
*/
class DevImpl;

/*
��һ����������Ϊ�����һ����Ԫ����������ͨ����һ����
���Ҳ��ô����޶�����::,Ҳ���ô�friend�ؼ���
*/
DevImpl operator+(int num, const DevImpl& dev)
{
	DevImpl ret;
	ret.m_size = num + dev.m_size;
	return ret;
}

/*
c++�ļ̳��Ƕ�̳�
��Ҫע�⣺
�̳з�ʽ�������м̳С������̳С�˽�м̳�
ʾ���ֱ�Ϊ��
class DevImpl : public Dev<int>{};
class DevImpl : protected Dev<int>{};
class DevImpl : private Dev<int>{};
���һ�����̳�
�����������ԣ��ڶ�̳��У����ܻ���������ĺ������߱���
ʹ����̳�֮����Щ�����ĺ������������������ϲ�Ϊһ����������ô��⣩
���磺A->B A->C B,C->D ��ʱ��D�����ʹ����̳У���ô��D�У���������������A�ĸ���
��̳е�ʹ�ã�Ҳ�����ڼ̳�ʱ����virtual�ؼ���
ʾ����
class DevImpl : virtual public Dev<int>{};
����ģ��ļ̳�
���������ģ�壬�������ѡ��ָ��ģ�����ͣ��Ӷ����಻����ģ��
����Ҳ���Լ�����ģ����
ʾ����
����ֱ��ָ�����ͣ����಻��ģ��
class DevImpl : virtual public Dev<int>{};
����Ҳ��ģ�壺
template<typename T>
class DevImpl : virtual public Dev<T>{};
��̳�ʾ����
class IronMan : virtual public Man , virtual public Machine{};
��̳�ʱģ�壺
template<typename T,typename E>
class IronMan : virtual public Man<T> ,virtual public Animal<T> , virtial public Machine<E>{};
*/
class DevImpl : virtual public Dev<int>
{
private:
	//ʹ�� m_ ��ͷ�������ڲ�������������c++�в�����������ͺ�����ͬ��
	int * m_data;
	int m_size;
	//��̬������Ҫ�������ʼ��
	static int max_size;
public:
	DevImpl()
	{
		this->m_size = 0;
		this->m_data = 0;
	}
	DevImpl(int size)
	{
		this->m_size = size;
		//��c++�У���new������ʹ��delete�ͷţ���new[]��������delete[]�ͷ�
		//�������Ҫ��Ӧ�ϵ�
		this->m_data = new int[size];
	}
	//��ͨ��������
	DevImpl(const DevImpl& dev)
	{
		//��ͨ�������죬��ʾ��������dev�����ڹ����걾����֮�󣬻����������ط�ʹ��
		//��ˣ���Ҫ���ľ��ǿ�¡��һ��dev�Ķ��󣬲����޸�dev
		//���³����лᷢ����
		//DevImpl p1;
		//DevImpl p2(p1);
		//���Ƴ������
		this->m_size = dev.m_size;
		//�������ڴ���Ϊ����
		this->m_data = new int[dev.m_size];
		//��������
		for (int i = 0; i < dev.m_size; i++){
			this->m_data[i] = dev.m_data[i];
		}
	}
	//�ƶ���������
	DevImpl(DevImpl&& dev)
	{
		//�ƶ�����ĺ��壬��ʾ�����dev�������ڹ�����ϱ�����֮�󣬾ͻ��ͷŵ�
		//���ԣ����������������&&�����Ҳ���const
		//��ˣ���Ҫ���ľ��ǰ�dev�е��ڴ�ֱ������������dev���ڴ����
		//�����ͱ������������ڴ棬���������Ŀ���
		//���³����ᷢ����
		//DevImpl get(){return DevImpl();}
		//DevImpl p=get();
		//��ͨ�������ɻ��Ǹ���
		this->m_size = dev.m_size;
		//�ڴ�ֱ��������
		this->m_data = dev.m_data;
		//Ϊ�˱�֤dev�����ͷ��ܹ��������У���Ҫ��dev�Ϳ�
		dev.m_size = 0;
		dev.m_data = 0;
	}
	//��ͨ��ֵ
	DevImpl& operator=(const DevImpl& dev)
	{
		//������ͨ���죬���������Ǹ�ֵ����˱��������֮ǰ�Ѿ����ڴ��ˣ���Ҫ�ͷ�
		//���Ƴ������
		this->m_size = dev.m_size;
		//�ͷ�֮ǰ�����Ѿ�������ڴ�
		if (this->m_data != 0){
			delete[] this->m_data;
		}
		//�������ڴ���Ϊ����
		this->m_data = new int[dev.m_size];
		//��������
		for (int i = 0; i < dev.m_size; i++){
			this->m_data[i] = dev.m_data[i];
		}

	}
	//�ƶ���ֵ
	DevImpl& operator=(DevImpl&& dev)
	{
		//�����ƶ����죬Ҳ����Ҫ�ͷ�֮ǰ���ڴ�
		//��ͨ�������ɻ��Ǹ���
		this->m_size = dev.m_size;
		//�ͷ�֮ǰ�����Ѿ�������ڴ�
		if (this->m_data != 0){
			delete[] this->m_data;
		}
		//�ڴ�ֱ��������
		this->m_data = dev.m_data;
		//Ϊ�˱�֤dev�����ͷ��ܹ��������У���Ҫ��dev�Ϳ�
		dev.m_size = 0;
		dev.m_data = 0;
	}
	//����������������ǰ��
	DevImpl& operator++()
	{
		//������������ʾǰ�ã�Ҳ���ǣ� ++DevImpl;
		//�������㣬Ҳ�ͱ�ʾ�����ֵ���ܵ�Ӱ��
		//ǰ������ʱ���ȶԶ��������������ض�����
		this->m_size++;
		return *this;
	}
	//��������������������
	DevImpl operator++(int)
	{
		//����������ʾ���ã�Ҳ���ǣ� DevImpl++;
		//ͬ����Ӱ������ע�ⷵ��ֵ���ͺ�ǰ�ò�ͬ
		//��������ʱ���ȷ��ض���ĸ������ٶԶ���������
		DevImpl ret = *this;
		this->m_size++;
		return ret;
	}
	//�ӷ�����
	DevImpl operator+(int num)
	{
		//���ּӷ���ʾ�����龰�������Ͷ��� + �������͵ı���
		//��˴���������˵��Ӧ�ý����һ���µĶ��󣬶����ǲ����ӷ��ı����Ͷ������ı�
		//��˷���ֵ��һ���µĶ���
		//ͬʱ�����Ҳ�����Ǳ����͵Ķ���
		//��ʾ����Ӧ: DevImpl + int
		DevImpl ret;
		ret.m_size += num;
		return ret;
	}
	//�Լ�����
	DevImpl& operator+=(const DevImpl& dev)
	{
		//���ּӷ�����ʾ���Ǳ����Ͷ����������һ������
		//�����������˵�������������Ƿ����ı�ģ����ص�ҲӦ���Ǳ�����
		this->m_size += dev.m_size;
		return *this;
	}
	//��Ԫ�ӷ�����,��֮ǰǰ��ʵ���ˣ�ע�⿴
	friend DevImpl operator+(int num, const DevImpl& dev);
	//��ʿ����ת��
	operator int(){
		//���ֱ�ʾ������������ʽת��Ϊ��������
		//���ʾ���ͱ�ʾ������ʽת��Ϊint,����������ʹ��intһ��ʹ�ñ������
		//������Щ���ǺϷ��ģ�int p=DevImpl; p+=DevImpl; 1+DevImpl+1;
		return this->m_size;
	}
	virtual ~DevImpl()
	{
		//������������Ҫ���ж��Ƿ��Ѿ��ͷ�
		//Ҳ����˵���������ƶ���ʱ���Ѿ����Ϳ���
		if (this->m_data != 0){
			delete[] this->m_data;
		}
		this->m_data = 0;
		this->m_size = 0;
	}
	//ʵ�����Ѿ�ָ���˸�ģ������ͣ��������Ҳ��Ҫ��������
	//���������ڲ�ֱ��ʵ�ֺ�������Ϊ����ʵ��
	virtual int* data()
	{
		return this->m_data;
	}
	//���ڸ����еĴ��麯������Ҫ����������������һ�飬����ʵ�֣�����̳�֮��������Ϊ�Ǵ��麯��
	//������ʵ�֣�����໹�ǳ����࣬����ʵ����
	virtual int size();
};

//�������ʼ����̬����
int DevImpl::max_size = 100;

//������ʵ�ֺ���
int DevImpl::size()
{
	return this->m_size;
}


/*
˵�����˳����һ�£������Ҫʹ�ö�̬
һ��ʹ���������ͻ���ʹ��ָ��
������������Ϳ��е�����£��������������ͣ�������ʹ��ָ��
��ĳЩ�����£�ʹ���������Ϳ��ܵ����麯�����޷���ȷʶ�𣬵������л��߱���ʧ��

Dev<int>& p=DevImpl;
Dev<int>* p=new DevImpl;

���c++�е���������أ��Ҹ����Ľ�����
���������ȷ������������Ӧ�����壬��ô��������������
���������ȷ��⣬�򲻽�����ô����������ܵ���������֮��Ľ��

������������صģ����Բο������������͵İ�װ��i2f/commons/base/Base.hpp
*/


#endif // _I2F_DEV_H_

