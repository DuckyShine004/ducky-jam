#pragma once

#include "database/models/resource_model.hpp"
#include "database/storage.hpp"

namespace database::repositories {

class ResourceRepository {
  public:
    ResourceRepository(database::Storage &storage);

    int create(const database::models::ResourceModel &resource);

    std::vector<database::models::ResourceModel> find_all_with_extension(const std::string &extension);
    std::vector<database::models::ResourceModel> find_all_audios();

  private:
    database::Storage &m_storage;
};

} // namespace database::repositories
