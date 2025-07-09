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
#pragma once

#if defined (_WIN32) || (__linux__)

#include <iostream>
#include <vulkan/vulkan.h>

#include "ValidationLayers.h"

namespace TomTekEngine::Rendering 
{
	class Instance final
	{
	public:
		Instance();
		~Instance();

	public:
		/// Initializes the Vulkan instance by creating the VkInstance handle.
		/// This sets up the Vulkan API connection and must be called before using any Vulkan functionality.
		void Initialize(VkApplicationInfo appInfo);

	public:
		VkInstance GetNative() const { return m_NativeInstance; }
		operator VkInstance() const { return m_NativeInstance; }

	private:
		VkInstance m_NativeInstance;

		const std::vector<const char*> m_ExtensionsUsed = {

#ifndef NDEBUG
			// Debug only extensions here
			"VK_EXT_debug_utils",
#endif

			"VK_KHR_surface",
			//"VK_KHR_swapchain",
		};

#ifndef NDEBUG
		ValidationLayers m_ValidationLayers;
#endif

	};
}

#endif