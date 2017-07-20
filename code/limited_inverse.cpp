#include "kinematics.h"
#include <armadillo>

using namespace arma;
using namespace std;

int main()
{
	double x,y,z;
	double y0, z0, y01, y02;
	float theta1, theta2, theta3;
	mat theta;
	
	while(1)
	{
		start:
		cout<<"Enter x,y,z values: ";
		cin>>x>>y>>z;
		
		float d1 = 14.5;
		float d2 = 29.5;
		
		float K = x*x + y*y + z*z  - d2*d2;
		float C = 2*d1 - 2*y;
		
		float B = 2*K*C - 8*d1*z*z;
		float A = 4*z*z + C*C;
		
		cout << K << endl << C << endl << B << endl << A << endl;

		float discriminant = B*B - 4*A*K*K;

		cout << discriminant << endl;
		
		if(discriminant>=0)
		{
			y01 = (-B + sqrt(discriminant))/2*A;
			y02 = (-B - sqrt(discriminant))/2*A;

			if(y01>=0 && y02>=0)
			{
				y0 = min(y01, y02);
			}
			else if(y01>=0 && y02<0)
			{
				y0 = y01;
			}
			else if(y01<0 && y02>=0)
			{
				y0 = y02;
			}
			else
			{
				cout << "No Solution";

				goto start;
			}

			z0 = sqrt(2*d1*y0 - y0*y0);
			
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
