#include "filesystem.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <vector>
#include <cstdio>

namespace fs = std::filesystem;

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/133552753
namespace {

void demo_status(const fs::path& p, fs::file_status s)
{
	std::cout << p;
	switch (s.type()) {
	case fs::file_type::none:
		std::cout << " has `not-evaluated-yet` type";
		break;
	case fs::file_type::not_found:
		std::cout << " does not exist";
		break;
	case fs::file_type::regular:
		std::cout << " is a regular file";
		break;
	case fs::file_type::directory:
		std::cout << " is a directory";
		break;
	case fs::file_type::symlink:
		std::cout << " is a symlink";
		break;
	case fs::file_type::block:
		std::cout << " is a block device";
		break;
	case fs::file_type::character:
		std::cout << " is a character device";
		break;
	case fs::file_type::fifo:
		std::cout << " is a named IPC pipe";
		break;
	case fs::file_type::socket:
		std::cout << " is a named IPC socket";
		break;
	case fs::file_type::unknown:
		std::cout << " has `unknown` type";
		break;
	default:
		std::cout << " has `implementation-defined` type";
		break;
	}
	std::cout << '\n';
}

void demo_status2(const fs::path& p, fs::file_status s)
{
	std::cout << p;
	// alternative: switch(s.type()) { case fs::file_type::regular: ...}
	if (fs::is_regular_file(s))
		std::cout << " is a regular file\n";
	if (fs::is_directory(s))
		std::cout << " is a directory\n";
	if (fs::is_block_file(s))
		std::cout << " is a block device\n";
	if (fs::is_character_file(s))
		std::cout << " is a character device\n";
	if (fs::is_fifo(s))
		std::cout << " is a named IPC pipe\n";
	if (fs::is_socket(s))
		std::cout << " is a named IPC socket\n";
	if (fs::is_symlink(s))
		std::cout << " is a symlink\n";
	if (!fs::exists(s))
		std::cout << " does not exist\n";
	//if (fs::is_empty(p))
	//	std::cout << " is empty\n";
	if (fs::is_other(s)) // equivalent to exists(s) && !is_regular_file(s) && !is_directory(s) && !is_symlink(s)
		std::cout << " is other file\n";
	//if (fs::status_known(s)) // equivalent to s.type() != file_type::none
	//	std::cout << " is status known\n";
}

void demo_perms(fs::perms p)
{
	using fs::perms;
	auto show = [=](char op, perms perm) {
		std::cout << (perms::none == (perm & p) ? '-' : op);
	};

	show('r', perms::owner_read);
	show('w', perms::owner_write);
	show('x', perms::owner_exec);
	show('r', perms::group_read);
	show('w', perms::group_write);
	show('x', perms::group_exec);
	show('r', perms::others_read);
	show('w', perms::others_write);
	show('x', perms::others_exec);
	std::cout << '\n';
}

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

std::string to_time_t(fs::file_time_type tp)
{
	using namespace std::chrono;
	auto sctp = time_point_cast<system_clock::duration>(tp - fs::file_time_type::clock::now() + system_clock::now());
	auto tt = system_clock::to_time_t(sctp);

	std::tm* gmt = std::localtime(&tt); // UTC: std::gmtime(&tt);
	std::stringstream buffer;
	buffer << std::put_time(gmt, "%Y-%m-%d %H:%M:%S");
	return buffer.str();
}

} // namespace

int test_filesystem_file_types()
{
	demo_status2("/dev/null", fs::status("/dev/null"));
	demo_status2("/dev/sda", fs::status("/dev/sda"));
	demo_status2(fs::current_path(), fs::status(fs::current_path()));
	demo_status2("/xxx/yyy", fs::status("/xxx/yyy"));
	demo_status2("/usr/bin/g++", fs::status("usr/bin/g++"));
	demo_status2("../../../testdata/list.txt", fs::status("../../../testdata/list.txt"));
	demo_status2("../../testdata/list.txt", fs::status("../../testdata/list.txt"));
	demo_status2("/mnt", fs::status("/mnt"));

	return 0;
}

