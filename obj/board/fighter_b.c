//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// fighter_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("武者留言板", ({ "board" }) );
	set("location", CLASS_D("fighter") + "/guildhall");
	set("board_id", "fighter_b");
	set("long",	"这是供武林中人留言记事的留言板。\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
