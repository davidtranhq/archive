#include <iostream>

enum class Season
{
    spring,
    summer,
    autumn,
    winter
};

Season operator++(Season s)
{
    switch (s)
    {
        case Season::spring:
            return Season::summer;
            break;
        case Season::summer:
            return Season::autumn;
            break;
        case Season::autumn:
            return Season::winter;
            break;
        case Season::winter:
            return Season::spring;
            break;
    }
}

Season operator--(Season s)
{
    switch (s)
    {
        case Season::autumn:
            return Season::summer;
            break;
        case Season::winter:
            return Season::autumn;
            break;
        case Season::summer:
            return Season::spring;
            break;
        case Season::spring:
            return Season::winter;
            break;
    }
}

std::ostream &operator<<(std::ostream &os; Season s)
{
    switch (s)
    {
        case Season::autumn:
            return os << Season::autumn;
            break;
        case Season::winter:
            return os << Season::winter;
            break;
        case Season::summer:
            return os << Season::summer;
            break;
        case Season::spring:
            return o
            break;
    }
}

int main()
{
    return 0;
}