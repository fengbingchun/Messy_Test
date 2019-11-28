#include "access.hpp"
#include <iostream>
#include <vector>
#include <string>
#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

// Blog: https://blog.csdn.net/fengbingchun/article/details/100342049

namespace access_ {

int test_access_1()
{
#ifdef _MSC_VER
	const std::string path{ "E:/GitCode/Messy_Test/" };
	const std::vector<std::string> names {"testdata", ".gitignore", "src", "invalid"};

	for (auto& name : names) {
		const std::string tmp = path + name;
		fprintf(stdout, "file or directory name: \"%s\": ", name.c_str());
		if (_access(tmp.c_str(), 0) == 0) fprintf(stdout, "exist, ");
		else fprintf(stdout, "not exist, ");
		
		if (_access(tmp.c_str(), 4) == 0) fprintf(stdout, "only has read premission, ");
		else fprintf(stdout, "does not have read premission, ");

		if (_access(tmp.c_str(), 2) == 0) fprintf(stdout, "only has  write premission, ");
		else fprintf(stdout, "does not have write premission, ");

		if (_access(tmp.c_str(), 6) == 0) fprintf(stdout, "has both read and write premission\n");
		else fprintf(stdout, "has neither read nor write premission\n");
	}
#else
	const std::vector<const char*> names {"testdata", "CMakeLists.txt", "build.sh", "invalid"};

	for (auto name : names) {
		fprintf(stdout, "file or directory name: \"%s\": ", name);
		if (access(name, F_OK) == 0) fprintf(stdout, "exist, ");
		else fprintf(stdout, "not exist, ", name);
		
		if (access(name, R_OK) == 0) fprintf(stdout, "has read premission, ");
		else fprintf(stdout, "does not have read premission, ");

		if (access(name, W_OK) == 0) fprintf(stdout, "has write premission, ");
		else fprintf(stdout, "does not have write premission, ");

		if (access(name, X_OK) == 0) fprintf(stdout, "has execute premission\n");
		else fprintf(stdout, "does not have execute premission\n");
	}
#endif
	return 0;
}

} // namespace access_


