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

#ifdef _WIN32

#include <Windows.h>
#include "EngineWindow.h"

namespace TomTekEngine::Rendering 
{
	class Win32EngineWindow final : public EngineWindow
	{
	public:
		Win32EngineWindow(const char* winName, const uint32_t width, const uint32_t height);
		~Win32EngineWindow() = default;

	public:
		/// Processes all pending window and input events from the OS message queue.
		/// This method should be called once per frame in the main engine loop.
		/// 
		/// Handles events such as:
		/// - User input (keyboard, mouse, controller)
		/// - Window state changes (resize, minimize, maximize)
		/// - System messages (close requests, focus changes)
		/// 
		/// @return true if the window should remain active, false if the window
		///         should be closed (e.g., user clicked the X button or pressed Alt+F4)
		virtual bool PollWindowEvents() override;

	public:
		HINSTANCE GetHandleToInstance() const { return m_HandleToInstance; }
		HWND GetHandleToWindow() const { return m_HandleToWindow; }

	private:
		HINSTANCE m_HandleToInstance;
		HWND m_HandleToWindow;
		MSG m_Message;

	};
}

#endif