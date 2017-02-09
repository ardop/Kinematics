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
#define t5bl 1.5707
#define t5al -1.5707


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

mat calculate_fk_mat(const mat& theta)
{
	mat fkmat, a, b, c, d, e;
	
	double theta1, theta2, theta3, theta4, theta5;
	
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

	fkmat = a*b*c*d*e;
	
	return fkmat;
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



bool validate_theta_left(const mat& angles)
{
	double theta1 = angles(0);
	double theta2 = angles(1);
	double theta3 = angles(2);
	double theta4 = angles(3);
	double theta5 = angles(4);
	
	int flag = 0;
	
	// if((theta1<=epsilon1) && (theta1>=-(PI-epsilon1)))
	// 	flag++;

	// if((theta2<=PI/2+epsilon2) && (theta2>=-alpha2))
	// 	flag++;

	// if((theta3<=PI) && (theta3>=0.0))
	// 	flag++;

	// if((theta4<=0) && (theta4>=-PI/2))
	// 	flag++;

	// if((theta5<=PI/2) && (theta5>=-PI/2))
	// 	flag++;

	if(theta1<=t1bl && theta1>=t1al)
		flag++;
	if(theta2<=t2bl && theta2>=t2al)
		flag++;
	if(theta3<=t3bl && theta3>=t3al)
		flag++;
	if(theta4<=t4bl && theta4>=t4al)
		flag++;
	if(theta5<=t5bl && theta5>=t5al)
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

double calculate_error(const mat&a, const mat &b)
{
	double err = 0.0;
	for(int i=0;i<a.n_cols;i++)
	{
		err += pow((a(i)-b(i)), 2);
	}
	err = err/a.n_cols;
	err = sqrt(err);
	return err;
}
		


mat calculate_jacobian(const mat& theta)
{

	float j11, j12, j13, j14, j21, j22, j23, j24, j31, j32, j33, j34, theta1, theta2, theta3, theta4;

	mat J;

 	theta1 = theta(0);
	theta2 = theta(1);
 	theta3 = theta(2);
 	theta4 = theta(3);

 	// Calculating jacobian

 	j11 = -l5*sin(theta1)*cos(theta2)*cos(theta3)*sin(theta4) + l5*sin(theta1)*cos(theta4)*sin(theta2) + l3*sin(theta1)*sin(theta2) + l5*cos(theta1)*sin(theta3)*sin(theta4) - l2*cos(theta1);
 	j12 = -l5*cos(theta1)*sin(theta2)*cos(theta3)*sin(theta4) - l5*cos(theta1)*cos(theta4)*cos(theta2) - l3*cos(theta1)*cos(theta2);
 	j13 = -l5*cos(theta1)*cos(theta2)*sin(theta3)*sin(theta4) + l5*sin(theta1)*cos(theta3)*sin(theta4);
 	j14 = l5*cos(theta1)*cos(theta2)*cos(theta3)*cos(theta4) + l5*cos(theta1)*sin(theta4)*sin(theta2) + l5*sin(theta1)*sin(theta3)*cos(theta4);

 	j21 = l5*cos(theta2)*cos(theta3)*cos(theta1)*sin(theta4) - l5*cos(theta4)*cos(theta1)*sin(theta2) - l3*cos(theta1)*sin(theta2) + l5*sin(theta1)*sin(theta3)*sin(theta4) - l2*sin(theta1);
 	j22 = -l5*sin(theta2)*cos(theta3)*sin(theta1)*sin(theta4) - l5*cos(theta4)*sin(theta1)*cos(theta2) - l3*sin(theta1)*cos(theta2);
 	j23 = -l5*cos(theta2)*sin(theta3)*sin(theta1)*sin(theta4) - l5*cos(theta1)*cos(theta3)*sin(theta4);
 	j24 = l5*cos(theta2)*cos(theta3)*sin(theta1)*cos(theta4) +  l5*sin(theta4)*sin(theta1)*sin(theta2) - l5*cos(theta1)*sin(theta3)*cos(theta4);

 	j31= 0.0;
 	j32 = l5*cos(theta3)*cos(theta2)*sin(theta4) - l5*sin(theta2)*cos(theta4) - l3*sin(theta2);
 	j33 = -l5*sin(theta3)*sin(theta2)*sin(theta4);
 	j34 = l5*cos(theta3)*sin(theta2)*cos(theta4) - l5*cos(theta2)*sin(theta4);

 	J << j11 << j12 << j13 << j14 << endr << j21 << j22 << j23 << j24 << endr << j31 << j32 << j33 << j34;


 	return J;

}

mat calculate_pseudo_inverse(const mat& theta_default, const mat& target)
{

	mat q, J, pJ, a, b, c, d, e, targeti;
	float alpha, theta1, theta2, theta3, theta4, theta5;

	q = trans(theta_default);

	alpha = 0.01;

	for(int i=0;i<500;i++)
	{
		J = calculate_jacobian(q);
		pJ = pinv(J);

		theta1 = q(0);
		theta2 = q(1);
		theta3 = q(2);
		theta4 = q(3);
		theta5 = 0.0;

		a<<cos(theta1)<< 0<< sin(theta1)<< 0<<endr<< sin(theta1)<<  0<< -cos(theta1)<< 0<<endr<< 0<< 1<< 0<< l1<<endr<< 0<< 0<< 0<< 1;
		b<<cos(theta2)<< 0<< sin(theta2)<< 0<<endr<< sin(theta2)<<  0<< -cos(theta2)<< 0<<endr<< 0<< 1<< 0<< -l2<<endr<< 0<< 0<< 0<< 1;
		c<<cos(theta3)<< 0<< sin(theta3)<< 0<<endr<< sin(theta3)<<  0<< -cos(theta3)<< 0<<endr<< 0<< 1<< 0<< -l3<<endr<< 0<< 0<< 0<< 1;
		d <<cos(theta4)<< 0<< sin(theta4)<< 0<<endr<< sin(theta4)<<  0<< -cos(theta4)<< 0<<endr<< 0<< 1<< 0<< 0<<endr<< 0<< 0<< 0<< 1;
		e <<cos(theta5)<< 0<< sin(theta5)<< 0<<endr<< sin(theta5)<<  0<< -cos(theta5)<< 0<<endr<< 0<< 1<< 0<< l5<<endr<< 0<< 0<< 0<< 1;

		targeti = p_map(a*b*c*d*e);

		q = q + alpha*pJ*trans(target - targeti);

	}

	target.print("Target:\n");
	targeti.print("Calculated Target:\n");

	return q;

}

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
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	
