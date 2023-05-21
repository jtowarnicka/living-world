#pragma once
#include "Organism.h"

class Animal : public Organism
{
public:
    Animal(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce);
    Animal(Organism* parent);
    Animal() {};
    virtual ~Animal() = default;

    virtual void move(int dx, int dy);

    virtual Organism* clone(Position position) = 0;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Organism>(*this);
    }
};

class Sheep : public Animal
{
public:
    Sheep(Position position, Organism* parent, int power = 3, int initiative = 3, int liveLength = 10, int powerToReproduce = 6);
    Sheep(Organism* parent);
    Sheep() {};
    ~Sheep();

    virtual Organism* clone(Position position);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Animal>(*this);
    }
};

class Wolf : public Animal
{
public:
    Wolf(Position position,  Organism* parent, int power = 8, int initiative = 5, int liveLength = 20, int powerToReproduce = 16);
    Wolf(Organism* parent);
    Wolf() {};
    ~Wolf();

    virtual Organism* clone(Position position);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Animal>(*this);
    }
};
