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

#include "Surface.h"
#include "Instance.h"

#ifdef _WIN32
	#include "Window/Win32EngineWindow.h"
#elif __linux__
	// Include the linux window class when I create it
#endif

namespace TomTekEngine::Rendering 
{
	Surface::Surface() :
		m_NativeSurface(VK_NULL_HANDLE),
		m_OwnerInstance(nullptr)
	{}

	Surface::~Surface()
	{
		if ( m_OwnerInstance )
		{
			vkDestroySurfaceKHR(m_OwnerInstance->GetNative(), m_NativeSurface, nullptr);
		}
	}

	void Surface::Initialize(Instance ownerInstance, EngineWindow* windowTarget)
	{
		m_OwnerInstance = &ownerInstance;

#ifdef _WIN32

		// Windows surface implementation
		VkWin32SurfaceCreateInfoKHR createInfo = {
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.hinstance = ((Win32EngineWindow*) windowTarget)->GetHandleToInstance(),
			.hwnd = ((Win32EngineWindow*) windowTarget)->GetHandleToWindow()
		};

		if ( vkCreateWin32SurfaceKHR(ownerInstance.GetNative(), &createInfo, nullptr, &m_NativeSurface) != VK_SUCCESS )
		{
			throw std::runtime_error("TomTek Vulkan vkCreateWin32SurfaceKHR failed to create m_NativeSurface");
		}

		std::cout << "Vulkan Win32 SurfaceKHR created\n";

#elif __linux__

#endif

	}
}

#endif