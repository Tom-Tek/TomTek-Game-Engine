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

#include "Instance.h"
#include <iostream>

namespace TomTekEngine::Rendering 
{
	void Instance::Initialize(const VkApplicationInfo& appInfo)
	{
		std::cout << "[VK_STATUS]: Attempting creation of VkInstance\n";

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.flags = 0;
		
		createInfo.ppEnabledExtensionNames = m_ExtensionNames.data();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_ExtensionNames.size());

#ifdef NDEBUG
		createInfo.ppEnabledLayerNames = nullptr;
		createInfo.enabledLayerCount = 0;
#else
		// Pass needed validation layer names cause we're in debug mode
		createInfo.ppEnabledLayerNames = m_ValidationLayer.GetValidationLayerNames().data();
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayer.GetValidationLayerNames().size());
#endif

		if ( vkCreateInstance(&createInfo, nullptr, &m_NativeInstance) != VK_SUCCESS )
		{
			throw std::runtime_error("vkCreateInstance failed to create m_NativeInstance");
		}

		std::cout << "[VK_STATUS]: vkInstance m_NativeInstance creation went ok\n";

#ifndef NDEBUG
		// Need to initialize validation layers after NativeInstance has been created
		// So initialize it here and pray that everything goes okay
		m_ValidationLayer.Initialize(this);
#endif
	}
}

#endif