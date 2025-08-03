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

#include <iostream>

/// Forces the rendering API to use one of the following
/// Comment out if not enforcing specific API
///		- Vulkan
///		- DirectX12
///		- Metal
#define FORCE_RENDERING_API	"Vulkan"

namespace TomTekEngine::Rendering 
{
	enum class SupportedRenderingAPIs : uint8_t
	{
		None,
		Vulkan,
		DirectX12,
		Metal,
	};

	class EngineWindow;

	class EngineRenderer
	{
	protected:
		EngineRenderer(EngineWindow* windowTarget);

	public:
		/// Creates a new graphics engine renderer
		/// The graphics API used depends on the operating system which the user
		/// is currently on.
		static std::unique_ptr<EngineRenderer> CreateEngineRenderer(EngineWindow* windowTarget);

		/// Depending on the operating system which the client is using
		/// this function will return the best suited graphics API to use
		/// for the local user's machine.
		///		Windows - Vulkan
		///		Linux - Vulkan
		///		MacOS - Metal
		static SupportedRenderingAPIs GetBestSuitedAPI();

	protected:
		EngineWindow* m_WindowTarget;
	};
}