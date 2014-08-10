/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * fpu_test.c: test the fpu.
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 *
 *
 *   Author		Operation		Date
 *   Duran		Add/Edit		2014-7-1
 *   Duran		Edit			2014-7-6
 */

#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include <xtime_l.h>
#include "common.h"

#define N 1000
//define results for uart out
#define RESULT_SIZE 16

//function def
//double Dart(int n);
//double RandomDouble();
void GetCoefficient(float x[],float y[],int n1,int n2,float a[2],float RR[1]);


//use to generate the random number
//const unsigned long maxshort = 65536L;
//const unsigned long multiplier = 1194211693L;
//const unsigned long adder = 12345L;


typedef struct{
	double real;
	double img;
}complex;

int size_x=8;      /*输入序列的大小，在本程序中仅限2的次幂*/
complex x[N], W[N]; /*输入序列,变换核*/

double PI;         /*圆周率*/

void fft();     /*快速傅里叶变换*/
void initW();   /*初始化变换核*/
void change(); /*变址*/
void add(complex ,complex ,complex *); /*复数加法*/
void mul(complex ,complex ,complex *); /*复数乘法*/
void sub(complex ,complex ,complex *); /*复数减法*/
void output();

int fftmain()
{
	int i;                             /*输出结果*/
	//system("cls");
	PI=atan(1)*4;
	//printf("Please input the size of x:\n");
	//scanf("%d",&size_x);
	//printf("Please input the data in x[N]:\n");
	for(i=0;i<size_x;i++)
	{
	   x[i].real=(i+3)*(i+3)+4;
	   x[i].img=0;
	}
	initW();
	fft();
	output();
	return 0;
}

/*快速傅里叶变换*/
void fft(){
	int i=0,j=0,k=0,l=0;
	complex up,down,product;
	change();
	for(i=0;i< log(size_x)/log(2) ;i++)
	{   /*一级蝶形运算*/
	   l=1<<i;
	   for(j=0;j<size_x;j+= 2*l )
	   {             /*一组蝶形运算*/
			for(k=0;k<l;k++)
			{        /*一个蝶形运算*/
				mul(x[j+k+l],W[size_x*k/2/l],&product);
				add(x[j+k],product,&up);
				sub(x[j+k],product,&down);
				x[j+k]=up;
				x[j+k+l]=down;
			}
	   }
	}
}

/*初始化变换核*/
void initW(){
	int i;
	//W=(complex *)malloc(sizeof(complex) * size_x);
	for(i=0;i<size_x;i++)
	{
	   W[i].real=cos(2*PI/size_x*i);
	   W[i].img=-1*sin(2*PI/size_x*i);
	}
}

/*变址计算，将x(n)码位倒置*/
void change()
{
	complex temp;
	unsigned short i=0,j=0,k=0;
	double t;
	for(i=0;i<size_x;i++)
	{
	   k=i;j=0;
	   t=(log(size_x)/log(2));
	   while( (t--)>0 )
	   {
		j=j<<1;
		j|=(k & 1);
		k=k>>1;
	   }
	   if(j>i)
	   {
		temp=x[i];
		x[i]=x[j];
		x[j]=temp;
	   }
	}
}

/*输出傅里叶变换的结果*/
void output()
{
	char results[RESULT_SIZE] = {0};
	double expectedResult[] = {412.0000, 0,
			-28.6863, 135.1960,
			-48.0000, 56.0000,
			-51.3137, 23.1960,
			-52.0000, 0,
			-51.3137, -23.1960,
			-48.0000, -56.0000,
			-28.6863, -135.1960 };
	double precision = 0.0001;
	int isSuccess = 1;
	int i;
//	printf("The result are as follows\n");

	for(i=0;i<size_x;i++)
	{
//		printf("%.4f",x[i].real);
		//compare to find if real part equals
		if(abs(expectedResult[2 * i] - x[i].real) > precision)
		{
			isSuccess = -1;
			UART_ToBytes(DATA_TYPE_DOUBLE, &expectedResult[2 * i], results, 0);
			UART_ToBytes(DATA_TYPE_DOUBLE, &x[i].real, results, 8);
//			results[0] = expectedResult[2 * i];
//			results[1] = x[i].real;
			UART_Fail(TEST_TYPE_FPU, results, RESULT_SIZE);
		}
		//compare to find if img part equals
		if(abs(expectedResult[2 * i + 1] - x[i].img) > precision)
		{
			isSuccess = -1;
			UART_ToBytes(DATA_TYPE_DOUBLE, &expectedResult[2 * i + 1], results, 0);
			UART_ToBytes(DATA_TYPE_DOUBLE, &x[i].img, results, 8);
//			results[0] = expectedResult[2 * i + 1];
//			results[1] = x[i].img;
			UART_Fail(TEST_TYPE_FPU, results, RESULT_SIZE);
		}
		/*if(x[i].img>=0.0001)
			printf("+%.4f\n",x[i].img);
		else if(fabs(x[i].img)<0.0001)
			printf("\n");
		else
			printf("%.4f\n",x[i].img);*/
	}
	if(isSuccess)
		UART_Success(TEST_TYPE_FPU);
//	printf("The except result are as follows\n");
//	printf("412.0000\n-28.6863+135.1960j\n-48.0000+56.0000j\n-51.3137+23.1960j\n-52.0000\n-51.3137-23.1960j\n-48.0000-56.0000j\n-28.6863-135.1960j\n ");
}

void add(complex a,complex b,complex *c){
	c->real=a.real+b.real;
	c->img=a.img+b.img;
}

void mul(complex a,complex b,complex *c){
	c->real=a.real*b.real - a.img*b.img;
	c->img=a.real*b.img + a.img*b.real;
}

