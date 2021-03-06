//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/teleport.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, obj_env;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("你要飞奔到哪？\n");

	obj = find_player(arg);
	if( !obj ) return notify_fail("没有这个玩家或不在线上。\n");
	if( obj==me ) return notify_fail("指令格式：teleport <国民>\n");
	if(!me->query("kingdom/id") ) return 0;

	if( !obj->query("kingdom/id")
	|| obj->query("kingdom/id") != me->query("kingdom/id") )
		return notify_fail("他不是本国国民。\n");

	if(!obj_env = environment(obj)) return notify_fail("他的环境已经消失，无法过去。\n");
	if( obj_env->query("no_teleport") ) return notify_fail("对方所在的地方不准 teleport。\n");

	message_vision("只见一阵烟雾过后，$N的身影已经不见了。\n", me);
	me->move(obj_env);
	message("vision","一阵烟雾过"+me->name_id(1)+"的身影出现在你面前。\n", environment(me), ({me}) );
	return 1;
}

int help()
{
	write(@HELP

指令格式：teleport <国民>

这是国王专用的瞬间传送指令, 可以传送到他的任何一个人民的所在，只要他
的环境没有设定 no_teleport 都可以立刻前往。

HELP
	);
	return 1;
}
