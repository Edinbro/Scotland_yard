#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

class Player {
    void bus(int);
    void taxi(int);
    void under(int);
    void black(int);
    void doubleride(int);
    int turn(string, int);
    int ID;
    string Moves[24];
public:
    double Bus, Taxi, Under, Black, Doubleride;
    int Position;
    string Name;
    Player(void);
    void setx(int);
    void correct(void);
    int start(Player[], int);
    void startposition(void);
    void add(int[], int);
};

Player::Player(void) {
    ID = 1;
    Bus = 8;
    Taxi = 10;
    Under = 4;
    Black = 0;
    Doubleride = 0;
}

void Player::setx(int n) {
    ID = 0;
    Taxi = 4;
    Bus = 3;
    Under = 2;
    Black = n-1;
    Doubleride = 2;
}

int Player::start(Player play[], int q) {
    if (ID == 0 && ((q == 2) || (q == 7) || (q == 12) || (q == 17) || (q == 23))) {
        cout << "\033[96m" << "After his next move, Mister X has to reveal his position!" << "\033[0m" << endl;
        cout << endl;
    }
    if (ID == 0 && ((q == 3) || (q == 8) || (q == 13) || (q == 18) || (q == 24))) {
        cout << "\033[96m" << "After his move, Mister X has to reveal his position!" << "\033[0m" << endl;
        cout << endl;
    }
    
    TURN:
    
    string trans;
    int invalid = 0;
    if (ID == 0) {
        cout << "\033[34m" << "Turn n°" << q << ":" << "\033[0m" << " Which mode of transport does " << Name << " use?" << endl;
        cin >> trans;
    }
    else {
        cout << "\033[34m" << "Turn n°" << q << ":" << "\033[0m" << " Which mode of transport does " << Name << " use and where?" << endl;
        cin >> trans;
        cin >> Position;
    }
    if ((trans == "lastmoves") || (trans == "last moves") || (trans == "last-moves") || (trans == "LM") || (trans == "PM") || (trans == "pm") || (trans == "lm") || (trans == "moves")) {
        cout << endl;
        cout << "Mister X' moves until now:" << endl;
        for (int z = 0; z < q; z++) {
            cout << "\033[34m" << "Round n°" << z+1+Position-Position << ": " << "\033[0m" << play[0].Moves[z+1] << endl;
        }
        cout << endl;
        goto TURN;
    }
    else if ((trans == "done") || (trans == "caught") || (trans == "finished") || (trans == "over") || (trans == "finish") || (trans == "end") || (trans == "list")) {
        string end;
        cout << "\033[34m" << "Is the game over?" << "\033[0m" << endl;
        cin >> end;
        if ((end == "Yes") || (end == "yes") || (end == "y") || (end == "Y") || (end == "YES")) return(3);
        else goto TURN;
    }
    else if ((trans == "correct") || (trans == "corr") || (trans == "mistake") || (trans == "error")) {
        CORRE:
        int z;
        string end;
        cout << endl;
        cout << "Which player's tickets to you want to correct?" << endl;
        cin >> z;
        play[z].correct();
        cout << endl;
        cout << "Do you want to correct another player's tickets?" << endl;
        cin >> end;
        if ((end == "Yes") || (end == "yes") || (end == "y") || (end == "Y") || (end == "YES")) goto CORRE;
        goto TURN;
    }    
        
    else {
        invalid = turn(trans, q);
        if (invalid == 1) {
            goto TURN;
        }
            
    }
    return(invalid);
}

