#pragma once
#include <cmath>
struct SummandPointer
{
	int degree;
	int absolutePosition;
	int reverseDegree;
	int positionInNumber;
	int Number;
};
struct FirstBit {
	unsigned int isOne;
	unsigned int isZero;
};
class RecLine {
public:
	RecLine(int &FisrtDegree,int &SecondDegree);
	~RecLine();
	int AmountOfNumbers = 0;
	int RandomSequence = 0;
	int fb_bit = 0;
	int unused_bits = 0;
	FirstBit firstbit;
	
	SummandPointer FirstSummand;
	SummandPointer SecondSummand;
	unsigned int* Sequence;
	void CreateRandomSequence();
	int GetFBbit();
	void SequenceOffset();
private:

};
