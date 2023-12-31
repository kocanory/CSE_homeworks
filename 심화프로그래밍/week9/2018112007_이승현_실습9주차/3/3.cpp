#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student; //class Student를 미리 정의

class Teacher
{
private:
	string t_name;
	vector<Student*> students;

public:
	Teacher(string myname) : t_name(myname){}
	
	void addStudent(Student* student)
	{
		students.push_back(student); //배열에 변수 students의 주소값을 저장
	}
	
	void advice(); //학생과 상담한다

	friend class Student;
};

class Student
{
private:
	string s_name;
	vector<Teacher*> teacher;

public:
	Student(string myname) : s_name(myname){}
	void addTeacher(Teacher* student)
	{
		teacher.push_back(student); //배열에 변수 teacher의 주소값을 저장
	}
	void ask() //교수님께 질문한다
	{
		for (auto & ele : teacher)
		{
			cout << "ask to " << ele->t_name << endl; //교수님께 묻는 학생들의 이름들을 출력
		}
	}

	friend class Teacher;
};

void Teacher::advice() //이 함수는 class teacher내에서 정의할 경우 class Student의 정보를 알지 못해 밑에서 정의
{
	for (auto & ele : students)
	{
		cout << "advice with " << ele->s_name << endl;
	}
}

int main()
{
	Teacher *teacher = new Teacher("professor"); 
	Student *student = new Student("me");//포인터 객체의 메모리 할당

	teacher->addStudent(student);
	student->addTeacher(teacher);

	student->ask();
	teacher->advice();
	

	delete teacher;
	delete student; //포인터 객체의 메모리 반환
}
