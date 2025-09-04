//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <irondash_plus_engine_context/irondash_plus_engine_context_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) irondash_plus_engine_context_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "IrondashPlusEngineContextPlugin");
  irondash_plus_engine_context_plugin_register_with_registrar(irondash_plus_engine_context_registrar);
}
