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

#include <iostream>
#include <set>

#include "LogicalDevice.h"
#include "Instance.h"
#include "PhysicalDevices.h"

#ifndef NDEBUG
	#include "ValidationLayer.h"
#endif

namespace TomTekEngine::Rendering 
{
	LogicalDevice::LogicalDevice() :
		m_NativeDevice(VK_NULL_HANDLE),
		m_GraphicsQueue(VK_NULL_HANDLE),
		m_PresentQueue(VK_NULL_HANDLE)
	{}

	LogicalDevice::~LogicalDevice()
	{
		vkDestroyDevice(m_NativeDevice, nullptr);
	}

	void LogicalDevice::Initialize(Instance* ancestorInstance, PhysicalDevices* ancestorPhysicalDevices)
	{
		std::cout << "[VK_STATUS]: Attempting creation of VkDevice\n";

		const QueueFamilyIndices& indicies =
			ancestorPhysicalDevices->FindQueueFamilies(ancestorPhysicalDevices->GetNativePhysicalDevice());

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {
			indicies.GraphicsFamilyIndex.value(), 
			indicies.PresentFamilyIndex.value()
		};

		float queuePriority = 1.0f;
		for ( uint32_t queueFamily : uniqueQueueFamilies )
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}
		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = static_cast<uint32_t>( ancestorPhysicalDevices->DeviceExtensionNames.size() );
		createInfo.ppEnabledExtensionNames = ancestorPhysicalDevices->DeviceExtensionNames.data();

#ifndef NDEBUG
		const ValidationLayer ancestorValidationLayer = ancestorInstance->GetValidationLayer();
		createInfo.enabledLayerCount = static_cast<uint32_t>(ancestorValidationLayer.GetValidationLayerNames().size());
		createInfo.ppEnabledLayerNames = ancestorValidationLayer.GetValidationLayerNames().data();
#else
		createInfo.enabledLayerCount = 0;
		createInfo.ppEnabledLayerNames = nullptr;
#endif

		if ( vkCreateDevice(ancestorPhysicalDevices->GetNativePhysicalDevice(), &createInfo, nullptr, &m_NativeDevice) != VK_SUCCESS )
		{
			throw std::runtime_error("vkCreateDevice failed to create Native Device");
		}

		std::cout << "[VK_STATUS]: Created VkDevice ok\n";

		// Get the Graphics Queue
		std::cout << "[VK_STATUS]: Getting Graphics Queue\n";
		vkGetDeviceQueue(m_NativeDevice, indicies.GraphicsFamilyIndex.value(), 0, &m_GraphicsQueue);

		// Get the Present Queue
		std::cout << "[VK_STATUS]: Getting Present Queue\n";
		vkGetDeviceQueue(m_NativeDevice, indicies.PresentFamilyIndex.value(), 0, &m_PresentQueue);
	}
}

#endif
