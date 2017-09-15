
#include <b2ge/b2ge.hpp>
#include <cmath>
#include <functional>

bool isRunning;

// Components

struct Player : public b2ge::Component
{
  std::string name;
  float startX;
  float startY;
  float targetX;
  float targetY;
  float speed;

  double distance;
  bool moving;
  double directionX;
  double directionY;
  bool isInitialized;

  std::function<void()> onPlayerReachTarget;

  Player()
  {
    isInitialized = false;
    moving = true;
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
  void initializePlayer(std::shared_ptr<b2ge::Entity> &entity)
  {
    auto &entityPlayer = entity->getComponent<Player>();
    auto &entityPosition = entity->getComponent<Vector2D>();

    auto powOfX = std::pow(entityPosition.x - entityPlayer.startX, 2);
    auto powOfY = std::pow(entityPosition.y - entityPlayer.startY, 2);
    auto currentDistance = std::sqrt(powOfX + powOfY);

    entityPlayer.directionX = (entityPlayer.targetX - entityPlayer.startX) / currentDistance;
    entityPlayer.directionY = (entityPlayer.targetY - entityPlayer.startY) / currentDistance;

    entityPosition.x = entityPlayer.startX;
    entityPosition.y = entityPlayer.startY;
    entityPlayer.moving = true;
    entityPlayer.isInitialized = true;
  }

  void moveEntityToTargetPosition(float deltaTime, std::shared_ptr<b2ge::Entity> &entity)
  {
    auto &entityPlayer = entity->getComponent<Player>();

    exit;

    if (entityPlayer.moving && !entityPlayer.isInitialized)
      initializePlayer(entity);

    if (!entityPlayer.moving)
      return;

    auto &entityPosition = entity->getComponent<Vector2D>();

    entityPosition.x += entityPlayer.directionX * entityPlayer.speed * deltaTime;
    entityPosition.y += entityPlayer.directionY * entityPlayer.speed * deltaTime;

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

    std::cout << entities.size() << std::endl;

    exit(1);

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
  std::cout << "Ok" << std::endl;
  isRunning = false;
}

void addEntities(b2ge::World &world)
{
  auto &entity1 = world.getEntityManager().create();

//  entity1.addComponent<Vector2D>();

  auto &entity1Player = entity1.addComponent<Player>();
  entity1Player.onPlayerReachTarget = onPlayerReachTarget;
  entity1Player.startX = 0;
  entity1Player.startY = 0;
  entity1Player.targetX = 5;
  entity1Player.targetY = 5;
  entity1Player.speed = 0.5f;
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