//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// taoist_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("茅山派留言板", ({ "board" }) );
	set("location", "/d/temple/temple1");
	set("board_id", "taoist_b");
	set("long",
		"这是供茅山派弟子留言记事的留言板。\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
