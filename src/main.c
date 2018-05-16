#include <kipr/botball.h>
#include <functions.h>
#include <camera.h>
//#include <movement.h>

/*	
	turn
	1) drive towards center
    cameraOn
    check first zone
    check second zone
    deduce 3rd zone

    pick up cubes
    drive back 
    based on location of yellow zone
    run either function 1, 2, or 3
*/

void checkingCamera() {
    cameraOn();
    display_clear();
    camera_update();
    camera_update();
    msleep(1200);
    int first = 5;
    do{
        first = getFirstPos();
        camera_update();
    }while(first == 5);

    cameraOff();
    //msleep(500); //when the pause in main is 50
    cameraOn();
    display_clear();
    camera_update();
    camera_update();
    camera_update();
    int second = 5;
    if(gPosition[0] == RED){
        do{
            second = getSecondPosIfFirstRed();
            camera_update();
        }while(second == 5);
    }else{
        do{
            second = getSecondPos();
            camera_update();
        }while(second == 5);
    }


    getThirdPos();
    int posY = posYellow();
    printf("Position of Yellow: Zone %d\n", posY);
    printf("Thread ends\n");

}

void hypotenuse(){
    set_servo_position(0, 1000);

    thread id1;
    id1 = thread_create(checkingCamera);
    thread_start(id1);

    printf("Starting camera...");
    msleep(500); // for camera to focus
    msleep(PAUSE);
    distance(64, 1500); //drives towards center
    msleep(PAUSE);
    distance(58, 1500);
    getCubes();
    //msleep(250);
    //dis(49, 800);
    thread_destroy(id1);
}



int main()                                   //1120
{
	//checkingCamera();
//    wait_for_light(2);
//    shut_down_in(119);
    enable_servo(0);
    set_servo_position(0, 1000);
    //backwards(100, 1000);
   // go(800, 1000);
   // placeCubes();
   // pidbacksensor(1200, 2000, 800);
    //back_left(90, 200);
    //back_right(90,200);
    //getcube();
    //msleep(200);
  //  pidbacksensor(1700, 2000, 1000);
    //back2Start();
    //pid(1700, 2000, 1000);
    //msleep(2000);
    // pid(1700, 5000, 1000);

    //pid(1700, 3000, 1200);

    /*
    hypotenuse();	//checks location of cubes as bot drives towards intersection
    msleep(1000);
    int posY = posYellow();
    if(posY == 1){
        printf("Yellow is in Zone 1\n");
        block1();
    }
    else if (posY == 2){
        printf("Yellow is in Zone 2\n");
        ao();
        msleep(40000);
        block2();
    }
    else{
        printf("Yellow is in Zone 3\n");
        ao();
        msleep(40000);
        block3(); 
    }  
    */
    
    while(analog(4) < 3000)								//line follow back until senses starting box corner
    {
        backwards_pid_back_sensor(1200, 100, 1200);
    }
    printf("WE HAVE SENSED BLACK STARTING BOX\n");
    backwards_pid_back_sensor(1200, 2000, 1500);        //line follow back to pom farm push pom farm pop
    printf("we pushed pom pom farm pom pom\n");
    while(analog(4) > 3000)
    {
    	forwards_pid(1200, 10, 1200);					//line follow forward to rest position
        printf("%i\n", analog(4));
    }
    bmd(LEFTWHEEL);
    bmd(RIGHTWHEEL);
    return 0;


}