
#include <b2ge/b2ge.hpp>
#include <cmath>
#include <functional>

bool isRunning;

// Components

struct Player : public b2ge::Component
{
  std::string name;
};

struct Vector2D : public b2ge::Component
{
  float x;
  float y;
};

std::ostream& operator<<(std::ostream& out, const Vector2D& vector2D)
{
  out << "(" << vector2D.x << "," << vector2D.y << ")";
  return out;
}

// Systems

class MoveSystem : public b2ge::SystemUpdatable
{
 public:
  MoveSystem()
  {
    addComponentRequired<Player, Vector2D>();
  }

  void update(float deltaTime) override
  {
    auto entities = getEntities();

    for (auto &it : entities)
    {
      auto &player = it.second->getComponent<Player>();

      std::cout << player.name << std::endl;
    }
    isRunning = false;
    (void)deltaTime;
  }
};

void addSystems(b2ge::World &world)
{
  world.getSystemManager().add<MoveSystem>();
}

void addEntities(b2ge::World &world)
{
  auto &entity1 = world.getEntityManager().create("entity1");

  entity1.addComponent<Vector2D>();
  auto &entity1Player = entity1.addComponent<Player>();
  entity1Player.name = "playerName1";

  world.getEntityManager().create("entity2");

  auto &entity2 = world.getEntityManager().get("entity2");

  entity2.addComponent<Vector2D>();
  entity2.addComponent<Player>().name = "playerName2";
}

int main()
{
  b2ge::World world;
  float deltaTime = 0.6f;

  isRunning = true;

  addSystems(world);
  addEntities(world);

  while (isRunning)
  {
    world.update(deltaTime);
  }

  return 0;
}
