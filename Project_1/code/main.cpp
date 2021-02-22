#include "main.h"
#include "member.h"
#include "game.h"
#include "purchase.h"
#include<iostream>

using namespace std;


void print_menu() {
	cout << "+-----------Main Menu-----------+" << endl;
	cout << "| 1. showMember                 |" << endl;
	cout << "| 2. showGame                   |" << endl;
	cout << "| 3. showPurchase               |" << endl;
	cout << "| 4. MemberTest                 |" << endl;
	cout << "| 5. GameTest                   |" << endl;
	cout << "| 6. PurchaseTest               |" << endl;
	cout << "| 7. LecturePurchaseSystem      |" << endl;
	cout << "| 8. Exit                       |" << endl;
	cout << "+-------------------------------+" << endl;
	cout << "input the number of menu >>> ";
}
void showMember() {
	ifstream in("listOfMember.txt");
	if (in.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	Member temp;
	int n;
	in >> n;
	in.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int i = 0; i < 10; i++) {
		in >> temp;
		cout << temp;
		if(i!=9)
			cout << "+-------------------------------+" << endl;
	}
	in.close();
}
void showGame() {
	ifstream in("listOfGame.txt");
	if (in.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	Game temp;
	string n;
	getline(in, n);
	for (int i = 0; i < 10; i++) {
		in >> temp;
		cout << temp;
		if (i != 9)
			cout << "+-------------------------------+" << endl;
	}
	in.close();
}
void showPurchase() {
	ifstream in("listOfPurchase.txt");
	if (in.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	Purchase temp;
	string n;
	getline(in, n);
	for (int i = 0; i < 10; i++) {
		in >> temp;
		cout << temp;
		if (i != 9)
			cout << "+-------------------------------+" << endl;
	}
	in.close();
}
void MemberTest() {
	ifstream in("listOfMember.txt");
	if (in.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	int n;
	in >> n;
	in.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Member> MemberFile(buffer);

	char filename[20] = "fileOfMember.dat";
	MemberFile.Create(filename, ios::out | ios::trunc);
	
	for (int i = 0; i < n; i++) {
		Member s;
		in >> s;
		int recaddr;
		if ((recaddr = MemberFile.Write(s)) == -1)
			cout << "Write Error!" << endl;
		//else
		//	cout << "Write at " << recaddr << endl;
	}
	MemberFile.Close();
	in.close();

	MemberFile.Open(filename, ios::in);
	for (int i = 0; i < 10; i++) {
		Member s;
		MemberFile.Read(s);			
		cout << s;
		if (i != 9)
			cout << "+-------------------------------+" << endl;
	}
	MemberFile.Close();
}
void GameTest() {
	ifstream in("listOfGame.txt");
	if (in.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	int n;
	in >> n;
	in.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	char filename[20] = "fileOfGame.dat";
	GameFile.Create(filename, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Game s;
		in >> s;
		int recaddr;
		if ((recaddr = GameFile.Write(s)) == -1)
			cout << "Write Error!" << endl;
		//else
		//	cout << "Write at " << recaddr << endl;
	}
	GameFile.Close();
	in.close();

	GameFile.Open(filename, ios::in);
	for (int i = 0; i < 10; i++) {
		Game s;
		GameFile.Read(s);
		cout << s;
		if (i != 9)
			cout << "+-------------------------------+" << endl;
	}
	GameFile.Close();
}
void PurchaseTest() {
	ifstream in("listOfPurchase.txt");
	if (in.fail()) {
		cout << "File Open error!" << endl;
		return;
	}
	int n;
	in >> n;
	in.ignore(numeric_limits<streamsize>::max(), '\n');

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Purchase> PurchaseFile(buffer);

	char filename[20] = "fileOfPurchase.dat";
	PurchaseFile.Create(filename, ios::out | ios::trunc);
	for (int i = 0; i < n; i++) {
		Purchase s;
		in >> s;
		int recaddr;
		if ((recaddr = PurchaseFile.Write(s)) == -1)
			cout << "Write Error!" << endl;
	}
	PurchaseFile.Close();
	in.close();

	PurchaseFile.Open(filename, ios::in);
	for (int i = 0; i < 10; i++) {
		Purchase s;
		PurchaseFile.Read(s);
		cout << s;
		if (i != 9)
			cout << "+-------------------------------+" << endl;
	}
	PurchaseFile.Close();
}


void Member_manipulate(int n) {
	if (n == 1) {	//search
		string Target_ID;
		cout << "+---------Searching Member------+" << endl;
		cout << "input the ID of Member >>> ";
		cin >> Target_ID;

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Member> MemberFile(buffer);

		char filename[20] = "fileOfMember.dat";
		MemberFile.Open(filename, ios::in | ios::out);
		Member m;

		m.chg_ID(Target_ID);
		int address = MemberFile.Search(m);
		if (address == -1) {
			cout << "ERROR: No Member Found!" << endl;
		}
		else {
			MemberFile.Read(m, address);
			cout << m;
		}
		MemberFile.Close();
	}
	else if (n == 2) {	//insert
		string _ID;
		string _Password;
		string _Name;
		string _Email;
		string _Address;
		char _Birthday[10];
		char _Class;
		string temp;
		getline(cin, temp);
		cout << "+---------Inserting Member------+" << endl;
		cout << "input the ID of Member >>> ";
		getline(cin, _ID);

		cout << "input the Password of Member >>> ";
		getline(cin, _Password);
		
		cout << "input the Name of Member >>> ";
		getline(cin, _Name);
	
		cout << "input the E-mail of Member >>> ";
		getline(cin, _Email);
		
		cout << "input the Address of Member >>> ";
		getline(cin, _Address);
	
		cout << "input the Birthday of Member >>> ";
		getline(cin, temp);
		if (temp.length() != 10) {
			cout << "ERROR: Not Date Format" << endl;
			return;
		}
		for (int i = 0; i < 10; i++)
			_Birthday[i] = temp.at(i);
		cout << "input the Class of Member >>> ";
		cin >> _Class;
		

		Member m = Member(_ID,_Password,_Name,_Email,_Address,_Birthday,_Class);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Member> MemberFile(buffer);
		char filename[20] = "fileOfMember.dat";
		MemberFile.Open(filename, ios::in | ios::out);
		unsigned short total_l = MemberFile.Get_Packed_Length(m);
		if (MemberFile.Search(m) != -1) {
			MemberFile.Close();
			cout << "ERROR: ID Overlap" << endl;
			return;
		}
		MemberFile.Close();

		MemberFile.Open(filename, ios::in | ios::out);
		int before_addr=-1;
		int addr = MemberFile.show_Delete_first();
		//해당하는 주소의 길이, 다음 주소를 알아야 된다
		//만약 길이가 total_l보다 크다면 시작 주소에 write를 한다.
		//필요한 함수
		//1. 주소의 버퍼 길이를 읽어오는 함수
		//2. 주소의 다음 주소를 읽어오는 함수
		//3. 주소에 새로운 Record를 write하는 함수
		//4. 가용 리스트에 이전 과 다음을 이어주는 함수
		int flag = 0;
		while (addr != -1) {
			unsigned short s = MemberFile.Get_Buffer_Length(addr);
			int next = MemberFile.Get_Next_Addr(addr);
			if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
				flag = 1;
				MemberFile.Update(m, addr, s); //현 주소에 새 레코드 입력
				if (before_addr == -1) { // next를 header에 delete head로 넣어준다
					MemberFile.update_Delete_first(next);
				}
				else { //before_addr가 가리키는 곳에 next를 넣어준다.
					MemberFile.update_Deleted(before_addr, next);
				}
				break;
			}
			before_addr = addr;
			addr = next;
		}	

		if (flag == 0) { //뒤에 append 해야되는 경우
			MemberFile.Append(m);
		}
		MemberFile.Close();
		cout << "Insertion Complete!" << endl;
	}
	else if (n == 3) {	//delete
		string Target_ID;
		cout << "+----------Delete Member--------+" << endl;
		cout << "input the ID of Member >>> ";
		cin >> Target_ID;

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Member> MemberFile(buffer);

		char filename[20] = "fileOfMember.dat";
		MemberFile.Open(filename, ios::in | ios::out);
		Member m;

		m.chg_ID(Target_ID);
		int address = MemberFile.Search(m);
		if (address == -1) {
			cout << "ERROR: No Member Found!" << endl;
		}
		else {
			MemberFile.Delete(address);
			cout << "Deletion Complete!"<<endl;
		}
		MemberFile.Close();

		
		RecordFile <Purchase> PurchaseFile(buffer);
		strcpy(filename, "fileOfPurchase.dat");
		Purchase p = Purchase();
		p.chg_Member_ID(Target_ID);

		while (1) {
			PurchaseFile.Open(filename, ios::in | ios::out);
			int address = PurchaseFile.Search(p);
			if (address == -1) break;
			else PurchaseFile.Delete(address);
			PurchaseFile.Close();
		}

	}
	else {	//update
		string Target_ID;
		cout << "+----------Updating Member------+" << endl;
		cout << "input the ID of Member >>> ";
		cin >> Target_ID;

		
		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Member> MemberFile(buffer);

		char filename[20] = "fileOfMember.dat";
		MemberFile.Open(filename, ios::in | ios::out);
		Member m;

		m.chg_ID(Target_ID);
		int address = MemberFile.Search(m);
		if (address == -1) {
			cout << "ERROR: No Member Found!" << endl;
			MemberFile.Close();
			return;
		}
		else {
			MemberFile.Read(m, address);
		}
		MemberFile.Close();
		
		cout << "+-----------Select Field--------+" << endl;
		cout << "| 1.Password                    |" << endl;
		cout << "| 2.Name                        |" << endl;
		cout << "| 3.Email                       |" << endl;
		cout << "| 4.Address                     |" << endl;
		cout << "| 5.Birthday                    |" << endl;
		cout << "| 6.Class                       |" << endl;
		cout << "| 7.Back to Choose action       |" << endl;
		cout << "+-------------------------------+" << endl;
		cout << "input the Field to Update>>> ";
		char target_Field;
		cin >> target_Field;

		target_Field -= '0';
		if (target_Field == 7)
			return;

		string temp;
		getline(cin, temp);

		if (target_Field == 1) {
			string _Password;
			cout << "input the Password of Member >>> ";
			getline(cin, _Password);
			m.chg_Password(_Password);
		}
		else if (target_Field == 2) {
			string _Name;
			cout << "input the Name of Member >>> ";
			getline(cin, _Name);
			m.chg_Name(_Name);
		}
		else if (target_Field == 3) {
			string _Email;
			cout << "input the E-mail of Member >>> ";
			getline(cin, _Email);
			m.chg_Email(_Email);
		}
		else if (target_Field == 4) {
			string _Address;
			cout << "input the Address of Member >>> ";
			getline(cin, _Address);
			m.chg_Address(_Address);
		}
		else if (target_Field == 5) {
			char _Birthday[10];
			cout << "input the Birthday of Member >>> ";
			getline(cin, temp);
			if (temp.length() != 10) {
				cout << "ERROR: Not Date Format" << endl;
				return;
			}
			for (int i = 0; i < 10; i++)
				_Birthday[i] = temp.at(i);
			m.chg_Birthday(_Birthday);
		}
		else if (target_Field == 6) {
			char _Class;
			cout << "input the Class of Member >>> ";
			cin >> _Class;
			m.chg_Class(_Class);
		}
		else {
			cout << "Wrong Input!" << endl;
			return;
		}
		
		//update 할 member을 새로 만들었다.
		//이전에 존재하는 member을 삭제하고 새로 삽입하는 형식을 취한다.

		MemberFile.Open(filename, ios::in | ios::out);
		unsigned short total_l = MemberFile.Get_Packed_Length(m);
		MemberFile.Delete(address);
		MemberFile.Close();

		MemberFile.Open(filename, ios::in | ios::out);

		int before_addr = -1;
		int addr = MemberFile.show_Delete_first();
		int flag = 0;
		while (addr != -1) {
			unsigned short s = MemberFile.Get_Buffer_Length(addr);
			int next = MemberFile.Get_Next_Addr(addr);
			if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
				flag = 1;
				MemberFile.Update(m, addr, s); //현 주소에 새 레코드 입력
				if (before_addr == -1) { // next를 header에 delete head로 넣어준다
					MemberFile.update_Delete_first(next);
				}
				else { //before_addr가 가리키는 곳에 next를 넣어준다.
					MemberFile.update_Deleted(before_addr, next);
				}
				break;
			}
			before_addr = addr;
			addr = next;
		}

		if (flag == 0) { //뒤에 append 해야되는 경우
			MemberFile.Append(m);
		}
		MemberFile.Close();
		cout << "Update Complete!" << endl;
	}
}

void Game_manipulate(int n) {
	if (n == 1) {	//search
		string Target_ID;
		cout << "+---------Searching Game--------+" << endl;
		cout << "input the ID of Game >>> ";
		cin >> Target_ID;

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Game> GameFile(buffer);

		char filename[20] = "fileOfGame.dat";
		GameFile.Open(filename, ios::in | ios::out);
		Game g;
		if (Target_ID.length() != 8)
			cout << "ERROR: No Game Found!" << endl;
		else {
			char temp_ID[8];
			for (int i = 0; i < 8; i++)
				temp_ID[i] = Target_ID.at(i);
			g.chg_ID(temp_ID);
			int address = GameFile.Search(g);
			if (address == -1) {
				cout << "ERROR: No Game Found!" << endl;
			}
			else {
				GameFile.Read(g, address);
				cout << g;
			}
		}
		GameFile.Close();
	}
	else if (n == 2) {	//insert
		char _ID[8];
		string _Title;
		char _Release_date[10];
		string _Developer;
		string _Platform;
		char _Score[2];
		char _Price[3];
		string temp;
		getline(cin, temp);
		cout << "+----------Inserting Game-------+" << endl;
		cout << "input the ID of Game >>> ";
		getline(cin, temp);
		if (temp.length() != 8) {
			cout << "ERROR: Not ID Format" << endl;
			return;
		}
		for (int i = 0; i < 8; i++)
			_ID[i] = temp.at(i);

		cout << "input the Title of Game >>> ";
		getline(cin, _Title);

		cout << "input the Release date of Game >>> ";
		getline(cin, temp);
		if (temp.length() != 10) {
			cout << "ERROR: Not Date Format" << endl;
			return;
		}
		for (int i = 0; i < 10; i++)
			_Release_date[i] = temp.at(i);

		cout << "input the Developer of Game >>> ";
		getline(cin, _Developer);

		cout << "input the Platform of Game >>> ";
		getline(cin, _Platform);

		cout << "input the Score of Game >>> ";
		getline(cin, temp);
		if (temp.length() != 2) {
			cout << "ERROR: Not Score Format" << endl;
			return;
		}
		for (int i = 0; i < 2; i++)
			_Score[i] = temp.at(i);

		cout << "input the Price of Member >>> ";
		getline(cin, temp);
		if (temp.length() != 3) {
			cout << "ERROR: Not Score Format" << endl;
			return;
		}
		for (int i = 0; i < 3; i++)
			_Price[i] = temp.at(i);
		
		Game g = Game(_ID, _Title,_Release_date,_Developer,_Platform, _Score,  _Price);

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Game> GameFile(buffer);

		char filename[20] = "fileOfGame.dat";
		GameFile.Open(filename, ios::in | ios::out);
		unsigned short total_l = GameFile.Get_Packed_Length(g);
		if (GameFile.Search(g) != -1) {
			GameFile.Close();
			cout << "ERROR: ID Overlap" << endl;
			return;
		}

		int before_addr = -1;
		int addr = GameFile.show_Delete_first();
		//해당하는 주소의 길이, 다음 주소를 알아야 된다
		//만약 길이가 total_l보다 크다면 시작 주소에 write를 한다.
		//필요한 함수
		//1. 주소의 버퍼 길이를 읽어오는 함수
		//2. 주소의 다음 주소를 읽어오는 함수
		//3. 주소에 새로운 Record를 write하는 함수
		//4. 가용 리스트에 이전 과 다음을 이어주는 함수
		int flag = 0;
		while (addr != -1) {
			unsigned short s = GameFile.Get_Buffer_Length(addr);
			int next = GameFile.Get_Next_Addr(addr);
			if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
				flag = 1;
				GameFile.Update(g, addr, s); //현 주소에 새 레코드 입력
				if (before_addr == -1) { // next를 header에 delete head로 넣어준다
					GameFile.update_Delete_first(next);
				}
				else { //before_addr가 가리키는 곳에 next를 넣어준다.
					GameFile.update_Deleted(before_addr, next);
				}
				break;
			}
			before_addr = addr;
			addr = next;
		}

		if (flag == 0) { //뒤에 append 해야되는 경우
			GameFile.Append(g);
		}
		GameFile.Close();
		cout << "Insertion Complete!" << endl;

	}
	else if (n == 3) {	//delete
		string Target_ID;
		cout << "+----------Delete Game----------+" << endl;
		cout << "input the ID of Game >>> ";
		cin >> Target_ID;

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Game> GameFile(buffer);

		char filename[20] = "fileOfGame.dat";
		GameFile.Open(filename, ios::in | ios::out);
		Game g;
		if(Target_ID.length()!=8)
			cout << "ERROR: No Game Found!" << endl;
		else {
			char temp_ID[8];
			for (int i = 0; i < 8; i++)
				temp_ID[i] = Target_ID.at(i);
			g.chg_ID(temp_ID);
			int address = GameFile.Search(g);
			if (address == -1) {
				cout << "ERROR: No Game Found!" << endl;
			}
			else {
				GameFile.Delete(address);
				cout << "Deletion Complete!" << endl;
			}
		}
		if (Target_ID.length() == 8) {
			RecordFile <Purchase> PurchaseFile(buffer);
			strcpy(filename, "fileOfPurchase.dat");
			Purchase p = Purchase();
			char temp_ID[8];
			for (int i = 0; i < 8; i++)
				temp_ID[i] = Target_ID.at(i);
			p.chg_Game_ID(temp_ID);

			while (1) {
				PurchaseFile.Open(filename, ios::in | ios::out);
				int address = PurchaseFile.Search(p);
				if (address == -1) break;
				else PurchaseFile.Delete(address);
				PurchaseFile.Close();
			}
		}
	}
	else {	//update

	string Target_ID;
	cout << "+---------Updating Game---------+" << endl;
	cout << "input the ID of Game >>> ";
	cin >> Target_ID;

	DelimFieldBuffer buffer('|', STDMAXBUF);
	RecordFile <Game> GameFile(buffer);

	char filename[20] = "fileOfGame.dat";
	GameFile.Open(filename, ios::in | ios::out);
	Game g;
	int address = -1;
	if (Target_ID.length() != 8) {
		cout << "ERROR: No Game Found!" << endl;
		GameFile.Close();
		return;
	}
	else {
		char temp_ID[8];
		for (int i = 0; i < 8; i++)
			temp_ID[i] = Target_ID.at(i);
		g.chg_ID(temp_ID);
		address = GameFile.Search(g);
		if (address == -1) {
			cout << "ERROR: No Game Found!" << endl;
			GameFile.Close();
			return;
		}
		else {
			GameFile.Read(g, address);
		}
	}
	GameFile.Close();

	cout << "+-----------Select Field--------+" << endl;
	cout << "| 1.Title                       |" << endl;
	cout << "| 2.Release date                |" << endl;
	cout << "| 3.Developer                   |" << endl;
	cout << "| 4.Platform                    |" << endl;
	cout << "| 5.Score                       |" << endl;
	cout << "| 6.Price                       |" << endl;
	cout << "| 7.Back to Choose action       |" << endl;
	cout << "+-------------------------------+" << endl;
	cout << "input the Field to Update>>> ";
	char target_Field;
	cin >> target_Field;
	target_Field -= '0';
	if (target_Field == 7)
		return;

	string temp;
	getline(cin, temp);


	if (target_Field == 1) {
		string _Title;
		cout << "input the Title of Game >>> ";
		getline(cin, _Title);
		g.chg_Title(_Title);
	}
	else if (target_Field == 2) {
		char _Release_date[10];
		cout << "input the Release date of Game >>> ";
		getline(cin, temp);
		if (temp.length() != 10) {
			cout << "ERROR: Not Date Format" << endl;
			return;
		}
		for (int i = 0; i < 10; i++)
			_Release_date[i] = temp.at(i);
		g.chg_Release_date(_Release_date);
	}
	else if (target_Field == 3) {
		string _Developer;
		cout << "input the Developer of Game >>> ";
		getline(cin, _Developer);
		g.chg_Developer(_Developer);
	}
	else if (target_Field == 4) {
		string _Platform;
		cout << "input the Platform of Game >>> ";
		getline(cin, _Platform);
		g.chg_Platform(_Platform);
	}
	else if (target_Field == 5) {
		char _Score[2];
		cout << "input the Score of Game >>> ";
		getline(cin, temp);
		if (temp.length() != 2) {
			cout << "ERROR: Not Score Format" << endl;
			return;
		}
		for (int i = 0; i < 2; i++)
			_Score[i] = temp.at(i);
		g.chg_Score(_Score);
	}
	else if (target_Field == 6) {
		char _Price[3];
		cout << "input the Price of Member >>> ";
		getline(cin, temp);
		if (temp.length() != 3) {
			cout << "ERROR: Not Score Format" << endl;
			return;
		}
		for (int i = 0; i < 3; i++)
			_Price[i] = temp.at(i);
		g.chg_Price(_Price);
	}
	else {
		cout << "Wrong Input!" << endl;
		return;
	}

	GameFile.Open(filename, ios::in | ios::out);
	unsigned short total_l = GameFile.Get_Packed_Length(g);
	GameFile.Delete(address);
	GameFile.Close();

	GameFile.Open(filename, ios::in | ios::out);

	int before_addr = -1;
	int addr = GameFile.show_Delete_first();
	int flag = 0;
	while (addr != -1) {
		unsigned short s = GameFile.Get_Buffer_Length(addr);
		int next = GameFile.Get_Next_Addr(addr);
		if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
			flag = 1;
			GameFile.Update(g, addr, s); //현 주소에 새 레코드 입력
			if (before_addr == -1) { // next를 header에 delete head로 넣어준다
				GameFile.update_Delete_first(next);
			}
			else { //before_addr가 가리키는 곳에 next를 넣어준다.
				GameFile.update_Deleted(before_addr, next);
			}
			break;
		}
		before_addr = addr;
		addr = next;
	}

	if (flag == 0) { //뒤에 append 해야되는 경우
		GameFile.Append(g);
	}
	GameFile.Close();
	cout << "Update Complete!" << endl;
	}
}

