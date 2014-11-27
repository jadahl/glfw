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

#ifndef POINTER_LOCK_CLIENT_PROTOCOL_H
#define POINTER_LOCK_CLIENT_PROTOCOL_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

struct wl_client;
struct wl_resource;

struct _wl_confined_pointer;
struct _wl_locked_pointer;
struct _wl_pointer_lock;
struct wl_region;
struct wl_seat;
struct wl_surface;

extern const struct wl_interface _wl_confined_pointer_interface;
extern const struct wl_interface _wl_locked_pointer_interface;
extern const struct wl_interface _wl_pointer_lock_interface;
extern const struct wl_interface wl_region_interface;
extern const struct wl_interface wl_seat_interface;
extern const struct wl_interface wl_surface_interface;

#define _WL_POINTER_LOCK_LOCK_POINTER	0
#define _WL_POINTER_LOCK_CONFINE_POINTER	1

static inline void
_wl_pointer_lock_set_user_data(struct _wl_pointer_lock *_wl_pointer_lock, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) _wl_pointer_lock, user_data);
}

static inline void *
_wl_pointer_lock_get_user_data(struct _wl_pointer_lock *_wl_pointer_lock)
{
	return wl_proxy_get_user_data((struct wl_proxy *) _wl_pointer_lock);
}

static inline void
_wl_pointer_lock_destroy(struct _wl_pointer_lock *_wl_pointer_lock)
{
	wl_proxy_destroy((struct wl_proxy *) _wl_pointer_lock);
}

static inline struct _wl_locked_pointer *
_wl_pointer_lock_lock_pointer(struct _wl_pointer_lock *_wl_pointer_lock, struct wl_surface *surface, struct wl_seat *seat, struct wl_region *region)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_constructor((struct wl_proxy *) _wl_pointer_lock,
			 _WL_POINTER_LOCK_LOCK_POINTER, &_wl_locked_pointer_interface, NULL, surface, seat, region);

	return (struct _wl_locked_pointer *) id;
}

static inline struct _wl_confined_pointer *
_wl_pointer_lock_confine_pointer(struct _wl_pointer_lock *_wl_pointer_lock, struct wl_surface *surface, struct wl_seat *seat, struct wl_region *region)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_constructor((struct wl_proxy *) _wl_pointer_lock,
			 _WL_POINTER_LOCK_CONFINE_POINTER, &_wl_confined_pointer_interface, NULL, surface, seat, region);

	return (struct _wl_confined_pointer *) id;
}

/**
 * _wl_locked_pointer - receive relative pointer motion events
 * @locked: enter event
 * @unlocked: leave event
 *
 * The wl_locked_pointer interface represents a locked pointer state.
 *
 * While the lock of this object is active, the pointer of the associated
 * seat will not move.
 *
 * This object will send the event 'locked' when the lock is activated.
 * Whenever the lock is activated, it is guaranteed that the locked surface
 * will already have received pointer focus and that the pointer will be
 * within the region passed to the request creating this object.
 *
 * To unlock the pointer, send the destroy request. This will also destroy
 * the wl_locked_pointer object.
 *
 * If the compositor decides to unlock the pointer the unlocked event is
 * sent. The wl_locked_pointer object is at this point defunct and should
 * be destroyed.
 *
 * When unlocking, the compositor may or may not take the cursor position
 * hint provided using the set_cursor_position_hint request and warp the
 * pointer. If it does, it will not result in any relative motion events.
 */
struct _wl_locked_pointer_listener {
	/**
	 * locked - enter event
	 *
	 * Notification that the pointer lock of this seat's pointer is
	 * activated.
	 */
	void (*locked)(void *data,
		       struct _wl_locked_pointer *_wl_locked_pointer);
	/**
	 * unlocked - leave event
	 *
	 * Notification that the pointer lock of seat's pointer is no
	 * longer active. This object is no defunct and should be
	 * destroyed.
	 */
	void (*unlocked)(void *data,
			 struct _wl_locked_pointer *_wl_locked_pointer);
};

