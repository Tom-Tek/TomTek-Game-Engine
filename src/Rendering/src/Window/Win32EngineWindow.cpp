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
#ifdef _WIN32

#include "Win32EngineWindow.h"

namespace TomTekEngine::Rendering 
{
	static LRESULT CALLBACK WindowProcess(HWND handleToWindow, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch ( msg )
		{
		case WM_CLOSE:
		{
			// Tell 

			HMENU handleMenu;
			handleMenu = GetMenu(handleToWindow);
			if ( handleToWindow )
			{
				DestroyMenu(handleMenu);
			}

			break;
		}

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT paintStruct;
			HDC hdc = BeginPaint(handleToWindow, &paintStruct);
			EndPaint(handleToWindow, &paintStruct);
			return 0;
		}

		default:
			return DefWindowProc(handleToWindow, msg, wParam, lParam);
		}

		return DefWindowProc(handleToWindow, msg, wParam, lParam);
	} 

	Win32EngineWindow::Win32EngineWindow(const char* winName, const uint32_t width, const uint32_t height) :
		EngineWindow(winName, width, height),
		m_Message({})
	{
		WNDCLASS windowClass = {
			.lpfnWndProc = WindowProcess,
			.hInstance = m_HandleToInstance,
			.hCursor = LoadCursor( nullptr, IDC_ARROW ),
			.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH),
			.lpszClassName = L"WindowClassName",
		};

		if ( !RegisterClass(&windowClass) )
		{
			throw std::runtime_error("TomTek Win32EngineWindow failed to register WNDCLASS");
		}

		m_HandleToWindow = CreateWindow(
			windowClass.lpszClassName,
			L"TomTek Engine x64 Windows", //i only plan to support x64 configurations
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			m_Width, m_Height,
			nullptr, nullptr,
			m_HandleToInstance,
			nullptr
		);

		if ( !m_HandleToWindow )
		{
			throw std::runtime_error("TomTek Win32EngineWindow window creation failed [HWND NULL]");
		}


		ShowWindow(m_HandleToWindow, SW_SHOW);
		UpdateWindow(m_HandleToWindow);


	}

	bool Win32EngineWindow::PollWindowEvents()
	{
		// See if the window is offline
		if ( GetWindowThreadProcessId(m_HandleToWindow, nullptr) == 0 )
		{
			return false;
		}

		// Process Window Events
		// Using PeekMessage() so we can use idle time to render the scene
		const bool gotMessage = ( PeekMessage(&m_Message, nullptr, 0U, 0U, PM_REMOVE) != 0 );
		if ( gotMessage )
		{
			TranslateMessage(&m_Message);
			DispatchMessage(&m_Message);
		}
		else
		{

		}

		return true;
	}
}

#endif