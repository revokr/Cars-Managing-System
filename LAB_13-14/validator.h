#include "domain.h"


class Validator {
private:
	//vector<std::unique_ptr<actiune_undo>> undo_actions;
public:
	bool validate_string(const std::string& s) noexcept;
	string valideaza(Masina& m);
};