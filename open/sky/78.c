//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/78
// saveroom by pawlo    Wed May 28 09:40:12 2003

#include <ansi.h>
inherit CHURCH;
void create()
{
	set("short", "教堂");
	set("long", @TEXT
你走进一间幽静的教堂，从屋顶上的七彩琉璃窗透入的光芒中，你隐约\n看见有些牧师正在烛光环绕的祭坛前祈祷，他们专心与心中崇拜的神衹沟通，
浑然不觉你的到来。
TEXT
);
	set("type", "church");
	set("refresh_data", ({ "pawlo", "Wed May 28 09:40:12 2003", "pawlo", "Wed May 28 09:40:12 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/75",
]));

	setup();
	replace_program(CHURCH);
}
