//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/special/no_reborn_room.c
// by bor @DA, 3/11 2003

inherit ROOM;

void create()
{
	set("short","永不消失的密室");
	set("long",@TEXT	
这里住着一推不会死亡的恐龙 .... 黑唷黑唷 ~~~~
TEXT
	);
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}
