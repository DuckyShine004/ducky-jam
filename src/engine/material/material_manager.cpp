#include "engine/graphic/material/material_manager.hpp"

namespace engine::graphic::material {

MaterialManager::MaterialManager() = default;

MaterialManager::~MaterialManager() = default;

MaterialManager &MaterialManager::get_instance() {
    static MaterialManager instance;

    return instance;
}

void MaterialManager::initialise() {
    m_material_id = 0;
}

int MaterialManager::add_material() {
    ++m_material_id;

    return m_material_id;
}

Material &MaterialManager::get_material(int material_id) {
    return *m_materials.at(material_id);
}

} // namespace engine::graphic::material
