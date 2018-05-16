#define GREEN 0			//Assigned Channel Number 
#define YELLOW 1		//Assigned Channel Number
#define RED 2			//Assigned Channel Number
#define SIZE1 700		//Size of the first cube
#define SIZE2 400		//Size of the second cube
#define PAUSE 700		/***Amount of time it takes 
						for the camera to adapt to the exposure***/

int gPosition[3] = {5,5,5};

void cameraOn(){
    camera_open(LOW_RES);
    msleep(PAUSE); //necessary for the camera to adapt to the exposure
    display_clear();
    camera_update();
    camera_update();
    camera_update();
    printf("Camera Status: On\n");
}

void cameraOff(){
    display_clear(); 
    camera_update();    
    camera_close();
    printf("Camera Status: Off\n");
}

int getFirstPos(){
    	//________________Check for COLOR at FIRST position______________
        if(get_object_count(GREEN) > 0){
            if(get_object_area(GREEN,0) > SIZE1) {
            	printf("Green object detected\n");                
            	printf("Green size: %d\n", get_object_area(GREEN,0)); 
                gPosition[0] = GREEN;
            	return GREEN;
            }
        }
        if(get_object_count(YELLOW) > 0){
            if(get_object_area(YELLOW,0) > SIZE1) {
           	 	printf("Yellow object detected\n");
            	printf("Yellow size: %d\n", get_object_area(YELLOW,0)); 
                gPosition[0] = YELLOW;
            	return YELLOW;
            }
        }
        if(get_object_count(RED) > 0){
            if(get_object_area(RED,0) > SIZE1) {
                printf("Red object detected\n");
            	printf("Red size: %d\n", get_object_area(RED,0)); 
                gPosition[0] = RED;
            	return RED;
            }
        }
        printf("1st Detect: Nothing / Checking again\n");
        camera_update();            
        msleep(100);   
    	return 5;
    printf("1st Check: (%d, %d, %d)\n", gPosition[0],gPosition[1],gPosition[2]);
}
int getSecondPosIfFirstRed(){
       if(get_object_count(GREEN) > 0){
            if(get_object_area(GREEN,0) > SIZE2) {
            	printf("Green object detected\n");                
            	printf("Green size: %d\n", get_object_area(GREEN,0)); 
                gPosition[1] = GREEN;
            	return GREEN;
            }
        }
        if(get_object_count(YELLOW) > 0){
            if(get_object_area(YELLOW,0) > SIZE2) {
           	 	printf("Yellow object detected\n");
            	printf("Yellow size: %d\n", get_object_area(YELLOW,0)); 
                gPosition[1] = YELLOW;
            	return YELLOW;
            }
        }
    return 5;
}
int getSecondPos(){
    	//________________Check for COLOR at SECOND position______________
        if(get_object_count(GREEN) > 0){
            if(get_object_area(GREEN,0) > SIZE2) {
            	printf("Green object detected\n");                
            	printf("Green size: %d\n", get_object_area(GREEN,0)); 
                gPosition[1] = GREEN;
            	return GREEN;
            }
        }
        if(get_object_count(YELLOW) > 0){
            if(get_object_area(YELLOW,0) > SIZE2) {
           	 	printf("Yellow object detected\n");
            	printf("Yellow size: %d\n", get_object_area(YELLOW,0)); 
                gPosition[1] = YELLOW;
            	return YELLOW;
            }
        }
        if(get_object_count(RED) > 0){
            if(get_object_area(RED,0) > SIZE2) {
                printf("Red object detected\n");
            	printf("Red size: %d\n", get_object_area(RED,0)); 
                gPosition[1] = RED;
            	return RED;
            }
        }
        printf("2nd Detect: Nothing / Checking again\n");
        camera_update();            
        msleep(100);   
    	return 5;
    printf("1st Check: (%d, %d, %d)\n", gPosition[0],gPosition[1],gPosition[2]);
}

    //________________Deduce COLOR at THIRD position______________
