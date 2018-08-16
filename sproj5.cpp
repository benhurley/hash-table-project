// Benjamin Hurley
// proj5.cpp (driver)

#include <iostream>
#include "passserver.h"
#include <cstring>

// libraries for password hiding
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;
using namespace hashProject;

void Menu();
// functions for password hiding
string hidePassword(const char* prompt, bool show_asterisk=true);
int getch();

int main()
{
	char choice;
	size_t size;

    cout << "\n";
	cout << "--------------------------------------" << endl;
    cout << "|| CREDENTIALS MANAGER - SIMULATION ||" << endl;
	cout << "--------------------------------------" << endl;

    cout << "\n";
	cout << "Welcome. Enter preferred Hash Table capacity to begin: ";
	cin >> size;

	PassServer p(size);

  do
  {
	cout << endl;

	Menu();
	cin >> choice;

	if (choice == 'l')
	{
		// load from file into hash table
		string file;
		bool result;

		cout << "Enter password file name to load from: ";
		cin >> file;

		const char * filename = file.c_str();

		result = p.load(filename);

		if (result == false)   cout << "Error" << endl;
	}
	else if (choice == 'a')
	{
		// add user
	        string username;
	        string password;

	        cout << "Enter new Username: ";
	        cin >> username;
			
			cin.ignore();
			password = hidePassword("Enter new Password: ",true);

		// create pair
		pair<string, string> x;

		x.first = username;
		x.second = password;

		bool result = p.addUser(x);

		if (result == false) cout << "Error" << endl;
		else cout << "User Added" << endl;
	}
	else if (choice == 'r')
	{
		// remove user
		string username;

		cout << "Enter Username: ";
		cin >> username;

		// stub: would like to add password check before removing

		bool result = p.removeUser(username);

		if (result == false) cout << "Error" << endl;
		else cout << "User Removed" << endl;
	}
	else if (choice == 'c')
	{
		// change user password

		string username;
		string oldPassword;
		string newPassword;

		pair<string, string> x;

		cout << "Enter Username: ";
		cin >> username;
		x.first = username;
		cin.ignore();

        oldPassword = hidePassword("Enter Current Password: ",true);
		x.second = oldPassword;

        newPassword = hidePassword("Enter New Password: ",true);

		bool result = p.changePassword(x, newPassword);

		if (result == false) cout << "Error" << endl;
	}
	else if (choice == 'f')
	{
		// find user
		string username;

		cout << "Enter Username: ";
		cin >> username;

		bool result = p.find(username);

		if (result == false) cout << "Could not find user." << endl;
		else cout << "Username '" << username << "' Has Been Found." << endl;
	}
	else if (choice == 'd')
	{
		// dump hashtable
		p.dump();
	}
	else if (choice == 's')
	{
		cout << "Size (in entries) of Hash Table: " << p.size() << endl;
	}
	else if (choice == 'w')
	{
		// write to file

		string filename;

		cout << "Enter Filename: ";
		cin >> filename;

		const char* changed = filename.c_str();

		bool result = p.write_to_file(changed);
		if (result == false) cout << "Error" << endl;
		else cout << "Info Written to file Successfully" << endl;
	}
	else if (choice != 'x')
	{
		// invalid
		cout << "*** Invalid Entry ***" << endl;
		cout << endl;
	}

   }while(choice != 'x');

	// exit
	cout << "Terminating Simulation..." << endl;

	return 0;
}

// Below function was provided by University
// The functions thay follow are sources, and are
// used to hide keyboard input from console for passwords.

void Menu()
{
    cout << "\n";
	cout << "--------------------------------" << endl;
	cout << "||          Main Menu          ||" << endl;
	cout << "--------------------------------" << endl;
    cout << "l - Load User Data from File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

// hidePassword function for password hiding
// Code Source: http://www.cplusplus.com/articles/E6vU7k9E/
string hidePassword(const char *prompt, bool show_asterisk)
{
  const char BACKSPACE=127;
  const char RETURN=10;

  string password;
  unsigned char ch=0;
  show_asterisk = true;

  cout << prompt;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

// getch function for password hiding
// Code Source: http://www.cplusplus.com/articles/E6vU7k9E/
int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

