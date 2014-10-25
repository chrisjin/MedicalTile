#include"amyPure.h"
#include<math.h>
#include<stdlib.h>
void amyDate::operator=(const char* str)
{
	int idate=atoi(str);
	int a1=idate%100;
	int a2=idate%10000;
	int a3=idate;
	this->day=a1;
	this->month=(a2-a1)/100;
	this->year=(a3-a2)/10000;
}
amyDate::amyDate(const char* str)
{
	int idate=atoi(str);
	int a1=idate%100;
	int a2=idate%10000;
	int a3=idate;
	this->day=a1;
	this->month=(a2-a1)/100;
	this->year=(a3-a2)/10000;

}
void amyTime::operator=(const char* str)
{
	double time=atof(str);
	int itime=(int)time;
	int a1=itime%100;
	int a2=itime%10000;
	int a3=itime;
	this->second=a1;
	this->minute=(a2-a1)/100;
	this->hour=(a3-a2)/10000;
}
void amyTime::operator+=(int sec)
{
	int newsec=this->second+=sec;
	int min=newsec/60;
	int res=newsec%60;
	this->second=res;

	int newmin=this->minute+=min;
	int hour=newmin/60;
	int minres=newmin%60;
	this->minute=minres;

	this->hour+=hour;
}
amyTime::amyTime(const char* str)
{
	double time=atof(str);
	int itime=(int)time;
	int a1=itime%100;
	int a2=itime%10000;
	int a3=itime;
	this->second=a1;
	this->minute=(a2-a1)/100;
	this->hour=(a3-a2)/10000;

}

bool operator<(amyDate& t1,amyDate& t2)
{
	if(t1.year<t2.year)
		return 1;
	else if(t1.year==t2.year)
	{
		if(t1.month<t2.month)
			return 1;
		else if(t1.month==t2.month)
		{
			if(t1.day<t2.day)
				return 1;
		}
	}
	return 0;
}

bool operator>(amyDate& t1,amyDate& t2)
{
	if(t1.year>t2.year)
		return 1;
	else if(t1.year==t2.year)
	{
		if(t1.month>t2.month)
			return 1;
		else if(t1.month==t2.month)
		{
			if(t1.day>t2.day)
				return 1;
		}
	}
	return 0;
}

bool operator<(amyTime& t1,amyTime& t2)
{
	if(t1.hour<t2.hour)
		return 1;
	else if(t1.hour==t2.hour)
	{
		if(t1.minute<t2.minute)
			return 1;
		else if(t1.minute==t2.minute)
		{
			if(t1.second<t2.second)
				return 1;
		}
	}
	return 0;
}
bool operator>(amyTime& t1,amyTime& t2)
{
	if(t1.hour>t2.hour)
		return 1;
	else if(t1.hour==t2.hour)
	{
		if(t1.minute>t2.minute)
			return 1;
		else if(t1.minute==t2.minute)
		{
			if(t1.second>t2.second)
				return 1;
		}
	}
	return 0;
}

bool operator==(amyDate& t1,amyDate& t2)
{
	if(t1.day==t2.day&&t1.month==t2.month&&t1.year==t2.year)
		return 1;
	else
		return 0;
}

bool operator==(amyTime& t1,amyTime& t2)
{
	if(t1.hour==t2.hour&&t1.minute==t2.minute&&t1.second==t2.second)
		return 1;
	else
		return 0;
}

amyRect::amyRect()
{

}

amyRect::amyRect(int xx,int yy,int awidth,int aheight):x(xx),y(yy),width(awidth),height(aheight)
{

}