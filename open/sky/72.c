//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/72.c
// saveroom by pawlo @DA, Mon May 26 16:08:31 2003
#include <ansi.h>
inherit TRAINYARD;

void create()
{
	set("short", "训练听");
	set("long", @LONG
这里是一个充斥着汗水与呼喊声的训练厅, 宽敞的大厅里是一个方形\\n的广场, 有许\多人正在场上卖力地锻练着, 呼喊声与刀剑撞击声不断传来\\n, 广场边堆满了一些训练道具和武器装备, 几个看起来像是教练模样的人
正站在场边对着场上的人指指点点。你可以在这里训练(train)技能、提\\n升(advance)等级、查看(list)技能种类和训练所需代价(cost)。
LONG
	);
	set("type", "trainyard");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 16:08:21 2003",
  "pawlo",
  "Mon May 26 16:08:31 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "up" : __DIR__"73",
  "down" : __DIR__"kingdom",
]));

	setup();
	replace_program(TRAINYARD);
}
