//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/46.c
// saveroom by pawlo @DA, Fri May 23 15:00:02 2003
#include <ansi.h>
inherit BARRACKS;

void create()
{
	set("short", "军营");
	set("long", @LONG
你走近一座军部的大门，几个持矛的士兵正在木寨围成的拒马前站着，
你可以看见军部门前的一张木牌上贴了一张布告，上面写着有关从军募兵和
近期发生的事情。向北你可以看见一片操场，象征着军纪的军旗正在操场上
飘扬着。犹克多皇家军队不单只在战争时才上战场杀敌，就是在平日，也会
努力维持国家治安．要是有人犯案，军人们还是会照捕不误的。
LONG
	);
	set("type", "barracks");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Fri May 23 14:51:27 2003",
  "pawlo",
  "Fri May 23 15:00:02 2003"
}));
	set("data", ({ /* sizeof() == 1 */
  __DIR__"npc/8"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"38",
]));

	setup();
	replace_program(BARRACKS);
}
