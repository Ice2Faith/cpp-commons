#ifndef _I2F_LINE2D_H_
#define _I2F_LINE2D_H_

#include"Point2d.h"
#include<math.h>

template<typename T>
class  Line2d
{
private:
	Point2d<T> m_from;
	Point2d<T> m_to;
public:
	Line2d();
	Line2d(const T& x1, const T& y1,const T& x2,const T& y2);
	Line2d(const Point2d<T> & sp, const Point2d<T> & ep);
	Line2d(const Line2d<T> & p);
	Line2d(Line2d<T> && p);
	virtual Line2d<T>& operator=(const Line2d<T>& p);
	virtual Line2d<T>& operator=(Line2d<T>&& p);
	virtual ~Line2d();
	virtual Point2d<T>& from();
	virtual Point2d<T>& to();
	virtual void from(const Point2d<T>& p);
	virtual void to(const Point2d<T>& p);
	virtual void set(const Line2d<T>& line);
	virtual void set(const Point2d<T> & sp, const Point2d<T> & ep);
	virtual void set(const T& x1, const T& y1, const T& x2, const T& y2);
	virtual T distance();
};

typedef Line2d<int> LineI;
typedef Line2d<double> LineD;

template<typename T>
Line2d<T>::Line2d()
{
}

template<typename T>
Line2d<T>::Line2d(const T& x1, const T& y1, const T& x2, const T& y2)
{
	this->m_from = Point2d<T>(x1, y1);
	this->m_to = Point2d<T>(x2, y2);
}

template<typename T>
Line2d<T>::Line2d(const Point2d<T> & sp, const Point2d<T> & ep)
{
	this->m_from = sp;
	this->m_to = ep;
}

template<typename T>
Line2d<T>::Line2d(const Line2d<T> & p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
}

template<typename T>
Line2d<T>::Line2d(Line2d<T> && p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
}

template<typename T>
Line2d<T>& Line2d<T>::operator=(const Line2d<T>& p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
	return *this;
}

template<typename T>
Line2d<T>& Line2d<T>::operator=(Line2d<T>&& p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
	return *this;
}

template<typename T>
Line2d<T>::~Line2d()
{
}

template<typename T>
Point2d<T>& Line2d<T>::from()
{
	return this->m_from;
}

template<typename T>
Point2d<T>& Line2d<T>::to()
{
	return this->m_to;
}

template<typename T>
void Line2d<T>::from(const Point2d<T>& p)
{
	this->m_from = p;
}

template<typename T>
void Line2d<T>::to(const Point2d<T>& p)
{
	this->m_to = p;
}

template<typename T>
void Line2d<T>::set(const Line2d<T>& p)
{
	this->m_from = p.m_from;
	this->m_to = p.m_to;
}

template<typename T>
void Line2d<T>::set(const Point2d<T> & sp, const Point2d<T> & ep)
{
	this->m_from = sp;
	this->m_to = ep;
}

template<typename T>
void Line2d<T>::set(const T& x1, const T& y1, const T& x2, const T& y2)
{
	this->m_from = Point2d<T>(x1, y1);
	this->m_to = Point2d<T>(x2, y2);
}

template<typename T>
T Line2d<T>::distance()
{
	return sqrt(pow((double)(this->m_to.x() - this->m_from.x()), 2.0) + pow((double)(this->m_to.y() - this->m_from.y()), 2.0));
}

#endif // _I2F_LINE2D_H_
