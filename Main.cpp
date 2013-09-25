#include "GameEngine.h"


using namespace std;

int main(void)
{
	GameEngine *engine = GameEngine::getInstance();
	engine->run();
	delete engine;
	return 0;
}
