//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_n_2w.c

#include <room.h>

inherit PET_SHOP;

void create()
{
        set("short", "宠物专门店");
        set("long", @LONG
好多宠物提供给你购买。你可以利用 list 看一下有什么宠物可以购买(buy),
也可以利用 take 将自己的宠物带出来...
LONG
        );
        set("exits", ([
                "east" : __DIR__"recall_n_2",
        ]));
        setup();
        replace_program(PET_SHOP);
}

