//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/potion/potion.c
// by bor @DA, 3/11 2003

inherit "/std/potion/heal.c";

void create()
{
	set_name("普通药水",({"hp potion","hp","potion"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","这是一瓶普通药水, 可以用来恢复体力, 你可以喝(drink)看看 !\n");
		set("base_value", 500);
		set("base_unit", "罐");
		set("base_weight", 50);
		set("unit","罐");
		set("item", "potion");
		set("kind","hp");
		set("cure",100);
	}
	setup();
}
