//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/potion/heal.c
// 这是一个 potion 继承程式

#pragma optimize
#pragma save_binary

inherit COMBINED_ITEM;

void init()
{
	add_action("do_drink", "drink");
}

int do_drink(string arg)
{
	if( !id(arg) ) return notify_fail("你要喝什么？\n");
	if(query("eat_msg")) message_vision(query("eat_msg")+"\n", this_player(), this_object());
	else message_vision("$N噜咕噜地喝下一" + query("unit") + query("name") + "。\n", this_player() );
	this_player()->receive_heal(query("kind"), query("cure"));
	add_amount(-1);
	return 1;
}

int is_potion() { return 1; }
