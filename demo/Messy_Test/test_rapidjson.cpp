#include "funset.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <string>
#include "common.hpp"

// Blog: https://blog.csdn.net/fengbingchun/article/details/91139889 

int test_rapidjson_parse()
{
#ifdef _MSC_VER
	const char* file_name = "../../../testdata/json.data";
#else
	const char* file_name = "testdata/json.data";
#endif
	std::ifstream in(file_name);
	if (!in.is_open()) {
		fprintf(stderr, "fail to read json file: %s\n", file_name);
		return -1;
	}

	std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();

	rapidjson::Document dom;
	if (!dom.Parse(json_content.c_str()).HasParseError()) {
		if (dom.HasMember("name") && dom["name"].IsString()) {
			fprintf(stdout, "name: %s\n", dom["name"].GetString());
		}

		if (dom.HasMember("address") && dom["address"].IsString()) {
			fprintf(stdout, "address: %s\n", utf8_to_gbk(dom["address"].GetString()));
		}

		if (dom.HasMember("age") && dom["age"].IsInt()) {
			fprintf(stdout, "age: %d\n", dom["age"].GetInt());
		}

		const char* tmp = "xxx";
		if (!dom.HasMember(tmp)) {
			fprintf(stdout, "Warning: it has no member: %s\n", tmp);
		}

		if (dom.HasMember("value1") && dom["value1"].IsArray()) {
			const rapidjson::Value& arr = dom["value1"];
			for (int i = 0; i < arr.Size(); ++i) {
				const rapidjson::Value& tmp = arr[i];
				
				fprintf(stdout, "value1:\ni = %d:", i);
				for (int j = 0; j < tmp.Size(); ++j) {
					if (tmp[j].IsInt())
						fprintf(stdout, "%d, ", tmp[j].GetInt());
					if (tmp[j].IsFloat())
						fprintf(stdout, "%.1f, ", tmp[j].GetFloat());
				}
				fprintf(stdout, "\n");
			}
		}

		if (dom.HasMember("value2") && dom["value2"].IsArray()) {
			const rapidjson::Value& arr = dom["value2"];

			fprintf(stdout, "value2: ");
			for (int i = 0; i < arr.Size(); ++i) {
				fprintf(stdout, "%.2f, ", arr[i].GetFloat());
			}
			fprintf(stdout, "\n");
		}

		if (dom.HasMember("bei_jing") && dom["bei_jing"].IsObject()) {
			const rapidjson::Value& obj = dom["bei_jing"];

			if (obj.HasMember("address") && obj["address"].IsString()) {
				fprintf(stdout, "address: %s\n", utf8_to_gbk(obj["address"].GetString()));
			}

			if (obj.HasMember("car") && obj["car"].IsBool()) {
				fprintf(stdout, "car: %d\n", obj["car"].GetBool());
			}

			if (obj.HasMember("cat") && obj["cat"].IsBool()) {
				fprintf(stdout, "cat: %d\n", obj["cat"].GetBool());
			}
		}

		if (dom.HasMember("shan_dong") && dom["shan_dong"].IsObject()) {
			const rapidjson::Value& obj = dom["shan_dong"];

			if (obj.HasMember("address") && obj["address"].IsString()) {
				fprintf(stdout, "address: %s\n", utf8_to_gbk(obj["address"].GetString()));
			}

			if (obj.HasMember("value1") && obj["value1"].IsArray()) {
				const rapidjson::Value& arr = obj["value1"];

				if (arr[0].HasMember("ji_nan") && arr[0]["ji_nan"].IsString()) {
					fprintf(stdout, "ji_nan: %s\n", utf8_to_gbk(arr[0]["ji_nan"].GetString()));
				}

				if (arr[0].HasMember("tai_an") && arr[0]["tai_an"].IsString()) {
					fprintf(stdout, "tai_an: %s\n", utf8_to_gbk(arr[0]["tai_an"].GetString()));
				}
			}
		}
	} else {
		fprintf(stderr, "fail to parse json file: %s\n", file_name);
		return -1;
	}

	// iter json
	for (rapidjson::Value::ConstMemberIterator iter = dom.MemberBegin(); iter != dom.MemberEnd(); ++iter) {
		fprintf(stdout, "iter json name: %s, type: %d\n", iter->name.GetString(), iter->value.GetType());
	}

	return 0;
}

int test_rapidjson_write()
{
	rapidjson::StringBuffer buf;
	//rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buf); // it can word wrap

	writer.StartObject();

	writer.Key("name"); writer.String("spring");
	writer.Key("address"); writer.String("北京");
	writer.Key("age"); writer.Int(30);

	writer.Key("value1");
	writer.StartArray();
	writer.StartArray();

	writer.StartObject();

	writer.Key("name"); writer.String("spring");
	writer.Key("address"); writer.String("北京");
	writer.Key("age"); writer.Int(30);

	writer.Key("value1");
	writer.StartArray();
	writer.StartArray();
	writer.Double(23); writer.Double(43); writer.Double(-2.3); writer.Double(6.7); writer.Double(90);
	writer.EndArray();

	writer.StartArray();
	writer.Int(-9); writer.Int(-19); writer.Int(10); writer.Int(2);
	writer.EndArray();

	writer.StartArray();
	writer.Int(-5); writer.Int(-55);
	writer.EndArray();
	writer.EndArray();

	writer.Key("value2");
	writer.StartArray();
	writer.Double(13.3); writer.Double(1.9); writer.Double(2.10);
	writer.EndArray();

	writer.Key("bei_jing");
	writer.StartObject();
	writer.Key("address"); writer.String("海淀");
	writer.Key("car"); writer.Bool(false);
	writer.Key("cat"); writer.Bool(true);
	writer.EndObject();

	writer.Key("shan_dong");
	writer.StartObject();
	writer.Key("address"); writer.String("济南");
	writer.Key("value1");
	writer.StartArray();
	writer.Key("ji_nan"); writer.String("趵突泉");
	writer.Key("tai_an"); writer.String("泰山");
	writer.EndArray();
	writer.EndObject();

	writer.EndObject();

	const char* json_content = buf.GetString();
	fprintf(stdout, "json content: %s\n", json_content);

#ifdef _MSC_VER
	const char* file_name = "../../../testdata/out.json";
#else
	const char* file_name = "testdata/out.json";
#endif
	std::ofstream outfile;
	outfile.open(file_name);
	if (!outfile.is_open()) {
		fprintf(stderr, "fail to open file to write: %s\n", file_name);
		return -1;
	}

	outfile << json_content << std::endl;
	outfile.close();

	return 0;
}

