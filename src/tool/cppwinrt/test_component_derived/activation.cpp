#include "pch.h"
#include "winrt/base.h"
#include <Windows.h>

using namespace winrt;

bool starts_with(std::wstring_view value, std::wstring_view match) noexcept
{
    return 0 == value.compare(0, match.size(), match);
}

int32_t WINRT_CALL WINRT_RoGetActivationFactory(void* classId, guid const& iid, void** factory) noexcept
{
    *factory = nullptr;
    std::wstring_view name{ WINRT_WindowsGetStringRawBuffer(classId, nullptr) };
    HMODULE library{ nullptr };

    if (starts_with(name, L"test_component_base."))
    {
        library = LoadLibraryW(L"test_component_base.dll");
    }

    if (!library)
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    using DllGetActivationFactory = HRESULT __stdcall(void* classId, void** factory);
    auto call = reinterpret_cast<DllGetActivationFactory*>(GetProcAddress(library, "DllGetActivationFactory"));

    if (!call)
    {
        HRESULT const hr = HRESULT_FROM_WIN32(GetLastError());
        WINRT_VERIFY(FreeLibrary(library));
        return hr;
    }

    winrt::com_ptr<winrt::Windows::Foundation::IActivationFactory> activation_factory;
    HRESULT const hr = call(classId, activation_factory.put_void());

    if (FAILED(hr))
    {
        WINRT_VERIFY(FreeLibrary(library));
        return hr;
    }

    if (iid != winrt::guid_of<winrt::Windows::Foundation::IActivationFactory>())
    {
        return activation_factory->QueryInterface(iid, factory);
    }

    *factory = activation_factory.detach();
    return S_OK;
}
