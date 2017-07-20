#include "kinematics.h"
#include "motor_control.h"
#include <fstream>
#include <string>
#include "jetsonGPIO.h"
#include <ctime>
	
int main()
{
	jetsonGPIO force_input = gpio166;
	gpioExport(force_input);
	gpioSetDirection(force_input, inputPin);
	
	long elapsed = 0;
	long head_center = 0;
	
	bool hand_up = false;
	bool time_shake = false; //to start time elapsed count
	
	unsigned int force_val = low;
	
    PCA9685 *pca1 = new PCA9685(0x42);
    PCA9685 *pca2 = new PCA9685(0x40);
	int val[20];
    char ud,lr,flag_faces,check_face;
    flag_faces = '0';
    char face_ver = '1';
    char face_ver_shake = '1';
    ifstream file;
    string line;
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
		pca1->setPWM(0,0,map(137,0,180,servoMin,servoMax)); //servo 1
		pca1->setPWM(1,0,map(26,0,180,servoMin,servoMax));  //servo 2
    	pca1->setPWM(2,0,map(105,0,180,servoMin,servoMax));  //servo 3
    	pca1->setPWM(3,0,map(180,0,180,servoMin,servoMax));  //servo 4
    	pca1->setPWM(4,0,map(90,0,180,servoMin,servoMax));  //servo 5
    	pca1->setPWM(5,0,map(60,0,180,servoMin,servoMax));  //thumb
		pca1->setPWM(6,0,map(60,0,180,servoMin,servoMax));  //index
    	pca1->setPWM(7,0,map(60,0,180,servoMin,servoMax));  //middle
    	pca1->setPWM(8,0,map(60,0,180,servoMin,servoMax));  //ring
    	 	
    	//Right hand
    	pca2->setPWM(0,0,map(60,0,180,servoMin,servoMax));  //servo 1
		pca2->setPWM(1,0,map(100,0,180,servoMin,servoMax));  // servo 2
    	pca2->setPWM(2,0,map(105,0,180,servoMin,servoMax));  //servo 3
    	pca2->setPWM(3,0,map(0,0,180,servoMin,servoMax));  //servo 4
    	pca2->setPWM(4,0,map(90,0,180,servoMin,servoMax));  //servo 5
		pca2->setPWM(5,0,map(90,0,180,servoMin,servoMax));  //thumb
		pca2->setPWM(6,0,map(90,0,180,servoMin,servoMax));  //index
    	pca2->setPWM(7,0,map(90,0,180,servoMin,servoMax));  //middle
    	pca2->setPWM(8,0,map(90,0,180,servoMin,servoMax));  //ring  	
    	
    	// head
		pca2->setPWM(9,0,map(100,0,180,servoMin,servoMax));  //sideways
    	pca2->setPWM(10,0,map(100,0,180,servoMin,servoMax));  //up-down
    	
		val[0]=137;
		val[1]=26;
		val[2]=105;
		val[3]=180;
		val[4]=90;	
		val[5]=60;
		val[6]=60;
		val[7]=60;
		val[8]=60;
		
		//val[9]=137;
		//val[10]=35;
		//val[11]=105;
		//val[12]=180;
		//val[13]=90;	
		//val[14]=90;
		//val[15]=90;
		//val[16]=90;
		//val[17]=90;
		
		val[9]=60;
		val[10]=100;
		val[11]=105;
		val[12]=0;
		val[13]=90;	
		val[14]=90;
		val[15]=90;
		val[16]=90;
		val[17]=90;
		
		val[18]=100;
		val[19]=100;
		
		//for convenience : 137 26 105 180 90 120 120 120 120 53 150 105 0 90 120 120 120 120 90 90			
		//while((pca1->error >= 0 || pca1->error >= 0)  && getkey() != 27)
		while(pca2->error>=0 && getkey() !=27)
		{   
			file.open("comms.txt");
			
			head_center++;
			
			cout << "head center elapsed "<<head_center<<endl;
			
			if(head_center>=1000)
			{
				head_center = 0;
				val[18] = 100;
				val[19] = 100;
				rotate_all(val, pca1, pca2);
			}

			
				if(file.is_open())
				{
					getline(file,line);
					check_face=line[0];
					getline(file,line);
					lr=line[0];
					getline(file,line);
					ud=line[0];
					getline(file,line);
					flag_faces=line[0];
					getline(file, line);
					face_ver = line[0];
				}
				cout<<lr<<" "<<ud<<" "<<flag_faces<<" "<<face_ver<<endl;
				file.close();
				
				if(face_ver == face_ver_shake)
				{
					if(check_face=='1')
					{
						if(lr=='0')
							val[18]+=2;
						else if(lr=='1')
							val[18]-=2;
						if(ud=='0')
							val[19]-=1;
						else if(ud=='1')
							val[19]+=1;
							

					}
					

				}
				
				if(val[18]<=60 || val[18]>=140)
				{
					val[18] = 100;
					val[19] = 100;
					rotate_all(val, pca1, pca2);
				}
				
						if(face_ver_shake=='1')
						{
							face_ver_shake = '0';
						}
						else if(face_ver_shake=='0')
						{
							face_ver_shake = '1';
						}
					
					
					if(flag_faces=='1' && !hand_up)
					{
						val[12]=80;
						hand_up = true;
					}
					else
					{

					}
					


					
				//for(int i=0;i<30;i++)
				//{
					//val[18]+=i;
					//rotate_all(val, pca1, pca2);
				//}

					
				rotate_all(val,pca1,pca2);	
				
				if(hand_up)
				{
					time_shake = true;
					elapsed++;
					
					gpioGetValue(force_input, &force_val);
					if(force_val==high)
					{
						cout<<"force inside hand up"<<endl;
						usleep(100000);
						val[12] = 70;
						rotate_all(val, pca1, pca2);
						val[12] = 80;
						rotate_all(val, pca1, pca2);
						val[12] = 0;
						rotate_all(val, pca1, pca2);
						hand_up = false;
						force_val = low;
						elapsed = 0;
						val[18] = 100;
						rotate_all(val, pca1, pca2);
						usleep(4000000);
						
						
					}
					//force_val = low;
					//usleep(3500000);
					//val[12] = 0;
					//rotate_all(val, pca1, pca2);
					//hand_up = false;
				}
				
				if(hand_up)
				{
					cout<<"elapsed "<<elapsed << endl;
				}
				
				
				if(hand_up && elapsed>=150)
				{
					hand_up = false;
					val[12] = 0;
					rotate_all(val, pca1, pca2);
					cout << "keeping it down. Bored"<<endl;
					time_shake = false;
					elapsed = 0;
					val[18] = 100;
					rotate_all(val, pca1, pca2);
					usleep(4000000);

				}
				
				gpioGetValue(force_input, &force_val);
				if(force_val==high)
				{
					cout<<"huehue"<<endl;
					force_val = low;
				}

				

				
		}		
	}
	//pca1->closePCA9685();
	pca2->closePCA9685();
}

