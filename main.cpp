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
    cout << "Won:   " << wins << " (" << round(((float) wins) / total * 100) << "%)" << "\n"
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
        int open_door;
        switch (first_choice) {
            case 0:
                if (doors[1]) open_door = 2;
                else if (doors[2]) open_door = 1;
                else open_door = dist2(gen) + 1;
                break;
            case 1:
                if (doors[0]) open_door = 2;
                else if (doors[2]) open_door = 0;
                else open_door = dist2(gen) * 2;
                break;
            case 2:
                if (doors[0]) open_door = 1;
                else if (doors[1]) open_door = 0;
                else open_door = dist2(gen);
                break;
        }
        set<int> tmp = {0, 1, 2};
        tmp.erase(first_choice);
        tmp.erase(open_door);
        if (doors[*tmp.begin()]) wins++;
    }
    print_result(a, wins);

    wins = 0;
    for (int i = 0; i < a; i++) {
        auto doors = gen_doors();
        int open_door;
        if (doors[0]) open_door = dist2(gen) + 1;
        else if (doors[1]) open_door = dist2(gen) * 2;
        else if (doors[2]) open_door = dist2(gen);
        int first_choice;
        switch (open_door) {
            case 0:
                if (doors[1] == doors[2]) return -1;
                first_choice = dist2(gen) + 1;
                break;
            case 1:
                if (doors[0] == doors[2]) return -1;
                first_choice = dist2(gen) * 2;
                break;
            case 2:
                if (doors[0] == doors[1]) return -1;
                first_choice = dist2(gen);
                break;
        }
        set<int> tmp = {0, 1, 2};
        tmp.erase(first_choice);
        tmp.erase(open_door);
        if (doors[*tmp.begin()]) wins++;
    }
    print_result(a, wins);

    wins = 0;
    for (int i = 0; i < a; i++) {
        auto doors = gen_doors();
        int open_door;
        if (doors[0]) open_door = dist2(gen) + 1;
        else if (doors[1]) open_door = dist2(gen) * 2;
        else if (doors[2]) open_door = dist2(gen);
        doors.erase(doors.begin() + open_door);
        int first_choice = dist2(gen);
        if (doors[!first_choice]) wins += 1;
    }
    print_result(a, wins);

    return 0;
}