#include "purchase.h"

Purchase::Purchase() {
	fill(this->Purchase_ID, this->Purchase_ID + 12, -1);
	fill(this->Game_ID, this->Game_ID + 8, -1);
	this->Member_ID = "";
	fill(this->Purchase_date, this->Purchase_date + 10, -1);
}
Purchase::Purchase(const char _Purchase_ID[12], const char _Game_ID[8], const string _Member_ID, const char _Purchase_date[10]) {
	for (int i = 0; i < 12; i++)
		this->Purchase_ID[i] = _Purchase_ID[i];
	for (int i = 0; i < 8; i++)
		this->Game_ID[i] = _Game_ID[i];
	this->Member_ID = _Member_ID;
	for (int i = 0; i < 10; i++)
		this->Purchase_date[i] = _Purchase_date[i];
}

Purchase& Purchase::operator=(const Purchase& ref) {
	for (int i = 0; i < 12; i++)
		this->Purchase_ID[i] = ref.Purchase_ID[i];
	for (int i = 0; i < 8; i++)
		this->Game_ID[i] = ref.Game_ID[i];
	this->Member_ID = ref.Member_ID;
	for (int i = 0; i < 10; i++)
		this->Purchase_date[i] = ref.Purchase_date[i];
	return *this;
}
bool Purchase::operator==(const Purchase& ref) {
	bool result = true;
	for (int i = 0; i < 12; i++)
		if (this->Purchase_ID[i] != ref.Purchase_ID[i])
			result = false;

	return result;
}
bool Purchase::operator!=(const Purchase& ref) {
	bool result = true;
	for (int i = 0; i < 12; i++)
		if (this->Purchase_ID[i] != ref.Purchase_ID[i])
			result = false;
	return !result;
}
bool Purchase::compare_member(const string _Member_ID) {
	return this->Member_ID == _Member_ID;
}

bool Purchase::compare(const Purchase& ref) {
	bool result1 = true;
	bool result2 = true;
	bool result3 = true;

	for (int i = 0; i < 12; i++)
		if (this->Purchase_ID[i] != ref.Purchase_ID[i])
			result1 = false;
	for (int i = 0; i < 8; i++)
		if (this->Game_ID[i] != ref.Game_ID[i])
			result2 = false;
	if (this->Member_ID != ref.Member_ID)
		result3 = false;

	return (result1 || result2 || result3);
}

void Purchase::chg_Purchase_ID(const char _Purchase_ID[12]) {
	for (int i = 0; i < 12; i++)
		this->Purchase_ID[i] = _Purchase_ID[i];
}
void Purchase::chg_Game_ID(const char _Game_ID[8]) {
	for (int i = 0; i < 8; i++)
		this->Game_ID[i] = _Game_ID[i];
}
void Purchase::chg_Member_ID(const string _Member_ID) {
	this->Member_ID = _Member_ID;
}
void Purchase::chg_Purchase_date(const char _Purchase_date[10]) {
	for (int i = 0; i < 10; i++)
		this->Purchase_date[i] = _Purchase_date[i];
}

istream& operator>>(istream& is, Purchase& m) {
	string temp;
	getline(is, temp, '|');
	if (temp.length() == 0)	return is;

	for (int i = 0; i < 12; i++)
		m.Purchase_ID[i] = temp.at(i);
	getline(is, temp, '|');
	for (int i = 0; i < 8; i++)
		m.Game_ID[i] = temp.at(i);
	getline(is, m.Member_ID, '|');
	getline(is, temp);
	for (int i = 0; i < 10; i++)
		m.Purchase_date[i] = temp.at(i);

	return is;
}
ostream& operator<<(ostream& os, Purchase& m) {
	if (m.Member_ID.length() == 0)	return os;

	os << "Purchase_ID: \t";
	for (int i = 0; i < 12; i++)
		os << m.Purchase_ID[i];
	os << endl;
	os << "Game_ID:\t";
	for (int i = 0; i < 8; i++)
		os << m.Game_ID[i];
	os << endl;
	os << "Member_ID:\t"<<m.Member_ID << endl;
	os << "Purchase_Date:\t";
	for (int i = 0; i < 10; i++)
		os << m.Purchase_date[i];
	cout << endl;
	return os;
}

bool Purchase::Pack(IOBuffer& Buffer)const {
	int numBytes;

	Buffer.Clear();

	string s_Purchase_id(Purchase_ID, 12);
	string s_Game_id(Game_ID,8);
	string s_Member_id = Member_ID;
	string s_Purchase_date(Purchase_date, 10);

	numBytes = Buffer.Pack(s_Purchase_id.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Game_id.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Member_id.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Purchase_date.c_str());
	if (numBytes == -1) return false;

	return true;
}


bool Purchase::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(Purchase_ID,12);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(Game_ID, 8);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Member_ID = buf;

	numBytes = Buffer.Unpack(Purchase_date, 10);
	if (numBytes == -1) return false;

	return true;
}

char Purchase::Key() {
	key = Purchase_ID[0];
	return key;
}