/* XXX Infinity!

   Copyright (C) 2015 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef INFINITY_H
#define INFINITY_H

#include "nat/gdb_thread_db.h"

/* Initialize the thread debug support library.  */
extern td_err_e infinity_td_init (void);

/* Generate new thread debug library handle for process PS.  */
extern td_err_e infinity_td_ta_new (struct ps_prochandle *ps,
				    td_thragent_t **ta);

/* Map thread library handle PT to thread debug library handle for process
   associated with TA and store result in *TH.  */
extern td_err_e infinity_td_ta_map_id2thr (const td_thragent_t *ta,
					   pthread_t pt,
					   td_thrhandle_t *th);

/* Map process ID LWPID to thread debug library handle for process
   associated with TA and store result in *TH.  */
extern td_err_e infinity_td_ta_map_lwp2thr (const td_thragent_t *ta,
					    lwpid_t lwpid,
					    td_thrhandle_t *th);

/* Call for each thread in a process associated with TA the callback function
   CALLBACK.  */
extern td_err_e infinity_td_ta_thr_iter (const td_thragent_t *ta,
					 td_thr_iter_f *callback,
					 void *cbdata_p,
					 td_thr_state_e state,
					 int ti_pri,
					 sigset_t *ti_sigmask_p,
					 unsigned int ti_user_flags);

/* Validate that TH is a thread handle.  */
extern td_err_e infinity_td_thr_validate (const td_thrhandle_t *th);

/* Return information about thread TH.  */
extern td_err_e infinity_td_thr_get_info (const td_thrhandle_t *th,
					  td_thrinfo_t *infop);

/* Get event address for EVENT.  */
extern td_err_e infinity_td_ta_event_addr (const td_thragent_t *ta,
					   td_event_e event,
					   td_notify_t *ptr);

/* Enable EVENT in global mask.  */
extern td_err_e infinity_td_ta_set_event (const td_thragent_t *ta,
					  td_thr_events_t *event);

/* Disable EVENT in global mask.  */
extern td_err_e infinity_td_ta_clear_event (const td_thragent_t *ta,
					    td_thr_events_t *event);

/* Return information about last event.  */
extern td_err_e infinity_td_ta_event_getmsg (const td_thragent_t *ta,
					     td_event_msg_t *msg);

/* Enable reporting for EVENT for thread TH.  */
extern td_err_e infinity_td_thr_event_enable (const td_thrhandle_t *th,
					      int event);

/* Get address of thread local variable.  */
extern td_err_e infinity_td_thr_tls_get_addr (const td_thrhandle_t *th,
					      psaddr_t map_address,
					      size_t offset,
					      psaddr_t *address);

/* Get address of the given module's TLS storage area for the given thread.  */
extern td_err_e infinity_td_thr_tlsbase (const td_thrhandle_t *th,
					 unsigned long int modid,
					 psaddr_t *base);

#endif /* INFINITY_H */
