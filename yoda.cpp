#include <iostream>
#include <math.h>
#include <string>

using namespace std;

int getDigitAtIndex(int index, int value) {
    int res = round(pow(10,index+1));
    int res2 = round(pow(10,index));
    return (value%res - value%res2)/res2;
}

int getNumDigits(int value) {
    return ceil(log10(value+1));

}
int main(void) {
    int input1, input2;
    int numDigits1, numDigits2;
    cin >> input1;
    cin >> input2;
    numDigits1 = getNumDigits(input1);
    numDigits2 = getNumDigits(input2);
    int input1Res = 0, input2Res = 0;
    int max = numDigits1 > numDigits2 ? numDigits1 : numDigits2;
    int digitsRemoved1 = 0, digitsRemoved2 = 0;
    int d1Index = 0;
    int d2Index = 0;
    for(int i = 0; i < max; i++) {
        int d1, d2;
        d1 =getDigitAtIndex(i, input1);
        d2 = getDigitAtIndex(i,input2);
        
        if(d1 > d2) {
            input1Res+=d1*(int)round(pow(10,d1Index++));
            digitsRemoved2++;
            
        } else if(d2 > d1) {
            input2Res+=d2*(int)round(pow(10,d2Index++));
            digitsRemoved1++;
        } else {
            input1Res+=d1*(int)round(pow(10,d1Index++));
            input2Res+=d2*(int)round(pow(10,d2Index++));
        }
        cout << endl;
    }
    
    if(digitsRemoved1 > 0 && digitsRemoved1 >= numDigits1 && input1Res == 0) {
        cout << "YODA" << endl;
    } else {
        cout << input1Res << endl;
    } 
    if(digitsRemoved2 > 0 && digitsRemoved2 >= numDigits2 && input2Res == 0) {
        cout << "YODA" << endl;
    } else {
        cout << input2Res << endl;
    } 
    return 0;
}