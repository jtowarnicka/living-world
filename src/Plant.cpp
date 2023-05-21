#include "../headers/Plant.h"

Plant::Plant(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Organism(position, parent, power, initiative, liveLength, powerToReproduce)
{
	setSpecies("P");
}

Plant::Plant(Organism* parent) : Organism(parent)
{
	setSpecies("P");
}

void Plant::move(int dx, int dy)
{
	position.move(0,0);
}

Grass::Grass(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Plant(position, parent, power, initiative, liveLength, powerToReproduce)
{
    setSpecies("G");
}

Grass::Grass(Organism* parent) : Plant(parent)
{
    setSpecies("G");
    setPower(0);
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(3);
}

Grass::~Grass()
{
    std::cout << "Grass destructor" << std::endl;
//    std::cout << "Grass " << this << " is deleting itself" << std::endl;
}

Organism* Grass::clone(Position position)
{
    setPower(power/2);
    Organism* newOrg = new Grass(this);
    newOrg->setPosition(position);
    newOrg->history->ancestor = history;
    history->descendant.emplace_back(newOrg->history);
    return newOrg;
}


Dandelion::Dandelion(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Plant(position, parent, power, initiative, liveLength, powerToReproduce)
{
    setSpecies("D");
}

Dandelion::Dandelion(Organism* parent) : Plant(parent)
{
    setSpecies("D");
    setPower(0);
    setInitiative(0);
    setLiveLength(6);
    setPowerToReproduce(2);
}

Dandelion::~Dandelion()
{
    std::cout << "Dandelion destructor" << std::endl;
}

Organism* Dandelion::clone(Position position)
{
    setPower(power/2);
    Organism* newOrg = new Dandelion(this);
    newOrg->setPosition(position);
    newOrg->history->ancestor = this->history;
    this->history->descendant.emplace_back(newOrg->history);
    return newOrg;
}

Toadstool::Toadstool(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
    : Plant(position, parent, power, initiative, liveLength, powerToReproduce)
{
    setSpecies("T");
}

Toadstool::Toadstool(Organism* parent) : Plant(parent)
{
    setSpecies("T");
    setPower(0);
    setInitiative(0);
    setLiveLength(12);
    setPowerToReproduce(4);
}

Toadstool::~Toadstool()
{
    std::cout << "Toadstool destructor" << std::endl;
}

Organism* Toadstool::clone(Position position)
{
    setPower(power/2);
    Organism* newOrg = new Toadstool(this);
    newOrg->setPosition(position);
    newOrg->history->ancestor = history;
    history->descendant.emplace_back(newOrg->history);
    return newOrg;
}

BOOST_CLASS_EXPORT(Grass)
BOOST_CLASS_EXPORT(Dandelion)
BOOST_CLASS_EXPORT(Toadstool)
