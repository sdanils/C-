#include <iostream>
using namespace std;

class TicketM {
    private:
        string destination;
        int flightNumber;
        string name;
        int date; // 10.10.2023 - 10102023

    public:
        TicketM(string dest, int numberF, string name, int date){
            this->destination = dest;
            this->flightNumber = numberF;
            this->name = name;
            this->date = date;
        }

        TicketM(const TicketM& ticket2){
            this->date = ticket2.date;
            this->destination = ticket2.destination;
            this->flightNumber = ticket2.flightNumber;
            this->name = ticket2.name;
        }

        bool operator >(const TicketM& ticket){
            if(this->date % 10000 < ticket.date % 10000){
                return true;
            }
            else if(this->date % 10000 > ticket.date % 10000){
                return false;
            }
            else if(this->date % 10000 == ticket.date % 10000){
                if(this->date % 1000000 < ticket.date % 1000000){
                    return true;
                }
                else if(this->date % 1000000 > ticket.date % 1000000){
                    return false;
                }
                else if(this->date % 1000000 == ticket.date % 1000000){
                    if(this->date < ticket.date){
                        return true;
                    }
                    else if(this->date > ticket.date){
                        return false;
                    }
                    else if(this->date == ticket.date){
                        return false;
                    }
                }
            }
            return false;
        }

        bool operator == (const TicketM& ticket){
            if(this->date == ticket.date){
                return true;
            }
            else{
                return false;
            }
        }

        static bool comparisonDateNumber(const TicketM& ticket1, const TicketM& ticket2){
            if(ticket1.date == ticket2.date && ticket1.flightNumber == ticket2.flightNumber){
                return true;
            }
            else
                return false;
        }

        void entedTicketInfo(){
            cout << "\nTicket:\n    Destination: " << this->destination << "\n    Flight number:" << this->flightNumber << "\n    Date:" << this->date << "\n";
            cout << "   Name: " << this->name << "\n";
            return;
        }

};