//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// mob1.c

inherit MISC_SHOP_NPC;

void create()
{
	set_name("商人", ({ "man" }) );
	set("con", 20);
	set("level", 1);

	set("long", "我是一个商人, 要买东西找我吧!!\n");

	setup();
}
