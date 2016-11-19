#include <iostream>
#include <armadillo>
#include <math.h>
#include <stdio.h>
#include <string>

//Initializing pi, link lengths and constraints
#define PI 3.14159265358979323846
#define l1  14.2
#define l2  1.8
#define l3  14.5
#define l5  29.5
#define epsilon1 0.5235987756
#define epsilon2 0.1745329252
#define alpha2 0.5235987756

#define t1bl 0.0 
#define t1al -(PI-0.523598)
#define t2bl 1.5707+0.174532
#define t2al -0.523598 
#define t3bl PI
#define t3al 0.0
#define t4bl 0.0
#define t4al -1.5707


using namespace arma;
using namespace std;

mat t_map(const mat& t)
{
	mat ans;
	// return n, o, a and p values
	ans<<t(0, 0)<<t(1, 0)<<t(2, 0)<<t(0, 1)<<t(1, 1)<<t(2, 1)<<t(0, 2)<<t(1, 2)<<t(2, 2)<<t(0, 3)<<t(1, 3)<<t(2, 3);

	return ans;
}

mat p_map(const mat& t)
{
	mat ans;
	// Returning coordinate values from the Transformation matrix
	ans<<t(0, 3)<<t(1, 3)<<t(2, 3);
	return ans;
}

mat round_mat(const mat& m, int precision )
{
    const int adjustment = pow(10,precision);
    double value;
	mat newmat;	
	for(int i=0;i<m.n_rows;i++)
        {
        for(int j=0;j<m.n_cols;j++)
            {
            value=m(i,j);        
            newmat = floor( value*(adjustment) + 0.5 )/adjustment;
			}
        }
    return newmat;
}

// Functions to convert between radians and degrees
double deg2rad(double deg)
{
	double rad;
	rad = (deg*PI)/180.0;
	return rad;
}

double rad2deg(double rad)
{
	double deg;
	deg = (rad*180.0)/PI;
	return deg;
}



//mat find_theta1(const mat& t)
//{
	//mat t_m=t_map(t);
	//mat ans;
	//double nx,ny,nz,ox,oy,oz,ax,ay,az,px,py,pz,num,den;
	//nx=t_m(0);
	//ny=t_m(1);
	//nz=t_m(2);
	//ox=t_m(3);
	//oy=t_m(4);
	//oz=t_m(5);
	//ax=t_m(6);
	//ay=t_m(7);
	//az=t_m(8);
	//px=t_m(9);
	//py=t_m(10);
	//pz=t_m(11);

	//num=-py + l4*oy;
	//den=px - l4*ox;
	//double phi= atan2(num,den);
	//ans<<-phi + atan2(-l1,sqrt(num*num + den*den - l1*l1))<<-phi + atan2(-l1,-sqrt(num*num + den*den - l1*l1));
	//return ans;
//}

//mat find_theta2(const mat& t,double theta1)
//{
	//mat t_m=t_map(t);
	//mat ans;
	//double nx,ny,nz,ox,oy,oz,ax,ay,az,px,py,pz,num,den;
	//nx=t_m(0);
	//ny=t_m(1);
	//nz=t_m(2);
	//ox=t_m(3);
	//oy=t_m(4);
	//oz=t_m(5);
	//ax=t_m(6);
	//ay=t_m(7);
	//az=t_m(8);
	//px=t_m(9);
	//py=t_m(10);
	//pz=t_m(11);
	//num = cos(theta1)*(tan(theta1)*(py - l4*oy) + px - l4*ox);
	//den = l4*oz - pz + l0;
    
    //ans<<atan2(num,den)<<atan2(-num,-den);
	//return ans;
//}

//mat find_theta3(const mat& t,double theta1,double theta2)
//{

	//mat t_m=t_map(t);
	//mat ans;
	//double nx,ny,nz,ox,oy,oz,ax,ay,az,px,py,pz,num,den;
	//nx=t_m(0);
	//ny=t_m(1);
	//nz=t_m(2);
	//ox=t_m(3);
	//oy=t_m(4);
	//oz=t_m(5);
	//ax=t_m(6);
	//ay=t_m(7);
	//az=t_m(8);
	//px=t_m(9);
	//py=t_m(10);
	//pz=t_m(11);

    //num = ox*sin(theta1) - oy*cos(theta1);
    //den = ox*cos(theta1)*cos(theta2) + oy*sin(theta1)*cos(theta2) + oz*sin(theta2);

    //ans<<atan2(num, den)<<atan2(-num, -den);
	//return ans;