int test_filesystem_non_member_functions()
{
	const fs::path p1 = "../funset.cpp";
#ifdef _MSC_VER
	const fs::path p2{ "../../../testdata/list.txt" }, p3{ "../../../testdata/list_copy.txt" }, p4{ "E:\\yulong.mp4" }, p5{ "../../../testdata/list_new.txt" };
#else
	const fs::path p2{ "../../testdata/list.txt" }, p3{ "../../testdata/list_copy.txt" }, p4{ "./build/CppBaseTest" }, p5{"../../testdata/list_new.txt"};
#endif
	// windows: current path is "E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\CppBaseTest"
	// linux: current path is "/home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest"
	std::cout << "current path is " << fs::current_path() << '\n';
	// 1. absolute
	// windows: absolute path for "../funset.cpp" is "E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\funset.cpp"
	// linux: absolute path for "../funset.cpp" is "/home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest/../funset.cpp"
	std::cout << "absolute path for " << p1 << " is " << fs::absolute(p1) << '\n';

	// 2. canonical, weakly_canonical
	/* windows:
		canonical path: "E:\\GitCode\\Messy_Test\\testdata\\list.txt"
		weakly canonical path: "E:\\GitCode\\Messy_Test\\testdata\\list.txt" */
	/* linux:
		canonical path: "/home/spring/GitCode/Messy_Test/testdata/list.txt"
		weakly canonical path: "/home/spring/GitCode/Messy_Test/testdata/list.txt" */
	std::cout << "canonical path: " << fs::canonical(p2) << "\n";
	std::cout << "weakly canonical path: " << fs::weakly_canonical(p2) << "\n";

	// 3. relative, proximate
	std::cout << "relative path: " << fs::relative("/a/b/c", "/a/b")
		<< ", proximat path: " << fs::proximate("/a/b/c", "/a/b") << "\n";	// relative path: "c", proximat path: "c"

	// 4. copy, exists, remove
	if (fs::exists(p3))
		fs::remove(p3);
	fs::copy(p2, p3);

	// 5. copy_file
	if (fs::exists(p3))
		fs::remove(p3);
	fs::copy_file(p2, p3);

	// 6. create_directory, create_directories
	fs::create_directory("./a");
	fs::create_directories("./b/c/d");

	// 7. equivalent
	if (fs::equivalent(".", fs::current_path()))
		std::cout << "they are equal" << "\n";

	// 8. file_size
	std::string suffix;
	auto value = get_file_size(static_cast<std::intmax_t>(fs::file_size(p4)), suffix);
	// windows: size: 1.35 GB; linux: size: 7.61 MB
	std::cout << "size: " << std::fixed << std::setprecision(2) << value << suffix << "\n";

	// 9. last_write_time
	// windows: last write time: 2023-08-19 22:42:56
	// linux: last write time: 2023-10-03 12:32:49
	std::cout << "last write time: " << to_time_t(last_write_time(p4)) << std::endl;

	// 10. permissions
	// windows: rwxrwxrwx r-xr-xr-x
	// linux:   rw-rw-r-- -w-r-----
	demo_perms(fs::status(p3).permissions());
#ifdef _MSC_VER
	fs::permissions(p3, fs::perms::none);
#else
	fs::permissions(p3, fs::perms::owner_write | fs::perms::group_read);
#endif
	demo_perms(fs::status(p3).permissions());

	// 11. rename
	if (fs::exists(p5))
		fs::remove(p5);
	fs::rename(p3, p5);

	// 12. resize_file
	// linux: size: 187.00 Bytes  size: 64.00 KB
	value = get_file_size(static_cast<std::intmax_t>(fs::file_size(p5)), suffix);
	std::cout << "size: " << std::fixed << std::setprecision(2) << value << suffix << "\n";
#ifdef __linux__
	fs::resize_file(p5, 64 * 1024); // resize to 64 KB, windows crash
	value = get_file_size(static_cast<std::intmax_t>(fs::file_size(p5)), suffix);
	std::cout << "size: " << std::fixed << std::setprecision(2) << value << suffix << "\n";
#endif

	// 13. temp_directory_path
	// windows: temp directory is: "C:\\Users\\f06190\\AppData\\Local\\Temp\\"
	// linux: temp directory is: "/tmp"
	std::cout << "temp directory is: " << fs::temp_directory_path() << "\n";

	// std::error_code
	std::error_code ec;
	fs::copy_file("xxx", "yyy", ec); // does not throw
	// windows: error code: 2,系统找不到指定的文件。
	// linux: error code: 2,No such file or directory
	std::cout << "error code: " << ec.value() << "," << ec.message() << "\n";

	try {
		fs::copy_file("xxx", "yyy");
	} catch (fs::filesystem_error const& ex) {
		std::cout << "what():  " << ex.what() << '\n'
			<< "path1(): " << ex.path1() << '\n'
			<< "path2(): " << ex.path2() << '\n'
			<< "code().value():    " << ex.code().value() << '\n'
			<< "code().message():  " << ex.code().message() << '\n'
			<< "code().category(): " << ex.code().category().name() << '\n';
	}

	return 0;
}

