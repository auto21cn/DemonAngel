//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/wedding.c

#include <room.h>

inherit WEDDING;

void create()
{
	set("short", "礼堂");
	set("long", @LONG
结婚的地方唷 ~~~

指令是: marry <男方> with <女方>
回答请用 answer yes

LONG
	);
	set("exits", ([
		"west" : "/d/gourd/2.c",
	]));
	setup();
	replace_program(WEDDING);
}
