/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: set ts=8 sts=2 et sw=2 tw=80:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "builtin/WeakMapObject-inl.h"

#include "builtin/WeakSetObject.h"
#include "gc/GC.h"
#include "gc/GCContext.h"
#include "js/friend/ErrorMessages.h"  // JSMSG_*
#include "js/PropertySpec.h"
#include "js/WeakMap.h"
#include "vm/Compartment.h"
#include "vm/Interpreter.h"
#include "vm/JSContext.h"
#include "vm/SelfHosting.h"

#include "builtin/MapObject-inl.h"
#include "gc/GCContext-inl.h"
#include "gc/WeakMap-inl.h"
#include "vm/NativeObject-inl.h"

using namespace js;

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::is(HandleValue v) {
  return v.isObject() && v.toObject().is<WeakMapObject>();
}

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::has_impl(
    JSContext* cx, const CallArgs& args) {
  MOZ_ASSERT(is(args.thisv()));

  if (!CanBeHeldWeakly(cx, args.get(0))) {
    args.rval().setBoolean(false);
    return true;
  }

  if (ValueValueWeakMap* map =
          args.thisv().toObject().as<WeakMapObject>().getMap()) {
    Value key = args[0];
    if (map->has(key)) {
      args.rval().setBoolean(true);
      return true;
    }
  }

  args.rval().setBoolean(false);
  return true;
}

/* static */
bool WeakMapObject::has(JSContext* cx, unsigned argc, Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  return CallNonGenericMethod<WeakMapObject::is, WeakMapObject::has_impl>(cx,
                                                                          args);
}

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::get_impl(
    JSContext* cx, const CallArgs& args) {
  MOZ_ASSERT(WeakMapObject::is(args.thisv()));

  if (!CanBeHeldWeakly(cx, args.get(0))) {
    args.rval().setUndefined();
    return true;
  }

  if (ValueValueWeakMap* map =
          args.thisv().toObject().as<WeakMapObject>().getMap()) {
    Value key = args[0];
    if (ValueValueWeakMap::Ptr ptr = map->lookup(key)) {
      args.rval().set(ptr->value());
      return true;
    }
  }

  args.rval().setUndefined();
  return true;
}

/* static */
bool WeakMapObject::get(JSContext* cx, unsigned argc, Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  return CallNonGenericMethod<WeakMapObject::is, WeakMapObject::get_impl>(cx,
                                                                          args);
}

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::delete_impl(
    JSContext* cx, const CallArgs& args) {
  MOZ_ASSERT(WeakMapObject::is(args.thisv()));

  if (!CanBeHeldWeakly(cx, args.get(0))) {
    args.rval().setBoolean(false);
    return true;
  }

  if (ValueValueWeakMap* map =
          args.thisv().toObject().as<WeakMapObject>().getMap()) {
    Value key = args[0];
    // The lookup here is only used for the removal, so we can skip the read
    // barrier. This is not very important for performance, but makes it easier
    // to test nonbarriered removal from internal weakmaps (eg Debugger maps.)
    if (ValueValueWeakMap::Ptr ptr = map->lookupUnbarriered(key)) {
      map->remove(ptr);
      args.rval().setBoolean(true);
      return true;
    }
  }

  args.rval().setBoolean(false);
  return true;
}

/* static */
bool WeakMapObject::delete_(JSContext* cx, unsigned argc, Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  return CallNonGenericMethod<WeakMapObject::is, WeakMapObject::delete_impl>(
      cx, args);
}

static bool SetWeakMapEntryImpl(JSContext* cx, Handle<WeakMapObject*> mapObj,
                                Handle<Value> keyVal, Handle<Value> value) {
  if (MOZ_UNLIKELY(!CanBeHeldWeakly(cx, keyVal))) {
    unsigned errorNum = GetErrorNumber(true);
    ReportValueError(cx, errorNum, JSDVG_IGNORE_STACK, keyVal, nullptr);
    return false;
  }

  return WeakCollectionPutEntryInternal(cx, mapObj, keyVal, value);
}

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::set_impl(
    JSContext* cx, const CallArgs& args) {
  MOZ_ASSERT(WeakMapObject::is(args.thisv()));

  Rooted<WeakMapObject*> map(cx, &args.thisv().toObject().as<WeakMapObject>());
  if (!SetWeakMapEntryImpl(cx, map, args.get(0), args.get(1))) {
    return false;
  }

  args.rval().set(args.thisv());
  return true;
}

