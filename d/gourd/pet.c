//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/pet.c

#include <room.h>

inherit PET_SHOP;

void create()
{
	set("short", "宠物专门店");
	set("long", @LONG
好多宠物提供给你购买。
LONG
	);
	set("exits", ([
		"east" : "/d/gourd/3.c",
	]));
	setup();
	replace_program(PET_SHOP);
}
