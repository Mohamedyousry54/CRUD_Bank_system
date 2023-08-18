#include <iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>

using namespace std;
// enums and structres
enum enoptions_main_menu {
	list_clients = 1,
	add_client = 2,
	delete_client = 3,
	update_client = 4,
	find_client = 5,
	transaction=6,
	manage_users=7,
	log_out = 8
};
enum enoptions_User_menu {
	list_Users= 1,
	add_user = 2,
	delete_user = 3,
	update_user = 4,
	find_user = 5,
	Main_menu = 6
};
enum entransactions_options {
	deposit = 1,
	withdraw = 2,
	total_balances = 3,
	main_menu = 4
};
struct stuser_info{
	string userName;
	string Password;
	short permission=0;
	bool mark_for_delete = false;
};
struct strecord {
	string Name = "";
	string PinCode = "";
	string Phone = "";
	float Balance = 0;
	string AccountNumber = "";
	bool mark_for_delete = false;
};

// global variables
stuser_info user_logined;
string file_Path_for_clients = "G:\clients_data.txt";
string delim_for_clients = "  &&^^&&  ";
string file_path_for_login = "users_login_info.txt";
string delim_for_users_login_info = " -0_0- ";

void main_menu_screen();
void transaction_screen();
void manage_user_page();
void manage_users_screen();
void log_out_screen();

// home pages
void welcome_screen() {
	system("cls");
	cout << "=====================================================================================================\n";
	cout << "==============================             WELCOME TO OUR BANK               ======================== \n";
	cout << "=====================================================================================================\n\n\n";
}

void Home_page()
{
	cout << "\nPress any key to return to the home page...";
	system("pause>0");
	main_menu_screen();
}

void manage_user_page()
{
	cout << "\nPress any key to return to the home page...";
	system("pause>0");
	manage_users_screen();
}

void Home_page_transaction()
{
	cout << "\nPress any key to return to the transaction menu...";
	system("pause>0");
	transaction_screen();
}

void Login_screen()
{
	cout << "------------------------------------------\n";
	cout << "               Login  Screen              \n";
	cout << "------------------------------------------\n";
}

//take inputs from user
string accNumber()
{
	string account_number;
	cout << "Enter account number please?";
	cin >> account_number;
	return account_number;

}

strecord Read_New_client() {
	strecord Client;
	cout << "Enter Name? ";
	getline(cin >> ws, Client.Name);
	cout << "Enter Account Number? ";
	getline(cin, Client.AccountNumber);
	cout << "Enter PinCode?";
	getline(cin, Client.PinCode);
	cout << "Enter Phone?";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance?";
	cin >> Client.Balance;
	return Client;
}

int take_permission()
{
	char yes_no = 'n';
	int permissions = 0;
	cout << "Do you want to give access to : " << endl;

	cout << "show client list  ?y/n";
	cin >> yes_no;
	if (yes_no == 'y'|| yes_no == 'Y')
		permissions += 1;

	cout << "add client ?y/n";
	cin >> yes_no;
	if (yes_no == 'y' || yes_no == 'Y')
		permissions += 2;

	cout << "delete client ?y/n";
	cin >> yes_no;
	if (yes_no == 'y' || yes_no == 'Y')
		permissions += 4;

	cout << "update client ?y/n";
	cin >> yes_no;
	if (yes_no == 'y' || yes_no == 'Y')
		permissions += 8;

	cout << "find client ?y/n";
	cin >> yes_no;
	if (yes_no == 'y' || yes_no == 'Y')
		permissions += 16;

	cout << "transaction ?y/n";
	cin >> yes_no;
	if (yes_no == 'y' || yes_no == 'Y')
		permissions += 32;

	cout << "manage users ?y/n";
	cin >> yes_no;
	if (yes_no == 'y' || yes_no == 'Y')
		permissions += 64;

	return permissions;
}

stuser_info Read_New_user(bool signUp=false) {
	stuser_info user;
	char yes_or_no = 'n';
	cout << "Enter User_Name? ";
	getline(cin >> ws, user.userName);
	cout << "Enter password? ";
	getline(cin, user.Password);
	if (signUp)
	{
		user.permission += 18;
	}
	else
	{
		cout << "Do you want to give full access to this user ?y/n ";
		cin >> yes_or_no;
		if (yes_or_no == 'y' || yes_or_no == 'Y')
			user.permission = -1;
		else
			user.permission = take_permission();
	}

	return user;
}

