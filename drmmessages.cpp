#include <iostream>
#include <vector>
#include <string>
using namespace std;

int getRotationSum(string input) {
    int sum = 0;
    for(int i = 0; i < input.size(); i++) {
        sum+=input[i]-65;
    }
    return sum;
}

string rotateString(string input, int rotationAmount) {
    string result = input;
    for(int i = 0; i <input.size(); i++) {        
        result[i] = (input[i]-65+rotationAmount%26);
        if(result[i] > 26) {
            result[i]-= 26;
        }   
        result[i]+=65;
    }
    return result;
}

string rotateString(string input, string rotationString) {
    string result = input;
    for(int i = 0; i < result.size(); i++) {
        result[i] = input[i]-65+(rotationString[i]-65)%26;
        if(result[i] >= 26) {
            result[i]-=26;
        }
        result[i]+=65;
    }
    return result;
}

int main(void) {
    string fullString;
    getline(std::cin, fullString);
    
    
    string leftString, rightString;
    leftString = fullString.substr(0,fullString.size()/2);
    rightString = fullString.substr(fullString.size()/2);
    
    int leftSum = getRotationSum(leftString);
    int rightSum = getRotationSum(rightString);
    
    string rotatedLeftString, rotatedRightString;
    rotatedLeftString = rotateString(leftString, leftSum);
    rotatedRightString = rotateString(rightString, rightSum);

    cout << rotateString(rotatedLeftString, rotatedRightString);
   
    return 0;
}


