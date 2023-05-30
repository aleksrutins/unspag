#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace unspag {
	auto InitConfig(fs::path path) -> int {
		if(fs::exists(path)) {
			cerr << "Warning: configuration path " << path << " already exists; overwriting." << endl;
		}

		ofstream stream(path);

		stream << "% This is your configuration file." << endl;

		stream.close();

		cerr << "Wrote configuration " << path << endl;

		return 0;
	}
}