stuser_info temp_user() {
	stuser_info user;
	cout << "Enter User_Name? ";
	getline(cin >> ws, user.userName);
	cout << "Enter password? ";
	getline(cin, user.Password);
	return user;
}


//Print informations
void printinfo_header(vector<strecord> records)
{
	cout << "                      list of [" << records.size() << "] clients              \n\n";
	cout << left << setw(30) << "\n   name";
	cout << left << setw(24) << "AccountNumber";
	cout << left << setw(25) << "PinCode";
	cout << left << setw(25) << "Phone";
	cout << left << setw(40) << "AccountBalance" << endl;
	cout << "____________________________________________________________________________________________________________________________________\n";
}

void print_User_header(vector<stuser_info> users)
{
	cout << "                      list of [" << users.size() << "] clients              \n\n";
	cout << left << setw(35) << "\nname" << "      |       ";
	cout << left << setw(30) << "password  " << "     |        ";
	cout << left << setw(35) << "PinCode   ";
	cout << "\n_____________________________________________________________________________________________________\n";
}

void print_balance_info(vector<strecord> records)
{
	cout << "                      list of [" << records.size() << "] clients              \n\n";
	cout << left << setw(30) << "\n   name";
	cout << left << setw(24) << "AccountNumber";
	cout << left << setw(40) << "AccountBalance" << endl;
	cout << "____________________________________________________________________________________________________________________________________\n";
}

void print_client_blances(strecord record)
{
	cout << "\n " << setw(27) << record.Name << " |";
	cout << setw(20) << record.AccountNumber << " | ";
	cout << setw(25) << record.Balance << " | ";
	cout << "\n_____________________________________________________________________________________________________________________________________\n";
}

void print_client_info_from_file(strecord& record)
{
	cout << "\n " << setw(27) << record.Name << " |";
	cout << setw(20) << record.AccountNumber << " | ";
	cout << setw(23) << record.PinCode << " | ";
	cout << setw(25) << record.Phone << " | ";
	cout << setw(25) << record.Balance << " | ";
	cout << "\n_____________________________________________________________________________________________________________________________________\n";
}

void print_User_info(stuser_info& user)
{
	cout << "\n " << setw(40) << user.userName << " | ";
	cout << setw(40) << user.Password<< " | ";
	cout << setw(40) << user.permission;
	cout << "\n___________________________________________________________________________________________________________\n";
}

void print_user(stuser_info user)
{
	cout << "\n___________________________________________________________________________________________________________\n";
	cout << "\nUser name      : " << user.userName <<endl;
	cout << "user pass word   : " << user.Password << endl;
	cout << "user permission  : "<< user.permission;
	cout << "\n___________________________________________________________________________________________________________\n";
}

void print_client_info(strecord& x)
{
	cout << "\nname          : " << x.Name;
	cout << "\nAccountNumber : " << x.AccountNumber;
	cout << "\nPinCode       : " << x.PinCode;
	cout << "\nPhone         : " << x.Phone;
	cout << "\nAccountBalance: " << x.Balance;
}




string one_line_record(strecord x, string delim = "&&__")
{
	string concat = "";
	concat += x.Name + delim;
	concat += x.AccountNumber + delim;
	concat += x.PinCode + delim;
	concat += x.Phone + delim;
	concat += to_string(x.Balance);
	return concat;

}

string one_line_user_info(stuser_info user, string delim = "&&__")
{
	string concat = "";
	concat += user.userName + delim;
	concat += user.Password + delim;
	concat += to_string(user.permission);
	return concat;

}

void enterNumber(vector<int>& vnumbers)
{
	int x;
	bool want = 1;
	while (want)
	{
		cout << "\nenter a number ?" << endl;
		cin >> x;
		vnumbers.push_back(x);
		cout << "\ndo you want to enter another number?\n";
		cin >> want;
	}
}

void printv_records(vector<strecord>& records)
{
	for (strecord& i : records)
		print_client_info_from_file(i);
}

void printv_users(vector<stuser_info>& users)
{
	for (stuser_info& i : users)
		print_User_info(i);
}