static inline int
_wl_locked_pointer_add_listener(struct _wl_locked_pointer *_wl_locked_pointer,
				const struct _wl_locked_pointer_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) _wl_locked_pointer,
				     (void (**)(void)) listener, data);
}

#define _WL_LOCKED_POINTER_SET_CURSOR_POSITION_HINT	0
#define _WL_LOCKED_POINTER_DESTROY	1

static inline void
_wl_locked_pointer_set_user_data(struct _wl_locked_pointer *_wl_locked_pointer, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) _wl_locked_pointer, user_data);
}

static inline void *
_wl_locked_pointer_get_user_data(struct _wl_locked_pointer *_wl_locked_pointer)
{
	return wl_proxy_get_user_data((struct wl_proxy *) _wl_locked_pointer);
}

static inline void
_wl_locked_pointer_set_cursor_position_hint(struct _wl_locked_pointer *_wl_locked_pointer, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	wl_proxy_marshal((struct wl_proxy *) _wl_locked_pointer,
			 _WL_LOCKED_POINTER_SET_CURSOR_POSITION_HINT, surface_x, surface_y);
}

static inline void
_wl_locked_pointer_destroy(struct _wl_locked_pointer *_wl_locked_pointer)
{
	wl_proxy_marshal((struct wl_proxy *) _wl_locked_pointer,
			 _WL_LOCKED_POINTER_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) _wl_locked_pointer);
}

/**
 * _wl_confined_pointer - confined pointer object
 * @confined: enter event
 * @unconfined: leave event
 *
 * The wl_confined_pointer interface represents a confined pointer state.
 *
 * This object will send the event 'confined' when the confinement is
 * activated. Whenever the confinement is activated, it is guaranteed that
 * the surface the pointer is confined to will already have received
 * pointer focus and that the pointer will be within the region passed to
 * the request creating this object. It is up to the compositor to decide
 * whether this requires some user interaction and if the pointer will warp
 * to within the passed region if outside.
 *
 * To unconfine the pointer, send the destroy request. This will also
 * destroy the wl_confined_pointer object.
 *
 * If the compositor decides to unconfine the pointer the unconfined event
 * is sent. The wl_confined_pointer object is at this point defunct and
 * should be destoryed.
 */
struct _wl_confined_pointer_listener {
	/**
	 * confined - enter event
	 *
	 * Notification that the pointer confinement of this seat's
	 * pointer is activated.
	 */
	void (*confined)(void *data,
			 struct _wl_confined_pointer *_wl_confined_pointer);
	/**
	 * unconfined - leave event
	 *
	 * Notification that the pointer confinement of seat's pointer is
	 * no longer active. This object is no defunct and should be
	 * destroyed.
	 */
	void (*unconfined)(void *data,
			   struct _wl_confined_pointer *_wl_confined_pointer);
};

static inline int
_wl_confined_pointer_add_listener(struct _wl_confined_pointer *_wl_confined_pointer,
				  const struct _wl_confined_pointer_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) _wl_confined_pointer,
				     (void (**)(void)) listener, data);
}

#define _WL_CONFINED_POINTER_DESTROY	0

static inline void
_wl_confined_pointer_set_user_data(struct _wl_confined_pointer *_wl_confined_pointer, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) _wl_confined_pointer, user_data);
}

static inline void *
_wl_confined_pointer_get_user_data(struct _wl_confined_pointer *_wl_confined_pointer)
{
	return wl_proxy_get_user_data((struct wl_proxy *) _wl_confined_pointer);
}

static inline void
_wl_confined_pointer_destroy(struct _wl_confined_pointer *_wl_confined_pointer)
{
	wl_proxy_marshal((struct wl_proxy *) _wl_confined_pointer,
			 _WL_CONFINED_POINTER_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) _wl_confined_pointer);
}

#ifdef  __cplusplus
}
#endif

#endif
