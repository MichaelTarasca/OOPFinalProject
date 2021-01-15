#include <iostream>
#include "IOAble.h"
using namespace std;
namespace sdds {
	IOAble::~IOAble() {

	}

	ostream& operator<<(ostream& a, const IOAble& b) {
		b.write(a);
		return a;
	}
	istream& operator>>(istream& a, IOAble& b) {
		b.read(a);
		return a;
	}
}