//}

//mat find_theta4(const mat& t,double theta1,double theta2,double theta3)
//{
	//mat t_m=t_map(t);
	//mat ans;
	//double nx,ny,nz,ox,oy,oz,ax,ay,az,px,py,pz,num,den;
	//nx=t_m(0);
	//ny=t_m(1);
	//nz=t_m(2);
	//ox=t_m(3);
	//oy=t_m(4);
	//oz=t_m(5);
	//ax=t_m(6);
	//ay=t_m(7);
	//az=t_m(8);
	//px=t_m(9);
	//py=t_m(10);
	//pz=t_m(11);

    //num = oy*cos(theta1) - ox*sin(theta1);
    //den = sin(theta3)*(ox*cos(theta1)*sin(theta2) + oy*sin(theta1)*sin(theta2) - oz*cos(theta2));
    
    //ans<<atan2(num, den)<<atan2(-num, -den);

//return ans;
//}

//mat find_theta5(const mat& t,double theta1,double theta2)
//{
	//mat t_m=t_map(t);
	//mat ans;
	//double nx,ny,nz,ox,oy,oz,ax,ay,az,px,py,pz,num,den;
	//nx=t_m(0);
	//ny=t_m(1);
	//nz=t_m(2);
	//ox=t_m(3);
	//oy=t_m(4);
	//oz=t_m(5);
	//ax=t_m(6);
	//ay=t_m(7);
	//az=t_m(8);
	//px=t_m(9);
	//py=t_m(10);
	//pz=t_m(11);

    //num = ax*cos(theta1)*sin(theta2) + ay*sin(theta1)*sin(theta2) - az*cos(theta2);
    //den = nx*cos(theta1)*sin(theta2) + ny*sin(theta1)*sin(theta2) - nz*cos(theta2);
    
    //ans<<atan2(num, den)<<atan2(-num, -den);
	//return ans;
//}

