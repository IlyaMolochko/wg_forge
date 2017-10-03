#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

int compare(std::pair<int, int> v1, std::pair<int, int> v2) {
    if (v1.second > v2.second) {
        return false;
    } else {
        return true;
    }
}

int get_index(std::vector<std::pair<int, int>> teams) {
    int min_index = 0;
    int sum = 0;
    for (int i = 2; i < teams.size(); i += 2) {
        sum += teams[i].second - teams[i - 1].second;
    }
    int min_sum = sum;
    for (int j = 2; j < teams.size(); j += 2) {
        sum += 2 * teams[j - 1].second - teams[j - 2].second - teams[j].second;
        if (min_sum > sum) {
            min_sum = sum;
            min_index = j;
        }
    }
    return min_index;
}

void print_teams_id(std::vector<std::pair<int, int>> teams) {
    freopen("test_D_pairs.txt", "w", stdout);
    std::sort(teams.begin(), teams.end(), compare);
    if (teams.size() % 2 == 1) {
        int index = get_index(teams);
        std::cout << teams[index].first << std::endl;
        teams.erase(teams.begin() + index);
    }
    for (int i = 0; i < teams.size(); i += 2) {
        std::cout << teams[i].first << " " << teams[i + 1].first << std::endl;
    }
}

int main() {
    std::ifstream fin("players.txt");
    std::vector<int> players;
    int n;
    int i;
    while (fin >> i) {
        fin >> n;
        players.push_back(n);
    }
    fin.close();
    std::ifstream in("teams.txt");

    std::vector<std::pair<int, int>> teams;
    std::string line;
    teams.resize(0);
    int sum;
    while (std::getline(in, line)) {
        sum = 0;
        std::istringstream istringstream(line);
        istringstream >> i;
        while (istringstream >> n) {
            sum += players[n];
        }
        teams.push_back(std::pair<int, int>(i, sum));
    }
    in.close();
    print_teams_id(teams);

    return 0;
}