namespace Chrono
{
    enum class Month {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, 
    nov, dec };
    class Date;
    
    bool is_date(int d, Month m, int y);
    bool is_leap(int y);
    
    bool operator==(const Date &a, const Date &b);
    bool operator!=(const Date &a, const Date &b);
    
    const Date default_date {1, Month::jan, 1970}; // the default date
    
    ostream &operator<<(ostream &os, const Date &d);
    istream &operator>>(istream &is, Date &d);
}

class Date
{
    public:
        // exception class
        class BadDate {};
        // constructors
        explicit Date(int d={}, int m={}, int y={});
        // getters
        int day() const;
        int month() const;
        int year() const;
        // modifying functions
        Date &add_day(int n);
        Date &add_month(int n);
        Date &add_year(int n);
    private:
        bool is_valid(); // does this Date represent a valid date
        int d, y;
        Month m;
}

Date::Date(int dd, int mm, int yy)
: d{dd}, m{mm}, y{yy}
{
    d = dd ? dd : default_date.day;
    m = mm ? mm : default_date.month;
    y = yy ? yy : default_date.year;
    if (!is_valid())
        throw BadDate {};
}

int Date::day() const
{
    return d;
}

Month Date::month() const
{
    return m;
}

int Date::year() const
{
    return y;
}

Date &Date::add_day(int n)
{
    // TODO:
}

Date &Date::add_month(int n)
{
    // TODO:
}

Date &Date::add_year(int n)
{
    // TODO:
}

bool Date::is_valid()
{
    return is_date(d, m, y);
}


bool Chrono::is_date(int d, Month m, int y)
// check if the day d exists in the month m
{
    int ndays;
    
    switch (m)
    {
        case Month::feb:
            ndays = 28+is_leap(y);
            break;
        case Month::apr: case Month::jun: case Month::sep: case Month::nov:
            ndays = 30;
            break;
        case Month::jan: case Month::mar: case Month::may: case Month::jul:
        case Month::aug: case Month::oct: case Month::dec:
            ndays = 31;
            break;
        default
            return false;
    }
    return d >= 1 && d <= ndays;
}

bool Chrono::is_leap(int y)
{
    if (y % 400)
        return true;
    if (y % 100)
        return false;
    if (y % 4)
        return false;
    return false;
}