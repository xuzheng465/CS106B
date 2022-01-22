#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "vector.h"


using namespace std;

void printBinary(int digits, string prefix="");
void printDecimal(int digits, string prefix="");

void permute(string s, string prefix="");
void combin(string, int length);
void diceRolls(int dice);
void diceSum(int dice, int desiredSum);
void sublists(Vector<string>& v);

int main() {

//    cout << "printBinary(3):" << endl;
//    printBinary(3);
//    cout<<endl;
//    cout << "printDecimal(2)" << endl;
//    printDecimal(2);
//    cout<<endl;
//    permute("SAM");
//    diceSum(3, 7);
    Vector<string> v {"Jane", "Bob", "Matt", "Sara"};
    sublists(v);
    return 0;
}

void printBinary(int digits, string prefix) {
    if (digits==0) {
        cout << prefix<<endl;
    } else {
        printBinary(digits-1, prefix+"0");
        printBinary(digits-1, prefix+"1");
    }
}
void printDecimal(int digits, string prefix) {
    if (digits==0) {
        cout << prefix<<endl;
    } else {
        for (int i = 0; i <=9; i++) {
            printDecimal(digits-1, prefix+integerToString(i));
        }
    }
}

void permute(string s, string prefix) {
    if (s.length() == 0) {
//        base
        cout << prefix << endl;
    } else {
        // choose the next letter
        for (int i = 0; i < s.length(); i++) {
            char ch = s[i];
            string s2 = s.substr(0, i) + s.substr(i+1);
            permute(s2, prefix+ch);
        }
    }
}
void diceRollsHelper(int dice, Vector<int>& chosen, Vector<Vector<int>>& res) {
    // if there are choices to make
    if (dice==0){
        res.add(chosen);
    } else {
        for (int i = 1; i <= 6; i++) {
            // choose
            chosen.add(i);
            // search/explore
            diceRollsHelper(dice-1, chosen, res);
            // un-choose
            chosen.remove(chosen.size() - 1);
        }
    }
}
/**
 * @brief diceRolls
 * @param dice
 */
void diceRolls(int dice) {
    Vector<int> v;
    Vector<Vector<int>> res;
    diceRollsHelper(dice, v, res);
    cout << res <<endl;
}

int sumAll(const Vector<int>& v) {
    int sum = 0;
    for (int k: v) {
        sum+=k;
    }
    return sum;
}

void diceSumHelper(int dice, int desiredSum, int sumSoFar, Vector<int>& chosen) {
    // if there are choices to make
    if (dice==0){
        if (sumSoFar == desiredSum) {
            cout << chosen << endl;
        }
    } else {
        for (int i = 1; i <= 6; i++) {
            if (sumSoFar+i <= desiredSum) {
                // choose
                chosen.add(i);
                // search/explore
                diceSumHelper(dice-1, desiredSum, sumSoFar+i, chosen);
                // un-choose
                chosen.remove(chosen.size() - 1);
            }
        }
    }
}

/**
 * @brief diceSum
 * @param dice
 * @param desiredSum
 */
void diceSum(int dice, int desiredSum) {
    Vector<int> v;
    diceSumHelper(dice, desiredSum, 0, v);
}

void sublistsHelper(Vector<string>& v, Vector<string>& chosen) {
    if (v.isEmpty()) {
        cout<< chosen <<endl;
    } else {
        // choose
        string first = v[0];
        v.remove(0);

        // explore/search
        // - Yes, include them
        chosen.add(first);
        sublistsHelper(v, chosen);
        chosen.remove(chosen.size() - 1);
        // - No, exclude them
        sublistsHelper(v, chosen);

        // un choose
        v.insert(0, first);
    }

}

void sublists(Vector<string>& v) {
    Vector<string> chosen;
    sublistsHelper(v, chosen);
}
