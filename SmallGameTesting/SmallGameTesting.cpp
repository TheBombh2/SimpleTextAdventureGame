//THIS PROJECT IS MADE FOR FUN JUST FOR GETTING FAMILIER WITH WRITING AND GAMING TERMS 
//TODAY IS 7/2/2023 5:52 PM I STARTED WRITING THIS ON 6/2/2023 I DON'T REMEMBER THE EXACT TIME I WROTE SHOULD HAVE NOTED
//and yes this is the first time I used comments and didn't even use it when I started this program but a day after lmao
#include <iostream>
#include<Windows.h>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <conio.h>
using namespace std;



//Function to wait for key input to start
void WaitKey(){
	cout << endl << endl << endl << "\t\t\tPress any key to start ";
	while (_kbhit()) _getch(); // Empty the input buffer
	_getch(); // Wait for a key
	while (_kbhit()) _getch(); // Empty the input buffer (some keys sends two messages)
	//Clear the screen after getting an input
	system("cls");
}
bool Isoddnum(int Rand) {
	int check = Rand % 2 ;
	if (check == 0) {
		return false;
	}
	else return true;

}

//Replay function (But is not working)
/*void replay(bool& isGameover) {
	string replay;
	cout << "\nDo you want to replay? \nYes or No" << endl;
	cin >> replay;
	if (replay == "Yes") {
		isGameover = false;
		health = 100;
		WaitKey();
	}
	else if (replay == "No") {
		exit(1);
	}
	else { exit(1); }
}
*/




//List of Spells enum I wasn't sure how to do it with an array and it wasn't easy doing it with enum
enum spellsID { FireBall, Heal, Shield,Boost};
string SpellsList[4] = { "FireBall","Heal","Shield","Boost"};




//Damage function 
int damage(int amount, int health,int armor) {
	double armorDef = armor - 100;
	armorDef = (armorDef / 100) * -1;
	amount *= armorDef;
	return health -= amount;

}
//Enemey damaged function
int enemyhit(int enemyhealth,int hitdamage) {
	
	enemyhealth -= hitdamage;
	if (enemyhealth <= 0) {
		enemyhealth = 0;
		return enemyhealth;
	}
	else { return enemyhealth; }
}




