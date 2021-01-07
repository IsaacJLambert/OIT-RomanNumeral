#include <iostream>
#include <string>

using namespace std;

int Menu() {
    cout << "++++Roman Numeral Translator++++\n 1. Roman Numeral to Modern\n 2. Modern Number to Roman Numerals\n 3. Exit \n";
    bool invalidInput;
    int userInput;
    do{
        invalidInput = false;
        try {
            cout << "User Selection: ";
            cin >> userInput;
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                throw invalidInput = true;
            }
            else if ((userInput > 3) || (userInput < 1)) {
                cout << "Invalid Menu Selection" << endl;
                invalidInput = true;
            }
        }
        catch(bool invalidInput) {
            cout << "Invalid Input" << endl;
            invalidInput = true;
        }
    }while(invalidInput);

    return userInput;
}

int getModernNumber(char c) {
    //take roman numeral and return int
    switch(c){
        case 'M':
            return 1000;
            break;
        case 'D':
            return 500;
            break;
        case 'C':
            return 100;
            break;
        case 'L':
            return 50;
            break;
        case 'X':
            return 10;
            break;
        case 'V':
            return 5;
            break;
        case 'I':
            return 1;
            break;
        default:
            return 0;
    }
}

int romanToModern (string userInput) {
    int num1;
    int num2;
    int modernToReturn = 0;

    for(int i = 0; i < userInput.size(); i++) {
        num1 = getModernNumber(userInput.at(i)); 
        if (i != userInput.size() - 1) {
            num2 = getModernNumber(userInput.at(i + 1));
            if (num1 < num2) {
                //CM - CD - XC - XL - IX - IV
                modernToReturn += num2 - num1;
                i++;
            }
            else {
                modernToReturn += num1;
            }
        }
        else {
            modernToReturn += num1;
        }
    }
    return modernToReturn;
}

string modernToRoman(int userInput) {
    //Please read the ReadMe file for info about this function
    string romanNumber = "";
    string romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int modernNumbers[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

    for (int i = 0; i < 13; i++) {
        while((userInput - modernNumbers[i]) >= 0) {
            //if we can subtract that amount from the total then subtract
            userInput -= modernNumbers[i];
            //add letter to the translation
            romanNumber += romanNumerals[i];
        }
    }
    return romanNumber;
}

bool verifyRoman(string userRoman) {
    //make sure they only used valid characters
    for(char c : userRoman) {
        if((c == 'M') || (c == 'D') || (c == 'C') || (c == 'L') || (c == 'X') || (c == 'V') || (c == 'I')) {
            //valid do nothing
        }
        else {
            //invalid character
            return true;
        }
    }

    //verify that the string of roman numerals make sense(inorder, valid combinations, etc.)
    for (int i = 0; i < userRoman.size(); i++) {
        //M can be followed by anything
        //D can't be followed by M
        if ((userRoman.at(i) == 'D') && (i < userRoman.size() - 1)){
            if(userRoman.at(i + 1) == 'M') {
                return true;
            }
        }
        //C can be followed by anything
        //L can't be followed by M - D - C
        if ((userRoman.at(i) == 'L') && (i < userRoman.size() - 1)){
            if((userRoman.at(i + 1) == 'M') || (userRoman.at(i + 1) == 'D') || (userRoman.at(i + 1) == 'C')) {
                return true;
            }
        }
        //X can't be followed by M - D
        if ((userRoman.at(i) == 'X') && (i < userRoman.size() - 1)){
            if((userRoman.at(i + 1) == 'M') || (userRoman.at(i + 1) == 'D')) {
                return true;
            }
        }
        //V can't be followed by M - D - C - L - X
        if ((userRoman.at(i) == 'V') && (i < userRoman.size() - 1)){
            if((userRoman.at(i + 1) == 'M') || (userRoman.at(i + 1) == 'D') || (userRoman.at(i + 1) == 'C') || (userRoman.at(i + 1) == 'L') || (userRoman.at(i + 1) == 'X')) {
                return true;
            }
        }
        //I can't be followed by M - D - C - L
        if ((userRoman.at(i) == 'I') && (i < userRoman.size() - 1)){
            if((userRoman.at(i + 1) == 'M') || (userRoman.at(i + 1) == 'D') || (userRoman.at(i + 1) == 'C') || (userRoman.at(i + 1) == 'L')) {
                return true;
            }
        }
    }

    //valid input
    return false;
}

int main() {
    int userSelection;
    string userRoman;
    int userModern;
    bool error;
    do {
        userSelection= Menu();
        switch(userSelection) {
            case 1:
            //roman numeral to modern
                do {
                    error = false;
                    cout << "Enter Roman Numerals to be translated(use capital letters and no spaces ex: MCL): ";
                    cin >> userRoman;
                    error = verifyRoman(userRoman);
                    if (error) {
                        cout << "Invalid Input" << endl;
                    }
                } while(error);
                //is a valid input so translate:
                cout << userRoman << " in Modern numbers is: " << to_string(romanToModern(userRoman)) << endl << endl;
                break;
            case 2:
            //modern to roman numeral
                do {
                    error = false;
                    try {
                        cout << "Enter Modern number to be translated: ";
                        cin >> userModern;
                        if (cin.fail()) {    
                            throw true;
                        }
                    }
                    catch(bool error) {
                        cout << "Invalid Input" << endl;
                        cin.clear();
                        cin.ignore();
                        error = true;
                    }
                } while(error);
                //is a valid input so translate:
                cout << to_string(userModern) << " in Roman Numerals is: " << modernToRoman(userModern) << endl << endl;
                break;
            case 3:
            //exit
                break;
            default:
                cout << "Menu Error" << endl;
                break;
        }
    } while(userSelection != 3);

    return 0;
}