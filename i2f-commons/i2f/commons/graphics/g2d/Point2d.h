#ifndef _I2F_POINT2D_H_
#define _I2F_POINT2D_H_

template<typename T>
class  Point2d
{
private:
	T m_x;
	T m_y;
public:
	Point2d();
	Point2d(const T& x,const T& y);
	Point2d(const Point2d<T> & p);
	Point2d(Point2d<T> && p);
	virtual Point2d<T>& operator=(const Point2d<T>& p);
	virtual Point2d<T>& operator=(Point2d<T>&& p);
	virtual ~Point2d();
	virtual T& x();
	virtual T& y();
	virtual void x(const T& x);
	virtual void y(const T& y);
	virtual void set(const T& x, const T& y);
	virtual void set(const Point2d<T>& p);
};

typedef Point2d<int> PointI;
typedef Point2d<double> PointD;

template<typename T>
Point2d<T>::Point2d()
{
}

template<typename T>
Point2d<T>::Point2d(const T& x, const T& y)
{
	this->m_x = x;
	this->m_y = y;
}

template<typename T>
Point2d<T>::Point2d(const Point2d<T> & p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
}

template<typename T>
Point2d<T>::Point2d(Point2d<T> && p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
}

template<typename T>
Point2d<T>& Point2d<T>::operator=(const Point2d<T>& p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	return *this;
}

template<typename T>
Point2d<T>& Point2d<T>::operator=(Point2d<T>&& p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	return *this;
}

template<typename T>
Point2d<T>::~Point2d()
{
}

template<typename T>
T& Point2d<T>::x()
{
	return this->m_x;
}

template<typename T>
T& Point2d<T>::y()
{
	return this->m_y;
}

template<typename T>
void Point2d<T>::x(const T& x)
{
	this->m_x = x;
}

template<typename T>
void Point2d<T>::y(const T& y)
{
	this->m_y = y;
}

template<typename T>
void Point2d<T>::set(const T& x, const T& y)
{
	this->m_x = x;
	this->m_y = y;
}

template<typename T>
void Point2d<T>::set(const Point2d<T>& p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
}


#endif // _I2F_POINT2D_H_
