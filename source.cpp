
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <numeric>
#include <climits>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cstdlib>
using namespace std;

// hàm kiểm tra, ràng buộc, chuẩn hóa
bool checkUsername(string username);
bool checkPassword(string password);
bool kiTuDacBiet(char c) {
	if (int(c) >= 32 && int(c) <= 47 || int(c) >= 58 && int(c) <= 64 || int(c) >= 91 && int(c) <= 96 || int(c) >= 123) {
		return true;
	}
	return false;
}
bool checkEmail(string email);
bool checkPhoneNumber(string phoneNumber);
void chuanHoaTen(string& ten);
bool checkContactID(string contactID);

//Set dùng để check trùng lập và check xem đã tồn tại username, phone number,... của User và Contact chưa.
set<string> usernameCheck;
set<string> phoneNumberCheck;
set<string> emailCheck;
set<string> userIDCheck;


//Cấu trúc dữ liệu map để quản lí tài khoản User (không phải tài khoản contact);
map<string, string> userAccountData;



class User {
private:
	string userID, username, email, password;
public:
	User() {};
	User(string username, string email, string password) {
		this->username = username;
		this->email = email;
		this->password = password;
	}
	friend istream& operator >> (istream& in, User& x) {

		//Tạo userID ngẫu nhiên từ 10000 đến 99999 và kiểm tra trùng lặp
		srand(time(NULL));
		int soID = rand() % 90000 + 10000;
		string ssoID = to_string(soID);
		while (userIDCheck.count(ssoID)) {
			soID = rand() % 90000 + 10000;
		}
		x.userID = soID;

		//Nhập và kiểm tra username
		cout << "Ten dang nhap: ";
		getline(in, x.username);
		while (!checkUsername(x.username) || usernameCheck.count(x.username)) {
			cout << "Ten dang nhap khong hop le. Vui long nhap lai: ";
			getline(in, x.username);
		}
		usernameCheck.insert(x.username);

		//Nhập và kiểm tra password

		cout << "Mat khau : ";
		getline(in, x.password);
		while (!checkPassword(x.password)) {
			cout << "Mat khau khong hop le. Vui long nhap lai: ";
			getline(in, x.password);
		}

		//Nhập và kiểm tra email
		cout << "Email : ";
		getline(in, x.email);
		while (!checkEmail(x.email)) {
			cout << "Email khong hop le. Vui long nhap lai: ";
			getline(in, x.email);
		}

		//Thêm email vào set để kiểm tra trùng lặp
		emailCheck.insert(x.email);
		userAccountData.insert({ x.username,x.password });
		return in;
	}
	void showProfile() {
		cout << "UserID : " << userID << endl;
		cout << "Username : " << username << endl;
		cout << "Email : " << email << endl;
		cout << "Password : ";
		string tmpPassword = password;
		for (int i = 0; i < tmpPassword.size(); i++) {
			tmpPassword[i] = '*';
			cout << tmpPassword[i];
		}
		cout << endl;
		cout << "Nhan 1 de hien Password : ";
		string ch; getline(cin, ch);
		while (ch != "1") {
			cout << "Vui long nhap lai : ";
			getline(cin, ch);
		}
		if (ch == "1") {
			cout << "Password : " << password << endl;
		}
		cout << endl;
	}
	string getUserID() {
		return userID;
	}
	string getUsername() {
		return username;
	}
	string getEmail() {
		return email;
	}
	string getPassword() {
		return password;
	}
	void setUserID(string userID) {
		this->userID = userID;
	}
	void setUsername(string username) {
		this->username = username;
	}
	void setEmail(string email) {
		this->email = email;
	}
	void setPassword(string password) {
		this->password = password;
	}
	void login(string username, string password) {
		if (userAccountData.find(username) != userAccountData.end() && userAccountData[username] == password) {
			cout << "Dang nhap thanh cong !" << endl;
		}
		else cout << "Dang nhap that bai !" << endl;
	}
	void logout() {
		cout << "Dang xuat thanh cong!" << endl;
	}
};


