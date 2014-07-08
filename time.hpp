#ifndef CORE_HPP
#define CORE_HPP

#include <iostream>
//#include <ctime>

#define TEST(msg) std::cout << "TEST: " << msg << std::endl;
#define ERROR(msg) std::cout << "ERROR: " << msg << std::endl;

namespace tiempo
{
    const int dim[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    const char* daysofweek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    bool is_leap(int year);

    class date
    {
	int day, month, year;

	int cmp(const date& other) const;

	int dimf() const; //days in month function

	int end_month();

	int end_year();

	static int sub_da(date& early, const date& late);

	void reset();

	bool week;

	date() {}

    public:

	int dow; //Day of week

	date(int m, int d, int y, bool w=true);

	date(int m, int d, int y, int wk);

	bool operator==(const date& other) const
	{return cmp(other) == 0;}

	bool operator<(const date& other) const
	{return cmp(other) < 0;}

	bool operator<=(const date& other) const
	{return cmp(other) <= 0;}

	friend std::ostream& operator<<(std::ostream& os, const date& d)
	{return os << d.month << "/" << d.day << "/" << d.year;}

	int days_away(const date& other) const;

	void shift(int d)
	{
	    day += d;
	    if (week)
		dow = (dow+d)%7; 
	    reset();
	}

	int get_day()
	{return day;}

	std::string weekday()
	{
	    if (week)
		return std::string(daysofweek[dow]);
	    else
		ERROR("This date is not set to keep track of the weekday.");
	}
    };

    const date monad(12, 1, 2013, 0);

    date get_today();
}

#endif
