#pragma once

struct Mouse_info {
	double  rawX, rawY;
	double localX, localY;
	double Scroll;
	bool buttons[3];

};
static Mouse_info MOUSE_INFO_INIT = {
0.00, //RawX 
0.00, //RAW Y
0.00, // LocalX
0.00, // Local Y
0.00, // Scroll
{0,0,0} // Button Values
};

