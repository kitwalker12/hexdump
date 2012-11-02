#include "base64.h"
#include "hexdump.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main (int argc, char *argv[]) {
	FILE *file;
	string usage="Usage: ./hw1 <hexdump|enc-base64|dec-base64> [file]  \n";
	
	if(argc<=1) {	//check for command without options
		fputs(usage.c_str(),stderr);
		return 1;
	}
	
	if(argc==2) {	//check for malformed command & input from stdin
		if((strcmp(argv[1], "hexdump") != 0) && (strcmp(argv[1], "enc-base64") != 0) && (strcmp(argv[1], "dec-base64") != 0)) {
			fputs(usage.c_str(),stderr);
			return 1;
		}
		file=stdin;
	}
	
	if(argc==3){	//check for malformed command & input from file
		if((strcmp(argv[1], "hexdump") != 0) && (strcmp(argv[1], "enc-base64") != 0) && (strcmp(argv[1], "dec-base64") != 0)) {
			fputs(usage.c_str(),stderr);
			return 1;
		}
		if(strcmp(argv[2], "") != 0) {
			file=fopen(argv[2],"rb");
			if(file==NULL) {fputs("Error in opening file\n",stderr);exit(1);}
		}
		else {
			fputs(usage.c_str(),stderr);
			return 1;
		}
	}
	
	//pass file to selected function
	if(strcmp(argv[1], "hexdump") == 0) {
		hexdump(file);
	} else if(strcmp(argv[1], "enc-base64") == 0) {
		encode(file);
	} else if(strcmp(argv[1], "dec-base64") == 0) {
		decode(file);
	}
	else {
		fputs(usage.c_str(),stderr);
		fclose(file);
		return 1;
	}
	
	fclose(file);
	return 0;	
}



