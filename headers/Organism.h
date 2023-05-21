#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "Position.h"
#include "HistoryPair.h"

class Organism
{
protected:
	Position position;
	std::string species;
    int power;
    int initiative;
    int liveLength;
    int powerToReproduce;

public:
    HistoryPair *history;
	Organism(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce);
    Organism(Organism* parent)
        : position(0, 0), species("O"), power(0), initiative(0), liveLength(0), powerToReproduce(0)
    {
        history = new HistoryPair;
        if (parent != NULL) history->ancestor = parent->history;
        else history->ancestor = NULL;
    }
    Organism() {};
    virtual ~Organism() = default;

    int& getPower();
	void setPower(int power);
    Position& getPosition();
	void setPosition(Position position);
    int getInitiative();
    void setInitiative(int initiative);
    int& getLiveLength();
    void setLiveLength(int liveLength);
    int getPowerToReproduce();
    void setPowerToReproduce(int powerToReproduce);
	std::string getSpecies();
	void setSpecies(std::string spec);

	std::string toString();

    bool canReproduce();
    bool shouldDie();
    void lifeCycle();
    void seeAncestors();
    void seeDescendants();

    virtual Organism* clone(Position position) = 0;

	virtual void move(int dx, int dy) = 0;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& position;
        ar& species;
        ar& power;
        ar& initiative;
        ar& liveLength;
        ar& powerToReproduce;
        ar& history;
    }
};
