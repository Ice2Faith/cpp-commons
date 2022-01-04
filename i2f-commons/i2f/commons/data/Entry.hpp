#ifndef _I2F_ENTRY_H_
#define _I2F_ENTRY_H_

template<typename T,typename E>
class Entry
{
private:
    T m_key;
    E m_val;
public:
    Entry();
    ~Entry();
    Entry(const T& k,const E& v);
    Entry(const Entry<T,E>& e);
    Entry(Entry<T,E> && e);
    Entry<T,E>& operator=(const Entry<T,E>& e);
    Entry<T,E>& operator=(Entry<T,E>&& e);
    T& key();
    void key(const T& k);
    E& val();
    void val(const E& v);
	T& gkey(){
		return this->m_key;
	}
	E& gval(){
		return this->m_val;
	}
};

template<typename T,typename E>
Entry<T,E>::Entry()
{

}

template<typename T,typename E>
Entry<T,E>::~Entry()
{

}

template<typename T,typename E>
Entry<T,E>::Entry(const T& k,const E& v)
{
    this->m_key=k;
    this->m_val=v;
}

template<typename T,typename E>
Entry<T,E>::Entry(const Entry<T,E>& e)
{
    this->m_key=e.m_key;
    this->m_val=e.m_val;
}

template<typename T,typename E>
Entry<T,E>::Entry(Entry<T,E> && e)
{
    this->m_key=e.m_key;
    this->m_val=e.m_val;
}

template<typename T,typename E>
Entry<T, E>& Entry<T, E>::operator=(const Entry<T, E>& e)
{
    this->m_key=e.m_key;
    this->m_val=e.m_val;
	return *this;
}

template<typename T,typename E>
Entry<T,E>& Entry<T,E>::operator=(Entry<T,E>&& e)
{
    this->m_key=e.m_key;
    this->m_val=e.m_val;
	return *this;
}

template<typename T,typename E>
T& Entry<T,E>::key()
{
    return this->m_key;
}

template<typename T,typename E>
void Entry<T,E>::key(const T& k)
{
    this->m_key=k;
}

template<typename T,typename E>
E& Entry<T,E>::val()
{
    return this->m_val;
}

template<typename T,typename E>
void Entry<T,E>::val(const E& v)
{
    this->m_val=v;
}

#endif // _I2F_ENTRY_H_