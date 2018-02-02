#include "unordered_map.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52235026

//////////////////////////////////////////////////
// reference: http://en.cppreference.com/w/cpp/container/unordered_map
int test_unordered_map1()
{
	// Create an unordered_map of three strings (that map to strings)
	std::unordered_map<std::string, std::string> u = {
			{ "RED", "#FF0000" },
			{ "GREEN", "#00FF00" },
			{ "BLUE", "#0000FF" }
	};

	// Iterate and print keys and values of unordered_map
	for (const auto& n : u) {
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
	}

	// Add two new entries to the unordered_map
	u["BLACK"] = "#000000";
	u["WHITE"] = "#FFFFFF";

	// Output values by key
	std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
	std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n";

	std::cout << "The u's size: " << u.size() << std::endl;

	return 0;
}

/////////////////////////////////////////////////////
// reference: http://www.cplusplus.com/reference/unordered_map/unordered_map/at/
typedef std::unordered_map<std::string, std::string> stringmap;

stringmap merge(stringmap a, stringmap b) {
	stringmap temp(a); temp.insert(b.begin(), b.end()); return temp;
}

int test_unordered_map2()
{
	////////// at/size
	std::unordered_map<std::string, int> mymap = { { "Mars", 3000 }, { "Saturn", 60000 }, { "Jupiter", 70000 } };

	mymap.at("Mars") = 3396;
	mymap.at("Saturn") += 272;
	mymap.at("Jupiter") = mymap.at("Saturn") + 9638;

	for (auto& x : mymap) {
		std::cout << x.first << ": " << x.second << std::endl;
	}

	std::cout << "mymap.size() is " << mymap.size() << std::endl;

	/////////// begin
	std::unordered_map<std::string, std::string> mymap2 = { { "Australia", "Canberra" }, { "U.S.", "Washington" }, { "France", "Paris" } };

	std::cout << "mymap2 contains:";
	for (auto it = mymap2.begin(); it != mymap2.end(); ++it)
		std::cout << " " << it->first << ":" << it->second;
	std::cout << std::endl;

	std::cout << "mymap2's buckets contain:\n";
	for (unsigned i = 0; i < mymap2.bucket_count(); ++i) {
		std::cout << "bucket #" << i << " contains:";
		for (auto local_it = mymap2.begin(i); local_it != mymap2.end(i); ++local_it)
			std::cout << " " << local_it->first << ":" << local_it->second;
		std::cout << std::endl;
	}

	////////////// bucket
	std::unordered_map<std::string, std::string> mymap3 = {
			{ "us", "United States" },
			{ "uk", "United Kingdom" },
			{ "fr", "France" },
			{ "de", "Germany" }
	};

	for (auto& x : mymap3) {
		std::cout << "Element [" << x.first << ":" << x.second << "]";
		std::cout << " is in bucket #" << mymap3.bucket(x.first) << std::endl;
	}

	/////////////// count
	std::unordered_map<std::string, double> mymap4 = {
			{ "Burger", 2.99 },
			{ "Fries", 1.99 },
			{ "Soda", 1.50 } };

	for (auto& x : { "Burger", "Pizza", "Salad", "Soda" }) {
		if (mymap4.count(x)>0)
			std::cout << "mymap4 has " << x << std::endl;
		else
			std::cout << "mymap4 has no " << x << std::endl;
	}

	///////////////// erase
	std::unordered_map<std::string, std::string> mymap5;

	// populating container:
	mymap5["U.S."] = "Washington";
	mymap5["U.K."] = "London";
	mymap5["France"] = "Paris";
	mymap5["Russia"] = "Moscow";
	mymap5["China"] = "Beijing";
	mymap5["Germany"] = "Berlin";
	mymap5["Japan"] = "Tokyo";

	// erase examples:
	mymap5.erase(mymap5.begin());      // erasing by iterator
	mymap5.erase("France");             // erasing by key
	mymap5.erase(mymap5.find("China"), mymap5.end()); // erasing by range

	// show content:
	for (auto& x : mymap5)
		std::cout << x.first << ": " << x.second << std::endl;

	////////////////////// find
	std::unordered_map<std::string, double> mymap6 = {
			{ "mom", 5.4 },
			{ "dad", 6.1 },
			{ "bro", 5.9 } };

	std::string input;
	std::cout << "who? ";
	getline(std::cin, input);

	std::unordered_map<std::string, double>::const_iterator got = mymap6.find(input);

	if (got == mymap6.end())
		std::cout << "not found";
	else
		std::cout << got->first << " is " << got->second;

	std::cout << std::endl;

	//////////////////// insert
	std::unordered_map<std::string, double>
		myrecipe,
		mypantry = { { "milk", 2.0 }, { "flour", 1.5 } };

	std::pair<std::string, double> myshopping("baking powder", 0.3);

	myrecipe.insert(myshopping);                        // copy insertion
	myrecipe.insert(std::make_pair<std::string, double>("eggs", 6.0)); // move insertion
	myrecipe.insert(mypantry.begin(), mypantry.end());  // range insertion
	myrecipe.insert({ { "sugar", 0.8 }, { "salt", 0.1 } });    // initializer list insertion

	std::cout << "myrecipe contains:" << std::endl;
	for (auto& x : myrecipe)
		std::cout << x.first << ": " << x.second << std::endl;

	std::cout << std::endl;

	//////////////////// =
	stringmap first = { { "AAPL", "Apple" }, { "MSFT", "Microsoft" } };  // init list
	stringmap second = { { "GOOG", "Google" }, { "ORCL", "Oracle" } };   // init list
	stringmap third = merge(first, second);                      // move
	first = third;                                    // copy

	std::cout << "first contains:";
	for (auto& elem : first) std::cout << " " << elem.first << ":" << elem.second;
	std::cout << std::endl;

	return 0;
}

//////////////////////////////////////////////////////
// reference: http://www.geeksforgeeks.org/unordered_map-in-stl-and-its-applications/
int test_unordered_map3()
{
	// key will be of string type and mapped value will be of double type
	std::unordered_map<std::string, double> umap;

	// inserting values by using [] operator
	umap["PI"] = 3.14;
	umap["root2"] = 1.414;
	umap["root3"] = 1.732;
	umap["log10"] = 2.302;
	umap["loge"] = 1.0;

	// inserting value by insert function
	umap.insert(std::make_pair("e", 2.718));

	std::string key = "PI";

	// If key not found in map iterator to end is returned
	if (umap.find(key) == umap.end()) {
		std::cout << key << " not found\n\n";
	} else {// If key found then iterator to that key is returned
		std::cout << "Found " << key << "\n\n";
	}

	key = "lambda";
	if (umap.find(key) == umap.end())
		std::cout << key << " not found\n";
	else
		std::cout << "Found " << key << std::endl;

	//  iterating over all value of umap
	std::unordered_map<std::string, double>::iterator itr;
	std::cout << "\nAll Elements : \n";
	for (itr = umap.begin(); itr != umap.end(); itr++) {
		// itr works as a pointer to pair<string, double> type itr->first stores the key part
		// and itr->second stroes the value part
		std::cout << itr->first << "  " << itr->second << std::endl;
	}

	return 0;
}
