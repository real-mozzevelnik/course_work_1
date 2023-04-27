#ifndef ECS_h
#define ECS_h

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;


class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}


template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID();
}


constexpr size_t maxComponents = 32;

using ComponentBitSet = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;


class Component
{
    public:
        Entity *entity;

        virtual void init() {};
        virtual void update() {};
        virtual void draw() {};

        virtual ~Component() {};
};


class Entity
{
    private:
        bool active = true;
        vector<unique_ptr<Component>> components;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;

    public:
        void update()
        {
            for (auto& c : components) c->update();
            for (auto& c : components) c->draw();
        }

        void draw() {};
        bool isActive() { return active; };
        void destroy() { active = false; }

        template <typename T> bool hasComponent() const
        {
            return componentBitSet[getComponentID<T>];
        }

        template<typename T, typename... Targs>
        T& addComponent(Targs&&... mArgs)
        {
            T* c(new T(forward<Targs>(mArgs)...));
            c->entity = this;
            unique_ptr<Component> uPtr{ c };
            components.emplace_back(move(uPtr));

            componentArray[getComponentTypeID<T>()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;

            c->init();
            return *c;
        }

        template<typename T> T& getComponent() const
        {
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }
};

#endif