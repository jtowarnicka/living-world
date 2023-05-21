#pragma once
#include <string>
#include <cmath>

class Position {
private:
	int x;
	int y;

public:
	Position(int x, int y);
	Position() : x(0), y(0) {}

	int getX() const;
	void setX(int x);
	int getY() const;
	void setY(int y);

	std::string toString();

	double distance(Position position);
	void move(int dx, int dy);

    bool operator==(const Position& position) const;
    bool operator!=(const Position& position) const;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& x;
        ar& y;
    }
};
