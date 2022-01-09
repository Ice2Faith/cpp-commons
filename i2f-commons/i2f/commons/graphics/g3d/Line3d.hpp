#ifndef _I2F_LINE3D_H_
#define _I2F_LINE3D_H_

#include"Point3d.hpp"
#include<math.h>

template<typename T>
class  Line3d
{
private:
	Point3d<T> m_from;
	Point3d<T> m_to;
public:
	Line3d();
	Line3d(const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2);
	Line3d(const Point3d<T> & sp, const Point3d<T> & ep);
	Line3d(const Line3d<T> & p);
	Line3d(Line3d<T> && p);
	virtual Line3d<T>& operator=(const Line3d<T>& p);
	virtual Line3d<T>& operator=(Line3d<T>&& p);
	virtual ~Line3d();
	virtual Point3d<T>& from();
	virtual Point3d<T>& to();
	virtual void from(const Point3d<T>& p);
	virtual void to(const Point3d<T>& p);
	virtual void set(const Line3d<T>& line);
	virtual void set(const Point3d<T> & sp, const Point3d<T> & ep);
	virtual void set(const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2);
	virtual T distance();
};

typedef Line3d<int> LineI3;
typedef Line3d<double> LineD3;

template<typename T>
Line3d<T>::Line3d()
{
}

template<typename T>
Line3d<T>::Line3d(const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2)
{
	this->m_from = Point3d<T>(x1, y1,z1);
	this->m_to = Point3d<T>(x2, y2,z2);
}

template<typename T>
Line3d<T>::Line3d(const Point3d<T> & sp, const Point3d<T> & ep)
{
	this->m_from = sp;
	this->m_to = ep;
}

template<typename T>
Line3d<T>::Line3d(const Line3d<T> & p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
}

template<typename T>
Line3d<T>::Line3d(Line3d<T> && p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
}

template<typename T>
Line3d<T>& Line3d<T>::operator=(const Line3d<T>& p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
	return *this;
}

template<typename T>
Line3d<T>& Line3d<T>::operator=(Line3d<T>&& p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
	return *this;
}

template<typename T>
Line3d<T>::~Line3d()
{
}

template<typename T>
Point3d<T>& Line3d<T>::from()
{
	return this->m_from;
}

template<typename T>
Point3d<T>& Line3d<T>::to()
{
	return this->m_to;
}

template<typename T>
void Line3d<T>::from(const Point3d<T>& p)
{
	this->m_from = p;
}

template<typename T>
void Line3d<T>::to(const Point3d<T>& p)
{
	this->m_to = p;
}

template<typename T>
void Line3d<T>::set(const Line3d<T>& p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
}

template<typename T>
void Line3d<T>::set(const Point3d<T> & sp, const Point3d<T> & ep)
{
	this->m_from = sp;
	this->m_to = ep;
}

template<typename T>
void Line3d<T>::set(const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2)
{
	this->m_from = Point3d<T>(x1, y1,z1);
	this->m_to = Point3d<T>(x2, y2,z2);
}

template<typename T>
T Line3d<T>::distance()
{
	return sqrt(pow((double)(this->m_to.x() - this->m_from.x()), 2.0) 
		+ pow((double)(this->m_to.y() - this->m_from.y()), 2.0)
		+ pow((double)(this->m_to.z() - this->m_from.z()), 2.0));
}

#endif // _I2F_LINE3D_H_
