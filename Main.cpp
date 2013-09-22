#include "GameEngine.h"


using namespace std;

int main(void)
{
	GameEngine *engine = GameEngine::getInstance();
	engine->run();
	deleteObj(engine);

	return 0;
}
