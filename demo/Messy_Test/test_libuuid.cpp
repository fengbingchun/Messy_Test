#include "funset.hpp"
#include <iostream>
#ifndef _MSC_VER
#include <uuid.h>

// Blog: https://blog.csdn.net/fengbingchun/article/details/94590406

int test_libuuid()
{
	uuid_t uuid1, uuid2, uuid3, uuid4, uuid5;
	char uuid1_str[37], uuid2_str[37], uuid3_str[37], uuid4_str[37];

	uuid_generate(uuid1);
	uuid_unparse(uuid1, uuid1_str);
	fprintf(stdout, "uuid1 result: %s\n", uuid1_str);

	uuid_generate_random(uuid2);
	uuid_unparse_lower(uuid2, uuid2_str);
	fprintf(stdout, "uuid2 result: %s\n", uuid2_str);

	uuid_generate_time(uuid3);
	uuid_unparse_upper(uuid3, uuid3_str);
	fprintf(stdout, "uuid3 result: %s\n", uuid3_str);

	uuid_generate_time_safe(uuid4);
	uuid_unparse(uuid4, uuid4_str);
	fprintf(stdout, "uuid4 result: %s\n", uuid4_str);

	uuid_parse(uuid1_str, uuid5);
	int ret = uuid_compare(uuid1, uuid5);
	fprintf(stdout, "uuid1 compare uuid5: %d\n", ret);

	ret = uuid_is_null(uuid1);
	fprintf(stdout, "uuid1 is null: %d\n", ret);
	uuid_clear(uuid1);
	ret = uuid_is_null(uuid1);
	fprintf(stdout, "uuid1 is null: %d\n", ret);

	ret = uuid_type(uuid2);
	fprintf(stdout, "uuid2 type: %d\n", ret);
	ret = uuid_variant(uuid2);
	fprintf(stdout, "uuid2 variant: %d\n", ret);

	struct timeval tv;
	time_t time_reg = uuid_time(uuid3, &tv);
	fprintf(stdout, "uuid3 time is: (%ld, %ld): %s\n", tv.tv_sec, tv.tv_usec, ctime(&time_reg));

	return 0;
}

#else
int test_libuuid()
{
	fprintf(stderr, "Error: libuuid only support linux\n");
	return -1;
}
#endif

