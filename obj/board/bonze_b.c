//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// bonze_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("缘法轮", ({ "wheel" }) );
	set("location", "/d/sanyen/temple" );
	set("board_id", "bonze_b");
	set("long",
		"这是一个黄铜铸成的法轮，从它上面斑驳的铜绿痕迹可以看出它的年代已经\n"
		"相当久远了，缘法轮旁边放着一本册子供寺中僧人或香客留言。\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
