#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>  


using namespace std;

// Structur Character Class Hero
struct classes {
    string name;
    int damage;
    int power;
    int maxHealth;
};
// Structur Character Class Monster
struct monster {
    string name;
    int damage;
    int maxHealth;
    int expGained;
    int goldGained;
};

bool isNew = false;
// Data Class Monster
monster monsters[] = {
    {
        "Goblin",
        5,
        200,
        10,
        5
    },
    {
        "Orc",
        3,
        250,
        12,
        7
    },
    {
        "Wizard",
        10,
        150,
        15,
        10
    }
};

// Data Class Hero
classes _class[] = {
    {
        "Warrior",
        5,
        0,
        400
    },
    {
        "Rogue",
        10,
        0,
        400
    },
    {
        "Archer",
        7,
        0,
        400
    }
};

// Strunctur Character Player
struct character {
    string name;
    classes _class;
    int exp;
    int level;
    int gold;
    int health;
};

// Funsi Load Untuk Memilih Character
character playerCharacter;
classes loadClass(string c) {
    if (c == "Warrior") {
        playerCharacter._class = _class[0];
    }
    else if (c == "Rogue") {
        playerCharacter._class = _class[1];
    }
    else { //Archer
        playerCharacter._class = _class[2];
    }
    return playerCharacter._class;
}

// Menu NewGame
void newGame() {
    string tempclass;
    cout << "Input your character's name : ";
    getline(cin, playerCharacter.name);
    do {
        cout << "Choose your class[Warrior|Rogue|Archer] : ";
        getline(cin, tempclass);
    } while (tempclass != "Warrior" && tempclass != "Rogue" && tempclass != "Archer");
    playerCharacter.exp = 0;
    playerCharacter.level = 1;
    playerCharacter.gold = 0;
    playerCharacter.health = loadClass(tempclass).maxHealth;
}

//Save Account 
character playercharacter;
void saveAccount() {
	//buat dulu sebuah file txt yang bernama account
    ofstream file("account.txt");
    if (file.is_open()) {
        file << playerCharacter.name << "#" << playerCharacter._class.name << "#" << playerCharacter.exp << "#"
             << playerCharacter.level << "#" << playerCharacter.gold << "#" << playerCharacter.health << "#";
        file.close();
    }
}

//fungsi masih eror dan perlu perbaikan
//kalau ingin diperbaiki boleh

/*
void loadClass(const string& className) {
    // Load class implementation
}

void loadAccount() {
    ifstream file("account.txt");
    if (file.is_open()) {
        string tempclass;
        if (file.peek() == ifstream::traits_type::eof()) {
            isNew = true;
            file.close();
            return;
        }
        getline(file, playerCharacter.name, '#');
        getline(file, playerCharacter._class.name, '#');
        file >> playerCharacter.exp;
        file.ignore();
        file >> playerCharacter.level;
        file.ignore();
        file >> playerCharacter.gold;
        file.ignore();
        file >> playerCharacter.health;
        file.ignore();
        file.close();
        loadClass(tempclass);
    }
}
*/

// First Menu
void firstMenu() {
    int input;
    do {
        cout << "1. Start New Game\n";
        cout << ">> ";
        cin >> input;
        cin.ignore();
        switch (input) {
        case 1:
            newGame();
            break;
        }
    } while (input > (isNew == true ? 1 : 2) || input < 1);
}

