#include "funset.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// Blog: https://blog.csdn.net/fengbingchun/article/details/81606432

#ifdef _MSC_VER
#include <Windows.h>
void utf8_to_gbk(const char* utf8, char* gbk)
{
	const int maxlen = 256;
	wchar_t unicode_str[maxlen];
	int outlen = MultiByteToWideChar(CP_UTF8, 0, utf8, strlen(utf8), unicode_str, maxlen);
	outlen = WideCharToMultiByte(CP_ACP, 0, unicode_str, outlen, gbk, 256, NULL, NULL);
	gbk[outlen] = '\0';
}
#else // linux
void utf8_to_gbk(const char* utf8, char* gbk)
{
	gbk = utf8;
}
#endif

int read_file(const char* filename, char** content)
{
	// open in read binary mode
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		fprintf(stderr, "read file fail: %s\n", filename);
		return -1;
	}

	// get the length
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	// allocate content buffer
	*content = (char*)malloc((size_t)length + sizeof(""));

	// read the file into memory
	size_t read_chars = fread(*content, sizeof(char), (size_t)length, file);
	if ((long)read_chars != length) {
		fprintf(stderr, "length dismatch: %d, %d\n", read_chars, length);
		free(*content);
		return -1;
	}
	(*content)[read_chars] = '\0';

	fclose(file);
	return 0;
}

int test_cjson_1()
{
	const char* filename = "E:/GitCode/Messy_Test/testdata/cjson_test7";
	char *json = NULL;
	if (read_file(filename, &json) != 0) return -1;;
	if ((json == NULL) || (json[0] == '\0') || (json[1] == '\0')) {
		fprintf(stderr, "file content is null\n");
		return -1;
	}

	cJSON* item = cJSON_Parse(json + 2);
	if (item == NULL) {
		fprintf(stderr, "pasre json file fail\n");
		return -1;
	}

	int do_format = 0;
	if (json[1] == 'f') do_format = 1;

	char *printed_json = NULL;
	if (json[0] == 'b') {
		// buffered printing
		printed_json = cJSON_PrintBuffered(item, 1, do_format);
	} else {
		// unbuffered printing
		if (do_format) printed_json = cJSON_Print(item);
		else printed_json = cJSON_PrintUnformatted(item);
	}

	if (printed_json == NULL) {
		fprintf(stderr, "print json fail\n");
		return -1;
	}
	printf("%s\n", printed_json);

	int num = cJSON_GetArraySize(item);
	for (int i = 0; i < num; ++i) {
		cJSON* arr = cJSON_GetArrayItem(item, i);
		if (arr == NULL) {
			fprintf(stderr, "get array item fail\n");
			return -1;
		}

		fprintf(stdout, "has item \"City\": %d; has item \"abc\": %d\n",
			cJSON_HasObjectItem(arr, "City"), cJSON_HasObjectItem(arr, "abc"));
		cJSON* tmp = cJSON_GetObjectItem(arr, "City");
		if (tmp != NULL)
			fprintf(stdout, "key: %s, value: %s\n", tmp->string, tmp->valuestring);
	}

	if (item != NULL) cJSON_Delete(item);
	if (json != NULL) free(json);
	if (printed_json != NULL) free(printed_json);

	return 0;
}

int test_cjson_2()
{
	const char* filename = "E:/GitCode/Messy_Test/testdata/json.data";
	char *json = NULL;
	if (read_file(filename, &json) != 0) return -1;;
	if ((json == NULL) || (json[0] == '\0') || (json[1] == '\0')) {
		fprintf(stderr, "file content is null\n");
		return -1;
	}

	cJSON* items = cJSON_Parse(json);
	if (items == NULL) {
		fprintf(stderr, "pasre json file fail\n");
		return -1;
	}

	char* printed_json = cJSON_PrintUnformatted(items);
	if (printed_json == NULL) {
		fprintf(stderr, "print json fail\n");
		return -1;
	}
	printf("%s\n\n", printed_json);

	cJSON*  item = cJSON_GetObjectItem(items, "name");
	fprintf(stdout, "key: %s, value: %s\n", "name", item->valuestring);

	char gbk[256];
	item = cJSON_GetObjectItem(items, "address");
	utf8_to_gbk(item->valuestring, gbk);
	fprintf(stdout, "key: %s, value: %s\n", "address", gbk);

	item = cJSON_GetObjectItem(items, "age");
	fprintf(stdout, "key: %s, value: %d\n", "age", item->valueint);

	item = cJSON_GetObjectItem(items, "value1");
	int size = cJSON_GetArraySize(item);
	for (int i = 0; i < size; ++i) {
		cJSON* tmp = cJSON_GetArrayItem(item, i);
		int len = cJSON_GetArraySize(tmp);
		fprintf(stdout, "key: %s:", "value1");
		for (int j = 0; j < len; ++j) {
			cJSON* tmp2 = cJSON_GetArrayItem(tmp, j);
			fprintf(stdout, " %f,", tmp2->valuedouble);
		}
		fprintf(stdout, "\n");
	}

	item = cJSON_GetObjectItem(items, "value2");
	size = cJSON_GetArraySize(item);
	fprintf(stdout, "key: %s:", "value2");
	for (int i = 0; i < size; ++i) {
		cJSON* tmp = cJSON_GetArrayItem(item, i);
		fprintf(stdout, " %f,", tmp->valuedouble);
	}
	fprintf(stdout, "\n");

	item = cJSON_GetObjectItem(items, "bei_jing");
	cJSON* tmp = cJSON_GetObjectItem(item, "address");
	utf8_to_gbk(tmp->valuestring, gbk);
	fprintf(stdout, "key: %s, value: %s\n", "address", gbk);
	tmp = cJSON_GetObjectItem(item, "car");
	fprintf(stdout, "key: %s, value: %d\n", "car", tmp->valueint);
	tmp = cJSON_GetObjectItem(item, "cat");
	fprintf(stdout, "key: %s, value: %d\n", "cat", tmp->valueint);

	item = cJSON_GetObjectItem(items, "shan_dong");
	tmp = cJSON_GetObjectItem(item, "address");
	utf8_to_gbk(tmp->valuestring, gbk);
	fprintf(stdout, "key: %s, value: %s\n", "address", gbk);
	tmp = cJSON_GetObjectItem(item, "value1");
	size = cJSON_GetArraySize(tmp);
	for (int i = 0; i < size; ++i) {
		char* names[2] = { "ji_nan", "tai_an" };
		cJSON* tmp2 = cJSON_GetArrayItem(tmp, i);
		cJSON* tmp3 = cJSON_GetObjectItem(tmp2, names[i]);
		utf8_to_gbk(tmp3->valuestring, gbk);
		fprintf(stdout, "key: %s, value: %s\n",names[i], gbk);
	}

	if (items != NULL) cJSON_Delete(items);
	if (json != NULL) free(json);
	if (printed_json != NULL) free(printed_json);

	return 0;
}

