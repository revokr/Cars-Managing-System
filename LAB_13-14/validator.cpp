#include "exceptie.h"

bool Validator::validate_string(const std::string& s) noexcept {
    if (s.size() == 0)
        return false;
    for (const char c : s) {
        if (!isalpha(c) && !isspace(c) && !isdigit(c) && !(c == '_'))
            return false;
    }

    return true;
}

string Validator::valideaza(Masina& m) {
    std::string erori = "";
    if (!validate_string(m.get_nr()))
        erori.append("Numar invalid\n");
    if (!validate_string(m.get_producator()))
        erori.append("Producator invalid\n");
    if (!validate_string(m.get_model()))
        erori.append("Model invalid\n");
    if (!validate_string(m.get_tip()))
        erori.append("Tip invalid\n");
    if (erori.size() != 0)
        throw parcare_exception(erori);
    return erori;
}