//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/special/void.c
// by bor @ RG, DA

inherit ROOM;

void create()
{
	set("short","死神之约");
	set("long",@LONG	
这里是跟死神约会的地方，相信我，你来到这里绝对不是偶然的，
如果你害怕请尽快离开以免被人骚扰。
LONG
	);
	setup();
	replace_program(ROOM);
}

