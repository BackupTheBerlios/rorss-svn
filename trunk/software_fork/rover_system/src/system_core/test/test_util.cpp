#include "utilities.h"
#define SIZE 20

int main()
	{
	char variable1[SIZE]="";
	char variable2[SIZE]="";
	char variable3[SIZE]="";
	char variable4[SIZE]="";
	char variable5[SIZE]="";
	
	get_var_from_file("config", "variable", variable1, SIZE);
	get_var_from_file("config", "jockie", variable1, SIZE);
	get_var_from_file("config", "fartpoop", variable3, SIZE);
	get_var_from_file("config", "junkie", variable4, SIZE);
	get_var_from_file("config", "flatulance", variable5, SIZE);
	
	
	return 0;
	}