/* static */
bool WeakMapObject::set(JSContext* cx, unsigned argc, Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  return CallNonGenericMethod<WeakMapObject::is, WeakMapObject::set_impl>(cx,
                                                                          args);
}

static bool getOrAddWeakMapEntryImpl(JSContext* cx,
                                     Handle<WeakMapObject*> mapObj,
                                     Handle<Value> keyVal, Handle<Value> value,
                                     MutableHandleValue rval) {
  if (MOZ_UNLIKELY(!CanBeHeldWeakly(cx, keyVal))) {
    unsigned errorNum = GetErrorNumber(true);
    ReportValueError(cx, errorNum, JSDVG_IGNORE_STACK, keyVal, nullptr);
    return false;
  }

  return WeakCollectionGetOrAddEntryInternal(cx, mapObj, keyVal, value, rval);
}

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::getOrInsert_impl(
    JSContext* cx, const CallArgs& args) {
  MOZ_ASSERT(WeakMapObject::is(args.thisv()));

  Rooted<WeakMapObject*> map(cx, &args.thisv().toObject().as<WeakMapObject>());
  return getOrAddWeakMapEntryImpl(cx, map, args.get(0), args.get(1),
                                  args.rval());
}

/* static */
bool WeakMapObject::getOrInsert(JSContext* cx, unsigned argc, Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  return CallNonGenericMethod<WeakMapObject::is,
                              WeakMapObject::getOrInsert_impl>(cx, args);
}

static bool getOrAddWeakMapEntryComputed(JSContext* cx,
                                         Handle<WeakMapObject*> mapObj,
                                         Handle<Value> key,
                                         Handle<Value> callbackfn,
                                         MutableHandleValue rval) {
  if (MOZ_UNLIKELY(!callbackfn.isUndefined() && !IsCallable(callbackfn))) {
    ReportValueError(cx, JSMSG_NOT_FUNCTION, JSDVG_IGNORE_STACK, callbackfn,
                     nullptr);
    return false;
  }

  if (MOZ_UNLIKELY(!CanBeHeldWeakly(cx, key))) {
    unsigned errorNum = GetErrorNumber(true);
    ReportValueError(cx, errorNum, JSDVG_IGNORE_STACK, key, nullptr);
    return false;
  }

  ValueValueWeakMap* map = mapObj->getMap();
  if (!map) {
    auto newMap = cx->make_unique<ValueValueWeakMap>(cx, mapObj.get());
    if (!newMap) {
      return false;
    }
    map = newMap.release();
    InitReservedSlot(mapObj, WeakCollectionObject::DataSlot, map,
                     MemoryUse::WeakMapObject);
  }

  if (ValueValueWeakMap::Ptr p = map->lookup(key)) {
    rval.set(p->value());

  } else {
    if (key.isObject()) {
      RootedObject keyObj(cx, &key.toObject());

      // Preserve wrapped native keys to prevent wrapper optimization.
      if (!TryPreserveReflector(cx, keyObj)) {
        return false;
      }

      RootedObject delegate(cx, UncheckedUnwrapWithoutExpose(keyObj));
      if (delegate && !TryPreserveReflector(cx, delegate)) {
        return false;
      }
    }
    MOZ_ASSERT_IF(key.isObject(),
                  key.toObject().compartment() == obj->compartment());
    MOZ_ASSERT_IF(
        value.isGCThing(),
        gc::ToMarkable(value)->zoneFromAnyThread() == obj->zone() ||
            gc::ToMarkable(value)->zoneFromAnyThread()->isAtomsZone());
    MOZ_ASSERT_IF(value.isObject(),
                  value.toObject().compartment() == obj->compartment());

    RootedValue value(cx);
    if (!js::Call(cx, callbackfn, JS::UndefinedHandleValue, key, &value)) {
      return false;
    }

    if (!map->put(key, value)) {
      JS_ReportOutOfMemory(cx);
      return false;
    }
    rval.set(value);
  }

  return true;
}

