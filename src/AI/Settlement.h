#include <iostream>

#pragma once

using namespace std;

/** @brief Class that defines a settlement built by AI
 *
 *  Represents one settlement built by AI that has soldiers
 *
*/
class Settlement{
public:
    Settlement(const size_t & initialSoldiers);
    /** number of current soldiers in the settlement*/
    size_t soldiers;
    /** Self-explanatory, simply adds to soldiers*/
    void addSoldiers(const size_t & number);
    /** Self-explanatory, simply removes from soldiers*/
    void removeSoldiers(const size_t & number);

    virtual ~Settlement();
};
