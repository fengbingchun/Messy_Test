#include "filesystem.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>

int test_filesystem_directory_iterator()
{
	namespace fs = std::filesystem;

	const std::string path{ "../../../src/cJSON" };
	
	std::cout << "directory_iterator result:" << std::endl;
	for (auto const& dir_entry : fs::directory_iterator(path))
		std::cout << dir_entry.path() << std::endl;

	return 0;
}

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/133430293
namespace {

float get_file_size(std::uintmax_t size, std::string& suffix)
{
	float s1 = size / 1024. / 1024 / 1024;
	float s2 = size / 1024. / 1024;
	float s3 = size / 1024.;

	if (s1 > 1) {
		suffix = " GB";
		return s1;
	}
	if (s2 > 1) {
		suffix = " MB";
		return s2;
	}
	if (s3 > 1) {
		suffix = " KB";
		return s3;
	}
	suffix = " Bytes";
	return size;
}

std::string to_time_t(std::filesystem::file_time_type tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - std::filesystem::file_time_type::clock::now() + system_clock::now());
	auto tt = system_clock::to_time_t(sctp);

	std::tm* gmt = std::localtime(&tt); // UTC: std::gmtime(&tt);
	std::stringstream buffer;
	buffer << std::put_time(gmt, "%Y-%m-%d %H:%M:%S");
	return buffer.str();
}

} // namespace

