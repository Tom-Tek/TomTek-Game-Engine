--[=[

    Copyright (c) 2025 Liam Rousselle
    Copyright (c) 2025 TomTek

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

]=]--

workspace "TomTek-Game-Engine"
    architecture "x64"
    startproject "Editor"

    configurations { "Debug", "Release" }

group "Engine"
project "Editor"
    location "src/Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.h",
    }

    filter { "configurations:Debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"