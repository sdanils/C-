#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "classDecString.cpp"
using namespace std;

int DecimalString::numCopyDec = 0;
int String::numCopy = 0;

int main(){
    vector <String*> DecimalStrings;
    bool PlanExit = false;
    int choiceOne = 0, choice2 = -1;
    do{
        cout << "\n1 - add string\n2 - choose operator\n3 - show all string\n4 - exit\n";
        cin >> choiceOne;
        switch(choiceOne){
            case 1:{
                cout << "\nEnter decimal number:";
                string dec; 
                cin >> dec;

                DecimalString* decimalNumber = new DecimalString(dec.c_str());
                
                DecimalStrings.push_back(decimalNumber);
                break;
            }
            case 2:{
                cout << "\n1 - >\n2 - <\n3 - difarance\n";
                cin >> choice2;
                cout << "\nEnted operands. format X Y:";
                int str1 = -1, str2 = -1;
                cin >> str1; cin >> str2;
                if((str1 < -1 || str1 > DecimalStrings.size()) || (str2 < -1 || str2 > DecimalStrings.size())){
                    cout << "\nUncorrect ented.\n";
                    break;
                }
                switch(choice2){
                    case 1:{
                        bool result;
                        result = ((DecimalString)*DecimalStrings[str1] > (DecimalString)*DecimalStrings[str2]);
                        if(result){
                            cout << "\nResult positive\n";
                        }
                        else{
                            cout << "\nResult negative\n";
                        }
                        break;
                    }
                    case 2:{
                        bool result;
                        result = ((DecimalString)*DecimalStrings[str1] < (DecimalString)*DecimalStrings[str2]);
                        if(result){
                            cout << "\nResult positive\n";
                        }
                        else{
                            cout << "\nResult negative\n";
                        }
                        break;
                    }
                    case 3:{
                        DecimalString* result_ = new DecimalString();
                        *result_ = (DecimalString)*DecimalStrings[str1] - (DecimalString)*DecimalStrings[str2];
                        cout << "\nCreated number: ";
                        result_->EnterNumber();
                        cout << "\nSave string? N/Y\n";
                        char choiceThree = 0;
                        cin >> choiceThree;
                        if(choiceThree == 'N' || choiceThree == 'Y'){
                            switch(choiceThree){
                                case 'Y':
                                {
                                    DecimalStrings.push_back(result_);
                                    break;
                                }
                                case 'N':
                                    delete result_;
                                    break;
                            }
                        }
                        else{
                            cout << "\nUncorrect ented.\n";
                        }
                        break;
                    }
                    default:
                        cout << "\nUncorrect ented.\n";
                }
                break;
            }
            case 3:{
                int numString = DecimalStrings.size();
                if(numString != 0)
                    for(int i = 0; i < numString; ++i){
                        cout << "\nString " << i << ": ";
                        DecimalStrings[i]->EnterString();
                    }
                    else   
                        cout << "\nUncorrect ented\n";
                break;
            }
            case 4:{
                for(int i =0; i < DecimalStrings.size(); ++i)
                    delete DecimalStrings[i];
                PlanExit = true;
                break;
            }
            default:
                cout << "\nUncorrect ented\n";
                break;
        }
    }while(choiceOne != 4);

    if(PlanExit != true)
        for(int i =0; i < DecimalStrings.size(); ++i)
                    delete DecimalStrings[i];

    return 1;
}