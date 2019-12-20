#include<stdio.h>
#define offset(type, name) (size_t)(&(((type *)0)->name))

#pragma pack(4)
typedef struct Test_2char{
	char var1;
	char var2;
}Test_2char_t;	//2

typedef struct Test_3char{
	char var1;
	char var2;
	char var3;
}Test_3char_t;	//4

typedef struct Test_3array{
	char var[3];
}Test_3array_t;	//4

typedef struct Test_struct{
	char var1;
	char var2;
	Test_3char_t var3;
}Test_struct_t;	//5

typedef struct Test_ics{
	int var1;
	char var2;
	short var3;
}Test_ics_t;	//8

typedef struct Test_cis{
	char var1;
	int var2;
	short var3;
}Test_cis_t;	//12

typedef struct Test_cics{
	char var1;
	int var2;
	char var3;
	Test_2char_t var4;
}Test_cics_t;	//12

int main(int argc, char** argv){
	printf("Test_2char: %ld \n",sizeof(Test_2char_t));
	printf("Test_3char: %ld \n",sizeof(Test_3char_t));
	printf("Test_3array: %ld \n",sizeof(Test_3array_t));
	printf("Test_struct: %ld \n",sizeof(Test_struct_t));
	printf("Test_ics: %ld \n",sizeof(Test_ics_t));
	printf("Test_cis: %ld \n",sizeof(Test_cis_t));
	printf("Test_cics: %ld \n",sizeof(Test_cics_t));

	return 0;
}
