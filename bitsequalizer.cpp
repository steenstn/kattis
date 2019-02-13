#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool fail = false;
struct bitstring {
    bitstring(string input) {
        this->bits = input;
        this->numOnes = 0;
        this->numZeros = 0;
        for(int i = 0; i < this->bits.length(); i++) {
            if(this->bits[i]=='0') {
                numZeros++;
            }
            if(this->bits[i]=='1') {
                numOnes++;
            }
            if(this->bits[i]=='?') {
                questionMarks.push_back(i);
            }
        }
    }
    string bits;
    int numOnes;
    int numZeros;
    vector<int> questionMarks;

    int convertTo(bitstring target) {
        if(this->questionMarks.size() == 0) {
            int zeroFlips = 0;
            for(int i = 0; i < this->bits.length();i++) {
                if(this->bits[i] == '0' && target.bits[i]=='1' && (this->numZeros != target.numZeros && this->numOnes != target.numOnes)) {
                    this->bits[i] = '1';
                    zeroFlips++;
                    this->numOnes++;
                    this->numZeros--;
                }
            }
            if(this->numZeros != target.numZeros && this->numOnes != target.numOnes) {
                fail = true;
                return -1;
            }
            int differences = 0;
            for(int i = 0; i < this->bits.length(); i++) {
                if(this->bits[i] != target.bits[i]) {
                    differences++;
                }
            }
            if(differences%2 != 0) {
                fail = true;
                return -1;
            }
            return zeroFlips + differences/2;
        } else {
            int index = questionMarks.back();
            questionMarks.pop_back();
            if(target.bits[index]=='0') {
                if(target.numZeros > this->numZeros) {
                    this->bits[index]='0';
                    this->numZeros++;
                    return 1 + convertTo(target);
                } else {
                    this->bits[index]='1';
                    this->numOnes++;
                    return 1 + convertTo(target);
                }
            }
            if(target.bits[index]=='1') {
                if(target.numOnes > this->numOnes) {
                    this->bits[index]='1';
                    this->numOnes++;
                    return 1 + convertTo(target);
                } else {
                    this->bits[index]='0';
                    this->numZeros++;
                    return 1 + convertTo(target);
                }
            }

        }
        return 0;
    }
};
int main(void) {
    
    int numCases;
    
    string inputS, inputT;
    cin >> numCases;
    
    vector<bitstring> allS;
    vector<bitstring> allT;

    for(int i = 0; i < numCases;i++) {
        cin >> inputS;
        cin >> inputT;
        allS.push_back(bitstring(inputS));
        allT.push_back(bitstring(inputT));
    }
    for(int i = 0; i < numCases; i++) {
        fail = false;
        int result = allS[i].convertTo(allT[i]);
        if(fail) {
            cout << "Case " << (i+1) << ": " << (-1) << endl;
        } else {
            cout << "Case " << (i+1) << ": " << result << endl;

        }
    }
    

    return 0;
}
