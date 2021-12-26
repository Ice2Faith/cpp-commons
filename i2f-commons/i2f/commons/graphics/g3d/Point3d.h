#ifndef _I2F_POINT3D_H_
#define _I2F_POINT3D_H_

template<typename T>
class  Point3d
{
private:
	T m_x;
	T m_y;
	T m_z;
public:
	Point3d();
	Point3d(const T& x, const T& y, const T& z);
	Point3d(const Point3d<T> & p);
	Point3d(Point3d<T> && p);
	virtual Point3d<T>& operator=(const Point3d<T>& p);
	virtual Point3d<T>& operator=(Point3d<T>&& p);
	virtual ~Point3d();
	virtual T& x();
	virtual T& y();
	virtual T& z();
	virtual void x(const T& x);
	virtual void y(const T& y);
	virtual void z(const T& z);
	virtual void set(const T& x, const T& y, const T& z);
	virtual void set(const Point3d<T>& p);
};

typedef Point3d<int> PointI3;
typedef Point3d<double> PointD3;

template<typename T>
Point3d<T>::Point3d()
{
}

template<typename T>
Point3d<T>::Point3d(const T& x, const T& y, const T& z)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
}

template<typename T>
Point3d<T>::Point3d(const Point3d<T> & p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	this->m_z = p.m_z;
}

template<typename T>
Point3d<T>::Point3d(Point3d<T> && p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	this->m_z = p.m_z;
}

template<typename T>
Point3d<T>& Point3d<T>::operator=(const Point3d<T>& p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	this->m_z = p.m_z;
	return *this;
}

template<typename T>
Point3d<T>& Point3d<T>::operator=(Point3d<T>&& p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	this->m_z = p.m_z;
	return *this;
}

template<typename T>
Point3d<T>::~Point3d()
{
}

template<typename T>
T& Point3d<T>::x()
{
	return this->m_x;
}

template<typename T>
T& Point3d<T>::y()
{
	return this->m_y;
}

template<typename T>
T& Point3d<T>::z()
{
	return this->m_z;
}

template<typename T>
void Point3d<T>::x(const T& x)
{
	this->m_x = x;
}

template<typename T>
void Point3d<T>::y(const T& y)
{
	this->m_y = y;
}

template<typename T>
void Point3d<T>::z(const T& z)
{
	this->m_z = z;
}

template<typename T>
void Point3d<T>::set(const T& x, const T& y, const T& z)
{
	this->m_x = x;
	this->m_y = y;
	this->m_z = z;
}

template<typename T>
void Point3d<T>::set(const Point3d<T>& p)
{
	this->m_x = p.m_x;
	this->m_y = p.m_y;
	this->m_z = p.m_z;
}


#endif // _I2F_POINT3D_H_
