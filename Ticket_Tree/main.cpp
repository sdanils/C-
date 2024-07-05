#include <iostream>
#include <fstream>
#include <string>
#include "tamplateTree.cpp"

using namespace std;

TicketM* createTicket();
TicketM* searchTicket();
void readFile(Tree<TicketM>* Tree);

int main(){
    Tree<TicketM> tickets;
    bool stopProgramm = false;
    
    while(!stopProgramm){
        cout << "\nMenu:\n  1 - add ticket\n  2 - enter all tickets\n  3 - enter tickets by date and number with subsequent deletion\n  4 - exit\n";

        int choise;
        cin >> choise;

        if(choise < 1 || choise > 5){
            cout << "\nUncorrect!\n";
            continue;
        }

        switch(choise){
            case 1:{
                TicketM* newTicket;
                newTicket = createTicket();
                
                if(!tickets.addNode(tickets.getRoot(), newTicket)){
                    cout << "\nCannot save ticket!\n";
                };
                break;
            }
            case 2:{
                tickets.entedTree(tickets.getRoot());
                break;
            }
            case 3:{
                TicketM* searchTi;
                searchTi = searchTicket();

                int countTickets = 0;
                tickets.entedByKey(tickets.getRoot(), searchTi, &countTickets);

                while(countTickets != 0){
                    tickets.root = tickets.deleteNode(searchTi, tickets.getRoot());
                    --countTickets;
                }

                break;
            }
            case 4:{
                stopProgramm = true;
                tickets.clearTree(tickets.getRoot());
                break;
            }
            case 5:{
                readFile(&tickets);
            }
        }
    }

    return 1;
}

TicketM* createTicket(){
        cout << "\nEnted destination: ";
        string dest;
        cin >> dest;

        cout << "\nEnted number: ";
        int num;
        cin >> num;

        cout << "\nEnted name: ";
        string name;
        cin >> name;

        cout << "\nEnted date (10101000): ";
        int date;
        cin >> date;

        
        TicketM *newTick = new TicketM(dest, num, name, date);
        return newTick;

}

TicketM* searchTicket(){
        cout << "\nEnted number: ";
        int num;
        cin >> num;
        cout << "\nEnted date (10101000): ";
        int date;
        cin >> date;

        TicketM* newTick = new TicketM("dest", num, "name", date);
        return newTick;
}

void readFile(Tree<TicketM>* Tree){
    ifstream file("ticketsInfo.txt");
    string deriction, name, bufNumber, bufDate;
    int number, date;
    int numTickets = -1;
    int countTicket = 0;

    getline(file, name);
    numTickets = stoi(name);

    if(numTickets > 0){
        if(file.is_open()){
            while(numTickets != 0){
               getline(file, deriction, ' ');
               getline(file, name, ' ');
               getline(file, bufNumber, ' ');
               getline(file, bufDate, '\n'); 
               ++countTicket;  

               number = stoi(bufNumber.c_str());
               date = stoi(bufDate.c_str());

               TicketM *newTick = new TicketM(deriction, number, name, date);
               Tree->addNode(Tree->getRoot(), newTick);
               --numTickets;
            }
            Tree->entedTree(Tree->getRoot());

        }
        else{
            cout << "\nCannot open file\n";
            return;
        }
        file.close();

    }
};