//Mana Regenration Function
void ManaRegen(int& mana,bool isGameover) {
	if (!isGameover) {
		double rate = 1.4;
		mana *= rate;
		if (mana >= 100) {
			mana = 100;
		}
		if (mana <= 0) {
			mana = 10;
		}
	}
}
//sets the color of the text back to white
void settextcolor() {
	HANDLE console_color;
	console_color = GetStdHandle(
		STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(
		console_color, 15);//15 for white
}



//Convert from string to Enum to get the ID of the spell for the switch statement
spellsID convert(string& str) {

	if (str == "FireBall") return FireBall;
	else if (str == "Heal") return Heal;
	else if (str == "Shield") return Shield;
	else if (str == "Boost") return Boost;
	else cout << "You must enter a correct spell name"<<endl;

}
//Function to cast the spells what spells do is also written here P.S: Could have made that every spells has its own funciton
void castspell(string spell, int& mana,int& health,int& armor,int& hitdamage,int& enemyhealth) {
	int ReqMana = 0;
	int amountHealed = 0;
	int shield = 0;
	int calc = 0;
	double rate = 0;
	int FireBallHit = 0;

	spellsID ID = convert(spell);
	switch (ID) {
	case 0:
		ReqMana = 40;
		if (mana >= ReqMana) {
			cout << "You Cast FireBall and that costs " << ReqMana << " mana." << endl;
			mana -= ReqMana;
			FireBallHit = 40;
			enemyhealth = enemyhit(enemyhealth, FireBallHit);
			cout << "And your enemy health is now = " << enemyhealth<<endl;
		}
		else { cout << "You don't have enough mana. You need " << ReqMana <<" mana" << endl; }
		break;
	case 1:
		ReqMana = 30;
		if (mana >= ReqMana) {
			amountHealed = 40;
			cout << "You Cast Heal and that costs " << ReqMana << " mana." << endl;
			mana -= ReqMana;
			health += amountHealed;
			if (health >= 100) {
				health = 100;
			}
			cout << "And your health now = " << health << endl;
		}
		else { cout << "You don't have enough mana. You need " << ReqMana << " mana." << endl; }
		break;
	case 2 :
		ReqMana = 20;
		shield = 50;
		if (mana >= ReqMana) {
			armor += shield;
			if (armor <= 100) {
				
				cout << "You cast Shield and that costs " << ReqMana << " mana." << endl;
				cout << "And now your armor = " << armor << endl;
				mana -= ReqMana;
			}
			else if (armor > 100) {
				armor = 100;
				cout << "Your armor is 100, You can't get more!" << endl;
			}
		
		}
		else {
			if(mana<ReqMana)
				{ cout << "You don't have enough mana. You need " << ReqMana << "mana." << endl; 
			}
		}
		break;
	case 3:
		ReqMana = 50;
		if (mana >= ReqMana && hitdamage<100) 
		{
			if (hitdamage < 100) {
				calc = 40 + rand() % 70;
				rate = (100 + calc);
				rate = rate / 100;
				hitdamage *= rate;
				if (hitdamage >= 100) {
					hitdamage = 100;
					cout << "You boosted your damage and is now = " << hitdamage << endl;
					cout << "And that costs = " << ReqMana << endl;
					mana -= ReqMana;
				}
				else {
					cout << "You boosted your damage and is now = " << hitdamage << endl;
					cout << "And that costs = " << ReqMana << endl;
					mana -= ReqMana;
				}
			}

		}
		else {
			if (mana < 50) {
				cout << "You don't have enough mana. You need " << ReqMana << " mana." << endl;

			}
			else if (hitdamage >= 100) {
				hitdamage = 100;
				{
				cout << "Your damage is 100. You Can't get more!" << endl;
			}
			}
			
		}
		break;

	default:
		cout << "You didn't cast anything and that didn't use any mana "<<endl;
	}
}

bool isGameover;
bool isnotfirstround = false;
bool CanGetHit = false;

int main() 
{
	//Sets the color of the console
	HANDLE console_color;
	console_color = GetStdHandle(
		STD_OUTPUT_HANDLE);
	//sets the color of the text
	int textcolor;
	textcolor = 11;
	//Calls a function to wait for key input
	WaitKey();

	int health, mana,armor,Rand,enemyhealth,hitdamage;
	//Counter and Rand to get hit randomily after rounds P.S:every round is supposed to be after every keyword entered
	int counter = 0;
	
	
	//----------
	health = 100;
	mana = 100;
	armor = 10;
	hitdamage = 10;
	enemyhealth = 160;
	cout << "\n\nKeywords are : "<<endl;
	cout << "spell " << endl;
	cout << "status " << endl;
	cout << "damage ( Will damage you ) " << endl;
	cout << "hit ( Will hit your enemy ) " << endl;

	cout << "\nHealth = " << health << endl;
	cout << "Mana = " << mana << endl;
	cout << "Armor = " << armor << endl;
	cout << "Damage = " << hitdamage << endl;
	cout << "\nYour enemy health is = " << enemyhealth << endl;
	string keyword;
	::isGameover = false;
	//The Game loop
	while (keyword != "stop" && health > 0 && enemyhealth > 0)
	{
		srand(time(0));
		Rand = rand();
		//What is available for the user to do
		cin >> keyword;
		if (keyword == "damage") {
			cout << "Enter the amount of damage = ";
			int amount;
			cin >> amount;

			health = damage(amount, health, armor);
			if (health <= 0) { 
				continue; 
			}
			else {
				//change the color of hit text to red : 12
				textcolor = 12;
				SetConsoleTextAttribute(
					console_color, textcolor);

				cout << "You got hit by " << amount << " damage points" << endl;
				cout << "And now your health = " << health << endl;
			}

		}
		if (keyword == "status") {
			cout << "Health = " << health << endl;
			cout << "Mana = " << mana << endl;
			cout << "Armor = " << armor << endl;
			cout << "Damage = " << hitdamage << endl;
		}

		if (keyword == "spell") {
			string spell;
			cout << "Enter the name of the spell or Write Index = "<<endl;
			cin >> spell;
			if (spell == "Index")
			{
				cout << "The Spells you unlocked are "<<endl; 
				for (string spell : SpellsList) {
					cout << spell<<" , ";
				}
				cout << "\nEnter the spell you want = " << endl;
				cin >> spell;
			}

			castspell(spell, mana, health,armor,hitdamage,enemyhealth);
		}
		//hit enemy function
		if (keyword == "hit") {
					
			cout << "You hit your enemy with " << hitdamage << " damage points!" << endl;
			enemyhealth = enemyhit(enemyhealth, hitdamage);
			cout << "And your enemy health = "<< enemyhealth<<endl;
		}
		//Get hit randomly with amounts that varies from 0 to 50
		bool isoddnum;
		isoddnum = Isoddnum(Rand);
		if (isoddnum && isnotfirstround&& CanGetHit) {
			//change the color of the hit text to Red : 12
			textcolor = 12;
			SetConsoleTextAttribute(
				console_color, textcolor);
			int Hitamount = 10 + rand() % 50;
			//Critical hit is just a name , it doesnt do anything fancy yet
			if (Hitamount >= 35) {
				cout << "CRITICAL HIT!"<<endl;
			}
			cout << "YOU GOT HIT BY " << Hitamount<<endl;
			health -= Hitamount;
			if (health < 0) {
				health = 0;
			}
			cout << "YOUR HEALTH NOW = " << health << endl;
			CanGetHit = false;
		}
		//this is what does the randomization for the user to get hit and always cant get hit in the first round
		while (!isGameover) {
			
			if (counter % 3) {
				CanGetHit = true;
				counter++;
			}
			counter++;
			break;

		}
		isnotfirstround = true;
		ManaRegen(mana, isGameover);
		settextcolor();
	}
	string str;
	if (keyword == "stop") {
		
		cout << "You ended the game" << endl;


		//just to not exit immediately when launched from the exe in the project directory
		//and looks like it worked one time and didnt want to do it again :(
		getline(cin, str);
		//--------------------------
	}
	else if (health <= 0) {
		cout << "\nYou Died. " << endl;
		
		getline(cin, str);
	}
	else if (enemyhealth == 0) {
		cout << "\nYOU WIN!!!!!!" << endl;
		
		getline(cin, str);
		
	}
	return 0;

}

