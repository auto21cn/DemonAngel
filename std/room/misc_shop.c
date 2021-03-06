//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/misc_shop.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit ROOM;

private string *got_list( string dir );
private void reset_list();
private object find_list(string id);

void setup()
{
	seteuid(getuid());
	reset_list();
	::setup();
}

void init()
{
	add_action("do_list","list");
	add_action("do_buy","buy");
}

private int do_list(string arg)
{
	string msg="", *str, *list=({});

	msg += "目前提供的商品如下, 欢迎购买(buy):\n";

	list = got_list( "/obj/misc_shop/" );

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		msg += sprintf("    %-35s %5d 枚金币  还有 %3d %s\n",
			list[i]->short(1), list[i]->query("value"),
			tmp_dbase["list"][list[i]], list[i]->query("unit"));
	this_player()->start_more(msg);
	return 1;
}

private string *got_list( string dir )
{
	string *str, *list=({});

	str = get_dir(dir);
	for(int i=0;i<sizeof(str);i++) {
		if( file_size( dir+str[i] )<0 ) continue;
		if( member_array( dir+str[i], list) != -1 ) continue;
		list += ({ dir+str[i] });
	}
	return list;
}

private int do_buy(string arg)
{
	int count = 1;
	string id, file;
	object ob;

	if(!arg) return notify_fail("你要买什么 ?\n");
	if(sscanf(arg,"%d %s", count, id) != 2) id = arg;

	if( !objectp(ob = find_list(id)) )
		return notify_fail("你要买什么东西？\n");

	file = full_name(ob);

	for(int i=0; i<count; i++) {
		if(tmp_dbase["list"][file] < 1) return notify_fail("对不起, 这样东西已经卖完了, 请待会再来。\n");
		if( ob->query("base_value") )
			if(!this_player()->can_afford(ob->query("base_value"))) return notify_fail("你的钱不够。\n");
		else 
			if(!this_player()->can_afford(ob->query("value"))) return notify_fail("你的钱不够。\n");
		if(!ob->move(this_player())) {
			destruct(ob);
			return notify_fail("你拿不动了.\n");
		}
		tmp_dbase["list"][file] -= 1;
		if( ob->query("base_value") )
			this_player()->pay_money(ob->query("base_value"));
		else this_player()->pay_money(ob->query("value"));
		message_vision("$N买下了一"+ob->query("unit")+"$n。\n",this_player(), ob);
	}
	return 1;
}

private object find_list(string id)	// 检查你输入要购买的物件是否存在
{
	string *list;
	object ob;

	list = got_list( "/obj/misc_shop/" );

	if( sizeof(list)>0 )
	for(int i=0; i<sizeof(list); i++) {
		ob = new(list[i]);
		if( id != ob->query("id") ) {
			destruct(ob);
			continue;
		}
		return ob;
	}
	return 0;
}

private void reset_list()
{
	string *list;
	list = got_list( "/obj/misc_shop/" );
	set_temp("list", ([]));				// 先设定为 [], 方便后来设定

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		tmp_dbase["list"][list[i]] = 30;	// tmp_dbase 的使用方法请参考 dbase.c
	return;
}
