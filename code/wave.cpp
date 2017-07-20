#include "kinematics.h"
#include "motor_control.h"


int main()
{
    PCA9685 *pca1 = new PCA9685(0x40);
    PCA9685 *pca2 = new PCA9685(0x42);
    int err1 = pca1->openPCA9685();
    int err2 = pca2->openPCA9685();
    if (err1 < 0 || err2 <0){
        printf("Error: %d", pca1->error);
    } else {
        printf("PCA9685 Device Address: 0x%02X\n",pca1->kI2CAddress);
        pca1->setAllPWM(0,0) ;
        pca1->reset() ;
        pca1->setPWMFrequency(50) ;
        printf("PCA9685 Device Address: 0x%02X\n",pca2->kI2CAddress);
        pca2->setAllPWM(0,0) ;
        pca2->reset() ;
        pca2->setPWMFrequency(50) ;
        // 27 is the ESC keyOC
        printf("Hit ESC key to exit\n");
        
        //Left hand
		pca1->setPWM(5,0,map(137,0,180,servoMin,servoMax)); //servo 1
		pca1->setPWM(6,0,map(26,0,180,servoMin,servoMax));  //servo 2
    	pca1->setPWM(7,0,map(105,0,180,servoMin,servoMax));  //servo 3
    	pca1->setPWM(8,0,map(180,0,180,servoMin,servoMax));  //servo 4
    	pca1->setPWM(9,0,map(90,0,180,servoMin,servoMax));  //servo 5
    	pca1->setPWM(0,0,map(53,0,180,servoMin,servoMax));  //thumb (right values)
		pca1->setPWM(1,0,map(150,0,180,servoMin,servoMax));  //index
    	pca1->setPWM(2,0,map(105,0,180,servoMin,servoMax));  //middle
    	pca1->setPWM(3,0,map(0,0,180,servoMin,servoMax));  //ring
    	pca1->setPWM(4,0,map(90,0,180,servoMin,servoMax));  
    	 	
    	//Right hand
    	//pca2->setPWM(0,0,map(53,0,180,servoMin,servoMax));  //servo 1
		//pca2->setPWM(1,0,map(150,0,180,servoMin,servoMax));  // servo 2
    	//pca2->setPWM(2,0,map(105,0,180,servoMin,servoMax));  //servo 3
    	//pca2->setPWM(3,0,map(0,0,180,servoMin,servoMax));  //servo 4
    	//pca2->setPWM(4,0,map(90,0,180,servoMin,servoMax));  //servo 5
		//pca2->setPWM(5,0,map(120,0,180,servoMin,servoMax));  //thumb
		//pca2->setPWM(6,0,map(120,0,180,servoMin,servoMax));  //index
    	//pca2->setPWM(7,0,map(120,0,180,servoMin,servoMax));  //middle
    	//pca2->setPWM(8,0,map(120,0,180,servoMin,servoMax));  //ring  	
    	
    	// head
		pca1->setPWM(10,0,map(90,0,180,servoMin,servoMax));  //up-down
    	pca1->setPWM(11,0,map(90,0,180,servoMin,servoMax));  //sideways
		//for convenience : 137 26 105 180 180 120 120 120 120 53 150 105 90 90 120 120 120 120 90 90
		//53 150 105 90 90 137 26 105 180 90 90 90 


		char hand_id;
		int val[5];	
		while((pca1->error >= 0 || pca1->error >= 0)  && getkey() != 27)
		{    
		//Temporarily not used:
									//////cout<<"Enter hand l/r ";
									//////cin>>hand_id;
									//////if(hand_id=='l')
									//////{
										//////cout<<"Enter motor values in order ";
										//////cin>>val[0]>>val[1]>>val[2]>>val[3]>>val[4]>>val[5]>>val[6]>>val[7]>>val[8];
										//////rotate(val,pca1);
									//////}
									//////else if(hand_id=='r')
									//////{
										//////cout<<"Enter motor values in order ";
										//////cin>>val[0]>>val[1]>>val[2]>>val[3]>>val[4]>>val[5]>>val[6]>>val[7]>>val[8];
										//////rotate(val,pca2);
									//////}
			val[0]=53;
			val[1]=150;
			val[2]=105;
			val[3]=0;
			val[4]=90;
			val[5]=137;
			val[6]=86;
			val[7]=15;
			val[8]=90;
			val[9]=90;
			val[10]=90;
			val[11]=90;
			for(int i=0;i<2;i++)
			{
			rotate(val,pca1);
			usleep(1000);
			val[8]=120;
			rotate(val,pca1);
			usleep(1000);
			val[8]=90;
			rotate(val,pca1);
		}
		val[6]=26;
		val[7]=105;
		val[8]=180;
		rotate(val,pca1);
		sleep(5);
		}		
	}
	pca1->closePCA9685();
	pca2->closePCA9685();
}
