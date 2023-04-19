#include <iostream>
#include <fstream>
#include <string>
#include "RecLine.h"
#define INT_SIZE 32
using namespace std;
int main(int argc, char** argv)
{

int cycles = 0;
char ch;
	string str;
	unsigned int result;
	int FirstDegree_1 = 33;
	int SecondDegree_1 = 13;
	int FirstDegree_2 = 134;
	int SecondDegree_2 = 57;
	long long unsigned int byte = 0;
	RecLine first_rec(FirstDegree_1, SecondDegree_1);
	RecLine second_rec(FirstDegree_2, SecondDegree_2);
	cout << "Enter number of cycles : ";
	cin >> cycles;
//	cout << numbers << endl;
	 long long unsigned int ResultSequence=0;
		for (int i=0;i<cycles;i++){
		result =first_rec.GetFBbit() ^ second_rec.GetFBbit();
		ResultSequence <<= 1;
		ResultSequence += result;
		}
		cout<<ResultSequence<<endl;
	ifstream in;
	in.open("123.bmp", ios::binary | ios::in);
	int size = 0;
	in.seekg(0,ios::end);
	cout << in.tellg() << endl;
	size = in.tellg();
	cout << "File size : " << size << " bytes" << endl;
	cout << "Without header ?" << endl;
	cin >> str;
	in.seekg(0, ios::beg);
	ofstream out;
	string path = "123_copy.bmp";
	out.open(path, ios::binary);
	int counter = 0;
	if (out.is_open()){

		if (str == "yes") {
			for (int i = 0; i < 54; i++) {
				in.read(reinterpret_cast<char*>( & ch), sizeof(unsigned char));
				out.write(reinterpret_cast<char*>(&ch), sizeof(unsigned char));
			}
		}
	while (in.read(reinterpret_cast<char*>(&ch), sizeof(unsigned char)))
	{

		ch ^= (ResultSequence>>counter);
		out.write(reinterpret_cast<char*>(&ch), sizeof(unsigned char));
		counter+=8;
		if (counter == 64) {
			counter = 0;
		}
	}
	cout << "its ok" << endl;
	}
	else {
		cout << "couldn`t open" << endl;
	}
	in.close();
	out.close();


	return 0;
}