#ifndef SDDS_TRIAGE_H
#define SDDS_TIRAGE_H
#include <iostream>
#include "Patient.h"
namespace sdds {
    class TriagePatient : public Patient {
        char* p_symptoms;
    public:
        TriagePatient();
        char type()const;
        std::ostream& csvWrite(std::ostream& ostr)const;
        std::istream& csvRead(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
        ~TriagePatient();
    };

}
#endif // !SDDS_
