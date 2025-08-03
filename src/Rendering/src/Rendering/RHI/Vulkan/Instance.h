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

#if defined (_WIN32) || defined (__linux__)

#include "VulkanPlatform.h"

#include <vector>

#ifndef NDEBUG
	#include "ValidationLayer.h"
#endif

namespace TomTekEngine::Rendering 
{
	class Instance final
	{
	public:
		/// Post construction initialization for creation of Native Instance.
		/// Mandatory for this to be called after construction as otherwise m_NativeInstance
		/// will remain as VK_NULL_HANDLE. Which will cause bugs for other classes accessing the
		/// Native Instance.
		void Initialize(const VkApplicationInfo& appInfo);

	public:
		VkInstance GetNative() const { return m_NativeInstance; }
		
#ifndef NDEBUG
		ValidationLayer GetValidationLayer() const { return m_ValidationLayer; }
#endif

	private:
		const std::vector<const char*> m_ExtensionNames = {
			VK_KHR_SURFACE_EXTENSION_NAME,

#ifndef NDEBUG
			VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif

#ifdef _WIN32
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#elif __linux__
			
#endif
		};

		VkInstance m_NativeInstance = VK_NULL_HANDLE;

#ifndef NDEBUG
		ValidationLayer m_ValidationLayer;
#endif
	};
}

#endif