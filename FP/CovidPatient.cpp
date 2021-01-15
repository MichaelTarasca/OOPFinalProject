#include "CovidPatient.h"
using namespace std;
namespace sdds {
    int nextCovidTicket = 1;


    CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
        nextCovidTicket++;
    }

    char CovidPatient::type() const {
        return 'C';
    }

    std::ostream& CovidPatient::csvWrite(std::ostream& ostr) const {
        Patient::csvWrite(ostr);
        return ostr;
    }

    std::istream& CovidPatient::csvRead(std::istream& istr) {
        Patient::csvRead(istr);
        nextCovidTicket = Patient::number() + 1;
        return istr;
    }

    std::ostream& CovidPatient::write(std::ostream& ostr) const {
        if (fileIO()) {
            csvWrite(ostr);
        }
        else {
            ostr << "COVID TEST" << endl;
            Patient::write(ostr);
            ostr << endl;
        }
        return ostr;
    }

    std::istream& CovidPatient::read(std::istream& istr) {
        if (fileIO()) {
            csvRead(istr);
        }
        else {
            Patient::read(istr);
        }
        return istr;
    }

}

