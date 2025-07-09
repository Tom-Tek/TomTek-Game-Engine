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
#if defined (_WIN32) || (__linux__) && !defined (NDEBUG)

#include "ValidationLayers.h"
#include "Instance.h"

namespace TomTekEngine::Rendering 
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
		void* userData
	)
	{
		std::cout << "Validation error: " << messageSeverity << ", " << messageType << "\n";
		std::cout << "\t" << callbackData->pMessage << "\n";
		return VK_FALSE; // Never abort from the program
	}

	ValidationLayers::ValidationLayers() :
		m_DebugMessenger(VK_NULL_HANDLE)
	{}

	void ValidationLayers::Initialize(Instance* ownerInstance)
	{
		const VkDebugUtilsMessengerCreateInfoEXT createInfo = {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.pNext = nullptr,
			//All message severities which we're interested in for debugging
			.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
			//All message types which we are interested in for debugging
			.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			.pfnUserCallback = &ValidationDebugCallback,
			.pUserData = nullptr,
		};

		PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessenger =
			(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr( ownerInstance->GetNative(), "vkCreateDebugUtilsMessengerEXT");
		if ( !createDebugUtilsMessenger )
		{
			throw std::runtime_error( "Fatal Error! Cannot find address of vkCreateDebugUtilsMessengerEXT" );
		}

		if ( createDebugUtilsMessenger( ownerInstance->GetNative(), &createInfo, nullptr, &m_DebugMessenger ) != VK_SUCCESS )
		{
			throw std::runtime_error( "vkCreateDebugUtilsMessengerEXT failed to create m_DebugMessenger!" );
		}

		std::cout << "[DEBUG]: Vulkan ValidationLayers created.\n";
	}
}

#endif