void Purchase_manipulate(int n) {
	if (n == 1) {	//search
		while (1) {
			string Target_ID;
			char ID_n;
			cout << "+-------Searching Purchase------+" << endl;
			cout << "| 1. Search by Member ID        |" << endl;
			cout << "| 2. Search by Game ID          |" << endl;
			cout << "| 3. Search by Purchase ID      |" << endl;
			cout << "| 4. Back to Action Menu        |" << endl;
			cout << "+-------------------------------+" << endl;
			cout << "input the number of menu >>> ";
			cin >> ID_n;
			ID_n -= '0';
			if (ID_n == 4)
				break;
			else if (ID_n < 1 && ID_n >3) {
				cout << "ERROR: Wrong Number" << endl;
				continue;
			}

			DelimFieldBuffer buffer('|', STDMAXBUF);
			RecordFile <Purchase> PurchaseFile(buffer);

			char filename[20] = "fileOfPurchase.dat";
			Purchase p=Purchase();

			if (ID_n == 1) {
				cout << "input the ID of Member >>> ";
				cin >> Target_ID;
				p.chg_Member_ID(Target_ID);
			}
			else if (ID_n == 2) {
				cout << "input the ID of Game >>> ";
				cin >> Target_ID;
				if (Target_ID.length() != 8) {
					cout << "ERROR: No Game Found!" << endl;
					continue;
				}
				char temp_ID[8];
				for (int i = 0; i < 8; i++)
					temp_ID[i] = Target_ID.at(i);
				p.chg_Game_ID(temp_ID);
			}
			else if(ID_n==3){
				cout << "input the ID of Purchase >>> ";
				cin >> Target_ID;
				if (Target_ID.length() != 12) {
					cout << "ERROR: No Purchase Found!" << endl;
					continue;
				}
				char temp_ID[12];
				for (int i = 0; i < 12; i++)
					temp_ID[i] = Target_ID.at(i);
				p.chg_Purchase_ID(temp_ID);
			}
			else {
				cout << "ERROR: Wrong Number" << endl;
				continue;
			}
			
			PurchaseFile.Open(filename, ios::in | ios::out);
			int flag = 0;
			while(1) {
				int address = PurchaseFile.Search_For_Purchase(p);
				if (address == -1) {
					if(flag==0)
						cout << "ERROR: No Purchase Found!" << endl;
					break;
				}
				else {
					flag = 1;
					Purchase q;
					PurchaseFile.Read(q, address);
					cout << q;
					cout << "+-------------------------------+" << endl;
				}
			}
			PurchaseFile.Close();
		}
	}
	else if (n == 2) {	//insert
		// 기존의 ID와 겹치는 ID가 있는지 확인한다.
		// 기존의 gameID, memberID를 사용하는지 확인한다.
		// 앞과 마찬가지로 삭제된 레코드 탐색 + 길이에 맞으면 삽입 아니면 append
		char _Purchase_ID[12];
		char _Game_ID[8];
		string _Member_ID;
		char _Purchase_date[10];
		string temp;
		getline(cin, temp);

		cout << "+-------Inserting Purchase------+" << endl;
		cout << "input the ID of Purchase >>> ";
		getline(cin, temp);
		if (temp.length() != 12) {
			cout << "ERROR: Not Purchase ID Format" << endl;
			return;
		}
		for (int i = 0; i < 12; i++)
			_Purchase_ID[i] = temp.at(i);

		cout << "input the ID of Game >>> ";
		getline(cin, temp);
		if (temp.length() != 8) {
			cout << "ERROR: Not Game ID Format" << endl;
			return;
		}
		for (int i = 0; i < 8; i++)
			_Game_ID[i] = temp.at(i);
		
		cout << "input the ID of Member >>> ";
		getline(cin, _Member_ID);
		
		cout << "input the Date of Purchase >>> ";
		getline(cin, temp);
		if (temp.length() != 10) {
			cout << "ERROR: Not Date Format" << endl;
			return;
		}
		for (int i = 0; i < 10; i++)
			_Purchase_date[i] = temp.at(i);
		

		Purchase p = Purchase( _Purchase_ID,_Game_ID,_Member_ID,_Purchase_date);

		//purchase ID 중복 검사
		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Purchase> PurchaseFile(buffer);
		char filename[20] = "fileOfPurchase.dat";
		PurchaseFile.Open(filename, ios::in | ios::out);
		unsigned short total_l = PurchaseFile.Get_Packed_Length(p);
		if (PurchaseFile.Search(p) != -1) {
			PurchaseFile.Close();
			cout << "ERROR: ID Overlap" << endl;
			return;
		}
		PurchaseFile.Close();

		//member ID 있는지 검사
		RecordFile <Member> MemberFile(buffer);
		strcpy(filename, "fileOfMember.dat");
		MemberFile.Open(filename, ios::in | ios::out);
		Member m;

		m.chg_ID(_Member_ID);
		int member_addr = MemberFile.Search(m);
		if (member_addr == -1) {
			cout << "ERROR: No Member ID Found!" << endl;
			MemberFile.Close();
			return;
		}
		MemberFile.Close();

		//Game ID 있는지 검사
		RecordFile <Game> GameFile(buffer);
		strcpy(filename, "fileOfGame.dat");
		GameFile.Open(filename, ios::in | ios::out);
		Game g;

		g.chg_ID(_Game_ID);
		int game_address = GameFile.Search(g);
		if (game_address == -1) {
			cout << "ERROR: No Game ID Found!" << endl;
			GameFile.Close();
			return;
		}
		GameFile.Close();

		//purchase안에 삽입하는 과정
		strcpy(filename, "fileOfPurchase.dat");
		PurchaseFile.Open(filename, ios::in | ios::out);

		int before_addr = -1;
		int addr = PurchaseFile.show_Delete_first();
		int flag = 0;
		while (addr != -1) {
			unsigned short s = PurchaseFile.Get_Buffer_Length(addr);
			int next = PurchaseFile.Get_Next_Addr(addr);
			if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
				flag = 1;
				PurchaseFile.Update(p, addr, s); //현 주소에 새 레코드 입력
				if (before_addr == -1) { // next를 header에 delete head로 넣어준다
					PurchaseFile.update_Delete_first(next);
				}
				else { //before_addr가 가리키는 곳에 next를 넣어준다.
					PurchaseFile.update_Deleted(before_addr, next);
				}
				break;
			}
			before_addr = addr;
			addr = next;
		}

		if (flag == 0) { //뒤에 append 해야되는 경우
			PurchaseFile.Append(p);
		}
		PurchaseFile.Close();
		cout << "Insertion Complete!" << endl;
	}
	else if (n == 3) {	//delete
		string Target_ID;
	
		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Purchase> PurchaseFile(buffer);
	
		char filename[20] = "fileOfPurchase.dat";
		PurchaseFile.Open(filename, ios::in | ios::out);
		Purchase p =Purchase();

		cout << "input the ID of Purchase >>> ";
		cin >> Target_ID;
		if (Target_ID.length() != 12) {
			cout << "ERROR: No Purchase Found!" << endl;
		}
		else {
			char temp_ID[12];
			for (int i = 0; i < 12; i++)
				temp_ID[i] = Target_ID.at(i);
			p.chg_Purchase_ID(temp_ID);

			int address = PurchaseFile.Search(p);
			if (address == -1) {
				cout << "ERROR: No Purchase Found!" << endl;
			}
			else {
				PurchaseFile.Delete(address);
				cout << "Deletion Complete!" << endl;
			}
		}
	}
	else {	//update
		//기존에 존재하는 Purchase인가
		//gameID를 고치려고한다면 이미 있는 gameID인지 확인.
		//memberID를 고치려고 한다면 이미 있는 memberID인지 확인
		//기존 레코드 삭제 + 레코드 삽입 구조

		string Target_ID;
		cout << "+---------Updating Purchase-----+" << endl;
		cout << "input the ID of Purchase >>> ";
		cin >> Target_ID;

		DelimFieldBuffer buffer('|', STDMAXBUF);
		RecordFile <Purchase> PurchaseFile(buffer);

		char filename[20] = "fileOfPurchase.dat";
		PurchaseFile.Open(filename, ios::in | ios::out);
		Purchase p;
		int address = -1;	//update할 purchase의 주소를 저장한다.
		if (Target_ID.length() != 12) {
			cout << "ERROR: No Purchase Found!" << endl;
			PurchaseFile.Close();
			return;
		}
		else {
			char temp_ID[12];
			for (int i = 0; i < 12; i++)
				temp_ID[i] = Target_ID.at(i);

			p.chg_Purchase_ID(temp_ID);
			address = PurchaseFile.Search(p);
			if (address == -1) {
				cout << "ERROR: No Purchase Found!" << endl;
				PurchaseFile.Close();
				return;
			}
			else {
				PurchaseFile.Read(p, address);
			}
		}
		PurchaseFile.Close();

		cout << "+-----------Select Field--------+" << endl;
		cout << "| 1.Game ID                     |" << endl;
		cout << "| 2.Member ID                   |" << endl;
		cout << "| 3.Purchase Date               |" << endl;
		cout << "| 4.Back to Choose action       |" << endl;
		cout << "+-------------------------------+" << endl;
		cout << "input the Field to Update>>> ";
		char target_Field;
		cin >> target_Field;
		target_Field -= '0';
		if (target_Field == 4)
			return;

		string temp;
		getline(cin, temp); 

		if (target_Field == 1) {
			char _Game_ID[8];
			cout << "input the ID of Game >>> ";
			getline(cin, temp);
			if (temp.length() != 8) {
				cout << "ERROR: Not Game ID Format" << endl;
				return;
			}
			for (int i = 0; i < 8; i++)
				_Game_ID[i] = temp.at(i);

			RecordFile <Game> GameFile(buffer);
			strcpy(filename, "fileOfGame.dat");
			GameFile.Open(filename, ios::in | ios::out);
			Game g;

			g.chg_ID(_Game_ID);
			int game_address = GameFile.Search(g);
			if (game_address == -1) {
				cout << "ERROR: No Game ID Found!" << endl;
				GameFile.Close();
				return;
			}
			GameFile.Close();

			p.chg_Game_ID(_Game_ID);
		}
		else if (target_Field == 2) {
			string _Member_ID;
			cout << "input the ID of Member >>> ";
			getline(cin, _Member_ID);

			RecordFile <Member> MemberFile(buffer);
			strcpy(filename, "fileOfMember.dat");
			MemberFile.Open(filename, ios::in | ios::out);
			Member m;

			m.chg_ID(_Member_ID);
			int member_addr = MemberFile.Search(m);
			if (member_addr == -1) {
				cout << "ERROR: No Member ID Found!" << endl;
				MemberFile.Close();
				return;
			}
			MemberFile.Close();
			p.chg_Member_ID(_Member_ID);
		}
		else if (target_Field == 3) {
			char _Purchase_date[10];
			cout << "input the Date of Purchase >>> ";
			getline(cin, temp);
			if (temp.length() != 10) {
				cout << "ERROR: Not Date Format" << endl;
				return;
			}
			for (int i = 0; i < 10; i++)
				_Purchase_date[i] = temp.at(i);
			p.chg_Purchase_date(_Purchase_date);
		}
		else {
			cout << "Wrong Input!" << endl;
			return;
		}

		strcpy(filename, "fileOfPurchase.dat");
		PurchaseFile.Open(filename, ios::in | ios::out);
		unsigned short total_l = PurchaseFile.Get_Packed_Length(p);
		PurchaseFile.Delete(address);
		PurchaseFile.Close();

		PurchaseFile.Open(filename, ios::in | ios::out);

		int before_addr = -1;
		int addr = PurchaseFile.show_Delete_first();
		int flag = 0;
		while (addr != -1) {
			unsigned short s = PurchaseFile.Get_Buffer_Length(addr);
			int next = PurchaseFile.Get_Next_Addr(addr);
			if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
				flag = 1;
				PurchaseFile.Update(p, addr, s); //현 주소에 새 레코드 입력
				if (before_addr == -1) { // next를 header에 delete head로 넣어준다
					PurchaseFile.update_Delete_first(next);
				}
				else { //before_addr가 가리키는 곳에 next를 넣어준다.
					PurchaseFile.update_Deleted(before_addr, next);
				}
				break;
			}
			before_addr = addr;
			addr = next;
		}

		if (flag == 0) { //뒤에 append 해야되는 경우
			PurchaseFile.Append(p);
		}
		PurchaseFile.Close();
		cout << "Update Complete!" << endl;
	

	}
}

