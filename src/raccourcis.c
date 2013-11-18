#include <gtk/gtk.h>
#include "callback.h"
#include "raccourcis.h"

GtkAccelGroup *accel_group_new (gpointer user_data)
{
  GtkAccelGroup *p_accel_group = NULL;

  p_accel_group = gtk_accel_group_new ();
  /* ... */
  return p_accel_group;
}




static void accelerator_new (GtkAccelGroup *p_accel_group, const gchar *accelerator, const gchar *accel_path,
                             GCallback callback, gpointer user_data)
{
  guint key;
  GdkModifierType mods;
  GClosure *closure = NULL;

  gtk_accelerator_parse (accelerator, &key, &mods);
  closure = g_cclosure_new (callback, user_data, NULL);
  gtk_accel_group_connect (p_accel_group, key, mods, GTK_ACCEL_VISIBLE, closure);
  gtk_accel_map_add_entry (accel_path, key, mods);
}
static gboolean accel_new (GtkAccelGroup *accel_group, GObject *acceleratable, guint keyval, GdkModifierType modifier, gpointer user_data)
{
  cb_new (NULL, user_data);
  return TRUE;
}
void create_accel_path(){
  accelerator_new (p_accel_group, "<Control>N", ACCEL_PATH_NEW, G_CALLBACK (accel_new), user_data);
  accelerator_new (p_accel_group, "<Control>O", ACCEL_PATH_OPEN, G_CALLBACK (accel_open), user_data);
  accelerator_new (p_accel_group, "<Control>S", ACCEL_PATH_SAVE, G_CALLBACK (accel_save), user_data);
  accelerator_new (p_accel_group, "<Control><Shift>S", ACCEL_PATH_SAVEAS, G_CALLBACK (accel_saveas), user_data);
  accelerator_new (p_accel_group, "<Control>W", ACCEL_PATH_CLOSE, G_CALLBACK (accel_close), user_data);
  accelerator_new (p_accel_group, "<Control>Q", ACCEL_PATH_QUIT, G_CALLBACK (accel_quit), user_data);

}
