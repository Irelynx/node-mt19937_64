
#include <node.h>
#include <v8.h>

#include <random>
#include <chrono>

class MT19937_64 {
private:
    std::mt19937_64 _ref;
    uint64_t _seed;
public:
    MT19937_64() {
        _seed = std::mt19937_64::default_seed;
        _ref = std::mt19937_64();
    }
    MT19937_64(uint64_t s) {
        _seed = s;
        _ref = std::mt19937_64(_seed);
    }
    ~MT19937_64() {}
    static void newFromSeed(const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        uint64_t seed = std::mt19937_64::default_seed; // default_seed value for mersenne_twister_engine
    
        if (args.Length() > 1) {
            isolate->ThrowException(v8::Exception::TypeError(
                v8::String::NewFromUtf8(isolate, "Wrong number of arguments (0 or 1 expected - seed_orUseTimeAsSeed).").ToLocalChecked()
            ));
            args.GetReturnValue().SetUndefined();
            return;
        } else if (args.Length() == 1) {
            if (!args[0]->IsNumber() && !args[0]->IsBigInt() && !args[0]->IsBoolean()) {
                isolate->ThrowException(v8::Exception::TypeError(
                    v8::String::NewFromUtf8(isolate, "Wrong argument 0 type. Number, BigInt or Boolean expected").ToLocalChecked()
                ));
                args.GetReturnValue().SetUndefined();
                return;
            }
            
            if (args[0]->IsNumber()) {
                seed = args[0].As<v8::Uint32>()->Value();
            } else if (args[0]->IsBigInt()) {
                seed = args[0].As<v8::BigInt>()->Uint64Value();
            } else if (args[0]->IsBoolean() && args[0].As<v8::Boolean>()->Value()) {
                seed = std::chrono::system_clock::now().time_since_epoch().count();
            }
        }
        
        MT19937_64* instance = new MT19937_64(seed);
        
        v8::Local<v8::Object> jsObject = wrap(instance, isolate);
        jsObject->Set(
            context,
            v8::String::NewFromUtf8(isolate, "next").ToLocalChecked(),
            v8::FunctionTemplate::New(isolate,
                MT19937_64::next_wrap
            )->GetFunction(context).ToLocalChecked()
        );
        jsObject->Set(
            context,
            v8::String::NewFromUtf8(isolate, "seed").ToLocalChecked(),
            v8::BigInt::NewFromUnsigned(isolate, seed)
        );
        args.GetReturnValue().Set(jsObject);
    }
    
    uint64_t next() { return _ref(); }
    uint64_t getSeed() { return _seed; }
    void setSeed(uint64_t s) {
        _seed = s;
        _ref = std::mt19937_64(_seed);
    }
    
    static void next_wrap(const v8::FunctionCallbackInfo<v8::Value>& args) {
        v8::Isolate* isolate = args.GetIsolate();
        
        MT19937_64* instance = unwrap(args.This());
        uint64_t result = instance->next();
        args.GetReturnValue().Set(
            v8::BigInt::NewFromUnsigned(isolate, result)
        );
    }
    
    static v8::Local<v8::Object> wrap(MT19937_64* instance, v8::Isolate* isolate) {
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        
        v8::Local<v8::ObjectTemplate> raw_template = v8::ObjectTemplate::New(isolate);
        raw_template->SetInternalFieldCount(1);
        // v8::Persistent<v8::ObjectTemplate> class_template = v8::Persistent<v8::ObjectTemplate>::New(raw_template);
        v8::Local<v8::Object> result = raw_template->NewInstance(context).ToLocalChecked();
        v8::Local<v8::External> instance_pointer = v8::External::New(isolate, instance);
        // hidden field for C++ usage ONLY
        result->SetInternalField(0, instance_pointer);
        return result;
    }
    
    static MT19937_64* unwrap(v8::Local<v8::Object> jsObject) {
        v8::Local<v8::External> instance_pointer = v8::Local<v8::External>::Cast(
            jsObject->GetInternalField(0)
        );
        return static_cast<MT19937_64*>(instance_pointer->Value());
    }
};

void init(v8::Local<v8::Object> exports, v8::Local<v8::Value> module) {
    v8::Isolate* isolate = exports->GetIsolate();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    
    NODE_SET_METHOD(exports, "newFromSeed", ::MT19937_64::newFromSeed);
}

NODE_MODULE(mt19937_64, init)