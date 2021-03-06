//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/pet_shop.c
// modify /std/room/gift_shop.c
// by bor @DA, 3/12 2003

// 宠物店

inherit ROOM;

string *gift = ({
	"/d/pet/pet",
});

void reset_gift();
object find_gift(string id);

void setup()
{
	seteuid(getuid());
	reset_gift();
	::setup();
}

void init()
{
	add_action("do_list","list");
	add_action("do_buy","buy");
	add_action("do_take","take");
}

int do_list(string arg)
{
	string msg="";

	msg += "目前本宠物店贩卖(buy)的宠物如下 :\n";
	for(int i=0;i<sizeof(gift);i++)
		msg += sprintf("    %-35s %5d 枚金币  还有 %3d %s\n",
			gift[i]->short(1), gift[i]->query("value"),
			tmp_dbase["list"][gift[i]], gift[i]->query("unit"));
	this_player()->start_more(msg);
	return 1;
}

int do_buy(string arg)
{
	string file, err;
	object me = this_player(), ob;

	if(!arg) return notify_fail("你要购买什么 ?\n");
	if(!userp(me)) return 0;
	if(me->query("list/pet")) return notify_fail("你买过宠物了。\n");

	arg = lower_case(arg);

	if( !objectp(ob = find_gift(arg)) )
		return notify_fail("你要购买什么东西？\n");

	file = base_name(ob);

	if(tmp_dbase["list"][file] < 1) return notify_fail("对不起, 这只宠物已经卖完了, 请待会再来。\n");
	if(!me->can_afford(ob->query("value"))) return notify_fail("你的钱不够。\n");
	assure_file(DATA_DIR+"pet/"+me->query("id")[0..0]+"/"+me->query("id")+"_pet.c");
	cp( file+".c", DATA_DIR+"pet/"+me->query("id")[0..0]+"/"+me->query("id")+"_pet.c");
	destruct(ob);

	file = DATA_DIR+"pet/"+me->query("id")[0..0]+"/"+me->query("id")+"_pet.c";

	err = catch(ob = new(file));
	if(err) {
		write("档案制造失败 !!\n");
		return 1;
	}

	ob->set("owner", me->query("id"));
	ob->move(environment(me));
	tmp_dbase["list"][file] -= 1;
	me->pay_money(ob->query("value"));
	me->set("list/pet/file", DATA_DIR+"pet/"+me->query("id")[0..0]+"/"+me->query("id")+"_pet.c");
	me->set("list/pet/owner", me->query("id"));
	me->set("list/pet/level", ob->query("level"));
	me->set("list/pet/damage", ob->query_temp("pet/damage") );
	me->set("list/pet/armor",  ob->query_temp("pet/armor") );
	me->set("list/pet/kee",  ob->query_temp("pet/kee") );
	message_vision("$N买下了一"+ob->query("unit")+"$n。\n", me, ob);
	ob->set_leader(me);
	ob->guard_ob(me);
	return 1;
}

int do_take(string arg)
{
	object me = this_player(1), ob;
	string *list = ({});

	if(!me->query("list/pet")) return notify_fail("你尚未购买宠物。\n");
	if( !objectp( ob = find_object(me->query("list/pet/file")) ) ) {
		call_other(me->query("list/pet/file"), "???");
		ob = find_object(me->query("list/pet/file"));
	}
	if(!ob) return notify_fail("你的宠物资料似乎有点问题。\n");


	if( me->query("list/pet/damage") ) ob->set_temp("apply/damage", me->query("list/pet/damage") );
	if( me->query("list/pet/armor") ) ob->set_temp("apply/armor", me->query("list/pet/armor") );
	if( me->query("list/pet/kee") ) ob->set_temp("apply/kee", me->query("list/pet/kee") );

	if( me->query("list/pet/level") ) ob->set("level", me->query("list/pet/level") );

	if( me->query("list/pet/attr") ) {
		if( arrayp(list = me->query("list/pet/attr")) ) {
			for(int i=0; i<sizeof(list); i++) {
				ob->set(list[i], me->query("list/pet/attr/"+list[i]) );
			}
		}
	}

	CHAR_D->setup_char( ob );

	ob->move(environment(me));
	message_vision("$N兴高采烈地走了过来。\n", ob);
	ob->set("owner", me->query("id"));
	ob->set_leader(me);
	ob->guard_ob(me);
	return 1;
}

object find_gift(string id)	// 检查你输入要购买的物件是否存在
{
	object ob;

	for(int i=0; i<sizeof(gift); i++) {
		ob = new(gift[i]);
		if( id != ob->query("id") ) {
			destruct(ob);
			continue;
		}
		return ob;
	}
	return ob;
}

void reset_gift()
{
	set_temp("list", ([]));				// 先设定为 [], 方便后来设定
	for(int i=0;i<sizeof(gift);i++)
		tmp_dbase["list"][gift[i]] = 10;	// tmp_dbase 的使用方法请参考 dbase.c
	return;
}

void reset()
{
	reset_gift();
	::reset();
}
