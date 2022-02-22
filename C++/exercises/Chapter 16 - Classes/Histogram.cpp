/* (*2)  Define  a  class Histogram that  keeps  count  of  numbers  in  some  intervals  specified  as
arguments  to
Histogram
’s  constructor.  Provide  functions  to  print  out  the  histogram.  Handle
out-of-range values
*/

#include <iostream>
#include <vector>
#include <set>

class Histogram
{
    public:
        class BadHistogram {};
        struct Interval;
        struct Bin;
        // constructor takes list of intervals to be recorded
        Histogram(std::initializer_list<Interval> l);
    
        // record data in the histogram
        Histogram &record(std::initializer_list<int> d);
        // print the histogram
        std::ostream operator<<(Histogram h) const;
        
    private:
        // representation: vector of Bins, which contain the interval
        // and it's value (count)
        std::vector<Bin> data {};
        // keep track of which values are already represented by the
        // histogram, so as to disallow repeats
        std::set<int> used {};
        // keeep track of out of range values
        int out_of_range {};
};

struct Histogram::Interval
{
    int low, high;
};

struct Histogram::Bin
{
    int count;
    Interval inter;
};


Histogram::Histogram(std::initializer_list<Interval> intervals)
{
    // invariant: every number is represented by one and only one interval
    //            i.e. intervals cannot overlap
    
    for (Interval p : intervals)
    {
        // check if interval is a valid range (a < b)
        if (p.high < p.low)
            throw BadHistogram {};
        // check if any number in the interval is already represented
        for (int i = p.low; i <= p.high; i++)
        {
            // look through the represented values for a match
            auto search = used.find(i);
            // a match was found
            if (search != used.end())
                throw BadHistogram {};
        }
        // all good; push the interval and record the numbers represented
        data.push_back({0, p});
        for (int i = p.low; i <= p.high; i++)
            used.insert(i);
    }
}

Histogram &Histogram::record(std::initializer_list<int> d)
{
    bool is_represented; // records out of range values
    for (int x : d)
    {
        is_represented = false;
        // record x if it is represented in any intervals of the histogram
        for (Bin &b : data)
        {
            if (x >= b.inter.low && x <= b.inter.high)
            {
                is_represented = true;
                b.count++;
                break;
            }
        }
        if (!is_represented)
            out_of_range++;
    }
    return *this;
}

std::ostream &operator<<(Histogram h) const
{
    for (Bin b : data)
        os << b.inter.low << '-' << b.inter.high << ": " << b.count << '\n';
    if (out_of_range > 0)
        os << out_of_range << " value(s) were out of range and not recorded.\n";
    return os;
}

int main()
{
    Histogram h { {0,5}, {6,10}, {-1,15} };
    h.record({0,5,3,1,5,2,7,5,3,100});
    std::cout << h;
    return 0;
}