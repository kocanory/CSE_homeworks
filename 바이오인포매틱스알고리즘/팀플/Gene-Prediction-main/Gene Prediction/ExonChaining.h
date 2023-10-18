#pragma once

#include "Biological.h"
#include "Utility.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;


class ExonChaining
{
public:
	typedef long long int_l;

	struct CandidateExon {
		int _Start_Position, _End_Position; int_l _Weight;
		CandidateExon() :_Start_Position(0), _End_Position(0), _Weight(0) {}
		CandidateExon(int _start_pos, int _end_pos, int_l _weight) :_Start_Position(_start_pos), _End_Position(_end_pos), _Weight(_weight) {}
	//	bool operator < (const CandidateExon& _other) { return _Start_Position < _other._Start_Position ? true : _Start_Position == _other._Start_Position ? _End_Position < _other._End_Position ? true : _End_Position == _other._End_Position ? _Weight < _other._Weight : false : false; }
	};

	struct Compare_For_Set {
		bool operator()(const CandidateExon* _left, const CandidateExon* _right) const {
			return _left->_Start_Position < _right->_Start_Position ? true : _left->_Start_Position == _right->_Start_Position ? _left->_End_Position < _right->_End_Position ? true : _left->_End_Position == _right->_End_Position ? _left->_Weight < _right->_Weight : false : false;
		}
	};

	enum LocalAlignmentScore { Match_Reward = 1, Mismatch_Penalize = -1, Indel_Penalize = -1, Free_Ride = 0 };

	struct LocalAlignmentCell {
		int_l _Score; set<int> _Start_Point_Set;
		LocalAlignmentCell() :LocalAlignmentCell(0, set<int>()) {}
		LocalAlignmentCell(int_l _score, set<int> _starting_point_set) :_Score(_score), _Start_Point_Set(_starting_point_set) {}
	};

	struct CellCoordinate {
		int _X, _Y;
		CellCoordinate() :CellCoordinate(0, 0) {}
		CellCoordinate(int _x, int _y) :_X(_x), _Y(_y) {}
	};

	struct ChainingCell {
		int_l _Value, _Gene_Count; vector<CandidateExon*> _Selected_Exon_Set;
		ChainingCell() :ChainingCell(0, 1, vector<CandidateExon*>()) {}
		ChainingCell(int_l _value, int_l _gene_count, vector<CandidateExon*> _selected_exon_set) :_Value(_value), _Gene_Count(_gene_count), _Selected_Exon_Set(_selected_exon_set) {}
	};


private:
	Sequence_Generator _Sequence_Generator;
	vector<string> _Protein_Sequence;
	string _Genome_Sequence, _Target_Sequence;
	set<CandidateExon*, Compare_For_Set> _Candidate_Exon_Set;


public:
	ExonChaining(int _protien_length) :
		_Protein_Sequence(_Sequence_Generator.Generate_Protein_Sequence(_protien_length)),
		_Genome_Sequence(_Sequence_Generator.Protein_To_Rna(_Protein_Sequence)),
		_Target_Sequence(_Sequence_Generator.Modify_Rna(_Genome_Sequence, 30)) {
		Contruct_Candidate_Exon_Set();
	}

	ExonChaining(int _sequence_length, set<CandidateExon*, Compare_For_Set> _candidate_exon_set) :
		_Protein_Sequence(vector<string>()),
		_Genome_Sequence(_Sequence_Generator.Make_Rna_Sequence(_sequence_length)),
		_Target_Sequence(_Sequence_Generator.Modify_Rna(_Genome_Sequence, 30)),
		_Candidate_Exon_Set(_candidate_exon_set) {}

	~ExonChaining() { _Protein_Sequence.clear(); _Genome_Sequence.clear(); _Target_Sequence.clear(); _Candidate_Exon_Set.clear(); }

