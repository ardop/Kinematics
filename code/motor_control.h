/*
 * The MIT License (MIT)

Copyright (c) 2015 Jetsonhacks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
// servoExample.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <JHPWMPCA9685.h>
#include <iostream>
#include <math.h>

using namespace std;

// Calibrated for a Robot Geek RGS-13 Servo
// Make sure these are appropriate for the servo being used!

 int servoMin = 100;
 int servoMax = 510;
// int servoMin = 135;
// int servoMax = 545;
//int servoMin=1000;
//int servoMax=2000;
int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

// Map an integer from one coordinate system to another
// This is used to map the servo values to degrees
// e.g. map(90,0,180,servoMin, servoMax)
// Maps 90 degrees to the servo value

double map ( int x, int in_min, int in_max, int out_min, int out_max) {
    double toReturn =  (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min ;
    // For debugging:
    // printf("MAPPED %d to: %d\n", x, toReturn);
    return toReturn ;
}

double invmap(double y,double in_min,double in_max,double out_min,double out_max)
{
double toReturn = ((y-out_min)*(in_max-in_min)/(out_max-out_min)+in_min);
return toReturn;
}

double regread(int chan ,PCA9685 *a)
{
double  read,read1,read2,dread;
read1=a->getPWMofl(chan);
usleep(100);
read2=a->getPWMofh(chan);
usleep(100);
read=(read2*256)+read1;
dread=invmap(read,0,180,servoMin,servoMax);
return dread;
}
//void rotate(int d,int chan, PCA9685 *a)
//{
    //int temp,count;
    //temp=regread(chan,a);
    //if(temp>d)
    //{
	//count=-1;
    //}
    //else if(temp<d)
    //{
	//count=1;
    //}
    //else if(temp==d)
	//count=0;
  //for(int i=temp+1;i!=d;i+=count)
    //{
	//temp=regread(chan,a);
	//a->setPWM(chan,0,map(i,0,180,servoMin,servoMax));
	//usleep(40000);
	//cout<<temp<<"="<<d<<' '<<i<<endl;
    //}
//}
void rotate_multi(int d[5],PCA9685 *a)
{
    double j[5],temp[5],count[5],flag[5];
	for(int i=0;i<5;i++)
	{
    temp[i]=round(regread(i,a));
    j[i]=temp[i];
    flag[i]=0;
    if(temp[i]>d[i])
    {
	count[i]=-1;
    }
    else if(temp[i]<d[i])
    {
	count[i]=1;
    }
    else if(temp[i]==d[i])
	count[i]=0;
	}
	while(true)
	{
		
	for(int i=0;i<5;i++)
	{
	temp[i]=round(regread(i,a));
	if(d[i]!=temp[i])
	{	
		j[i]+=count[i];
		a->setPWM(i,0,map(j[i],0,180,servoMin,servoMax));
	}
	else
	flag[i]=1;
	}
	for(int i=0;i<5;i++)
	{
	cout<<temp[i]<<"->"<<d[i]<<" NEXT ";
	}
	cout<<endl;
	usleep(5000);
	if(flag[0]==1 &&flag[1]==1 && flag[2]==1 && flag[3]==1 &&flag[4]==1)
	break;
	}
}

double kin_map_left(int c,double angle)
{
	switch(c)
	{
		case 0: 		
			return angle*180/(PI)+137;
			break;
		case 1:
			return 116-angle*180/(PI);
			break;
		case 2:
			return angle*180/(PI)+15;
			break;
		case 3:
			return angle*180/(PI)+180;
			break;
		case 4:
			return angle*180/(PI)+90;
			break;
	}
}

double kin_map_right(int c,double angle)
{
	switch(c)
	{
		case 0: 		
			return angle*180/(PI)+233;
			break;
		case 1:
			return angle*180/(PI)+244;
			break;
		case 2:
			return angle*180/(PI)+15;
			break;
		case 3:
			return angle*180/(PI)+180;
			break;
		case 4:
			return angle*180/(PI)+90;
			break;
	}
}

void rotate(int d[9],PCA9685 *a)
{
    double j[9],temp[9],count[9],flag[9];
	for(int i=0;i<9;i++)
	{
    temp[i]=round(regread(i,a));
    j[i]=temp[i];
    flag[i]=0;
    if(temp[i]>d[i])
    {
	count[i]=-1;
    }
    else if(temp[i]<d[i])
    {
	count[i]=1;
    }
    else if(temp[i]==d[i])
	count[i]=0;
	}
	while(true)
	{
		
		for(int i=0;i<9;i++)
		{
		temp[i]=round(regread(i,a));
		if(d[i]!=temp[i])
		{	
			j[i]+=count[i];
			a->setPWM(i,0,map(j[i],0,180,servoMin,servoMax));
		}
		else
		flag[i]=1;
		}
		for(int i=0;i<9;i++)
		{
		cout<<temp[i]<<"->"<<d[i]<<"..";
		}
		cout<<endl;
		usleep(5000);
		if(flag[0]==1 &&flag[1]==1 && flag[2]==1 && flag[3]==1 && flag[4]==1 && flag[5]==1 && flag[6]==1 && flag[7]==1 && flag[8]==1)
			break;
	}
}

void rotate_all(int d[20],PCA9685 *a,PCA9685 *b)
{
    double j[20],temp[20],count[20],flag[20];
	for(int i=0;i<9;i++)
	{
    temp[i]=round(regread(i,a));
    j[i]=temp[i];
    flag[i]=0;
    if(temp[i]>d[i])
    {
	count[i]=-1;
    }
    else if(temp[i]<d[i])
    {
	count[i]=1;
    }
    else if(temp[i]==d[i])
	count[i]=0;
	}
	for(int i=9;i<20;i++) //second object (b) has the head servo connections.
	{
    temp[i]=round(regread((i-9),b));
    j[i]=temp[i];
    flag[i]=0;
    if(temp[i]>d[i])
    {
	count[i]=-1;
    }
    else if(temp[i]<d[i])
    {
	count[i]=1;
    }
    else if(temp[i]==d[i])
	count[i]=0;
	}
	
	while(true)
	{
		for(int i=0;i<9;i++)
		{
		temp[i]=round(regread(i,a));
		if(d[i]!=temp[i])
		{	
			j[i]+=count[i];
			a->setPWM(i,0,map(j[i],0,180,servoMin,servoMax));
		}
		else
		flag[i]=1;
		}
		for(int i=9;i<20;i++)
		{
		temp[i]=round(regread((i-9),b));
		if(d[i]!=temp[i])
		{	
			j[i]+=count[i];
			b->setPWM((i-9),0,map(j[i],0,180,servoMin,servoMax));
		}
		else
		flag[i]=1;
		}
		for(int i=0;i<20;i++)
		{
		cout<<temp[i]<<"->"<<d[i]<<"..";
		}
		cout<<endl;
		usleep(1000);
		if(flag[0]==1 &&flag[1]==1 && flag[2]==1 && flag[3]==1 && flag[4]==1 && flag[5]==1 && flag[6]==1 && flag[7]==1 && flag[8]==1 && flag[9]==1 &&flag[10]==1 && flag[11]==1 && flag[12]==1 && flag[13]==1 && flag[14]==1 && flag[15]==1 && flag[16]==1 && flag[17]==1 && flag[18]==1 && flag[19]==1)
			break;
	}
}

	 void shake_hand(PCA9685 *pca1,PCA9685 *pca2)
	 {
			 int val[20];
			 val[0]=137;
			 val[1]=26;
			 val[2]=105;
			 val[3]=180;
			 val[4]=90;	
			 val[5]=60;
			 val[6]=60;
			 val[7]=60;
			 val[8]=60;
			 val[9]=53;
			 val[10]=150;
			 val[11]=105;
			 val[12]=90;
			 val[13]=90;	
			 val[14]=60;
			 val[15]=60;
			 val[16]=60;
			 val[17]=60;
			 val[18]=90;
			 val[19]=90;
			 rotate_all(val,pca1,pca2);
			 sleep(2);
			 for(int i=0;i<2;i++)
			 {
				 val[12]=70;
				 rotate_all(val,pca1,pca2);
				 usleep(100000);
				 val[12]=90;			
				 rotate_all(val,pca1,pca2);
				 usleep(100000);
			 }
			 val[12]=0;
			 rotate_all(val,pca1,pca2);
	 }
