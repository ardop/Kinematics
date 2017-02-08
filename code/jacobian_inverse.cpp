#include "kinematics.h"
#include <armadillo>

using namespace arma;
using namespace std;

int main()
{
	arma_rng::set_seed_random();
	float x,y,z, theta1, theta2, theta3, theta4, theta5;
	mat ze;
	ze << 0.0;
	while(1)
	{
		cout<<"Enter x,y,z values: ";
		cin>>x>>y>>z;

		mat target;
		target<<x<<y<<z;

		mat theta_default;

		while(true)
		{
			mat ar = randu<mat>(1, 5);

			theta1 = (t1bl-t1al)*ar(0) + t1al;
			theta2 = (t2bl-t2al)*ar(1) + t2al;
			theta3 = (t3bl-t3al)*ar(2) + t3al; 
			theta4 = (t4bl-t4al)*ar(3) + t4al;
			theta5 = (t5bl-t5al)*ar(4) + t5al;

			theta_default << theta1 << theta2 << theta3 << theta4;

			cout << endl;
			theta_default.print("Default theta:");

			mat theta_calc = calculate_pseudo_inverse(theta_default, target);
			// theta_calc.print("Calculated angles: ");			

			theta_calc = join_vert(theta_calc, ze);

			if(validate_theta_left(theta_calc))
			{
				cout << "VALID!" << endl;
				theta_calc.print("Calculated angles: ");
				break;
			}
			else
			{
				cout << "INVALID" << endl;
			}
		}
	}
	return 0;
}
