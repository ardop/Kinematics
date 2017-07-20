#include "kinematics.h"
#include <armadillo>
#include "motor_control.h"

using namespace arma;
using namespace std;

int main()
{
	arma_rng::set_seed_random();
	float x,y,z, theta1, theta2, theta3, theta4, theta5;
	mat ze;
	ze << 0.0;
	double error_threshold = 1.5;
	
	int val[12];
	PCA9685 *pca1 = new PCA9685(0x40);
	int err1 = pca1->openPCA9685();
    if (err1 < 0){
        printf("Error: %d", pca1->error);
    } else {
        printf("PCA9685 Device Address: 0x%02X\n",pca1->kI2CAddress);
        pca1->setAllPWM(0,0) ;
        pca1->reset() ;
        pca1->setPWMFrequency(50) ;
        // 27 is the ESC keyOC
        printf("Hit ESC key to exit\n");
        
        //Right hand
		pca1->setPWM(0,0,map(53,0,180,servoMin,servoMax));  //servo 1
		pca1->setPWM(1,0,map(150,0,180,servoMin,servoMax));  // servo 2
    	pca1->setPWM(2,0,map(105,0,180,servoMin,servoMax));  //servo 3
    	pca1->setPWM(3,0,map(0,0,180,servoMin,servoMax));  //servo 4
    	pca1->setPWM(4,0,map(90,0,180,servoMin,servoMax));  //servo 5
    	//Left hand
		pca1->setPWM(5,0,map(137,0,180,servoMin,servoMax)); //servo 1
		pca1->setPWM(6,0,map(26,0,180,servoMin,servoMax));  //servo 2
    	pca1->setPWM(7,0,map(105,0,180,servoMin,servoMax));  //servo 3
    	pca1->setPWM(8,0,map(180,0,180,servoMin,servoMax));  //servo 4
    	pca1->setPWM(9,0,map(90,0,180,servoMin,servoMax));  //servo 5
		//Head
		pca1->setPWM(10,0,map(90,0,180,servoMin,servoMax));  //up-down
		pca1->setPWM(11,0,map(90,0,180,servoMin,servoMax));  //sideways
	cout<<"Enter x,y,z values: ";
	cin>>x>>y>>z;

	mat target;
	target<<x<<y<<z;

	mat ans;
	ans = calculate_ik_jacobian(target);
	ans.print("Calculated Theta");
	cout << endl << endl;
	val[0] = 53;
	val[1] = 150;
	val[2] = 105;
	val[3] = 0;
	val[4] = 90;
	val[5] = kin_map_left(1, ans(0));
	val[6] = kin_map_left(2, ans(1));
	val[7] = kin_map_left(3, ans(2));
	val[8] = kin_map_left(4, ans(3));
	val[9] = 90;
	val[10] = 90;
	val[11] = 90;
	rotate(val,pca1);
	pca1->closePCA9685();
return 0;
}
}

