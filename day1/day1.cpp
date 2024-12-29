#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void split_into(string line, int& result1, int& result2){    
    // Splits the line into two ints
    
    int len = line.length();
    int space_pos;
    for (int i = 0; i < len; i++){
        if (line[i] == ' '){
            space_pos = i; 
            break;
        }
    }
    
    
    result1 = stoi(line.substr(0, space_pos));
    result2 = stoi(line.substr(space_pos+3));
}

int main(int argc, char const *argv[])
{
    string Line;     
    vector<int> numbers_left;
    vector<int> numbers_right;
    int res1,res2;


    // open file
    ifstream MyFile("lists/problem.txt");

    // read and validate line (not null, two integers after space)
    while (getline(MyFile, Line)) {
        int res1, res2;
        split_into(Line, res1, res2);

        // store both integers in seperate arrays
        numbers_left.push_back(res1);
        numbers_right.push_back(res2);

    }

    MyFile.close();
    // sort arrays
    sort(numbers_left.begin(), numbers_left.end());
    sort(numbers_right.begin(), numbers_right.end());
    
    // compare each element and find difference
    if (numbers_left.size() != numbers_right.size()){
        cout << "ERROR: List numbers are unmatched " << endl; 
    }
    
    // sum of all differences
    int difference = 0;
    for (int i=0; i<numbers_left.size(); i++){
        difference +=  abs(numbers_left[i] - numbers_right[i]);
    }
    
    cout << "Sum of Differences: " << difference << endl;
    return 0;    
}
