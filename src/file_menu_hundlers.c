#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include<stdlib.h>
#include <glade/glade.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "file_menu_hundlers.h"
#include "definition.h"
#include "ichimanyen.h"


/*################################################### FILE MENU ITEM HUNDLERS ###############################################################*/
/* gchar *file_saving=NULL; */
int on_save_button_clicked(GtkFileChooserDialog *window,GtkButton *save_button){
  FILE* fichier;
  GtkTextIter iStart;
  GtkTextIter iEnd;
  gchar* sBuffer;
  gchar* chemin =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window));
  GtkWidget *pDialog;
  if (strstr(chemin,".c")==NULL){
    if(strstr(chemin,".")==NULL){
      chemin = strcat(chemin,".c");
    }else{
      errno=22;
      perror("Nom de fichier incorrect:");
      pDialog = gtk_message_dialog_new(NULL,
				       GTK_DIALOG_MODAL,
				       GTK_MESSAGE_INFO,
				       GTK_BUTTONS_OK,
				       "Bad file name\n%s\ncan't be finished by \".e\"\nchoise a .c or let the program do for you", chemin);
      
      gtk_dialog_run(GTK_DIALOG(pDialog));
      gtk_widget_destroy(pDialog);
      return 0;
    }
  }
  fichier = fopen(chemin,"w+");
  saved= TRUE;
  gtk_text_buffer_set_text(c_prog_text," ", 1);
  gtk_text_buffer_get_start_iter(c_prog_text, &iStart);
  gtk_text_buffer_get_end_iter(c_prog_text, &iEnd);
  sBuffer = gtk_text_buffer_get_text(c_prog_text, &iStart, &iEnd, TRUE); 
  guint i=0;
  if (fichier!=NULL){
    //printf("%s\n",program);
    if (fwrite(sBuffer, strlen(sBuffer), 1,fichier)){
      printf("fin ecriture\n");
      i=1;
     
    }
  }
  fclose(fichier);
  g_free(sBuffer); 
  gtk_widget_destroy(GTK_WIDGET(window));
  gtk_main_quit();
  if (i!=0){
    gtk_statusbar_push (GTK_STATUSBAR (bar), GPOINTER_TO_INT(iContextId1), "saved");
    //i= gtk_statusbar_push((GtkStatusbar*)bar,1,"Saved");
  }
  return 1;
}



int on_save_as_button_clicked(GtkFileChooserDialog *window,GtkButton *save_button){
  FILE* fichier;
  GtkTextIter iStart;
  GtkTextIter iEnd;
  gchar* sBuffer;
  gchar* chemin =  gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(window));
  GtkWidget *pDialog;
  if (strstr(chemin,".c")==NULL){
    if(strstr(chemin,".")==NULL){
      chemin = strcat(chemin,".c");
    }else{
      errno=22;
      perror("Nom de fichier incorrect:");
      pDialog = gtk_message_dialog_new(NULL,
				       GTK_DIALOG_MODAL,
				       GTK_MESSAGE_INFO,
				       GTK_BUTTONS_OK,
				       "Bad file name\n%s\ncan't be finished by \".e\"\nchoise a .c or let the program do for you", chemin);
      
      gtk_dialog_run(GTK_DIALOG(pDialog));
      gtk_widget_destroy(pDialog);
      
      return 0;
      
    }
  }
  file_saving=(gchar*) malloc (strlen(chemin));
  file_saving = strcpy(file_saving,chemin);
  fichier = fopen(chemin,"w+");
  gtk_text_buffer_get_start_iter(c_prog_text, &iStart);
  gtk_text_buffer_get_end_iter(c_prog_text, &iEnd);
  sBuffer = gtk_text_buffer_get_text(c_prog_text, &iStart, &iEnd, TRUE); 
  gint i=0;
  if (fichier!=NULL){
    //printf("%s\n",program);
    if (fwrite(sBuffer, strlen(sBuffer), 1,fichier)){
      printf("fin sauvegarde\n");
      saved=TRUE;
      i=1;
    }
  }
  g_free(sBuffer); 
  gtk_widget_destroy(GTK_WIDGET(window));
  gtk_main_quit();
  fclose(fichier);
  if (i!=0){
   gtk_statusbar_push (GTK_STATUSBAR (bar), GPOINTER_TO_INT(iContextId1), "saved");
  }
  
  return 1;
}

/*################################################################# SAVE FUNCTION #############################################################*/
void saving(){
  FILE* fichier;
 GtkTextIter iStart;
 GtkTextIter iEnd;
 gchar* sBuffer;
 GtkWidget *pDialog;
 
 fichier = fopen(file_saving,"w+");
 gtk_text_buffer_get_start_iter(c_prog_text, &iStart);
 gtk_text_buffer_get_end_iter(c_prog_text, &iEnd);
  sBuffer = gtk_text_buffer_get_text(c_prog_text, &iStart, &iEnd, TRUE); 
  guint i=0;
  if (fichier!=NULL){
    //printf("%s\n",program);
    if (fwrite(sBuffer, strlen(sBuffer), 1,fichier)){
      printf("fin ecriture\n");
      i=1;
      saved=TRUE;
     }
  }
  
  fclose(fichier);
  g_free(sBuffer); 
  if (i!=0){
    //i= gtk_statusbar_get_context_id((GtkStatusbar*)bar, "save");
    gtk_statusbar_push (GTK_STATUSBAR (bar), GPOINTER_TO_INT(iContextId1), "saved");
    printf("%d\n",i);
  }
}



void on_cancel_button_clicked(GtkWindow *window,GtkButton *cancel_button){
  //printf("Closing...\n");
  gtk_widget_destroy(GTK_WIDGET(window));
  gtk_main_quit();
  gtk_statusbar_push (GTK_STATUSBAR (bar), GPOINTER_TO_INT(iContextId1), "Canceled");
    
}




void on_new_activate(GtkTextView *c_program ,GtkMenuItem *new_item){
  GladeXML *xml;
  GtkWidget *window;
  gtk_init(&args.argc, &args.argv);
  xml = glade_xml_new("../xml/saver.glade", NULL, NULL);
  glade_xml_signal_autoconnect(xml);
  window = glade_xml_get_widget(xml, "window1");
  c_prog_text = gtk_text_view_get_buffer(c_program);
  gtk_widget_show_all(window);
  gtk_main();
  
}

void on_save_as_activate(GtkTextView *c_program ,GtkMenuItem *new_item){
  GladeXML *xml;
  GtkWidget *window;
  gtk_init(&args.argc, &args.argv);
  xml = glade_xml_new("../xml/save_as.glade", NULL, NULL);
  glade_xml_signal_autoconnect(xml);
  window = glade_xml_get_widget(xml, "window1");
  c_prog_text = gtk_text_view_get_buffer(c_program);
  gtk_widget_show_all(window);
  gtk_main();
}




void on_save_activate(GtkTextView *c_program ,GtkMenuItem *new_item){
  GladeXML *xml;
  GtkWidget *window;
  gtk_init(&args.argc, &args.argv);
  
  xml = glade_xml_new("../xml/save_as.glade", NULL, NULL);
  glade_xml_signal_autoconnect(xml);
  window = glade_xml_get_widget(xml, "window1");
  c_prog_text = gtk_text_view_get_buffer(c_program);
  if (file_saving==NULL){
    gtk_widget_show_all(window);
    gtk_main();
  }else{
    saving();
  }
  
}
