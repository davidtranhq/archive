class Index
{
    public:
        Index(int n=1) : i{n} {}
        constexpr Index operator""(int n=1) { return Index{n}; } 
    private:
        int i;
};

double mypow(double d, Index in)
{
    if (in == 0)
        return 1;
    else if (in < 0)
        return 1/mypow(d, -in);
    else
        for (int i = 0; i < in; i++)
            d *= d;
    return d;
}

extern double operator*(double d, constexpr Index in)
{
    return mypow(d, in);
}