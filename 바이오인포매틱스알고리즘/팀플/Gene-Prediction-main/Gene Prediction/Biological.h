#pragma once

#include "Utility.h"

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


class Sequence_Generator
{
public:
	typedef vector<string> ProteinSequence;
	typedef string DnaSequence;
	typedef string RnaSequence;

private:
	string _Dna_Nucleobases = "ATGC";
	string _Rna_Nucleobases = "AUGC";
	vector<string> _Protein_List = { "Phe", "Leu", "Ile", "Val", "Ser", "Pro", "Thr", "Ala", "Tyr", "His", "Gln", "Asn", "Lys", "Asp", "Glu", "Cys", "Trp", "Arg", "Gly" };
	unordered_map<string, vector<string>> _Protein_Codon = {
		{"Phe", vector<string>{"UUU", "UUC"}},
		{"Leu", vector<string>{"UUA", "UUG", "CUU", "CUC", "CUA", "CUG"}},
		{"Ile", vector<string>{"AUU", "AUC", "AUA"}},
		{"Val", vector<string>{"GUU", "GUC", "GUA", "GUG"}},
		{"Ser", vector<string>{"UCU", "UCC", "UCA", "UCG", "AGU", "AGC"}},
		{"Pro", vector<string>{"CCU", "CCC", "CCA", "CCG"}},
		{"Thr", vector<string>{"ACU", "ACC", "ACA", "ACG"}},
		{"Ala", vector<string>{"GCU", "GCC", "GCA", "GCG"}},
		{"Tyr", vector<string>{"UAU", "UAC"}},
		{"His", vector<string>{"CAU", "CAC"}},
		{"Gln", vector<string>{"CAA", "CAG"}},
		{"Asn", vector<string>{"AAU", "AAC"}},
		{"Lys", vector<string>{"AAA", "AAG"}},
		{"Asp", vector<string>{"GAU", "GAC"}},
		{"Glu", vector<string>{"GAA", "GAG"}},
		{"Cys", vector<string>{"UGU", "UGC"}},
		{"Trp", vector<string>{"UGG"}},
		{"Arg", vector<string>{"CGU", "CGC", "CGA", "CGG", "AGA", "AGG"}},
		{"Gly", vector<string>{"GGU", "GGC", "GGA", "GGG"}},
	};


public:
	ProteinSequence Generate_Protein_Sequence(int _protein_number) {	// 프로틴 서열 생성
		ProteinSequence _protein_sequence;
		while (_protein_number--) { _protein_sequence.push_back(_Protein_List[util::Random_Generate<int>(0, 18)]); }
		return _protein_sequence;
	}

	RnaSequence Protein_To_Rna(ProteinSequence _protein_sequence) {	// 프로틴 서열 -> RNA 서열
		RnaSequence _rna_sequence;
		for (auto& _protein : _protein_sequence) {
			auto& _codon = _Protein_Codon[_protein];
			_rna_sequence += _codon[util::Random_Generate<int>(0, (int)_codon.size() - 1)];
		}
		return _rna_sequence;
	}

	RnaSequence Modify_Rna(RnaSequence _rna_sequence, int _differ_percent) {	// RNA 서열 변형
		int _modify_cnt = (int)_rna_sequence.size() * _differ_percent / 100;
		vector<bool> _alreay_modified(_rna_sequence.size(), false);

		while (_modify_cnt--) {
			int _target_index = util::Random_Generate<int>(0, (int)_rna_sequence.size() - 1);
			while (_alreay_modified[_target_index]) _target_index = util::Random_Generate<int>(0, (int)_rna_sequence.size() - 1);
			_alreay_modified[_target_index] = true;

			char _new_Nucleobases = _Rna_Nucleobases[util::Random_Generate<int>(0, 3)];
			while (_rna_sequence[_target_index] == _new_Nucleobases) _new_Nucleobases = _Rna_Nucleobases[util::Random_Generate<int>(0, 3)];
			_rna_sequence[_target_index] = _new_Nucleobases;
		}
		return _rna_sequence;
	}

	DnaSequence Make_Dna_Sequence(int _sequence_length) {   // dna 생성 (A, T, G, C로 구성된 크기가 size인 문자열 return)
		string _dna(_sequence_length, ' ');
		while (_sequence_length) _dna[--_sequence_length] = _Dna_Nucleobases[util::Random_Generate<int>(0, 3)];
		return _dna;
	}

	RnaSequence Make_Rna_Sequence(int _sequence_length) {   // rna 생성 (A, U, G, C로 구성된 크기가 size인 문자열 return)
		string _rna(_sequence_length, ' ');
		while (_sequence_length) _rna[--_sequence_length] = _Rna_Nucleobases[util::Random_Generate<int>(0, 3)];
		return _rna;
	}
};