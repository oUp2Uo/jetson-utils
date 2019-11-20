/*
 * Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
 
#ifndef __GL_USER_EVENT_H__
#define __GL_USER_EVENT_H__


/**
 * Define for MOUSE_BUTTON event when button is pressed.
 * @see glEventType::MOUSE_BUTTON
 * @ingroup OpenGL
 */
#define BUTTON_PRESSED 1

/**
 * Define for MOUSE_BUTTON event when button is released.
 * @see glEventType::MOUSE_BUTTON
 * @ingroup OpenGL
 */
#define BUTTON_RELEASED 0

/**
 * Define for KEY_STATE and KEY_RAW events when key is pressed.
 * @see glEventType::KEY_STATE
 * @ingroup OpenGL
 */
#define KEY_PRESSED  1

/**
 * Define for KEY_STATE and KEY_RAW events when key is released.
 * @see glEventType::KEY_STATE
 * @ingroup OpenGL
 */
#define KEY_RELEASED 0


/**
 * User interface event message types.
 *
 * Each event message consists of the event type, a & b message values,
 * and a user-specified pointer.  The event types and message values are
 * desribed below for each type of message.
 *
 * These event messages are dispatched at runtime to glEventHandler
 * callbacks that have been registered via glRegisterEvents() 
 *
 * @see glEventHandler
 * @see glRegisterEvents
 *
 * @ingroup OpenGL
 */
enum glEventType
{
	/**
	 * Message when the mouse has been moved
	 * a = x-coordinate, b = y-coordinate
	 */
	MOUSE_MOVE = 0,

	/**
	 * Message when a mouse button has been pressed/released
	 *
	 * a = button ID
	 * b = BUTTON_PRESSED or BUTTON_RELEASED
	 *
	 * Here is the mapping of the mouse buttons to their ID:
	 *
	 *	- 1 (left button)
	 *   - 2 (middle button / scroll wheel button)
	 *   - 3 (right button)
	 *   - 4 (scroll wheel up)
	 *   - 5 (scroll wheel down)
	 */
	MOUSE_BUTTON,

	/**
	 * Message when the mouse wheel has been scrolled
	 * a = -1 for scrolled up, or +1 for scrolled down
	 */
	MOUSE_WHEEL,

	/**
	 * Message when a key has been pressed or released (with modifiers applied)
	 *
	 * a = key symbol (with modifier translations)
	 * b = KEY_PRESSED or KEY_RELEASED
	 *
	 * These symbols have modifiers applied (Shift, CapsLock, NumLock, ect),
	 * so for example if you press Shift + a, it will be reported as XK_A (A)
	 *
	 * @see `/usr/include/X11/keysymdef.h` for the `XK_ KeySym` symbol definitions.
	 */ 
	KEY_STATE,

	/**
	 * Message when a raw key state has changed (raw, so no modifiers applied)
	 *
	 * a = raw key symbol (without modifier translation)
	 * b = KEY_PRESSED or KEY_RELEASED
	 *
	 * These raw symbols are left unmodified, so they won't be changed by keys like
	 * Shift, CapsLock, NumLock, ect.  Letters will always be reported as lowercase.
	 * For example if you press Shift + a, it will still be reported as XK_a (a)
	 *
	 * @see `/usr/include/X11/keysymdef.h` for the `XK_ KeySym` symbol definitions.
	 */ 
	KEY_RAW,

	/**
	 * Message when a keyboard ASCII character (0-255) was entered
	 *
	 * a = ASCII character (0-9, a-Z, !-?, ect.)
	 *
	 * These will have modifiers applied (Shift, CapsLock, NumLock, ect),
	 * so for example if you press Shift + a, it will be reported as 'A'.
	 */
	KEY_CHAR,

	/**
	 * Message indicating that the window is closing
	 * (no parameters)
      */
	WINDOW_CLOSED
};


/**
 * Event message handler callback for recieving UI messages from a window.
 *
 * Recieves 4 parameters - the event type, a & b message values (see above),
 *                         and a user-specified pointer from registration.
 *
 * Event message handlers should return `true` if the message was 
 * handled, or `false` if the message was skipped or not handled.
 *
 * @see glRegisterEvents
 * @see glRemoveEvents
 *
 * @ingroup OpenGL
 */
typedef bool (*glEventHandler)(uint16_t event, int a, int b, void* user);


/**
 * Register an event message handler that will be called with events.
 * @param callback function pointer to the event message handler callback
 * @param user optional user-specified pointer that will be passed to all
 *             invocations of this event handler (typically an object)
 * @param display optional display ID of the glDisplay instance to use
 */
void glRegisterEvents( glEventHandler callback, void* user=NULL, uint32_t display=0 );


/**
 * Unregister an event message handler from being called with events.
 * UnregisterEventHandler() will search for previously registered event
 * handlers that have the same function pointer and/or user pointer,
 * and remove them for being called again in the future.
 */
void glUnregisterEvents( glEventHandler callback, void* user=NULL );


#endif
