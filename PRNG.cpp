#include <iostream>
#include <ctime>
#include <C:\Users\ryask\source\repos\PRNG\PRNG\RecLine.h>
#define INT_SIZE 32
using namespace std;
RecLine::RecLine(int &FirstDegree, int &SecondDegree) {
	firstbit.isOne = 0b10000000000000000000000000000000u;
	firstbit.isZero =0b01111111111111111111111111111111u;
	FirstSummand.degree = FirstDegree;
	SecondSummand.degree = SecondDegree;
	AmountOfNumbers = (FirstDegree + INT_SIZE - 1) / INT_SIZE;
	Sequence = new unsigned int[AmountOfNumbers];
	unused_bits = INT_SIZE - (FirstSummand.degree % INT_SIZE);
	FirstSummand.reverseDegree = FirstDegree;
	SecondSummand.reverseDegree = -(SecondDegree - FirstDegree);
	FirstSummand.absolutePosition = INT_SIZE - FirstDegree % INT_SIZE + FirstSummand.reverseDegree;
	SecondSummand.absolutePosition = INT_SIZE - FirstDegree % INT_SIZE + SecondSummand.reverseDegree;
//	cout << "Reverse degree= " << FirstSummand.reverseDegree<< endl;
//	cout << "FirstSummand absolute position= " << FirstSummand.absolutePosition<<endl;
//	cout << "Reverse degree= " << SecondSummand.reverseDegree<< endl;
//	cout << "SecondSummand absolute position= " << SecondSummand.absolutePosition << endl;
	FirstSummand.Number = (FirstSummand.absolutePosition + INT_SIZE - 1) / INT_SIZE - AmountOfNumbers;
	SecondSummand.Number = abs((SecondSummand.absolutePosition + INT_SIZE - 1) / INT_SIZE - AmountOfNumbers);
//	cout << "First Number = " << FirstSummand.Number << endl;
//	cout << "Second Number = " << SecondSummand.Number << endl;
	FirstSummand.positionInNumber = FirstSummand.absolutePosition - INT_SIZE * abs(AmountOfNumbers - FirstSummand.Number -1);
//	cout << "FirstSummand.positionInNumber = " << FirstSummand.positionInNumber << endl;
	SecondSummand.positionInNumber = SecondSummand.absolutePosition - INT_SIZE * abs(AmountOfNumbers - SecondSummand.Number - 1);
//	cout << "SecondSummand.positionInNumber = " << SecondSummand.positionInNumber << endl;
	this->CreateRandomSequence();
//	cout << "unused bits= " << unused_bits<<endl;
}

RecLine::~RecLine() {
	delete [] Sequence;
}

void RecLine::CreateRandomSequence() {
	int RandomBit = 0;
	srand(time(NULL));
	for (int i=0; i < AmountOfNumbers; i++) {
		cout << "Sequence[" << i << "]=";
		Sequence[i] = 0;
		for (int bits = 0; bits < INT_SIZE; bits++) {
			RandomBit = rand() % 2;
			Sequence[i] <<= 1;
			Sequence[i] += RandomBit;
			cout << RandomBit;
		}
		cout << endl;
	}
}

int RecLine::GetFBbit() {
	unsigned int Firstbit = (Sequence[FirstSummand.Number] >> (INT_SIZE - FirstSummand.positionInNumber));
		if ((Firstbit << 31) == 0) {
//			cout << "Firstbit = 0" << endl;
		} else if ((Firstbit << 31) == INT32_MAX+1) {
//			cout << "Firstbit = 1" << endl;
			}
		unsigned int Secondbit = (Sequence[SecondSummand.Number] >> (INT_SIZE - SecondSummand.positionInNumber));
		if ((Secondbit << 31) == 0) {
//			cout << "Secondbit = 0" << endl;
		}
		else if ((Secondbit << 31) == INT32_MAX + 1) {
//			cout << "Secondbit = 1" << endl;
		}
	fb_bit =((Sequence[FirstSummand.Number]>>(INT_SIZE - FirstSummand.positionInNumber))^(Sequence[SecondSummand.Number]>>(INT_SIZE - SecondSummand.positionInNumber))) & 0x1;
	this->SequenceOffset();
//	cout << fb_bit << endl;
	return fb_bit;
}
void RecLine::SequenceOffset() {
	for (int i = 0; i < AmountOfNumbers; i++) {
		Sequence[i] >>= 1;
		if (i != (AmountOfNumbers - 1)) {
			if ((Sequence[i + 1] << 31) == firstbit.isOne) {
//				cout << "Added 1" << endl;
				Sequence[i] |= firstbit.isOne;
			}
			else {
//				cout << "Added 0" << endl;
			}
		}
		else {
			Sequence[i] <<= unused_bits;
			if (1 == fb_bit) {
				Sequence[i] |= firstbit.isOne;
//				cout << "Added 1" << endl;
			}
			else {
				Sequence[i] &= firstbit.isZero;
//				cout << "Added 0" << endl;

			} 
			Sequence[i] >>= (unused_bits);

		}
	}
}
//х^33 + х^13 + 1