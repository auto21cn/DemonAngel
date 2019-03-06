//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/obj/gift/fairy_firework.c
// by bor @DA, 3/5 2003

#include <ansi.h>

inherit ITEM;

string *color = ({
		RED"", YEL"", GRN"", BLU"", MAG"", CYN"", WHT"",
		HIR"", HIG"", HIY"", HIB"", HIM"", HIC"", HIW""
		});
string *msg = ({
		"五彩缤纷的火光在四周呼明呼暗，闪烁不已。\n",
		"刹那周围被七彩亮光照射，令人眼花潦乱。\n",
		});
void create()
{
	set_name(HIW"仙女棒"NOR, ({ "fairy firework","firework","fairy" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "这一根是小朋友在玩的仙女棒，点火(light firework)下去就会有很多火花。\n");
		set("value", 200);
	}
	setup();
}
void init()
{
	if(userp(this_player())) add_action("do_light","light");
}

int do_light(string arg)
{
	string reason="";
	object me;
	int colornum, msgnum;

	me = this_player();

	if(!arg || !id(arg) ) return notify_fail("你想点燃什么呢?\n");

	msgnum = random(sizeof(msg));
	reason = msg[msgnum];

	colornum = random(sizeof(color));        

	message_vision(color[colornum]+"$N点燃$n, "+color[random(sizeof(color))]+reason+NOR, me, this_object());
	destruct(this_object());
	return 1;
}
