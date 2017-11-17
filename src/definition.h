#ifndef DEFINITION_H
#define DEFINITION_H
#include <gdk/gdk.h>
#include <gtk/gtk.h>
typedef struct {
  /*            PLAYERS FILE NAME             */
  gchar* file_player1;
  gchar* file_player2;
}files;

typedef struct {
  /*          ARGUMENTS FOR GTK-INIT          */
  int argc;
  char** argv;
}arguments; 
/*            PROPERTIES FOR MODULOS RULES    */
typedef struct {
  int modulo;
  int value;
  
}modulo_rules;
/*          PROPERTIES FOR "FROM I TO J" RULE */
typedef struct {
  int begin;
  int end;
  int value;
}values_rules;
#endif
