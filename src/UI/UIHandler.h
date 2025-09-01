#pragma once

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "Clickable.h"

using namespace std;

class UIHandler {
public:
    UIHandler() = default;
    void handleUI();
    virtual ~UIHandler() = default;
};