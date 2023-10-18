#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <tuple>

using namespace std;

 struct Players{
	string name, position1, position2;
    int ascore, pscore;
};

string CheckPosition(int &keeper, int &depender, int &mid, int &attacker, Players &player)
{
    if(keeper > 0 && player.position1 == "��Ű��")
    {
        player.pscore += 2;
        --keeper;
        return "��Ű��";
    }
    if(depender > 0 && player.position1 == "�����")
    {
        player.pscore += 2;
        --depender;
        return "�����";
    }
    if(mid > 0 && player.position1 == "�̵��ʴ�")
    {
        player.pscore += 2;
        --mid;
        return "�̵��ʴ�";
    }

    if(attacker > 0 && player.position1 == "���ݼ�")
    {
        player.pscore += 2;
        --attacker;
        return "���ݼ�";
    }


    if(keeper > 0 && player.position2 == "��Ű��")
    {
        player.pscore++;
        --keeper;
        return "��Ű��";
    }
    if(depender > 0 && player.position2 == "�����")
    {
        player.pscore++;
        --depender;
        return "�����";
    }
    if(mid > 0 && player.position2 == "�̵��ʴ�")
    {
        player.pscore++;
        --mid;
        return "�̵��ʴ�";
    }
    if(attacker > 0 && player.position2 == "���ݼ�")
    {
        player.pscore++;
        --attacker;
        return "���ݼ�";
    }

    if(keeper > 0)
        {
            --keeper;
            return "��Ű��";
        }
    else if(depender > 0)
        {
            --depender;
            return "�����";
        }
    else if(mid > 0)
        {
            --mid;
            return "�̵��ʴ�";
        }
    else if(attacker > 0)
        {
            --attacker;
            return "���ݼ�";
        };
    return NULL;
}

class Queue
{
    public:
    int front;
    int rear;
    int size;
    Players * queue;

    public:
    Queue()
    {
        size = 100;
        queue = new Players[size];     
        front = 0;
        rear = 0;
    }
    ~Queue()
    {
        delete[] queue;
    }
    void push(Players element)
    {
        queue[rear] = element;
        rear = (rear + 1) % size;
    }
    Players pop()
    {
        Players player = queue[front];
        player.ascore++;
        front = (front + 1) % size;
        return player;
    }
    void setSize(int size)
    {
        this->size = size;
    }

    void init_shuffle()
    {
        srand((unsigned int)time(NULL));
        for(int i = 0; i < size; i++)
        {
            int index1 = rand() % size;
            int index2 = rand() % size;
            if(index1 != index2) swap(queue[index1], queue[index2]);
        }
        rear = 0;
        front = 0;
    }    
};

void swap(Players &p1, Players &p2)
{
    Players temp = p1;
    p1 = p2;
    p2 = temp;
}

void shuffle(vector<Players> p)
{
    srand((unsigned int)time(NULL));
    int size = p.size();
    for(int i = 0; i < size; i++)
    {
        int index1 = rand() % size;
        int index2 = rand() % size;
        if(index1 != index2) swap(p[index1], p[index2]);
    }
}

int main(){
	string filename, pname, p1, p2;
    int ps;

	cout << "input: ";
	cin >> filename;
    ifstream ifs(filename);

    if(ifs.fail()) {
        cout << "input error" << endl;
		exit(1);
    }
    Queue q;
    int size = 0, play = 0, count = 1; 
	while(!ifs.eof()){
     	ifs >> pname >> p1 >> p2 >> ps;
        Players p = {pname, p1, p2, ps, 0};
        q.push(p);
        size++;
	}
    q.setSize(size);   
    q.init_shuffle();
    vector<Players> played;
	while(play < 4)    {
        
        int keeper = 1, depender = 4, mid = 4, attacker = 2;
        vector<tuple<Players, string>> played_position;
        if(size - played.size() < 11)
        {
            shuffle(played);
            for(auto a : played)
                q.push(a);
            played.clear();
        }

        for(int i = 0;i < 11; i++, ++count)
            {
                Players player = q.pop();
                string position = CheckPosition(keeper, depender, mid, attacker, player);
                tuple<Players, string> p = make_tuple(player, position);
                played_position.push_back(p);
            }

        for(auto a : played_position)
            played.push_back(get<0>(a));

        cout << "���ݼ�:  ";
        for(auto a : played_position)
            if(get<1>(a) == "���ݼ�")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl;

        cout << "�̵��ʴ�:  ";
        for(auto a : played_position)
            if(get<1>(a) == "�̵��ʴ�")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl;

        cout << "�����:  ";
        for(auto a : played_position)
            if(get<1>(a) == "�����")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl;

        cout << "��Ű��:  ";
        for(auto a : played_position)
            if(get<1>(a) == "��Ű��")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl << endl;

        play++;
    }
}
