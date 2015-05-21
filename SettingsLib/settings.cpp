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

settings::param::param(const string & name, std::string value, const settings *parent) { 
    this->name = name;
    this->value = value;
    this->parent = const_cast<settings* const>(parent);;
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
settings::param & settings::param::operator=(char const * value) { 
     return this->operator=(std::string(value));
}

settings::param & settings::param::operator=(std::string const & value) {
    this->value = value;
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator=(int value) {
    stringstream temp;
    temp << value;
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator=(bool value) {
    ostringstream temp;
    temp << boolalpha << value;
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator=(double value) {
    ostringstream temp;
    temp << value;
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}
//------------------------------------------------------------------------
//+=
settings::param & settings::param::operator+=(std::string const & value) {
    this->value += value;
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator+=(int value) {
    stringstream temp;
    temp << (value + atoi(this->value.c_str()));
    this->value += temp.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator+=(double value) {
    stringstream temp;
    temp << atof(this->value.c_str()) + value;
    this->value += temp.str();
    parent->set(this->name, this->value);
    return *this;
}
//------------------------------------------------------------------------
//-=
settings::param & settings::param::operator-=(int value) {
    stringstream temp;
    temp << (atoi(this->value.c_str()) - value);
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator-=(double value) {
    stringstream temp;
    temp << atof(this->value.c_str()) - value;;
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}
//------------------------------------------------------------------------
//*=
settings::param & settings::param::operator*=(int value) {
    stringstream temp;
    temp << (atoi(this->value.c_str()) * value);
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator*=(double value) {
    stringstream temp;
    temp << atof(this->value.c_str()) * value;;
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}
//------------------------------------------------------------------------
// /=
settings::param & settings::param::operator/=(int value) {
    stringstream temp;
    temp << (atoi(this->value.c_str()) / value);
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator/=(double value) {
    stringstream temp;
    temp << atof(this->value.c_str()) / value;;
    this->value = temp.str();
    parent->set(this->name, this->value);
    return *this;
}
//------------------------------------------------------------------------
// | and &
settings::param & settings::param::operator|=(bool value) {
    bool temp = false;
    if (this->value != "true") temp =  true;
    temp |= value;
    string res = "false";
    if (temp) res = "true";
    this->value = temp;
    parent->set(this->name, this->value);
    return *this;
}

settings::param & settings::param::operator&=(bool value) {
    bool temp = false;
    if (this->value != "true") temp =  true;
    temp &= value;
    string res = "false";
    if (temp) res = "true";
    this->value = temp;
    parent->set(this->name, this->value);
    return *this;
}
//------------------------------------------------------------------------
const settings::param settings::operator[](std::string const & name) const {
    return param(name, this->pairs.find(name)->second, this);
}
settings::param settings::operator[](std::string const & name) {
    return param(name, this->pairs.find(name)->second, this);
}
int main(int argc, char* argv[])
{
        return 0;
}