/* static */ MOZ_ALWAYS_INLINE bool WeakMapObject::getOrInsertComputed_impl(
    JSContext* cx, const CallArgs& args) {
  MOZ_ASSERT(WeakMapObject::is(args.thisv()));

  Rooted<WeakMapObject*> map(cx, &args.thisv().toObject().as<WeakMapObject>());
  return getOrAddWeakMapEntryComputed(cx, map, args.get(0), args.get(1),
                                      args.rval());
}

bool WeakMapObject::getOrInsertComputed(JSContext* cx, unsigned argc,
                                        Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);
  return CallNonGenericMethod<WeakMapObject::is,
                              WeakMapObject::getOrInsertComputed_impl>(cx,
                                                                       args);
}

size_t WeakCollectionObject::sizeOfExcludingThis(
    mozilla::MallocSizeOf aMallocSizeOf) {
  ValueValueWeakMap* map = getMap();
  return map ? map->sizeOfIncludingThis(aMallocSizeOf) : 0;
}

bool WeakCollectionObject::nondeterministicGetKeys(
    JSContext* cx, Handle<WeakCollectionObject*> obj, MutableHandleObject ret) {
  RootedObject arr(cx, NewDenseEmptyArray(cx));
  if (!arr) {
    return false;
  }
  if (ValueValueWeakMap* map = obj->getMap()) {
    // Prevent GC from mutating the weakmap while iterating.
    gc::AutoSuppressGC suppress(cx);
    for (ValueValueWeakMap::Base::Range r = map->all(); !r.empty();
         r.popFront()) {
      const auto& key = r.front().key();
      MOZ_ASSERT(key.isObject() || key.isSymbol());
      JS::ExposeValueToActiveJS(key);
      RootedValue keyVal(cx, key);
      if (!cx->compartment()->wrap(cx, &keyVal)) {
        return false;
      }
      if (!NewbornArrayPush(cx, arr, keyVal)) {
        return false;
      }
    }
  }
  ret.set(arr);
  return true;
}

JS_PUBLIC_API bool JS_NondeterministicGetWeakMapKeys(JSContext* cx,
                                                     HandleObject objArg,
                                                     MutableHandleObject ret) {
  RootedObject obj(cx, UncheckedUnwrap(objArg));
  if (!obj || !obj->is<WeakMapObject>()) {
    ret.set(nullptr);
    return true;
  }
  return WeakCollectionObject::nondeterministicGetKeys(
      cx, obj.as<WeakCollectionObject>(), ret);
}

static void WeakCollection_trace(JSTracer* trc, JSObject* obj) {
  if (ValueValueWeakMap* map = obj->as<WeakCollectionObject>().getMap()) {
    map->trace(trc);
  }
}

static void WeakCollection_finalize(JS::GCContext* gcx, JSObject* obj) {
  if (ValueValueWeakMap* map = obj->as<WeakCollectionObject>().getMap()) {
    gcx->delete_(obj, map, MemoryUse::WeakMapObject);
  }
}

JS_PUBLIC_API JSObject* JS::NewWeakMapObject(JSContext* cx) {
  return NewBuiltinClassInstance<WeakMapObject>(cx);
}

JS_PUBLIC_API bool JS::IsWeakMapObject(JSObject* obj) {
  return obj->is<WeakMapObject>();
}

JS_PUBLIC_API bool JS::GetWeakMapEntry(JSContext* cx, HandleObject mapObj,
                                       HandleValue key,
                                       MutableHandleValue rval) {
  CHECK_THREAD(cx);
  cx->check(key);
  rval.setUndefined();

  if (!CanBeHeldWeakly(cx, key)) {
    return true;
  }

  ValueValueWeakMap* map = mapObj->as<WeakMapObject>().getMap();
  if (!map) {
    return true;
  }

  if (ValueValueWeakMap::Ptr ptr = map->lookup(key)) {
    // Read barrier to prevent an incorrectly gray value from escaping the
    // weak map. See the comment before UnmarkGrayChildren in gc/Marking.cpp
    ExposeValueToActiveJS(ptr->value().get());
    rval.set(ptr->value());
  }
  return true;
}

JS_PUBLIC_API bool JS::SetWeakMapEntry(JSContext* cx, HandleObject mapObj,
                                       HandleValue key, HandleValue val) {
  CHECK_THREAD(cx);
  cx->check(key, val);
  return SetWeakMapEntryImpl(cx, mapObj.as<WeakMapObject>(), key, val);
}

