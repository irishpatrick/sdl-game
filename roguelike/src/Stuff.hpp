#pragma once

#include <string>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

bool json_has(json&, const std::string&);
