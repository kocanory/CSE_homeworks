#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class FriendList
{
public:
	vector<People> friendlist;
};


class People : public FriendList
{
private:
	string name;
	FriendList friendList;
	int i = 0;

public:
	People(string name) : name(name) {}

	void addFriend(People &other)
	{
		friendList.friendlist.push_back(other);
	}

	void removeFriend(People &other)
	{
		while (friendList.friendlist.begin() != friendList.friendlist.end())
		{
			
			if (friendList.friendlist[i] == other)
				friendList.friendlist.erase(friendList.friendlist.begin()+i);

			i++;
		}
	}

	bool isFriend(People &other)
	{
		for (auto & e : friendList.friendlist)
		{
			if (e == other)
				return true;
			else
				return false;
		}
	}

	bool operator == (People other)
	{
		if (name == other.name)
			return true;
		else
			return false;
	}

	void printFriendList()
	{
		for (auto &e : friendList.friendlist)
		{
			cout << e.name << endl;
		}
	}

};


int main()
{
	People A("me");
	People B("he");

	A.addFriend(B);
	B.addFriend(A);

	cout << A.isFriend(B) << endl;
	cout << B.isFriend(A) << endl;

	A.printFriendList();
	B.printFriendList();

	A.removeFriend(B);
	B.removeFriend(A);

	A.printFriendList();
	B.printFriendList();

	return 0;
}