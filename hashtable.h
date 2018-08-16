/* Benjamin Hurley
   hashtable.h

   This file includes necessary dependencies and declarations to
   make and manage the hash table. Skeleton was provided by
   University, and I do not own. Changes earmarked below are mine,
   and were added by me.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

namespace hashProject
{
	template <typename K, typename V>
	class HashTable
	{	
	 // private
		std::vector< std::list < std::pair<K, V> > > theLists;
		size_t currentSize;

		// max_prime is used by the helpful functions provided
		// to you.
		static const unsigned int max_prime = 1301081;
		// the default_capacity is used if the initial capacity 
		// of the underlying vector of the hash table is zero. 
		static const unsigned int default_capacity = 11; 

		// Added by Benjamin Hurley...

		void makeEmpty();
		void rehash();
		std::size_t myhash(const K & k);
		unsigned long prime_below(unsigned long);
		void setPrimes(std::vector<unsigned long> &);

	 public:
		explicit HashTable(std::size_t size);
		~HashTable();
		bool contains(const K & k);
		bool match(const std::pair<K, V> & kv);
		bool insert(const std::pair<K, V> & kv);
		bool insert(const std::pair<K, V> & kv, const K & k);
		bool insert(std::pair<K, V> && kv);
		bool remove(const K & k);

		void clear();
		bool load(const char* filename);
		void dump();
		bool write_to_file(const char* filename);
		size_t size();
	};

 #include "hashtable.hpp"

} // end of namespace

#endif
