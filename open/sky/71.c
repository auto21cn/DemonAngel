//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/71
// saveroom by pawlo    Mon May 26 11:01:40 2003

#include <ansi.h>
inherit MISC_SHOP;
void create()
{
	set("short", "杂货店");
	set("long", @TEXT
这里是杂货店，店里摆满着各式各样冒险用的杂货货品，您可以努力的找\n找看，是否有您自己需要或是迫切需要的的东西。用 list 看看你需要的东西\n吧。
TEXT
);
	set("type", "misc_shop");
	set("refresh_data", ({ "pawlo", "Mon May 26 11:01:40 2003", "pawlo", "Mon May 26 11:01:40 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/69",
]));

	setup();
	replace_program(MISC_SHOP);
}
