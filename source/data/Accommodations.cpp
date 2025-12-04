#include<iostream>
#include<fstream>
#include<direct.h>
#include <unordered_map>
#include"../../header/data/Accommodations.h"
#include"../../source/data/library/json.hpp"

namespace
{
	std::string FILE_PATH;
}



// static definition for maps
std::unordered_map<std::string, long long> Accommodations::locationIndexMap;
std::unordered_map<std::string, long long> Accommodations::nameIndexMap;
std::unordered_map<std::string, long long> Accommodations::numberIndexMap;

void Accommodations::init() {
	FILE_PATH =  R"(..\data\data\DormitoryData.json)";
}

nlohmann::json Accommodations::readFromJson() {
	
	std::ifstream in_file(FILE_PATH);
	nlohmann::json newData = nlohmann::json::parse(in_file);
	if (!newData.contains("dormitory_building") || !newData["dormitory_building"].is_array()) {
		newData["dormitory_building"] = nlohmann::json::array();
	}
	in_file.close();
	return newData;
}

bool Accommodations::writeInFile() {
	std::ofstream out_file(FILE_PATH);
	if (!out_file.is_open()) {
		return false;
	}
	out_file << data.dump(4);
	out_file.close();
	return true;
}

nlohmann::json Accommodations::getBuildingJson(int index) {
	if (index >= 0 && index < data["dormitory_building"].size())return data["dormitory_building"][index];
	return nlohmann::json();
}

// Build the index maps from the JSON file (or provided data)
void Accommodations::buildIndexMaps() {
	locationIndexMap.clear();
	nameIndexMap.clear();
	numberIndexMap.clear();
	nlohmann::json j = readFromJson();
	long long idx = 0;
	for (auto& b : j["dormitory_building"]) {
		if (b.contains("building_location") && b["building_location"].is_string()) {
			std::string loc = (std::string)b["building_location"];
			if (locationIndexMap.find(loc) == locationIndexMap.end()) {
				locationIndexMap.emplace(loc, idx);
			}
		}
		if (b.contains("building_name") && b["building_name"].is_string()) {
			std::string name = (std::string)b["building_name"];
			if (nameIndexMap.find(name) == nameIndexMap.end()) {
				nameIndexMap.emplace(name, idx);
			}
		}
		if (b.contains("building_number") && b["building_number"].is_string()) {
			std::string num = (std::string)b["building_number"];
			if (numberIndexMap.find(num) == numberIndexMap.end()) {
				numberIndexMap.emplace(num, idx);
			}
		}
		idx++;
	}
}

Accommodations::Accommodations() {
	init();
	if (!this->data.contains("dormitory_building") || !this->data["dormitory_building"].is_array()) {
		this->data["dormitory_building"] = nlohmann::json::array();
	}
	data = readFromJson();
	// build the maps for O(1) lookups
	buildIndexMaps();
}

void Accommodations::addBulidings(BuildingData data) {
	if (!this->data.contains("dormitory_building") || !this->data["dormitory_building"].is_array()) {
		this->data["dormitory_building"] = nlohmann::json::array();
	}
	this->data["dormitory_building"].push_back(data.getBuildingData());
	// update maps for the newly added building
	long long newIndex = (long long)this->data["dormitory_building"].size() - 1;
	nlohmann::json bd = data.getBuildingData();
	if (bd.contains("building_location") && bd["building_location"].is_string()) {
		std::string loc = (std::string)bd["building_location"];
		if (locationIndexMap.find(loc) == locationIndexMap.end()) {
			locationIndexMap.emplace(loc, newIndex);
		}
	}
	if (bd.contains("building_name") && bd["building_name"].is_string()) {
		std::string name = (std::string)bd["building_name"];
		if (nameIndexMap.find(name) == nameIndexMap.end()) {
			nameIndexMap.emplace(name, newIndex);
		}
	}
	if (bd.contains("building_number") && bd["building_number"].is_string()) {
		std::string num = (std::string)bd["building_number"];
		if (numberIndexMap.find(num) == numberIndexMap.end()) {
			numberIndexMap.emplace(num, newIndex);
		}
	}
}

long long Accommodations::findBulidingByName(std::string name) {
	if (nameIndexMap.empty()) buildIndexMaps();
	auto it = nameIndexMap.find(name);
	if (it == nameIndexMap.end()) return -1;
	return it->second;
}

long long Accommodations::findBulidingByNumber(std::string number) {
	if (numberIndexMap.empty()) buildIndexMaps();
	auto it = numberIndexMap.find(number);
	if (it == numberIndexMap.end()) return -1;
	return it->second;
}

long long Accommodations::findBulidingByLocation(std::string location) {
	// ensure map is built
	if (locationIndexMap.empty()) {
		buildIndexMaps();
	}
	auto it = locationIndexMap.find(location);
	if (it == locationIndexMap.end()) return -1;
	return it->second;
}