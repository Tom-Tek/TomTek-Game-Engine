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

#endif

namespace TomTekEngine::Rendering 
{
	Surface::Surface() :
		m_AncestorInstance(nullptr),
		m_NativeSurface(VK_NULL_HANDLE)
	{}

	Surface::~Surface()
	{
		vkDestroySurfaceKHR(m_AncestorInstance->GetNative(), m_NativeSurface, nullptr);
	}

	void Surface::Initialize(Instance* ancestorInstance, EngineWindow* windowTarget)
	{
		m_AncestorInstance = ancestorInstance;

		std::cout << "[VK_STATUS]: Attempt creation of Surface, using API:\n";

#ifdef _WIN32

		std::cout << "\tSurface API: Win32\n";

		Win32EngineWindow* win32TargetWindow = static_cast<Win32EngineWindow*>(windowTarget);
		if ( !win32TargetWindow )
		{
			throw std::runtime_error("StaticCast failed on Win32TargetWindow");
		}

		// Win32 Surface Implementation
		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hinstance = win32TargetWindow->GetHandleToInstance();
		createInfo.hwnd = win32TargetWindow->GetHandleToWindow();

		if ( vkCreateWin32SurfaceKHR(ancestorInstance->GetNative(), &createInfo, nullptr, &m_NativeSurface) != VK_SUCCESS )
		{
			throw std::runtime_error("vkCreateWin32SurfaceKHR failed to create m_NativeSurface");
		}

		std::cout << "[VK_STATUS]: Creation of vkSurfaceKHR ok\n";

#elif __linux__

		// Linux Surface Implementation

#endif

	}
}

#endif