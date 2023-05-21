#include "../headers/Organism.h"

Organism::Organism(Position position, Organism* parent, int power, int initiative, int liveLength, int powerToReproduce)
{
    setPosition(position);
    setPower(power);
    setInitiative(initiative);
    setLiveLength(liveLength);
    setPowerToReproduce(powerToReproduce);
    setSpecies("O");
    history = new HistoryPair;
    if (parent != NULL) history->ancestor = parent->history;
    else history->ancestor = NULL;
}

//Organism::~Organism()
//{
//
//}

int& Organism::getPower()
{
	return this->power;
}
void Organism::setPower(int power)
{
	this->power = power;
}

Position& Organism::getPosition()
{
	return this->position;
}
void Organism::setPosition(Position position)
{
	this->position = position;
}

int Organism::getInitiative()
{
    return this->initiative;
}
void Organism::setInitiative(int initiative)
{
    this->initiative = initiative;
}

int& Organism::getLiveLength()
{
    return this->liveLength;
}
void Organism::setLiveLength(int liveLength)
{
    this->liveLength = liveLength;
}

int Organism::getPowerToReproduce()
{
    return this->powerToReproduce;
}
void Organism::setPowerToReproduce(int powerToReproduce)
{
    this->powerToReproduce = powerToReproduce;
}

std::string Organism::getSpecies()
{
    return this->species;
}
void Organism::setSpecies(std::string spec)
{
    this->species = spec;
}

std::string Organism::toString()
{
	return "{ species: " + this->getSpecies() + 
		", power: " + std::to_string(getPower()) +
		", position: " + getPosition().toString() +
        ", initiative: " + std::to_string(getInitiative()) +
        ", liveLength: " + std::to_string(getLiveLength()) +
        ", powerToReproduce: " + std::to_string(getPowerToReproduce()) +
        "}";
}

bool Organism::canReproduce()
{
    return getPower() >= getPowerToReproduce();
}

bool Organism::shouldDie()
{
    return getLiveLength() <= 0;
}

void Organism::lifeCycle() {
    setPower(getPower() + 1);
    setLiveLength(getLiveLength() - 1);
}

void Organism::seeAncestors()
{
    HistoryPair *temp = history->ancestor;
    if (temp != NULL) {
        std::cout << "Ancestors of " << getSpecies() << ": ";
        while (temp != NULL) {
            std::cout << "birth: " << temp->birth << ", ";
            if (temp->death != -1) std::cout << "death: " << temp->death;
            else std::cout << "still alive";
            std::cout << " | ";
            temp = temp->ancestor;
        }
        std::cout << std::endl;
    }
}

void Organism::seeDescendants()
{
    HistoryPair *temp = history;
    if (!temp->descendant.empty()) {
        std::cout << "Descendants of " << getSpecies() << ": ";
        for (int i = 0; i < (int) temp->descendant.size(); i++) {
            std::cout << "birth: " << temp->descendant[i]->birth << ", ";
            if (temp->descendant[i]->death != -1) std::cout << "death: " << temp->descendant[i]->death;
            else std::cout << "still alive";
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
}
