#ifndef WAVETABLES_H_
#define WAVETABLES_H_

#include <avr/pgmspace.h>

enum
{
	WAVE_SINE = 0,
	WAVE_TRI,
	WAVE_LSAW,
	WAVE_RSAW,
	WAVE_SQU,
	NUM_WAVE
}WAVE_TYPE;

PROGMEM const char analogWaveTable[]  = 
{
	//sine wave
	127,130,133,136,139,143,146,149,152,155,158,161,164,167,170,173,176,178,181,184,187,190,192,195,198,200,203,205,208,
	210,212,215,217,219,221,223,225,227,229,231,233,234,236,238,239,240,242,243,244,245,247,248,249,249,250,251,252,252,
	253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,249,249,248,247,245,244,243,242,240,239,238,236,
	234,233,231,229,227,225,223,221,219,217,215,212,210,208,205,203,200,198,195,192,190,187,184,181,178,176,173,170,167,
	164,161,158,155,152,149,146,143,139,136,133,130,127,124,121,118,115,111,108,105,102,99,96,93,90,87,84,81,78,76,73,
	70,67,64,62,59,56,54,51,49,46,44,42,39,37,35,33,31,29,27,25,23,21,20,18,16,15,14,12,11,10,9,7,6,5,5,4,3,2,2,1,1,1,0,
	0,0,0,0,0,0,1,1,1,2,2,3,4,5,5,6,7,9,10,11,12,14,15,16,18,20,21,23,25,27,29,31,33,35,37,39,42,44,46,49,51,54,56,59,
	62,64,67,70,73,76,78,81,84,87,90,93,96,99,102,105,108,111,115,118,121,124,

	//triangle wave
	128,129,131,133,135,137,139,141,144,146,148,150,152,154,157,159,161,164,166,168,170,173,175,
	177,179,181,183,185,187,189,191,193,195,197,198,200,202,204,206,208,210,213,215,217,220,222,
	224,227,229,232,234,237,239,241,244,246,248,249,251,252,253,254,255,255,255,255,254,254,253,
	251,250,248,247,245,243,240,238,236,233,231,228,226,223,221,218,216,214,212,209,207,205,203,
	201,199,197,196,194,192,190,188,186,184,182,180,178,176,174,171,169,167,165,162,160,158,156,
	153,151,149,147,145,142,140,138,136,134,132,130,128,127,125,123,121,119,117,115,113,110,108,
	106,104,102,99,97,95,93,90,88,86,84,81,79,77,75,73,71,69,67,65,63,61,59,58,56,54,52,50,48,46,
	43,41,39,37,34,32,29,27,24,22,19,17,15,12,10,8,7,5,4,2,1,1,0,0,0,0,1,2,3,4,6,7,9,11,14,16,18,
	21,23,26,28,31,33,35,38,40,42,45,47,49,51,53,55,57,58,60,62,64,66,68,70,72,74,76,78,80,82,85,
	87,89,91,94,96,98,101,103,105,107,109,111,114,116,118,120,122,124,126,127,

	//left saw (negative slope)
	87,87,87,87,87,86,86,85,84,83,81,80,78,77,75,73,71,69,68,66,65,64,63,62,61,61,61,61,61,61,61,61,61,61,
	61,61,60,60,59,57,56,55,53,51,49,47,46,44,42,41,39,38,37,37,36,36,36,36,37,37,38,38,39,39,39,39,39,39,
	38,37,35,34,32,30,28,26,24,22,20,19,17,16,16,15,15,16,17,18,19,21,23,24,26,28,29,30,30,31,30,29,28,26,
	24,21,18,15,12,8,6,3,1,0,0,1,3,6,11,17,24,33,43,54,66,80,94,108,123,138,153,167,181,194,207,218,227,236,
	243,248,252,254,255,255,253,250,246,242,237,232,226,220,215,209,204,200,196,193,190,188,186,185,185,185,
	185,185,186,186,187,187,187,187,186,186,184,183,181,179,176,173,171,168,165,162,159,157,155,153,151,150,
	148,148,147,147,147,147,147,147,147,147,147,147,146,145,144,143,142,140,138,136,134,132,130,128,126,124,
	122,121,119,118,117,117,116,116,116,115,115,115,115,115,115,115,114,114,113,112,111,109,108,106,104,102,
	100,98,97,95,93,92,91,90,89,88,88,87,87,87,87,87,


	//right saw (positive slope)
	168,168,168,168,168,169,169,170,171,172,174,175,177,178,180,182,184,186,187,189,190,191,192,
	193,194,194,194,194,194,194,194,194,194,194,194,194,195,195,196,198,199,200,202,204,206,208,
	209,211,213,214,216,217,218,218,219,219,219,219,218,218,217,217,216,216,216,216,216,216,217,
	218,220,221,223,225,227,229,231,233,235,236,238,239,239,240,240,239,238,237,236,234,232,231,
	229,227,226,225,225,224,225,226,227,229,231,234,237,240,243,247,249,252,254,255,255,254,252,
	249,244,238,231,222,212,201,189,175,161,147,132,117,102,88,74,61,48,37,28,19,12,7,3,1,0,0,2,
	5,9,13,18,23,29,35,40,46,51,55,59,62,65,67,69,70,70,70,70,70,69,69,68,68,68,68,69,69,71,72,
	74,76,79,82,84,87,90,93,96,98,100,102,104,105,107,107,108,108,108,108,108,108,108,108,108,108,
	109,110,111,112,113,115,117,119,121,123,125,127,129,131,133,134,136,137,138,138,139,139,139,
	140,140,140,140,140,140,140,141,141,142,143,144,146,147,149,151,153,155,157,158,160,162,163,
	164,165,166,167,167,168,168,168,168,168,

	//Square
	127,141,154,167,180,192,203,213,222,230,237,243,247,251,253,255,255,255,253,251,249,246,243,240,237,234,232,
	229,227,226,224,224,224,224,225,226,227,229,231,233,235,237,239,240,242,243,244,244,244,244,243,243,241,240,
	238,237,235,233,232,230,229,228,227,227,227,227,228,228,230,231,232,234,236,238,239,241,242,243,244,244,244,
	244,243,242,241,239,238,236,234,232,230,228,226,225,224,224,224,224,225,226,228,230,233,236,239,242,245,248,
	250,252,254,255,255,254,252,249,245,240,234,226,217,208,197,186,174,161,148,134,121,107,94,81,69,58,47,38,
	29,21,15,10,6,3,1,0,0,1,3,5,7,10,13,16,19,22,25,27,29,30,31,31,31,31,30,29,27,25,23,21,19,17,16,14,13,12,11,
	11,11,11,12,13,14,16,17,19,21,23,24,25,27,27,28,28,28,28,27,26,25,23,22,20,18,17,15,14,12,12,11,11,11,11,12,
	13,15,16,18,20,22,24,26,28,29,30,31,31,31,31,29,28,26,23,21,18,15,12,9,6,4,2,0,0,0,2,4,8,12,18,25,33,42,52,
	63,75,88,101,114,127,
};

