//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// rg_board.c
#include <login.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("水鸭留言板", ({ "board" }) );
	set("location", "/u/b/bor/workroom.c");
	set("board_id", "bor_board");
	setup();
	set("capacity", 150);
	replace_program(BULLETIN_BOARD);
}
