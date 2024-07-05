#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class String{
    public:
    static int numCopy;
    char* string;
    int numberElements; // 1 bite - 1 si

    String(){
        this->string = new char;
        *this->string = '\0';
        numberElements = 0;
    }

    String(const char* string){
        int numElements = 0;

        for(int i = 0; string[i] != '\0'; ++i){
            ++numElements;
        }

        this->string = new char[numElements + 1];

        for(int i = 0; i <= numElements; ++i){
            this->string[i] = string[i];
        }

        this->numberElements = numElements;
    }

    String(char sym){
        this->numberElements = 1;
        this->string = new char[2];
        string[0] = sym;
        string[1] = '\0';
    }

    String(const String &obj){
        this->numberElements = obj.numberElements;
        this->string = new char[this->numberElements + 1];
        for(int i = 0; i <= this->numberElements; ++i)
            this->string[i] = obj.string[i];
        
        //++this->numCopy;
        //cout << "\n                                       + numCopyString " << numCopy;
    }

    int size(){
        return this->numberElements;
    }

    void deleteString(){
        delete[] this->string;
        this->numberElements = 0;
    }

    void EnterString(){
        for(int i = 0; i < this->numberElements; ++i){
            cout << this->string[i];
        }
    }

    ~String(){
        delete this->string;
    }
};

class DecimalString : public String{

    private:
    char massValidChar[13] = {'+','-', ',' ,'0', '1','2','3','4','5','6','7','8','9'};
    public:
    static int numCopyDec;

    DecimalString():String(){
    };

    DecimalString(const char* string):String(string){
        bool oneComma = false;

        for(int it = 0; it < this->numberElements; ++it){
            if(it == 0 && find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar + 2){
                this->numberElements = 0;
                delete[] this->string;
                this->string = new char;
                *this->string = '\0';
                break;
            }
            if(it > 0 && (find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar || find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar + 1)){
                this->numberElements = 0;
                delete[] this->string;
                this->string = new char;
                *this->string = '\0';
                break;
            }
            if(find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar + 12){
                if(this->string[it] != '9'){
                    this->numberElements = 0;
                    delete[] this->string;
                    this->string = new char;
                    *this->string = '\0';
                    break;
                }
            }
            if(find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar + 2){
                if(oneComma == false)
                    oneComma = true;
                else{
                    this->numberElements = 0;
                    delete[] this->string;
                    this->string = new char;
                    *this->string = '\0';
                    break;
                }
            }
        }
    }

    DecimalString(const DecimalString &obj){
        this->numberElements = obj.numberElements;
        this->string = new char[this->numberElements + 1];
        for(int i = 0; i <= this->numberElements; ++i)
            this->string[i] = obj.string[i];  

        //++this->numCopyDec;
        //cout << "\n                                  + numCopyDec " << this->numCopyDec;    
    }

    DecimalString(const String &obj){
        this->numberElements = obj.numberElements;

        delete[] this->string;
        this->string = new char[this->numberElements + 1];

        for(int i = 0; i <= this->numberElements; ++i)
            this->string[i] = obj.string[i];  

        //++this->numCopyDec;
        //cout << "\n                                  + numCopyDec " << this->numCopyDec;    
    }

    bool possibleParseInt(){
        int indexComma = -1;

        for(int it = 0; it < this->numberElements; ++it)
            if(find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar + 2){
                indexComma = it;
                break;
            }

        if(indexComma == -1)
            return true;
        else{
            for(int it = indexComma + 1; it < this->numberElements; ++it)
                if(find(this->massValidChar, this->massValidChar + 12, this->string[it]) == this->massValidChar + 3)
                    return false;
            return true;
        }
    }

    DecimalString& operator = (const DecimalString &obj){
        this->deleteString();
        this->string = new char[obj.numberElements + 1];
        for(int i = 0; i <= obj.numberElements; ++i)
            this->string[i] = obj.string[i];

        this->numberElements = obj.numberElements;
        return *this;
    }

