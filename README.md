# Netvirta-Coding Challenge

This c++ project is created as part of job interview for Netvirta.
Following is the summary of the requirements given to implement:
- Write a program that searches a 2 dimensional matrix of integers for the row(s) that match a certain selected criteria (each criteria to be implemented as a separate search function)
- When the search program starts up, user must be able to indicate the matrix data file they will be using parameters (argc/argv)
- There are 3 search functions to implement:
    - Find all rows that have a specific sequence of numbers (if that number sequence appears more than once for that row, you only need to print it once)
    - Find all rows that contain all of the required numbers (if number repeats, that row must contain at least that many number)
    - Find the row that has the closest match to a specific number sequence (just need to consider the number of matches)
- Assume that the search function can be performed multiple times (with different number sequence) but using the same matrix data file.
- Assume that the matrix data contains sensitive information, it should not be stored in plain text
- Assume that the search function can be performed multiple times (with different number sequence) but using the same matrix data file
- You are expected to speed up the search time (ie. it should not be linear to the matrix element count)

#### Application Design
The application is written in C++ (C++11) and written on Ubuntu OS (16.04). Visual studio code was the IDE used.
The input to the application is a csv file and provided as command line argument. Since one of the requirement states that this input file has to be secure, the file has to be encrpyted. To achieve this, a submodule is provided which will encrpyt the input csv file. 

The enc_dec_file.cpp file contains the encryption and decryption logic. XOR cipher, A simple but effective encyption scheme is used to implement this. To build the submodule following build command needs to used. 
```sh
$ g++ -DCREATE_ENC_EXE -I./include ./src/enc_dec_file.cpp -o ./bin/encryptFile -std=c++11
```
The following shows an example of encrpting the input file using the created binary
```sh
$ ./encryptFile
Please provide the name of the file to be encrypted
testfile.csv
Please provide the path where testfile.csv exists
../data
The input file ../data/testfile.csv has been encrypted
The Encrypted file is ../data/enc-testfile.csv
```
The created file has to be used as input to the main search binary. The following command has to be used to build this binary.
```sh
$ g++ -g -I./include ./src/*.cpp -o ./bin/searchExe -std=c++11
```
The following example shows the opearation of the binary.
```sh
$ $ cat ../data/testfile.csv
1,2,4,5,7,10,30,51
6,10,5,25,1,25,90,-14
10,5,25,6,7,8,30,515
$ cat ../data/enc-testfile.csv
ifz}~amyiefeadm{t
xiefegxs{iez{gxx~iyg}
uxce`amxiczq~gqbpec

$ ./searchExe ../data/enc-testfile.csv

Available Search Commands
1. searchOrdered <sequence of integers>
2. searchUnordered <sequence of integers>
3. searchClosest <sequence of integers>

use "exit" command to exit program
searchOrdered 10 5 25
2 1
searchUnordered 515 10 7
2
searchClosest 10 -14 199 2
0 1 
```