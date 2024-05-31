#include "validator.h"

#include <string>

using std::string;

class parcare_exception {
	std::string mesaj;
public:
	parcare_exception(std::string m) : mesaj{ m } {

	}
	std::string get_mesaj() {
		return mesaj;
	}
};