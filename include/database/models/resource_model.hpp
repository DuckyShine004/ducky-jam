#pragma once

#include <string>

namespace database::models {

struct ResourceModel {
    int id = 0;
    std::string hash;
    std::string filename;
    std::string extension;
};

} // namespace database::models
