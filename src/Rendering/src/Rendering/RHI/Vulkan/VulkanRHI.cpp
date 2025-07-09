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

#include <vulkan/vulkan.h>

#include "VulkanRHI.h"
#include "Window/EngineWindow.h"

namespace TomTekEngine::Rendering 
{
	VulkanRHI::VulkanRHI(EngineWindow* windowTarget) :
		EngineRenderer(windowTarget),
		m_ApplicationInfo(
			{
				.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
				.pNext = nullptr,
				.pApplicationName = "TomTek-Vulkan",
				.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
				.pEngineName = "TomTek-Vulkan-Engine",
				.engineVersion = VK_MAKE_VERSION( 1, 0, 0 ),
				.apiVersion = VK_API_VERSION_1_2,
			}
		)
	{
		m_Instance.Initialize(m_ApplicationInfo);
	}

	VulkanRHI::~VulkanRHI()
	{}



}

#endif