/**
 * Ashita - Copyright (c) 2023 Ashita Development Team
 * Contact: https://www.ashitaxi.com/
 * Contact: https://discord.gg/Ashita
 *
 * This file is part of Ashita.
 *
 * Ashita is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ashita is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ashita.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "hardwaremouse.hpp"
#include <detours.h>

extern "C"
{
    auto Real_SetCursor = static_cast<decltype(::SetCursor)*>(::SetCursor);
}

/**
 * user32!SetCursor detour callback.
 *
 * @param {HCURSOR} hCursor - A handle to the cursor.
 * @return {HCURSOR} Handle to the previous cursor.
 */
HCURSOR __stdcall Mine_SetCursor(const HCURSOR hCursor)
{
    if (const auto caller = Ashita::Memory::GetOwningModule(reinterpret_cast<uintptr_t>(_ReturnAddress())); hCursor == nullptr && caller == ::GetModuleHandleA("d3d8.dll"))
        return nullptr;

    return Real_SetCursor(hCursor);
}

namespace hardwaremouse
{
    plugin::plugin(void)
        : core_{nullptr}
        , log_{nullptr}
        , id_{0}
    {}
    plugin::~plugin(void)
    {}

    auto plugin::GetName(void) const -> const char*
    {
        return "hardwaremouse";
    }

    auto plugin::GetAuthor(void) const -> const char*
    {
        return "atom0s";
    }

    auto plugin::GetDescription(void) const -> const char*
    {
        return "Force-enables the game mouse while using certain graphics proxies.";
    }

    auto plugin::GetLink(void) const -> const char*
    {
        return "https://www.ashitaxi.com/";
    }

    auto plugin::GetVersion(void) const -> double
    {
        return 4.1f;
    }

    auto plugin::GetInterfaceVersion(void) const -> double
    {
        return ASHITA_INTERFACE_VERSION;
    }

    auto plugin::GetPriority(void) const -> int32_t
    {
        return 0;
    }

    auto plugin::GetFlags(void) const -> uint32_t
    {
        return static_cast<uint32_t>(Ashita::PluginFlags::None);
    }

    auto plugin::Initialize(IAshitaCore* core, ILogManager* logger, const uint32_t id) -> bool
    {
        this->core_ = core;
        this->log_  = logger;
        this->id_   = id;

        ::DetourTransactionBegin();
        ::DetourUpdateThread(::GetCurrentThread());
        ::DetourAttach(&reinterpret_cast<PVOID&>(Real_SetCursor), Mine_SetCursor);
        ::DetourTransactionCommit();

        return true;
    }

    auto plugin::Release(void) -> void
    {
        ::DetourTransactionBegin();
        ::DetourUpdateThread(::GetCurrentThread());
        ::DetourDetach(&reinterpret_cast<PVOID&>(Real_SetCursor), Mine_SetCursor);
        ::DetourTransactionCommit();
    }

} // namespace hardwaremouse

__declspec(dllexport) auto __stdcall expCreatePlugin(const char* args) -> IPlugin*
{
    UNREFERENCED_PARAMETER(args);

    return new hardwaremouse::plugin();
}

__declspec(dllexport) auto __stdcall expGetInterfaceVersion(void) -> double
{
    return ASHITA_INTERFACE_VERSION;
}