void vector_string_split(string line, vector <string>& vstring, string delim)
{
	short pos = 0;
	string subword = "";
	while ((pos = line.find(delim)) != string::npos)
	{
		subword = line.substr(0, pos);
		if (subword != "")
			vstring.push_back(subword);
		line.erase(0, pos + delim.length());
	}
	if (line != "")
		vstring.push_back(line);
}

stuser_info login_process()
{
	stuser_info user;
	cout << "Enter your user name ? ";
	getline(cin>>ws,user.userName);
	cout << "Enter your password ? ";
	getline(cin, user.Password);
	return user;
}

int user_by_userName_password(stuser_info user, vector<stuser_info> users)
{
	int i = int (users.size());
	do
	{
		i--;
		if (users[i].userName == user.userName) {
			if (users[i].Password == user.Password)
				return i + 1;
		}
	}while (i);
	return 0;
}

void sign_up_screen()
{
	cout << "------------------------------------------\n";
	cout << "                   Sign Up                \n";
	cout << "------------------------------------------\n";
}

void login_actions(vector<stuser_info>& users)
{
	
	stuser_info user;
	int i = 0;
	short index = 0;
	do
	{
		system("cls");
		if (i > 0)
		{
			cout << "Envalid userName/password!!?\n";
		}
		Login_screen();
		user = login_process();
		index = user_by_userName_password(user, users);
		i++;
	} while (!user_by_userName_password(user, users));
	user_logined = users[index-1];
	main_menu_screen();
}

strecord finalrecord(string line, string delim)
{
	strecord record;
	vector<string> line_record;
	vector_string_split(line, line_record, delim);
	record.Name = line_record[0];
	record.AccountNumber = line_record[1];
	record.PinCode = line_record[2];
	record.Phone = line_record[3];
	record.Balance = stof(line_record[4]);
	return record;
}

stuser_info final_user_info(string line, string delim)
{
	stuser_info user;
	vector<string> line_record;
	vector_string_split(line, line_record, delim);
	user.userName = line_record[0];
	user.Password = line_record[1];
	user.permission = stoi(line_record[2]);
	return user;
}

void vector_content_to_file(string filePath, string delim, vector<strecord> records)
{
	fstream myfile;
	myfile.open(filePath, ios::out);
	if (myfile.is_open())
	{
		string line;
		strecord record;
		for (int i = 0; i < records.size(); i++)
		{
			if (!records[i].mark_for_delete)
			{
				line = one_line_record(records[i], delim);
				myfile << line << endl;
			}
		}
		myfile.close();
	}
}

void vector_users_to_file(string filePath, string delim, vector<stuser_info> users)
{
	fstream myfile;
	myfile.open(filePath, ios::out);
	if (myfile.is_open())
	{
		string line;
		strecord record;
		for (int i = 0; i < users.size(); i++)
		{
			if (!users[i].mark_for_delete)
			{
				line = one_line_user_info(users[i], delim);
				myfile << line << endl;
			}
		}
		myfile.close();
	}
}

void Add_info_in_file(string filePath, string st)
{
	fstream myfile;
	myfile.open(filePath, ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << st << endl;
		myfile.close();
	}
}

int client_by_account_number(string accNumber, vector<strecord> records)
{
	int i = 0;
	while (records.size() != i)
	{
		if (records[i].AccountNumber == accNumber)
			return i + 1;
		i++;
	}
	return 0;
}

void Add_clients(string filePath, string delim, vector<strecord> records)
{
	strecord record;
	bool want = 0;
	do
	{
		record = Read_New_client();
		while (client_by_account_number(record.AccountNumber, records)) 
		{
			cout << "client with [" << record.AccountNumber << "] already exist,Enter another account number?\n";
			cin >> record.AccountNumber;
		}
		Add_info_in_file(filePath, one_line_record(record, delim));
		cout << "\nyour cliend added successfully .\n";
		cout << "\ndo you want to add more clients ?1[yes] 0 [No]." << endl;
		cin >> want;
	} while (want);

}

vector<stuser_info>Load_Users_info_From_File(string FileName, string delim)
{
	vector<stuser_info>Users;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		stuser_info user;
		while (getline(MyFile, Line))
		{
			user = final_user_info(Line, delim);
			Users.push_back(user);
		}
		MyFile.close();
	}
	return Users;
}

