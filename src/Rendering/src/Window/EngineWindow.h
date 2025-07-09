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

namespace TomTekEngine::Rendering
{
    class EngineWindow
    {
    protected:
        EngineWindow(const char* winName, uint32_t width, uint32_t height);

    public:
        /// Factory method that creates platform-specific window instances.
        /// Call this method instead of directly constructing this class, as the base class
        /// has no concrete implementation for any operating system.
        static EngineWindow* CreateEngineWindow(const char* winName, uint32_t width, uint32_t height);

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
        virtual bool PollWindowEvents(void) = 0;

    protected:
        const char* m_WindowName;
        uint32_t m_Width;
        uint32_t m_Height;

    };
}