#include "game.h"

Game::Game() {
	fill(this->ID, this->ID + 8, 0);
	Title = "";
	fill(this->Release_date, this->Release_date + 10, 0);
	Developer = "";
	Platform = "";
	fill(this->Score, this->Score + 2, 0);
	fill(this->Price, this->Price + 3, 0);
}
Game::Game(const char _ID[8], const string _Title, const char _Release_date[10], const string _Developer, const string _Platform, const char _Score[2], const char _Price[3]) {
	for (int i = 0; i < 8; i++)
		this->ID[i] = _ID[i];
	this->Title = _Title;
	for (int i = 0; i < 10; i++)
		this->Release_date[i] = _Release_date[i];
	this->Developer = _Developer;
	this->Platform = _Platform;
	for (int i = 0; i < 2; i++)
		this->Score[i] = _Score[i];
	for (int i = 0; i < 3; i++)
		this->Price[i] = _Price[i];
}

Game& Game::operator=(const Game& ref) {
	for (int i = 0; i < 8; i++)
		this->ID[i] = ref.ID[i];
	this->Title = ref.Title;
	for (int i = 0; i < 10; i++)
		this->Release_date[i] = ref.Release_date[i];
	this->Developer = ref.Developer;
	this->Platform = ref.Platform;
	for (int i = 0; i < 2; i++)
		this->Score[i] = ref.Score[i];
	for (int i = 0; i < 3; i++)
		this->Price[i] = ref.Price[i];
	return *this;
}
bool Game::operator==(const Game& ref) {
	bool result = true;
	for (int i = 0; i < 8; i++)
		if (this->ID[i] != ref.ID[i])
			result = false;
	return result;
}
bool Game::operator!=(const Game& ref) {
	bool result = true;
	for (int i = 0; i < 8; i++)
		if (this->ID[i] != ref.ID[i])
			result = false;
	return !result;
}

void Game::chg_ID(const char _ID[8]) {
	for (int i = 0; i < 8; i++)
		this->ID[i] = _ID[i];
}
void Game::chg_Title(const string _Title) {
	this->Title = _Title;
}
void Game::chg_Release_date(const char _Release_date[10]) {
	for (int i = 0; i < 10; i++)
		this->Release_date[i] = _Release_date[i];
}
void Game::chg_Developer(const string _Developer) {
	this->Developer = _Developer;
}
void Game::chg_Platform(const string _Platform) {
	this->Platform = _Platform;
}
void Game::chg_Score(const char _Score[2]) {
	for (int i = 0; i < 2; i++)
		this->Score[i] = _Score[i];
}
void Game::chg_Price(const char _Price[3]) {
	for (int i = 0; i < 3; i++)
		this->Price[i] = _Price[i];
}
istream& operator>>(istream& is, Game& m) {
	string temp;
	getline(is, temp, '|');
	if (temp.length() == 0) return is;

	for (int i = 0; i < 8; i++)
		m.ID[i] = temp.at(i);
	getline(is, m.Title, '|');
	getline(is, temp, '|');
	for (int i = 0; i < 10; i++)
		m.Release_date[i] = temp.at(i);
	getline(is, m.Developer, '|');
	getline(is, m.Platform, '|');
	getline(is, temp, '|');
	for (int i = 0; i < 2; i++)
		m.Score[i] = temp.at(i);
	getline(is, temp);
	for (int i = 0; i < 3; i++)
		m.Price[i] = temp.at(i);

	return is;
}
ostream& operator<<(ostream& os, Game& m) {
	if (m.Title.length() == 0)	return os;

	os << "ID:\t\t";
	for (int i = 0; i < 8; i++)
		os << m.ID[i];
	os << endl;
	os << "Title:\t\t" << m.Title << endl;
	os << "Release_date:\t";
	for (int i = 0; i < 10; i++)
		os << m.Release_date[i];
	os << endl;
	os << "Developer:\t" << m.Developer << endl;
	os << "Platform:\t" << m.Platform << endl;
	os << "Score:\t\t";
	for (int i = 0; i < 2; i++)
		os << m.Score[i];
	os << endl;
	os << "Price:\t\t";
	for (int i = 0; i < 3; i++)
		os << m.Price[i];
	os << endl;

	return os;
}


bool Game::Pack(IOBuffer& Buffer)const {
	int numBytes;

	Buffer.Clear();

	string s_id(ID,8);
	string s_Title = Title;
	string s_RD(Release_date,10);
	string s_Developer = Developer;
	string s_Platform = Platform;
	string s_Score(Score,2);
	string s_Price(Price,3);

	numBytes = Buffer.Pack(s_id.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Title.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_RD.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Developer.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Platform.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Score.c_str());
	if (numBytes == -1) return false;

	numBytes = Buffer.Pack(s_Price.c_str());
	if (numBytes == -1) return false;

	return true;
}


bool Game::Unpack(IOBuffer& Buffer) {
	int numBytes;
	char buf[STDMAXBUF];

	numBytes = Buffer.Unpack(ID,8);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Title = buf;

	numBytes = Buffer.Unpack(Release_date,10);
	if (numBytes == -1) return false;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Developer = buf;

	numBytes = Buffer.Unpack(buf);
	if (numBytes == -1) return false;
	Platform = buf;

	numBytes = Buffer.Unpack(Score, 2);
	if (numBytes == -1)	return false;

	numBytes = Buffer.Unpack(Price,3);
	if (numBytes == -1)	return false;

	return true;
}