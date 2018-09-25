#pragma once

class context
{

	struct GLFWwindow * window;


public:
	bool init(int w, int h, const char * title);
	void tick();
	void term();
	void clear();

	bool shouldClose() const;
};