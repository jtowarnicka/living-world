#include "../headers/Animal.h"

Animal::Animal(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Organism(position, parent, power, initiative, liveLength, powerToReproduce)
{
	setSpecies("A");
}

Animal::Animal(Organism* parent) : Organism(parent)
{
	setSpecies("A");
}

void Animal::move(int dx, int dy)
{
    position.move(dx, dy);
}

Sheep::Sheep(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Animal(position, parent, power, initiative, liveLength, powerToReproduce)
{
    setSpecies("S");
}

Sheep::Sheep(Organism* parent) : Animal(parent)
{
    setSpecies("S");
    setPower(3);
    setInitiative(3);
    setLiveLength(10);
    setPowerToReproduce(6);
}

Sheep::~Sheep() {
    std::cout << "Sheep destructor" << std::endl;
}

Organism* Sheep::clone(Position position)
{
    setPower(power/2);
    Organism* newOrg = new Sheep(this);
    newOrg->setPosition(position);
    newOrg->history->ancestor = this->history;
    history->descendant.emplace_back(newOrg->history);
    return newOrg;
}

Wolf::Wolf(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Animal(position, parent, power, initiative, liveLength, powerToReproduce)
{
    setSpecies("W");
}

Wolf::Wolf(Organism* parent) : Animal(parent)
{
    setSpecies("W");
    setPower(8);
    setInitiative(5);
    setLiveLength(20);
    setPowerToReproduce(16);
}

Wolf::~Wolf()
{
    std::cout << "Wolf destructor" << std::endl;
}

Organism* Wolf::clone(Position position)
{
    setPower(power/2);
    Organism* newOrg = new Wolf(this);
    newOrg->setPosition(position);
    newOrg->history->ancestor = this->history;
    history->descendant.emplace_back(newOrg->history);
    return newOrg;
}

BOOST_CLASS_EXPORT(Sheep)
BOOST_CLASS_EXPORT(Wolf)
