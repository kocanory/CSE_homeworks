#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HMM {

	string DNAseq;
	vector<int> codingRegion;
	int exonNum;
	int DNALen;
	double HMMprob[2][4]; // Exon/Intron, A/T/C/G

public:
	HMM(int len) {
		DNALen = len;
		codingRegion.resize(len);
	}

	void getExonLoc() {
		
		int exonStart;
		int exonEnd;

		cout << "========================" << endl;
		cout << "Number of exons: ";
		cin >> exonNum;
		
		for (int i = 0; i < exonNum; i++) {
			cout << "Start location of exon" << i + 1 << ": ";
			cin >> exonStart;
			cout << "End location of exon" << i + 1 << ": ";
			cin >> exonEnd;

			for (int j = exonStart; j <= exonEnd; j++) {
				codingRegion[j] = 1;
			}

			cout << endl;
		}
		cout << "========================" << endl << endl;
	}

	void getDNAseq() {

		string tmpDNA;
		cout << "Input DNA sequence: ";
		cin >> tmpDNA;

		DNAseq = tmpDNA;
	}

	void makeHMMprob() {

		int countNeucleo[2][4] = { 0, }; // Exon/Intron, A/T/C/G

		for (int i = 0; i < DNALen; i++) {
			if (codingRegion[i] == 1) {
				switch (DNAseq[i]) {
				case 'A':
					countNeucleo[0][0] += 1;
					break;
				case 'T':
					countNeucleo[0][1] += 1;
					break;
				case 'C':
					countNeucleo[0][2] += 1;
					break;
				case 'G':
					countNeucleo[0][3] += 1;
					break;
				default:
					cout << "Not a neucleotide expected!!" << endl;
					exit(1);
				}
			}
			else {
				switch (DNAseq[i]) {

				case 'A':
					countNeucleo[1][0] += 1;
					break;
				case 'T':
					countNeucleo[1][1] += 1;
					break;
				case 'C':
					countNeucleo[1][2] += 1;
					break;
				case 'G':
					countNeucleo[1][3] += 1;
					break;
				default:
					cout << "Not a neucleotide expected!!" << endl;
					exit(1);
				}
			}
		}

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				HMMprob[i][j] = countNeucleo[i][j] / (double) DNALen;
			}
		}
	}

	void printHMMProb() {
		cout << "==================< HMM Probability >==================" << endl;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				cout << fixed;
				cout.precision(3);
				cout << HMMprob[i][j] << '/t' << "|";
			}
			cout << endl;
		}
		cout << "=======================================================" << endl;
	}
};

int main() {

	HMM DNA_1(28);
	DNA_1.getDNAseq();
	DNA_1.getExonLoc();
	DNA_1.makeHMMprob();
	DNA_1.printHMMProb();
}