PROGMEM const uint8_t DutyIndex[][256] =
{
	//0
	{0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,
		21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,38,38,
		39,39,40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48,49,49,50,50,51,51,52,52,53,53,54,54,55,55,56,
		56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,
		74,74,75,75,76,76,77,77,78,78,79,79,80,80,81,81,82,82,83,83,84,84,85,85,86,86,87,87,88,88,89,89,90,90,91,
		91,92,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99,100,100,101,101,102,102,103,103,104,104,105,105,106,
		106,107,107,108,108,109,109,110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,
		119,120,120,121,121,122,122,123,123,124,124,125,125,126,126,127,127},
		
	//1
	{0,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,139,140,140,141,
		141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,150,150,151,151,152,152,153,153,154,
		154,155,155,156,156,157,157,158,158,159,159,160,160,161,161,162,162,163,163,164,164,165,165,166,166,167,
		167,168,168,169,169,170,170,171,171,172,172,173,173,174,174,175,175,176,176,177,177,178,178,179,179,180,
		180,181,181,182,182,183,183,184,184,185,185,186,186,187,187,188,188,189,189,190,190,191,191,192,192,193,
		193,194,194,195,195,196,196,197,197,198,198,199,199,200,200,201,201,202,202,203,203,204,204,205,205,206,
		206,207,207,208,208,209,209,210,210,211,211,212,212,213,213,214,214,215,215,216,216,217,217,218,218,219,
		219,220,220,221,221,222,222,223,223,224,224,225,225,226,226,227,227,228,228,229,229,230,230,231,231,232,
		232,233,233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241,242,242,243,243,244,244,245,
		245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255},
		
	//2
	{0,64,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,139,140,140,
		141,141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,150,150,151,151,152,152,153,153,
		154,154,155,155,156,156,157,157,158,158,159,159,160,160,161,161,162,162,163,163,164,164,165,165,166,166,
		167,167,168,168,169,169,170,170,171,171,172,172,173,173,174,174,175,175,176,176,177,177,178,178,179,179,
		180,180,181,181,182,182,183,183,184,184,185,185,186,186,187,187,188,188,189,189,190,190,191,191,192,193,
		193,194,194,195,195,196,196,197,197,198,198,199,199,200,200,201,201,202,202,203,203,204,204,205,205,206,
		206,207,207,208,208,209,209,210,210,211,211,212,212,213,213,214,214,215,215,216,216,217,217,218,218,219,
		219,220,220,221,221,222,222,223,223,224,224,225,225,226,226,227,227,228,228,229,229,230,230,231,231,232,
		232,233,233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241,242,242,243,243,244,244,245,
		245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255},
		
	//3
	{0,42,85,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,139,140,
		140,141,141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,150,150,151,151,152,152,153,
		153,154,154,155,155,156,156,157,157,158,158,159,159,160,160,161,161,162,162,163,163,164,164,165,165,166,
		166,167,167,168,168,169,169,170,171,171,172,172,173,173,174,174,175,175,176,176,177,177,178,178,179,179,
		180,180,181,181,182,182,183,183,184,184,185,185,186,186,187,187,188,188,189,189,190,190,191,191,192,192,
		193,193,194,194,195,195,196,196,197,197,198,198,199,199,200,200,201,201,202,202,203,203,204,204,205,205,
		206,206,207,207,208,208,209,209,210,210,211,211,212,212,213,214,214,215,215,216,216,217,217,218,218,219,
		219,220,220,221,221,222,222,223,223,224,224,225,225,226,226,227,227,228,228,229,229,230,230,231,231,232,
		232,233,233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241,242,242,243,243,244,244,245,
		245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255},
		
	//4
	{0,32,64,96,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,139,
		140,140,141,141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,150,150,151,151,152,152,
		153,153,154,154,155,155,156,156,157,157,158,158,159,159,160,161,161,162,162,163,163,164,164,165,165,166,
		166,167,167,168,168,169,169,170,170,171,171,172,172,173,173,174,174,175,175,176,176,177,177,178,178,179,
		179,180,180,181,181,182,182,183,183,184,184,185,185,186,186,187,187,188,188,189,189,190,190,191,191,192,
		193,193,194,194,195,195,196,196,197,197,198,198,199,199,200,200,201,201,202,202,203,203,204,204,205,205,
		206,206,207,207,208,208,209,209,210,210,211,211,212,212,213,213,214,214,215,215,216,216,217,217,218,218,
		219,219,220,220,221,221,222,222,223,223,224,225,225,226,226,227,227,228,228,229,229,230,230,231,231,232,
		232,233,233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241,242,242,243,243,244,244,245,
		245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255},
		
	//5
	{0,25,51,76,102,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,
		139,140,140,141,141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,150,150,151,151,152,
		152,153,154,154,155,155,156,156,157,157,158,158,159,159,160,160,161,161,162,162,163,163,164,164,165,165,
		166,166,167,167,168,168,169,169,170,170,171,171,172,172,173,173,174,174,175,175,176,176,177,177,178,178,
		179,180,180,181,181,182,182,183,183,184,184,185,185,186,186,187,187,188,188,189,189,190,190,191,191,192,
		192,193,193,194,194,195,195,196,196,197,197,198,198,199,199,200,200,201,201,202,202,203,203,204,205,205,
		206,206,207,207,208,208,209,209,210,210,211,211,212,212,213,213,214,214,215,215,216,216,217,217,218,218,
		219,219,220,220,221,221,222,222,223,223,224,224,225,225,226,226,227,227,228,228,229,229,230,231,231,232,
		232,233,233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241,242,242,243,243,244,244,245,
		245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255},
		
	//128
	{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,
		39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,
		74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,
		106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,
		132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,
		158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,
		184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,
		210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,
		236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255},
		
	//255
	{128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,139,140,140,141,
		141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,150,150,151,151,152,152,153,153,154,
		154,155,155,156,156,157,157,158,158,159,159,160,160,161,161,162,162,163,163,164,164,165,165,166,166,167,
		167,168,168,169,169,170,170,171,171,172,172,173,173,174,174,175,175,176,176,177,177,178,178,179,179,180,
		180,181,181,182,182,183,183,184,184,185,185,186,186,187,187,188,188,189,189,190,190,191,191,192,192,193,
		193,194,194,195,195,196,196,197,197,198,198,199,199,200,200,201,201,202,202,203,203,204,204,205,205,206,
		206,207,207,208,208,209,209,210,210,211,211,212,212,213,213,214,214,215,215,216,216,217,217,218,218,219,
		219,220,220,221,221,222,222,223,223,224,224,225,225,226,226,227,227,228,228,229,229,230,230,231,231,232,
		232,233,233,234,234,235,235,236,236,237,237,238,238,239,239,240,240,241,241,242,242,243,243,244,244,245,
		245,246,246,247,247,248,248,249,249,250,250,251,251,252,252,253,253,254,254,255,255}
};

