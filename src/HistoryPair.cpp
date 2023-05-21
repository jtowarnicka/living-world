#include "../headers/HistoryPair.h"

bool HistoryPair::isAnyChildAlive(HistoryPair *temp) {
    if (temp->death == -1) return true;
    for(int i = 0; i < (int)temp->descendant.size(); i++)
    {
        if (isAnyChildAlive(temp->descendant[i]))
            return true;
    }
    return false;
}