#ifndef _I2F_MATH_H_
#define _I2F_MATH_H_

#include<math.h>
#include<stdlib.h>

class Math
{
public:
	static double pi();
	static double p180();
	static double a2r(double angle);
	static double r2a(double radian);
	static double angle2radian(double angle);
	static double radian2angle(double radian);
	static double randDouble();
	static int randInt(int max);
	static int randInt(int min, int max);
};

double Math::pi()
{
	return 3.141592653549626;
}
double Math::p180()
{
	return 180.0;
}
double Math::a2r(double angle)
{
	return Math::angle2radian(angle);
}
double Math::r2a(double radian)
{
	return Math::radian2angle(radian);
}
double Math::angle2radian(double angle)
{
	return angle / Math::p180()*Math::pi();
}
double Math::radian2angle(double radian)
{
	return radian / Math::pi()*Math::p180();
}

double Math::randDouble()
{
	int max = 0x7fff;
#ifdef RAND_MAX
	max = RAND_MAX;
#endif
	return (rand() % max)*1.0 / max;
}
int Math::randInt(int max)
{
	return rand() % max;
}
int Math::randInt(int min, int max)
{
	return rand() % (max - min) + min;
}
#endif // _I2F_MATH_H_
