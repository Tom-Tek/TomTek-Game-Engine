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
#ifndef NDEBUG
#if defined (_WIN32) || defined (__linux__)

#include "ValidationLayer.h"
#include "Instance.h"

#include <iostream>

namespace TomTekEngine::Rendering 
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationLayerDebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
			void* userData
		) 
	{
		std::cout << "[VK_VALIDATION_DEBUG_CALLBACK]: " << messageSeverity << ", " << messageType << "\n";
		std::cout << "\t" << callbackData->pMessage << "\n";

		return VK_FALSE; // Never abort for now
	}
	
	ValidationLayer::~ValidationLayer()
	{
		if ( m_AncestorInstance )
		{
			// Destroy the vkDebugUtilsMessenger apart of this class
			// Find the callback which will destroy DebugUtilsMessenger then call it
			PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT =
				(PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_AncestorInstance->GetNative(), "vkDestroyDebugUtilsMessengerEXT");
			if ( vkDestroyDebugUtilsMessengerEXT )
			{
				vkDestroyDebugUtilsMessengerEXT(m_AncestorInstance->GetNative(), m_DebugUtilsMessenger, nullptr);
			}
		}
	}

	void ValidationLayer::Initialize(Instance* ancestorInstance)
	{
		std::cout << "[VK_STATUS]: Attempt creation of ValidationLayer\n";

		m_AncestorInstance = ancestorInstance;

		VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.pNext = nullptr;

		// All error severities which we are interested in output to the console
		createInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
		createInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

		createInfo.pfnUserCallback = &ValidationLayerDebugCallback;
		createInfo.pUserData = nullptr;
		
		// Get the address of where vkCreateDebugUtilsMessenger callback is so that
		// we can call that function to create m_DebugUtilsMessenger
		PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessenger =
			(PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(ancestorInstance->GetNative(), "vkCreateDebugUtilsMessengerEXT");
		if ( vkCreateDebugUtilsMessenger )
		{
			std::cout << "[VK_STATUS]: vkDebugUtilsMessenger creation went ok\n";
			vkCreateDebugUtilsMessenger(ancestorInstance->GetNative(), &createInfo, nullptr, &m_DebugUtilsMessenger);
		}
		else
		{
			std::cout << "[VK_STATUS]: ERROR // Failed to get address of vkCreateDebugUtilsMessengerEXT\n";
		}
	}

	void ValidationLayer::DebugLogAllAvailableLayers()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		std::cout << "Available validation layers:\n";
		for ( const auto& layer : availableLayers )
			std::cout << "\t" << layer.layerName << " - " << layer.description << "\n";
	}
}

#endif
#endif