//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_n_1

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
这是一个葫芦城的北大街。道路四周有着许多的旅客，这里大概是城里
的商业重心，到处都是一堆小贩在叫卖，如果有空不妨慢慢逛逛，往北边可
以大致看到北门的雄伟，而再往南边走就是中央广场了。
LONG
        );
        set("exits", ([
                "south" : __DIR__"gourd_recall",
                "north" : __DIR__"recall_n_2",
                "east"  : __DIR__"recall_n_e",
                "west"  : __DIR__"recall_n_w",
        ]));
        setup();
}
 


