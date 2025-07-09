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
#include "EngineRenderer.h"

#ifdef _WIN32
	#include "RHI/DirectX12/DX12RHI.h"
	#include "RHI/Vulkan/VulkanRHI.h"
#elif __linux__
	#include "RHI/Vulkan/VulkanRHI.h"
#elif __APPLE__

#endif

namespace TomTekEngine::Rendering 
{
	EngineRenderer::EngineRenderer(EngineWindow* windowTarget) :
		m_WindowTarget(windowTarget)
	{}

	EngineRenderer* EngineRenderer::CreateEngineRenderer(EngineWindow* windowTarget)
	{
		const SupportedRenderingAPIs& suitedAPI = GetBestSuitedAPI();

		if ( suitedAPI == SupportedRenderingAPIs::Vulkan )
			return new VulkanRHI(windowTarget);
		else if ( suitedAPI == SupportedRenderingAPIs::DirectX12 )
			return new DX12RHI(windowTarget);
		else if ( suitedAPI == SupportedRenderingAPIs::Metal )
			return nullptr;

		return nullptr;
	}

	SupportedRenderingAPIs EngineRenderer::GetBestSuitedAPI()
	{
#ifdef FORCE_RENDERING_API
		if (strcmp(FORCE_RENDERING_API, "None") == 0)
			return SupportedRenderingAPIs::None;
		else if (strcmp(FORCE_RENDERING_API, "Vulkan") == 0)
			return SupportedRenderingAPIs::Vulkan;
		else if (strcmp(FORCE_RENDERING_API, "DirectX12") == 0)
			return SupportedRenderingAPIs::DirectX12;
		else if (strcmp(FORCE_RENDERING_API, "Metal") == 0)
			return SupportedRenderingAPIs::Metal;
#else
	#ifdef _WIN32
		return SupportedRenderingAPIs::DirectX12;
	#elif __linux__
		return SupportedRenderingAPIs::Vulkan;
	#elif __APPLE__
		return SupportedRenderingAPIs::Metal;
	#endif
#endif

		return SupportedRenderingAPIs::None;
	}

}