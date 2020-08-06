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

#include "meetinglistview.h"
#include "meetinglistboxrow.h"


struct _ChimeMeetingListView
{
    GtkGrid parent_instance;

    GtkListBox *list_box;
    GListStore *store;

    ChimeConnection *connection;
};

enum
{
    PROP_0,
    LAST_PROP
};

enum
{
    JOIN_MEETING,
    LAST_SIGNAL
};

static GParamSpec *props[LAST_PROP];
static guint signals[LAST_SIGNAL];

G_DEFINE_TYPE(ChimeMeetingListView, chime_meeting_list_view, GTK_TYPE_GRID)

static void
chime_meeting_list_view_dispose(GObject *object)
{
    ChimeMeetingListView *self = CHIME_MEETING_LIST_VIEW(object);

    G_OBJECT_CLASS(chime_meeting_list_view_parent_class)->dispose(object);
}

static void
chime_meeting_list_view_get_property(GObject    *object,
                                     guint       prop_id,
                                     GValue     *value,
                                     GParamSpec *pspec)
{
    ChimeMeetingListView *self = CHIME_MEETING_LIST_VIEW(object);

    switch (prop_id) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void
chime_meeting_list_view_set_property(GObject      *object,
                                     guint         prop_id,
                                     const GValue *value,
                                     GParamSpec   *pspec)
{
    ChimeMeetingListView *self = CHIME_MEETING_LIST_VIEW(object);

    switch (prop_id) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void
chime_meeting_list_view_constructed(GObject *object)
{
    ChimeMeetingListView *self = CHIME_MEETING_LIST_VIEW(object);


    G_OBJECT_CLASS(chime_meeting_list_view_parent_class)->constructed(object);
}

static void
chime_meeting_list_view_class_init(ChimeMeetingListViewClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    object_class->dispose = chime_meeting_list_view_dispose;
    object_class->get_property = chime_meeting_list_view_get_property;
    object_class->set_property = chime_meeting_list_view_set_property;
    object_class->constructed = chime_meeting_list_view_constructed;


    g_object_class_install_properties(object_class, LAST_PROP, props);

    signals[JOIN_MEETING] =
        g_signal_new_class_handler("join-meeting",
                                   G_TYPE_FROM_CLASS(klass),
                                   G_SIGNAL_RUN_LAST,
                                   NULL, NULL, NULL, NULL,
                                   G_TYPE_NONE, 1,
                                   CHIME_TYPE_MEETING);

    /* Bind class to template */
    gtk_widget_class_set_template_from_resource(widget_class,
                                                "/org/gnome/Chime/ui/meetinglistview.ui");
    gtk_widget_class_bind_template_child(widget_class, ChimeMeetingListView, list_box);
}

static GtkWidget *
create_row(gpointer item,
           gpointer user_data)
{
    ChimeMeeting *meeting = item;

    return chime_meeting_list_box_row_new(meeting);
}

static void
on_row_activated(GtkListBox            *box,
                 GtkListBoxRow         *row,
                 ChimeMeetingListView *self)
{
    g_message("meeting activated");
    g_signal_emit(self, signals[JOIN_MEETING], 0, chime_meeting_list_box_row_get_meeting(CHIME_MEETING_LIST_BOX_ROW(row)));
}

static void
chime_meeting_list_view_init(ChimeMeetingListView *self)
{
    gtk_widget_init_template(GTK_WIDGET(self));

    self->store = g_list_store_new(CHIME_TYPE_MEETING);
    gtk_list_box_bind_model(self->list_box, G_LIST_MODEL(self->store), create_row, self, NULL);

    g_signal_connect(self->list_box, "row-activated",
                     G_CALLBACK(on_row_activated), self);
}

GtkWidget *
chime_meeting_list_view_new(void)
{
    return g_object_new(CHIME_TYPE_MEETING_LIST_VIEW, NULL);
}

static void
on_connection_new_meeting(ChimeConnection      *connection,
                          ChimeMeeting         *meeting,
                          ChimeMeetingListView *self)
{
    g_list_store_append(self->store, meeting);
}

void
chime_meeting_list_view_set_connection(ChimeMeetingListView *self,
                                       ChimeConnection      *connection)
{
    g_return_if_fail(CHIME_IS_MEETING_LIST_VIEW(self));
    g_return_if_fail(CHIME_IS_CONNECTION(connection));

    (void)g_set_object(&self->connection, connection);

    if (connection != NULL) {
        g_signal_connect(connection, "new-meeting",
                         G_CALLBACK(on_connection_new_meeting), self);
    }
}

/* ex:set ts=4 et: */