/* static */
bool WeakMapObject::construct(JSContext* cx, unsigned argc, Value* vp) {
  CallArgs args = CallArgsFromVp(argc, vp);

  // ES6 draft rev 31 (15 Jan 2015) 23.3.1.1 step 1.
  if (!ThrowIfNotConstructing(cx, args, "WeakMap")) {
    return false;
  }

  RootedObject proto(cx);
  if (!GetPrototypeFromBuiltinConstructor(cx, args, JSProto_WeakMap, &proto)) {
    return false;
  }

  Rooted<WeakMapObject*> obj(cx,
                             NewObjectWithClassProto<WeakMapObject>(cx, proto));
  if (!obj) {
    return false;
  }

  // Steps 5-6, 11.
  if (!args.get(0).isNullOrUndefined()) {
    Handle<Value> iterable = args[0];
    bool optimized = false;
    if (!IsOptimizableInitForMapOrSet<JSProto_WeakMap>(
            cx, WeakMapObject::set, obj, iterable, &optimized)) {
      return false;
    }

    if (optimized) {
      RootedValue keyVal(cx);
      RootedValue value(cx);
      Rooted<ArrayObject*> array(cx, &iterable.toObject().as<ArrayObject>());
      uint32_t len = array->getDenseInitializedLength();
      for (uint32_t index = 0; index < len; index++) {
        Value element = array->getDenseElement(index);
        MOZ_ASSERT(IsPackedArray(&element.toObject()));

        auto* elementArray = &element.toObject().as<ArrayObject>();
        keyVal.set(elementArray->getDenseElement(0));
        value.set(elementArray->getDenseElement(1));
        MOZ_ASSERT(!keyVal.isMagic(JS_ELEMENTS_HOLE));
        MOZ_ASSERT(!value.isMagic(JS_ELEMENTS_HOLE));

        if (!SetWeakMapEntryImpl(cx, obj, keyVal, value)) {
          return false;
        }
      }
    } else {
      FixedInvokeArgs<1> args2(cx);
      args2[0].set(iterable);

      RootedValue thisv(cx, ObjectValue(*obj));
      if (!CallSelfHostedFunction(cx, cx->names().WeakMapConstructorInit, thisv,
                                  args2, args2.rval())) {
        return false;
      }
    }
  }

  args.rval().setObject(*obj);
  return true;
}

const JSClassOps WeakCollectionObject::classOps_ = {
    nullptr,                  // addProperty
    nullptr,                  // delProperty
    nullptr,                  // enumerate
    nullptr,                  // newEnumerate
    nullptr,                  // resolve
    nullptr,                  // mayResolve
    WeakCollection_finalize,  // finalize
    nullptr,                  // call
    nullptr,                  // construct
    WeakCollection_trace,     // trace
};

const ClassSpec WeakMapObject::classSpec_ = {
    GenericCreateConstructor<WeakMapObject::construct, 0,
                             gc::AllocKind::FUNCTION>,
    GenericCreatePrototype<WeakMapObject>,
    nullptr,
    nullptr,
    WeakMapObject::methods,
    WeakMapObject::properties,
};

const JSClass WeakMapObject::class_ = {
    "WeakMap",
    JSCLASS_HAS_RESERVED_SLOTS(SlotCount) |
        JSCLASS_HAS_CACHED_PROTO(JSProto_WeakMap) | JSCLASS_BACKGROUND_FINALIZE,
    &WeakCollectionObject::classOps_,
    &WeakMapObject::classSpec_,
};

const JSClass WeakMapObject::protoClass_ = {
    "WeakMap.prototype",
    JSCLASS_HAS_CACHED_PROTO(JSProto_WeakMap),
    JS_NULL_CLASS_OPS,
    &WeakMapObject::classSpec_,
};

const JSPropertySpec WeakMapObject::properties[] = {
    JS_STRING_SYM_PS(toStringTag, "WeakMap", JSPROP_READONLY),
    JS_PS_END,
};

const JSFunctionSpec WeakMapObject::methods[] = {
    JS_FN("has", has, 1, 0),
    JS_FN("get", get, 1, 0),
    JS_FN("delete", delete_, 1, 0),
    JS_FN("set", set, 2, 0),
    JS_FN("getOrInsert", getOrInsert, 2, 0),
    JS_FN("getOrInsertComputed", getOrInsertComputed, 2, 0),
    JS_FS_END,
};