static const int waveformOffset[] = {0, 256, 512, 768, 1024};

#define KEY_OFFSET	10

PROGMEM const uint32_t keyFreq[] =
{
	0x0331A ,	0x03624	,  0x0395d ,  0x03cc3 ,  0x04063 ,	//Octave 0
	0x04437 ,  0x04845 ,  0x04c92 ,  0x0511f ,  0x055f2 ,  0x05b0e ,  0x06079 ,  0x06635 ,  0x06c49 ,  0x072ba ,  0x07986 ,  0x080c6 ,  //Octave 1
	0x0886e ,  0x0908a ,  0x09924 ,  0x0a23e ,  0x0abe4 ,  0x0b61c ,  0x0c0f2 ,  0x0cc6a ,  0x0d892 ,  0x0e574 ,  0x0f30c ,  0x1018c ,  //Octave 2
	0x110dc ,  0x12114 ,  0x13248 ,  0x1447c ,  0x157c8 ,  0x16c38 ,  0x181e4 ,  0x198d4 ,  0x1b124 ,  0x1cae8 ,  0x1e618 ,  0x20318 ,  //Octave 3
	0x221b8 ,  0x24228 ,  0x26490 ,  0x288f8 ,  0x2af90 ,  0x2d870 ,  0x303c8 ,  0x331a8 ,  0x36248 ,  0x395d0 ,  0x3cc30 ,  0x40630 ,  //Octave 4
	0x44370 ,  0x48450 ,  0x4c920 ,  0x511f0 ,  0x55f20 ,  0x5b0e0 ,  0x60790 ,  0x66350 ,  0x6c490 ,  0x72ba0 ,  0x79860 ,  0x80c60 ,  //Octave 5
	0x886e0 ,  0x908a0 ,  0x99240 ,  0xa23e0 ,  0xabe40 ,  0xb61c0 ,  0xc0f20 ,  0xcc6a0 ,  0xd8920 ,  0xe5740 ,  0xf30c0 ,  0x1018c0,  //Octave 6
	0x110dc0,  0x121140,  0x132480,  0x1447c0,  0x157c80,  0x16c380,  0x181e40,  0x198d40,  0x1b1240,  0x1cae80,  0x1e6180,  0x203180,  //Octave 7
	0x221b80                                                                                                                            //Octave 8
};

#endif /* WAVETABLES_H_ */