#include "kinematics.h"
#include "motor_control.h"
int main()
{
	cout<<"Enter the Euler type, 3 Euler angle values and the 3 coordinate values:"<<endl;
	string type;
	double angle1, angle2, angle3,theta1,theta2,theta3,theta4,theta5;

	
	PCA9685 *pca9685 = new PCA9685() ;
    int err = pca9685->openPCA9685();
    int reg[5],val[5];
	double x, y, z;
    if (err < 0){
	printf("Error: %d", pca9685->error);
	} 
	else 
	{
		printf("PCA9685 Device Address: 0x%02X\n",pca9685->kI2CAddress) ;
		pca9685->setAllPWM(0,0) ;
		pca9685->reset() ;
		pca9685->setPWMFrequency(50) ;
		// 27 is the ESC keyOC
		printf("Hit ESC key to exit\n");
		pca9685->setPWM(0,0,map(137,0,180,servoMin,servoMax));
		pca9685->setPWM(1,0,map(26,0,180,servoMin,servoMax));
		pca9685->setPWM(2,0,map(105,0,180,servoMin,servoMax));
		pca9685->setPWM(3,0,map(180,0,180,servoMin,servoMax));
		pca9685->setPWM(4,0,map(90,0,180,servoMin,servoMax));
	}
	getline(cin, type);
	cin>>angle1>>angle2>>angle3>>x>>y>>z;
	
	// Assuming that user input is in degrees, we conver to radians
	angle1 = deg2rad(angle1);
	angle2 = deg2rad(angle2);
	angle3 = deg2rad(angle3);
	
	//cout << type << " " << angle1 << " " << angle2 << " " << angle3 << " " << x << " " << y << " " << z<< endl;
	
	mat euler_angles;
	euler_angles<<angle1<<angle2<<angle3;
	
	mat coord;
	coord<<x<<y<<z;
	
	mat t = find_transformation_matrix(type, euler_angles, coord);
	//px, py, pz for the Transformation matrix
	mat points_t = p_map(t);

	
	mat p = find_all_perm_new_theta(t);
	mat perm_theta;
	// Rearranging to account for the perm theta interchange
	perm_theta=join_horiz(p.col(0),p.col(1));
	perm_theta=join_horiz(perm_theta,p.col(2));
	perm_theta=join_horiz(perm_theta,p.col(4));
	perm_theta=join_horiz(perm_theta,p.col(3));
	
	mat ik_angles;
	
	bool solution_exists = false;
	
	for(int j=0;j<perm_theta.n_rows;j++)
	{
		mat fk;
		fk=fk_manual(perm_theta.row(j));
		
		//px, py, pz for the current permutation fk matrix
		mat points_fk = p_map(fk);

		if(approx_equal(fk,t,"absdiff",0.002)&&validate_theta_left(perm_theta.row(j)))
		{
			cout<<"------------------------"<<endl;
			cout<<"Orientation and position: "<<endl<<j<<endl;
			cout<<"------------------------"<<endl;
			
			solution_exists = true;
			ik_angles = perm_theta.row(j);
		}
		
		else if(approx_equal(points_t, points_fk, "absdiff", 5.0)&&validate_theta_left(perm_theta.row(j)))
		{
			cout<<"------------------------"<<endl;
			cout<<"Position only: "<<endl<<j<<endl;
			cout<<"------------------------"<<endl;
			
			solution_exists = true;
			ik_angles = perm_theta.row(j);
		}
			
		
		//if(validate_theta_left(perm_theta.row(j)))
		//{
			//cout<<"-------------------------"<< endl<<j<<endl<<"---------------------------------"<<endl;
			//perm_theta.row(j).print("Solution");
			//ik_angles = perm_theta.row(j);

		//}
		
	}
	
	if(solution_exists)
	{
	
		theta1=kin_map_left(0,ik_angles(0));
		theta2=kin_map_left(1,ik_angles(1));
		theta3=kin_map_left(2,ik_angles(2));
		theta4=kin_map_left(3,ik_angles(3));
		theta5=kin_map_left(4,ik_angles(4));
		
		for(int i=0;i<5;i++)
		{	
		reg[i]=regread(i,pca9685);
		}
		val[0]=theta1;
		val[1]=theta2;
		val[2]=theta3;
		val[3]=theta4;
		val[4]=theta5;
		
		if (err < 0){
		printf("Error: %d", pca9685->error);
		} 
		else 
		{
			rotate_multi(val,pca9685);	
		}
		
	    pca9685->closePCA9685();
	}
	else
	{
		cout<<"No solution"<<endl;
	}
    
}
