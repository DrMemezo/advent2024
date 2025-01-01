#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>
#include <utility>
#include <algorithm>

using namespace std;

vector<pair<int,int>> RULES;
vector<vector<int>> UPDATES;

vector<pair<int,int>> get_rules(string rule_file_path){
    ifstream rule_file(rule_file_path);

    if (!rule_file.is_open() ){
        cerr << rule_file_path << " not found!" << endl;
        throw (rule_file_path);
    }

    string line;
    vector<pair<int, int>> rules;
    while (getline(rule_file, line)){
        stringstream ss(line);
        int x, y;
        char delimiter;
        ss >> x >> delimiter >> y;
        if (delimiter == '|'){
            rules.push_back(make_pair(x, y));
        }
        else {
            cerr << "Invalid Delimier: " << delimiter << " in line: " << line << endl; 
        }
    }
    
    sort(rules.begin(), rules.end());
    
    return rules;
}

vector<vector<int>> get_updates(string update_file_path){
    ifstream updates_file(update_file_path);

    if (!updates_file.is_open()){
        throw(update_file_path);
    }

    string line;
    vector<vector<int>> updates;
    while (getline(updates_file, line)){
        stringstream ss(line);
        int num;
        vector<int> upd;
        while (ss >> num){
            upd.push_back(num);

            if (ss.peek() == ','){
                ss.ignore();
            }
        }
        updates.push_back(upd);
    }
    return updates;
}

void swap_indexes(int i1, int i2, vector<int>& row);
bool is_row_valid(vector<int>& row);
bool check_the_rules(const int& num_before, const int& num_after);
pair<bool, int> is_update_valid(const int& index, const vector<int>& row, int next=0);
vector<int> correct_row(vector<int>row);

int main(int argc, char const *argv[])
{
    if (argc != 4){
        cerr << "USAGE: day5.exe [RULES] [UPDATES] [PART]" << endl;
        return 1;
    }

    string part = (string) argv[3];
    if (part != "1" && part != "2"){
        cerr << "[PART] must be '1' or '2'" << endl;
        return 1;
    }
    

    try {
        RULES = get_rules(argv[1]);
        UPDATES = get_updates(argv[2]);
    }
    catch(string file_path){
        cerr << file_path << " not found!" << endl; 
        return 1;       
    }

    int mid_total = 0;
    for (vector<int>& row: UPDATES){
        if (is_row_valid(row)) {
            // * THIS IS CODE FOR PART 1; 
            if (part == "1"){
                int x = row[(row.size()) / 2]; // Gets value in the middle of the row
                mid_total += x; 
            }   
        }
        else{ 
            // * THIS IS CODE FOR PART 2; 
            if (part == "2"){
                row = correct_row(row);
                int x = row[(row.size()) / 2];
                mid_total += x;
            }
        }
    }
    cout << "Total is: " << mid_total << endl;
    return 0;
}

bool is_row_valid(vector<int>& row){
    // For every update in row, check if update is valid against the other     
    size_t size = row.size();
    for (int i=0; i < size; i++){
        if (is_update_valid(i, row).first == false){
            return false;
        }
    }
    return true;
}

vector<int> correct_row(vector<int>row){
    // Swaps rows if incorrect
    size_t row_size = row.size();
    bool incorrect = true;

    while(incorrect){
        incorrect = false;

        for (int i=0; i < row_size; ++i){
            auto res = is_update_valid(i, row);
            if (res.first == false){
                swap_indexes(i, res.second, row);
                incorrect = true;
            }
        }

    }
    return row;
}

void swap_indexes(int i1, int i2, vector<int>& row){
    int temp = row[i1];
    row[i1] = row[i2];
    row[i2] = temp;
}

bool check_the_rules(const int& num_before, const int& num_after){
    for (pair<int,int> rule: RULES){
        if (rule.first == num_before && rule.second == num_after){
            return true;
        }

        if (rule.first == num_after && rule.second == num_before){
            return false;
        }
        // Since rules are sorted,
        if (rule.first > num_before && rule.first > num_after){
            cerr << num_before << '|' << num_after << " is not valid!" << endl;
            return false;
        }
    }
    return false;
}

pair<bool, int> is_update_valid(const int& index, const vector<int>& row, int next){
    // For every element, check if it is behind or in front, then check the rules for the same
    if (next >= row.size()){
        return make_pair(true, next);
    }
    
    if (next == index){
        return is_update_valid(index, row, ++next);
    }

    if (next < index){
        if (check_the_rules(row[next], row[index])){
            return is_update_valid(index, row, ++next);
        }
        return make_pair(false, next);
    }
    
    if (check_the_rules(row[index], row[next])){
        return is_update_valid(index, row, ++next);
    }
    return make_pair(false, next);
}
