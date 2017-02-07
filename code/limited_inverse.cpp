#include "kinematics.h"
#include <armadillo>

using namespace arma;
using namespace std;

int main()
{
	double x,y,z;
	double y0, z0;
	float theta1, theta2, theta3;
	mat theta;
	
	while(1)
	{
		cout<<"Enter x,y,z values: ";
		cin>>x>>y>>z;
		
		float d1 = 14.5;
		float d2 = 29.5;
		
		float K = x*x + y*y + z*z + d1*d1 - d2*d2;
		float C = K*K - 4*y*y*d1*d1;
		
		float discriminant = K*K*z*z - C*y*y - C*z*z;
		
		cout << K << endl << C << endl << discriminant << endl;
		
		if(discriminant>=0)
		{
			z0 = (K*z + sqrt(discriminant))/(y*y + z*z);
			y0 = sqrt(d1*d1 - z0*z0);
			
			theta1 = atan2(z0, y0);
			theta2 = atan2(abs(z-z0), abs(y-y0));
			theta3 = atan2(abs(x), abs(z-z0));
			
			cout << theta1 << endl << theta2 << endl << theta3 << endl;
			
			
			
		}
		else
		{
			cout << "No solution found" << endl;
		}
	}
	
}
