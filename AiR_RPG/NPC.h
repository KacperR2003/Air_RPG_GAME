#pragma once
#include <string>
class NPC
{
private:
	std::string name;
	std::string dialog;
public:
	void talk();
	bool take_mission();
};

