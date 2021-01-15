#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "PreTriage.h"
#include "utils.h"
using namespace std;
namespace sdds {
	PreTriage::PreTriage(const char* dataFilename): m_averCovidWait(15), m_averTriageWait(5), m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit",  2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage() {
		ofstream myfile;
		myfile.open(m_dataFilename);
		myfile << m_averCovidWait << "," << m_averTriageWait << '\n';
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;
		for (int i = 0; i < m_lineupSize; i++) {
			m_lineup[i]->csvWrite(myfile);
			myfile << '\n';
			cout << i + 1 << "- ";
			m_lineup[i]->csvWrite(cout);
			cout << endl;
			delete m_lineup[i];
		}
		delete[] m_dataFilename;
		cout << "done!" << endl;
	}

	void PreTriage::run(void) {
		int choice = -1;
		while (choice != 0) {
			m_appMenu >> choice;
			switch (choice) {
			case 1:
				reg();
				break;
			case 2:
				admit();
				break;
			case 0: 
				break;
			}
		}
	}

	void PreTriage::reg() {
		Patient* p{};
		int option = 0;
		if (m_lineupSize >= 100) {
			cout << "Line up full!" << endl;
		}
		else {
			m_pMenu >> option;
			if (option == 1) {
				p = new CovidPatient();
			}
			else if (option == 2) {
				p = new TriagePatient();
			}
			else {
				return;
			}
			p->setArrivalTime();
			p->fileIO(false);
			cout << "Please enter patient information: " << endl;
			p->read(cin);

			cout << endl << "******************************************" << endl;
			p->write(cout);
			cout << "Estimated Wait Time: ";
			getWaitTime(*p).write(cout);
			cout << endl;
			cout << "******************************************" << endl << endl;
			m_lineup[m_lineupSize] = p;
			m_lineupSize++;
		}
	}

	void PreTriage::admit() {
		int choice = 0;
		int num = 0;
		m_pMenu >> choice;
		if (choice == 1) {
			num = indexOfFirstInLine('C');
			if (num == -1){}
			else {
				cout << endl << "******************************************" << endl;
				m_lineup[num]->fileIO(false);
				cout << "Calling for ";
				m_lineup[num]->write(cout);
				cout << "******************************************" << endl << endl;
				setAverageWaitTime(*m_lineup[num]);
				removePatientFromLineup(num);
			}
		}
		else if (choice == 2) {
			num = indexOfFirstInLine('T');
			if (num == -1) {}
			else {
				cout << endl << "******************************************" << endl;
				m_lineup[num]->fileIO(false);
				cout << "Calling for ";
				m_lineup[num]->write(cout);
				cout << "******************************************" << endl << endl;
				setAverageWaitTime(*m_lineup[num]);
				removePatientFromLineup(num);
			}
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p) const {
		int count = 0;
		for (int i = 0; i < m_lineupSize; i++) {
			if (m_lineup[i]->type() == p.type()) {
				count++;
			}
		}
		if (p.type() == 'T') {
			count *= (int)m_averTriageWait;
		}
		else {
			count *= (int)m_averCovidWait;
		}
		return Time(count);
	}

	void PreTriage::setAverageWaitTime(const Patient& p) {
		
		if (p.type() == 'T') {
			m_averTriageWait = ((Time().reset() - (Time)p) + ((int)m_averTriageWait * (p.number() - 1))) / p.number();
		}
		else {
			m_averCovidWait = ((Time().reset() - (Time)p) + ((int)m_averCovidWait * (p.number() - 1))) / p.number();
		}
	}

	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	void PreTriage::load() {
		Patient* p{};
		bool flag = true;
		char p_type = '\0';
		cout << "Loading data..." << endl;
		ifstream myfile;
		myfile.open(m_dataFilename);
		myfile >> m_averCovidWait;
		myfile.ignore();
		myfile >> m_averTriageWait;
		myfile.ignore(1000, '\n');

		for (int i = 0; i < maxNoOfPatients && flag == true; i++) {
			p_type = '\0';
			myfile.get(p_type);
			myfile.ignore();
			

			if (p_type == 'C') {
				p = new CovidPatient();
			}
			else if (p_type == 'T') {
				p = new TriagePatient();
			}
			else {
				flag = false;
			}
			if (flag == true) {
				p->fileIO(true);
				p->csvRead(myfile);
				p->fileIO(false);
				m_lineup[m_lineupSize] = p;
				m_lineupSize++;
			}
			if (p_type == 'C') {
				myfile.ignore(100, '\n');
			}
			if (m_lineupSize >= 100) {
				cout << "Warning: number of records exceeded 100" << endl;
				flag = false;
			}
		}
		if (m_lineupSize == 0) {
			cout << "No data or bad data file!" << endl << endl;
		}
		else {
			cout << m_lineupSize << " Records imported..." << endl << endl;
		}
		myfile.close();
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		int index = -1;
		for (int i = 0; i < m_lineupSize && index == -1; i++) {
			if (m_lineup[i]->type() == type) {
				index = i;
			}
		}
		return index;
	}

}
