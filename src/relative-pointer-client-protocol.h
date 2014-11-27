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

#ifndef RELATIVE_POINTER_CLIENT_PROTOCOL_H
#define RELATIVE_POINTER_CLIENT_PROTOCOL_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

struct wl_client;
struct wl_resource;

struct _wl_relative_pointer;
struct _wl_relative_pointer_manager;
struct wl_pointer;

extern const struct wl_interface _wl_relative_pointer_interface;
extern const struct wl_interface _wl_relative_pointer_manager_interface;
extern const struct wl_interface wl_pointer_interface;

#define _WL_RELATIVE_POINTER_MANAGER_GET_RELATIVE_POINTER	0

static inline void
_wl_relative_pointer_manager_set_user_data(struct _wl_relative_pointer_manager *_wl_relative_pointer_manager, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) _wl_relative_pointer_manager, user_data);
}

static inline void *
_wl_relative_pointer_manager_get_user_data(struct _wl_relative_pointer_manager *_wl_relative_pointer_manager)
{
	return wl_proxy_get_user_data((struct wl_proxy *) _wl_relative_pointer_manager);
}

static inline void
_wl_relative_pointer_manager_destroy(struct _wl_relative_pointer_manager *_wl_relative_pointer_manager)
{
	wl_proxy_destroy((struct wl_proxy *) _wl_relative_pointer_manager);
}

static inline struct _wl_relative_pointer *
_wl_relative_pointer_manager_get_relative_pointer(struct _wl_relative_pointer_manager *_wl_relative_pointer_manager, struct wl_pointer *pointer)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_constructor((struct wl_proxy *) _wl_relative_pointer_manager,
			 _WL_RELATIVE_POINTER_MANAGER_GET_RELATIVE_POINTER, &_wl_relative_pointer_interface, NULL, pointer);

	return (struct _wl_relative_pointer *) id;
}

/**
 * _wl_relative_pointer - relative pointer object
 * @relative_motion: relative pointer motion
 *
 * A wl_relative_pointer object is an extension to the wl_pointer
 * interface used for emitting relative pointer events. It shares the same
 * focus as wl_pointer objects of the same seat and will only emit events
 * when it has focus.
 */
struct _wl_relative_pointer_listener {
	/**
	 * relative_motion - relative pointer motion
	 * @time: timestamp with millisecond granularity
	 * @dx_int: integral part of the x component of the motion vector
	 * @dx_frac: fractional part of the x component of the motion
	 *	vector
	 * @dy_int: integral part of the y component of the motion vector
	 * @dy_frac: fractional part of the y component of the motion
	 *	vector
	 * @dx_unaccel_int: integral part of the x component of the
	 *	unaccelerated motion vector
	 * @dx_unaccel_frac: fractional part of the x component of the
	 *	unaccelerated motion vector
	 * @dy_unaccel_int: integral part of the y component of the
	 *	unaccelerated motion vector
	 * @dy_unaccel_frac: fractional part of the y component of the
	 *	unaccelerated motion vector
	 *
	 * Relative pointer motion from the pointer of the seat
	 * associated with this object.
	 *
	 * A relative motion is in the same dimension as regular wl_pointer
	 * motion events, except they do not represent an absolute
	 * position. For instance, moving a pointer from (x, y) to (x', y')
	 * would have the equivalent relative motion (x' - x, y' - y).
	 *
	 * This event also contains non-accelerated motion deltas. The
	 * non-accelerated delta is, when applicable, the regular pointer
	 * motion delta as it was before having applied motion acceleration
	 * transformations. The compositor will have applied the same
	 * processing (such as normalization) meaning the events will have
	 * roughly the same magnitude as accelerated motion events.
	 *
	 * Note that it does not represent 'raw' events as they were read
	 * from some device. What acceleration corresponds to is device
	 * specific and may be identical to non-accelerated for some
	 * devices, while for others not.
	 *
	 * Relative motions are not coupled to wl_pointer.motion events,
	 * and can be sent in combination with such events, but also
	 * independently. There may also be scenarious where
	 * wl_pointer.motion is sent, but there is no relative motion.
	 *
	 * The motion vectors are encoded as double fixed point values.
	 *
	 * A double fixed point value is a 64 bit data type encoded as two
	 * separate signed 32 bit integers. The integral part of the value
	 * is stored in one of the integers and the fractional part in the
	 * other.
	 */
	void (*relative_motion)(void *data,
				struct _wl_relative_pointer *_wl_relative_pointer,
				uint32_t time,
				int32_t dx_int,
				int32_t dx_frac,
				int32_t dy_int,
				int32_t dy_frac,
				int32_t dx_unaccel_int,
				int32_t dx_unaccel_frac,
				int32_t dy_unaccel_int,
				int32_t dy_unaccel_frac);
};

static inline int
_wl_relative_pointer_add_listener(struct _wl_relative_pointer *_wl_relative_pointer,
				  const struct _wl_relative_pointer_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) _wl_relative_pointer,
				     (void (**)(void)) listener, data);
}

#define _WL_RELATIVE_POINTER_RELEASE	0

static inline void
_wl_relative_pointer_set_user_data(struct _wl_relative_pointer *_wl_relative_pointer, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) _wl_relative_pointer, user_data);
}

static inline void *
_wl_relative_pointer_get_user_data(struct _wl_relative_pointer *_wl_relative_pointer)
{
	return wl_proxy_get_user_data((struct wl_proxy *) _wl_relative_pointer);
}

static inline void
_wl_relative_pointer_destroy(struct _wl_relative_pointer *_wl_relative_pointer)
{
	wl_proxy_destroy((struct wl_proxy *) _wl_relative_pointer);
}

static inline void
_wl_relative_pointer_release(struct _wl_relative_pointer *_wl_relative_pointer)
{
	wl_proxy_marshal((struct wl_proxy *) _wl_relative_pointer,
			 _WL_RELATIVE_POINTER_RELEASE);

	wl_proxy_destroy((struct wl_proxy *) _wl_relative_pointer);
}

#ifdef  __cplusplus
}
#endif

#endif
