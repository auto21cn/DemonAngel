//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /d/gourd/ship_port.c
// saveroom by bor @DA, Tue Mar 11 13:11:09 2003
#include <ansi.h>
inherit PORT;

void create()
{
	set("short", "船埠");
	set("long", @LONG
港口拉 ~~~
LONG
	);
	set("type", "port");
	set("refresh_data", ({ /* sizeof() == 4 */
  "bor",
  "Wed Feb 26 01:08:10 2003",
  "bor",
  "Tue Mar 11 13:11:09 2003"
}));
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"recall_pray.c",
]));
	set("objects", ([ /* sizeof() == 2 */
  "/open/sky/ship/ship.c" : 1,
  "/open/test/ship/ship.c" : 1,
]));

	setup();
	replace_program(PORT);
}