	string Get_Genome_Sequence() { return _Genome_Sequence; }
	string Get_Genome_Sequence(int _begin, int _end) { return _Genome_Sequence.substr(_begin, _end - _begin + 1); }
	string Get_Target_Sequence() { return _Target_Sequence; }
	string Get_Target_Sequence(int _begin, int _end) { return _Target_Sequence.substr(_begin, _end - _begin + 1); }
	set<CandidateExon*, Compare_For_Set> Get_Candidate_Exon_Set() { return _Candidate_Exon_Set; }


private:
	void Contruct_Candidate_Exon_Set()
	{
		string _text_a = '.' + _Genome_Sequence, _text_b = ',' + _Target_Sequence;
		int _text_a_size = _text_a.size(), _text_b_size = _text_b.size();

		// local alignment
		vector<vector<LocalAlignmentCell>> _dp_table(_text_a_size, vector<LocalAlignmentCell>(_text_b_size));
		LocalAlignmentScore _score[3] = { Indel_Penalize, Match_Reward, Indel_Penalize };
		CellCoordinate _move[3] = { {-1, 0}, {-1, -1}, {0, -1} };

		auto _scoring_function = [&](int _x, int _y) {
			_score[1] = (_text_a[_x] == _text_b[_y] ? Match_Reward : Mismatch_Penalize);
			for (int i = 0; i < 3; i++) _dp_table[_x][_y]._Score = max(_dp_table[_x][_y]._Score, _dp_table[_x + _move[i]._X][_y + _move[i]._Y]._Score + _score[i]);

			if (_dp_table[_x][_y]._Score > 0) {
				for (int i = 0; i < 3; i++) {
					if (_dp_table[_x + _move[i]._X][_y + _move[i]._Y]._Score + _score[i] == _dp_table[_x][_y]._Score) {
						if (_dp_table[_x + _move[i]._X][_y + _move[i]._Y]._Score == 0) _dp_table[_x][_y]._Start_Point_Set.insert(_y);
						else _dp_table[_x][_y]._Start_Point_Set.insert(_dp_table[_x + _move[i]._X][_y + _move[i]._Y]._Start_Point_Set.begin(), _dp_table[_x + _move[i]._X][_y + _move[i]._Y]._Start_Point_Set.end());
					}
				}
			}
		};
		cout << "Finish Local Alignment" << "\n";


		for (int i = 1; i < _text_a_size; i++) {
			for (int j = 1; j < _text_b_size; j++) {
				_scoring_function(i, j);
				for (auto& _start_point : _dp_table[i][j]._Start_Point_Set)
					if (_dp_table[i][j]._Score > 1) _Candidate_Exon_Set.insert(new CandidateExon(_start_point - 1, j - 1, _dp_table[i][j]._Score));
			}
		}
		cout << "Finish Create Exons" << "\n";
	}


public:
	pair<vector<vector<CandidateExon*>>, vector<ChainingCell>> Get_Gene()	// exon chaining
	{
		// dynamic
		int_l _max_score_gene = 0; vector<ChainingCell> _dp_table(_Target_Sequence.size());

		int _pos = 0;
		auto _Shift = [&]() {
			if (_dp_table[_pos - 1]._Value == 0) return;
			if (_dp_table[_pos - 1]._Value > _dp_table[_pos]._Value) _dp_table[_pos] = ChainingCell(_dp_table[_pos - 1]._Value, _dp_table[_pos - 1]._Gene_Count, vector<CandidateExon*>{ nullptr });
			else if (_dp_table[_pos - 1]._Value == _dp_table[_pos]._Value) {
				_dp_table[_pos]._Gene_Count += _dp_table[_pos - 1]._Gene_Count;
				_dp_table[_pos]._Selected_Exon_Set.push_back(nullptr);
			}
		};

		for (auto& _exon : _Candidate_Exon_Set) {
			while (_pos < _exon->_Start_Position) { _pos++; _Shift(); }

			if (_dp_table[_exon->_End_Position]._Value < _dp_table[_exon->_Start_Position]._Value + _exon->_Weight) {
				_dp_table[_exon->_End_Position] = ChainingCell(_dp_table[_exon->_Start_Position]._Value + _exon->_Weight, _dp_table[_exon->_Start_Position]._Gene_Count, vector<CandidateExon*>{ _exon });
			}
			else if (_dp_table[_exon->_End_Position]._Value == _dp_table[_exon->_Start_Position]._Value + _exon->_Weight) {
				_dp_table[_exon->_End_Position]._Gene_Count += _dp_table[_exon->_Start_Position]._Gene_Count;
				_dp_table[_exon->_End_Position]._Selected_Exon_Set.push_back(_exon);
			}
			_max_score_gene = max(_max_score_gene, _dp_table[_exon->_End_Position]._Value);
		}
		while (++_pos < _dp_table.size()) { _Shift(); }
		cout << "Finish Dynamic" << "\n";



		// backtracking for find all genes
		int _gene_set_limit = 1000000;
		vector<vector<CandidateExon*>> _gene_set; vector<CandidateExon*> _exon_index_set;

		function<void(int)> Backtracking = [&](int _curr_pos) {
			if (_gene_set.size() == _gene_set_limit) return;
			if (_dp_table[_curr_pos]._Selected_Exon_Set.empty()) { _gene_set.push_back(_exon_index_set); reverse(_gene_set.back().begin(), _gene_set.back().end()); return; }

			for (auto& _selected_exon : _dp_table[_curr_pos]._Selected_Exon_Set) {
				if (_gene_set.size() == _gene_set_limit) return;

				if (_selected_exon == nullptr) Backtracking(_curr_pos - 1);
				else {
					_exon_index_set.push_back(_selected_exon);
					Backtracking(_selected_exon->_Start_Position);
					_exon_index_set.pop_back();
				}
			}
		};

		Backtracking((int)_dp_table.size() - 1);
		cout << "Finish Backtracking" << "\n";

		return { _gene_set,_dp_table };
	}
};



/* {
	for (auto& e : _Candidate_Exon_Set) cout << e->_Start_Position << ' ' << e->_End_Position << ' ' << e->_Weight << '\n';
	cout << "  ";
	for (int j = 0; j < _text_b_size; j++) cout << _text_b[j] << ' '; cout << '\n';
	for (int i = 0; i < _text_a_size; i++) {
		cout << _text_a[i] << " ";
		for (int j = 0; j < _text_b_size; j++) {
			cout << _dp_table[i][j]._Score << ' ';
		}
		cout << '\n';
	}

	cout << "  ";
	for (int j = 0; j < _text_b_size; j++) cout << _text_b[j] << ' '; cout << '\n';
	for (int i = 0; i < _text_a_size; i++) {
		cout << _text_a[i] << " ";
		for (int j = 0; j < _text_b_size; j++) {
			cout << _dp_table[i][j]._Start_Point_Set.size() << ' ';
		}
		cout << '\n';
	}
}*/