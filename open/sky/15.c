//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/15
// saveroom by pawlo    Wed May 14 21:43:59 2003

#include <ansi.h>
inherit BOARD;
void create()
{
	set("short", "留言版");
	set("long", "这是一个普通的留言版。
");
	set("type", "board");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/open/sky/1",
]));

	setup();
	replace_program(BOARD);
}
