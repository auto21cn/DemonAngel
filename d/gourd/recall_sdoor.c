//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_sdoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "南城门");
        set("long", @LONG
这里是葫芦城的南城门。从各个不同地方来的人简直是络绎不绝，让你
大感叹为观止，这里繁华的样子可见一班，而且到处可见武装良好的守卫在
巡逻，想要作乱的念头可能都要打消，让人感到极为安全。
LONG
        );
        set("exits", ([
                "north"  : __DIR__"recall_s_2",
        ]));
        setup();
}


