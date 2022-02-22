#include <iostream>
#include <string>

struct Date
{
    int year;
    int month;
    int day;
};

std::ostream &operator<<(std::ostream &os, Date d)
{
    return os << d.year << '/' << d.month << '/' << d.day;
}

std::istream& operator>>(std::istream& is, Date& d)
{
    int day;
    int month;
    int year;
    char slash;
    if(is>>day)
    {
        if(is>>slash && slash == '/')
        {
            if(is>>month)
            {
                if(is>>slash && slash == '/')
                {
                    if(is>>year)
                    {
                        d = {day, month, year};
                        return is;
                    }
                }
            }
        }

    }

    return is;
}

int main()
{
    Date today;
    std::cin >> today;
    std::cout << today;
    return 0;
}
