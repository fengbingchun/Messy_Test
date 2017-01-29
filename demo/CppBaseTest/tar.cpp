#include "tar.hpp"

TarFile::TarFile(const char* tar_name)
	: file(nullptr), size(0)
{
	file_names.clear();
	file_sizes.clear();
	file_data_start_addrs.clear();
	file = fopen(tar_name, "rb");
}

TarFile::~TarFile()
{
	if (file) {
		fclose(file);
		file = nullptr;
	}
	file_names.clear();
	file_sizes.clear();
	file_data_start_addrs.clear();
}

bool TarFile::IsValidTarFile()
{
	if (!file) return false;

	const int block_size{ 512 };
	unsigned char buf[block_size];
	tar_posix_header* header = (tar_posix_header*)buf;
	memset(buf, 0, block_size);

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (size % block_size != 0) {
		fprintf(stderr, "tar file size should be a multiple of 512 bytes: %d\n", size);
		return false;
	}

	size_t pos{ 0 };

	while (1) {
		size_t read_size = fread(buf, block_size, 1, file);
		if (read_size != 1) break;
		if (strncmp(header->magic, TMAGIC, 5)) break;

		pos += block_size;
		size_t file_size{0};
		sscanf(header->size, "%lo", &file_size);
		size_t file_block_count = (file_size + block_size - 1) / block_size;

		switch (header->typeflag) {
			case '0': // intentionally dropping through
			case '\0':
				// normal file
				file_sizes.push_back(file_size);
				file_names.push_back(std::string(header->name));
				file_data_start_addrs.push_back(pos);
				break;
			case '1':
				// hard link
				break;
			case '2':
				// symbolic link
				break;
			case '3':
				// device file/special file
				break;
			case '4':
				// block device
				break;
			case '5':
				// directory
				break;
			case '6':
				// named pipe
				break;
			default:
				break;
		}

		pos += file_block_count * block_size;
		fseek(file, pos, SEEK_SET);
	}

	fseek(file, 0, SEEK_SET);

	return true;
}

std::vector<std::string> TarFile::GetFileNames()
{
	return file_names;
}

bool TarFile::GetFileContents(const char* file_name, char* contents)
{
	bool flag = false;
	for (int i = 0; i < file_names.size(); i++) {
		std::string name_(file_name);

		if (file_names[i].compare(name_) == 0) {
			int file_size = file_sizes[i];
			flag = true;
			fseek(file, file_data_start_addrs[i], SEEK_SET);
			fread(contents, file_size, 1, file);
			fseek(file, 0, SEEK_SET);

			break;
		}
	}

	return flag;
}

size_t TarFile::GetFileSize(const char* file_name)
{
	size_t file_size{0};

	for (int i = 0; i < file_names.size(); i++) {
		std::string name_(file_name);

		if (file_names[i].compare(name_) == 0) {
			file_size = file_sizes[i];
			break;
		}
	}

	return file_size;
}

size_t TarFile::GetTarSize()
{
	return size;
}

//////////////////////////////////////////////
int test_tar()
{
	const std::string tar_file_path{ "E:/GitCode/Messy_Test/testdata/test.tar" };
	TarFile tarfile(tar_file_path.c_str());

	bool is_valid_tar_file = tarfile.IsValidTarFile();
	if (!is_valid_tar_file) {
		fprintf(stderr, "it is not a valid tar file: %s\n", tar_file_path.c_str());
		return -1;
	}

	fprintf(stderr, "tar file size: %d byte\n", tarfile.GetTarSize());

	std::vector<std::string> file_names = tarfile.GetFileNames();
	fprintf(stderr, "tar file count: %d\n", file_names.size());
	for (auto name : file_names) {
		fprintf(stderr, "=====================================\n");
		size_t file_size = tarfile.GetFileSize(name.c_str());
		fprintf(stderr, "file name: %s,  size: %d byte\n", name.c_str(), file_size);

		char* contents = new char[file_size + 1];
		tarfile.GetFileContents(name.c_str(), contents);
		contents[file_size] = '\0';

		fprintf(stderr, "contents:\n%s\n", contents);
		delete[] contents;
	}

	return 0;
}
