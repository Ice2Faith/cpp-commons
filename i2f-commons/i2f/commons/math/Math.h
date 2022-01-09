#ifndef _I2F_MATH_H_
#define _I2F_MATH_H_

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

#endif // _I2F_MATH_H_
