//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/31
// saveroom by pawlo    Tue May 20 14:07:22 2003

#include <ansi.h>
inherit HERB_SHOP;
void create()
{
	set("short", "药店");
	set("long", @TEXT
药店
TEXT
);
	set("type", "herb_shop");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/29",
]));

	setup();
	replace_program(HERB_SHOP);
}
