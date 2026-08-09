#include "database/repositories/resource_repository.hpp"

#include <sys/wait.h>

namespace database::repositories {

ResourceRepository::ResourceRepository(Storage &storage) : m_storage(storage) {
}

int ResourceRepository::create(const models::ResourceModel &resource) {
    return m_storage.insert(resource);
}

std::vector<models::ResourceModel> ResourceRepository::find_all_with_extension(const std::string &extension) {
    return m_storage.get_all<models::ResourceModel>(sqlite_orm::where(sqlite_orm::c(&models::ResourceModel::extension) == extension));
}

std::vector<models::ResourceModel> ResourceRepository::find_all_audios() {
    return find_all_with_extension(".mp3");
}

} // namespace database::repositories