//mat find_all_perm_new_theta(const mat& t)
//{
	//mat perm_theta;
	//mat theta1 = find_theta1(t);

	//mat theta2a = find_theta2(t, theta1(0));
	//mat theta2b = find_theta2(t, theta1(1));


	//mat theta3a = find_theta3(t, theta1(0), theta2a(0));
	//mat theta3b = find_theta3(t, theta1(0), theta2a(1));
	//mat theta3c = find_theta3(t, theta1(1), theta2b(0));
	//mat theta3d = find_theta3(t, theta1(1), theta2b(1));

	///*
	//mat theta4a1 = find_theta4(t, theta1(0), theta2a(0), theta3a(0));
	//mat theta4a2 = find_theta4(t, theta1(0), theta2a(0), theta3a(1));
	//mat theta4b1 = find_theta4(t, theta1(0), theta2a(1), theta3b(0));
	//mat theta4b2 = find_theta4(t, theta1(0), theta2a(1), theta3b(1));
	//mat theta4c1 = find_theta4(t, theta1(1), theta2b(0), theta3c(0));
	//mat theta4c2 = find_theta4(t, theta1(1), theta2b(0), theta3c(1));
	//mat theta4d1 = find_theta4(t, theta1(1), theta2b(1), theta3d(0));
	//mat theta4d2 = find_theta4(t, theta1(1), theta2b(1), theta3d(1));
	//*/
	//mat theta4a1 = find_theta4(t, theta1(0), theta2a(0), theta3a(0));
	//mat theta4b1 = find_theta4(t, theta1(0), theta2a(0), theta3a(1));
	//mat theta4c1 = find_theta4(t, theta1(0), theta2a(1), theta3b(0));
	//mat theta4d1 = find_theta4(t, theta1(0), theta2a(1), theta3b(1));
	//mat theta4a2 = find_theta4(t, theta1(1), theta2b(0), theta3c(0));
	//mat theta4b2 = find_theta4(t, theta1(1), theta2b(0), theta3c(1));
	//mat theta4c2 = find_theta4(t, theta1(1), theta2b(1), theta3d(0));
	//mat theta4d2 = find_theta4(t, theta1(1), theta2b(1), theta3d(1));


	//mat theta5a = find_theta5(t, theta1(0), theta2a(0));
	//mat theta5b = find_theta5(t, theta1(0), theta2a(1));
	//mat theta5c = find_theta5(t, theta1(1), theta2b(0));
	//mat theta5d = find_theta5(t, theta1(1), theta2b(1));

	////theta1.print("theta1");
	////theta2a.print("theta2a");
	////theta2b.print("theta2b");
	////theta3a.print("theta3a");
	////theta3b.print("theta3b");
	////theta3c.print("theta3c");
	////theta3d.print("theta3d");
	////theta4a1.print("theta4a1");
	////theta4a2.print("theta4a2");
	////theta4b1.print("theta4b1");
	////theta4b2.print("theta4b2");
	////theta4c1.print("theta4c1");
	////theta4c2.print("theta4c2");
	////theta4d1.print("theta4d1");
	////theta4d2.print("theta4d2");
	////theta5a.print("theta5a");
	////theta5b.print("theta5b");
	////theta5c.print("theta5c");
	////theta5d.print("theta5d");

		//perm_theta    <<theta1(0)<<theta2a(0)<<theta3a(0)<<theta5a(0)<<theta4a1(0)<<endr
					  //<<theta1(0)<<theta2a(0) <<theta3a(0) <<theta5a(0) <<theta4a1(1)<<endr
					  //<<theta1(0)<<theta2a(0) <<theta3a(0) <<theta5a(1) <<theta4b1(0)<<endr
					  //<<theta1(0)<<theta2a(0) <<theta3a(0) <<theta5a(1) <<theta4b1(1)<<endr
					  //<<theta1(0)<<theta2a(0) <<theta3a(1) <<theta5a(0) <<theta4a1(0)<<endr
					  //<<theta1(0) <<theta2a(0) <<theta3a(1) <<theta5a(0) <<theta4a1(1)<<endr
					  //<<theta1(0) <<theta2a(0) <<theta3a(1) <<theta5a(1) <<theta4b1(0)<<endr
					  //<<theta1(0) <<theta2a(0) <<theta3a(1) <<theta5a(1) <<theta4b1(1)<<endr
					  
					  //<<theta1(0) <<theta2a(1) <<theta3b(0) <<theta5b(0) <<theta4c1(0)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(0) <<theta5b(0) <<theta4c1(1)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(0) <<theta5b(1) <<theta4d1(0)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(0) <<theta5b(1) <<theta4d1(1)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(1) <<theta5b(0) <<theta4c1(0)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(1) <<theta5b(0) <<theta4c1(1)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(1) <<theta5b(1) <<theta4d1(0)<<endr
					  //<<theta1(0) <<theta2a(1) <<theta3b(1) <<theta5b(1) <<theta4d1(1)<<endr
					  
					  //<<theta1(1) <<theta2b(0) <<theta3c(0) <<theta5c(0) <<theta4a2(0)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(0) <<theta5c(0) <<theta4a2(1)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(0) <<theta5c(1) <<theta4b2(0)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(0) <<theta5c(1) <<theta4b2(1)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(1) <<theta5c(0) <<theta4a2(0)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(1) <<theta5c(0) <<theta4a2(1)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(1) <<theta5c(1) <<theta4b2(0)<<endr
					  //<<theta1(1) <<theta2b(0) <<theta3c(1) <<theta5c(1) <<theta4b2(1)<<endr
					 
					  //<<theta1(1) <<theta2b(1) <<theta3d(0) <<theta5d(0) <<theta4c2(0)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(0) <<theta5d(0) <<theta4c2(1)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(0) <<theta5d(1) <<theta4d2(0)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(0) <<theta5d(1) <<theta4d2(1)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(1) <<theta5d(0) <<theta4c2(0)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(1) <<theta5d(0) <<theta4c2(1)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(1) <<theta5d(1) <<theta4d2(0)<<endr
					  //<<theta1(1) <<theta2b(1) <<theta3d(1) <<theta5d(1) <<theta4d2(1)<<endr;
//return perm_theta;
//}

