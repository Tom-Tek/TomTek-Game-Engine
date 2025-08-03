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
#include "EngineCore.h"

#include <iostream>

#ifndef ENGINE_CORE_HEADLESS
	using namespace TomTekEngine::Rendering;
#endif

namespace TomTekEngine::Core 
{
	EngineCore::EngineCore()
	{
#ifdef ENGINE_CORE_HEADLESS
		std::cout << "Building engine core headless.\n";
#else
		std::cout << "Building engine core with head.\n";

		// Create the window
		m_Window = EngineWindow::CreateEngineWindow("My Window!", 800, 600);
		// Create the renderer
		m_Renderer = EngineRenderer::CreateEngineRenderer(m_Window.get());
#endif
	}

	void EngineCore::BeginRuntime()
	{
		while ( true )
		{
			if ( m_Window.get() )
				if ( !m_Window->PollWindowEvents() )
					break;
		}

		system("pause");
	}
}