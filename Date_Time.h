#ifndef Date_Time_h
#define Date_Time_h

#include <iostream>
#include <fstream>
#include <string>

class Date_Time{
public:
	int minutes;
	int hours;
	int day;
	int month;
	int year;

	Date_Time::Date_Time()
	{
	}

	Date_Time::Date_Time(int a, int b, int c, int d, int e)
	{
		minutes = a;
		hours = b;
		day = c;
		month = d;
		year = e;
	}

	void AddMinutes(int min)
	{
		minutes = minutes + min;
		if (minutes >= 60)
		{
			minutes = minutes - 60;
			hours++;
			if (hours >= 24)
			{
				hours = hours - 24;
				day++;
				if (day > 29 && month == Feb)
				{
					day = day-29;
					month++;
				}else if (day > 30 && month == Apr||month ==Jun||month ==Sept||month ==Nov)
				{
					day = day-30;
					month++;
				}else if(day > 31)
				{
					day = day-31;
					month++;
				}
				if (month > Dec)
				{
					month = Jan;
					year++;
				}
			}
		}
	}

	void toString()
	{
		cout<< hours << ":" << minutes << " "<< month << "/"<< day << "/"<< year << '\n';
	}
};

#endif

