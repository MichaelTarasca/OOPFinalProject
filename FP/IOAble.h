#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_
#include <iostream>
#include <ostream>
using namespace std;
namespace sdds {
    class IOAble {
    public:
        virtual ostream& csvWrite(ostream& ostr)const = 0;
        virtual istream& csvRead(istream& istr) = 0;
        virtual ostream& write(ostream& ostr)const = 0;
        virtual istream& read(istream& istr) = 0;
        virtual ~IOAble();
    };
    ostream& operator<<(ostream& a, const IOAble& b);
    istream& operator>>(istream& a, IOAble& b);
}
#endif // !SDDS_IOABLE_H_