// Fight
void fight(monster m) {
    int input;
    int exp = m.expGained;
    int gold = m.goldGained;
    int damage = m.damage;
    int health = m.maxHealth;
    string name = m.name;
    do {
        system("cls");
        cout << name << "\nHealth : " << health << "\nDamage : " << damage << "\n\n";
        cout << playerCharacter.name << "\nHealth : " << playerCharacter.health << "\nDamage : " << playerCharacter._class.damage << "\n\n";
        cout << "1. Attack\n";
        cout << "2. Magic Attack\n";
        cout << "3. Run\n";
        cout << ">> ";
        cin >> input;
        cin.ignore();
        switch (input) {
        // Searangan Biasa
        case 1:
            health -= playerCharacter._class.damage;
            if (health <= 0) { //Player win
                playerCharacter.gold += gold;
                playerCharacter.exp += exp;
                cout << "You won!\nYou gained " << gold << " gold(s) and " << exp << " exp(s)\n";
                if (playerCharacter.exp >= 100) {
                    cout << "You've leveled up!\n";
                    playerCharacter.exp -= 100;
                    playerCharacter.level += 1;
                }
                cout << "Press any key to continue...";
                cin.ignore();
                return;
            }
            cout << "Serangan Magic Anda Berdamage : "<< playerCharacter._class.power<<endl;
            
            playerCharacter.health -= damage;
            if (playerCharacter.health <= 0) { //Player lose
                playerCharacter.gold = 0;
                playerCharacter.exp = 0;
                playerCharacter.health = playerCharacter._class.maxHealth;
                cout << "You lose!\nYou lost all your golds and exps\nPress any key to continue...";
                cin.ignore();
                return;
            }
            break;
        // Searangan Magic Dengan Damage Magic Random
        case 2:
        	//Inisialisasi random
        	srand(time(NULL));
    		playerCharacter._class.power = rand() % 100 + 1;
    		
    		if (playerCharacter._class.power > 50) {
    			health -= playerCharacter._class.power;
    				if (health <= 0) { //Player win
                		playerCharacter.gold += gold;
                		playerCharacter.exp += exp;
                		cout << "You won!\nYou gained " << gold << " gold(s) and " << exp << " exp(s)\n";
                			if (playerCharacter.exp >= 100) {
                    			cout << "You've leveled up!\n";
                    			playerCharacter.exp -= 100;
                    			playerCharacter.level += 1;
                			}
                				cout << "Press any key to continue...";
                				cin.ignore();
                				return;
            				}
            		cout << "Serangan Magic Berhasil!!\n";
            		cout << "Serangan Magic Anda Berdamage : "<<playerCharacter._class.power<<endl;
            		cin.ignore();
            		break;
            	
            	playerCharacter.health -= damage;
            		if (playerCharacter.health <= 0) { //Player lose
                		playerCharacter.gold = 0;
               			playerCharacter.exp = 0;
                		playerCharacter.health = playerCharacter._class.maxHealth;
                		cout << "You lose!\nYou lost all your golds and exps\nPress any key to continue...";
                		cin.ignore();
                		return;
            }
   			 } else {
        		playerCharacter.health -= damage;
            		if (playerCharacter.health <= 0) { //Player lose
                		playerCharacter.gold = 0;
                		playerCharacter.exp = 0;
                		playerCharacter.health = playerCharacter._class.maxHealth;
                		cout << "You lose!\nYou lost all your golds and exps\nPress any key to continue...";
            		}
            		cout << "Anda Gagal Merapal Mantra!!\n";
            		cout << "Serangan Magic Gagal!!\n";
            	  	cout << "Press any key to continue...";
                	cin.ignore();
               		break;
    		}
    	// Kabur Dari Musuh
        case 3:
			cout<<"Run Away!!";
			cin.ignore();
			return;
        }
    } while (true);
}

// Menu Fight
void fightMenu() {
    int input;
    do {
        system("cls");
        cout << "Fight Menu\n==========\n";
        cout << "1. Goblin\n";
        cout << "2. Orc\n";
        cout << "3. Wizard\n";
        cout << "4. Back\n";
        cout << ">> ";
        cin >> input;
        cin.ignore();
        switch (input) {
        case 1:
            fight(monsters[0]);
            break;
        case 2:
            fight(monsters[1]);
            break;
        case 3:
            fight(monsters[2]);
            break;
        }
    } while (input != 4);
}

// Menu Heal
void heal() {
    int gold = playerCharacter.gold;
    int healPrice = 20;
    if (playerCharacter.health == playerCharacter._class.maxHealth) {
        cout << "You're already at max health!\n";
    }
    else if (gold >= healPrice) {
        int input;
        do {
            cout << "Do you want to heal yourself for " << healPrice << " golds ?\n";
            cout << "1. Yes\n2. No\n>> ";
            cin >> input;
            cin.ignore();
        } while (input != 1 && input != 2);
        if (input == 2) {
            cout << "Press any key to continue...";
            cin.ignore();
            return;
        }
        playerCharacter.health = playerCharacter._class.maxHealth;
        playerCharacter.gold -= healPrice;
        cout << "Healed!!\n";
    }
    else
        cout << "You don't have enough gold!\n";
    cout << "Press any key to continue...";
    cin.ignore();
}

int main() {
    int input;
    firstMenu();
    do {
        system("cls");
        cout << playerCharacter.name << "'s Status\n==========\n";
        cout << "Level " << playerCharacter.level << "\nClass : " << playerCharacter._class.name << "\nGold : " << playerCharacter.gold << "\nExp : " << playerCharacter.exp << "/100\nHealth : " << playerCharacter.health << "/" << playerCharacter._class.maxHealth << "\n";
        cout << "1. Fight\n";
        cout << "2. Heal\n";
        cout << "3. Save\n";
        cout << "4. Quit\n";
        cout << ">> ";
        cin >> input;
        cin.ignore();
        switch (input) {
        case 1:
            fightMenu();
            break;
        case 2:
            heal();
            break;
        // Save Acount
        case 3:
			saveAccount();
			printf("Saved Successfully!!\nPress any key to continue..."); 
			getchar();
            break;
        }
    } while (input != 4);
    return 0;
}



