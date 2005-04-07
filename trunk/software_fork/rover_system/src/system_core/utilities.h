#ifndef __utilities_h
#define __utilities_h

char* get_var_from_file(char* filename, 
							  char *varname, 
							  char *var_container, 
							  int length);


void next_non_space(char* buff, int &i);

bool match(char* varname, char* buff, int &i);

void grab(char *buff, int &i, char *container,int length);

bool string_to_bool(char *b_string, bool default_val);

#endif
