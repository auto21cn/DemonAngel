//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/special/relax.c
// by bor @DA, 2/22/2003

inherit ROOM;

void create()
{
	set("short","休息室");
	set("long",@TEXT
公共休息的地方，不过还是不要乱丢烟蒂唷。
TEXT
	);
	setup();
	replace_program(ROOM);
}

