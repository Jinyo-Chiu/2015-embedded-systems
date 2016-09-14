
#include "fb_initial.h"

int FB_Create(fb_configure *fb_conf,char *DEVICE_NAME){
	
	fb_conf->fb_handler = open(DEVICE_NAME,O_RDWR);
		
	if(!fb_conf->fb_handler){
		printf("Error: cannot open framebuffer device.\n");
		return -1;
	}

	printf("The framebuffer device was opened successfully.\n");

	if(ioctl(fb_conf->fb_handler,FBIOGET_FSCREENINFO,&fb_conf->fix_info)){
		printf("Error reading fixed information.\n");
		return -1;
	}

	if(ioctl(fb_conf->fb_handler,FBIOGET_VSCREENINFO,&fb_conf->variable_info)){
		printf("Error reading variable information.\n");
		return -1;
	}

	printf("%dx%d , %dbpp\n",fb_conf->variable_info.xres,fb_conf->variable_info.yres,fb_conf->variable_info.bits_per_pixel);
	
	fb_conf->screensize = fb_conf->variable_info.xres*fb_conf->variable_info.yres*fb_conf->variable_info.bits_per_pixel/8;
	fb_conf->fbp = (char*)mmap(0,fb_conf->screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fb_conf->fb_handler,0);

	if((int)fb_conf->fbp==-1){
		printf("Error: failed to map framebuffer device to memory.\n");
	    return -1;	
	}
	printf("The framebuffer was mapped to memory successful.\n");
	
	return 0;
}

void FB_Destroy(fb_configure *fb_conf){
	munmap(fb_conf->fbp,fb_conf->screensize);
	close(fb_conf->fb_handler);
}