#include "stdafx.h"
#include "GenericPlayer.h"
#include <string>

GenericPlayer::GenericPlayer(const std::string& name, std::string& token) : pName(name), pToken(token) {}
GenericPlayer::~GenericPlayer() {}