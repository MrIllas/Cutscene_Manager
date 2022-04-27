#include "SceneGame.h"

class SpellSpawnManager;

class TestScene :  public SceneGame
{
public:

	TestScene();

	~TestScene();

	bool Start() override;

	bool PreUpdate() override;

	bool Update() override;

	bool PostUpdate() override;

	bool CleanUp() override;
private:

	SpellSpawnManager* spawnManager = nullptr;
};