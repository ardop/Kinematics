#include "kinematics.h"
#include "motor_control.h"
#include <armadillo>

using namespace arma;
using namespace std;

int main()
{
	double x,y,z;
	while(1)
	{
		cout<<"Enter x,y,z values: ";
		cin>>x>>y>>z;
		mat target;
		target<<x<<y<<z;
		target.print();
		mat theta_default;
		theta_default<<0<<1.5707<<1.5707<<0;
		theta_default.print();
		mat calc = calculate_ccd(theta_default, target);			
		calc.print("CALC");
	}
	return 0;
}
