#include "Settlement.h"

using namespace std;

Settlement::Settlement(const size_t & initialSoldiers): soldiers(initialSoldiers) {}

void Settlement::addSoldiers(const size_t &number) {
    soldiers += number;
}

void Settlement::removeSoldiers(const size_t &number) {
    soldiers -= number;
}

Settlement::~Settlement() {}