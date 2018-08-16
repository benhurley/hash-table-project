/* Benjamin Hurley
   passserver.h

   This header file declares the helper functions that
   pass operations over to the hash functions.
*/

#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include <string>
#include <cstring>

namespace hashProject
{
  class PassServer
  {
     // private
     std::string encrypt(const std::string & str);
     HashTable<std::string, std::string> * table;

     public:
	PassServer(std::size_t size = 101);
	~PassServer();
	bool load(const char* filename);
	bool addUser(std::pair<std::string, std::string> & kv);
	bool addUser(std::pair<std::string, std::string> && kv);
	bool removeUser(const std::string & k);
	bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword); 
	bool find(const std::string & user);
	void dump();
	std::size_t size();
	bool write_to_file(const char* filename);
  };

}	// end of namespace

#endif 
