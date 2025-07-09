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
#include "Instance.h"
#include "ValidationLayers.h"

namespace TomTekEngine::Rendering 
{
	Instance::~Instance()
	{
		vkDestroyInstance(m_NativeInstance, nullptr);
	}

	void Instance::Initialize(VkApplicationInfo applicationInfo)
	{
		const VkInstanceCreateInfo createInfo = {
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.pApplicationInfo = &applicationInfo,

#ifdef NDEBUG
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = nullptr,
#else
			.enabledLayerCount = (uint32_t) m_ValidationLayers.GetValidationLayers().size(),
			.ppEnabledLayerNames = m_ValidationLayers.GetValidationLayers().data(),
#endif
			.enabledExtensionCount = 0,
			.ppEnabledExtensionNames = nullptr
		};

		if ( vkCreateInstance(&createInfo, nullptr, &m_NativeInstance) != VK_SUCCESS )
		{
			throw std::runtime_error("TomTekEngine::Rendering vulkan vkInstance failed to create m_NativeInstance");
		}

		m_ValidationLayers.Initialize(this);

		std::cout << "Vulkan Instance created\n";
	}
}