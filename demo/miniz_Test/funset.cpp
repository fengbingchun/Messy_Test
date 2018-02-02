#include "funset.hpp"
#include "../../src/miniz/miniz.c"

// Blog: http://blog.csdn.net/fengbingchun/article/details/52903219

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

#define my_max(a,b) (((a) > (b)) ? (a) : (b))
#define my_min(a,b) (((a) < (b)) ? (a) : (b))

#define BUF_SIZE (1024 * 1024)

// Demonstrates miniz.c's compress() and uncompress() functions (same as zlib's)£¬
// also a crude decompressor fuzzy test.
int test_miniz_1()
{
	// The string to compress.
	static const char *s_pStr = "Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
		"Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
		"Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
		"Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
		"Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
		"Good morning Dr. Chandra. This is Hal. I am ready for my first lesson." \
		"Good morning Dr. Chandra. This is Hal. I am ready for my first lesson.";

	uint step = 0;
	int cmp_status;
	uLong src_len = (uLong)strlen(s_pStr);
	uLong cmp_len = compressBound(src_len);
	uLong uncomp_len = src_len;
	uint8 *pCmp, *pUncomp;
	uint total_succeeded = 0;

	printf("miniz.c version: %s\n", MZ_VERSION);

	do {
		// Allocate buffers to hold compressed and uncompressed data.
		pCmp = (mz_uint8 *)malloc((size_t)cmp_len);
		pUncomp = (mz_uint8 *)malloc((size_t)src_len);
		if ((!pCmp) || (!pUncomp)) {
			printf("Out of memory!\n");
			return EXIT_FAILURE;
		}

		// Compress the string.
		cmp_status = compress(pCmp, &cmp_len, (const unsigned char *)s_pStr, src_len);
		if (cmp_status != Z_OK) {
			printf("compress() failed!\n");
			free(pCmp);
			free(pUncomp);
			return EXIT_FAILURE;
		}

		printf("Compressed from %u to %u bytes\n", (mz_uint32)src_len, (mz_uint32)cmp_len);

		if (step) {
			// Purposely corrupt the compressed data if fuzzy testing (this is a very crude fuzzy test).
			uint n = 1 + (rand() % 3);
			while (n--) {
				uint i = rand() % cmp_len;
				pCmp[i] ^= (rand() & 0xFF);
			}
		}

		// Decompress.
		cmp_status = uncompress(pUncomp, &uncomp_len, pCmp, cmp_len);
		total_succeeded += (cmp_status == Z_OK);

		if (step) {
			printf("Simple fuzzy test: step %u total_succeeded: %u\n", step, total_succeeded);
		} else {
			if (cmp_status != Z_OK) {
				printf("uncompress failed!\n");
				free(pCmp);
				free(pUncomp);
				return EXIT_FAILURE;
			}

			printf("Decompressed from %u to %u bytes\n", (mz_uint32)cmp_len, (mz_uint32)uncomp_len);

			// Ensure uncompress() returned the expected data.
			if ((uncomp_len != src_len) || (memcmp(pUncomp, s_pStr, (size_t)src_len))) {
				printf("Decompression failed!\n");
				free(pCmp);
				free(pUncomp);
				return EXIT_FAILURE;
			}
		}

		free(pCmp);
		free(pUncomp);

		step++;

		// Keep on fuzzy testing if there's a non-empty command line.
	} while (step <= 2);

	printf("Success.\n");
	return EXIT_SUCCESS;
}

