#include "pch.h"
#include "winrt/test_component_base.h"
#include "winrt/test_component_derived.nested.h"
#include <inspectable.h>
#include <weakreference.h>

using namespace winrt;
using namespace test_component_base;
using namespace test_component_derived::Nested;

TEST_CASE("hierarchy")
{
    // TODO: make sure this excercises all the wonky code paths in implements and wrap_as_result

    HierarchyA a;
    REQUIRE(a == weak_ref<HierarchyA>(a).get()
        .as<IUnknown>()
        .as<IInspectable>()
        .as<IWeakReferenceSource>()
        .as<IAgileObject>()
        .as<IMarshal>()
        .as<HierarchyA>());

    HierarchyB b;
    REQUIRE(b == weak_ref<HierarchyB>(b).get()
        .as<IUnknown>()
        .as<IInspectable>()
        .as<IWeakReferenceSource>()
        .as<IAgileObject>()
        .as<IMarshal>()
        .as<HierarchyA>()
        .as<HierarchyB>());

    HierarchyC c;
    REQUIRE(c == weak_ref<HierarchyC>(c).get()
        .as<IUnknown>()
        .as<IInspectable>()
        .as<IWeakReferenceSource>()
        .as<IAgileObject>()
        .as<IMarshal>()
        .as<HierarchyA>()
        .as<HierarchyB>()
        .as<HierarchyC>());

    HierarchyD d;
    REQUIRE(d == weak_ref<HierarchyD>(d).get()
        .as<IUnknown>()
        .as<IInspectable>()
        .as<IWeakReferenceSource>()
        .as<IAgileObject>()
        .as<IMarshal>()
        .as<HierarchyA>()
        .as<HierarchyB>()
        .as<HierarchyC>()
        .as<HierarchyD>());
}
