//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/rest.c

inherit ROOM;

void create()
{
	set("short", "客房");
	set("long", @TEXT
这是一间清净的客房, 房内就只有一桌一床, 桌边有一扇小窗, 细细的
鸟语和淡淡的花香不时飘来。现在这里是你专属的个人空间, 你可以在这里
安心的歇息, 如果你要离开, 请记得把自己的东西带走, 不然服务生在整理
房间时会把他们集中到储藏室。
TEXT);

	set("type","normal");
	set("no_fight", 1);
	set("no_quit", 1);
	set("no_recall", 1);
	set("no_teleport", 1);
	setup();
	replace_program(ROOM);
}
