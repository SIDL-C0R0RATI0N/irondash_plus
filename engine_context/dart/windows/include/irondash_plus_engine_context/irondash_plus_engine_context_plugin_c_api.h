#ifndef FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_C_API_H_
#define FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_C_API_H_

#include <flutter_plugin_registrar.h>
#include <stdint.h>

#ifdef FLUTTER_PLUGIN_IMPL
#define FLUTTER_PLUGIN_EXPORT __declspec(dllexport)
#else
#define FLUTTER_PLUGIN_EXPORT __declspec(dllimport)
#endif

#if defined(__cplusplus)
extern "C" {
#endif

FLUTTER_PLUGIN_EXPORT void IrondashPlusEngineContextPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar);

FLUTTER_PLUGIN_EXPORT void
IrondashPlusEngineContextPerformOnMainThread(void (*callback)(void *data),
                                         void *data);

FLUTTER_PLUGIN_EXPORT unsigned long IrondashPlusEngineContextGetMainThreadId();

FLUTTER_PLUGIN_EXPORT size_t
IrondashPlusEngineContextGetFlutterView(int64_t engine_handle);

FLUTTER_PLUGIN_EXPORT FlutterDesktopTextureRegistrarRef
IrondashPlusEngineContextGetTextureRegistrar(int64_t engine_handle);

FLUTTER_PLUGIN_EXPORT FlutterDesktopMessengerRef
IrondashPlusEngineContextGetBinaryMessenger(int64_t engine_handle);

typedef void (*EngineDestroyedCallback)(int64_t);
FLUTTER_PLUGIN_EXPORT void IrondashPlusEngineContextRegisterDestroyNotification(
    EngineDestroyedCallback callback);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_C_API_H_