//mat fk_manual(const mat& kin_angles_test)
//{
	//double theta1 = kin_angles_test(0);
	//double theta2 = kin_angles_test(1);
	//double theta3 = kin_angles_test(2);
	//double theta4 = kin_angles_test(3);
	//double theta5 = kin_angles_test(4);

	//mat a,b,c,d,e,fkmatp;
	//a<<cos(theta1)<< 0<< sin(theta1)<< 0<<endr<< sin(theta1)<<  0<< -cos(theta1)<< 0<<endr<< 0<< 1<< 0<< l1<<endr<< 0<< 0<< 0<< 1;
	//b<<cos(theta2)<< 0<< sin(theta2)<< 0<<endr<< sin(theta2)<<  0<< -cos(theta2)<< 0<<endr<< 0<< 1<< 0<< -l2<<endr<< 0<< 0<< 0<< 1;
	//c<<cos(theta3)<< 0<< sin(theta3)<< 0<<endr<< sin(theta3)<<  0<< -cos(theta3)<< 0<<endr<< 0<< 1<< 0<< -l3<<endr<< 0<< 0<< 0<< 1;
	//d <<cos(theta4)<< 0<< sin(theta4)<< 0<<endr<< sin(theta4)<<  0<< -cos(theta4)<< 0<<endr<< 0<< 1<< 0<< 0<<endr<< 0<< 0<< 0<< 1;
	//e <<cos(theta5)<< 0<< sin(theta5)<< 0<<endr<< sin(theta5)<<  0<< -cos(theta5)<< 0<<endr<< 0<< 1<< 0<< l5<<endr<< 0<< 0<< 0<< 1;
	//fkmatp = a*b*c*d*e;
	//return fkmatp;
//}

//mat rotation_matrix(char axis, double angle)
//{
	//double co = cos(angle);
	//double si = sin(angle);
	
	//mat q;
	
	//// Getting rotations matrices for rotation about a specific axis
	
	//if((axis=='z')||(axis=='Z'))
	//{
		//q<<co<<-si<<0<<endr<<si<<co<<0<<endr<<0<<0<<1;
	//}
	//else if((axis=='Y')||(axis=='y'))
	//{
		//q<<co<<0<<si<<endr<<0<<1<<0<<endr<<-si<<0<<co;
	//}
	//else if((axis=='X')||(axis=='x'))
	//{
		//q<<1<<0<<0<<endr<<0<<co<<-si<<endr<<0<<si<<co;
	//}
	
	//return q;
//}

//mat find_transformation_matrix(string s, const mat& angles, const mat& coordinates)
//{
	//mat grb;
	//grb.eye(3, 3);
	
	////Calculating the final orientation matrix by calculating the individual rotation matrix using Euler angles
	
	//char ch;
	//for(int i=0;i<3;i++)
	//{
		//ch = s.at(i);
		//if(islower(ch))
		//{
			////Local rotation. Post multiply rotation matrix
			//grb = grb*rotation_matrix(ch, angles(i));
		//}
		//else
		//{
			////Global rotation. Pre multiply rotation matrix
			//grb = rotation_matrix(ch, angles(i))*grb;
		//}
	//}
	
	////mat coord;
	////coord<<x<<endr<<y<<endr<<z;
	
	//mat coord;
	//coord = coordinates.t();
	
	//mat tmp = join_rows(grb, coord);
	//mat tmp2;
	//tmp2<<0<<0<<0<<1;
	//mat t = join_cols(tmp, tmp2);
	
	//return t;
	
	
//}

bool validate_theta_left(const mat& angles)
{
	double theta1 = angles(0);
	double theta2 = angles(1);
	double theta3 = angles(2);
	double theta4 = angles(3);
	double theta5 = angles(4);
	
	int flag = 0;
	
	if((theta1<=epsilon1) && (theta1>=-(PI-epsilon1)))
		flag++;

	if((theta2<=PI/2+epsilon2) && (theta2>=-alpha2))
		flag++;

	if((theta3<=PI) && (theta3>=0.0))
		flag++;

	if((theta4<=0) && (theta4>=-PI/2))
		flag++;

	if((theta5<=PI/2) && (theta5>=-PI/2))
		flag++;
		
	if(flag==5)
		return true;
	else
		return false;
		
}

double dist(const mat &v1,const mat &v2)
{
	double d=0;
	for(int i=0;i<v1.n_cols;i++)
	{
		d=d+pow((v1(i)-v2(i)),2);
	}
	d=sqrt(d);
	return d;
}

//double norm(const mat &v)
//{
	//double n=0;
	//for(i=0;i<v.n_cols;i++)
	//{
		//d=d+pow(v(i),2);
	//}
	//return sqrt(d);
