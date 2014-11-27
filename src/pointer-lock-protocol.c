/* 
 * Copyright © 2014      Jonas Ådahl
 * 
 * Permission to use, copy, modify, distribute, and sell this
 * software and its documentation for any purpose is hereby granted
 * without fee, provided that the above copyright notice appear in
 * all copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * the copyright holders not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 * 
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 */

#include <stdlib.h>
#include <stdint.h>
#include "wayland-util.h"

extern const struct wl_interface _wl_confined_pointer_interface;
extern const struct wl_interface _wl_locked_pointer_interface;
extern const struct wl_interface wl_region_interface;
extern const struct wl_interface wl_seat_interface;
extern const struct wl_interface wl_surface_interface;

static const struct wl_interface *types[] = {
	NULL,
	NULL,
	&_wl_locked_pointer_interface,
	&wl_surface_interface,
	&wl_seat_interface,
	&wl_region_interface,
	&_wl_confined_pointer_interface,
	&wl_surface_interface,
	&wl_seat_interface,
	&wl_region_interface,
};

static const struct wl_message _wl_pointer_lock_requests[] = {
	{ "lock_pointer", "noo?o", types + 2 },
	{ "confine_pointer", "noo?o", types + 6 },
};

WL_EXPORT const struct wl_interface _wl_pointer_lock_interface = {
	"_wl_pointer_lock", 1,
	2, _wl_pointer_lock_requests,
	0, NULL,
};

static const struct wl_message _wl_locked_pointer_requests[] = {
	{ "set_cursor_position_hint", "ff", types + 0 },
	{ "destroy", "", types + 0 },
};

static const struct wl_message _wl_locked_pointer_events[] = {
	{ "locked", "", types + 0 },
	{ "unlocked", "", types + 0 },
};

WL_EXPORT const struct wl_interface _wl_locked_pointer_interface = {
	"_wl_locked_pointer", 1,
	2, _wl_locked_pointer_requests,
	2, _wl_locked_pointer_events,
};

static const struct wl_message _wl_confined_pointer_requests[] = {
	{ "destroy", "", types + 0 },
};

static const struct wl_message _wl_confined_pointer_events[] = {
	{ "confined", "", types + 0 },
	{ "unconfined", "", types + 0 },
};

WL_EXPORT const struct wl_interface _wl_confined_pointer_interface = {
	"_wl_confined_pointer", 1,
	1, _wl_confined_pointer_requests,
	2, _wl_confined_pointer_events,
};

