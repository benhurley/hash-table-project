# Hash Table Project - Credential Manager

This project simulates how usernames and passwords are hashed, stored, and managed in the backend of a web or mobile application.

## Getting Started

To get started, grab the https link above and clone this repo to your local machine
```
git clone https://github.com/thebenhurley/hash-table-project.git
```

Next, run a g++ build locally using the makefile included in the project
```
make
```

Finally, run the executable
```
./hashTable.exe
```

## Prerequisites

In order to clone and run this project, you will need the following:
1. git (to clone the project) 
2. g++ (to compile and create the executable)

## How it works

### Intro
This project begins with a prompt asking how large of a hash table you would like to work on (array size). Any number between 2 and 32767 will be accepted, others will be rejected and the hash table will default to 5. Hash table will be resized dynamically if needed.

If a valid number is provided, the closest prime number less than or equal to the desired number will be the size of the table created. So for example, if the number 10 is requested, the table will be initalized to size 7. 

### Main Menu
Upon creation of the hash table, the main menu will appear. You can then choose which action you would like to perform. Invalid entries will be denied. Entries are also case sensitive, and need to be lowercase.

#### l - Load User Data from File
This action will prompt the user for the password file name to load from and then upload the contents into the hash table. The file format for this action requires a valid username and a previously-hashed password from this program (with a single space separating the two). 

Easiest way to use this function is to add users manually the first time, [write to a new password ile](####w - Write to Password file), and then load that new file back in.

I included [test_load.txt](#### test_load.txt) as an example. You will have to move from tests directory into same directory as the executable for the program to be able to find it.

#### a - Add User
This action will allow you to manually add a user to the system. Enter a username followed by a password for the user. Will respond with "User Added" if done correctly. The hash table can be [dumped](#### d - Dump HashTable) afterwards to see the new user in the table.

#### r - Remove User
This action will remove a user from the system. The username of the profile to be removed must be provided. Will respond with "User Removed" if done correctly.

#### c - Change User Password
This action will allow you to change a users password. The username and current password must be required first in order to do so. If the new password matches the current password, the system will not let you make the change (notices the same key mapping to the same hashed password).

#### f - Find User
This action looks to see if a user exists in the system. Requires the username of the profile in question. Will respond with "User [username] Has Been Found" if done correctly.

#### d - Dump HashTable
This action prints the contents of the hash table to the console. You will be able to see the indexes of the table, the un-encrypted username, and the hashed password.

#### s - HashTable Size
This action prints the size of the hash table to the screen (Size being number of users entered into the system).

#### w - Write to Password file
This action writes the contents of the hash table into a file. The desired filename should be given.

**Note: This action will overwrite a file if the name given matches the name of a file in the working directory. A new file name is recommended.**

#### x - Exit Program
This action ends the simulation.

## Breakdown of the Hashing Algorithm
This program uses crypt(3) to hash the passwords given. Due to it's OS-specific implementation, there will be differences in output based on which operating system you are using. 

#### Linux
Linux glibc uses the salt of the password to determine the type of hash generated. As stated in the [crypt.3](http://man7.org/linux/man-pages/man3/crypt.3.html) manpage
```
 If salt is a character string starting with the characters "$id$" followed by
   a string terminated by "$":

          $id$salt$encrypted

   then instead of using the DES machine, id identifies the encryption method
   used and this then determines how the rest of the password string is
   interpreted.  The following values of id are supported:

          ID  | Method
          ---------------------------------------------------------
          1   | MD5
          2a  | Blowfish (not in mainline glibc; added in some
              | Linux distributions)
          5   | SHA-256 (since glibc 2.7)
          6   | SHA-512 (since glibc 2.7)
```

The Linux crypt function lives in <crypt.h>, which differs now from other operating systems. This project was oringially built to be linux-specific, but was recently modified to also work on [macOS](#### macOS).

The program currently uses the MD5 encryption algorithm (ID 1) on Linux and creates a 22-character string for the hashed password. 

#### macOS
The OSX implementation of crypt() uses DES encryption (does not include options to choose other algorithms). Additionally, OSX did away with the separate <crypt.h> library and moved the crypt function into <unistd.h>.

To keep the project working on macOS, the following changes were made:
1. <crypt.h> libraries were removed from the project.
2. the `-lcrypt` flag was removed from the makefile

The DES algorithm results in a 13-character string for the hashed password.

## Tests

Two different tests have been included in the /tests directory. 

**Note: The tests should be moved back into the same directory as the executable when desired Otherwise they will not be found.**

#### test_load.txt
This text file can be used while the program is running to [Load User Data From File](#### l - Load User Data From File). This will load six example users into the hash table.

#### test_input.txt
This text file can be passed into the executable as input to replace keyboard entries. I would also recommend redirecting the output into a new text file.

Example run
```
cat test_input.txt | ./hashTable.exe > output.txt
```

This test works through all of the menu options and was used for testing / grading.

## Acknowledgments

FSU Department of CS for project skeletons
