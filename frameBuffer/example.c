#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "fb_initial.h"
#define FBDEV "/dev/fb0"

int main(int argc,char *argv[]){
   
	fb_configure fb_conf;
	int ret;
	
	if(ret=FB_Create(&fb_conf,FBDEV))!=0){
		printf("ERROR\n");
	}
	/*
	 *  Do some thing
	 */
	FB_Destroy(&fb_conf);
	return 0;
}
