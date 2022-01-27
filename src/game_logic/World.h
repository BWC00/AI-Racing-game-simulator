#ifndef PHYSICS_ENGINE_WORLD_H
#define PHYSICS_ENGINE_WORLD_H

#ifdef WIN32
#include "../imageclasses/imageProcessor.h"
#endif
#include "data_structures/Raycast.h"
#include "entities/Checkpoint.h"
#include "entities/IEntityModelCreator.h"
#include "entities/Wall.h"
#include "utils/InputMap.h"
#include "utils/Stopwatch.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <utility>

namespace Core {
class World
{
private:
        std::shared_ptr<Camera> _camera;

        // entities
        std::shared_ptr<IEntityModelCreator> _entity_model_creator;
        std::shared_ptr<Car> _player;
        std::vector<std::shared_ptr<Car>> _cars;
        std::vector<std::shared_ptr<Wall>> _walls;
        std::vector<std::shared_ptr<Checkpoint>> _checkpoints;
        std::shared_ptr<Checkpoint> _finish_line;
        std::vector<std::shared_ptr<GroundTile>> _ground_tiles;

        std::shared_ptr<InputMap> _user_input_map;

        Vector2f _spawn_location{2, 0}, _spawn_direction{0, 1};

        unsigned int generation;
        unsigned int _generation;
        float _generation_time;
        float _time_limit;

public:
        World(std::shared_ptr<IEntityModelCreator> entity_model_creator, float x_min, float x_max, float y_min,
              float y_max);

        ~World();

        void update(double t, float dt);

        std::shared_ptr<InputMap> getInputMap();

private:
        void saveMap(const std::string& filepath) const;

        void loadMap(const std::string& filepath);

        void generateGroundTiles(float scale = 1);

        void generateMapFromImage(const std::string& inputname, float scale = 1.0f);

        void meltWalls();

        void meltRows();

        void meltColumns();

        void generateSquareWallEnclosure(const Vector2f& origin, float size, float wall_thickness);

        void generateCars(const Vector2f& position, const Vector2f& direction, unsigned int amount,
                          const std::string& physics_preset = "", const std::string& sprite_preset = "");

        void generateTestMap();

        void updateEntities(double t, float dt);

        void checkCollisions();

        static bool checkCollision(const std::shared_ptr<EntityModel>& entity1,
                                   const std::shared_ptr<EntityModel>& entity2, bool collision_response = true);

        static bool checkCollision(const std::shared_ptr<Core::Raycast>& raycast,
                                   const std::shared_ptr<EntityModel>& entity);

        static bool checkCollisionPolygonAndPolygon(const std::shared_ptr<EntityModel>& entity1,
                                                    const std::shared_ptr<EntityModel>& entity2,
                                                    bool collision_response, Vector2f& mtv);

        static bool checkCollisionPolygonAndCircle(const std::shared_ptr<EntityModel>& entity1,
                                                   const std::shared_ptr<EntityModel>& entity2, bool collision_response,
                                                   Vector2f& mtv);

        static bool checkCollisionCircleAndCircle(const std::shared_ptr<EntityModel>& entity1,
                                                  const std::shared_ptr<EntityModel>& entity2, bool collision_response,
                                                  Vector2f& mtv);

        static bool checkLinesegmentLinesegmentIntersection(const Vector2f& l1p1, const Vector2f& l1p2,
                                                            const Vector2f& l2p1, const Vector2f& l2p2,
                                                            Vector2f& intersection1, Vector2f& intersection2,
                                                            bool& is_collinear);

        static bool checkLinesegmentCircleIntersection(const Vector2f& l1p1, const Vector2f& l1p2, const Vector2f& cmp,
                                                       float cr, Vector2f& intersection1, Vector2f& intersection2,
                                                       bool& collided_twice);
};
} // namespace Core

#endif // PHYSICS_ENGINE_WORLD_H
