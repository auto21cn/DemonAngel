//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/medicine/heal.c
// by bor @RG, DA

inherit COMBINED_ITEM;

void init()
{
	add_action("do_drink", "drink");
}

int do_drink(string arg)
{
	object ob;
	if( !id(arg) ) return notify_fail("你要喝什么？\n");
	if( !ob = present(arg, this_player()) ) return notify_fail("你要喝什么？\n");
	this_player()->receive_heal(query("type"), query("heal"));
	message_vision("$N咕噜咕噜地喝下一"+query("unit") + "$n。\n", this_player(), ob);
	add_amount(-1);
	return 1;
}
