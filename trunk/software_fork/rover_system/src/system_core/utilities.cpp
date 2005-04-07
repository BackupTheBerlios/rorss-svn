#include <stdio.h>
#include "utilities.h"

char bool_string_true[][8] =  { "yes", "YES", "Yes", "true", "TRUE", "True", "\0" };
char bool_string_false[][8] = { "no", "NO", "No", "false", "FALSE", "False", "\0" };


char* get_var_from_file(char* filename, 
							  char *varname, 
							  char *var_container, 
							  int length)
	{
	int i=0;
	FILE* config_file;
	char buff[255]= "a";
	
	if ( ! (config_file = fopen(filename,"r")) )
		{
		fprintf(stderr,"error opening %s\n",filename);
		return NULL;
		}
	
	while( fgets(buff,255,config_file) )
		{
		//printf("checking: %s",buff);
		if(match(varname,buff,i))
			{
			printf("found: [%s]   ",varname);
			grab(buff,i,var_container,length);
			printf("to be: [%s]\n",var_container);
			return var_container;
			}
		i=0;
		}
	return NULL;
	}


void next_non_space(char* buff, int &i)
	{
	for( ; 
		    buff[i] != '\0'
	    && ( buff[i] == ' ' 
	      || buff[i] == '\t'
		   || buff[i] == '\n' )
	                      ; i++ );
	}

bool match(char* varname, char* buff, int &i)
	{
	int j;
	next_non_space(buff,i);

	for(j=0;;i++ + j++)
		{
		if(varname[j] == '\0')       break;
		if(buff[i]    != varname[j]) 
			{
			//printf("%c != %c\n", buff[i] ,varname[j]);
			return false;
			}
		} 
	
	next_non_space(buff,i);
	
	if(buff[i++] != '=')
		return false;
	else
		return true;
	}

void grab(char *buff, int &i, char *container,int length)
	{
	int j;
	next_non_space(buff,i);
	
		for(j=0 ; 
						 buff[i] != '\0' 
					 && buff[i] != ' ' 
					 && buff[i] != '\t'
					 && buff[i] != '\n'
					 && j < length-1
	                               ; i++ + j++ )
			container[j] = buff[i];
		container[j] = '\0' ;
	return;
	}

bool string_to_bool(char *b_string, bool default_val)
	{
	int  i,j  ;
	bool match=false;
	
	if(b_string == NULL)
		return default_val;
	
	for( i=0 ; bool_string_true[i][0] != '\0' ; i++ )
		{
		for( j=0 ; bool_string_true[i][j] != '\0' && b_string[j] != '\0' ; j++ )
			{
			if(bool_string_true[i][j+1] == b_string[j+1] )
				{
				if(bool_string_true[i][j+1] == '\0' && b_string[j+1] == '\0')
					return true;
				}
			else
				break;
			}
		}
	
	for(i=0;bool_string_false[i][0] != '\0' ;i++)
		{
		for( j=0 ; bool_string_false[i][j] != '\0' && b_string[j] != '\0' ; j++ )
			{
			if(bool_string_false[i][j+1] == b_string[j+1] )
				{
				if(bool_string_false[i][j+1] == '\0' && b_string[j+1] == '\0')
					return false;
				}
			else
				break;
			}
		}
	return default_val;
	}
	
	