int test_filesystem_space_info()
{
	fs::space_info info = fs::space(fs::current_path());
	std::cout << "current path: " << fs::current_path() << "  ";
	// windows: current path: "E:\\GitCode\\Messy_Test\\prj\\x86_x64_vc12\\CppBaseTest"   size: 311.00 GB   size: 189.23 GB   size: 189.23 GB
	// linux: current path: "/home/spring/GitCode/Messy_Test/prj/linux_cmake_CppBaseTest"   size: 311.00 GB   size: 189.23 GB   size: 189.23 GB
	for (auto x : { info.capacity, info.free, info.available }) {
		std::string suffix;
		auto value = get_file_size(static_cast<std::intmax_t>(x), suffix);
		std::cout << " size: " << std::fixed << std::setprecision(2) << value << suffix << "  ";
	}
	std::cout << std::endl;

	return 0;
}

int test_filesystem_file_status()
{
#ifdef _MSC_VER
	const std::string path{ "../../../testdata/list.txt" };
#else
	const std::string path{ "../../testdata/list.txt" };
#endif

	// 1. type
	// windows: "../../../testdata/list.txt" is a regular file
	// linux: "../../testdata/list.txt" is a regular file
	demo_status(path, fs::status(path));

	// 2. permissions
	demo_perms(fs::status(path).permissions()); // rwxrwxrwx

	return 0;
}

int test_filesystem_filesystem_error()
{
	// path1, path2, whtat
	// creates a unique filename that does not name a currently existing file
	const fs::path oldp{ std::tmpnam(nullptr) }, newp{ std::tmpnam(nullptr) };

	/* windows:
		what():  rename: 系统找不到指定的文件。: "C:\Users\f06190\AppData\Local\Temp\sf2w.0", "C:\Users\f06190\AppData\Local\Temp\sf2w.1"
		path1(): "C:\\Users\\f06190\\AppData\\Local\\Temp\\sf2w.0"
		path2(): "C:\\Users\\f06190\\AppData\\Local\\Temp\\sf2w.1" */
	/* linux
		what():  filesystem error: cannot rename: No such file or directory [/tmp/filezJrUkO] [/tmp/filey7tqKV]
		path1(): "/tmp/filezJrUkO"
		path2(): "/tmp/filey7tqKV" */
	try {
		fs::rename(oldp, newp); // throws since oldp does not exist
	} catch (fs::filesystem_error const& ex) {
		std::cout << "what():  " << ex.what() << '\n'
			<< "path1(): " << ex.path1() << '\n'
			<< "path2(): " << ex.path2() << '\n';
	}

	return 0;
}

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/133437356
int test_filesystem_recursive_directory_iterator()
{
#ifdef _MSC_VER
	const std::string path{ "../../../src/cJSON" };
#else
	const std::string path{ "../../src/cJSON" };
#endif

	std::vector<fs::path> files, directories;
	for (auto const& dir_entry : fs::recursive_directory_iterator(path)) {
		if (dir_entry.is_directory())
			directories.emplace_back(dir_entry.path());
		else if (dir_entry.is_regular_file())
			files.emplace_back(dir_entry.path());
		else
			std::cout << "other:" << dir_entry.path() << std::endl;
	}

	std::cout << "recursive_directory_iterator result:" << std::endl;
	std::cout << "directories:" << std::endl;
	for (const auto& dir : directories)
		std::cout << "\t" << dir << std::endl;

	std::cout << "\n\nregular files:" << std::endl;
	for (const auto& file : files)
		std::cout << "\t" << file << std::endl;

	// depth
	std::cout << "\n\ndepth:" << std::endl;
	for (auto it = fs::recursive_directory_iterator(path); it != fs::recursive_directory_iterator(); ++it)
		std::cout << *it << ": " << it.depth() << std::endl;

	return 0;
}

int test_filesystem_directory_iterator()
{
#ifdef _MSC_VER
	const std::string path{ "../../../src/cJSON" };
#else
	const std::string path{ "../../src/cJSON" };
#endif
	
	std::cout << "directory_iterator result:" << std::endl;
	for (auto const& dir_entry : fs::directory_iterator(path))
		std::cout << dir_entry.path() << std::endl;

	return 0;
}

/////////////////////////////////////////////////////////////////
// Blog: https://blog.csdn.net/fengbingchun/article/details/133430293
int test_filesystem_directory_entry()
{
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
