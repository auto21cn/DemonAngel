//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// entrance.c

#include <login.h>
#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "巫师会客室");
	set("long",
		"这里是巫师和玩家聊天的地方，如果你有什么意见要让巫师们知道，在这里\n"
	"留言是最快的途径，不过如果是对于游戏中的问题，请您先确定我们提供的说明\n"
	"文件里没有说明，再提出疑问，巫师的主要职责并不是教玩家如何玩。\n"
	"    为了杜绝机器人，您可以在这里检举(accuse)某个玩家，该名玩家会被抓去\n"
	"做一些小小的测验，目前这项功\能尚未做任何限制，请勿利用来骚扰别人。\n");
	set("exits", ([
		"west" : "/d/wiz/hall1",
		"southeast": "/d/snow/inn" ]) );
	set("no_fight", 1);
	set("no_magic", 1);
	create_door("southeast", "木门", "northwest", DOOR_CLOSED);

	setup();
	call_other( "/obj/board/query_b", "???" );
}

int valid_leave(object me, string dir)
{
	if( dir=="west" && !wizardp(me) )
		return notify_fail("那里只有巫师才能进去。\n");
	return ::valid_leave(me, dir);
}

void init()
{
	add_action("do_accuse", "accuse");
}

int do_accuse(string arg)
{
	object ob;
	string s;

	if( (int)this_player()->query("age") < 15 )
		return notify_fail("你年纪太小了，没有检举别人的权力。\n");

	if( !arg ) return notify_fail("你要检举谁？\n");
	if( ob = find_player(arg) ) {
		if( ob==this_player() )
			return notify_fail("你要检举自己？\n");
		if( ob->is_ghost() )
			return notify_fail( ob->name(1) + "已经死了，放他一马吧。\n");
		if( wizardp(ob) )
			return notify_fail("你不能检举巫师。\n");
		tell_object(ob, HIW + this_player()->name(1) + "检举你是个机器人，请你接受一个小小的测验。\n" NOR);
		ROBOT_CHECK->test_me(ob);
		write("Ok. 已经将你检举的对象送去做测验。\n");
		write("为了避免有人用机器人乱检举骚扰别人，请你也接受相同的测验。\n");
		ROBOT_CHECK->test_me(this_player());
		log_file("robot_accuse",
			sprintf("%s accused %s on %s.\n", this_player()->query("id"), ob->query("id"), ctime(time())));
		return 1;
	}
	return notify_fail("目前线上并没有这位玩家。\n");
}

