//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/obj/gift/firework.c
// by bor @DA, 3/5 2003

#include <ansi.h>

inherit ITEM;

string *color = ({
		RED"", YEL"", GRN"", BLU"", MAG"", CYN"", WHT"",
		HIR"", HIG"", HIY"", HIB"", HIM"", HIC"", HIW""
		});
string *msg = ({
		"五彩缤纷的火光在天空中散开，好美丽。\n",
		"刹那天空被七彩光芒铺满，令人眼花潦乱。\n",
		"橘红色的火焰往上直射，又爆出无数银色的带状火花。\n",
		"四射的火花又立刻各自爆开来，发出霹霹拍拍的细碎爆音。\n",
		"散放出千万朵飞焰，向四处纷飞而去，让你目不暇给。\n",
		"像一片瀑布般撒下七彩的火花，缓缓地从天顶飞旋而降。\n"
		});
void create()
{
	set_name("烟火", ({ "firework","firework" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "这是一用来庆祝的烟火，你可以点燃它(light firework)。\n");
		set("value", 1000);
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

	if(!arg) return notify_fail("你想点燃什么呢?\n");
	else if(arg=="firework") {
		msgnum = random(sizeof(msg));
		reason = msg[msgnum];
	} else if(sscanf(arg, "firework %s", reason)==1) 
		reason = "火花和爆烟在空中排出‘"+reason+"’\n";
	else return notify_fail("你想点燃什么呢?\n");

	colornum = random(sizeof(color));        

	write(color[colornum]+me->short()+"燃起火苗,\n"+"一道闪光划过天际，一个烟火‘碰’地一声在空中爆开 ...\n"+reason+NOR);
	shout(color[colornum]+me->short()+"燃起火苗,\n"+"一道闪光划过天际，一个烟火‘碰’地一声在空中爆开 ...\n"+reason+NOR);
	destruct(this_object());
	return 1;
}