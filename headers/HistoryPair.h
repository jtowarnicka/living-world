#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>

struct HistoryPair
{
    int birth = -1;
    int death = -1;
    HistoryPair *ancestor = NULL;
    std::vector<HistoryPair*> descendant;

    bool isAnyChildAlive(HistoryPair *temp);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& birth;
        ar& death;
        ar& ancestor;
        ar& descendant;
    }
};
