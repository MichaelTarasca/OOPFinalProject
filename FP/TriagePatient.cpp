#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TriagePatient.h"
using namespace std;
namespace sdds {
    int nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
        p_symptoms = nullptr;
        nextTriageTicket++;
    }

    char TriagePatient::type() const {
        return 'T';
    }

    std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const {
        Patient::csvWrite(ostr) << ',' << p_symptoms;
        return ostr;
    }

    std::istream& TriagePatient::csvRead(std::istream& istr) {
        char temp[511];
        delete[] p_symptoms;
        Patient::csvRead(istr);
        istr.ignore(1000, ',');
        istr.getline(temp, 511, '\n');
        //istr.clear(istream::eofbit | istream::failbit);
        p_symptoms = new char[strlen(temp) + 1];
        strcpy(p_symptoms, temp);
        nextTriageTicket = Patient::number() + 1;
        return istr;
    }

    std::ostream& TriagePatient::write(std::ostream& ostr) const {
        if (fileIO()) {
            csvWrite(ostr);
        }
        else {
            ostr << "TRIAGE" << endl;
            Patient::write(ostr) << endl;
            ostr << "Symptoms: " << p_symptoms << endl;
        }
        return ostr;
    }

    std::istream& TriagePatient::read(std::istream& istr) {
        if (fileIO()) {
            csvRead(istr);
        }
        else {
            char temp[511];
            delete[] p_symptoms;
            Patient::read(istr);
            istr.ignore(1000, '\n');
            cout << "Symptoms: ";
            istr.getline(temp, 511, '\n');
            p_symptoms = new char[strlen(temp) + 1];
            strcpy(p_symptoms, temp);
        }
        return istr;
    }

    TriagePatient::~TriagePatient() {
        delete[] p_symptoms;
        p_symptoms = nullptr;
    }

}