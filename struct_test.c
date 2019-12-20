#include<stdio.h>
#pragma pack()
#define offset(type, name) (size_t)(&(((type *)0)->name))
typedef struct Test{
	char var1;	//1
	int var2;	//4
	long var3;	//8
	char var4;	//1
}Test_t;
/*
64bit:
Test_t: 
	cxxx iiii	//在char后面填充，使得后一个变量int从对齐参数的整数倍
	llll llll 
	cxxx xxxx	//结构体总长度必须为对齐参数的整数倍，因此在结构体尾部填充。

32bit:
Test_t:
	cxxx iiii
	llll cxxx
*/

int main(int argc, char** argv){
	Test_t t1;
	t1.var1 = 'A';
	t1.var2 = 99;
	t1.var3 = 999;
	
	printf("struct->var1: %ld \n", offset(Test_t, var1));		
	printf("struct->var2: %ld \n", offset(Test_t, var2));		
	printf("struct->var3: %ld \n", offset(Test_t, var3));		
	printf("struct->var4: %ld \n", offset(Test_t, var4));		
	
	printf("struct: %ld \n", sizeof(t1));

	return 0;
}