    bool operator > (const DecimalString &oper){
        bool positiveOne = true, positiveTwo = true;
        if(this->string[0] == '-')
            positiveOne = false;
        if(oper.string[0] == '-')
            positiveTwo = false;
        
        if(positiveOne != positiveTwo){
            if( positiveOne && !positiveTwo)
                return true;
            else if(!positiveOne && positiveTwo)
                return false;
        }
        else{
            int indexComma[2];
            for(int t = 0; t < this->numberElements && this->string[t] != ','; ++t)
                indexComma[0] = t + 1;
            for(int t = 0; t < oper.numberElements && oper.string[t] != ','; ++t)
                indexComma[1] = t + 1;

            if(positiveOne){
                if(indexComma[0] != indexComma[1])
                    if(indexComma[0] > indexComma[1])
                        return true;
                    else   
                        return false;

                bool hasSignOne = false, hasSignTwo = false;
                if(this->string[0] == '+')
                    hasSignOne = true;
                if(oper.string[0] == '+')
                    hasSignOne = true;
                
                int maxLength = max(this->numberElements, oper.numberElements);

                for(int i = 0; i < maxLength; ++i)
                    if(this->string[i + hasSignOne] > oper.string[i + hasSignTwo])// порядок ASCII
                        return true;
                    else if(this->string[i + hasSignOne] < oper.string[i + hasSignTwo])
                        return false;
                
                return false;
            }
            else if(!positiveOne){
                if(indexComma[0] != indexComma[1])
                    if(indexComma[0] < indexComma[1])
                        return true;
                    else   
                        return false;

               int maxLength = max(this->numberElements, oper.numberElements); 

               for(int i = 1; i < maxLength; ++i){
                    if(this->string[i] > oper.string[i]){ // порядок ASCII (, 0 1 ... 9)
                        return false;
                    }
                    else if(this->string[i] < oper.string[i]){
                        return true;
                    }
                }

                return false;
            }
        }
        return false;
    }

    bool operator < (const DecimalString &oper){
        bool positiveOne = true, positiveTwo = true;
        if(this->string[0] == '-')
            positiveOne = false;
        if(oper.string[0] == '-')
            positiveTwo = false;
        
        if(positiveOne != positiveTwo){
            if( positiveOne && !positiveTwo)
                return false;
            else if(!positiveOne && positiveTwo)
                return true;
        }
        else{
            int indexComma[2];
            for(int t = 0; t < this->numberElements && this->string[t] != ','; ++t)
                indexComma[0] = t + 1;
            for(int t = 0; t < oper.numberElements && oper.string[t] != ','; ++t)
                indexComma[1] = t + 1;

            if(positiveOne){
                if(indexComma[0] != indexComma[1])
                    if(indexComma[0] > indexComma[1])
                        return false;
                    else   
                        return true;

                bool hasSignOne = false, hasSignTwo = false;
                if(this->string[0] == '+')
                    hasSignOne = true;
                if(oper.string[0] == '+')
                    hasSignOne = true;
                
                int maxLength = max(this->numberElements, oper.numberElements);

                for(int i = 0; i < maxLength; ++i){
                    if(this->string[i + hasSignOne] > oper.string[i + hasSignTwo]) // порядок ASCII
                        return false;
                    else if(this->string[i + hasSignOne] < oper.string[i + hasSignTwo])
                        return true;               
                }

                return false;
            }
            else if(!positiveOne){
                if(indexComma[0] != indexComma[1])
                    if(indexComma[0] < indexComma[1])
                        return false;
                    else   
                        return true;

               int maxLength = max(this->numberElements, oper.numberElements); 

               for(int i = 1; i < maxLength; ++i)
                    if(this->string[i] > oper.string[i]) // порядок ASCII 
                        return true;
                    else if(this->string[i] < oper.string[i])
                        return false;
                
                return false;
            }
        }
        return false;
    }

