
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


typedef struct fb_configure{
	int fb_handler ;
	struct fb_var_screeninfo variable_info;
	struct fb_fix_screeninfo fix_info;
	long int screensize;
	char *fbp;
}fb_configure;


int FB_Create(fb_configure *fb_conf,char *DEVICE_NAME);
void FB_Destroy(fb_configure *fb_conf);