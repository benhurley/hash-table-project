/* Benjamin Hurley
   hashtable.hpp

   This file extension adds functionality to the declarations for
   creating and managing the hash table. Functions below are mine,
   and were created by me unless specifically noted.
*/

template <typename K, typename V>
HashTable<K, V>::HashTable(std::size_t size)
{
	int startingSize = prime_below(size);

	if (size <= 1 || size >= 32767)	// bounds on standard integer
	{
		startingSize = 5;
		std::cout << "Defaulting to " << startingSize << std::endl;
	}
	else
	{
		std::cout << "Finding prime number closest to " << size << "..." << std::endl;
		startingSize = prime_below(size);
		std::cout << "\n Creating Hash Table of Size " << prime_below(size) << "." << std::endl;
	}

	// resize vector
	theLists.resize(startingSize);
}

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	makeEmpty();
}


template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k)
{
	// Check to see if key k is in hash table
	// (from lecture slides)
	auto & whichList = theLists[myhash(k)];

	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{
		if (itr->first == k) return true;
	}
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> & kv)
{
	// see if key value pair is in hash table
	auto & whichList = theLists[myhash(kv.first)];

	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{
		if (itr->first == kv.first && itr->second == kv.second)
			return true;
	}
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv)
{
	// insert pair into table
	auto & whichList = theLists[myhash(kv.first)];

	whichList.push_back(kv);

	if (++currentSize > theLists.size())
		rehash();

	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv, const K & k)
{
	// insert pair
	auto & whichList = theLists[myhash(kv.first)];

	// check if it already exists
	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{
		// check if new password equals old
		if (itr->first == kv.first && itr->second == k)
		{
			return false;
		}
		else if (itr->first == kv.first && itr->second != k)
		{
			std::cout << "Changing Password..." << std::endl;
			itr->second = k;
			return true;
		}
	}

	return true;
}
template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> && kv)
{
	// insert pair (move)
	auto & whichList = theLists[myhash(kv.first)];

	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{
		if (itr->first == kv.first && itr->second == kv.second)
			return false;
	}

	whichList.push_back(std::move(kv));

	if (++currentSize > theLists.size())
		rehash();

	return true;

}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
	// delete key k and corresponding value
	auto & whichList = theLists[myhash(k)];

	// for loop to find
	for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
	{
		if (itr->first == k)
		{
			whichList.erase(itr);
			--currentSize;
			return true;
		}
	}

       return false;
}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
	theLists.clear();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename)
{
	std::ifstream inFile(filename);

	if (!inFile.is_open())	return false;
	else
	{
	  std::string line;
	  std::pair<std::string, std::string> x;

	  while(getline(inFile, line))
	  {
		std::istringstream iss(line);
		iss >> x.first >> x.second;
		insert(x);
	  }
	}
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump()
{
	// display contents of table
	bool flag = false;

	for (int i = 0; i < theLists.size(); ++i)
	{
		std::cout << "v[" << i << "]= ";

		auto & whichList = theLists[i];

		for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
		{
			if (flag)	std::cout << " : ";

			std::cout << itr->first << " " << itr->second;
			flag = true;
		}

		std::cout << std::endl;
		flag = false;
	}

}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename)
{
	std::ofstream outFile;

	outFile.open(filename);

	if (!outFile.is_open())	return false;
	else
	{
 	   for (int i = 0; i < theLists.size(); ++i)
	   {
		auto & whichList = theLists[i];

		for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
		{
			outFile << itr->first << " " << itr->second << std::endl;
		}
	   }
	}

	outFile.close();

	return true;
}

template <typename K, typename V>
size_t HashTable<K, V>::size()
{
	return currentSize;
}


// private functions

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
	for (auto & thisList: theLists)
	{
		thisList.clear();
	}
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	std::vector< std::list < std::pair<K, V>>> oldLists = theLists;

	// create new double-sized, empty table
	theLists.resize(prime_below(2 * theLists.size()));

	for (auto & thisList: theLists)
		thisList.clear();

	//copy table over
	currentSize = 0;

	for (auto & thisList: oldLists)
		for (auto & x: thisList)
			insert(std::move(x));
}

template <typename K, typename V>
std::size_t HashTable<K, V>::myhash(const K & k)
{
	static std::hash<K> hf;
	return hf(k) % theLists.size();
}

// Below functions provided by University, i did not create.

// This returns largest prime number <= n or 0 if too big or small.
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n == max_prime)
  {
    return max_prime;
  }
  
  if (n > max_prime)
  {
    std::cerr << "*** WARNING: Choice is too large. ***\n";
    return 0;
  }

  if (n <= 1)
  {
	std::cerr << "*** WARNING: Choice is too small. ***\n";
    return 0;
  }

  if (n >= 32767)
  {
	 std::cerr << "*** WARNING: CHoice is too big. ***\n"; 
	 return 0;
  }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

