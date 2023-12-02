#include <bits/stdc++.h>

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dist3(0, 2);
uniform_int_distribution<int> dist2(0, 1);

vector<bool> gen_doors() {
    int car = dist3(gen);
    vector<bool> doors(3, false);
    doors[car] = true;
    return doors;
}

void print_result(int total, int wins) {
    cout << "Won:   " << wins << " (" << round(((float) wins) / total * 1000) / 10 << "%)" << "\n"
         << "Lost:  " << total - wins << "\n"
         << "Total: " << total << endl;
}

int main() {

    int a, wins;
    a = 1'000'000;

    wins = 0;
    for (int i = 0; i < a; i++) {
        auto doors = gen_doors();
        int first_choice = dist3(gen);
        
        set<int> tmp1 = {0, 1, 2};
        tmp1.erase(first_choice);
        int open_door;
        if (doors[*tmp1.begin()]) open_door = *++tmp1.begin();
        else if (doors[*++tmp1.begin()]) open_door = *tmp1.begin();
        else open_door = dist2(gen) ? *++tmp1.begin() : *tmp1.begin();

        set<int> tmp2 = {0, 1, 2};
        tmp2.erase(first_choice);
        tmp2.erase(open_door);
        if (doors[*tmp2.begin()]) wins++;
    }
    print_result(a, wins);

    wins = 0;
    for (int i = 0; i < a; i++) {
        auto doors = gen_doors();
        set<int> tmp1 = {0, 1, 2};
        for (int j = 0; j < 3; j++) if (doors[j]) tmp1.erase(j);
        int open_door = dist2(gen) ? *++tmp1.begin() : *tmp1.begin();
        doors.erase(doors.begin() + open_door);

        int first_choice = dist2(gen);
        if (doors[!first_choice]) wins++;
    }
    print_result(a, wins);

    return 0;
}