// Demonstration of miniz.c's ZIP archive API's. Adds a bunch of filesto test.zip,
// dumps file stat info on each file in the archive, then extracts a single file into memory.
int test_miniz_2()
{
	// The string to compress.
	static const char *s_pTest_str =
		"MISSION CONTROL I wouldn't worry too much about the computer. First of all, there is still a chance that he is right, despite your tests, and" \
		"if it should happen again, we suggest eliminating this possibility by allowing the unit to remain in place and seeing whether or not it" \
		"actually fails. If the computer should turn out to be wrong, the situation is still not alarming. The type of obsessional error he may be" \
		"guilty of is not unknown among the latest generation of HAL 9000 computers. It has almost always revolved around a single detail, such as" \
		"the one you have described, and it has never interfered with the integrity or reliability of the computer's performance in other areas." \
		"No one is certain of the cause of this kind of malfunctioning. It may be over-programming, but it could also be any number of reasons. In any" \
		"event, it is somewhat analogous to human neurotic behavior. Does this answer your query?  Zero-five-three-Zero, MC, transmission concluded.";

	static const char *s_pComment = "This is a comment";

	int i, sort_iter;
	mz_bool status;
	size_t uncomp_size;
	mz_zip_archive zip_archive;
	void *p;
	const int N = 5; //50;
	char data[2048];
	char archive_filename[64];
	static const char *s_Test_archive_filename = "E:/GitCode/Messy_Test/testdata/miniz2.zip";

	assert((strlen(s_pTest_str) + 64) < sizeof(data));

	printf("miniz.c version: %s\n", MZ_VERSION);

	// Delete the test archive, so it doesn't keep growing as we run this test
	remove(s_Test_archive_filename);

	// Append a bunch of text files to the test archive
	for (i = (N - 1); i >= 0; --i) {
		sprintf(archive_filename, "%u.txt", i);
		sprintf(data, "%u %s %u", (N - 1) - i, s_pTest_str, i);

		// Add a new file to the archive. Note this is an IN-PLACE operation, so if it fails your archive is probably hosed (its central directory may not be complete) but it should be recoverable using zip -F or -FF. So use caution with this guy.
		// A more robust way to add a file to an archive would be to read it into memory, perform the operation, then write a new archive out to a temp file and then delete/rename the files.
		// Or, write a new archive to disk to a temp file, then delete/rename the files. For this test this API is fine.
		status = mz_zip_add_mem_to_archive_file_in_place(s_Test_archive_filename, archive_filename, data, strlen(data) + 1, s_pComment, (uint16)strlen(s_pComment), MZ_BEST_COMPRESSION);
		if (!status) {
			printf("mz_zip_add_mem_to_archive_file_in_place failed!\n");
			return EXIT_FAILURE;
		}
	}

	// Add a directory entry for testing
	status = mz_zip_add_mem_to_archive_file_in_place(s_Test_archive_filename, "directory/", NULL, 0, "no comment", (uint16)strlen("no comment"), MZ_BEST_COMPRESSION);
	if (!status) {
		printf("mz_zip_add_mem_to_archive_file_in_place failed!\n");
		return EXIT_FAILURE;
	}

	// Now try to open the archive.
	memset(&zip_archive, 0, sizeof(zip_archive));

	status = mz_zip_reader_init_file(&zip_archive, s_Test_archive_filename, 0);
	if (!status) {
		printf("mz_zip_reader_init_file() failed!\n");
		return EXIT_FAILURE;
	}

	// Get and print information about each file in the archive.
	for (i = 0; i < (int)mz_zip_reader_get_num_files(&zip_archive); i++) {
		mz_zip_archive_file_stat file_stat;
		if (!mz_zip_reader_file_stat(&zip_archive, i, &file_stat)) {
			printf("mz_zip_reader_file_stat() failed!\n");
			mz_zip_reader_end(&zip_archive);
			return EXIT_FAILURE;
		}

		printf("Filename: \"%s\", Comment: \"%s\", Uncompressed size: %u, Compressed size: %u, Is Dir: %u\n", file_stat.m_filename, file_stat.m_comment, (uint)file_stat.m_uncomp_size, (uint)file_stat.m_comp_size, mz_zip_reader_is_file_a_directory(&zip_archive, i));

		if (!strcmp(file_stat.m_filename, "directory/")) {
			if (!mz_zip_reader_is_file_a_directory(&zip_archive, i)) {
				printf("mz_zip_reader_is_file_a_directory() didn't return the expected results!\n");
				mz_zip_reader_end(&zip_archive);
				return EXIT_FAILURE;
			}
		}
	}

	// Close the archive, freeing any resources it was using
	mz_zip_reader_end(&zip_archive);

	// Now verify the compressed data
	for (sort_iter = 0; sort_iter < 2; sort_iter++) {
		memset(&zip_archive, 0, sizeof(zip_archive));
		status = mz_zip_reader_init_file(&zip_archive, s_Test_archive_filename, sort_iter ? MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY : 0);
		if (!status) {
			printf("mz_zip_reader_init_file() failed!\n");
			return EXIT_FAILURE;
		}

		for (i = 0; i < N; i++) {
			sprintf(archive_filename, "%u.txt", i);
			sprintf(data, "%u %s %u", (N - 1) - i, s_pTest_str, i);

			// Try to extract all the files to the heap.
			p = mz_zip_reader_extract_file_to_heap(&zip_archive, archive_filename, &uncomp_size, 0);
			if (!p) {
				printf("mz_zip_reader_extract_file_to_heap() failed!\n");
				mz_zip_reader_end(&zip_archive);
				return EXIT_FAILURE;
			}

			// Make sure the extraction really succeeded.
			if ((uncomp_size != (strlen(data) + 1)) || (memcmp(p, data, strlen(data)))) {
				printf("mz_zip_reader_extract_file_to_heap() failed to extract the proper data\n");
				mz_free(p);
				mz_zip_reader_end(&zip_archive);
				return EXIT_FAILURE;
			}

			printf("Successfully extracted file \"%s\", size %u\n", archive_filename, (uint)uncomp_size);
			printf("File data: \"%s\"\n", (const char *)p);

			// We're done.
			mz_free(p);
		}

		// Close the archive, freeing any resources it was using
		mz_zip_reader_end(&zip_archive);
	}

	printf("Success.\n");
	return EXIT_SUCCESS;
}

