#include "settings.h"
settings::settings(std::string const & filename) {
    this->filename = filename;
    this->reload();
}

std::string const & settings::get(std::string const & name,
			std::string const & def) const {
    if (this->pairs.count(name) != 0)
        return this->pairs.find(name)->second;
    else
        return def;
}

void settings::set(std::string const & name, std::string const & value) {
    char* filenameCh = new char[filename.length()];
    strcpy(filenameCh, this->filename.c_str());
    std::ofstream(filenameCh, std::ofstream::trunc);
    this->pairs[name] = value;
    std::ofstream out(filenameCh);
    map<string, string>::iterator i;
    for(i = pairs.begin(); i != pairs.end(); i++) {
        out << (*i).first << endl;
        out << (*i).second << endl;
    }
    out.close();
    delete[] filenameCh;
}

void settings::reset() {
    this->pairs.clear();
    char* filenameCh = new char[filename.length()];
    strcpy(filenameCh, this->filename.c_str());
    std::ofstream(filenameCh, std::ofstream::trunc);
    delete[] filenameCh;
}

void settings::reload() {
    this->pairs.clear();
    string name, value;
    char *filenameCh = new char[this->filename.length()];
    strcpy(filenameCh, this->filename.c_str());
    std::ifstream in(filenameCh);
    while (getline(in, name)) {
        getline(in, value);
        this->pairs[name] = value;
    }
    in.close();
    delete[] filenameCh;
}

//----------------------------------------------------------------------
//cast


settings::param::operator std::string() const {
    return this->value;
}
settings::param::operator bool() const {
    return this->value == "true";
}
settings::param::operator int() const {
    return atoi(value.c_str());
}
settings::param::operator double() const {
     return atof(value.c_str());
}
//-----------------------------------------------------------------------
// =
settings::param & settings::param::operator=(std::string const & value) {
    this->value = value;
    return *this;
}

settings::param & settings::param::operator=(int value) {
    stringstream temp;
    temp << value;
    this->value = temp.str();
    return *this;
}

settings::param & settings::param::operator=(bool value) {
    stringstream temp;
    temp << boolalpha << value;
    this->value = temp.str();
    return *this;
}

settings::param & settings::param::operator=(double value) {
    stringstream temp;
    temp << value;
    this->value = temp.str();
    return *this;
}
//------------------------------------------------------------------------
//+=

//------------------------------------------------------------------------
int main(int argc, char* argv[])
{
        return 0;
}
