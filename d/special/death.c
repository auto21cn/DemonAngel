//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/special/death.c

#include <login.h>
inherit ROOM;

void create()
{
	set("short", "地府");
	set("long", @LONG
这里是死者聚集之地，有多少死者呢？有....这么多，吓人吧 ~~~
LONG
	);
	set("exits", ([
		"out" : START_ROOM
	]) );
	setup();
	replace_program(ROOM);
}
