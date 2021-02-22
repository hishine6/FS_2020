#include "main.h"

class Purchase {
private:
	char Purchase_ID[12];
	char Game_ID[8];
	string Member_ID;
	char Purchase_date[10];

public:
	Purchase();
	Purchase(const char _Purchase_ID[12], const char _Game_ID[8], const string _Member_ID, const char _Purchase_date[10]);

	Purchase& operator=(const Purchase& ref);
	bool operator==(const Purchase& ref);
	bool operator!=(const Purchase& ref);
	
	bool compare(const Purchase & ref);	//game id, member id로도 비교한다.
	void chg_Purchase_ID(const char _Purchase_ID[12]);
	void chg_Game_ID(const char _Game_ID[8]);
	void chg_Member_ID(const string _Member_ID);
	void chg_Purchase_date(const char _Purchase_date[10]);

	friend istream& operator>>(istream& is, Purchase& m);
	friend ostream& operator<<(ostream& os, Purchase& m);

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer& Buffer);
};
istream& operator>>(istream& is, Purchase& m);
ostream& operator<<(ostream& os, Purchase& m);