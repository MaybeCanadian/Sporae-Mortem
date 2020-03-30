#pragma once
#include "engine.h"
#include "Label.h"
class Label;
class LabelManager
{
private:
	LabelManager();
	std::vector<Label*> labels;
public:
	static LabelManager& getInstance();
	~LabelManager();
	bool initManager();
	void clean();
	void render();
	void update();
};

