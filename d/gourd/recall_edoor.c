//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_edoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "东城门");
        set("long", @LONG
这里是葫芦城的东城门。你望着城门不禁想着如此雄伟的城门要花多少
时间来盖好，周围有着极多不同国家的人正在入城，看来大陆中央之城的名
字应该不是虚名，而城门附近有着武装好的士兵在巡视，使人不敢轻举妄动
。
LONG
        );
        set("exits", ([
                "west"  : __DIR__"recall_e_2",
        ]));
        setup();
}