//}

mat calculate_ccd(const mat& theta_default, const mat& t)
{
	mat theta;
	theta<<theta_default(0)<<theta_default(1)<<theta_default(2)<<theta_default(3)<<0<<0<<0;

	double theta1, theta2, theta3, theta4, theta5;
	mat fk,epos,a,b,c,d,e,jpos;
	double err,erra,errb;
	
	for(int i=0;i<10;i++)
	{
		theta1 = theta(0);
		theta2 = theta(1);
		theta3 = theta(2);
		theta4 = theta(3);
		theta5 = theta(4);
		
		a<<cos(theta1)<< 0<< sin(theta1)<< 0<<endr<< sin(theta1)<<  0<< -cos(theta1)<< 0<<endr<< 0<< 1<< 0<< l1<<endr<< 0<< 0<< 0<< 1;
		b<<cos(theta2)<< 0<< sin(theta2)<< 0<<endr<< sin(theta2)<<  0<< -cos(theta2)<< 0<<endr<< 0<< 1<< 0<< -l2<<endr<< 0<< 0<< 0<< 1;
		c<<cos(theta3)<< 0<< sin(theta3)<< 0<<endr<< sin(theta3)<<  0<< -cos(theta3)<< 0<<endr<< 0<< 1<< 0<< -l3<<endr<< 0<< 0<< 0<< 1;
		d <<cos(theta4)<< 0<< sin(theta4)<< 0<<endr<< sin(theta4)<<  0<< -cos(theta4)<< 0<<endr<< 0<< 1<< 0<< 0<<endr<< 0<< 0<< 0<< 1;
		e <<cos(theta5)<< 0<< sin(theta5)<< 0<<endr<< sin(theta5)<<  0<< -cos(theta5)<< 0<<endr<< 0<< 1<< 0<< l5<<endr<< 0<< 0<< 0<< 1;


		fk = a*b*c*d*e;

		epos=p_map(fk);
		err=dist(epos,t);
		if(err<0.1)
		{	
			cout<<"ERROR IS LESS THAN 0.1"<<endl;
			break;
		}
		for(int j=0;j<4;j++)
		{
			theta1 = theta(0);
			theta2 = theta(1);
			theta3 = theta(2);
			theta4 = theta(3);
			theta5 = theta(4);
			
			a<<cos(theta1)<< 0<< sin(theta1)<< 0<<endr<< sin(theta1)<<  0<< -cos(theta1)<< 0<<endr<< 0<< 1<< 0<< l1<<endr<< 0<< 0<< 0<< 1;
			b<<cos(theta2)<< 0<< sin(theta2)<< 0<<endr<< sin(theta2)<<  0<< -cos(theta2)<< 0<<endr<< 0<< 1<< 0<< -l2<<endr<< 0<< 0<< 0<< 1;
			c<<cos(theta3)<< 0<< sin(theta3)<< 0<<endr<< sin(theta3)<<  0<< -cos(theta3)<< 0<<endr<< 0<< 1<< 0<< -l3<<endr<< 0<< 0<< 0<< 1;
			d <<cos(theta4)<< 0<< sin(theta4)<< 0<<endr<< sin(theta4)<<  0<< -cos(theta4)<< 0<<endr<< 0<< 1<< 0<< 0<<endr<< 0<< 0<< 0<< 1;
			e <<cos(theta5)<< 0<< sin(theta5)<< 0<<endr<< sin(theta5)<<  0<< -cos(theta5)<< 0<<endr<< 0<< 1<< 0<< l5<<endr<< 0<< 0<< 0<< 1;
			
			fk = a*b*c*d*e;
			epos=p_map(fk);
			cout<<"EPOS\n";
			epos.print();
				
			if(i==0)
				fk=a*b*c*d;
			else if(i==1)
				fk=a*b*c;
			else if(i==2)
				fk=a*b;
			else if(i==3)
				fk=a;
			
			jpos=p_map(fk);
			mat aa=(epos-jpos)/norm((epos-jpos),2);
			mat bb=(t-jpos)/norm((t-jpos),2);
			
			double theta_change=acos(dot(aa,bb));
			//for direction:
			mat theta_tempa;
			theta_tempa<<theta(0)<<theta(1)<<theta(2)<<theta(3)<<theta(4);
			theta_tempa(3-j)+=theta_change;		
			
			mat theta_tempb;
			theta_tempb<<theta(0)<<theta(1)<<theta(2)<<theta(3)<<theta(4);
			theta_tempb(3-j)-=theta_change;
			
			theta1=theta_tempa(0);
			theta2=theta_tempa(1);
			theta3=theta_tempa(2);
			theta4=theta_tempa(3);
			theta5=theta_tempa(4);
				
			a<<cos(theta1)<< 0<< sin(theta1)<< 0<<endr<< sin(theta1)<<  0<< -cos(theta1)<< 0<<endr<< 0<< 1<< 0<< l1<<endr<< 0<< 0<< 0<< 1;
			b<<cos(theta2)<< 0<< sin(theta2)<< 0<<endr<< sin(theta2)<<  0<< -cos(theta2)<< 0<<endr<< 0<< 1<< 0<< -l2<<endr<< 0<< 0<< 0<< 1;
			c<<cos(theta3)<< 0<< sin(theta3)<< 0<<endr<< sin(theta3)<<  0<< -cos(theta3)<< 0<<endr<< 0<< 1<< 0<< -l3<<endr<< 0<< 0<< 0<< 1;
			d <<cos(theta4)<< 0<< sin(theta4)<< 0<<endr<< sin(theta4)<<  0<< -cos(theta4)<< 0<<endr<< 0<< 1<< 0<< 0<<endr<< 0<< 0<< 0<< 1;
			e <<cos(theta5)<< 0<< sin(theta5)<< 0<<endr<< sin(theta5)<<  0<< -cos(theta5)<< 0<<endr<< 0<< 1<< 0<< l5<<endr<< 0<< 0<< 0<< 1;
					
			epos=p_map(a*b*c*d*e);
			erra=dist(epos,t);
			
			theta1=theta_tempb(0);
			theta2=theta_tempb(1);
			theta3=theta_tempb(2);
			theta4=theta_tempb(3);
			theta5=theta_tempb(4);
				
			a<<cos(theta1)<< 0<< sin(theta1)<< 0<<endr<< sin(theta1)<<  0<< -cos(theta1)<< 0<<endr<< 0<< 1<< 0<< l1<<endr<< 0<< 0<< 0<< 1;
			b<<cos(theta2)<< 0<< sin(theta2)<< 0<<endr<< sin(theta2)<<  0<< -cos(theta2)<< 0<<endr<< 0<< 1<< 0<< -l2<<endr<< 0<< 0<< 0<< 1;
			c<<cos(theta3)<< 0<< sin(theta3)<< 0<<endr<< sin(theta3)<<  0<< -cos(theta3)<< 0<<endr<< 0<< 1<< 0<< -l3<<endr<< 0<< 0<< 0<< 1;
			d <<cos(theta4)<< 0<< sin(theta4)<< 0<<endr<< sin(theta4)<<  0<< -cos(theta4)<< 0<<endr<< 0<< 1<< 0<< 0<<endr<< 0<< 0<< 0<< 1;
			e <<cos(theta5)<< 0<< sin(theta5)<< 0<<endr<< sin(theta5)<<  0<< -cos(theta5)<< 0<<endr<< 0<< 1<< 0<< l5<<endr<< 0<< 0<< 0<< 1;
					
			epos=p_map(a*b*c*d*e);
			errb=dist(epos,t);
			//direction ends
			
			if(erra<errb)
				theta(3-j)+=theta_change;
			else if(erra>errb)
				theta(3-j)-=theta_change;
				
			if(theta(0)<t1al)
				theta(0)=t1al;
			if(theta(0)>t1bl)
				theta(0)=t1bl;
			if(theta(1)<t2al)
				theta(1)=t2al;
			if(theta(1)>t2bl)
				theta(1)=t2bl;
			if(theta(2)<t3al)
				theta(2)=t3al;
			if(theta(2)>t3bl)
				theta(2)=t3bl;
			if(theta(3)<t4al)
				theta(3)=t4al;
			if(theta(3)>t4bl)
				theta(3)=t4bl;
			
			cout<<theta<<endl;
		}
	}
	cout<<"TARGET"<<endl<<t<<endl;
//	cout<<"CALCULATED"<<epos<<endl;
	return theta;
}
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	
