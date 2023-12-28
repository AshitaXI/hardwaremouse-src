####################################################################################################
# Ashita - Copyright (c) 2023 Ashita Development Team
# Contact: https://www.ashitaxi.com/
# Contact: https://discord.gg/Ashita
#
# This file is part of Ashita.
#
# Ashita is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Ashita is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Ashita.  If not, see <https://www.gnu.org/licenses/>.
####################################################################################################
#
# Locates and prepares Microsoft Detours for usage with CMAKE.
#
# This module creates the following defines:
#
#   Detours_FOUND
#   DETOURS_INCLUDE_DIRS
#   DETOURS_LIBRARY_DIRS
#   DETOURS_LIBRARY_LIBS
#
####################################################################################################

find_path(DETOURS_INCLUDE_DIRS
    NAMES
        "detours.h"
    PATHS
        "ext/detours/"
    )

find_library(DETOURS_LIBRARY
    NAMES
        "detours"
    PATHS
        "ext/detours/"
    )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Detours
    DEFAULT_MSG
        DETOURS_INCLUDE_DIRS
        DETOURS_LIBRARY
    )

mark_as_advanced(
    DETOURS_INCLUDE_DIRS
    DETOURS_LIBRARY
    )

####################################################################################################
#
# Helper Functions
#
# General helper functions that can be used with this module.
#
####################################################################################################

if (MSVC)

    # Attaches detours to the given target.
    function (detours_attach target)
        target_include_directories(${target}
            PRIVATE
                ${DETOURS_INCLUDE_DIRS}
            )
        target_link_directories(${target}
            PRIVATE
                ${DETOURS_INCLUDE_DIRS}
            )
        target_link_libraries(${target}
            PRIVATE
                ${DETOURS_LIBRARY}
            )
    endfunction()

endif()