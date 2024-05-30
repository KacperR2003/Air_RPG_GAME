#pragma once
#include <string>
class Task
{
private:
	std::string name;
	std::string description;
	std::string reward;
public:
	void talk();
	bool take_mission();
	void show_task();
};

