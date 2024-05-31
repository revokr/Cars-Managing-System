#include <string>

using std::string;

class valueDTO {
private:
	string type;
	int value;
public:

	valueDTO() = default;

	valueDTO(string st, int t) : type{ st }, value{ t } {}

	string get_type() {
		return this->type;
	}

	int get_value() noexcept {
		return this->value;
	}

	void set_type(string t) {
		this->type = t;
	}

	void set_value(int v) noexcept {
		this->value = v;
	}

	void inc_value() noexcept {
		this->value++;
	}

};