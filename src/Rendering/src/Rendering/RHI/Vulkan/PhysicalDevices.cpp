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

#include "PhysicalDevices.h"
#include "Instance.h"
#include "Surface.h"

#include <set>

namespace TomTekEngine::Rendering 
{
	PhysicalDevices::PhysicalDevices() :
		m_PhysicalDevice(VK_NULL_HANDLE),
		m_AncestorSurface(nullptr)
	{}

	void PhysicalDevices::Initialize(Instance* ancestorInstance, Surface* ancestorSurface)
	{
		PickPhysicalDevice(ancestorInstance, ancestorSurface);
	}

	void PhysicalDevices::PickPhysicalDevice(Instance* ancestorInstance, Surface* ancestorSurface)
	{
		m_AncestorSurface = ancestorSurface;

		std::cout << "[VK_STATUS]: Picking best suited PhysicalDevice\n";

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(ancestorInstance->GetNative(), &deviceCount, nullptr);

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(ancestorInstance->GetNative(), &deviceCount, devices.data());

		for ( const VkPhysicalDevice& physicalDevice : devices )
		{
			QueueFamilyIndices indicies;
			if ( IsDeviceSuitable(&indicies, physicalDevice) )
			{
				m_PhysicalDevice = physicalDevice;

				break;
			}
		}

		// Ignore this, just logging to the output
		if ( m_PhysicalDevice )
			std::cout << "[VK_STATUS]: Found best suited PhysicalDevice!\n";
		else
			std::cout << "[VK_STATUS]: No Physical Device was found.\n";
	}

	bool PhysicalDevices::IsDeviceSuitable(QueueFamilyIndices*, VkPhysicalDevice physicalDevice)
	{
		QueueFamilyIndices indicies = FindQueueFamilies(physicalDevice);
		return
			indicies.GraphicsFamilyIndex.has_value() && 
			indicies.PresentFamilyIndex.has_value() &&
			CheckDeviceExtensionSupport(physicalDevice);
	}

	bool PhysicalDevices::CheckDeviceExtensionSupport(VkPhysicalDevice physicalDevice)
	{
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtenions(DeviceExtensionNames.begin(), DeviceExtensionNames.end());
		for ( const VkExtensionProperties& extension : availableExtensions )
		{
			requiredExtenions.erase(extension.extensionName);
		}

		return requiredExtenions.empty();
	}

	QueueFamilyIndices PhysicalDevices::FindQueueFamilies(VkPhysicalDevice physicalDevice)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

		QueueFamilyIndices indicies;
		
		for ( uint32_t i = 0; i < queueFamilyCount; i++ )
		{
			const VkQueueFamilyProperties& queueFamilyProperty = queueFamilyProperties[i];
			if ( queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT )
			{
				indicies.GraphicsFamilyIndex = i;
			}

			// Check if this devices supports presenting
			VkBool32 doesSupportPresent = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, m_AncestorSurface->GetNative(), &doesSupportPresent);

			if ( doesSupportPresent )
			{
				indicies.PresentFamilyIndex = i;
			}
		}

		return indicies;
	}
}

#endif