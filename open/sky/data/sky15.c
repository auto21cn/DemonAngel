//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : KINGDOM_DIR+id+/data/sky15
// saveroom by pawlo    Wed May 14 21:43:59 2003

#include <ansi.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("留言板", ({ "board" }) );
	set("location", "/open/sky/15");
	set("board_id", "sky15");
	setup();
	set("capacity", 70);
	replace_program(BULLETIN_BOARD);
}