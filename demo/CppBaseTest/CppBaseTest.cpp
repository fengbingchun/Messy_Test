#include <iostream>
#include "common.hpp"

int main()
{
	int ret = tracing_war_story_::test_tracing_war_story();

	if (ret == 0) fprintf(stdout, "========== test success ==========\n");
	else fprintf(stderr, "########## test fail ##########\n");

	return 0;
}
