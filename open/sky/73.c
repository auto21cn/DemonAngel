//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/73
// saveroom by pawlo    Mon May 26 16:08:31 2003

#include <ansi.h>
inherit MAGIC_TOWER;
void create()
{
	set("short", "法术研习营");
	set("long", @TEXT
这里是一个安静明亮的研习室, 研习室的正中有一张长条桌, 两旁则是
直达屋顶的书架, 架上摆了画满各式奇怪符号的书籍, 大部份是有关魔法的,
在这里, 你可以翻看看(list)有什么适合你目前程度的法术可学, 也可以静
下心来研习(study)法术。
TEXT
);
	set("type", "magic_tower");
	set("refresh_data", ({ "pawlo", "Mon May 26 16:08:31 2003", "pawlo", "Mon May 26 16:08:31 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "down" : "/open/sky/72",
]));

	setup();
	replace_program(MAGIC_TOWER);
}