void getThirdPos(){
	if((gPosition[0]==YELLOW && gPosition[1]==RED) || (gPosition[0]==RED && gPosition[1]==YELLOW)){
		printf("Deduce: Green object\n");
      	gPosition[2] = GREEN;
    }
	else if((gPosition[0]==GREEN && gPosition[1]==RED) || (gPosition[0]==RED && gPosition[1]==GREEN)){
    	printf("Deduce: Yellow object\n");
        gPosition[2] = YELLOW;
    }
	else if ((gPosition[0]==YELLOW && gPosition[1]==GREEN) || (gPosition[0]==GREEN && gPosition[1]==YELLOW)){
        printf("Deduce: Red object\n");
        gPosition[2] = RED;
    }
    printf("Final: (%d, %d, %d)\n", gPosition[0],gPosition[1],gPosition[2]);
	cameraOff();
}

int posYellow(){
    int i = 0;
    while(i < sizeof(gPosition)){
    	if(gPosition[i] == YELLOW){
        	return i+1;
        }
        i++;
    }
	return 5;
}

/*
void oldGetFirstPos(){
    	//________________Check for COLOR at FIRST position______________
        if(get_object_count(RED) > 0){
            if(get_object_area(RED,0) > 50) {
                printf("Red object detected\n");
            	printf("Red size: %d\n", get_object_area(RED,0)); 
            	gPosition[0] = RED;
            }
        }
        if(get_object_count(YELLOW) > 0){
            if(get_object_area(YELLOW,0) > 50) {
           	 	printf("Yellow object detected\n");
            	printf("Yellow size: %d\n", get_object_area(YELLOW,0)); 
            	gPosition[0] = YELLOW;
            }
        }
        if(get_object_count(GREEN) > 0){
            if(get_object_area(GREEN,0) > 50) {
            	printf("Green object detected\n");                
            	printf("Green size: %d\n", get_object_area(GREEN,0)); 
            	gPosition[0] = GREEN;
            }
        }
        if (gPosition[0] == 5) {
            printf("1st Detect: Nothing / Checking again\n");
            camera_update();            
            msleep(100);
            //getFirstPos();
        }       
    printf("1st Check: (%d, %d, %d)\n", gPosition[0],gPosition[1],gPosition[2]);
	}
    	//________________Check for COLOR at SECOND position______________
void getSecondPos(){
    printf("...Getting Second Position...\n");
        if(get_object_count(YELLOW) > 0 && gPosition[0] != YELLOW){
            if(get_object_area(YELLOW,0) > 50) {
                printf("Yellow object detected\n");
            	printf("Yellow size: %d\n", get_object_area(YELLOW,0)); 
            	gPosition[1] = YELLOW;
            }
        }
        if(get_object_count(RED) > 0){
            if(get_object_area(RED,0) > 50) {
            	printf("Red object detected\n");                
            	printf("Red size: %d\n", get_object_area(RED,0)); 
            	gPosition[1] = RED;
            }
        }
        if(get_object_count(GREEN) > 0){
            if(get_object_area(GREEN,0) > 50) {
                printf("Green object detected\n");
            	printf("Green size: %d\n", get_object_area(GREEN,0)); 
            	gPosition[1] = GREEN;
            }
        } 
    	if (gPosition[1] == 5) {
            printf("2nd Detect: Nothing / Checking again\n");
            camera_update();            
            msleep(100);
            getSecondPos();
        }
        printf("2nd Check: (%d, %d, %d)\n", gPosition[0],gPosition[1],gPosition[2]);
}

    	//________________Deduce COLOR at THIRD position______________
	void getThirdPos(){
		if((gPosition[0]==YELLOW && gPosition[1]==RED) || (gPosition[0]==RED && gPosition[1]==YELLOW)){
            printf("Deduce: Green object\n");
        	gPosition[2] = GREEN;
        }
		else if((gPosition[0]==GREEN && gPosition[1]==RED) || (gPosition[0]==RED && gPosition[1]==GREEN)){
            printf("Deduce: Yellow object\n");
        	gPosition[2] = YELLOW;
        }
		else if ((gPosition[0]==YELLOW && gPosition[1]==GREEN) || (gPosition[0]==GREEN && gPosition[1]==YELLOW)){
            printf("Deduce: Red object\n");
        	gPosition[2] = RED;
        }
        printf("Final: (%d, %d, %d)\n", gPosition[0],gPosition[1],gPosition[2]);
    	cameraOff();
}
*/