int test_filesystem_directory_entry()
{
	namespace fs = std::filesystem;

	// 1. construct,operator=,assign
	fs::directory_entry d1{ fs::current_path() };
	fs::directory_entry d2 = d1;
	fs::directory_entry d3;
	d3.assign(fs::current_path());
	if ((d1 == d2) && (d1 == d3))
		std::cout << "they are equal" << std::endl; // they are equal
	// windows: d1:"E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\CppBaseTest"
	// linux: d1:"/home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest"
	std::cout << "d1:" << d1 << std::endl;

	// 2. replace_filename
	d1.replace_filename("C++17Test");
	// windows: d1:"E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\C++17Test"
	// linux: d1:"/home/spring/GitCode/Messy_Test/prj/C++17Test"
	std::cout << "d1:" << d1 << std::endl;

	// 3. path
	fs::path p1 = d1.path();
	// windows: p1:"E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\C++17Test"
	// linux: p1:"/home/spring/GitCode/Messy_Test/prj/C++17Test"
	std::cout << "p1:" << p1 << std::endl;

	// 4. exists
	for (const auto& str : { "C:\\Program Files (x86)", "/usr/local" , "E:\\GitCode\\xxx", "/usr/xxx"}) {
		fs::directory_entry entry{ str };
		/* windows:
			directory entry: "C:\\Program Files (x86)":exists
			directory entry: "/usr/local":does not exist
			directory entry: "E:\\GitCode\\xxx":does not exist
			directory entry: "/usr/xxx":does not exist */
		/* linux:
			directory entry: "C:\\Program Files (x86)":does not exist
			directory entry: "/usr/local":exists
			directory entry: "E:\\GitCode\\xxx":does not exist
			directory entry: "/usr/xxx":does not exist
		*/
		std::cout << "directory entry: " << entry << (entry.exists() ? ":exists\n" : ":does not exist\n");
	}

	// 5. is_block_file,is_character_file,is_directory,is_fifo,is_other,is_regular_file,is_socket,is_symlink
	for (const auto& str : { "/dev/null", "C:\\Program Files (x86)", "/usr/include/time.h", "C:\\MinGW\\bin\\c++filt.exe",
		"/usr/bin/g++", "/dev/block/11:0"}) {
		fs::directory_entry entry{ str };
		/* windows:
			"C:\\Program Files (x86)" is a directory
			"C:\\MinGW\\bin\\c++filt.exe" is a regular_file */
		/* linux:
			"/dev/null" is a character device
			"/dev/null" is an other file
			"/usr/include/time.h" is a regular_file
			"/usr/bin/g++" is a regular_file
			"/usr/bin/g++" is a symlink
			"/dev/block/11:0" is a block device
			"/dev/block/11:0" is an other file
			"/dev/block/11:0" is a symlink */
		if (entry.is_block_file())
			std::cout << entry << " is a block device" << std::endl;
		if (entry.is_character_file())
			std::cout << entry << " is a character device" << std::endl;
		if (entry.is_directory())
			std::cout << entry << " is a directory" << std::endl;
		if (entry.is_fifo())
			std::cout << entry << " is a FIFO" << std::endl;
		if (entry.is_other())
			std::cout << entry << " is an other file" << std::endl;
		if (entry.is_regular_file())
			std::cout << entry << " is a regular_file" << std::endl;
		if (entry.is_socket())
			std::cout << entry << " is a named socket" << std::endl;
		if (entry.is_symlink())
			std::cout << entry << " is a symlink" << std::endl;
	}

	// 6. file_size, last_write_time
	for (const auto& str : { "/usr/bin/g++", "D:\\FSCapture.exe", "D:\\DownLoad\\tmp.txt", "/usr/bin/cmake", "E:\\yulong.mp4"}) {
		fs::directory_entry entry{ str };
		/* windows:
			"D:\\FSCapture.exe" size: 2.82 MB
			"D:\\FSCapture.exe" last write time: 2016-03-29 09:26:26
			"D:\\DownLoad\\tmp.txt" size: 10 Bytes
			"D:\\DownLoad\\tmp.txt" last write time: 2023-09-26 09:00:35
			"E:\\yulong.mp4" size: 1.35 GB
			"E:\\yulong.mp4" last write time: 2023-08-19 22:42:56 */
		/* linux:
			"/usr/bin/g++" size: 910.82 KB
			"/usr/bin/g++" last write time: 2023-05-13 15:52:47
			"/usr/bin/cmake" size: 6.43 MB
			"/usr/bin/cmake" last write time: 2022-08-17 18:44:05 */
		if (entry.is_regular_file()) {
			std::string suffix;
			auto value = get_file_size(entry.file_size(), suffix);
			if (suffix == " Bytes")
				std::cout << entry << " size: " << static_cast<int>(value) << suffix << std::endl;
			else
				std::cout << entry << " size: " << std::fixed << std::setprecision(2) << value << suffix << std::endl;

			std::cout << entry << " last write time: " << to_time_t(entry.last_write_time()) << std::endl;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/133217504
int test_filesystem_path()
{
	namespace fs = std::filesystem;

	// 1. constructs a path
	fs::path p1 = "/usr/lib";
	fs::path p2 = "C:/Program Files";
	fs::path p3("/usr/local");
	
	// 2. operator=
	p1 = p1 / "include"; // move assignment
	p2 = p2 / "NVIDIA GPU Computing Toolkit";
	// windows: p1:"/usr/lib\\include", p2: "C:/Program Files\\NVIDIA GPU Computing Toolkit"
	// linux: p1:"/usr/lib/include", p2: "C:/Program Files/NVIDIA GPU Computing Toolkit" 
	std::cout << "p1:" << p1 << ", p2: " << p2 << std::endl; 

	// 3. assign
	std::cout << "p3: " << p3 << std::endl; // p3: "/usr/local"
	p3.assign("/usr/bin");
	std::cout << "p3: " << p3 << std::endl; // p3: "/usr/bin"

	// 4. append, operator/=
	fs::path p4 = "C:";
	p4.append("Git"); // note: windows: "C:Git" not "C://Git"; linux: "C:/Git"
	p3.append("include");

	p1 /= "include";
	p2 /= "NVIDIA";
	// windows: p4:"C:Git", p3:"/usr/bin\\include", p1:"/usr/lib\\include\\include", p2:"C:/Program Files\\NVIDIA GPU Computing Toolkit\\NVIDIA"
	// linux: p4:"C:/Git", p3:"/usr/bin/include", p1:"/usr/lib/include/include", p2:"C:/Program Files/NVIDIA GPU Computing Toolkit/NVIDIA"
	std::cout << "p4:" << p4 << ", p3:" << p3 << ", p1:" << p1 << ", p2:" << p2 << std::endl;

	// 5. concat, operator+=
	p1 = "";
	p1.concat("var");
	p1 += "lib";
	std::cout << "p1:" << p1 << std::endl; // p1:"varlib"

	// 6. clear
	p1.clear();
	std::cout << "p1:" << p1 << std::endl; // p1:""

	// 7. make_preferred
	p1 = "a\\b\\c";
	p2 = "a/b/c";
	// windows: p1:"a\\b\\c", p2:"a\\b\\c"
	// linux: p1:"a\\b\\c", p2:"a/b/c"
	std::cout << "p1:" << p1.make_preferred() << ", p2:" << p2.make_preferred() << std::endl;

	// 8. remove_filename
	p1 = "C:/Program Files/CUDA";
	p2 = "/usr/local/bin";
	p1 = p1.remove_filename();
	p2 = p2.remove_filename();
	// p1:"C:/Program Files/", p2:"/usr/local/", false, false
	std::cout << "p1:" << p1 << ", p2:" << p2 << std::boolalpha << ", " << p1.has_filename() << ", " << p2.has_filename() << std::endl;

	// 9. replace_filename
	p1 = "C:/Program Files/CUDA";
	p2 = "/usr/local/bin";
	p1.replace_filename("include");
	p2.replace_filename("include");
	// p1:"C:/Program Files/include", p2:"/usr/local/include"
	std::cout << "p1:" << p1 << ", p2:" << p2 << std::endl;

	// 10. replace_extension
	p1 = "C:/Program Files/CUDA.jpg";
	p2 = "/usr/local/lena.jpg";
	p1.replace_extension("bmp");
	p2.replace_extension(".bmp");
	// p1:"C:/Program Files/CUDA.bmp", p2:"/usr/local/lena.bmp"
	std::cout << "p1:" << p1 << ", p2:" << p2 << std::endl;

	// 11. swap
	p1 = "C:/Program Files/CUDA";
	p2 = "/usr/local/bin";
	p1.swap(p2);
	// p1:"/usr/local/bin", p2:"C:/Program Files/CUDA"
	std::cout << "p1:" << p1 << ", p2:" << p2 << std::endl;

	// 12. string
	auto str = p1.string(); // note: cannot be: p1.string().c_str()
	std::cout << "str:" << str.c_str() << std::endl; // str:/usr/local/bin

	// 13. generic_string
	str = p1.generic_string();
	std::cout << "str:" << str << std::endl; // str:/usr/local/bin

	// 14. compare
	p1 = "/usr/abc";
	p2 = "/usr/Abc";
	auto ret1 = p1.compare(p2); // A: 65, a: 97
	auto ret2 = p2.compare(p1);
	// windows: ret1:32, ret2:-32
	// linux: ret1:2097152, ret2:-2097152
	std::cout << "ret1:" << ret1 <<", ret2:" << ret2 << std::endl;

	// 15. root_name, root_directory, root_path, relative_path, parent_path, filename
	fs::path p = fs::current_path();
	// windows: current path:"E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\CppBaseTest", 
	//     root name:"E:", root directory:"\\", root path:"E:\\", relative path:"GitCode\\Messy_Test\\prj\\x86_x64_vc12\\CppBaseTest", 
	//     parent path:"E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12", filename:"CppBaseTest"
	// linux: current path:"/home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest",
	//     root name:"", root directory:"/", root path:"/", relative path:"home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest",
	//     parent path:"/home/spring/GitCode/Messy_Test/prj", filename:"linux_cmake_CppBaseTest"
	std::cout << "current path:" << p
		<< ", root name:" << p.root_name() << ", root directory:" << p.root_directory()
		<< ", root path:" << p.root_path() << ", relative path:" << p.relative_path()
		<< ", parent path:" << p.parent_path() << ", filename:" << p.filename() << std::endl;

	// 16. stem, extension
	p1 = "E:\\x86_x64_vc12\\CppBaseTest.cpp";
	p2 = "/usr/local/linux.cpp";
	// windows: stem:"CppBaseTest", extension:".cpp"
	// linux: stem:"E:\\x86_x64_vc12\\CppBaseTest", extension:".cpp"
	std::cout << "stem:" << p1.stem() << ", extension:" << p1.extension() << std::endl;
	// stem:"linux", extension:".cpp
	std::cout << "stem:" << p2.stem() << ", extension:" << p2.extension() << std::endl;

	// 17. empty, has_root_path, has_root_name, has_root_directory, has_relative_path, has_parent_path, has_filename, has_stem, has_extension
	p = fs::current_path();
	// windows: false,true,true,true,true,true,true,true,false
	// linux: false,true,false,true,true,true,true,true,false
	std::cout << std::boolalpha << p.empty() << "," << p.has_root_path() << "," << p.has_root_name() << "," << p.has_root_directory()
		<< "," << p.has_relative_path() << "," << p.has_parent_path() << "," << p.has_filename() << "," << p.has_stem() << "," << p.has_extension() << std::endl;

	// 18. is_absolute, is_relative
	p1 = "../../images";
	p2 = "/usr/local";
	p3 = "E:\\x86_x64_vc12";
	p4 = "images/test";
	// windows: false,false,true,false,true,true,false,true
	// linux: false,true,false,false,true,false,true,true
	std::cout << std::boolalpha << p1.is_absolute() << "," << p2.is_absolute() << "," << p3.is_absolute() << "," << p4.is_absolute()
		<< "," << p1.is_relative() << "," << p2.is_relative() << "," << p3.is_relative() << "," << p4.is_relative() << std::endl;

	// 19. begin, end
	p = fs::current_path();
	// windows: current path:"E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\CppBaseTest"
	// linux: current path:"/home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest"
	std::cout << "current path:" << p << std::endl;
	// windows: "E:" | "\\" | "GitCode" | "Messy_Test" | "prj" | "x86_x64_vc12" | "CppBaseTest" |
	// linux: "/" | "home" | "spring" | "GitCode" | "Messy_Test" | "prj" | "linux_cmake_CppBaseTest" |
	for (auto it = p.begin(); it != p.end(); ++it)
		std::cout << *it << " | ";
	std::cout << std::endl;

	// non-member functions
	// 1. swap
	std::cout << "p1:" << p1 << ", p2:" << p2 << std::endl; // p1:"../../images", p2:"/usr/local"
	fs::swap(p1, p2);
	std::cout << "p1:" << p1 << ", p2:" << p2 << std::endl; // p1:"/usr/local", p2:"../../images"

	// 2. hash_value
	/* windows:
	  541593CE5A744D49 : .. / .. / images
	  E20DE9FA0712ACAC : /usr/local
	  448B5E8D233AB844 : E:\x86_x64_vc12 */
	/* linux:
	  C5561B62D374C247 : ../../images
	  8A5180B805D0D290 : /usr/local
	  D937A950FC185671 : E:\x86_x64_vc12 */
	for (const auto& s : {"../../images", "/usr/local", "E:\\x86_x64_vc12"})
		std::cout << std::hex << std::uppercase << std::setw(16) << fs::hash_value(s) << " : " << s << '\n';

	// 3. operator==,!=,<,<=,>,>=,
	p1 = "image/1.txt";
	p2 = "image/2.txt";
	// true,true
	std::cout << std::boolalpha << (p1 != p2) << "," << (p1.parent_path() == p2.parent_path()) << std::endl;

	// 4. operator/
	p1 = "C:";
	p1 = p1 / "Users" / "admin";
	p2 = "/home";
	p2 = p2 / "local" / "bin";
	// windows: "C:Users\\admin","/home\\local\\bin"
	// linux: "C:/Users/admin","/home/local/bin"
	std::cout << p1 << "," << p2 << std::endl;

	// 5. std::hash: std::hash<std::filesystem::path>{}(p) is equal to std::filesystem::hash_value(p)
	/* windows:
	  541593CE5A744D49 : .. / .. / images
	  E20DE9FA0712ACAC: /usr/local
	  448B5E8D233AB844 : E:\x86_x64_vc12 */
	/* linux:
	  C5561B62D374C247 : ../../images
	  8A5180B805D0D290 : /usr/local
	  D937A950FC185671 : E:\x86_x64_vc12 */
	for (const auto& s : { "../../images", "/usr/local", "E:\\x86_x64_vc12" })
		std::cout << std::hex << std::uppercase << std::setw(16) << std::hash<fs::path>{}(fs::path(s)) << " : " << s << '\n';

	return 0;
}
