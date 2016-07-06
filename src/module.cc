/**
 * callsync-os-addon
 * made by goldworm
 */

#include <uv.h>
#include <node.h>
#include "idleTime.h"

using namespace v8;

void GetIdleTime_ms(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    const uint32_t idleTime_ms = (uint32_t)getIdleTime_ms();

    Local<Number> js_ret = Number::New(isolate, idleTime_ms);
    args.GetReturnValue().Set(js_ret);
}

void init(Handle<Object> exports)
{
    NODE_SET_METHOD(exports, "getIdleTime_ms", GetIdleTime_ms);
}

// The module_name must match the filename of the final binary
// (excluding the .node suffix).
NODE_MODULE(osIdleTimer, init)
