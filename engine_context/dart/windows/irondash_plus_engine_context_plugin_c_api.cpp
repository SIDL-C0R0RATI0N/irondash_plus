#include "include/irondash_plus_engine_context/irondash_plus_engine_context_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "irondash_plus_engine_context_plugin.h"

void IrondashPlusEngineContextPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  irondash_plus_engine_context::IrondashPlusEngineContextPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar),
      registrar);
}

void IrondashPlusEngineContextPerformOnMainThread(void (*callback)(void *data),
                                              void *data) {
  irondash_plus_engine_context::PerformOnMainThread(callback, data);
}

unsigned long IrondashPlusEngineContextGetMainThreadId() {
  return irondash_plus_engine_context::GetMainThreadId();
}

size_t IrondashPlusEngineContextGetFlutterView(int64_t engine_handle) {
  return irondash_plus_engine_context::GetFlutterView(engine_handle);
}

FlutterDesktopTextureRegistrarRef
IrondashPlusEngineContextGetTextureRegistrar(int64_t engine_handle) {
  return irondash_plus_engine_context::GetTextureRegistrar(engine_handle);
}

FlutterDesktopMessengerRef
IrondashPlusEngineContextGetBinaryMessenger(int64_t engine_handle) {
  return irondash_plus_engine_context::GetBinaryMessenger(engine_handle);
}

void IrondashPlusEngineContextRegisterDestroyNotification(
    EngineDestroyedCallback callback) {
  return irondash_plus_engine_context::RegisterDestroyNotification(callback);
}