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

#include <iostream>
#include <optional>
#include <vector>
#include "VulkanPlatform.h"

namespace TomTekEngine::Rendering 
{
	class Instance;
	class Surface;

	/// Stores all indicies of where each Queue Family lives
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> GraphicsFamilyIndex;
		std::optional<uint32_t> PresentFamilyIndex;
	};

	class PhysicalDevices final
	{

	public:
		PhysicalDevices();

	public:
		const std::vector<const char*> DeviceExtensionNames = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};

	public:
		/// Currently a wrapper method for PickPhysicalDevice. Doing this cause it'll make
		/// everything more consistant with the other code base.
		void Initialize(Instance* ancestorInstance, Surface* ancestorSurface);
		/// This method sort of acts like an initalizer. Instead of returning the device that is best suited
		/// for runtime. It will assign the best suited device to the member field "m_PhysicalDevice"
		/// Other classes will then be able to get that device later during runtime.
		void PickPhysicalDevice(Instance* ancestorInstance, Surface* ancestorSurface);
		
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice physicalDevice);

	public:
		VkPhysicalDevice GetNativePhysicalDevice() const { return m_PhysicalDevice; }

	private:
		bool IsDeviceSuitable(QueueFamilyIndices* indicies, VkPhysicalDevice physicalDevice);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice);

	private:
		VkPhysicalDevice m_PhysicalDevice;

		Surface* m_AncestorSurface;

	};
}

#endif