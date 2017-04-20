#include "stdafx.h"
#include "GenericPlayer.h"
#include <string>

GenericPlayer::GenericPlayer(const std::string& name, std::string token, int value) : pName(name), pToken(token), value(value)  {}
GenericPlayer::~GenericPlayer() {}