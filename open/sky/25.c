//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/25
// saveroom by amgbell    Mon May 19 21:51:07 2003

#include <ansi.h>
inherit SHOP;
void create()
{
	set("short", "商店");
	set("long", @TEXT这是一间商店你可以 sell 商品。
TEXT
);
	set("type", "shop");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/open/sky/24",
]));

	setup();
	replace_program(SHOP);
}
