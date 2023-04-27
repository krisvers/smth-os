extern char _BSS_START;
extern char _BSS_END;

#include <stdio.h>
#include <tty.h>
#include <vga.h>

static uint8_t * boot_info = (void *) 0x500;
static void * video_ptr;
static uint16_t video_res[2];

void main();

/*
VGA-Compatible BIOS Video Modes
	0x00: 0xB8000 text 40x25,   16 shade greyscale
	0x01: 0xB8000 text 40x25,   16 colors
	0x02: 0xB8000 text 80x25,   16 shade greyscale
	0x03: 0xB8000 text 80x25,   16 FG colors, 16 BG colors
	0x04: 0xB8000 gfx  320x200, 4 colors
	0x05: 0xB8000 gfx  320x200, 4 shade greyscale
	0x06: 0xB8000 gfx  640x200, monochrome
	0x0D: 0xA0000 gfx  320x200, 16 color
	0x0E: 0xA0000 gfx  640x200, 16 color
	0x0F: 0xA0000 gfx  640x350, monochrome
	0x10: 0xA0000 gfx  640x350, 16 color
	0x11: 0xA0000 gfx  640x480, monochrome
	0x12: 0xA0000 gfx  640x480, 16 color
	0x13: 0xA0000 gfx  320x200, 8 bit RGB
*/


void __attribute((section(".entry"))) _kentry() {
	video_res[0] = (boot_info[7] << 8) | (boot_info[6]);
	video_res[1] = (boot_info[9] << 8) | (boot_info[8]);
	video_ptr = (void *) ((boot_info[5] << 24) | (boot_info[4] << 16) | (boot_info[3] << 8) | (boot_info[2]));

	switch (((uint16_t *) boot_info)[0]) {
		case 0x00:
			tty_init(video_res[0], video_res[1], video_ptr);
			break;
		case 0x01:
			tty_init(video_res[0], video_res[1], video_ptr);
			break;
		case 0x02:
			tty_init(video_res[0], video_res[1], video_ptr);
			break;
		case 0x03:
			tty_init(video_res[0], video_res[1], video_ptr);
			break;
		case 0x04:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x05:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x06:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x0D:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x0E:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x0F:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x10:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x11:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x12:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x13:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		case 0x115:
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			break;
		default:
			// other video modes (probably not standard vga) or possible headless
			vga_init(video_res[0], video_res[1], video_ptr, boot_info[10]);
			//tty_init(video_res[0], video_res[1], video_ptr);
			break;
	}

	main();

	while (1);
}