int Player::turn (string mx, int l) {
    if ((mx == "BUS") || (mx == "bus") || (mx == "Bus") || (mx == "b")) {
        if(Bus == 0) {
            cout << "\033[31m" << "You have no bus ticket left." << "\033[37m" << endl;
            return(1);
        }
        bus(l);
        return(5);
    }
    else if ((mx == "TAXI") || (mx == "taxi") || (mx == "Taxi") || (mx == "t")) {
        if(Taxi == 0) {
            cout << "\033[31m" << "You have no taxi ticket left." << "\033[37m" << endl;
            return(1);
        }
        else{
            taxi(l);
            //cout << misx.Taxi << endl;
            return(6);
        }
    }
    else if ((mx == "UNDER") || (mx == "under") || (mx == "Under") || (mx == "u") || (mx == "UNDERGROUND") || (mx == "underground") || (mx == "Underground")) {
        if(Under == 0) {
            cout << "\033[31m" << "You have no underground ticket left." << "\033[37m" << endl;
            return(1);
        }
        under(l);
        return(7);
    }
    else if ((mx == "Black Ticket") || (mx == "BLACK TICKET") || (mx == "black ticket") || (mx == "BlackTicket") || (mx == "BLACKTICKET") || (mx == "blackticket") || (mx == "bt")) {
        if(ID > 0) {
            goto Fail;
        }
        else if(Black == 0) {
            cout << "\033[31m" << "You have no black ticket left." << "\033[37m" << endl;
            return(1);
        }
        black(l);
        return(0);
    }
    else if ((mx == "DOUBLE-RIDE") || (mx == "Double-ride") || (mx == "double-ride") || (mx == "d") || (mx == "DOUBLE RIDE") || (mx == "Double Ride") || (mx == "double ride") || (mx == "dr")) {
        if(ID > 0) {
            goto Fail;
        }
        else if(Doubleride == 0) {
            cout << "\033[31m" << "You have no double-ride ticket left." << "\033[37m" << endl;
            return(1);
        }
        else {
            doubleride(l);
            return(2);
        }
    }
    else {
        Fail:
        if (ID > 0) {
            cout << "\033[31m" << "Invalid entry: Please enter 'Taxi' (t), 'Bus' (b) or 'Underground' (u)." << "\033[37m" << endl;
        }
        else {
        cout << "\033[31m" << "Invalid entry: Please enter 'Taxi' (t), 'Bus' (b), 'Underground' (u), 'Black Ticket' (bt) or 'Double-ride' (dr)." << "\033[37m" << endl;
        }
        return(1);
    }
}


void Player::bus(int l) {
     if (ID == 0) {
        cout << "\033[92m" << "Mister X takes the bus." << "\033[0m"<< endl;
        cout << endl;
    }
    else {
        cout << "\033[92m" << Name << " takes the bus to " << Position << "." << "\033[0m"<< endl;
        cout << endl;
    }
    Bus = Bus - 1;
    Moves[l] = "Bus";
}

void Player::taxi (int l) {
    if (ID == 0) {
        cout << "\033[93m" << "Mister X takes a taxi." << "\033[0m"<< endl;
        cout << endl;
    }
    else {
        cout << "\033[93m" << Name << " takes a taxi to " << Position << "." << "\033[0m"<< endl;
        cout << endl;
    }
    Taxi = Taxi - 1;
    //cout << mistx.Taxi << endl;
    //cout << mistx.Taxi << endl;
    Moves[l] = "Taxi";
}

void Player::under (int l) {
    if (ID == 0) {
        cout << "\033[35m" << "Mister X takes the underground." << "\033[0m"<< endl;
        cout << endl;
    }
    else {
        cout << "\033[35m" << Name << " takes the undergound to " << Position << "." << "\033[0m"<< endl;
        cout << endl;
    }
    Under = Under - 1;
    Moves[l] = "Underground";
}

void Player::black (int l) {
    cout << "\033[90m" << "Mister X uses a black ticket." << "\033[0m"<< endl;
    cout << endl;
    Black = Black - 1;
    Moves[l] = "Black Ticket";
}

void Player::doubleride (int l) {
    string a, b;
    int inval;
    cout << "\033[91m" << "Mister X uses a double-ride." << "\033[0m"<< endl;
    cout << endl;
    Doubleride = Doubleride - 1;
    
    doubler:
    cout << "What is the first used mode of transport?" << "\033[0m"<< endl;
    cin >> a;
    if ((a == "DOUBLE-RIDE") || (a == "Double-ride") || (a == "double-ride") || (a == "d") || (a == "DOUBLE RIDE") || (a == "Double Ride") || (a == "double ride") || (a == "dr")) {
        cout << "\033[31m" << "Invalid entry: You can't use a second double-ride." << "\033[0m" << endl;
        goto doubler;
    }
    inval = turn(a, l); 
    if (inval == 1)  {
        goto doubler;
    }
    second:
    cout << "What is the second used mode of transport?" << endl;
    cin >> b;
    if ((b == "DOUBLE-RIDE") || (b == "Double-ride") || (b == "double-ride") || (b == "d") || (b == "DOUBLE RIDE") || (b == "Double Ride") || (b == "double ride") || (b == "dr")) {
        cout << "\033[31m" << "Invalid entry: You can't use a second double-ride." << "\033[0m"<< endl;
        goto second;
    }
    int c = l+1;
    inval = turn(b, c); 
    if (inval == 1) goto second;
}

