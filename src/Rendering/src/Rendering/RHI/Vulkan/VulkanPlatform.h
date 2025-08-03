/**
 * Copyright (c) 2025 Liam Rousselle
 * Copyright (c) 2025 TomTek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * Script Author: Liam Rousselle
 */
#if defined (_WIN32) || defined (__linux__)

#include <string>

#ifndef VULKAN_PLATFORM_H
#define VULKAN_PLATFORM_H


#ifdef _WIN32
	#define VK_USE_PLATFORM_WIN32_KHR
#elif __linux__
	#define VK_USE_PLATFORM_XLIB_KHR
#endif
#include <vulkan/vulkan.h>

#ifndef NDEBUG
    #include <vulkan/vk_enum_string_helper.h>
#endif

#ifndef NDEBUG
	#define VK_PLAT_LOG_RESULT(result)                                                                             \
		std::cout << "[VK_PLAT_LOG_RESULT]: " << string_VkResult(result) << "\n"; 
#else
    #define VK_PLAT_LOG_RESULT(ptr) (void*) ptr
#endif

#endif
#endif