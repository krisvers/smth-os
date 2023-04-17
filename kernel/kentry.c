extern char _BSS_START;
extern char _BSS_END;

#include <tty.h>
#include <vga.h>

static uint8_t * boot_info = (void *) 0x500;
static void * video_ptr;
static uint16_t video_res[2];

void main();

void __attribute((section(".entry"))) _kentry() {
	video_res[0] = (boot_info[6] << 8) | (boot_info[5]);
	video_res[1] = (boot_info[8] << 8) | (boot_info[7]);
	video_ptr = (void *) ((boot_info[4] << 24) | (boot_info[3] << 16) | (boot_info[2] << 8) | (boot_info[1]));

	if (boot_info[0] == 0x03) {
		tty_init(video_res[0], video_res[1], video_ptr);
	} else if (boot_info[0] == 0x13) {
		vga_init(video_res[0], video_res[1], video_ptr, boot_info[9]);
	} else {
		// implement other sort of text/vga/cga stuff
	}

	main();

	while (1);
}
