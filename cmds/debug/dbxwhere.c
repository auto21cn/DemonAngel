//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
#include <globals.h>

int main()
{
  mapping error;
  int i;

  if (!(error = this_player()->query_error())) return 1;
  printf("%sProgram: %s\n", error["error"], error["program"]);
  for (i=0; i<sizeof(error["trace"]); i++) {
    printf("%i: %s in %s:%i\n", i, error["trace"][i]["function"], error["trace"][i]["program"], error["trace"][i]["line"]);
  }
  return 1;
}
