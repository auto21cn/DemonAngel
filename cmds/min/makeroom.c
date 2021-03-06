//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/makeroom.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#define ROOM_MONEY	500

int main(object me,string arg)
{
	object env;
	int num;
	string new_file, new_arg, str;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式：makeroom <方向>\n");
	if( !env = environment(me)) return notify_fail("找不到环境。\n");
	if( !me->query("kingdom/id") || !env->query("kingdom_id")
	|| env->query("kingdom_id") != me->query("kingdom/id")
	) return notify_fail("这里不是贵国的土地。\n");
	if( arg != "north" && arg != "south" && arg != "east" && arg != "west" && arg != "down" && arg != "up" ) return notify_fail("没有这个方向。\n");
	if( env->query("exits/"+arg) ) return notify_fail("这个方向已经有连接房间了。\n");
	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "room") >= kingdom_data(me->query("kingdom/id"), "data", "query_par", "max_room") ) return notify_fail("贵国房间上限已额满，请删除不必要的房间再建。\n");
	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < ROOM_MONEY ) return notify_fail("贵国国库金额不足。\n");

	// 我用实际房间数和房间流水号的总和作为下一间房间档名的依据
	num = kingdom_data(me->query("kingdom/id"), "data", "query_par", "room")
		+ kingdom_data(me->query("kingdom/id"), "data", "query_par", "room_num");

	new_file = KINGDOM_DIR+me->query("kingdom/id")+"/"+(string)num;

	if( file_size(new_file+".c")!=-1) return notify_fail("这个档案已经有了，请找管理者修改。\n");

	new_arg = inverse_dir(arg);

	str = "// room : " + new_file + ".c\n";
	str += "// saveroom by "+ me->query("id")+"    "+ctime(time())+"\n\n";
	str += @ROOM
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "空房间 - 请使用 set_short 来编辑标题");
	set("long", "这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。\n");
	set("type", "normal");
ROOM
	;

	// refresh_data 格式：({ 制造者, 建造时间, 最后更新者, 最后更新时间 })
	str += sprintf("\tset(\"refresh_data\", ({ %O, %O, %O, %O }));\n",
		me->query("id"), ctime(time()), me->query("id"), ctime(time()) );

	str += sprintf("\tset(\"kingdom_id\", %O);\n", me->query("kingdom/id"));
	str += sprintf("\tset(\"exits\", %O);\n", ([ new_arg: base_name(env) ]) );

	str += "\n\tsetup();\n";
	str += "\treplace_program(ROOM);\n}\n";

	if( !write_file(new_file+".c", str, 1) )
		return notify_fail("你没有建造房间的权利，请通知管理者。\n");

	message_vision("$N找了一堆工人来在 "+capitalize(arg)+" 敲敲打打的，做出一间房间。\n", me);

	// 原房间要开个方向
	env->add("exits",([ arg: new_file ]));
	do_saveroom(env);

	kingdom_data(me->query("kingdom/id"), "data", "add", "room", 1);
	kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", ROOM_MONEY);

	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : makeroom <方向>

这是国王与大臣用来开发国土以增加领地的指令, 开发人可以向东西南北
上下六个方向中的任一个还没有出口的方向建立出口, 这时那个方向就会
多出一间房间, 而开发者也会自动走过去,并可以用下列指令设定新房间
的性质 :

        set_short       : 设定房间的名字, 就是你看到的第一行。
        set_long        : 设定房间的描述, 就是你看到的那堆描述。
        add_mob         : 为这个房间添加一些生物。
        add_desc        : 为这个房间加入一些可以看的描述。
        saveroom        : 当你把房间的一切都设定好了,记得一定要存起来。
        delete_room     : 删除多余的房间。
        linkroom        : 连接两个房间。

其他相关资讯 :  set_short, set_long, add_mob, add_desc, saveroom,
		delete_room

HELP
	);
	return 1;
}
