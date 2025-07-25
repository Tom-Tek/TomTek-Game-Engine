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

#if defined (_WIN32) || defined (__linux__) && !defined (NDEBUG)

#include <vector>
#include "VulkanPlatform.h"
\
namespace TomTekEngine::Rendering 
{
	class Instance;

	class ValidationLayers final
	{
	public:
		ValidationLayers();
		~ValidationLayers();

	public:
		void Initialize(Instance* ownerInstance);

	public:
		const std::vector<const char*>& GetValidationLayers() const { return m_ValidationLayers; }

	private:
		VkDebugUtilsMessengerEXT m_DebugMessenger;
		Instance* m_OwnerInstance;

		const std::vector<const char*> m_ValidationLayers = {
			"VK_LAYER_KHRONOS_validation",
		};
	};
}

#endif