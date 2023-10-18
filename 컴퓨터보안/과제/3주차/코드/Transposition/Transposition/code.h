#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <list>
#include <map>
#include <algorithm>
#include <ctime>
#include <sstream>

#pragma once

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

class TranspositionCiper
{
private:
	bool decrypted = false;
	int mismatch = 0;
	string sentense, origin_sentense;
	vector<string> words;
	list<string> dictionory = { "THE CLOCK STOPPED TICKING FOREVER AGO",
								"The trembling fear",
								"I have a story to tell",
								"Do you hear me tonight",
								"I feel you drop tears",
								"And my heart become heavy"
								"Some lights turn around and around",
								"I lost my head again",
								"And just want to throw everything away",
								"Please tell me what should I do",
								"You made me feel so better" };

	vector<pair<int, string>> change_map;
	vector<double> sum_time;

private: String^ ToGcString(string std_string) {
	return gcnew String(std_string.data()); //std::string 에서 System::String으로 변환
}                                       //winform에서 std::string을 출력할 수 없어서 System::String으로 변환 필요


private: string ToStdString(String^ gc_string) {
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(gc_string)).ToPointer();
	string std_string = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return std_string; //System::String을 std::string으로 변환
}

public:
	TranspositionCiper()
	{
		for (auto l : dictionory)
		{
			vector<string> temp = split(l, ' ');
			words.insert(words.end(), temp.begin(), temp.end());
		}
		sort(words.begin(), words.end());
		words.erase(unique(words.begin(), words.end()), words.end());

	}

	int random(int low, int high)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> digit(low, high);    //문자셋에서 가져올 문자의 인덱스를 균일한 확률로 무작위로 선택
		int ran = digit(gen);                          //인덱스를 저장
		return ran;
	}

	void createSentense()
	{
		decrypted = false;
		int index = random(7, 10);
		string temp = "";
		for (int i = 0; i < index; i++)
		{
			temp += words[random(0, words.size() - 1)];
			temp += ' ';
		}
		sentense = temp;

		change_map.clear();
		if (sentense.length() % 5 != 0)
		{
			for (; sentense.length() % 5 != 0;)
				sentense += (random(0, 1) ? 65 + random(0, 25) : 97 + random(0, 25));
		}

		origin_sentense = sentense;
	}
	vector<string> split(string str, char delimeter)
	{
		vector<string> vec;
		stringstream ss(str);
		string s;

		while (getline(ss, s, delimeter)) vec.push_back(s);

		return vec;
	}

	void encrypt()
	{
		vector<string> array = { "", "", "", "", "" };
		array.reserve(5);

		for (int i = 0; i < sentense.length(); i++)
			array[i % 5] += sentense[i];

		for (int i = 0; i < array.size(); i++)
			change_map.push_back(pair<int, string> (i, array[i]));

		random_shuffle(change_map.begin(), change_map.end());
		sentense.clear();

		for (auto a : change_map) sentense += a.second;
	}

	void decrypt(TextBox^ Box)
	{
		vector<string> array;
		for (int i = 0; i < sentense.length(); i += (sentense.length() / 5))
			array.push_back(sentense.substr(i, (sentense.length() / 5)));

		vector<string> origin = { "", "", "", "", "" };

		for (int i = 0; i < array.size(); i++)
		{
			for (auto p : change_map)
			{
				if (p.second == array[i]) origin[p.first] = array[i];
			}
		}

		sentense.clear();
		for (int i = 0; i < origin[0].length(); i++)
		{
			for (int j = 0; j < origin.size(); j++)
			{
				sentense += origin[j][i];
			}
		}
		if (origin_sentense == sentense)
			Box->AppendText(ToGcString(sentense) + Environment::NewLine + Environment::NewLine);
		else mismatch++;
		decrypted = true;
	}

	void run(TextBox^ box)
	{
		sum_time.clear();
		clock_t start, finish;
		double duration;
		start = clock();
		for (int i = 0; i < 100; i++)
		{
			createSentense();
			box->Text = "<Created Random Sentense!>" + Environment::NewLine;
			box->AppendText(getSentense() + Environment::NewLine + Environment::NewLine);

			encrypt();
			box->AppendText("<Encrypt Transposition Ciper!>" + Environment::NewLine);
			box->AppendText(getSentense() + Environment::NewLine + Environment::NewLine);

			box->AppendText("<Decrypt Transposition Ciper!>" + Environment::NewLine);
			decrypt(box);
			finish = clock();
			duration = (double)(finish - start);
			sum_time.push_back(duration);
		}

		double sum = 0;
		for (auto a : sum_time) sum += a;

		box->AppendText("Transposition Ciper 평균 시간 : " + ( (sum / sum_time.size()) / CLOCKS_PER_SEC) + " sec" + Environment::NewLine);
		box->AppendText("mismatch count = " + mismatch);
	}

	String^ getSentense()
	{
		return ToGcString(sentense);
	}

	bool check_decrypted()
	{
		return decrypted;
	}
};