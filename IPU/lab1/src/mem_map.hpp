#ifndef src/mem_map_hpp_INCLUDED
#define src/mem_map_hpp_INCLUDED

enum mem_map_addr {
	TMR_TM1    = 0x0,
	TVAL_TM1   = 0x4,
	TCONF_TM1  = 0x8,
	TMR_TM2    = 0xC,
	TVAL_TM2   = 0x10,
	TCONF_TM2  = 0x14,
	OCCONF_OC  = 0x18,
	OCR_OC 	   = 0x1C
};

#endif // src/mem_map_hpp_INCLUDED
