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

int player_val(Players p)
{
    return 3 * p.ascore + p.pscore;
}

string CheckPosition(int &keeper, int &depender, int &mid, int &attacker, Players &player)
{
    if(keeper > 0 && player.position1 == "골키퍼")
    {
        player.pscore += 2;
        --keeper;
        return "골키퍼";
    }
    if(depender > 0 && player.position1 == "수비수")
    {
        player.pscore += 2;
        --depender;
        return "수비수";
    }
    if(mid > 0 && player.position1 == "미드필더")
    {
        player.pscore += 2;
        --mid;
        return "미드필더";
    }

    if(attacker > 0 && player.position1 == "공격수")
    {
        player.pscore += 2;
        --attacker;
        return "공격수";
    }


    if(keeper > 0 && player.position2 == "골키퍼")
    {
        player.pscore++;
        --keeper;
        return "골키퍼";
    }
    if(depender > 0 && player.position2 == "수비수")
    {
        player.pscore++;
        --depender;
        return "수비수";
    }
    if(mid > 0 && player.position2 == "미드필더")
    {
        player.pscore++;
        --mid;
        return "미드필더";
    }
    if(attacker > 0 && player.position2 == "공격수")
    {
        player.pscore++;
        --attacker;
        return "공격수";
    }

    if(keeper > 0)
        {
            --keeper;
            return "골키퍼";
        }
    else if(depender > 0)
        {
            --depender;
            return "수비수";
        }
    else if(mid > 0)
        {
            --mid;
            return "미드필더";
        }
    else if(attacker > 0)
        {
            --attacker;
            return "공격수";
        };
    return NULL;
}

class PriorityQueue
{
    public:
    int size;
    Players * priority_queue;

    public:
    PriorityQueue()
    {
        size = 0;
        priority_queue = new Players[100];
    }

    Players peek()
    {
        return priority_queue[1];
    }

    void adjust(int n)
    {
        int root = n;
        int left = 2 * n;
        int right = 2 * n + 1;

        if(left <= size && player_val(priority_queue[left]) < player_val(priority_queue[root]))
            root = left;
        if(right <= size && player_val(priority_queue[right]) < player_val(priority_queue[root]))
            root = right;

        if(root != n)
        {
            swap(priority_queue[n], priority_queue[root]);
            adjust(root);
        }
    }

    void push(Players element)
    {
        ++size;
        int i = size;
        priority_queue[i] = element;
        while(i > 1 && (player_val(priority_queue[i]) < player_val(priority_queue[i / 2])))
        {   
            swap(priority_queue[i], priority_queue[i / 2]);
            i /= 2;
        }
    }

    Players pop()
    {
        Players player = priority_queue[1];
        player.ascore++;
        swap(priority_queue[1], priority_queue[size]);
        --size;
        adjust(1);
        return player;
    }

    void init_shuffle()
    {
        srand((unsigned int)time(NULL));
        for(int i = 0; i < size; i++)
        {
            int index1 = rand() % size + 1;
            int index2 = rand() % size + 1;
            if(index1 != index2) swap(priority_queue[index1], priority_queue[index2]);
        }
    }
};

void swap(Players &p1, Players &p2)
{
    Players temp = p1;
    p1 = p2;
    p2 = temp;
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
    PriorityQueue q;
    int size = 0, play = 0, count = 1; 
	while(!ifs.eof()){
     	ifs >> pname >> p1 >> p2 >> ps;
        Players p = {pname, p1, p2, ps, 0};
        q.push(p);
	}
    size = q.size;    
    q.init_shuffle();
    
    vector<Players> played;
	while(play < 4){
        
        int keeper = 1, depender = 4, mid = 4, attacker = 2;
        vector<tuple<Players, string>> played_position;
        if(size - played.size() < 11)
        {
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
                if(count % size == 0) 
                {

                }
            }
        
        for(auto a : played_position)
            played.push_back(get<0>(a));
        
        cout << "공격수:  ";
        for(auto a : played_position)
            if(get<1>(a) == "공격수")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl;

        cout << "미드필더:  ";
        for(auto a : played_position)
            if(get<1>(a) == "미드필더")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl;

        cout << "수비수:  ";
        for(auto a : played_position)
            if(get<1>(a) == "수비수")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl;

        cout << "골키퍼:  ";
        for(auto a : played_position)
            if(get<1>(a) == "골키퍼")
                cout << "(" << get<0>(a).name << " " << get<1>(a) << " " << get<0>(a).pscore << ") ";
        cout << endl << endl;
        play++;
    }
}