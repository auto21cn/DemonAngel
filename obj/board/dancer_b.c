//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// dancer_b.c

inherit BULLETIN_BOARD;

void create()
{
	set("board_id", "dancer_b");
	set("location", "/d/latemoon/latemoon1" );
	setup();
	set_name("沐花镜屏", ({ "mirror" }) );
	set("long",
		"这是一面有一个人高的镜屏，有着古藤缠绕着的红木镜框，上面还缀着\n"
		"一些刚采来的鲜花，你看着镜中的自己，有如站在花丛之中，晚月庄的\n"
		"女子喜欢将自己的心事写成纸条绑在镜框上。\n");
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
