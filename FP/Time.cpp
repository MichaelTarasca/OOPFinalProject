#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include "Time.h"
#include "utils.h"


namespace sdds {

    Time& Time::reset() {
        m_min = getTime();
        return *this;
    }

    Time::Time(unsigned int min) {
        m_min = min;
    }

    std::ostream& Time::write(std::ostream& ostr) const {
        return ostr << std::setw(2) << std::setfill('0') << m_min / 60 << ":" << std::setw(2) << std::setfill('0') << m_min - (m_min / 60) * 60;
    }

    std::istream& Time::read(std::istream& istr) {
        int hours = 0, min = 0;
        char col = '\0';
        istr >> hours >> col >> min;

        if (col != ':') {
            istr.setstate(std::ios::failbit);
        }
        else {
            m_min = hours * 60 + min;
        }
        return istr;
    }

    Time::operator int() const {
        return m_min;
    }

    Time& Time::operator*=(int val) {
        m_min *= val;
        return *this;
    }

    Time& Time::operator-=(const Time& D) {
        if (m_min < (unsigned)(int)D) {
            m_min = (m_min + 1440) - (int)D;
        }
        else {
            m_min -= (int)D;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& a, const Time& b) {
        b.write(a);
        return a;
    }

    std::istream& operator>>(std::istream& a, Time& b) {
        b.read(a);
        return a;
    }

    Time& Time::operator-(const Time& ROperand) {
        Time LOperand = *this;
        LOperand -= ROperand;
        *this = LOperand;
        return *this;
    }
}