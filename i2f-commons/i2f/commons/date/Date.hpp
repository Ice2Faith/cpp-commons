#ifndef _I2F_DATE_H_
#define _I2F_DATE_H_

#include<time.h>
#include<stdlib.h>

class Date
{
private:
	time_t m_time;
	int m_year; //真实年份
	int m_month; //1-12
	int m_day; // 1-31
	int m_hour; // 0-23
	int m_minus; //0-59
	int m_second; // 0-59
	int m_millSecond; // std c not support
	int m_week; // 0-7 0 is sunday
public:
	Date(){
		this->m_time = ::time(NULL);
		this->localTime();
	}
	Date(long tm){
		this->m_time = tm;
		this->localTime();
	}
	Date(time_t tm){
		this->m_time = tm;
		this->localTime();
	}
	Date(const Date& date){
		this->m_time = date.m_time;
		this->localTime();
	}
	Date(Date&& date){
		this->m_time = date.m_time;
		this->localTime();
	}
	Date& operator=(const Date& date){
		this->m_time = date.m_time;
		this->localTime();
		return *this;
	}
	Date& operator=(Date&& date){
		this->m_time = date.m_time;
		this->localTime();
		return *this;
	}
	time_t apply(){
		struct tm * ptime = (struct tm *)malloc(sizeof(struct tm));
		ptime->tm_year = this->m_year - 1900;
		ptime->tm_mon = this->m_month - 1;
		ptime->tm_mday = this->m_day;
		ptime->tm_hour = this->m_hour;
		ptime->tm_min = this->m_minus;
		ptime->tm_sec = this->m_second;
		time_t ret = mktime(ptime);
		free(ptime);
		this->m_time = ret;
		localTime();
		return ret;
	}
	Date& inflate(struct tm * ptime){
		this->m_year = ptime->tm_year+1900;
		this->m_month = ptime->tm_mon+1;
		this->m_day = ptime->tm_mday;
		this->m_hour = ptime->tm_hour;
		this->m_minus = ptime->tm_min;
		this->m_second = ptime->tm_sec;
		this->m_week = ptime->tm_wday;
		this->m_millSecond = 0;
		return *this;
	}
	Date& localTime(){
		struct tm * ptime = localtime(&this->m_time);
		inflate(ptime);
		return *this;
	}
	Date& utcTime(){
		struct tm * ptime = gmtime(&this->m_time);
		inflate(ptime);
		return *this;
	}
	int year(){
		return this->m_year;
	}
	Date& year(int v){
		this->m_year = v;
		this->apply();
		return *this;
	}
	int month(){
		return this->m_month;
	}
	Date& month(int v){
		this->m_month = v;
		this->apply();
		return *this;
	}
	int day(){
		return this->m_day;
	}
	Date& day(int v){
		this->m_day = v;
		this->apply();
		return *this;
	}
	int hour(){
		return this->m_hour;
	}
	Date& hour(int v){
		this->m_hour = v;
		this->apply();
		return *this;
	}
	int minus(){
		return this->m_minus;
	}
	Date& minus(int v){
		this->m_minus = v;
		this->apply();
		return *this;
	}
	int second(){
		return this->m_second;
	}
	Date& second(int v){
		this->m_second = v;
		this->apply();
		return *this;
	}
	int week(){
		return this->m_week;
	}
	time_t time(){
		return this->m_time;
	}
	Date& time(time_t v){
		this->m_time = v;
		this->localTime();
		return *this;
	}
};


#endif // _I2F_DATE_H_