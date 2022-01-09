#include"Math.h"

#include<math.h>
#include<stdlib.h>


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


