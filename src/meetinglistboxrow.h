/*
 * Copyright © 2020 Amazon.com, Inc. or its affiliates.
 *
 * Authors: Ignacio Casal Quinteiro <icq@gnome.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef CHIME_MEETING_LIST_BOX_ROW_H
#define CHIME_MEETING_LIST_BOX_ROW_H

#include <gtk/gtk.h>

#include "chime-contact.h"
#include "chime-conversation.h"
#include "chime-room.h"
#include "chime-meeting.h"

G_BEGIN_DECLS

#define CHIME_TYPE_MEETING_LIST_BOX_ROW (chime_meeting_list_box_row_get_type ())
G_DECLARE_FINAL_TYPE(ChimeMeetingListBoxRow, chime_meeting_list_box_row, CHIME, MEETING_LIST_BOX_ROW, GtkListBoxRow)

GtkWidget       *chime_meeting_list_box_row_new            (ChimeMeeting           *meeting);

ChimeMeeting    *chime_meeting_list_box_row_get_meeting    (ChimeMeetingListBoxRow *self);

G_END_DECLS

#endif /* CHIME_MEETING_LIST_BOX_ROW_H */

/* ex:set ts=4 et: */
