#pragma once
#include "MapStates.h"
#include "MenuState.h"

class GameState {

public:
    GameState();
    MapStates fieldState = MapStates::PlayerOne;
    int cancelState = 0;
};
