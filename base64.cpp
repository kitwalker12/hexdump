#include "base64.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*--------------------*/
//Function returns Base64
//encoding for character
//parameter
/*---------------------*/
char encodechar(unsigned char encode)
{
	if(encode<26) { return 'A'+encode; }
	if(encode<52) { return 'a'+(encode-26); }
	if(encode<62) { return '0'+(encode-52); }
	if(encode==62) { return '+'; }
	return '/';
}

/*--------------------*/
//Function for encoding
//file. 
/*---------------------*/
void encode(FILE *file) {
	int i=0;
	char *buff;
	size_t result;
	unsigned char char3[]={0,0,0};  //define array for raw data
	unsigned char char4[]={0,0,0,0};	//array for encoded data
	buff=new char[3];
	while(true) {
		result=fread(buff,1,3,file); //read file 3 bytes at a time
		if(result!=3) {	//handle case for end of file
			if(result == 1) { //case with padding for 2 bytes
				char3[0]=buff[0];
				char3[1]=0;
				char3[2]=0;

				char4[0]=char3[0] >> 2;
				char4[1]=((char3[0] & 0x3) << 4) | (char3[1] >> 4);
				char4[2]=((char3[1] & 0xf) << 2) | (char3[2] >> 6);
				char4[3]= char3[2] & 0x3f;

				cout<< encodechar(char4[0])<< encodechar(char4[1]) << "==";
			}
			if(result == 2) { //case with padding for 1 byte
				char3[0]=buff[0];
				char3[1]=buff[1];
				char3[2]=0;

				char4[0]=char3[0] >> 2;
				char4[1]=((char3[0] & 0x3) << 4) | (char3[1] >> 4);
				char4[2]=((char3[1] & 0xf) << 2) | (char3[2] >> 6);
				char4[3]= char3[2] & 0x3f;

				cout<< encodechar(char4[0])<< encodechar(char4[1]) << encodechar(char4[2]) << "=";
			}
			break;
		}
		/*--------------------*/
		//Algorithm used and modified from 
		//http://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64
		/*---------------------*/
		char3[0]=buff[0];
		char3[1]=buff[1];
		char3[2]=buff[2];
		//shift bits to create 4 unsigned characters of 6 bits
		char4[0]=char3[0] >> 2;
		char4[1]=((char3[0] & 0x3) << 4) | (char3[1] >> 4);
		char4[2]=((char3[1] & 0xf) << 2) | (char3[2] >> 6);
		char4[3]= char3[2] & 0x3f;
		/*--------------------*/
		//End of 
		/*---------------------*/
		
		//output encoded string
		cout << encodechar(char4[0]) << encodechar(char4[1]) << encodechar(char4[2]) << encodechar(char4[3]);
		if(++i==16) { cout<<"\n"; i=0; }	//add newline after 64 characters
	}
	if(i!=0) {
		cout<<"\n";
	}
}

/*--------------------*/
//Function returns ASCII
//character for Base64
//encoded Data
/*---------------------*/
char decodechar(unsigned char decode)
{
	if (decode >= 'A' && decode <= 'Z')
	{
		return decode - 'A';
	}
	if (decode >= 'a' && decode <= 'z')
	{
		return decode - 'a' + 26;
	}
	if (decode >= '0' && decode <= '9')
	{
		return decode - '0' + 52;
	}
	if (decode == '+')
	{
		return 62;
	};
	return 63;
}

/*--------------------*/
//Function returns true
//or false if character 
//is legal Base64
/*---------------------*/
bool isbase64(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return true;
	}
	if (c >= 'a' && c <= 'z')
	{
		return true;
	}
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	if (c == '+')
	{
		return true;
	};
	if (c == '/')
	{
		return true;
	};
	if (c == '=')
	{
		return true;
	};
	return false;
}

void decode(FILE *file) {
	char *buff;
	size_t result;
	string enc="";
	string dec="";
	buff=new char;
	FILE *temp;
	int size=0;
	temp = fopen ("temp.b64","w+");
	if(file==NULL) {fputs("Error in opening temporary file\n",stderr);exit(1);}
	while(true) {	//check for illegal input and write to temporary file for decoding
		result=fread(buff,1,1,file);
		fwrite(buff,1,1,temp);
		if(result!=1) {
			break;
		}
		else{
			if(!isbase64(*buff) && *buff!='\n') {
				fputs("Input contains illegal characters\n",stderr);
				fclose(temp);
				fclose(file);
				remove("temp.b64");
				exit(1);
			}
			if(*buff=='\n') {
				continue;
			}
			size++;
		}
	}
	if((size%4)!=0) {
		cerr<<"Not enough characters for Base64 Decoding\n";
		fclose(temp);
		fclose(file);
		remove("temp.b64");
		exit(1);
	}
	rewind(temp);
	while(true) {	//perform decoding on temporary file
		result=fread(buff,1,1,temp);	//read 1 byte at a time
		if(result!=1) {
			break;
		}
		else {
			if(*buff=='\n') {
				continue;
			} else
			{
				enc += *buff;
				if(enc.length()==4) {	//perform decoding on set of 4 bytes
					char char1='A',char2='A',char3='A',char4='A';
					char1 = enc[0];
					char2 = enc[1];
					char3 = enc[2];
					char4 = enc[3];
					unsigned char byte1=0,byte2=0,byte3=0,byte4=0;
					byte1 = decodechar(char1);
					byte2 = decodechar(char2);
					byte3 = decodechar(char3);
					byte4 = decodechar(char4);
					dec.push_back( (byte1<<2)|(byte2>>4) );
					if (char3 != '=')
					{
						dec.push_back( ((byte2 & 0xf)<<4)|(byte3>>2) );
					}
					if (char4 != '=')
					{
						dec.push_back( ((byte3 & 0x3)<<6)|byte4 );
					}
					cout<<dec;
					dec="";
					enc="";
				}
			}
		}
	}
	fclose(temp);
	if( remove( "temp.b64" ) != 0 ) {	//remove temporary file
		fputs("Error deleting temporary file\n",stderr);
		fclose(file);
		exit(1);
	}
}
