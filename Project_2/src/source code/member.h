#ifndef MEMBER_H
#define MEMBER_H

#include"main.h"

class Member {
private:
	string ID;
	string Password;
	string Name;
	string Email;
	string Address;
	char Birthday[10];
	char Class;
	char Level;
	string key;

public:
	Member();
	Member(const string _ID, const string _Password, const string _Name, const string _Email, const string _Address, const char _Birthday[10], const char _Class,const char _Level);

	Member& operator=(const Member& ref);
	bool operator==(const Member& ref);
	bool operator!=(const Member& ref);

	bool Check_Password(const string _Password);
	char get_Level();

	void chg_ID(const string _ID);
	void chg_Password(const string _Password);
	void chg_Name(const string _Name);
	void chg_Email(const string _Email);
	void chg_Address(const string _Address);
	void chg_Birthday(const char _Birthday[10]);
	void chg_Class(const char _Class);
	void chg_Level(const char _Level);
	char* Key();

	friend istream& operator>>(istream& is, Member& m);
	friend ostream& operator<<(ostream& os, Member& m);

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer& Buffer);
};
istream& operator>>(istream& is, Member& m);
ostream& operator<<(ostream& os, Member& m);

#endif