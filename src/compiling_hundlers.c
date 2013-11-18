#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "definition.h"
#include "ichimanyen.h"
#include "compiling_hundlers.h"
#include "file_menu_hundlers.h"


/*##################################### COMPILATION HUNDLERS : USING GCC COMPILER ####################################*/
void on_compile_activate(GtkTextView *compilation_program ,GtkMenuItem *new_item){
  if (saved){
    char * exe= (char*)malloc(strlen(file_saving));
    char * object=(char*)malloc(strlen(file_saving));
    GtkTextIter iStart;
    GtkTextIter iEnd;
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(compilation_program);
    int file_descriptor[2];
    int compilation_success=0;
    exe = strcpy (exe, file_saving);
    object = strcpy(object, file_saving);
    gtk_text_buffer_get_start_iter(buffer, &iStart);
    gtk_text_buffer_get_end_iter(buffer, &iEnd);
    gtk_text_buffer_delete(buffer, &iStart, &iEnd);
    gtk_text_buffer_insert(buffer, &iStart, "Compilation submited...", 21);
    /* execlp("gcc","gcc","-",file_saving,(char*)NULL);*/
    char * buff = (char*) malloc (500);
    int status;
    int pid, p[2];
    int error=0;
    buff[0]='.';
    buff[1]='\0';
    pipe(p);
    pid = fork();
    gtk_text_buffer_insert(buffer, &iStart, "\n\nSeparated compilation...",24 );
    gtk_text_buffer_insert(buffer, &iStart, "\n.c Files Compilation...",24 );
    
    if (pid == 0) {
      /*Son*/
      close(p[0]);
      dup2(p[1],2);
      close(p[1]);
      execlp("gcc","gcc","-c","-pedantic","-Wall",file_saving,(char*)NULL);
      close(p[1]);
    }
    else {
      /*Daddy*/
      close(p[1]);
      dup2(p[0],0);
      scanf("%s",buff);
      if (strcmp(buff,".")!=0){
	gtk_text_buffer_get_end_iter(buffer, &iEnd);
	buff = strcat(buff, " ");
	gtk_text_buffer_insert(buffer, &iStart, "\n\terrors:\n",10 );
	gtk_text_buffer_insert(buffer, &iStart, buff, strlen(buff));
	error = 1;
	 
	while(scanf("%s",buff)>0){
	  
	  if (strcmp(buff,"error:")==0){
	    	gtk_text_buffer_insert(buffer, &iStart, "\n",1 );
	  }
	  gtk_text_buffer_get_end_iter(buffer, &iEnd);
	  buff = strcat(buff, " ");
	  gtk_text_buffer_insert(buffer, &iStart, buff, strlen(buff));
	} 
      }else{
	gtk_text_buffer_insert(buffer, &iStart, "\nerror: None\ncompilated",23 ); 
      } 
      waitpid(0,&status,NULL);
      close(p[0]);
    }
    if (error!=1){
      gtk_text_buffer_insert(buffer, &iStart, "\n\nLink edition:..", 15);
      exe[strlen(file_saving)-2]='\0';
      object[strlen(file_saving)-1]='o';
      pipe(p);
      pid = fork();
    if (pid == 0) {
      /*Son*/
      close(p[0]);
      dup2(p[1],2);
      close(p[1]);
      execlp("gcc","gcc","-o",exe,object,(char*)NULL);
      close(p[1]);
      
    }
    else {
      /*Daddy*/
      close(p[1]);
      dup2(p[0],0);
      scanf("%s",buff);
      //printf("%s\n",buff);
      if (strcmp(buff,".")!=0){
	gtk_text_buffer_get_end_iter(buffer, &iEnd);
	buff = strcat(buff, " ");
	gtk_text_buffer_insert(buffer, &iStart, "\n\terrors:\n",10 );
	gtk_text_buffer_insert(buffer, &iStart, buff, strlen(buff));
	while(scanf("%s",buff)>0){
	  if (strcmp(buff,"error:")==0){
	    gtk_text_buffer_insert(buffer, &iStart, "\n",1 );
	  }
	  gtk_text_buffer_get_end_iter(buffer, &iEnd);
	  buff = strcat(buff, " ");
	  gtk_text_buffer_insert(buffer, &iStart, buff, strlen(buff));
	} 
      }else{
	gtk_text_buffer_insert(buffer, &iStart, "\nerror: None\nLink edited, executable created",44 ); 
      }  
      waitpid(0,&status,NULL);
      close(p[0]);
    }
    }
    
    
    gtk_text_buffer_insert(buffer, &iStart, "\n\nCompilation Finished", 24); 
  }
  else{
    GtkWidget *pDialog;
    pDialog = gtk_message_dialog_new(NULL,
				     GTK_DIALOG_MODAL,
				     GTK_MESSAGE_ERROR,
				     GTK_BUTTONS_OK,
				     "You must save your project before submit a compile");
    gtk_dialog_run(GTK_DIALOG(pDialog));
    gtk_widget_destroy(pDialog);
    
  }
  
}


void on_c_program_key_press_event(GtkStatusbar* bar,GtkWidget *text){
  
  gtk_statusbar_push (GTK_STATUSBAR (bar), GPOINTER_TO_INT(iContextId2), " ");
}
