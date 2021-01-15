#ifndef SDDS_TIME_H
#define SDDS_TIME_H
#include <iostream>
namespace sdds {
    class Time {
        unsigned int m_min;
    public:
        Time& reset();
        Time(unsigned int min = 0);
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
        operator int()const;
        Time& operator-(const Time& ROperand);
        Time& operator *= (int val);
        Time& operator-=(const Time& D);
    };
    std::ostream& operator<<(std::ostream& a, const Time& b);
    std::istream& operator>>(std::istream& a, Time& b);
}
#endif