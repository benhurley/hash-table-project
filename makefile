# Benjamin Hurley
# makefile

hashTable.exe: sproj5.cpp passserver.cpp
	g++ -std=c++11 -Wall -pedantic sproj5.cpp passserver.cpp -o hashTable.exe

clean:
	rm hashTable.exe
