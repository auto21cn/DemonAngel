//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_s_2
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你来到了葫芦城的南大街。道路两边有着很多的特殊建筑，令你感到十
分的新奇，而你也发现行人好像不多了，这里大概不是让游客玩耍的好地方
，往南边可以清楚葫芦城的南门的模样，而往北边走就回中央广场了。
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_sdoor",
                "north"  : __DIR__"recall_s_1",
        ]));
        setup();
}
 




