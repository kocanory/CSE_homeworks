#pragma once

#include <typeinfo>
#pragma once

#include <random>
#include <string>
#include <vector>
using namespace std;


namespace util   // ����� ���� ���Ǽ� Ŭ����
{
	enum ALIGNMENT { Left, Right };

	template <typename dataType>
	dataType Random_Generate(dataType _lower_bound, dataType _upper_bound) {	// ���� ���� �Լ�
		random_device _random_device;
		mt19937 _generate(_random_device());
		return uniform_int_distribution<dataType>(_lower_bound, _upper_bound)(_generate);
	}

	template <typename dataType>
	string Print_Format(dataType _item, int _fix_len, ALIGNMENT _alignment = Left) {
		string _str = to_string(_item);
		return _str.insert(_alignment ? Left : _str.size(), string(_fix_len - (int)_str.size(), ' '));
	}

	string String_Format(string _str, int _fix_len, ALIGNMENT _alignment = Left) { return _str.insert(_alignment ? Left : _str.size(), string(_fix_len - (int)_str.size(), ' ')); }

	class Process_Bar   // ���μ��� Ŭ����
	{
	public:

		int _count, _max_count;
		double _process;

		Process_Bar(int _max = 0) :_count(0), _max_count(_max), _process(0) {}
		~Process_Bar() {}

		void initialize(int _max) { _count = 0; _max_count = _max; _process = 0; }
		void start(int _max) { initialize(_max); }
		void end() { initialize(0); }
		double update(int _cnt) { _count++; return get_process(); }
		double get_process() { return (double)_count / _max_count * 100; }
	};

}