
#include "FlappyTwitch\GameManager.h"

#include <iostream>
#include <time.h>

#include "Windows.h"
#include "MMSystem.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Hello, Twitch!" << endl;
	srand(time(NULL));
	
	
	GameManager gameManager;
	gameManager.Start();

	return 0;
}