#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


vector<string> find_all(string line){
    // Finds all mul statements
    
    // regex r_
    // regex r_mull("mul\\((\\d\\d\\d|\\d\\d|\\d),(\\d\\d\\d|\\d\\d|\\d)\\)");
    regex r_all("((don't\\(\\))|(mul\\((?:\\d\\d\\d|\\d\\d|\\d),(?:\\d\\d\\d|\\d\\d|\\d)\\))|(do\\(\\)))");
    auto words_begin = sregex_iterator(line.begin(), line.end(), r_all);
    auto words_end = sregex_iterator();
    vector<string> mulls ;

    for (sregex_iterator i = words_begin; i != words_end; ++i){
        smatch match = *i;
        string match_str = match.str();
        mulls.push_back(match_str);
    }

    return mulls;
}

void to_mul_or_not_to(string operand, bool& do_){
    regex r_dont("don't\\(\\)");
    regex r_do("do\\(\\)");

    if (regex_match(operand, r_dont)) {
        do_ = false;
    }
    else if (regex_match(operand, r_do)){
        do_ = true;
    }

    return;
}



int get_result_of_mul(string mul_statement){
    // Validates and gets result of a mul() call
    regex r("mul\\((\\d\\d\\d|\\d\\d|\\d),(\\d\\d\\d|\\d\\d|\\d)\\)");
    smatch match;
    if (regex_match(mul_statement, match, r)) {
        return stoi(match[1]) * stoi(match[2]);
    }

    return 0;
} 


int main(int argc, char const *argv[])
{
    if (argc != 2){
        cout << "USAGE: day3.exe [FILE]" << endl;
        return 1;
    } 
    
    
    vector<string> matches;
    bool do_ = true;
    string line;
    ifstream file(argv[1]);
    int x = 0;

    while (getline(file, line)){
        auto i = find_all(line);
        for (string mull: i){
            to_mul_or_not_to(mull, do_);
            if (do_){
                x += get_result_of_mul(mull);
            } 
        }
    }
    cout << "Sum of all muls: " << x << endl;
    return 0;
}
