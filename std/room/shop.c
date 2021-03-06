//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/shop.c
// by bor @DA

inherit ROOM;

#define SHOP_ROOM		"/d/special/recall_shop.c"
static object shop;

int do_sell_object(object me, object ob);
int is_shop() { return 1; }

void setup()
{
	::setup();
	seteuid(getuid());
	if( !shop = find_object(SHOP_ROOM) ) {
		call_other( SHOP_ROOM, "???" );
		shop = find_object(SHOP_ROOM);
	}
	if( !shop ) shop = new(SHOP_ROOM);
}

void init()
{
	add_action("do_sell", "sell");
	add_action("do_list", "list");
	add_action("do_buy", "buy");
	add_action("do_try", "try");
	add_action("do_value", "value");
}

int do_list(string arg)
{
	object *all;
	string msg;

	if( !shop ) return notify_fail("商店目前没有任何物品。\n");
	if( zerop(all = all_inventory(shop)) ) return notify_fail("商店目前没有任何物品。\n");

	msg = "商店目前贩售的物品有如下：\n";
	msg += implode( map_array(all, (: sprintf("%-50s%s", $1->short(), "价格 "+(string)$1->query("value")+" 枚金币。" ) :)), "\n  ");
	msg += "\n";
	reset_eval_cost();
	this_player()->start_more(msg);
	return 1;
}

int do_sell(string arg)
{
	object me = this_player(), ob;
	int value, gold;

	if( !arg ) return notify_fail("你要卖断什么物品？\n");
	if( arg=="all" ) {
		object *inv;
		inv = all_inventory(me);
		if( sizeof(inv) )
		foreach(ob in inv) {
			if(!objectp(ob)) continue;
			if(ob->query("equipped")) continue;
			do_sell_object(me, ob);
		}
		write("Ok。\n");
		return 1;
	}
	if( !(ob = present(arg, me)) ) return notify_fail("你要卖断什么物品？\n");
	do_sell_object(me, ob);
	write("Ok。\n");
	return 1;
}

int do_sell_object(object me, object ob)
{
	int value, gold;

	if(ob->query("equipped")) {
		write("这件物品正装备着，无法贩售。\n");
		return 0;
	}
	if( ob->query("money_id") ) return 0;

	value = ob->query("value");
	if( !value ) return notify_fail("这样东西不值钱。\n");

	gold = value*4/5;

	if( ob->is_corpse() ) gold = 1;

	message_vision("$N把身上的$n卖掉, 得到 "+gold+" 枚金币。\n", me, ob);

	if( ob->is_corpse() ) destruct(ob);
	if( !userp(me) ) gold = gold/10;
	me->got_money(gold);
	if( objectp(ob) ) ob->direct_move(SHOP_ROOM);
	return 1;
}

int do_buy(string arg)
{
	object *all;
	int flag = -1, value;

	if( !shop ) return notify_fail("你要买什么物品？\n");
	if( zerop(all = all_inventory(shop)) ) return notify_fail("商店目前没有你需要的物品。\n");
	for(int i=0; i<sizeof(all); i++) {
		if( !all[i]->id(arg) ) continue;
		flag = i;
		break;
	}
	if( flag == -1 ) return notify_fail("这里没有你需要的物品。\n");
	else {
		value = all[flag]->query("value");
		// 记得预留 mob 可以来商店购买物品
		if( userp(this_player()) )
		if( !(this_player()->can_afford(value) ) ) return notify_fail("你身上的钱不够。\n");
		if( !all[flag]->move(this_player()) ) return notify_fail("你身体负荷不了，没办法继续购买。\n");
		if(userp(this_player())) {
			this_player()->pay_money(value);
			this_player()->save();
		}
		message_vision("$N买下了一"+all[flag]->query("unit")+"$n。\n", this_player(), all[flag]);
		reset_eval_cost();
	}
	return 1;
}

int do_try(string arg)
{
	object *all, me = this_player();
	int flag=-1;

	if(!arg) return notify_fail("你要试什么 ?\n");
	if( zerop(all = all_inventory(shop)) ) return notify_fail("本店没有这种东西 !\n");
	for(int i=0; i<sizeof(all); i++) {
		if( !all[i]->id(arg) ) continue;
		flag = i;
		break;
	}
	if( flag == -1 ) return notify_fail("本店没有这种东西 !\n");
	if( all[flag]->query("skill_type") ) {
		if( all[flag]->query("skill") && all[flag]->query("skill")> me->query_skill(all[flag]->query("skill_type"),1) )
			tell_object(me, "你拿起"+all[flag]->query("name")+"看了一看，但是你"+
				to_chinese(all[flag]->query("skill_type"))+"的技能还不足以使用这种武器。\n");
		return 1;
	} else if( all[flag]->query("armor_type") ) {
		if( all[flag]->query("level")> me->query("level") )
			tell_object(me, "你拿起"+all[flag]->query("name")+"看了一看，但是你的等级还不足以使用这种防具。\n");
		return 1;
	}
	tell_object(me, "你拿起"+all[flag]->query("name")+"看了一看，满意的点点头。\n");
	return 1;
}

int do_value(string arg)
{
	object me = this_player(), ob;

	if( !arg || !(ob = present(arg, me)) ) return notify_fail("你要拿什么物品给老板估价？\n");
	tell_object( me, ob->name_id()+"价值 "+ob->query("value")+" 枚金币。如果要卖(sell)，可以拿到 "+ob->query("value")*4/5+" 枚金币。\n");
	return 1;
}