void LecturePurchaseSystem() {
	while (1) {
		char target_file = -1;
		char target_Action = -1;

		cout << "+----------Choose Table---------+" << endl;
		cout << "| 1. Member                     |" << endl;
		cout << "| 2. Game                       |" << endl;
		cout << "| 3. Purchase                   |" << endl;
		cout << "| 4. Back to main menu          |" << endl;
		cout << "+-------------------------------+" << endl;
		cout << "input the number of menu >>> ";
		cin >> target_file;
		target_file -= '0';
		if (target_file == 4)
			break;
		else if (target_file != 1 && target_file != 2 && target_file != 3) {
			cout << "ERROR: Wrong Number" << endl;
			continue;
		}
		while (1) {
			if (target_file == 1) cout << "+-------------Member------------+" << endl;
			else if (target_file == 2) cout << "+--------------Game-------------+" << endl;
			else cout << "+-------------Purchase----------+" << endl;
			cout << "+----------Choose Action--------+" << endl;
			cout << "| 1. Search                     |" << endl;
			cout << "| 2. Insert                     |" << endl;
			cout << "| 3. Delete                     |" << endl;
			cout << "| 4. Update                     |" << endl;
			cout << "| 5. Back to Choose Table       |"<< endl;
			cout << "+-------------------------------+" << endl;
			cout << "input the number of menu >>> ";
			cin >> target_Action;
			target_Action -= '0';
			if (target_Action == 5)
				break;
			else if (target_Action != 1 && target_Action != 2 && target_Action != 3 && target_Action != 4) {
				cout << "ERROR: Wrong Number" << endl;
				continue;
			}
			if (target_file == 1) Member_manipulate(target_Action);
			else if (target_file == 2) Game_manipulate(target_Action);
			else Purchase_manipulate(target_Action);
		}
	}
}

int main() {
	while (1) {
		char n;
		print_menu();
		cin >> n;
		n -= '0';
		if (n == 1) showMember();
		else if (n == 2) showGame();
		else if (n == 3) showPurchase();
		else if (n == 4) MemberTest();
		else if (n == 5) GameTest();
		else if (n == 6) PurchaseTest();
		else if (n == 7) LecturePurchaseSystem();
		else if (n == 8) break;
		else cout << "ERROR: Wrong Number" << endl;
	}
	return 0;
}


