//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/bank.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit ROOM;

void init()
{
	add_action("do_deposit", "deposit");
	add_action("do_withdraw", "withdraw");
	add_action("do_transfer", "transfer");
}

int do_deposit(string arg)
{
	int amount;
	object me = this_player();

	seteuid(getuid());
	if( me->is_busy()) return notify_fail("你现在正忙着。\n");
	if( !arg || sscanf(arg, "%d", amount)!=1 ) return notify_fail("格式 : deposit <多少钱>\n");
	if( amount < 0 ) return notify_fail("抱歉目前没有开放借贷的事宜。\n");
	if( amount == 0 ) return notify_fail("你把 "+amount+" 枚金币存进银行。\n");
	if( !me->deposit_bank(amount) ) return notify_fail("你身上没有这么多钱。\n");

        write("你把 "+amount+" 枚金币存进银行。\n");
	if(amount>100000) log_file("bank",sprintf("[%s] %s[%s] deposit %d 枚金币 <%s>。\n",
		ctime(time())[0..15], geteuid(me), me->query("kingdom/id"), amount,
		query_ip_name(me)));
	me->save();
        return 1;
}

int do_withdraw(string arg)
{
	int amount;
	object me=this_player();

	seteuid(getuid());
	if( !arg || sscanf(arg, "%d", amount)!=1 ) return notify_fail("格式 : withdraw <多少钱>\n");
	if( amount < 0) return notify_fail("抱歉目前没有开放借贷的事宜。\n");
	if( amount == 0 ) return notify_fail("你从银行提出 "+amount+" 枚金币。\n");
        if( !me->withdraw_bank(amount) ) return notify_fail("你银行内没有那么多钱。\n");

	write("你从银行提出 "+amount+" 枚金币。\n");
	if(amount>100000) log_file("bank",sprintf("[%s] %s[%s] withdraw %d 枚金币 <%s>。\n",
		ctime(time())[0..15], geteuid(me), me->query("kingdom/id"), amount,
		query_ip_name(me)));
	me->save();
	return 1;
}

int do_transfer(string arg)
{
	object me = this_player(), ob;
	string id;
	int flag =1, amount;

	if(!arg) return notify_fail("格式: transfer <玩家> <多少钱>\n");
	if( sscanf(arg, "%s %d", id, amount)!=2 ) return notify_fail("格式: transfer <玩家> <多少钱>\n");
	if( !(ob = find_player(id))) {
		ob = load_player(id);
		flag = -1;
	}
	if(!ob) return notify_fail("找不到这个玩家。\n");
	if( amount < 1 ) return notify_fail("抱歉目前没有开放借贷的事宜。\n");
	if( me->query("bank_gold")<amount ) return notify_fail("你银行内没有这么多钱。\n");
	ob->add("bank_gold", amount);
	ob->save();
	me->add("bank_gold", -amount);
	me->save();
	message_vision("$N从银行转出 "+amount+" 枚金币给$n。\n", me, ob);
	if(flag ==-1) destruct(ob);
	return 1;
}
