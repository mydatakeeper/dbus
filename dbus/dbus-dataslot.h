/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-dataslot.h  storing data on objects
 *
 * Copyright (C) 2003 Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 1.2
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#ifndef DBUS_DATASLOT_H
#define DBUS_DATASLOT_H

#include <dbus/dbus-internals.h>

DBUS_BEGIN_DECLS;

typedef struct DBusDataSlotAllocator DBusDataSlotAllocator;
typedef struct DBusDataSlotList DBusDataSlotList;

/** Opaque typedef for DBusDataSlot */
typedef struct DBusDataSlot DBusDataSlot;
/** DBusDataSlot is used to store application data on the connection */
struct DBusDataSlot
{
  void *data;                      /**< The application data */
  DBusFreeFunction free_data_func; /**< Free the application data */
};

struct DBusDataSlotAllocator
{
  int *allocated_slots;   /**< Allocated slots */
  int  n_allocated_slots; /**< number of slots malloc'd */
  int  n_used_slots;      /**< number of slots used */
  DBusMutex *lock;        /**< thread lock */
};

struct DBusDataSlotList
{
  DBusDataSlot *slots;   /**< Data slots */
  int           n_slots; /**< Slots we have storage for in data_slots */
};

dbus_bool_t _dbus_data_slot_allocator_init  (DBusDataSlotAllocator  *allocator);
int         _dbus_data_slot_allocator_alloc (DBusDataSlotAllocator  *allocator,
                                             DBusMutex              *mutex);
void        _dbus_data_slot_allocator_free  (DBusDataSlotAllocator  *allocator,
                                             int                     slot_id);
void        _dbus_data_slot_list_init       (DBusDataSlotList       *list);
dbus_bool_t _dbus_data_slot_list_set        (DBusDataSlotAllocator  *allocator,
                                             DBusDataSlotList       *list,
                                             int                     slot,
                                             void                   *data,
                                             DBusFreeFunction        free_data_func,
                                             DBusFreeFunction       *old_free_func,
                                             void                  **old_data);
void*       _dbus_data_slot_list_get        (DBusDataSlotAllocator  *allocator,
                                             DBusDataSlotList       *list,
                                             int                     slot);
void        _dbus_data_slot_list_free       (DBusDataSlotList       *list);


DBUS_END_DECLS;

#endif /* DBUS_DATASLOT_H */
