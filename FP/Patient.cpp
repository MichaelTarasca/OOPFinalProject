#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"
using namespace std;
namespace sdds {
	Patient::Patient(int number, bool flag) : p_ticket(number) {
		p_flag = flag;
		p_name = nullptr;
		ohipNum = 0;
	}

	Patient::~Patient() {
		delete[] p_name;
		p_name = nullptr;
	}

	bool Patient::fileIO() const {
		return p_flag;
	}

	void Patient::fileIO(bool foo) {
		p_flag = foo;
	}

	bool Patient::operator==(char a) const {
		return a == type();
	}

	bool Patient::operator==(const Patient& pat)const {
		return this->type() == pat.type();
	}

	void Patient::setArrivalTime() {
		p_ticket.resetTime();
	}

	Patient::operator Time() const {
		return Time(p_ticket);
	}

	int Patient::number() const {
		return p_ticket.number();
	}

	std::ostream& Patient::csvWrite(ostream& ostr)const {
		ostr << type() << ',' << p_name << ',' << ohipNum << ',';
		p_ticket.csvWrite(ostr);
		return ostr;
	}

	std::istream& Patient::csvRead(std::istream& istr) {
		char temp[51];
		istr.get(temp, 51, ',');
		delete[] p_name;
		p_name = new char[strlen(temp) + 1];
		strcpy(p_name, temp);
		istr.ignore(1000, ',');
		istr >> ohipNum;
		istr.ignore(1000, ',');
		p_ticket.csvRead(istr);
		return istr;
	}

	std::ostream& Patient::write(std::ostream& ostr) const {
		ostr << p_ticket << endl;
		ostr << p_name << ", OHIP: " << ohipNum;
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr) {
		char temp[51];
		cout << "Name: ";
		istr.get(temp, 51, '\n');
		delete[] p_name;
		p_name = new char[strlen(temp) + 1];
		strcpy(p_name, temp);
		istr.ignore(1000, '\n');
		cout << "OHIP: ";
		istr >> ohipNum;
		if (ohipNum < 100000000 || ohipNum > 999999999) {
			do {
				ohipNum = getInt();
				if (ohipNum < 100000000 || ohipNum > 999999999) {
					cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
				}
			} while (ohipNum < 100000000 || ohipNum > 999999999);
		}
		return istr;
	}

}
