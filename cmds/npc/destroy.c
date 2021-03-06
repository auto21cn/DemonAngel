//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/destroy.c
// by bor @DA, 3/7 2003
// actionroom 在被破坏后，怎么打开 action ? 有空想想吧
// 

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
inherit "/cmds/min/declare";			// 给攻破王座使用

#include <ansi.h>

int main(object me, string arg)
{
	string id, enemy_id;
	object env, ob, *inv;
	int money;

	seteuid(getuid());
	if(arg) return notify_fail("你不能破坏那个东西!!\n");
	if(!(id= me->query("kingdom/id"))) return notify_fail("无国籍不能乱破坏。\n");
	if(!objectp(env = environment(me))) return notify_fail("这里的环境属于空虚。\n");
	if( !(enemy_id = env->query("kingdom_id")) ) return notify_fail("这里是系统的区域 !!");
	if( enemy_id == id ) return notify_fail("你想叛国吗 ?\n");
	if(!kingdom_data(id, "war", "check")) return notify_fail("贵国目前没有任何一场战争发生!!\n");
	if(!kingdom_data(id, "war", "check", enemy_id, 1)) return notify_fail("贵国没有和该国家战争。\n");
	if(env->query_temp("destroy")) return notify_fail("这里已经被破坏一空。\n");

	if( env->query("type")=="normal"&&env->query("no_delete")==1 ) { // 如果该房间为王座
		if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
		if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");

		// 如果王座有 guard , 那么就限制敌人不能破坏的话
		inv = all_inventory(env);
		for(int i=0; i<sizeof(inv); i++) { // 检查该房间是否有敌人的 mob，若有则不能破坏
			if( inv[i]->query("kingdom")&& kingdom_data(id, "war", "check", inv[i]->query("kingdom"), 1) )
				return notify_fail("这里还有敌人存在, 无法焚烧建筑物!!\n");
		}

		message_vision("[1;30m$N拿起火把将这里焚烧殆尽。[m\n", me);
		money = 1300 + random(500);
		message_vision("[1;30m$N尽情的到处搜刮, 搜出 "+money+" 枚金币。[m\n", me);
		env->add_temp("destroy_normal", 1); // 每次增加一，直到 5，就被迫停战
		me->got_money(money);
		me->add("war_score/gold", money);

		kingdom_data(id, "war", "add", enemy_id, ({"gold", money}));
		kingdom_data(enemy_id, "war", "add", id, ({"gold_", money}));

		kingdom_data(enemy_id, "data", "sub", "gold", money);

		for(int i=0;i<2;i++) {
			// 根据基本的守卫出来, 顺便看要补啥资讯... 例如, 你可以依照各国家的某发展来决定出 npc 的 level
			// 都可以在此补进去
			ob = new("/d/obj/npc/guard_1.c");
			ob->set("kingdom", enemy_id);
			ob->move(env);
		}
		message_vision("$N从王座内冲出来，保护最后的防线。\n", ob);
		if( env->query_temp("destroy_normal")>=5 ) {
			env->set_temp("destroy", 1);
			me->add("war_score/building", 1);
			kingdom_data(id, "war", "add", enemy_id, ({"building",1}) );
			kingdom_data(enemy_id, "war", "add", id, ({"building_",1}) );

			shout(HIR+full_kingdom(id)+"强行攻陷"+full_kingdom(enemy_id)+"的王座"+NOR+"\n\n");
			write(HIR+full_kingdom(id)+"强行攻陷"+full_kingdom(enemy_id)+"的王座"+NOR+"\n\n");
			call_out("do_wait_war_end", 0, id, enemy_id);
		}
//	} else if() {	// 特殊建筑物的判定, 目前不提供, 请有空自己补进去
	} else {	// 其他的一般房间
		env->set_temp("destroy", 1);
		message_vision("[1;30m$N拿起火把将这里焚烧殆尽。[m\n", me);
		kingdom_data(id, "war", "add", enemy_id, ({"room",1}) );
		kingdom_data(enemy_id, "war", "add", id, ({"room_",1}) );
		me->add("war_score/room", 1);
	}
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : destroy

这是摧毁交战国建筑物的指令，当你下了这个指令，对方的建筑物会依其防
御程度进行反击，甚至还会有各种生物出来攻击你。不过，只要你能克服一
切障碍，你就可以对方的建筑物损坏，并且搜刮到一大笔钱。摧毁建筑物会
帮你的国家大量提升战胜点数，并且使敌方的国力蒙受损失，当然，你的战
绩和战功也会大大的记上一笔。

另外，敌人所建造房间也可以用这个指令清除，只是没有战功也搜不到钱。
这些非建筑物的房间被摧毁后不能修复，在下一次 reboot 后就会恢复正常。

当你斩杀敌人或摧毁敌方建筑物后, 你会增加你的战争经验, 这些经验可能
会对你的能力提升有所帮助。你可以在国内的英雄会馆利用 show 来查询你
所累积的战争经验。

如果你的建筑在战争中被摧毁，你可以用 set_room 中的 repair 的参数把
建筑修好。

相关讯息 : kill, kingdoms, declare, set_room

HELP
	);
	return 1;
}
