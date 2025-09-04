#ifndef FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_H_
#define FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_H_

#include <flutter_linux/flutter_linux.h>

G_BEGIN_DECLS

#ifdef FLUTTER_PLUGIN_IMPL
#define FLUTTER_PLUGIN_EXPORT __attribute__((visibility("default")))
#else
#define FLUTTER_PLUGIN_EXPORT
#endif

typedef struct _IrondashPlusEngineContextPlugin IrondashPlusEngineContextPlugin;
typedef struct {
  GObjectClass parent_class;
} IrondashPlusEngineContextPluginClass;

FLUTTER_PLUGIN_EXPORT GType irondash_plus_engine_context_plugin_get_type();

FLUTTER_PLUGIN_EXPORT
uint64_t IrondashPlusEngineContextGetMainThreadId();

FLUTTER_PLUGIN_EXPORT FlView *
IrondashPlusEngineContextGetFlutterView(int64_t engine_handle);

FLUTTER_PLUGIN_EXPORT FlBinaryMessenger *
IrondashPlusEngineContextGetBinaryMessenger(int64_t engine_handle);

FLUTTER_PLUGIN_EXPORT FlTextureRegistrar *
IrondashPlusEngineContextGetTextureRegistrar(int64_t engine_handle);

typedef void (*EngineDestroyedCallback)(int64_t);
FLUTTER_PLUGIN_EXPORT void IrondashPlusEngineContextRegisterDestroyNotification(
    EngineDestroyedCallback callback);

FLUTTER_PLUGIN_EXPORT void
irondash_plus_engine_context_plugin_register_with_registrar(
    FlPluginRegistrar *registrar);

G_END_DECLS

#endif // FLUTTER_PLUGIN_IRONDASH_PLUS_ENGINE_CONTEXT_PLUGIN_H_
