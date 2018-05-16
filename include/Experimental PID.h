#define P 0.001

void forwards_pid(double target, double position, int speed)
{
    double current = analog(0);
    double error = target - current;
	double proportional;
    double powerup;
    double powerdown;
    cmpc(LEFTWHEEL);
    
    while(gmpc(LEFTWHEEL) < position)
    {
        current = analog(0);
        error = target - current;
    	proportional = P * error;
        powerup = speed + proportional;
        powerdown = speed - proportional;
        
		mrp(LEFTWHEEL, powerup, 6);
        mrp(RIGHTWHEEL, powerdown, 6);
    }
}