//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/mail.c

#include <room.h>

inherit POST_OFFICE;

void create()
{
	set("short", "邮局");
	set("long", @TEXT
你走进一家小邮局, 几个邮差正坐在一堆信箱旁边整理信件, 他们边聊
天边把信件塞入不同的信箱中。在这堆信箱中应该也有你的吧, 如果你想看
看有没有你的信, 你可以找找看有没有你的信箱(search mailbox)。
TEXT
	);
	set("exits", ([
		"north"	: __DIR__"recall_w_1.c"
	]));
	setup();
}
