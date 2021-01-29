#include "CSCIx239.h"
//
//  Convenience routine to output raster text
//  Use VARARGS to make this more flexible
//

//  I lifted this font from Brent Smit - not sure if it is original
static int font=0;
static GLubyte letters[][14] = {
	{ 0x00, 0x00, 0x7e, 0xe7, 0xe7, 0xff, 0xe7, 0xe7, 0xf3, 0x99, 0x99, 0xc3, 0x7e, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x76, 0x00, 0xdc, 0x76, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x6e, 0xd8, 0xd8, 0xd8, 0xde, 0xd8, 0xd8, 0xd8, 0xd8, 0x6e, 0x00 },
	{ 0x00, 0x00, 0x00, 0x6e, 0xdb, 0xd8, 0xdf, 0xdb, 0xdb, 0x6e, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x00 },
	{ 0x00, 0x00, 0x20, 0x20, 0x38, 0x20, 0x3e, 0x00, 0x80, 0x80, 0xe0, 0x80, 0xf8, 0x00 },
	{ 0x00, 0x00, 0x22, 0x24, 0x3e, 0x22, 0x3c, 0x00, 0x78, 0x80, 0x80, 0x80, 0x78, 0x00 },
	{ 0x00, 0x00, 0x20, 0x20, 0x38, 0x20, 0x3e, 0x00, 0xf8, 0x80, 0x80, 0x80, 0x80, 0x00 },
	{ 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88 },
	{ 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa },
	{ 0xee, 0xbb, 0xee, 0xbb, 0xee, 0xbb, 0xee, 0xbb, 0xee, 0xbb, 0xee, 0xbb, 0xee, 0xbb },
	{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
	{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
	{ 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0 },
	{ 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f },
	{ 0x00, 0x00, 0x3e, 0x20, 0x20, 0x20, 0x20, 0x00, 0x88, 0x98, 0xa8, 0xc8, 0x88, 0x00 },
	{ 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x20, 0x50, 0x50, 0x88, 0x88, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x30, 0x18, 0x0c, 0x06, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x0c, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0xfe, 0x38, 0xfe, 0x0c, 0x06, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x02, 0x0e, 0x3e, 0x7e, 0xfe, 0x7e, 0x3e, 0x0e, 0x02, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xfc, 0xfe, 0xfc, 0xf0, 0xe0, 0x80, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0xfe, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0xfe, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x6c, 0xfe, 0x6c, 0x28, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0xfe, 0x66, 0x36, 0x06, 0x06, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x6c, 0x6c, 0x6c, 0x6c, 0x6e, 0x7c, 0xc0, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x3c, 0x3c, 0x3c, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x36, 0x36, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0xfe, 0x6c, 0x6c, 0xfe, 0x6c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x10, 0x7c, 0xd6, 0x1c, 0x38, 0x70, 0xd6, 0x7c, 0x10, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0x66, 0x30, 0x18, 0x0c, 0x66, 0x62, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xcc, 0xce, 0xf6, 0x76, 0x38, 0x38, 0x6c, 0x38, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x1c, 0x1c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0xfe, 0x38, 0x6c, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xd6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0xc6, 0x60, 0x30, 0x18, 0x0c, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x06, 0x06, 0x3c, 0x06, 0x06, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0c, 0xfe, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x06, 0x06, 0xfc, 0xc0, 0xc0, 0xc0, 0xfe, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xfc, 0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0xc6, 0xfe, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x06, 0x06, 0x7e, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x18, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x0c, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7e, 0xc0, 0xdc, 0xde, 0xde, 0xde, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfc, 0x66, 0x66, 0x66, 0x7c, 0x66, 0x66, 0x66, 0xfc, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x66, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x66, 0xfe, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xf0, 0x60, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x66, 0xfe, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xce, 0xc0, 0xc0, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x70, 0xd8, 0xd8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xcc, 0xd8, 0xf0, 0xf0, 0xd8, 0xcc, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x66, 0x62, 0x60, 0x60, 0x60, 0x60, 0x60, 0xf0, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xd6, 0xd6, 0xd6, 0xfe, 0xee, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xce, 0xce, 0xde, 0xf6, 0xe6, 0xe6, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xf0, 0x60, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0xfc, 0x00, 0x00 },
	{ 0x00, 0x00, 0x06, 0x7c, 0xd6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xe6, 0x66, 0x6c, 0x78, 0x7c, 0x66, 0x66, 0x66, 0xfc, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x06, 0x0c, 0x38, 0x60, 0xc0, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x5a, 0x7e, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xee, 0xfe, 0xd6, 0xd6, 0xd6, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x38, 0x6c, 0xc6, 0xc6, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0xc6, 0xc2, 0x60, 0x30, 0x18, 0x8c, 0xc6, 0xfe, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3c, 0x18, 0x00, 0x00 },
	{ 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x18, 0x1c, 0x1c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfc, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xe0, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7e, 0xcc, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0x0c, 0x1c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xfe, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x78, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x36, 0x1c, 0x00, 0x00 },
	{ 0x00, 0x7c, 0xc6, 0x06, 0x7e, 0xc6, 0xc6, 0xce, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xe6, 0x66, 0x66, 0x66, 0x76, 0x6c, 0x60, 0x60, 0xe0, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x38, 0x00, 0x18, 0x18, 0x00, 0x00 },
	{ 0x00, 0x78, 0xcc, 0xcc, 0x0c, 0x0c, 0x0c, 0x0c, 0x1c, 0x00, 0x0c, 0x0c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0x60, 0x60, 0xe0, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x38, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xd6, 0xd6, 0xfe, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0xf0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0x66, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x1e, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0xcc, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xf0, 0x60, 0x60, 0x60, 0x66, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x1c, 0x70, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x10, 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x6c, 0xfe, 0xd6, 0xd6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x7c, 0xc6, 0x06, 0x76, 0xce, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x62, 0x30, 0x18, 0x8c, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x0e, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x0e, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0e, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x76, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x3c, 0x66, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 },
	{ 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x30, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x60, 0x6f, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6f, 0x60, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6f, 0x60, 0x6f, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x0c, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x0c, 0xec, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xef, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0xec, 0x0c, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0xec, 0x0c, 0xec, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0xef, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0xef, 0x00, 0xef, 0x6c, 0x6c, 0x6c, 0x6c, 0x6c },
	{ 0x00, 0x00, 0xfe, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x18, 0x3c, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x10, 0x7c, 0xd6, 0xd0, 0xd0, 0xd6, 0x7c, 0x10, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x6c, 0xf6, 0x66, 0x60, 0xf0, 0x60, 0x60, 0x6c, 0x38, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x62, 0x60, 0xf8, 0x60, 0xf8, 0x60, 0x62, 0x3c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x18, 0x18, 0x3c, 0x18, 0x7e, 0x18, 0x3c, 0x66, 0x66, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0x06, 0x1c, 0x60, 0xc6, 0xc6, 0x7c, 0x00, 0x38, 0x6c },
	{ 0x00, 0x7c, 0xc6, 0xc6, 0x0c, 0x7c, 0xc6, 0xc6, 0x7c, 0x60, 0xc6, 0xc6, 0x7c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7e, 0x81, 0x99, 0xa5, 0xa1, 0xa5, 0x99, 0x81, 0x7e, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x3e, 0x6c, 0x6c, 0x3c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x6c, 0xd8, 0x6c, 0x36, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x7e, 0x81, 0xa5, 0xa5, 0xb9, 0xa5, 0xb9, 0x81, 0x7e, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x38, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7e, 0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x30, 0x18, 0x6c, 0x38, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x6c, 0x18, 0x6c, 0x38, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0xc6, 0x62, 0x30, 0x18, 0x8c, 0xc6, 0xfe, 0x00, 0x38, 0x6c },
	{ 0xc0, 0xc0, 0xc0, 0xf6, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x1b, 0x1b, 0x1b, 0x1b, 0x7b, 0xdb, 0xdb, 0xdb, 0x7f, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x62, 0x30, 0x18, 0x8c, 0xfe, 0x00, 0x38, 0x6c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x30, 0x30, 0x70, 0x30, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x38, 0x6c, 0x6c, 0x38, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0x6c, 0x36, 0x6c, 0xd8, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x77, 0xdf, 0xd8, 0xd8, 0xde, 0xde, 0xd8, 0xdf, 0x77, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x6e, 0xdb, 0xd8, 0xdf, 0xdb, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x3c, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00 },
	{ 0x00, 0x7c, 0xc6, 0xc6, 0x60, 0x30, 0x30, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0x18, 0x30, 0x60 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0x30, 0x18, 0x0c },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0x6c, 0x38, 0x10 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0xdc, 0x76, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0x6c, 0x6c, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6, 0x6c, 0x38, 0x00, 0x38, 0x6c, 0x38 },
	{ 0x00, 0x00, 0x00, 0xde, 0xd8, 0xd8, 0xd8, 0xfe, 0xd8, 0xd8, 0xd8, 0xd8, 0x7e, 0x00 },
	{ 0x38, 0x6c, 0x18, 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x66, 0x60, 0x7c, 0x60, 0x66, 0xfe, 0x00, 0x0c, 0x18, 0x30 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x66, 0x60, 0x7c, 0x60, 0x66, 0xfe, 0x00, 0x30, 0x18, 0x0c },
	{ 0x00, 0x00, 0x00, 0xfe, 0x66, 0x60, 0x7c, 0x60, 0x66, 0xfe, 0x00, 0x6c, 0x38, 0x10 },
	{ 0x00, 0x00, 0x00, 0xfe, 0x66, 0x60, 0x7c, 0x60, 0x66, 0xfe, 0x00, 0x6c, 0x6c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x0c, 0x18, 0x30 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x30, 0x18, 0x0c },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x66, 0x3c, 0x18 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00, 0x66, 0x66, 0x00 },
	{ 0x00, 0x00, 0x00, 0xf8, 0x6c, 0x66, 0x66, 0xf6, 0x66, 0x66, 0x6c, 0xf8, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xc6, 0xc6, 0xce, 0xde, 0xf6, 0xe6, 0xc6, 0x00, 0xdc, 0x76, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x18, 0x30, 0x60 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x30, 0x18, 0x0c },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x6c, 0x38, 0x10 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0xdc, 0x76, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x6c, 0x6c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x38, 0x38, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfc, 0xc6, 0xe6, 0xf6, 0xd6, 0xde, 0xce, 0xc6, 0x7e, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x18, 0x30, 0x60 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x30, 0x18, 0x0c },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x6c, 0x38, 0x10 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x6c, 0x6c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x3c, 0x66, 0x66, 0x66, 0x00, 0x18, 0x0c, 0x06 },
	{ 0x00, 0x00, 0x00, 0xf0, 0x60, 0x7c, 0x66, 0x66, 0x66, 0x7c, 0x60, 0xf0, 0x00, 0x00 },
	{ 0x00, 0x00, 0x80, 0xdc, 0xd6, 0xc6, 0xc6, 0xcc, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0x18, 0x30, 0x60, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0x60, 0x30, 0x18, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0xcc, 0x78, 0x30, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0xdc, 0x76, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0x6c, 0x6c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xdc, 0xcc, 0x7c, 0x0c, 0x78, 0x00, 0x38, 0x6c, 0x38, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7e, 0xdb, 0xd8, 0x7f, 0x1b, 0xdb, 0x7e, 0x00, 0x00, 0x00, 0x00 },
	{ 0x38, 0x6c, 0x18, 0x7c, 0xc6, 0xc0, 0xc0, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xfe, 0xc6, 0x7c, 0x00, 0x0c, 0x18, 0x30, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xfe, 0xc6, 0x7c, 0x00, 0x30, 0x18, 0x0c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xfe, 0xc6, 0x7c, 0x00, 0x6c, 0x38, 0x10, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc0, 0xfe, 0xc6, 0x7c, 0x00, 0x6c, 0x6c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x38, 0x00, 0x18, 0x30, 0x60, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x38, 0x00, 0x30, 0x18, 0x0c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x38, 0x00, 0x66, 0x3c, 0x18, 0x00 },
	{ 0x00, 0x00, 0x00, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x38, 0x00, 0x6c, 0x6c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7e, 0x0c, 0x78, 0x30, 0x78, 0x00 },
	{ 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0xdc, 0x00, 0xdc, 0x76, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x18, 0x30, 0x60, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x30, 0x18, 0x0c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x6c, 0x38, 0x10, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0xdc, 0x76, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x6c, 0x6c, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x7e, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0xfc, 0xe6, 0xf6, 0xde, 0xce, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x30, 0x60, 0xc0, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x30, 0x18, 0x0c, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0xcc, 0x78, 0x30, 0x00 },
	{ 0x00, 0x00, 0x00, 0x76, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0xcc, 0xcc, 0x00, 0x00 },
	{ 0x00, 0x7c, 0xc6, 0x06, 0x76, 0xce, 0xc6, 0xc6, 0xc6, 0x00, 0x30, 0x18, 0x0c, 0x00 },
	{ 0xf0, 0x60, 0x60, 0x78, 0x6c, 0x6c, 0x6c, 0x78, 0x60, 0x60, 0xf0, 0x00, 0x00, 0x00 },
	{ 0x00, 0x7c, 0xc6, 0x06, 0x76, 0xce, 0xc6, 0xc6, 0xc6, 0x00, 0xc6, 0xc6, 0x00, 0x00 }
};

//
//  Output text as bitmaps
//
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Setup font as display lists on first use
   if (!font)
   {
      int i;
      glPixelStorei(GL_UNPACK_ALIGNMENT,1);
      font = glGenLists(256);
      for (i=0;i<256;i++)
      {
         glNewList(font+i,GL_COMPILE);
         glBitmap(8,14,0.0,0.0,9.0,0.0,letters[i]);
         glEndList();
      }
   }
   //  Display the characters at the current raster position
   glListBase(font);
   glCallLists(strlen(buf),GL_UNSIGNED_BYTE,(GLubyte *)buf);
}
