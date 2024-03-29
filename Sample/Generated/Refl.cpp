/*
 * This file is generated by ReflCompiler
 */
// clang-format off
#include "Core/Object.hpp"
#include "Core/Reflection/Type.hpp"
#include "Core/Reflection/TypeRegistry.hpp"
#include "Core/Reflection/Registration.hpp"

    #include "TestComponent.hpp"

#include "Refl.hpp"

using namespace EngineS;

#define DROP_FIRST(X, ...) __VA_ARGS__

void EngineS::Registration::RegisterUserObjects() {
    Registration::Class<TestComponent>("TestComponent")
    .Bases
    <DROP_FIRST(_, EngineS::Component)>()
        .Method("GetType", static_cast
        <MethodType<TestComponent, false, true, const EngineS::Type *>>(&TestComponent::GetType), {  })
        .Method("GetPointer", static_cast
        <MethodType<TestComponent, false, false, void *>>(&TestComponent::GetPointer), {  })
        .Method("Update", static_cast
        <MethodType<TestComponent, false, false, void, float>>(&TestComponent::Update), { {"deltaTime"}, })
    ;
}
