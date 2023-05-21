#pragma once
#include "Organism.h"
#include <fstream>

class Plant : public Organism
{
public:
    Plant(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce);
    Plant(Organism* parent);
    Plant() = default;;
    virtual ~Plant() = default;

    void move(int dx, int dy);

    virtual Organism* clone(Position position) = 0;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Organism>(*this);
    }
};

class Grass : public Plant {
public:
    Grass(Position position, Organism *parent, int power = 0, int initiative = 0, int liveLength = 6,
          int powerToReproduce = 3);
    Grass(Organism *parent);
    Grass() {};
    ~Grass();

    virtual Organism *clone(Position position);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Plant>(*this);
    }

};

class Dandelion : public Plant
{
public:
    Dandelion(Position position, Organism* parent, int power = 0, int initiative = 0, int liveLength = 6, int powerToReproduce = 2);
    Dandelion(Organism* parent);
    Dandelion() {};
    ~Dandelion();

    virtual Organism* clone(Position position);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Plant>(*this);
    }
};

class Toadstool : public Plant
{
public:
    Toadstool(Position position, Organism* parent, int power = 0, int initiative = 0, int liveLength = 12, int powerToReproduce = 4);
    Toadstool(Organism* parent);
    Toadstool() {};
    ~Toadstool();

    virtual Organism* clone(Position position);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Plant>(*this);
    }
};
