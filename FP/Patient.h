#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
namespace sdds {
	class Patient : public IOAble {
		char* p_name;
		int ohipNum;
		Ticket p_ticket;
		bool p_flag;
	public:
		Patient(int number = 0, bool flag = false);
		Patient& operator=(Patient& a) = delete;
		~Patient();
		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(bool foo);
		bool operator==(char a)const;
		bool operator==(const Patient& pat)const;
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};
}
#endif // !SDDS_PATIENT_H_
