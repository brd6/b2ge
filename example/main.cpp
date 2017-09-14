
#include <b2ge/b2ge.hpp>
#include <cmath>
#include <functional>

// Components

struct Player : public b2ge::Component
{
  std::string name;
  float startX;
  float startY;
  float targetX;
  float targetY;
  double distance;
  bool moving;
  float speed;

  std::function<void()> onPlayerReachTarget;

  Player()
  {
    moving = true;
    startX = 0;
    startY = 0;
    speed = 0.3f;
    distance = 0;

    
  }
};

struct Vector2D : public b2ge::Component
{
  float x;
  float y;
};


// Systems

class MoveSystem : public b2ge::SystemUpdatable
{
 public:
  MoveSystem()
  {
    addComponentRequired<Player, Vector2D>();
  }

 protected:
  void moveEntityToTargetPosition(float deltaTime, std::shared_ptr<b2ge::Entity> &entity)
  {
    auto &entityPlayer = entity->getComponent<Player>();

    if (!entityPlayer.moving)
      return;

    auto &entityPosition = entity->getComponent<Vector2D>();

    entityPosition.x += entityPlayer.targetX * entityPlayer.speed * deltaTime;
    entityPosition.y += entityPlayer.targetY * entityPlayer.speed * deltaTime;

    auto powOfX = std::pow(entityPosition.x - entityPlayer.startX, 2);
    auto powOfY = std::pow(entityPosition.y - entityPlayer.startY, 2);
    auto currentDistance = std::sqrt(powOfX + powOfY);

    if(currentDistance >= entityPlayer.distance)
    {
      entityPosition.x = entityPlayer.targetX;
      entityPosition.y = entityPlayer.targetY;
      entityPlayer.moving = false;
      entityPlayer.onPlayerReachTarget();
    }
  }

  void update(float deltaTime) override
  {
    auto entities = getEntities();

    for (auto &it : entities)
    {
      moveEntityToTargetPosition(deltaTime, it.second);
    }
  }

};

void addSystems(b2ge::World &world)
{
  world.getSystemManager().add<MoveSystem>();
}

void onPlayerReachTarget()
{

}

void addEntities(b2ge::World &world)
{
  auto &entity1 = world.getEntityManager().create();

  auto &entity1Player = entity1.addComponent<Player>();
  entity1Player.onPlayerReachTarget = onPlayerReachTarget;
  entity1Player.startX = 12;
  entity1Player.startY = 12;
}

int main()
{
  b2ge::World world;
  float deltaTime = 0.6f;
  bool isRunning = true;

  addSystems(world);
  addEntities(world);

  while (isRunning)
  {
    world.update(deltaTime);
  }

  return 0;
}