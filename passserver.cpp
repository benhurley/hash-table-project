/* Benjamin hurley
   passserver.cpp

   This file handles options selected from the menu and
   passes operations to lower-level functions to execute.

   Note: rvalue extensions are present, requiring C++11
*/

#include <iostream>
#include "passserver.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>

using namespace std;
using namespace hashProject;

PassServer::PassServer(std::size_t size)
{
	// make new table
	table = new HashTable<string, string>(size);
}


PassServer::~PassServer()
{
	// clear table
	table->clear();
}

bool PassServer::load(const char* filename)
{
	// load from file, then save to hash table
	bool result = table->load(filename);
	return result;
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv)
{
	// add user
	kv.second = encrypt(kv.second);
	bool result = table->insert(kv);
	return result;
}


bool PassServer::addUser(std::pair<std::string, std::string> && kv)
{
	// add user
	bool result = table->insert(std::move(kv));
	return result;
}


bool PassServer::removeUser(const std::string & k)
{
	// remove existing user
	bool result = table->remove(k);
	return result;
}

bool PassServer::changePassword(const pair<std::string, std::string> &p, const std::string & newpassword)
{
	string tempPassword = encrypt(newpassword);

	// check if user exists
	bool result1 = table->contains(p.first);
	if (result1 == false)
	{
		cout << "Cant Find User" << endl;
		return false;
	}
	// check if new password is same as old one
	if (newpassword == p.second)
	{
		cout << "Same Password" << endl;
		 return false;
	}
	// check if old password is correct
	pair<string, string> x;
	x.first = p.first;

	x.second = encrypt(p.second);

	bool result2 = table->match(x);
	if (result2 == false)
	{
		cout << "Existing Password is Incorrect" << endl;
		return false;
	}
	bool result3 = table->insert(p, tempPassword);
	if (result3 == false) return false;

	return true;
}

bool PassServer::find(const std::string & user)
{
	// find user in table
	bool result = table->contains(user);
	return result;
}

void PassServer::dump()
{
	// print contents of hash table to screen
	table->dump();
}

std::size_t PassServer::size()
{
	return table->size();
}

bool PassServer::write_to_file(const char* filename)
{
	return table->write_to_file(filename);
}


// private functions
string PassServer::encrypt(const std::string & str)
{
	char salt[] = "$1$########";

	char* password = new char[100];

	strcpy(password, crypt(str.c_str(), salt));

	return password;
}
