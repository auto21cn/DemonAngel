//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/42
// saveroom by pawlo    Fri May 23 08:23:10 2003

#include <ansi.h>
inherit STABLE;
void create()
{
	set("short", "马厩\");
	set("long", @TEXT
你走进一间充满了草料香味的马插A到处可以看到一些壮硕高大强壮的
马。整个马斑Q一条走道分开，走道两旁被分成一格格的，有的养了马，有
的还空着。有几个工人正拉着堆着草料的车子，把草料铲进马面前的食槽里
，马的喷气声和嘶鸣声此起彼落，这里的马儿都是来自远古流传下来的最强
悍的马种，想要骑这些马儿的人势必首先要能自己去驯服他们，否则马儿是
不会承认您是牠的主人的。
TEXT
);
	set("type", "stable");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/38",
]));

	setup();
	replace_program(STABLE);
}
