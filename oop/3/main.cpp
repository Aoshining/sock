#include "Adventure.h"

using namespace std;

int main()
{
	cout << "(The size of this castle is " << N << "*" << N << ". Good luck!)" << endl;
	srand(time(NULL));
	Castle player;
	while(player.game)
	{
		player.choice();
		string cmd;
		getline(cin,cmd);
		player.move(cmd);
	}
}