    DecimalString& operator - (const DecimalString &oper){

        bool positive[2] = {true, true}, hasSign[2] = {false, false};

        if(this->string[0] == '-'){
            positive[0] = false;
            hasSign[0] = true;
        }
        else if(this->string[0] == '+'){
            hasSign[0] = true;
        }

        if(oper.string[0] == '-'){
            positive[1] = false;                    
            hasSign[1]= true;
        }
        else if(oper.string[0] == '+'){
            hasSign[1]= true;
        }
        
        vector <char> oneCopy;
        vector <char> twoCopy;

        int indexComma[2] = {this->numberElements + 1, oper.numberElements + 1};
        int indexComma2[2] = {this->numberElements + 1, oper.numberElements + 1};

        for(int t = 0 + hasSign[0]; t < this->numberElements && this->string[t] != ','; ++t){
            oneCopy.push_back(this->string[t]);
            indexComma[0] = t + 1;
            indexComma2[0] = t + 1;
        }
        for(int t = 0 + hasSign[1]; t < oper.numberElements && oper.string[t] != ','; ++t){
            twoCopy.push_back(oper.string[t]);
            indexComma[1] = t + 1;
            indexComma2[1] = t + 1;
        }

        if(indexComma[0] - hasSign[0] < indexComma[1] - hasSign[1] )
            while(indexComma[0] - hasSign[0] != indexComma[1] - hasSign[1]){
                oneCopy.insert(oneCopy.begin(), '0');
                ++indexComma[0];
            }

        if(indexComma[0] - hasSign[0] > indexComma[1] - hasSign[1] )
            while(indexComma[0] - hasSign[0] != indexComma[1] - hasSign[1]){
                twoCopy.insert(twoCopy.begin(), '0');
                ++indexComma[1];
            }
        
        oneCopy.push_back(',');
        twoCopy.push_back(',');

        int mantis[2] = {0,0};

        if(indexComma2[0] < this->numberElements)
            for(int i = indexComma2[0] + 1; i < this->numberElements; ++i){
                oneCopy.push_back(this->string[i]);
                ++mantis[0];
            }
        if(indexComma2[1] < oper.numberElements)
            for(int i = indexComma2[1] + 1; i < oper.numberElements; ++i){
                twoCopy.push_back(oper.string[i]);
                ++mantis[1];
            }

        if(mantis[0] != mantis[1]){
            if(mantis[0] > mantis[1]){
                while(mantis[0] != mantis[1]){
                    twoCopy.push_back('0');
                    ++mantis[1];
                }
            }
            if(mantis[0] < mantis[1]){
                while(mantis[0] != mantis[1]){
                    oneCopy.push_back('0');
                    ++mantis[0];
                }
            }
        }

        vector <char> result;
        bool positiveResult = true;
        int length = oneCopy.size();
        int loan = 0, resStep = 0;

        if(positive[0] == positive[1]){
            if(positive[0])
                if(*this < oper){
                    vector <char> buf;
                    buf = twoCopy;
                    twoCopy = oneCopy;
                    oneCopy = buf;
                    positiveResult =  false;
                }
            if(!positive[0])
                if(*this > oper){
                    vector <char> buf;
                    buf = twoCopy;
                    twoCopy = oneCopy;
                    oneCopy = buf;
                }
                else if(*this < oper)
                    positiveResult = false;
        
            for(int i = length - 1; i >= 0; --i){
                if(oneCopy[i] == ','){
                    result.insert(result.begin(), ',');
                    continue;
                    }
                resStep = (oneCopy[i] - '0') - (twoCopy[i] - '0') - loan;
                loan = 0;
                if(resStep < 0 && i !=0){
                    ++loan;
                    resStep += 10;
                }
                result.insert(result.begin(), resStep + '0');  
                }
            if(!positiveResult)
                result.insert(result.begin(), '-'); 
        }
        else if(positive[0] != positive[1]){
            for(int i = length - 1; i >= 0; --i){
                if(oneCopy[i] == ','){
                    result.insert(result.begin(), ',');
                    continue;
                    }
                resStep = (oneCopy[i] - '0') + (twoCopy[i] - '0') + loan;
                loan = 0;
                if(resStep >= 10 && i != 0){
                    ++loan;
                    resStep -= 10;
                }
                else if(resStep >= 10 && i == 0){
                    resStep -= 10;
                    positiveResult = false;
                }
                result.insert(result.begin(), resStep + '0');  
                }
            if(!positiveResult)
                result.insert(result.begin(), '1');
            if(!positive[0])
                result.insert(result.begin(), '-');
        }
        
        int i =0;
        if(result[0] == '-' || result[0] == '+') i++;
        while(result[i] == '0' && result[i+1] != ',') result.erase(result.begin() + i);
        if(indexComma[0] < result.size())
            while(result.back() == '0') result.pop_back();
        if(result.back() == ',') result.pop_back();
        
        char* returnStr = new char[result.size() + 1];
        for(int i = 0; i < result.size(); ++i){
            returnStr[i] = result[i];
        }

        returnStr[result.size()] = '\0';

        DecimalString* returnString = new DecimalString(returnStr);
        delete[] returnStr;

        return *returnString;
    }

    void EnterNumber(){
        for(int i =0; i < this->numberElements; ++i){
            cout << this->string[i];
        }
    }
};