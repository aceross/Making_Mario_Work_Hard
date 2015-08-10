
#ifndef _CTILE_H_
	#define _CTILE_H_

#include "Define.h"


enum {
    TILE_TYPE_NONE = 0,
    TILE_TYPE_NORMAL,           // 1
    TILE_TYPE_BLOCK,            // 2
    TILE_TYPE_BLOCK_ONEWAY,     // 3
    TILE_TYPE_SLOPE_0_15_LEFT,  // 4
    TILE_TYPE_SLOPE_0_15_RIGHT  // 5
};

class CTile {
    public:
        int     TileID;
        int     TypeID;
        bool    Highlight;
    public:
        CTile();
};


#endif
