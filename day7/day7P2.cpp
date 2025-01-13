#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
using namespace std;

pair<long long, vector<long long>> get_equation(string line);

bool is_possible(const long long& result, const vector<long long>& operands);

int main(int argc, char const *argv[])
{
    if (argc != 2){
        cout << "USAGE: day7.exe [FILE]"<< endl;
        return 1;
    }

    ifstream file(argv[1]);
    string line;
    unsigned long long equation_total = 0;

    while (getline(file, line)){
        pair equation_pair = get_equation(line);
        if (is_possible(equation_pair.first, equation_pair.second)){
            equation_total += equation_pair.first; 
        }
    }

    cout << "Total is:" << equation_total << endl;
    return 0;
}


void change_operators(vector<char>& operators, const int& value){

    int ops_size = operators.size();
    const char ops_sign[] = {'+', '*', '|'};

     for (int i=0; i < ops_size; i++){
        int operator_choice = (value / (int)pow(3, i)) % 3; // I honestly don't know.

        operators[i] = ops_sign[operator_choice];
     }
}

unsigned long long concatnum(const unsigned long long& numleft, const long long& numright){
    string strleft = to_string(numleft);
    string strright = to_string(numright);
    string complete_str = strleft + strright;
    unsigned long long complete_num = stoll(complete_str);
    return complete_num;
}

bool is_valid_equation(const vector<long long>& operands, const vector<char>& operators, const long long& result){
    size_t oprts_size = operators.size();
    unsigned long long this_result = operands[0];

    for (int i=0; i < oprts_size; i++){
        if (operators[i] == '+'){
            this_result += operands[i+1];
        }
        else if(operators[i] == '*'){
            this_result *= operands[i+1];
        }
        else if(operators[i] == '|'){
            this_result = concatnum(this_result, operands[i+1]);
        }

        if (this_result > result){
            return false;
        }
    } 

    if (this_result == result){
        return true;
    }

    return false;

}

bool is_possible(const long long& result, const vector<long long>& operands){

    size_t operators_size = operands.size() - 1;
    vector<char> operators(operators_size, '+');
    
    const size_t LIMIT = pow(3, operators_size);
    int curr_iter = 0;

    while (curr_iter < LIMIT){
        if (is_valid_equation(operands, operators, result)){
            return true;
        }
        
        curr_iter++;
        change_operators(operators, curr_iter);
    }


    
    return false;
}

pair<long long, vector<long long>> get_equation(string line) {
    
    size_t colon_pos = line.find(':'); // 18880346235: 59 5 8 1 8 3 462 35
    long long result = stoll(line.substr(0, colon_pos));
    stringstream ss(line.substr(colon_pos + 1));
    long long num;
    vector<long long> operands;
    while (ss >> num){
        operands.push_back(num);
    } 
    pair equation = make_pair(result, operands);
    
    return equation;
}