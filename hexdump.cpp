#include "hexdump.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*--------------------*/
//Function for hexdump
//output
/*---------------------*/
void hexdump(FILE *file) {
	char *buff;
	buff=new char[16];
	int result;
	int i;
	int offset=0;
	unsigned char temp;
	while(true){
		result=fread(buff,1,16,file);	//read 16 bytes at a time 
		if(result==0) { break; }
		if(result!=16) {
			printf("%06x: ",offset);
			for(i=0;i<result;i++){ //print hex value
				printf("%02x ",(unsigned char)buff[i]);
				if(i==7) {
					cout<<" ";
				}
			}
			for(i=result;i<16;i++) { //print empty lines
				cout<<"-- ";
				if(i==7) {
					cout<<" ";}
				}
			cout<<" ";
		for(i=0;i<result;i++){      //print ASCII data
			temp=(unsigned char)buff[i];
			if(temp>=0x20 && temp<=0x7e) {
				printf("%c",temp);
			}
			if(temp<=0x1f || temp==0x7f) {
				cout<<".";
			}
			if(temp>=0x80) {
				cout<<"~";
			}
		}
		for(i=result;i<16;i++) {
			cout<<" ";
		}
		cout<<"\n";
		break;
	}
	printf("%06x: ",offset);
	for(i=0;i<16;i++){	//print hex value
		printf("%02x ",(unsigned char)buff[i]);
		if(i==7){cout<<" ";}
	}
	cout<<" ";
	for(i=0;i<16;i++){	//print ASCII data
		temp=(unsigned char)buff[i];
		if(temp>=0x20 && temp<=0x7e) {
			printf("%c",temp);
		}
		if(temp<=0x1f || temp==0x7f) {
			cout<<".";
		}
		if(temp>=0x80) {
			cout<<"~";
		}
	}
	cout<<"\n";
	offset+=16;
}
}

