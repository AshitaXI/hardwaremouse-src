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

#ifndef HARDWAREMOUSE_HPP_INCLUDED
#define HARDWAREMOUSE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "defines.hpp"

namespace hardwaremouse
{
    class plugin final : public IPlugin
    {
        IAshitaCore* core_;
        ILogManager* log_;
        uint32_t id_;

    public:
        plugin(void);
        ~plugin(void) override;

        auto GetName(void) const -> const char* override;
        auto GetAuthor(void) const -> const char* override;
        auto GetDescription(void) const -> const char* override;
        auto GetLink(void) const -> const char* override;
        auto GetVersion(void) const -> double override;
        auto GetInterfaceVersion(void) const -> double override;
        auto GetPriority(void) const -> int32_t override;
        auto GetFlags(void) const -> uint32_t override;

        auto Initialize(IAshitaCore* core, ILogManager* logger, uint32_t id) -> bool override;
        auto Release(void) -> void override;
    };

} // namespace hardwaremouse

#endif // HARDWAREMOUSE_HPP_INCLUDED