// Demonstrates how to use miniz.c's deflate() and inflate() functions for simple file compression.
// Command line tool for file compression/decompression.
int test_miniz_3()
{
	static uint8 s_inbuf[BUF_SIZE];
	static uint8 s_outbuf[BUF_SIZE];

	const char *pMode;
	FILE *pInfile, *pOutfile;
	uint infile_size;
	int level = Z_BEST_COMPRESSION;
	z_stream stream;
	int p = 1;
	const char *pSrc_filename;
	const char *pDst_filename;
	long file_loc;

	printf("miniz.c version: %s\n", MZ_VERSION);

	int argc = 5;
	char* argv[5] {"", "-l5", "c", "E:/GitCode/Messy_Test/testdata/infile.zip", "E:/GitCode/Messy_Test/testdata/outfile_compress.zip"};
	//char* argv[5] {"", "-l5", "d", "E:/GitCode/Messy_Test/testdata/outfile_compress.zip", "E:/GitCode/Messy_Test/testdata/outfile_decompress.zip"};

	if (argc < 4) {
		printf("Usage: example3 [options] [mode:c or d] infile outfile\n");
		printf("\nModes:\n");
		printf("c - Compresses file infile to a zlib stream in file outfile\n");
		printf("d - Decompress zlib stream in file infile to file outfile\n");
		printf("\nOptions:\n");
		printf("-l[0-10] - Compression level, higher values are slower.\n");
		return EXIT_FAILURE;
	}

	while ((p < argc) && (argv[p][0] == '-')) {
		switch (argv[p][1]) {
			case 'l': {
				level = atoi(&argv[1][2]);
				if ((level < 0) || (level > 10)) {
					printf("Invalid level!\n");
					return EXIT_FAILURE;
				}
				break;
			}
			default: {
				printf("Invalid option: %s\n", argv[p]);
				return EXIT_FAILURE;
			}
		}
		p++;
	}

	if ((argc - p) < 3) {
		printf("Must specify mode, input filename, and output filename after options!\n");
		return EXIT_FAILURE;
	} else if ((argc - p) > 3) {
		printf("Too many filenames!\n");
		return EXIT_FAILURE;
	}

	pMode = argv[p++];
	if (!strchr("cCdD", pMode[0])) {
		printf("Invalid mode!\n");
		return EXIT_FAILURE;
	}

	pSrc_filename = argv[p++];
	pDst_filename = argv[p++];

	printf("Mode: %c, Level: %u\nInput File: \"%s\"\nOutput File: \"%s\"\n", pMode[0], level, pSrc_filename, pDst_filename);

	// Open input file.
	pInfile = fopen(pSrc_filename, "rb");
	if (!pInfile) {
		printf("Failed opening input file!\n");
		return EXIT_FAILURE;
	}

	// Determine input file's size.
	fseek(pInfile, 0, SEEK_END);
	file_loc = ftell(pInfile);
	fseek(pInfile, 0, SEEK_SET);

	if ((file_loc < 0) || (file_loc > INT_MAX)) {
		// This is not a limitation of miniz or tinfl, but this example.
		printf("File is too large to be processed by this example.\n");
		return EXIT_FAILURE;
	}

	infile_size = (uint)file_loc;

	// Open output file.
	pOutfile = fopen(pDst_filename, "wb");
	if (!pOutfile) {
		printf("Failed opening output file!\n");
		return EXIT_FAILURE;
	}

	printf("Input file size: %u\n", infile_size);

	// Init the z_stream
	memset(&stream, 0, sizeof(stream));
	stream.next_in = s_inbuf;
	stream.avail_in = 0;
	stream.next_out = s_outbuf;
	stream.avail_out = BUF_SIZE;

	if ((pMode[0] == 'c') || (pMode[0] == 'C')) {
		// Compression.
		uint infile_remaining = infile_size;

		if (deflateInit(&stream, level) != Z_OK) {
			printf("deflateInit() failed!\n");
			return EXIT_FAILURE;
		}

		for (;;) {
			int status;
			if (!stream.avail_in) {
				// Input buffer is empty, so read more bytes from input file.
				uint n = my_min(BUF_SIZE, infile_remaining);

				if (fread(s_inbuf, 1, n, pInfile) != n) {
					printf("Failed reading from input file!\n");
					return EXIT_FAILURE;
				}

				stream.next_in = s_inbuf;
				stream.avail_in = n;

				infile_remaining -= n;
				//printf("Input bytes remaining: %u\n", infile_remaining);
			}

			status = deflate(&stream, infile_remaining ? Z_NO_FLUSH : Z_FINISH);

			if ((status == Z_STREAM_END) || (!stream.avail_out)) {
				// Output buffer is full, or compression is done, so write buffer to output file.
				uint n = BUF_SIZE - stream.avail_out;
				if (fwrite(s_outbuf, 1, n, pOutfile) != n) {
					printf("Failed writing to output file!\n");
					return EXIT_FAILURE;
				}
				stream.next_out = s_outbuf;
				stream.avail_out = BUF_SIZE;
			}

			if (status == Z_STREAM_END)
				break;
			else if (status != Z_OK) {
				printf("deflate() failed with status %i!\n", status);
				return EXIT_FAILURE;
			}
		}

		if (deflateEnd(&stream) != Z_OK) {
			printf("deflateEnd() failed!\n");
			return EXIT_FAILURE;
		}
	} else if ((pMode[0] == 'd') || (pMode[0] == 'D')) {
		// Decompression.
		uint infile_remaining = infile_size;

		if (inflateInit(&stream)) {
			printf("inflateInit() failed!\n");
			return EXIT_FAILURE;
		}

		for (;;) {
			int status;
			if (!stream.avail_in) {
				// Input buffer is empty, so read more bytes from input file.
				uint n = my_min(BUF_SIZE, infile_remaining);

				if (fread(s_inbuf, 1, n, pInfile) != n) {
					printf("Failed reading from input file!\n");
					return EXIT_FAILURE;
				}

				stream.next_in = s_inbuf;
				stream.avail_in = n;

				infile_remaining -= n;
			}

			status = inflate(&stream, Z_SYNC_FLUSH);

			if ((status == Z_STREAM_END) || (!stream.avail_out)) {
				// Output buffer is full, or decompression is done, so write buffer to output file.
				uint n = BUF_SIZE - stream.avail_out;
				if (fwrite(s_outbuf, 1, n, pOutfile) != n) {
					printf("Failed writing to output file!\n");
					return EXIT_FAILURE;
				}
				stream.next_out = s_outbuf;
				stream.avail_out = BUF_SIZE;
			}

			if (status == Z_STREAM_END)
				break;
			else if (status != Z_OK) {
				printf("inflate() failed with status %i!\n", status);
				return EXIT_FAILURE;
			}
		}

		if (inflateEnd(&stream) != Z_OK) {
			printf("inflateEnd() failed!\n");
			return EXIT_FAILURE;
		}
	} else {
		printf("Invalid mode!\n");
		return EXIT_FAILURE;
	}

	fclose(pInfile);
	if (EOF == fclose(pOutfile)) {
		printf("Failed writing to output file!\n");
		return EXIT_FAILURE;
	}

	printf("Total input bytes: %u\n", (mz_uint32)stream.total_in);
	printf("Total output bytes: %u\n", (mz_uint32)stream.total_out);
	printf("Success.\n");
	return EXIT_SUCCESS;
}

// Uses tinfl.c to decompress a zlib stream in memory to an output file
int test_miniz_4()
{
	// need include "tinfl.c", conflict with "miniz.c"
	// reference: example4.c
	return 0;
}

// Demonstrates how to use miniz.c's low-level tdefl_compress() and tinfl_inflate() API's for simple file to file compression/decompression.
// The low-level API's are the fastest, make no use of dynamic memory allocation, and are the most flexible functions exposed by miniz.c.
int test_miniz_5()
{
	// reference: example5.c
	// conflict with other examples(1/2/3)
	return 0;
}

// Demonstrates how to miniz's PNG writer func
int test_miniz_6()
{
	// reference: example6.c
	// conflict with other examples(1/2/3)
	return 0;
}
