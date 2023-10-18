#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <list>
#include <ctime>
#include <sstream>

#pragma once

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

class CaeserCiper
{
	private:
		string sentense, origin;
		vector<string> words;
		bool decrypted = false;
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
									"You made me feel so better"};
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
		CaeserCiper()
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
			origin = sentense;
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
			int shift = random(1, 25);
			for (auto &s : sentense)
			{
				if (islower(s)) s = (((s - 97) + shift) % 26) + 97;
				if (isupper(s)) s = (((s - 65) + shift) % 26) + 65;
			}
		}

		void decrypt(TextBox^ Box)
		{
			for (int shift = 1; shift < 26; shift++)
			{
				for (auto &s : sentense)
				{
					if (islower(s)) s = (((s - 97) + 1) % 26) + 97;
					if (isupper(s)) s = (((s - 65) + 1) % 26) + 65;
				}
				if (search(sentense) > 5) Box -> AppendText(ToGcString(sentense) + Environment::NewLine + Environment::NewLine);
			}
			decrypted = true;
		}

		void run(TextBox^ Box)
		{
			sum_time.clear();
			clock_t start, finish;
			double duration;
			for (int i = 0; i < 100; i++) {
				start = clock();
				createSentense();
				Box->Text = "<Created Random Sentense!>" + Environment::NewLine;
				Box->AppendText(getSentense() + Environment::NewLine + Environment::NewLine);

				encrypt();
				Box->AppendText("<Encrypt Caeser Ciper!>" + Environment::NewLine);
				Box->AppendText(getSentense() + Environment::NewLine + Environment::NewLine);

				Box->AppendText("<Decrypt Caeser Ciper!>" + Environment::NewLine);
				decrypt(Box);
				finish = clock();
				duration = (double)(finish - start);
				sum_time.push_back(duration);
			}

			double sum = 0;
			for (auto a : sum_time) sum += a;
			Box->AppendText("Caeser Ciper 평균 시간 : " + ((sum / sum_time.size()) / CLOCKS_PER_SEC)+ " sec" + Environment::NewLine);
		}

		int search(string sentense)
		{
			int count = 0;
			vector<string> vec = split(sentense, ' ');
			for (auto a : words) {
				if (find(vec.begin(), vec.end(), a) != vec.end()) count++;
			}
			return count;
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