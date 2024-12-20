#ifndef WORLD_CONFIGURATOR_HPP
#define WORLD_CONFIGURATOR_HPP

#include "npc.hpp"
#include "field_configs.hpp"
#include "npc_properties_configs.hpp"
#include "attacker_visitors.hpp"
#include "factories.hpp"
#include <cstdlib>
#include <filesystem>
#include <shared_mutex>
#include <string>

class WorldConfigurator {
public:
    WorldConfigurator();

    static ptr<WorldConfigurator> create();
    ptr<AttackerVisitor> get_attacker_visitor(NpcType type) const;
    int get_max_x() const;
    int get_max_y() const;

    std::vector<ptr<NPC>> npcs;

private:
    std::string npc_properties_config_file_path_env = "NPC_PROPERTIES_CONFIG";
    std::string npc_properties_config_file_path;
    ptr<NpcPropertiesConfig> npc_properties_config;

    std::string field_config_file_path_env = "FIELD_CONFIG";
    std::string field_config_file_path;

    ptr<FieldConfig> field_config;
    std::vector<NpcFieldConfigData> npcs_field_data;

    int field_max_x;
    int field_max_y;

    std::unordered_map<NpcType, ptr<NpcFactory>> npc_factories;
    ptr<NpcGenerator> npc_generator;
    std::unordered_map<NpcType, ptr<AttackerVisitor>> attacker_visitors;

    std::string get_config_file_path(const std::string &env);
    void setup_npc_properties_config();
    void setup_npc_generator();
    void setup_field_config();
    void setup_attacker_visitors();
    void setup_factories();
    void setup_field_size();
    void generate_npcs();
};

#endif // WORLD_CONFIGURATOR