void Player::startposition(void) {
    if(ID == 0) {
        string end;
        ofstream ofs;
        ofs.open("MisterX.txt", ofstream::out | ofstream::trunc);
        ofs.close();
        MXposition:
        int v = rand() % 199 + 1;
        cout << "\033[34m" << "Mister X' starting position is in the file 'MisterX.txt'." << endl;
        cout << endl;
        ofstream outfile ("MisterX.txt", ios_base::app);
        outfile << v << endl;
        cout << "Is Mister X' position closer than two links away from a detective?" << "\033[0m" << endl;
        cin >> end;
        cout << endl;
        if ((end == "Yes") || (end == "yes") || (end == "y") || (end == "Y") || (end == "YES")) goto MXposition;
        outfile.close();
    }
    else {
        int v = rand() % 199 + 1;
        cout << "\033[34m" << Name << "'s starting position is field n°" << v << "." << endl;
    }
}

void Player::add(int b[], int l) {
    for (int k = 0; k < l; k++) {
        if (b[k] == 6) Taxi = Taxi + 1;
        if (b[k] == 5) Bus = Bus + 1;
        if (b[k] == 7) Under = Under + 1;
    }
}

void Player::correct(void){
    int p;
    cout << endl;
    cout << Name << " has " << Taxi << " taxi tickets. How many should she/he have?" << endl;
    cin >> p;
    Taxi = p;
    cout << endl;
    cout << Name << " has " << Bus << " bus tickets. How many should she/he have?" << endl;
    cin >> p;
    Bus = p;
    cout << endl;
    cout << Name << " has " << Under << " underground tickets. How many should she/he have?" << endl;
    cin >> p;
    Under = p;
    if (ID==0) {
        cout << endl;
        cout << Name << " has " << Black << " black tickets. How many should she/he have?" << endl;
        cin >> p;
        Black = p;
        cout << endl;
        cout << Name << " has " << Doubleride << " double-ride tickets. How many should she/he have?" << endl;
        cin >> p;
        Doubleride = p;
    }
}

int main() {
    
    Playercount:
    int n = 0;
    cout << "\033[34m" << "How many players are you in total?" << "\033[0m" << endl;
    cin >> n;
    if (n < 2 || n > 6){
        cout << "\033[31m" << "Invalid entry: The numbers of players has to be between 2 and 6." << "\033[37m" << endl;
        goto Playercount;
    }
    if (n < 4) {
        int a;
        cout << "\033[34m" << "With how many detectives do you want to play?" << "\033[0m" << endl;
        cin >> a;
        n = a + 1;
    }
    
    Player guys[n];
    
    cout << endl;
    cout << "\033[34m" << "Enter Mister X:" << "\033[0m" << endl;
    cin >> guys[0].Name;
    guys[0].setx(n);
    
    
    for (int i = 1; i < n; i++) {
        cout << endl;
        cout << "\033[34m" << "Enter detective n°" << i << ":" << "\033[0m" << endl;
        cin >> guys[i].Name;
    }
    cout << endl;
    
    for (int k = n-1; k >= 0; k--) guys[k].startposition();
    
    for (int q = 1; q < 25; q++) {
        int a[n-1] = {0};
        
        for (int r = 0; r < n; r++) {
            int d = guys[r].start(guys, q);
            if(d == 2) q++;
            if(d == 3) goto Endofgame;
            if(d > 4 && r > 0) a[r-1] = d;
        }
        
        guys[0].add(a, n-1);
        
        cout << endl;
        cout<< "Mister X has " << "\033[93m" << guys[0].Taxi << " taxi, " << "\033[92m" << guys[0].Bus << " bus, " << "\033[35m" << guys[0].Under << " underground, " << "\033[90m" << guys[0].Black << " black" << "\033[0m" << " and " << "\033[91m" << guys[0].Doubleride << " double-ride"  << "\033[0m" << " tickets." << "\033[0m"<< endl;
        for (int s = 1; s < n; s++) {
            cout << guys[s].Name << " is on field " << guys[s].Position << " and has " << "\033[93m" << guys[s].Taxi << " taxi, " << "\033[92m" << guys[s].Bus << " bus" << "\033[0m" << " and " << "\033[35m" << guys[s].Under << " underground" << "\033[0m"<< " tickets." << endl;
        }
        cout << endl;
        cout << endl;
    }
    
    cout << endl;
    cout << "\033[93m" << "Congratulations " << guys[0].Name << ", Mister X has escaped!" << "\033[0m" << endl;
    goto Mxwin;
    
    Endofgame:
    
    cout << endl;
    cout << "\033[93m" << "Congratulation ";
    for (int j = 1; j < n; j++){
        if (j < n-2) cout << guys[j].Name << ", ";
        if (j == n-2) cout << guys[j].Name;
        else cout << " and " << guys[j].Name << ", you caught Mister X!" << "\033[0m" << endl;
    }
    
    Mxwin:
    
    cout << endl;
    
    return(0);
}
