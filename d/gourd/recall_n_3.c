//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_n_3

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "北大街");
        set("long", @LONG
这是一个葫芦城的北大街。可以看到有各种不同国的人在这里，让人感
觉到一种耳目一新的感觉，周围的人都十分热络，看来都对此地非常熟悉，
如果要想了解此地历史不妨问问，北边是城里的北门南边通往城中央。
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_n_2",
                "north" : __DIR__"recall_ndoor",
                "west" : __DIR__"choice_class",
                "east" : __DIR__"recall_shop",
        ]));
        setup();
}
 


