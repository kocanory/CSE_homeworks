
#include "Utility.h"
#include "ExonChaining.h"

#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef long long int_l;


ExonChaining Example_Data() 
{
	int sequence_length = 19;
	set<ExonChaining::CandidateExon*, ExonChaining::Compare_For_Set> example_candidate_exon = {
		new ExonChaining::CandidateExon(2, 3, 3),
		new ExonChaining::CandidateExon(9, 10, 1),
		new ExonChaining::CandidateExon(13, 14, 0),
		new ExonChaining::CandidateExon(16, 18, 4),
		new ExonChaining::CandidateExon(1, 5, 5),
		new ExonChaining::CandidateExon(7, 17, 12),
		new ExonChaining::CandidateExon(4, 8, 6),
		new ExonChaining::CandidateExon(11, 15, 7),
		new ExonChaining::CandidateExon(6, 12, 10),
	};

	return ExonChaining(sequence_length, example_candidate_exon);
}


ExonChaining Random_Data(int protien_length = 5)
{
	return ExonChaining(protien_length);
}


void Print_Rusult_Detail(ExonChaining &exon_chaining, pair<vector<vector<ExonChaining::CandidateExon*>>, vector<ExonChaining::ChainingCell>> &result)
{
	cout << '\n';
	cout << "exon set ==============" << "\n";
	int exon_num = 0;
	for (auto& exon : exon_chaining.Get_Candidate_Exon_Set()) cout << "exon" << util::Print_Format<int>(++exon_num, 10) << "(" << exon->_Start_Position << ", " << exon->_End_Position << ", " << exon->_Weight << ")\n";
	cout << "=======================" << "\n\n";

	if (result.first.size() >= 0) {
		auto gene_set = result.first;
		auto dp_table = result.second;
		int_l max_score = dp_table[gene_set[0].back()->_End_Position]._Value;
		int_l num_of_gene = dp_table[gene_set[0].back()->_End_Position]._Gene_Count;

		cout << "Max Score: " << max_score << " ----------------------------------------------------------------------------------------" << "\n\n";
		cout << util::String_Format("index", 5) << ": ";
		for (int i = 0; i < dp_table.size(); i++) cout << util::Print_Format<int>(i, 4) << ' '; cout << '\n';
		cout << util::String_Format("value", 5) << ": ";
		for (int i = 0; i < dp_table.size(); i++) cout << util::Print_Format<int>(dp_table[i]._Value, 4) << ' '; cout << '\n';
		cout << util::String_Format("count", 5) << ": ";
		for (int i = 0; i < dp_table.size(); i++) cout << util::Print_Format<int>(dp_table[i]._Gene_Count, 4) << ' ';
		cout << "\n\n";

		int gene_num = 0;
		cout << "Number of Predicted Gene: " << num_of_gene << "\n\n";
		for (auto& gene : gene_set) {
			cout << "gene" << ++gene_num << " -> ";
			for (auto& exon : gene) cout << "(" << exon->_Start_Position << ", " << exon->_End_Position << ", " << exon->_Weight << ") "; cout << "\n";
			cout << "      -> ";
			for (auto& exon : gene) cout << exon_chaining.Get_Target_Sequence(exon->_Start_Position, exon->_End_Position);
			cout << "\n\n";
		}
		cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";
	}
}


void Print_Rusult_Normal(ExonChaining& exon_chaining, pair<vector<vector<ExonChaining::CandidateExon*>>, vector<ExonChaining::ChainingCell>>& result)
{
	cout << '\n';
	if (result.first.size() >= 0) {
		auto gene_set = result.first;
		auto dp_table = result.second;
		int_l max_score = dp_table[gene_set[0].back()->_End_Position]._Value;
		int_l num_of_gene = dp_table[gene_set[0].back()->_End_Position]._Gene_Count;

		cout << "Max Score: " << max_score << "\n";
		cout << "Number of Predicted Gene: " << num_of_gene << "\n";
		cout << "Number of Found Gene: " << gene_set.size() << "\n\n";

		int gene_num = 0;
		for (auto& gene : gene_set) {
			cout << "gene" << ++gene_num << " -> ";
			for (auto& exon : gene) cout << exon_chaining.Get_Target_Sequence(exon->_Start_Position, exon->_End_Position);
			cout << "\n\n";
		}
		cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";
	}
}


void Print_Rusult_Short(ExonChaining& exon_chaining, pair<vector<vector<ExonChaining::CandidateExon*>>, vector<ExonChaining::ChainingCell>>& result)
{
	cout << '\n';
	if (result.first.size() >= 0) {
		auto gene_set = result.first;
		auto dp_table = result.second;
		int_l max_score = dp_table[gene_set[0].back()->_End_Position]._Value;
		int_l num_of_gene = dp_table[gene_set[0].back()->_End_Position]._Gene_Count;

		cout << "Max Score: " << max_score << "\n";
		cout << "Number of Predicted Gene: " << num_of_gene << "\n";
		cout << "Number of Found Gene: " << gene_set.size() << "\n\n";
	}
}


void Test_Example()
{
	ExonChaining exon_chaining = Example_Data();
	auto result = exon_chaining.Get_Gene();
	Print_Rusult_Detail(exon_chaining, result);
}


void Test_Short()
{
	ExonChaining exon_chaining = Random_Data(5);
	auto result = exon_chaining.Get_Gene();
	Print_Rusult_Detail(exon_chaining, result);
}


void Test_Normal()
{
	ExonChaining exon_chaining = Random_Data(20);
	auto result = exon_chaining.Get_Gene();
	Print_Rusult_Normal(exon_chaining, result);
}


void Test_Long()
{
	ExonChaining exon_chaining = Random_Data(100);
	auto result = exon_chaining.Get_Gene();
	Print_Rusult_Short(exon_chaining, result);
}


void Test_LongLong()
{
	ExonChaining exon_chaining = Random_Data(300);
	auto result = exon_chaining.Get_Gene();
	Print_Rusult_Short(exon_chaining, result);
}


int main()
{
	//Test_Example();
	//Test_Short();
	//Test_Normal();
	//Test_Long();
	Test_LongLong();

	return 0;
}