int main()
{
	class Contact {
	private:
		string contactID, fullName, phoneNumber, email, address, company, relatives;
	public:
		Contact() {};
		Contact(string contactID, string fullName, string phoneNumber, string email, string address, string company, string relatives) {
			this->contactID = contactID;
			this->fullName = fullName;
			this->phoneNumber = phoneNumber;
			this->email = email;
			this->address = address;
			this->company = company;
			this->relatives = relatives;
		}
		void updateInfo(string contactID, string fullName, string phoneNumber, string email, string address, string company, string relatives) {
			this->contactID = contactID;
			this->fullName = fullName;
			this->phoneNumber = phoneNumber;
			this->email = email;
			this->address = address;
			this->company = company;
			this->relatives = relatives;
		}
		friend istream& operator >> (istream& in, Contact& x) {
			//Nhập và kiểm tra contactID
			cout << "Contact ID: ";
			getline(in, x.contactID);
			while (!checkContactID(x.contactID)) {
				cout << "ContactID khong hop le. Vui long nhap lai: ";
				getline(in, x.contactID);
			}
			userIDCheck.insert(x.contactID);

			//Full Name
			//Nhập và kiểm tra fullName
			cout << "Ten day du : ";
			getline(in, x.fullName);
			while (!checkUsername(x.fullName)) {
				cout << "Ten khong hop le. Vui long nhap lai: ";
				getline(in, x.fullName);
			}
			chuanHoaTen(x.fullName);

			//Nhập và kiểm tra phoneNumber
			cout << "Phone Number : ";
			getline(in, x.phoneNumber);
			while (!checkPhoneNumber(x.phoneNumber) || phoneNumberCheck.count(x.phoneNumber)) {
				cout << "So dien thoai khong hop le : ";
				getline(in, x.phoneNumber);
			}
			phoneNumberCheck.insert(x.phoneNumber);

			//Nhập và kiểm tra email
			cout << "Email : ";
			getline(in, x.email);
			while (!checkEmail(x.email)) {
				cout << "Email khong hop le. Vui long nhap lai: ";
				getline(in, x.email);
			}
			emailCheck.insert(x.email);

			cout << "Address : ";
			getline(in, x.address);
			cout << "Company : ";
			getline(in, x.company);

			//Nhập quan hệ
			cout << "Relative : ";
			getline(in, x.relatives);

			return in;
		}
		void displayContact() {
			cout << "ContactID : " << contactID << endl;
			cout << "Name : " << fullName << endl;
			cout << "Phone Number : " << phoneNumber << endl;
			cout << "Email : " << email << endl;
			cout << "Address : " << address << endl;
			cout << "Company : " << company << endl;
		}
		string getFullName() {
			return fullName;
		}
		string getPhoneNumber() {
			return phoneNumber;
		}
		string getEmail() {
			return email;
		}
		string getContactID() {
			return contactID;
		}
		char getContactFirstLetter() {
			string username = getFullName();
			stringstream ss(username);
			string tmp;
			vector<string> ten;
			while (ss >> tmp) {
				ten.push_back(tmp);
			}
			return ten[ten.size() - 1][0];
		}
		string getContactFirstName() {
			string username = getFullName();
			stringstream ss(username);
			string tmp;
			vector<string> ten;
			while (ss >> tmp) {
				ten.push_back(tmp);
			}
			return ten[ten.size() - 1];
		}
		void setFullName(string fullName) {
			this->fullName = fullName;
		}
		void setPhoneNumber(string phoneNumber) {
			this->phoneNumber = phoneNumber;
		}
		void setEmail(string email) {
			this->email = email;
		}
		void setAddress(string address) {
			this->address = address;
		}
		void setCompany(string company) {
			this->company = company;
		}
		void setRelatives(string relatives) {
			this->relatives = relatives;
		}
	};


	bool checkUsername(string username) {
		if (isdigit(username[0])) return false;
		return true;
	}
	bool checkPassword(string password) {
		if (password.length() < 8) return false;
		for (int i = 0; i < password.size(); i++) {
			if (kiTuDacBiet(password[i])) {
				return true;
			}
		}
		return false;
	}
	bool checkEmail(string email) {
		for (int i = 0; i < email.length(); i++) {
			if (email[i] == '@') {
				return true;
			}
		}
		return false;
	}
	bool checkPhoneNumber(string phoneNumber) {
		if (phoneNumber.size() != 10) return false;
		for (int i = 0; i < phoneNumber.size(); i++) {
			if (!isdigit(phoneNumber[i])) {
				return false;
			}
		}
		return true;
	}
	void chuanHoaTen(string & ten) {
		stringstream ss(ten);
		string tmp;
		string res = "";
		while (ss >> tmp) {
			res += toupper(tmp[0]);
			for (int i = 1; i < tmp.size(); i++) {
				res += tolower(tmp[i]);
			}
			res += " ";
		}
		res.pop_back();
		ten = res;
	}
	bool checkContactID(string contactID) {
		for (int i = 0; i < contactID.size(); i++) {
			if (!isdigit(contactID[i])) {
				return false;
			}
		}
		return true;
	}
}


