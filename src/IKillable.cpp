#include "IKillable.hpp"

IKillable::IKillable() : _isAlive(true) {}
IKillable::IKillable(bool isAlive) : _isAlive(isAlive) {}
IKillable::~IKillable() {}

bool IKillable::isAlive() { return this->_isAlive; }
void IKillable::revive() { this->_isAlive = true; }
void IKillable::kill() { this->_isAlive = false; }
