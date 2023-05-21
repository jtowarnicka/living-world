#include <fstream>
#include "../headers/World.h"

Organism* World::getOrganismFromPosition(int x, int y)
{
    for(int i = 0; i < (int)organisms.size(); i++)
    {
        if (organisms[i]->getPosition().getX() == x && organisms[i]->getPosition().getY() == y)
            return organisms[i];
    }
	return NULL;
}

bool World::isPositionOnWorld(int x, int y)
{
	return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
	return getOrganismFromPosition(position.getX(), position.getY()) != NULL;
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{
    int pos_x = position.getX(), pos_y = position.getY();
    vector<Position> result;
    for(int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) && isPositionOnWorld(pos_x + x, pos_y + y)
            && !isPositionFree(Position(pos_x+x, pos_y+y))) {
                result.emplace_back(pos_x + x, pos_y + y);
            }
    return result;
}

vector<Position> World::getVectorOfPositionsAround(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    string species = getOrganismFromPosition(pos_x, pos_y)->getSpecies();
    vector<Position> result;
    for(int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if (!(x == 0 && y == 0) &&
                isPositionOnWorld(pos_x + x, pos_y + y)) {
                if (getOrganismFromPosition(x, y) == NULL)
                    result.emplace_back(pos_x + x, pos_y + y);
                else if (species != getOrganismFromPosition(x, y)->getSpecies())
                    result.emplace_back(pos_x + x, pos_y + y);
            }
    return result;
}


World::World(int X, int Y)
{
	setWorldX(X);
	setWorldY(Y);
}

int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int X)
{
	worldX = X;
}

int World::getWorldY()
{
	return worldY;
}

void World::setWorldY(int Y)
{
	worldY = Y;
}

int World::getTurn()
{
	return turn;
}

int World::calcMovement(int coord, int m) {
    int movement = m - coord;
    if (movement > 1)
        movement = 1;
    else if (movement < -1)
        movement = -1;
    return movement;
}

template <typename Property>
void World::sortOrganisms(Property property) {
    sort(organisms.begin(), organisms.end(), [property](Organism* a, Organism* b) {
        return property(a) > property(b);
    });
}

void World::addOrganism(Organism* organism)
{
    organism->history->birth = getTurn();
    organisms.emplace_back(organism);
    if (organism != NULL)
        if (organism->history == NULL)
            progenitors.emplace_back(organism->history);

    sortOrganisms([](Organism* o) { return o->getInitiative(); });
}

void World::removeOrganism(Organism *organism) {
    for(int i = 0; i < (int)organisms.size(); ++i) {
        if (organisms[i] == organism) {
            cout << "Removing " << organism->getSpecies() << " at " << organism->getPosition().toString() << endl;
            organism->history->death = getTurn();
            delete organisms[i];
            organisms.erase(organisms.begin() + i);
        }
    }
}

void World::turnCollision(Organism* org, Organism* other, Position newPosition)
{
    if (other->getSpecies() != org->getSpecies()) {
        int dx = calcMovement(org->getPosition().getX(), newPosition.getX());
        int dy = calcMovement(org->getPosition().getY(), newPosition.getY());
        org->move(dx, dy);

        if (org->getPosition() == newPosition) {
            cout << org->getSpecies() << " moved to "
                 << org->getPosition().getX() << " " << org->getPosition().getY() << endl;

            if (org->getPower() > other->getPower() && other->getSpecies() != "T") {
                    cout << org->getSpecies() << " removed " << other->getSpecies() << endl;
                    removeOrganism(other);

            } else if (org->getPower() < other->getPower() || other->getSpecies() == "T") {
                cout << org->getSpecies() << " got removed by " << other->getSpecies() << endl;
                removeOrganism(org);
            }
        }
    }
}


void World::turnMove(Organism* org)
{
    int randomIndex;
    vector<Position> newPositions = getVectorOfPositionsAround(org->getPosition());
    if (!newPositions.empty()) {
        randomIndex = rand() % newPositions.size();
        Position newPosition = newPositions[randomIndex];
        Organism* other = getOrganismFromPosition(newPosition.getX(), newPosition.getY());
        if (other != NULL)
        {
            turnCollision(org, other, newPosition);
        } else {
            int dx = calcMovement(org->getPosition().getX(), newPosition.getX());
            int dy = calcMovement(org->getPosition().getY(), newPosition.getY());
            org->move(dx, dy);
            if (org->getPosition() == newPosition)
            cout << org->getSpecies() << " moved to "
                 << org->getPosition().getX() << " " << org->getPosition().getY() << endl;
        }
    }
}

void World::turnBirth(Organism *org)
{
    if (org->shouldDie()) {
        cout << org->getSpecies() << " died of an old age at " << org->getPosition().toString() << endl;
        removeOrganism(org);
    }
    else
    {
        if (org->canReproduce()) {
            vector<Position> newPositions;
            int randomIndex;
            newPositions = getVectorOfFreePositionsAround(org->getPosition());
            if (!newPositions.empty()) {
                randomIndex = rand() % newPositions.size();
                Organism *baby = org->clone(newPositions[randomIndex]);
                addOrganism(baby);
                cout << "There's new of " << org->getSpecies()
                << " birth at " << newPositions[randomIndex].toString() << endl;
            }
        }
    }
}

void World::makeTurn()
{
    for(int i = 0; i < (int)organisms.size(); i++) {
//        organisms[i]->seeAncestors();
//        organisms[i]->seeDescendants();
        turnMove(organisms[i]);
        organisms[i]->lifeCycle();
        turnBirth(organisms[i]);
    }
    sortOrganisms([](Organism* o) { return o->getInitiative(); });
    turn++;
}

void World::writeWorld(std::string fileName) {
    std::ofstream outFile(fileName, std::ios::binary);
    boost::archive::binary_oarchive outArchive(outFile);
    outArchive << *this;
    outFile.close();
}

void World::readWorld(std::string fileName) {
    std::ifstream inFile(fileName, std::ios::binary);
    boost::archive::binary_iarchive inArchive(inFile);
    inArchive >> *this;
    inFile.close();
}

void World::cleanDescendant(HistoryPair* org)
{
    for(int i = 0; i < org->descendant.size(); i++)
    {
        if (!org->descendant[i]->descendant.empty())
        {
            cleanDescendant(org->descendant[i]);
            delete org->descendant[i];
        }
        else
            delete org->descendant[i];
    }
}

void World::cleanWorldHistory()
{
    for(int i = 0; i < progenitors.size(); i++)
    {
        cleanDescendant(progenitors[i]);
        delete progenitors[i];
    }
}

string World::toString()
{
	string result = "\nturn: " + to_string(getTurn()) + "\n";
	string spec;
	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
            if (getOrganismFromPosition(wX, wY) != NULL) {
                result += getOrganismFromPosition(wX, wY)->getSpecies();
            }
            else {
                result += separator;
            }
		};
		result += "\n";
	}
	return result;
}
