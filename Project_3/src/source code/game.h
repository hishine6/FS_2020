#ifndef GAME_H
#define GAME_H
#include"main.h"

class Game {
private:
	char ID[8];
	string Title;
	char Release_date[10];
	string Developer;
	string Platform;
	char Score[2];
	char Price[3];
	string key;

public:
	Game();
	Game(const char _ID[8], const string _Title, const char _Release_date[10], const  string _Developer, const string _Platform, const char _Score[2], const char _Price[3]);

	Game& operator=(const Game& ref);
	bool operator==(const Game& ref);
	bool operator!=(const Game& ref);

	void chg_ID(const char _ID[8]);
	void chg_Title(const string _Title);
	void chg_Release_date(const char _Release_date[10]);
	void chg_Developer(const string _Developer);
	void chg_Platform(const string _Platform);
	void chg_Score(const char _Score[2]);
	void chg_Price(const char _Price[3]);
	char* Key();

	friend istream& operator>>(istream& is, Game& m);
	friend ostream& operator<<(ostream& os, Game& m);

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer& Buffer);
};
istream& operator>>(istream& is, Game& m);
ostream& operator<<(ostream& os, Game& m);

#endif