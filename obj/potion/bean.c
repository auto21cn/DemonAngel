//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/potion/bean.c
// by bor @DA, 3/11 2003

inherit "/std/potion/bean_eat.c";

void create()
{
	set_name("马豆",({"bean"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","这是一把给坐骑吃的马豆，可以增强不少体力 !\n");
		set("base_value", 300);
		set("base_unit", "把");
		set("base_weight", 30);
		set("unit","把");
		set("item", "potion");
		set("kind","kee");
		set("cure", 60);
	}
	setup();
}
