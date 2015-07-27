#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define COLOR_BAR_NUM 8
#define FBDEV "/dev/fb0"

typedef struct fb_configure{
	int fb_handler ;
	struct fb_var_screeninfo variable_info;
	struct fb_fix_screeninfo fix_info;
	long int screensize;
	char *fbp;
}fb_configure;

struct colour {
	int r;
	int g;
	int b;
	int a;
};

static struct colour colorTable[8] = {
	
	{.r =255, .g = 255, .b=255, .a=255},	//white
	{.r =255, .g = 255, .b=0,   .a=255},	//yellow
	{.r =0,   .g = 255, .b=255, .a=255},	//Cyan
	{.r =0,   .g = 255, .b=0,   .a=255},	//Green
	{.r =255, .g = 0,   .b=255, .a=255},	//Magenta
	{.r =255, .g = 0,   .b=0,   .a=255},	//Red
	{.r =0,   .g = 0,   .b=255, .a=255},	//Blue
	{.r =0,   .g = 0,   .b=0,   .a=255}		//Black
};


void ColorBar_Fill_RGB(fb_configure fb_conf){

	int x_plot= 0 , y_plot = 0;
	int part_length=0;
	long int location = 0;
	int index = 0;
	
	/*setting each color-bar's width Size*/	
	part_length = fb_conf.variable_info.xres/COLOR_BAR_NUM;

	for( index=0 ; index<COLOR_BAR_NUM ; index++ )
		for( x_plot = index * part_length ; x_plot < ((index+1) * part_length) ; x_plot++ )
			for( y_plot = 0 ; y_plot < fb_conf.variable_info.yres ; y_plot++ ){
				
				location  = (x_plot+fb_conf.variable_info.xoffset)*(fb_conf.variable_info.bits_per_pixel/8)+\
							(y_plot+fb_conf.variable_info.yoffset)*fb_conf.fix_info.line_length;

				if(fb_conf.variable_info.bits_per_pixel ==32){

					*(fb_conf.fbp + location) = colorTable[index].b;  //Blue
					*(fb_conf.fbp + location+1) = colorTable[index].g;//Green
					*(fb_conf.fbp + location+2) = colorTable[index].r;//Red
					*(fb_conf.fbp + location+3) = colorTable[index].a;//transparent
				}
			}

}

void ColorBar_FB_Init(fb_configure *fb_conf){
	
	fb_conf->fb_handler = open(FBDEV,O_RDWR);
		
	if(!fb_conf->fb_handler){
		printf("Error: cannot open framebuffer device.\n");
	}

	printf(" framebuffer open completed.\n");

	/*fetch fixed information*/
	if(ioctl(fb_conf->fb_handler,FBIOGET_FSCREENINFO,&fb_conf->fix_info)){
		printf("Error reading fixed information.\n");
	}
	
	/*fetch variable information*/
	if(ioctl(fb_conf->fb_handler,FBIOGET_VSCREENINFO,&fb_conf->variable_info)){
		printf("Error reading variable information.\n");
	}

	printf("%dx%d , %dbpp\n",fb_conf->variable_info.xres,fb_conf->variable_info.yres,fb_conf->variable_info.bits_per_pixel);
	
	fb_conf->screensize = fb_conf->variable_info.xres*fb_conf->variable_info.yres*fb_conf->variable_info.bits_per_pixel/8;
	fb_conf->fbp = (char*)mmap(0,fb_conf->screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fb_conf->fb_handler,0);

	if((int)fb_conf->fbp==-1){
		printf("Error: failed to map framebuffer device to memory.\n");
	}
	printf("The framebuffer was mapped to memory successful.\n");
}

void ColorBar_FB_Destroy(fb_configure *fb_conf){
	munmap(fb_conf->fbp,fb_conf->screensize);
	close(fb_conf->fb_handler);
}


int main(int argc,char *argv[]){
   
	fb_configure fb_conf;
	/*initial framebuffer data*/
	ColorBar_FB_Init(&fb_conf);
	/*setting colorBar*/
	ColorBar_Fill_RGB(fb_conf);
	/*destory*/
	ColorBar_FB_Destroy(&fb_conf);
	return 0;
}
