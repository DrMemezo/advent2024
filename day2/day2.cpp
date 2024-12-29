#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


bool checkline(string line);

int main(int argc, char const *argv[]){
    cout << min(2, 4);

    if (argc != 2){
        cout << "USAGE: ./day2.exe [FILENAME]" << endl;
        return 1;
    }

    string line;
    int safe_count;
    ifstream ProblemFile(argv[1]);

    while(getline(ProblemFile, line)){
        if (checkline(line) == true){
            safe_count++;
        }
    }

    cout << "No. of Safe: " << safe_count << endl;
    return 0;
}


bool check_for_increase(int previous, int current){
    int result = current - previous;

    if (!(result > 0)){
        return false;
    }
    
    if (abs(result) > 3){
        return false;
    }

    return true;
}

bool check_for_decrease(int previous, int current){
    int result = current - previous;

    if (!(result < 0)){
        return false;
    }
    
    if (abs(result) > 3){
        return false;
    }

    return true;
}


vector<int> get_numbers(string line){
    vector<int> numbers;
    int line_size = line.length();

    for (int i=0, prev=0; i <= line_size; i++){
        if (line[i] == ' ' || i == line_size){
            int num = stoi(line.substr(prev, i-prev));
            numbers.push_back(num);
            prev = i + 1;
        }
    }

    return numbers;
}

bool checkline(string line){
    
    vector<int> numbers = get_numbers(line);   

    int unsafe_count = 0;

    for (int i=1, prev_calc=numbers[0]-numbers[1]; i < numbers.size(); i++, prev_calc=numbers[i-1]-numbers[i]){

        if (prev_calc==0){
            unsafe_count++;
            continue;
        }
        
        
        if (prev_calc > 0 ){ // Decrease
            bool x = check_for_decrease(numbers[i-1], numbers[i]);
            if (!x){
                unsafe_count++;
                continue;
            }
        }
        else { // Increase
            bool x = check_for_increase(numbers[i-1], numbers[i]);
            if (!x){
                unsafe_count++;
                continue;
            }
        }
    }

    if (unsafe_count > 1){
        return false;
    }

    return true;
}

