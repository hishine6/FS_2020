#include "member.h"
#include "recfile.h"

Member::Member() {
	this->ID = "";
	this->Password = "";
	this->Name = "";
	this->Email = "";
	this->Address = "";
	fill(this->Birthday, this->Birthday + 10, 0);
	this->Class = 0;
	this->Level = '9';
}
Member::Member(const string _ID, const string _Password, const string _Name, const string _Email, const string _Address, const char _Birthday[10], const char _Class, const char _Level) {
	this->ID = _ID;
	this->Password = _Password;
	this->Name = _Name;
	this->Email = _Email;
	this->Address = _Address;
	for (int i = 0; i < 10; i++)
		this->Birthday[i] = _Birthday[i];
	this->Class = _Class;
	this->Level = _Level;
}
Member& Member::operator=(const Member& ref) {
	this->ID = ref.ID;
	this->Password = ref.Password;
	this->Name = ref.Name;
	this->Email = ref.Email;
	this->Address = ref.Address;
	for (int i = 0; i < 10; i++)
		this->Birthday[i] = ref.Birthday[i];
	this->Class = ref.Class;
	this->Level = ref.Level;
	return *this;
}
bool Member::operator==(const Member& ref) {
	return this->ID == ref.ID;
}
bool Member::operator!=(const Member& ref) {
	return this->ID != ref.ID;
}
bool Member::Check_Password(const string _Password) {
	return this->Password == _Password;
}
void Member::chg_ID(const string _ID) {
	this->ID = _ID;
}
void Member::chg_Password(const string _Password) {
	this->Password = _Password;
}
void Member::chg_Name(const string _Name) {
	this->Name = _Name;
}
void Member::chg_Email(const string _Email) {
	this->Email = _Email;
}
void Member::chg_Address(const string _Address) {
	this->Address = _Address;
}
void Member::chg_Birthday(const char _Birthday[10]) {
	for (int i = 0; i < 10; i++)
		this->Birthday[i] = _Birthday[i];
}
void Member::chg_Class(const char _Class) {
	Class = _Class;
}
void Member::chg_Level(const char _Level) {
	Level = _Level;
}
char Member::get_Level() {
	return this->Level;
}
istream& operator>>(istream& is, Member& m) {
	string temp;
	getline(is, m.ID, '|');
	if (m.ID.length() == 0) return is;

	getline(is, m.Password, '|');
	getline(is, m.Name, '|');
	getline(is, m.Email, '|');
	getline(is, m.Address, '|');
	getline(is, temp, '|');
	for (int i = 0; i < 10; i++)
		m.Birthday[i] = temp.at(i);
	getline(is, temp, '|');
	m.Class = temp.at(0);
	getline(is, temp);
	m.Level = temp.at(0);
	return is;
}
ostream& operator<<(ostream& os, Member& m) {
	if (m.ID.length() == 0) return os;

	os << "ID:\t\t"<<m.ID << endl;
	os << "Password:\t"<<m.Password << endl;
	os << "Name:\t\t"<<m.Name << endl;
	os << "E-mail:\t\t"<<m.Email << endl;
	os << "Address:\t"<<m.Address << endl;
	os << "Birthday:\t";
	for (int i = 0; i < 10; i++)
		os << m.Birthday[i];
	os << endl;
	os << "Class:\t\t" << m.Class << endl;
	os << "Level:\t\t" << m.Level << endl;
	return os;
}


bool Member::Pack(IOBuffer& Buffer)const {
	int numBytes;

	Buffer.Clear();
	string s_id = ID;
	string s_Password = Password;
	string s_Name = Name;
	string s_Email = Email;
	string s_Address = Address;
	string s_birthday(Birthday, 10);
	string s_Class;
	s_Class.push_back(Class);
	string s_Level;
	s_Level.push_back(Level);

	numBytes = Buffer.Pack(s_id.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Password.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Name.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Email.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Address.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_birthday.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Class.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Level.c_str());
	if (numBytes == -1)return false;

	return true;
}


bool Member::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];



	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	ID = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Password = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Name = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Email = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Address = buf;

	numBytes = Buffer.Unpack(Birthday, 10);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)	return false;
	Class = buf[0];

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1)return false;
	Level = buf[0];

	return true;
}

char* Member::Key() {
	key = ID;
	return (char*)(key.c_str());
}