#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "engine/graphic/material/material.hpp"

namespace engine::graphic::material {

class MaterialManager {
  public:
    MaterialManager(const MaterialManager &) = delete;
    MaterialManager &operator=(const MaterialManager &) = delete;

    static MaterialManager &get_instance();

    void initialise();
    int add_material();

    engine::graphic::material::Material &get_material(int material_id);

  private:
    MaterialManager();
    ~MaterialManager();

    int m_material_id;

    std::vector<std::unique_ptr<engine::graphic::material::Material>> m_materials;
    std::unordered_map<std::string, int> m_material_references;
};

} // namespace engine::graphic::material
