// gambling
// author:  Holger Arndt
// version: 12.11.2012
// framework for sheet 4, exercise 11

#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Bet
{
private:
	unsigned int money;
	char result; // one of o, e, 1, 2, 3, 4, 5, 6
public:
	Bet(int m = 0, char r = '0') : money(m), result(r) {}
	unsigned int getMoney() const { return money; }
	char getResult() const { return result; }
	void setMoney(int m){money = m;}//勝手につくっていいのか不明
	void setResult(char c){ result = c;}//勝手につくっていいのか不明
};

//////////////////////////////////////////////////////////////////
// Add the classes Player, HumanPlayer, and ComputerPlayer here //
//////////////////////////////////////////////////////////////////

class Player
{
private:
	char type;//いらないかも？？
	string name;
	unsigned int money;
public:
	Player(char t='0', string n="",int m = 1000): type(t), name(n),money(m){}
	string setName(string n) {n = name;}
	string getName() { return name;}
	unsigned int getMoney() const { return money; }
	virtual Bet bet();//変更の必要あり？？
	void win(int m);
};

class HumanPlayer:public Player
{
public:
	HumanPlayer(){}
	HumanPlayer(string n){
		Player p;
		p.setName(n);
	}
	virtual Bet bet();//virtualいる？？
};

class ComputerPlayer:public Player
{
public:
	ComputerPlayer(){}
	ComputerPlayer(string n){
		Player p;
		p.setName(n);
	}
	virtual Bet bet();//virtualいる？？
};

void Player::win(int m){
	money += m;
}
Bet Player::bet(){
	//いらないかも？？
}
Bet HumanPlayer::bet(){
	int betm;
	char c;
	Bet bh;
	HumanPlayer hp;
	cout << "Player " << hp.getName() << ", your bet :" << endl;
	cout << "amount of money (you have " << hp.getMoney() << "):";
	cin >> betm;
	cout << "result(o[dd], e[ven], 1, 2, 3, 4, 5, 6):";
	cin >> c;
	bh.setMoney(betm);//勝手につくっていいのか不明
	bh.setResult(c);//勝手につくっていいのか不明
	return bh;
}

Bet ComputerPlayer::bet(){
	//ここどうしようかなぁ　適当に
	int betm;
	string str;
	char c;
	int r = rand() % 8 + 1;
	ComputerPlayer cp;
	Bet bc;
	switch(r){
		case 0:
			str = "an odd number";
			c = 'o';
			break;
		case 1:
			str = "an even numer";
			c = 'e';
			break;
		case 2:
			str = '1';
			c = '1';
			break;
		case 3:
			str = '2';
			c = '2';
			break;
		case 4:
			str = '3';
			c = '3';
			break;
		case 5:
			str = '4';
			c = '4';
			break;
		case 6:
			str = '5';
			c = '5';
			break;
		case 7:
			str = '6';
			c = '6';
			break;
	}

	betm = rand() % cp.getMoney();
	cout << "Player " << cp.getName() << " bets " <<  betm << " on " << str << endl;
	bc.setMoney(betm);//勝手につくっていいのか不明
	bc.setResult(c);//勝手につくっていいのか不明
	return bc;
}
int main()
{
	list<Player*> pl;
	unsigned int n;
	string name;
	string dummy;
	char type;
	// setup players
	cout << "number of players: ";
	cin >> n;
	for (unsigned int i = 1; i <= n; ++i)
	{
		cout << "Player " << i << ": human or computer (enter h/c): ";
		cin >> type;
		cout << "player's name: ";
		getline(cin, dummy); // read rest of line after 'h' or 'c', at least '\n'
		getline(cin, name);
		if (type == 'h')
			pl.push_back(new HumanPlayer(name));//push_back＝リストに追加
		else
			pl.push_back(new ComputerPlayer(name));
	}

	// start game
	auto plit = pl.begin();
	Bet b;
	mt19937_64 rnd(time(nullptr));  // intialize random number generator
	while (pl.size() > 1)
	{
		b = (*plit)->bet();  // ask player for the bet
		int r = rnd() % 6 + 1;  //roll dice
		cout << "Rolled: " << r << endl;
		if ((b.getResult() == 'o' && (r == 1 || r == 3 || r == 5))
			|| (b.getResult() == 'e' && (r == 2 || r == 4 || r == 6)))
		{
			(*plit)->win(2 * b.getMoney()); // add money
			cout << (*plit)->getName() << " wins " << 2 * b.getMoney()
				<< ", now has " << (*plit)->getMoney() << endl;
		}
		else if (b.getResult() - '0' == r)
		{
			(*plit)->win(6 * b.getMoney());
			cout << (*plit)->getName() << " wins " << 6 * b.getMoney()
				<< ", now has " << (*plit)->getMoney() << endl;
		}
		else
			cout << (*plit)->getName() << " looses, now has "
			<< (*plit)->getMoney() << endl;
		if ((*plit)->getMoney() == 0)//残金が０、ゲームから抜ける
		{
			cout << (*plit)->getName() << " leaves the game" << endl;
			auto tmpit = plit;
			plit--;
			pl.erase(tmpit);
		}

		++plit;
		if (plit == pl.end())
			plit = pl.begin();
	}

	// just one player left, announce the winner
	cout << "Winner: " << (*pl.begin())->getName() << ", money: "
		<< (*pl.begin())->getMoney() << endl;

	return 0;
}
