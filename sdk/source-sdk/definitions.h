#pragma once

#define MULTIPLAYER_BACKUP 90

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)
#define IN_SPEED		(1 << 17)
#define IN_WALK			(1 << 18)
#define IN_ZOOM			(1 << 19)
#define IN_WEAPON1		(1 << 20)
#define IN_WEAPON2		(1 << 21)
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)
#define IN_GRENADE2		(1 << 24)

#define FL_ONGROUND             (1 << 0)
#define FL_DUCKING              (1 << 1)
#define FL_ANIMDUCKING          (1 << 2)
#define FL_WATERJUMP            (1 << 3)
#define FL_ONTRAIN              (1 << 4)
#define FL_INRAIN               (1 << 5)
#define FL_FROZEN               (1 << 6)
#define FL_ATCONTROLS           (1 << 7)
#define FL_CLIENT               (1 << 8)
#define FL_FAKECLIENT           (1 << 9)
#define FL_INWATER              (1 << 10)
#define FL_FLY                  (1 << 11)
#define FL_SWIM                 (1 << 12)
#define FL_CONVEYOR             (1 << 13)
#define FL_NPC                  (1 << 14)
#define FL_GODMODE              (1 << 15)
#define FL_NOTARGET             (1 << 16)
#define FL_AIMTARGET            (1 << 17)
#define FL_PARTIALGROUND        (1 << 18)
#define FL_STATICPROP           (1 << 19)
#define FL_GRAPHED              (1 << 20)
#define FL_GRENADE              (1 << 21)
#define FL_STEPMOVEMENT         (1 << 22)
#define FL_DONTTOUCH            (1 << 23)
#define FL_BASEVELOCITY         (1 << 24)
#define FL_WORLDBRUSH           (1 << 25)
#define FL_OBJECT               (1 << 26)
#define FL_KILLME               (1 << 27)
#define FL_ONFIRE               (1 << 28)
#define FL_DISSOLVING           (1 << 29)
#define FL_TRANSRAGDOLL         (1 << 30)
#define FL_UNBLOCKABLE_BY_PLAYER (1u << 31)

#define HITGROUP_GENERIC	0
#define HITGROUP_HEAD		1
#define HITGROUP_CHEST		2
#define HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10

#define MOVETYPE_NONE		0	
#define MOVETYPE_ISOMETRIC	1
#define MOVETYPE_WALK		2	
#define MOVETYPE_STEP		3	
#define MOVETYPE_FLY		4	
#define MOVETYPE_FLYGRAVITY	5
#define MOVETYPE_VPHYSICS	6
#define MOVETYPE_PUSH		7
#define MOVETYPE_NOCLIP		8
#define MOVETYPE_LADDER		9
#define MOVETYPE_OBSERVER	10
#define MOVETYPE_CUSTOM		11

#define MAX_STUDIO_BONES 256

#define NUM_BYTES 256
#define CRC32_INIT_VALUE 0xFFFFFFFFUL
#define CRC32_XOR_VALUE  0xFFFFFFFFUL
#define MD5_DIGEST_LENGTH 16  
#define MD5_BIT_LENGTH ( MD5_DIGEST_LENGTH * sizeof(unsigned char) )

#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) F1(z, x, y)
#define F3(x, y, z) (x ^ y ^ z)
#define F4(x, y, z) (y ^ (x | ~z))

#define MD5STEP(f, w, x, y, z, data, s) ( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )

#define RTL_NUMBER_OF_V2(A) (sizeof(*RtlpNumberOf(A))+0)
#define ARRAYSIZE(A)    RTL_NUMBER_OF_V2(A)
#define _ARRAYSIZE(A)   RTL_NUMBER_OF_V1(A)
#define Q_ARRAYSIZE(p)		ARRAYSIZE(p)

#define Q_BINARYTOHEX v_binarytohex

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100

#define DISPSURF_FLAG_SURFACE           (1<<0)
#define DISPSURF_FLAG_WALKABLE          (1<<1)
#define DISPSURF_FLAG_BUILDABLE         (1<<2)
#define DISPSURF_FLAG_SURFPROP1         (1<<3)
#define DISPSURF_FLAG_SURFPROP2         (1<<4)

#define CONTENTS_EMPTY                0

#define CONTENTS_SOLID                0x1       
#define CONTENTS_WINDOW               0x2
#define CONTENTS_AUX                  0x4
#define CONTENTS_GRATE                0x8
#define CONTENTS_SLIME                0x10
#define CONTENTS_WATER                0x20
#define CONTENTS_BLOCKLOS             0x40 
#define CONTENTS_OPAQUE               0x80 
#define LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME        0x100
#define CONTENTS_UNUSED               0x200     
#define CONTENTS_BLOCKLIGHT           0x400
#define CONTENTS_TEAM1                0x800 
#define CONTENTS_TEAM2                0x1000 
#define CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define CONTENTS_MOVEABLE             0x4000
#define CONTENTS_AREAPORTAL           0x8000
#define CONTENTS_PLAYERCLIP           0x10000
#define CONTENTS_MONSTERCLIP          0x20000
#define CONTENTS_CURRENT_0            0x40000
#define CONTENTS_CURRENT_90           0x80000
#define CONTENTS_CURRENT_180          0x100000
#define CONTENTS_CURRENT_270          0x200000
#define CONTENTS_CURRENT_UP           0x400000
#define CONTENTS_CURRENT_DOWN         0x800000

#define CONTENTS_ORIGIN               0x1000000 

#define CONTENTS_MONSTER              0x2000000 
#define CONTENTS_DEBRIS               0x4000000
#define CONTENTS_DETAIL               0x8000000 
#define CONTENTS_TRANSLUCENT          0x10000000
#define CONTENTS_LADDER               0x20000000
#define CONTENTS_HITBOX               0x40000000

#define SURF_LIGHT                    0x0001 
#define SURF_SKY2D                    0x0002 
#define SURF_SKY                      0x0004 
#define SURF_WARP                     0x0008 
#define SURF_TRANS                    0x0010
#define SURF_NOPORTAL                 0x0020 
#define SURF_TRIGGER                  0x0040 
#define SURF_NODRAW                   0x0080 

#define SURF_HINT                     0x0100 

#define SURF_SKIP                     0x0200   
#define SURF_NOLIGHT                  0x0400   
#define SURF_BUMPLIGHT                0x0800   
#define SURF_NOSHADOWS                0x1000   
#define SURF_NODECALS                 0x2000   
#define SURF_NOPAINT                  SURF_NODECALS
#define SURF_NOCHOP                   0x4000   
#define SURF_HITBOX                   0x8000   

#define MASK_ALL                      (0xFFFFFFFF)
#define MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

#define MAT_ANTLION			65
#define MAT_BLOODYFLESH		66
#define MAT_CONCRETE		67
#define MAT_DIRT			68
#define MAT_EGGSHELL		69
#define MAT_FLESH			70
#define MAT_GRATE			71
#define MAT_ALIENFLESH		72
#define MAT_CLIP			73
#define MAT_SNOW			74
#define MAT_PLASTIC			76
#define MAT_METAL			77
#define MAT_SAND			78
#define MAT_FOLIAGE			79
#define MAT_COMPUTER		80
#define MAT_SLOSH			83
#define MAT_TILE			84
#define MAT_GRASS			85
#define MAT_VENT			86
#define MAT_WOOD			87
#define MAT_DEFAULT			88
#define MAT_GLASS			89
#define MAT_WARPSHIELD		90