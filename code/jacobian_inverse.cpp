#include "kinematics.h"
#include <armadillo>

using namespace arma;
using namespace std;

int main()
{
	float x,y,z;
	mat ze;
	ze << 0.0;
	while(1)
	{
		cout<<"Enter x,y,z values: ";
		cin>>x>>y>>z;

		mat target;
		target<<x<<y<<z;

		mat theta_default;
		theta_default<<0<<1.5707<<1.5707<<0;

		mat theta_calc = calculate_pseudo_inverse(theta_default, target);			
		theta_calc.print("Calculated angles: ");

		theta_calc = join_vert(theta_calc, ze);

		if(validate_theta_left(theta_calc))
		{
			cout << "VALID!" << endl;
		}
		else
		{
			cout << "INVALID" << endl;
		}
	}
	return 0;
}
