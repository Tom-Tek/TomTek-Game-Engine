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

#ifndef NDEBUG
#if defined (_WIN32) || defined (__linux__)

#include "VulkanPlatform.h"

#include <vector>

namespace TomTekEngine::Rendering 
{
	class Instance;
	
	class ValidationLayer final
	{
	public:
		~ValidationLayer();

	public:
		const std::vector<const char*>& GetValidationLayerNames() const { return m_ValidationLayerNames; }

	public:
		/// Mandatory to call this method after the creation of the VkInstance
		/// Serves the purpose of creating m_DebugUtilsMessenger & handles the dispatch
		/// of ValidationLayer errors
		void Initialize(Instance* ancestorInstance);

		/// Added this to list all Validation Layers which the local machine has installed
		/// into the console. As I'm currently writing this method, adding "VK_LAYER_KHRONOS_validation"
		/// to m_ValidationLayerNames causes vkCreateInstance to always throw an exception.
		void DebugLogAllAvailableLayers();

	private:
		const std::vector<const char*> m_ValidationLayerNames = {
			"VK_LAYER_KHRONOS_validation",
		};

		Instance* m_AncestorInstance = nullptr;
		VkDebugUtilsMessengerEXT m_DebugUtilsMessenger = VK_NULL_HANDLE;
	};
}

#endif
#endif