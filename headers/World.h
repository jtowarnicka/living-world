#pragma once
#include "Organism.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;

class World {
private:
    int worldX;
    int worldY;
    int turn = 0;
    vector<Organism*> organisms;
    vector<HistoryPair*> progenitors;
    char separator = '.';

    Organism *getOrganismFromPosition(int x, int y);

    bool isPositionOnWorld(int x, int y);

    bool isPositionFree(Position position);

public:
    World(int X, int Y);

    World() : World(6, 6) {};

    int getWorldX();

    void setWorldX(int X);

    int getWorldY();

    void setWorldY(int Y);

    int getTurn();

    void addOrganism(Organism *organism);

    void removeOrganism(Organism *organism);

    vector<Position> getVectorOfFreePositionsAround(Position position);

    vector<Position> getVectorOfPositionsAround(Position position);

    void turnCollision(Organism *org, Organism *other, Position newPosition);

    void turnMove(Organism *org);

    void turnBirth(Organism *org);

    void makeTurn();

    static int calcMovement(int coord, int m);
    template <typename Property>
    void sortOrganisms(Property property);

    void cleanDescendant(HistoryPair* org);
    void cleanWorldHistory();

    string toString();

    void writeWorld(string fileName);
    void readWorld(string fileName);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & worldX;
        ar & worldY;
        ar & turn;
        ar & organisms;
    }
};