void sub(complex a,complex b,complex *c){
	c->real=a.real-b.real;
	c->img=a.img-b.img;
}


/**
 * The function test the fpu.
 *
 */
void FPU_Test()
{
	/*usleep(2);
	double e=0.1,b=0.5,d;
	long int i; i: 正多边形边数
	for(i=6;;i*=2) //正多边形边数加倍
	{
		d=1.0-sqrt(1.0-b*b); //计算圆内接正多边形的边长
		b=0.5*sqrt(b*b+d*d);
		if(2*i*b-i*e<1e-10) break; //精度达1e-15则停止计算
		e=b;//保存本次正多边形的边长作为下一次精度控制的依据
	}
	printf("p  =%.10lf\n\r",2*i*b); 输出π值和正多边形的边数*/
	/*double pi = 3.1415926, estimatedPi;
	int n = 100000; //1000dots
	estimatedPi = Dart(n);
	printf("expected pi = %.7f, estimated pi = %.7f\n", pi, estimatedPi);*/

	//set y = ax + b
	//a[0] denote a, a[1] denote b
	//RR[0] denote relation rate

	fftmain();

	/*float x[4] = {3 , 4, 5, 6}, y[4] = {2.5, 3, 4, 4.5}, a[2], RR[1], expectedA[2] = {0.7, 0.35};
	int n1 = 0, n2 = 3;
	GetCoefficient(x, y, n1, n2, a, RR);
	//printf the tips
	printf("set y = ax + b\n");
	printf("x[] = {");
	int i;
	for(i = n1; i <= n2; i++)
	{
		printf("%f", x[i]);
		if(i != n2)
			printf(", ");
		else
			printf("}\n");
	}
	printf("y[] = {");
	for(i = n1; i <= n2; i++)
	{
		printf("%f", y[i]);
		if(i != n2)
			printf(", ");
		else
			printf("}\n");
	}
	printf("expected a = %f, expected b = %f\ncalculated a = %f, calculated b = %f\n", expectedA[0], expectedA[1], a[0], a[1]);*/
}

/**
 * throw n dots, use the random algorithm to calculate the Pi
 * @param n
 * return estimated pi
 */
/*double Dart(int n){
	int k = 0;//record the dots who falls in the circle
	int i = 0;
	for(i = 0; i <= n; i++){
		double x = RandomDouble();
		double y = RandomDouble();
		if((x*x + y*y) <= 1)
			k++; //fall in the circle
	}
	return 4 * k/(double) n;
}*/

/**
 * use the time as seed to generate the random double number range from 0 to 1
 */
/*double RandomDouble(){
	XTime now;
	XTime_GetTime(&now);
	unsigned long randSeed = (unsigned long) now;
	randSeed = multiplier * randSeed + adder;
	randSeed = randSeed >> 16; //use higer 16 bit because its randomness is better
	return (double) randSeed / maxshort;
}*/


/*
 * 回归方程：y=ax+b,其中a代表斜率，b代表截距，对数组中n1到n2范围段内的数据进行线性回归。
 * x[],y[]分别代表存放横轴自变量和纵轴因变量数据的数组,
 * n1:范围段内的第一个点在数组中的位置（元素下标），
 * n2:范围段内的最后一个点在数组中的位置（元素下标），
 * a[0]:存放斜率a，a[1]存放截距b。
 * RR[0]存放相关系数R的平方
 */
void GetCoefficient(float x[],float y[],int n1,int n2,float a[2],float RR[1])
{
	//分别代表 ∑Xi, ∑Yi, ∑(XiYi)、∑(Xi*Xi), ∑(Yi*Yi), ∑Xi*∑Yi, (∑X)*(∑X), (∑Y)*(∑Y)
	float SumX=0,SumY=0,SumXY=0,SumXX=0,SumYY=0,SumXAndSumY,SumXAndSumX,SumYAndSumY;
	if(n1>n2) //如果n1比n2小，则交换二者数值,以保证n1<n2
	{
		int tmp;
		tmp=n1;
		n1=n2;
		n2=tmp;
	}
	int i;
	for(i = n1; i <= n2; i++) //此处根据实际情况可修改
	{
		SumX=SumX+x[i];         //SumX=∑xi
		SumY=SumY+y[i];         //SumY=∑yi
		SumXY=SumXY+x[i]*y[i];  //SumXY=∑(XiYi)
		SumXX=SumXX+x[i]*x[i];  //SumXX=∑(Xi*Xi)
		SumYY=SumYY+y[i]*y[i];  //SumYY=∑(Yi*Yi)
	}
	SumXAndSumY=SumX*SumY;    //SumXAndSumY= ∑Xi * ∑Yi
	SumXAndSumX=SumX*SumX;    //SumXAndSumX=(∑X)*(∑X)
	SumYAndSumY=SumY*SumY;    //SumYAndSumY=(∑Y)*(∑Y)

	if((n2-n1+1)*SumXX-SumXAndSumX)
	{
		a[0]=((n2-n1+1)*SumXY-SumXAndSumY)/((n2-n1+1)*SumXX-SumXAndSumX);  //斜率a
		a[1]=(SumY-a[0]*SumX)/(n2-n1+1);  //截距b
	}
	if(((n2-n1+1)*SumXX-SumXAndSumX)*((n2-n1+1)*SumYY-SumYAndSumY))//计算相关系数R的平方
		RR[0]=((n2-n1+1)*SumXY-SumXAndSumY)*((n2-n1+1)*SumXY-SumXAndSumY)/(((n2-n1+1)*SumXX-SumXAndSumX)*((n2-n1+1)*SumYY-SumYAndSumY));//R平方
}