void Add_user(string filePath, string delim, vector<stuser_info>&users,bool signUp=false)
{
	stuser_info user;
		user = Read_New_user(signUp);
		while (user_by_userName_password(user,users))
		{
			cout << "user with [" << user.userName <<"] already exist,Enter another user Name and password?\n";
			cin >> user.userName;
			cout << "user Password?\n";
			cin >> user.Password;
		}
		Add_info_in_file(filePath, one_line_user_info(user, delim));
		cout << "\nuser added successfully.\n";
		users = Load_Users_info_From_File(file_path_for_login, delim_for_users_login_info);
		if (signUp)
			login_actions(users);
}

void add_users_in_file(string filePath, string delim, vector<stuser_info> users)
{
	bool want = 0;
	do
	{
		Add_user(filePath, delim, users,false);
		cout << "\ndo you want to add more users ?1[yes] 0 [No]." << endl;
		cin >> want;
	} while (want);
}

vector<strecord>Load_Cleints_Data_From_File(string FileName, string delim)
{
	vector <strecord> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		strecord Client;
		while (getline(MyFile, Line))
		{
			Client = finalrecord(Line, delim);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void mark_client_to_delete(vector<strecord>& records, int index) {
	records[index - 1].mark_for_delete = true;
}

void mark_user_to_delete(vector<stuser_info>& users, int index) {
	if (users[index - 1].userName == "Mohamed yousry")
	{
		cout << "you can't delete this user .\n";
	}
	else
	users[index - 1].mark_for_delete = true;
}

void update_client_content(vector<strecord>& records, int index) {
	cout << "Enter Name? ";
	getline(cin >> ws, records[index - 1].Name);
	cout << "Enter PinCode?";
	getline(cin, records[index - 1].PinCode);
	cout << "Enter Phone?";
	getline(cin, records[index - 1].Phone);
	cout << "Enter AccountBalance?";
	cin >> records[index - 1].Balance;
}

void update_User_content(vector<stuser_info>& users, int index) {
	cout << "Enter user Name? ";
	getline(cin >> ws, users[index - 1].userName);
	cout << "Enter Password?";
	getline(cin, users[index - 1].Password);
}

void update_client_by_account_Number(string filePath, string delim, vector<strecord>& records)
{
	string number = accNumber();
	int index;
	index = client_by_account_number(number, records);
	if (index)
	{
		cout << "\nthe following is the client details : \n";
		print_client_info(records[index - 1]);
		char yes = 'n';
		cout << "\nAre you sure you want to update this client ?y/n \n";
		cin >> yes;
		if (yes == 'y' || yes == 'Y')
		{
			update_client_content(records, index);
			vector_content_to_file(filePath, delim, records);
			cout << "\ncleint updated succesfully\n";
			return;
		}
	}
	else
		cout << "client with account number [" << number << "] is NOT found !!?";
}

void update_user_by_user_pass(string filePath, string delim, vector<stuser_info>& users)
{
	stuser_info temp = temp_user();
	int index;
	index = user_by_userName_password(temp, users);
	if (index)
	{
		cout << "\nthe following is the user details : \n";
		print_user(users[index - 1]);
		char yes = 'n';
		cout << "\nAre you sure you want to update this User ?y/n \n";
		cin >> yes;
		if (yes == 'y' || yes == 'Y')
		{
			update_User_content(users, index);
			vector_users_to_file(filePath, delim, users);
			cout << "\nuser updated succesfully\n";
			return;
		}
	}
	else
		cout << "user with user name [" << temp.userName << "] is NOT found !!?";
}

void delete_client_by_account_Number(string filePath, string delim, vector<strecord>& records)
{
	string number = accNumber();
	int index;
	index = client_by_account_number(number, records);
	if (index)
	{
		print_client_info(records[index - 1]);
		char yes = 'n';
		cout << "\nAre you sure you want to delete this client ?y/n \n";
		cin >> yes;
		if (yes == 'y' || yes == 'Y')
		{
			mark_client_to_delete(records, index);
			vector_content_to_file(filePath, delim, records);
			cout << "\ncleint deleted succesfully\n";
			return;
		}
	}
	else
	{
		cout << "Client with account Number [" << number << "] is not found!!\n";
	}
}

void delete_User_by_userName_pass(string filePath, string delim, vector<stuser_info>& users)
{
	stuser_info temp = temp_user();
	int index;
	index = user_by_userName_password(temp, users);
	if (index)
	{
		print_user(users[index - 1]);
		char yes = 'n';
		cout << "\nAre you sure you want to delete this User ?y/n \n";
		cin >> yes;
		if (yes == 'y' || yes == 'Y')
		{
			mark_user_to_delete(users, index);
			vector_users_to_file(filePath, delim, users);
			cout << "\nuser deleted succesfully\n";
			return;
		}
	}
	else
	{
		cout << "User with user Name [" << temp.userName << "] is not found!!\n";
	}
}

void Add_new_client_screen(vector<strecord> records)
{
	cout << "------------------------------------------\n";
	cout << "        Add New client screeen            \n";
	cout << "------------------------------------------\n";
	cout << "Adding new client:\n";
	Add_clients(file_Path_for_clients, delim_for_clients, records);
}

void Add_new_User_screen(vector<stuser_info> Users)
{
	cout << "------------------------------------------\n";
	cout << "               Add New User               \n";
	cout << "------------------------------------------\n";
	cout << "Adding new User:\n";
	add_users_in_file(file_path_for_login, delim_for_users_login_info, Users);
}

void Delete_client_screen(vector<strecord> records)
{
	cout << "------------------------------------------\n";
	cout << "          Delete client screeen           \n";
	cout << "------------------------------------------\n";
	cout << "Deleting client:\n";
	delete_client_by_account_Number(file_Path_for_clients, delim_for_clients, records);
}

void Delete_User_screen(vector<stuser_info> users)
{
	cout << "------------------------------------------\n";
	cout << "               Delete User                \n";
	cout << "------------------------------------------\n";
	cout << "Deleting User:\n";
	delete_User_by_userName_pass(file_path_for_login, delim_for_users_login_info, users);
}

void Update_client_screen(vector<strecord> records)
{
	cout << "------------------------------------------\n";
	cout << "                 Update Client            \n";
	cout << "------------------------------------------\n";
	cout << "Updating client:\n";
	update_client_by_account_Number(file_Path_for_clients, delim_for_clients, records);
}

void Update_user_screen(vector<stuser_info> users)
{
	cout << "------------------------------------------\n";
	cout << "                 Update User              \n";
	cout << "------------------------------------------\n";
	cout << "Updating User:\n";
	update_user_by_user_pass(file_Path_for_clients, delim_for_clients, users);
}

void Find_client_screen()
{
	cout << "----------------------------------------------------------\n";
	cout << "                  Find client screen                      \n";
	cout << "---------------------------------------------------------\n";
	cout << "finding client :";
}

void Find_User_screen()
{
	cout << "----------------------------------------------------------\n";
	cout << "                       Find user                          \n";
	cout << "----------------------------------------------------------\n";
	cout << "finding User :";
}

void deposit_action(vector<strecord>& records)
{
	string account_number;
	account_number=accNumber();
	int index = client_by_account_number(account_number, records);
	if (index)
	{
		string deposit_number;
		print_client_info(records[index - 1]);
		cout << "\nplease enter deposit amount?";
		cin >> deposit_number;
		char y;
		cout << "\nare you sure you want to perform this transaction?y/n ";
		cin >> y;
		if (y == 'y' || y == 'Y')
		{
			float new_balance;
			records[index - 1].Balance = records[index - 1].Balance + stof(deposit_number);
			new_balance = records[index - 1].Balance;
			vector_content_to_file(file_Path_for_clients, delim_for_clients, records);
			cout << "this transaction is done new Balance is = " << new_balance << endl;
		}
	}
	else
		cout << "client with [" << account_number << "] is not found!!?";
}

void deposit_screen(vector<strecord>& records)
{

	cout << "------------------------------------------\n";
	cout << "               deposit screeen            \n";
	cout << "------------------------------------------\n";
	deposit_action(records);
}

void withdraw_action(vector<strecord>& records)
{
	string account_number;
	account_number = accNumber();
	int index = client_by_account_number(account_number, records);
	if (index)
	{
		string withdraw_number;
		print_client_info(records[index - 1]);
			cout << "\nplease enter withdraw amount?";
			cin >> withdraw_number;
			while (stof(withdraw_number) > records[index - 1].Balance)
			{ 
				cout << "amount exeeded the balance ,you can withdraw up to : " << records[index - 1].Balance ;
				cout << "\nplease enter withdraw amount?";
				cin >> withdraw_number;
		    }
			char y;
			cout << "are you sure you want to perform this transaction ?y/n\n";
			cin >> y;
			if (y == 'y' || y == 'Y')
			{
				float new_balance;
				records[index - 1].Balance = records[index - 1].Balance - stof(withdraw_number);
				new_balance = records[index - 1].Balance;
				vector_content_to_file(file_Path_for_clients, delim_for_clients, records);
				cout << "this transaction is done new Balance is = " << new_balance << endl;
			}	
	}
	else
		cout << "client with [" << account_number << "] is not found!!?";
}

void withdraw_screen(vector<strecord>& records)
{

	cout << "------------------------------------------\n";
	cout << "               Withdraw screeen            \n";
	cout << "------------------------------------------\n";
	withdraw_action(records);
}

void Total_action(vector<strecord>& records)
{
	float total=0;
	for (int i = 0; i < records.size(); i++)
	{
		total += records[i].Balance;
	}
	print_balance_info(records);
	for (int i = 0; i < records.size(); i++)
	{
		print_client_blances(records[i]);
	}
	cout << "                                             Total balances =" << total << endl;
}

void Total_balances_screen(vector<strecord>& records)
{

	cout << "------------------------------------------\n";
	cout << "               Total balances screeen            \n";
	cout << "------------------------------------------\n\n";
	Total_action(records);
}

entransactions_options trans_option()
{
	int option;
	cout << "Choose what do you want to do?[1:4]\n";
	cin >> option;
	return (entransactions_options)option;
}

void trans_menu_flow()
{
	int index = -1;
	vector<strecord> records;
	records = Load_Cleints_Data_From_File(file_Path_for_clients, delim_for_clients);

	switch (trans_option())
	{
	case entransactions_options::deposit:
		system("cls");
		deposit_screen(records);
		Home_page_transaction();
		break;
	case entransactions_options::withdraw:
		system("cls");
		withdraw_screen(records);
		Home_page_transaction();
		break;
	case entransactions_options::total_balances:
		system("cls");
		Total_balances_screen(records);
		Home_page_transaction();
		break;
	case entransactions_options::main_menu:
		system("cls");
		Home_page();
		break;
	}
}

void transaction_screen()
{
	system("cls");
	cout << "=====================================================================================================\n";
	cout << "======================================  transactions menu screen  ================================== \n";
	cout << "=====================================================================================================\n";
	cout << "            [1] Deposit.\n";
	cout << "            [2] Withdraw.\n";
	cout << "            [3] Total balances.\n";
	cout << "            [4] Main menu.\n";
	cout << "====================================================================================================\n";
	trans_menu_flow();
}

enoptions_main_menu take_option_from_menu()
{
	int option;
	cout << "Choose what do you want to do?[1:8]\n";
	cin >> option;
	return (enoptions_main_menu)option;
}

enoptions_User_menu choose_in_user_menu()
{
	int option;
	cout << "Choose what do you want to do?[1:6]\n";
	cin >> option;
	return (enoptions_User_menu)option;
}

void Access_Denied_Screen()
{
	cout << "___________________________________________________________________\n";
	cout << "Access Denied.\n";
	cout << "You don't have permission to do this ,\n";
	cout << " Please Contact Your Admin\n";
	cout << "___________________________________________________________________\n";
}

void User_menu_flow()
{
	int index = -1;
	vector<stuser_info> users;
	users = Load_Users_info_From_File(file_path_for_login, delim_for_users_login_info);
	switch (choose_in_user_menu())
	{
	case enoptions_User_menu::list_Users:
		system("cls");
		print_User_header(users);
		printv_users(users);
		manage_user_page();
		break;
	case enoptions_User_menu::add_user:
		system("cls");
		Add_new_User_screen(users);
		manage_user_page();
		break;
	case enoptions_User_menu::delete_user:
		system("cls");
		Delete_User_screen(users);
		manage_user_page();
		break;
	case enoptions_User_menu::update_user:
		system("cls");
		Update_user_screen(users);
		manage_user_page();
		break;
	case enoptions_User_menu::find_user:
		system("cls");
		Find_User_screen();
		index = user_by_userName_password(temp_user(), users);
		if (index)
			print_user(users[index - 1]);
		else
			cout << "User not found !!?\n";
		manage_user_page();
		break;
	case enoptions_User_menu::Main_menu:
		system("cls");
		Home_page();
		break;
	}
}

void manage_users_screen()
{
	system("cls");
	cout << "=====================================================================================================\n";
	cout << "===================================manage user screeen============================================== \n";
	cout << "=====================================================================================================\n";
	cout << "            [1] Lists Users\n";
	cout << "            [2] Add new User.\n";
	cout << "            [3] Delete User.\n";
	cout << "            [4] Update User.\n";
	cout << "            [5] Find User.\n";
	cout << "            [6] Main menu.\n";
	cout << "====================================================================================================\n";
	User_menu_flow();
}

void refactor_user_input_for_access_program_flow()
{
	int currentper = user_logined.permission;
	short index=-1;
	vector<strecord> records;
	records = Load_Cleints_Data_From_File(file_Path_for_clients, delim_for_clients);
	switch (take_option_from_menu())
	{	
	case enoptions_main_menu::list_clients:
		if ((currentper & 1)||currentper==-1) {
		system("cls");
		printinfo_header(records);
		printv_records(records);
		Home_page();
		}
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
		break;
	case enoptions_main_menu::add_client:
		if ((currentper & 2)|| currentper == -1) {
		system("cls");
		Add_new_client_screen(records);
		Home_page();
		}
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
		break;
	case enoptions_main_menu::delete_client:
		if ((currentper & 4)|| currentper == -1) {
		system("cls");
		Delete_client_screen(records);
		Home_page();
	   }
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
			break;
	case enoptions_main_menu::update_client:
		if ((currentper & 8)|| currentper == -1) {
			system("cls");
			Update_client_screen(records);
			Home_page();
		}
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
			break;
	case enoptions_main_menu::find_client:
		if ((currentper & 16)|| currentper == -1) {
		system("cls");
		Find_client_screen();
		index = client_by_account_number(accNumber(), records);
		if (index)
			print_client_info(records[index - 1]);
		else
			cout << "client is not found !!?\n";
		Home_page();
		}
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
			break;
	case enoptions_main_menu::transaction:
		if ((currentper & 32) || currentper == -1) {
		system("cls");
		transaction_screen();
		Home_page();
		}
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
		break;
	case enoptions_main_menu::manage_users:
		if ((currentper & 64)|| currentper == -1) {
			system("cls");
			manage_users_screen();
			Home_page();
		}
		else
		{
			system("cls");
			Access_Denied_Screen();
			Home_page();
		}
		break;
	case enoptions_main_menu::log_out:
		system("cls");
		log_out_screen();
		break;
	}
}

void sign_Up(vector<stuser_info> users)
{
	system("cls");
	sign_up_screen();
	Add_user(file_path_for_login, delim_for_users_login_info, users,true);
}

void sign_up_or_in()
{
	vector<stuser_info> users;
	users = Load_Users_info_From_File(file_path_for_login, delim_for_users_login_info);
	int y = 1;
	system("cls");
	welcome_screen();
	cout << "1-> sign_up\n\n2-> sign_in?\n\n enter 1 or 2\n";
	cin >> y;
	if (y == 1)
		sign_Up(users);
	else
		login_actions(users);
}

void log_out_screen()
{
	sign_up_or_in();
}

void main_menu_screen()
{
	system("cls");
	cout << "=====================================================================================================\n";
	cout << "==========================================Main menu screeen===================================== \n";
	cout << "=====================================================================================================\n";
	cout << "            [1] Show clients data.\n";
	cout << "            [2] Add new client.\n";
	cout << "            [3] Delete client.\n";
	cout << "            [4] Update client Info.\n";
	cout << "            [5] Find client.\n";
	cout << "            [6] transactions.\n";
	cout << "            [7] manage users.\n";
	cout << "            [8] Logout.\n";
	cout << "====================================================================================================\n";
	refactor_user_input_for_access_program_flow();
}

int main()
{
	sign_up_or_in();
	cout << "Press any key to end the program...";
	system("pause>0");
	return 0;
}