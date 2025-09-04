#ifndef FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_H_
#define FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>
#include <minwindef.h>

namespace irondash_plus_engine_context {

typedef void (*EngineDestroyedCallback)(int64_t);

void IrondashPlusEngineContextPerformOnMainThread(void (*callback)(void *data), void *data);
DWORD IrondashPlusEngineContextGetMainThreadId();

size_t IrondashPlusEngineContextGetFlutterView(int64_t engine_handle);
FlutterDesktopTextureRegistrarRef IrondashPlusEngineContextGetTextureRegistrar(int64_t engine_handle);
FlutterDesktopMessengerRef IrondashPlusEngineContextGetBinaryMessenger(int64_t engine_handle);
void IrondashPlusEngineContextRegisterDestroyNotification(EngineDestroyedCallback callback);

class IrondashPlusEngineContextPlugin : public flutter::Plugin {
public:
  static void
  RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar,
                        FlutterDesktopPluginRegistrarRef raw_registrar);

  IrondashPlusEngineContextPlugin(int64_t engine_handle);

  virtual ~IrondashPlusEngineContextPlugin();

  // Disallow copy and assign.
  IrondashPlusEngineContextPlugin(const IrondashPlusEngineContextPlugin &) = delete;
  IrondashPlusEngineContextPlugin &
  operator=(const IrondashPlusEngineContextPlugin &) = delete;

private:
  int64_t engine_handle_;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

} // namespace irondash_plus_engine_context

#endif // FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_H_
