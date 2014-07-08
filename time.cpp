#include "time.hpp"

namespace tiempo
{

    date::date(int m, int d, int y, bool w) :
	day(d), month(m), year(y), week(w)
    {
	if (week) //This date should keep track of the day of the week
	    dow = (monad.days_away(*this) + monad.dow)%7;
    }

    date::date(int m, int d, int y, int wk) :
	day(d), month(m), year(y), dow(wk), week(true){}

    bool is_leap(int year)
    {
	if (year % 4 == 0)
	    if (year % 100 == 0)
		if (year % 400 == 0) return true;
		else return false;
	    else return true;
	else return false;
    }

    int date::cmp(const date& other) const
    {int x;
	if ((x = year-other.year) != 0)
	    return x;
	else if ((x = month-other.month) != 0)
	    return x;
	else
	    return day-other.day;
    }

    int date::dimf() const //days in month function
    {
	int x = dim[month-1];
	if (month==2 && is_leap(year)) x++;
	return x;
    }

    int date::end_month()
    {
	int d = dimf()-day+1;
	month++;
	day=1;
	return d;
    }

    int date::end_year()
    {
	int d = end_month();
	while(month<=12)
	{
	    d += dimf();
	    month++;
	}
	year++;
	month=1;
	return d;
    }


    int date::sub_da(date& early, const date& late)
    {int x=0;
	while (early.year < late.year)
	    x += early.end_year();
	while (early.month < late.month)
	    x += early.end_month();
	return x + late.day - early.day;
    }

    void date::reset()
    {
	while(day < 1 )
	{
	    --month;
	    if (month < 1)
	    {year--; month=12;}
	    day += dimf();
	}
	while(day > dimf())
	{
	    day -= dimf();
	    ++month;
	    if (month > 12)
	    {year++; month=1;}
	}
    }


    int date::days_away(const date& other) const
    {
	int c = cmp(other);
	if (c == 0) return 0;
	else
	{
	    int sign, x;
	    date early;
	    if (c>0)
	    {
		early = other;
		x = sub_da(early, *this);
		sign = -1;
	    }
	    else
	    {
		early = *this;
		x = sub_da(early, other);
		sign = 1;
	    }
	    return x * sign;
	}
    }

    date get_today()
    {
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	int m, d, y;
	m = now->tm_mon + 1;
	d = now->tm_mday;
	y = now->tm_year + 1900;
	return date(m, d, y);
    }
}

using namespace tiempo;
int main(int argc, char** argv)
{
/*
  date bday(2,7,1991);
  date today = get_day();
  TEST("I was born " << bday.days_away(today) << " days ago!");
*/

/*
  date boc(1, 1, 1901); //beginning of century

  boc.dow = (monad.dow + monad.days_away(boc))%7;

  date i = boc;

  if (i.dow != 0)
  i.shift(7-i.dow); //Make it Sunday

  date eoc(31, 12, 2000); //end of century

  int c=0;
  while (i <= eoc)
  {
  if (i.get_day() == 1)
  c++;
  i.shift(7); //Next Sunday
  }

  TEST(c);
*/
    //   test weekday() function and monad on todays date
    //tiempo::monad.dow = 0;
    tiempo::date tday = tiempo::get_today();
    tday.shift(6);
    TEST(tday.weekday() << tday);
    return 1;
}
