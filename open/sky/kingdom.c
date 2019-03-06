//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/kingdom.c
// saveroom by amgbell @DA, Wed May 28 19:31:37 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "天空王座");
	set("long", @LONG
王座是国家最重要的地方，也是国家的精神象征，平时国王与大
臣们谈论国家重要政策的最佳场所，王座的存在与否关系着国家能不
能存在，所谓座在国在，座亡国亡，希望国民能好好保护这里。
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sun Mar 09 20:23:57 2003",
  "amgbell",
  "Wed May 28 19:31:37 2003"
}));
	set("kingdom_id", "sky");
	set("objects", ([ /* sizeof() == 4 */
  __DIR__"npc/16" : 1,
  __DIR__"npc/18" : 1,
  __DIR__"npc/19" : 1,
  __DIR__"npc/17" : 1,
]));
	set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"26",
  "west" : __DIR__"18",
  "east" : __DIR__"1",
  "up" : __DIR__"72",
]));
	set("no_delete", 1);

	setup();
	replace_program(ROOM);
}
