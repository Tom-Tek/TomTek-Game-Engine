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
#include "EngineWindow.h"

#ifdef _WIN32
	#include "Win32EngineWindow.h"
#elif __linux__

#elif __APPLE__

#endif

namespace TomTekEngine::Rendering 
{
	EngineWindow::EngineWindow(const char* winName, uint32_t width, uint32_t height) :
		m_WindowName(winName),
		m_Width(width),
		m_Height(height)
	{}

	std::unique_ptr<EngineWindow> EngineWindow::CreateEngineWindow(const char* winName, uint32_t width, uint32_t height)
	{
#ifdef _WIN32
		return std::make_unique<Win32EngineWindow>(winName, width, height);
#elif __linux__

#elif __APPLE__

#endif

		return nullptr;
	}
};