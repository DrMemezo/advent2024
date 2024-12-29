#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool is_valid(string line);

int main(int argc, char const *argv[]){
   
    if (argc != 2){
        cout << "USAGE: ./day2.exe [FILENAME]" << endl;
        return 1;
    }

    string line;
    int safe_count;
    ifstream ProblemFile(argv[1]);

    while(getline(ProblemFile, line)){
        if (is_valid(line) == true){
            safe_count++;
        }
    }

    cout << "No. of Safe: " << safe_count << endl;
    return 0;
}


bool check_for_increase(vector<int> record, int index){
    return record[index + 1] > record[index];
}

bool check_for_decrease(vector<int> record, int index){
    return record[index + 1] < record[index];
}

bool check_abs_difference(vector<int> record, int index){
    int diff = abs(record[index + 1] - record[index]);
    if (diff > 3 || diff < 1){
        return false;
    }

    return true;
}

vector<int> get_numbers(string line){
    vector<int> numbers;
    stringstream linestream(line);
        
    int num;

    while (linestream >> num){
        numbers.push_back(num);
    }

    return numbers;
}

vector<int> remove_element(vector<int> record, int index){
    // Removes an element
    record.erase(record.begin() + min(index, (int) record.size()));
    return record;
}


bool confirm_record(vector<int> record, int& index){
    bool is_inc, is_dec = false;
    int k = record.size() - 1;

    for (int i=0; i < k; i++){
        if (check_for_decrease(record, i) && !is_inc){
            is_dec = true;
        }

        else if (check_for_increase(record, i) && !is_dec){
            is_inc = true;
        }
        else {
            index = i;
            return false;
        }

        if (check_abs_difference(record, i) == false){
            return false;
        }
    }
        
    return true;
}


bool is_valid(string line){
    vector<int> numbers = get_numbers(line); 
    int index = 0;
    if (confirm_record(numbers, index)){
        return true;
    }
    return confirm_record(remove_element(numbers, index), index) || 
    confirm_record(remove_element(numbers, index + 1), index) || 
    confirm_record(remove_element(numbers, index + 2), index);
}

