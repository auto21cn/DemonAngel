//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_w_1
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
你来到了葫芦城的西大街。由于这里有着很多风俗特异的店家，所以很
多爱赏玩的人都常常来此，如果你也是奇珍异玩的爱好者，可以在此地多晃
晃，说不定会找到心目中的好东西，西边有着一座城门，而往东边走就回中
央广场了。
LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_w_2",
                "east"  : __DIR__"gourd_recall",
        ]));
        setup();
}
 






