#import "IrondashPlusEngineContextPlugin.h"

#import <objc/message.h>

// Flutter API doesn't provide an official way to get a view from registrar.
// This will likely break in future when multiple views per engine are
// supported. But that will be a major breaking change anyway.
@interface _FlutterPluginRegistrar : NSObject
@property(readwrite, nonatomic) FlutterEngine *flutterEngine;
@end

@interface _IrondashPlusEngineContext : NSObject {
@public
  __weak FlutterEngine *engine;
}

@end

@implementation _IrondashPlusEngineContext

@end

@interface IrondashPlusEngineContextPlugin () {
  int64_t engineHandle;
}
@end

@interface _IrondashPlusAssociatedObject : NSObject {
  int64_t engineHandle;
}

- (instancetype)initWithEngineHandle:(int64_t)engineHandle;

@end

@implementation IrondashPlusEngineContextPlugin

typedef void (^EngineDestroyedHandler)(int64_t);
typedef void (*EngineDestroyedCallback)(int64_t);

static NSMutableDictionary<NSNumber *, _IrondashPlusEngineContext *> *registry;
static int64_t nextHandle = 1;
static NSMutableArray<EngineDestroyedHandler> *engineDestroyedHandlers;

static char associatedObjectKey;

+ (void)initialize {
  registry = [NSMutableDictionary new];
  engineDestroyedHandlers = [NSMutableArray new];
}

+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar> *)registrar {
  int64_t engineHandle = nextHandle++;

  IrondashPlusEngineContextPlugin *instance =
      [[IrondashPlusEngineContextPlugin alloc] init];
  instance->engineHandle = engineHandle;

  _IrondashPlusEngineContext *context = [_IrondashPlusEngineContext new];
  context->engine = ((_FlutterPluginRegistrar *)registrar).flutterEngine;
  // There is no unregister callback on macOS, which means we'll leak
  // an _IrondashPlusEngineContext instance for every engine. Fortunately the
  // instance is tiny and only uses weak pointers to reference engine artifacts.
  [registry setObject:context forKey:@(instance->engineHandle)];

  // There is no destroy notification on macOS, so track the lifecycle of
  // BinaryMessenger.
  _IrondashPlusAssociatedObject *object =
      [[_IrondashPlusAssociatedObject alloc] initWithEngineHandle:engineHandle];
  objc_setAssociatedObject(context->engine, &associatedObjectKey, object,
                           OBJC_ASSOCIATION_RETAIN);

  FlutterMethodChannel *channel =
      [FlutterMethodChannel methodChannelWithName:@"dev.irondash_plus.engine_context"
                                  binaryMessenger:[registrar messenger]];
  [registrar addMethodCallDelegate:instance channel:channel];
}

- (void)handleMethodCall:(FlutterMethodCall *)call
                  result:(FlutterResult)result {
  if ([@"getEngineHandle" isEqualToString:call.method]) {
    result(@(engineHandle));
  } else {
    result(FlutterMethodNotImplemented);
  }
}

+ (UIView *)getFlutterView:(int64_t)engineHandle {
  _IrondashPlusEngineContext *context = [registry objectForKey:@(engineHandle)];
  return context->engine.viewController.view;
}

+ (id<FlutterTextureRegistry>)getTextureRegistry:(int64_t)engineHandle {
  _IrondashPlusEngineContext *context = [registry objectForKey:@(engineHandle)];
  return context->engine;
}

+ (id<FlutterBinaryMessenger>)getBinaryMessenger:(int64_t)engineHandle {
  _IrondashPlusEngineContext *context = [registry objectForKey:@(engineHandle)];
  return context->engine.binaryMessenger;
}

+ (void)registerEngineDestroyedCallback:(EngineDestroyedCallback)callback {
  [engineDestroyedHandlers addObject:^(int64_t handle) {
    callback(handle);
  }];
}

@end

@implementation _IrondashPlusAssociatedObject

- (instancetype)initWithEngineHandle:(int64_t)engineHandle {
  if (self = [super init]) {
    self->engineHandle = engineHandle;
  }
  return self;
}

- (void)dealloc {
  for (EngineDestroyedHandler handler in engineDestroyedHandlers) {
    handler(self->engineHandle);
  }
  [registry removeObjectForKey:@(self->engineHandle)];
}

@end
