#include <iostream>
#include "../headers/Animal.h"
#include "../headers/Plant.h"
#include "../headers/World.h"

int main()
{
    srand(time(NULL));

	World world;
    Grass *g1 = new Grass(NULL);
    g1->setPosition(Position(0, 0));
    Grass *g2 = new Grass(NULL);
    g2->setPosition(Position(4, 4));
    Sheep *s1 = new Sheep(NULL);
    s1 ->setPosition(Position(2,2));
    Wolf *w1 = new Wolf(NULL);
    w1->setPosition(Position(1,1));
    Toadstool *t1 = new Toadstool(NULL);
    t1->setPosition(Position(5,5));
    Dandelion *d1 = new Dandelion(NULL);
    d1->setPosition(Position(3,3));

    world.addOrganism(g1);
    world.addOrganism(g2);
    world.addOrganism(s1);
    world.addOrganism(w1);
    world.addOrganism(t1);
    world.addOrganism(d1);

    cout << world.toString() << endl;
//    for(int i = 0; i < 12; i++)
//    {
//        world.makeTurn();
//        cout << world.toString() << endl;
//    }

    // Tura 1
    world.makeTurn();
    cout << world.toString() << endl;

    // Tura 2
    world.makeTurn();
    cout << world.toString() << endl;

    world.writeWorld("world.bin");

    // Tura 3
    world.makeTurn();
    cout << world.toString() << endl;

    // powrot do Tury 2
    world.readWorld("world.bin");
    cout << world.toString() << endl;

    world.cleanWorldHistory();

	return 0;
}
