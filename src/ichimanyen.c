#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include<stdlib.h>
#include <glade/glade.h>
#include <glib.h>
#include <glib/gprintf.h>
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
#include "compiling_hundlers.h" 
#include "rules_applications.h"

extern arguments args;
files players;
modulo_rules modulo[10];
int nb_rules_modulos=0;
int nb_rounds=1;
int nb_rules_i_to_j=0;
values_rules iToj[10];

int nb_rules_i=0;
values_rules i_rule[10];
GtkTextBuffer *c_prog_text;



void on_value_rule_value_changed(GtkSpinButton *spinButton){
  iToj[nb_rules_i_to_j].value= gtk_spin_button_get_value(spinButton);
  //printf("value: %d\n",iToj[nb_rules_i_to_j].value);
}
void on_i_rule_value_changed(GtkSpinButton *spinButton){
   iToj[nb_rules_i_to_j].begin= gtk_spin_button_get_value(spinButton);
   //printf("From: %d\n",iToj[nb_rules_i_to_j].begin);
}
void on_j_rule_value_changed(GtkSpinButton *spinButton){
  iToj[nb_rules_i_to_j].end= gtk_spin_button_get_value(spinButton);
  //printf("to: %d\n",iToj[nb_rules_i_to_j].end);
}

void on_i_rule1_value_changed(GtkSpinButton *i_number){
  i_rule[nb_rules_i].begin= gtk_spin_button_get_value(i_number);
  //printf("%d\n",  i_rule[nb_rules_i].begin);
}


void on_value_rule_for_value_changed(GtkSpinButton *value){
  i_rule[nb_rules_i].value= gtk_spin_button_get_value(value);
  //printf("%d\n",  i_rule[nb_rules_i].value);
}

void add_for_i_clicked(GtkBox *rules_box){
  GtkWidget *toogleButton;
  //GtkWidget *joueur1;
  char label[256];
  //printf("AddButton\n");
  g_sprintf(label,"for %d value = %d", i_rule[nb_rules_i].begin, i_rule[nb_rules_i].value);
  toogleButton = gtk_toggle_button_new_with_label(label);
  gtk_box_pack_start(rules_box, toogleButton, FALSE, TRUE, 0);
  gtk_widget_show(toogleButton);
  int i=nb_rules_i;
  while (i<9){
    i_rule[i].begin=i_rule[nb_rules_i].begin;
    i_rule[i].value=i_rule[nb_rules_i].value;
    i+=1;
  }

  nb_rules_i+=1;  
}



void on_rule_itoj_button_clicked(GtkBox *rules_box){
  if (nb_rules_i_to_j <10){
    GtkWidget *toogleButton;
    //printf("Adding ...\n");
    char label[256];
    //GtkWidget *joueur1;
    g_sprintf(label,"from %d to %d value = %d", iToj[nb_rules_i_to_j].begin, iToj[nb_rules_i_to_j].end, iToj[nb_rules_i_to_j].value);
    toogleButton = gtk_toggle_button_new_with_label(label);
    gtk_box_pack_start(rules_box, toogleButton, FALSE, TRUE, 0);
    gtk_widget_show(toogleButton);
    int i=nb_rules_i_to_j;
    while (i<9){
      iToj[i].begin=iToj[nb_rules_i_to_j].begin;
      iToj[i].end=iToj[nb_rules_i_to_j].end;
      iToj[i].value=iToj[nb_rules_i_to_j].value;
      i+=1;
    }
    nb_rules_i_to_j+=1;  
  }
  else{
    printf("Erreur plus assez d'espace pour les règles\n");
  }
}

/*                                             Help Message Dialogs                                                 */
void on_messagedialog1_response(GtkWidget *message_dialog){
  gtk_widget_destroy(message_dialog);
  gtk_main_quit();
  
}
void on_help_modulo_clicked(GtkWidget* button_help, GtkWindow *parent){
  
  //printf(gtk_widget_get_name(button_help));
  GtkWidget* message = gtk_message_dialog_new_with_markup(parent,GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE , "<span foreground=\"#000FF0\" font_desc=\"Tohoma 12\">Modulo helping</span>\nmodulo is a mathematical rule giving the remain of a division\nFor exemple : 10[4]=2. Explain : 10/4 = 2 and Remain is <span foreground=\"#FF3000\">2</span>");
  gtk_widget_show_all(message);
  
}

void on_help_for_clicked(GtkWidget * button_help, GtkWindow *parent){
  GtkWidget* message = gtk_message_dialog_new_with_markup(parent,GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE , "<span foreground=\"#000FF0\" font_desc=\"Tohoma 12\">For rule help:</span>\n\nYou can select a value for a specified round. Select the round and then select the sum you want to play for this round.\n");
  gtk_widget_show_all(message);
  
}

void on_help_from_clicked(GtkWidget * button_help, GtkWindow *parent){
  GtkWidget* message = gtk_message_dialog_new_with_markup(parent,GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE , "<span foreground=\"#000FF0\" font_desc=\"Tohoma 12\">From rule helping:</span>\n\nYou can select an interval wich you want to play a sum. Select the interval and then the sum you want.");
  gtk_widget_show_all(message);
  
}





/*                                          Expander box Hundlers                                                   */
void on_remove_rule_clicked(GtkBox *rules_box, GtkButton *remove_button){
  GList* widgets= gtk_container_get_children(GTK_CONTAINER(rules_box));
  if (widgets!=NULL){
    int i=0;
    for (i;i<(int)g_list_length(widgets);i+=1){
      GtkWidget *toggleButton = GTK_WIDGET(g_list_nth_data(widgets,i));
      if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggleButton)) ){	
	gtk_widget_destroy(toggleButton);
	nb_rules_modulos-=1;
      }
    }
  }else{
    printf("Rien a effacer\n");
  }
}


/*                                              Add Rules buttons Hundlers                                           */
void on_add_modulo_clicked(GtkBox *rules_box, GtkButton *add_button){
  if (nb_rules_modulos <10){
    GtkWidget *toogleButton;
    //printf("Adding ...\n");
    char label[256];
    GtkWidget *joueur1;
    g_sprintf(label,"modulo %d value = %d",modulo[nb_rules_modulos].modulo,modulo[nb_rules_modulos].value);
    toogleButton = gtk_toggle_button_new_with_label(label);
    gtk_box_pack_start(rules_box, toogleButton, FALSE, TRUE, 0);
    gtk_widget_show(toogleButton);
    int i=nb_rules_modulos;
    while (i<9){
      modulo[i].modulo=modulo[nb_rules_modulos].modulo;
      modulo[i].value=modulo[nb_rules_modulos].value;
      i+=1;
    }
    nb_rules_modulos+=1;  
  }
  else{
    printf("Erreur plus assez d'espace pour les modulos\n");
  }
}
void on_modulo_remain_value_changed(GtkSpinButton *spinButton){
  int i=0;
  for (i; i<10;i+=1){
    if (nb_rules_modulos <10){
      modulo[i].value = gtk_spin_button_get_value(spinButton);
    }
    else{
      printf("Erreur plus assez d'espace pour les modulos\n");
    }
  }
}
void on_modulo_value_changed(GtkSpinButton *spinButton){
  int i=0;
  for (i; i<10;i+=1){
    if (nb_rules_modulos <10){
      modulo[i].modulo = gtk_spin_button_get_value(spinButton);
    }
    else{
      printf("Erreur plus assez d'espace pour les modulos\n");
    }
  }
}



/*                                    Executing dialog Window hundlers                                             */
void on_player2_file_set(GtkWidget *file){ 
  players.file_player2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
  //printf("%s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file)));
}
void on_player1_file_set(GtkWidget *file){ 
  players.file_player1 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
  //printf("%s\n",gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file)));
}
void on_round_nb_value_changed(GtkSpinButton *spin_button_nb_rounds){
  nb_rounds=  gtk_spin_button_get_value(spin_button_nb_rounds);
  printf("%d\n",nb_rounds);
}
void on_OKbutton_clicked(GtkWidget *ok,GtkWidget * fenetre){
  int pid=-1; 
  
  pid=fork(); 
  char sText[30];
  //printf("game %s, %s, %d\n", players.file_player1,players.file_player2,nb_rounds);
  if(pid==0){  
    /*fils */
    g_sprintf(sText,"%d",nb_rounds);
    execlp("./game","./game",players.file_player1,players.file_player2,sText,NULL);
    fprintf(stderr,"Cannot execute game\n");
    exit(EXIT_FAILURE);
  }
  
}
/*################################ LOADING RUNNING-WINDOW INTERFACE ############################## */ 
void on_Execute_activate(GtkWidget *widget) {
  GladeXML *xml;
  GtkWidget *window;
  gtk_init(&args.argc, &args.argv);
  xml = glade_xml_new("../xml/Run.glade", NULL, NULL);
  glade_xml_signal_autoconnect(xml);
  window = glade_xml_get_widget(xml, "dialog1");
  gtk_widget_show_all(window);
  gtk_main();
}

/*########################################## LOADING ABOUT INTERFACE ###############################*/
void on_about_activate(GtkWidget *widget) {
  GladeXML *xml;
  GtkWidget *window;
  gtk_init(&args.argc, &args.argv);
  xml = glade_xml_new("../xml/about.glade", NULL, NULL);
  glade_xml_signal_autoconnect(xml);
  window = glade_xml_get_widget(xml, "aboutdialog1");
  gtk_widget_show_all(window);
  gtk_main();
}

/*################################ GLOBALS VARIABLE INITIALIZING ###################################*/
void initialisation(){
  
  int i=0;
  nb_rules_modulos=0;
  nb_rounds=1;
  nb_rules_i_to_j=0;
  
  for (i;i<10;i+=1){
    modulo[i].modulo=1;
    modulo[i].value=0;
    iToj[i].begin=1;
    iToj[i].end=2;
    iToj[i].value=0;
    
  }
  iContextId1 = gtk_statusbar_get_context_id((GtkStatusbar*)bar, "ExitMsg");
  iContextId2 = gtk_statusbar_get_context_id((GtkStatusbar*)bar, "AboutMsg");
  saved=FALSE;
}









/*########################################### ENTRY POINT PROGRAM ####################################*/

int main(int argc, char** argv){
  GladeXML *xml;
  GtkWidget *window;
  GtkWidget * item;
  guint key;
  GdkModifierType mods;
  GtkTextView *text;
  gtk_init(&argc, &argv);
  args.argc=argc;
  args.argv = argv;
  
  /*#################################### LOADING INTERFACE ########################################### */
  xml = glade_xml_new("../xml/ide.glade", NULL, NULL);
  
  /*################################### CONNECTING SIGNALS WITH INTERFACE #############################*/
  glade_xml_signal_autoconnect(xml);
  
  /*######################################## GETING WINDOW WIDGET #####################################*/
  window = glade_xml_get_widget(xml, "window1");
  bar = glade_xml_get_widget(xml, "satutBarCprog");
  text = (GtkTextView*) glade_xml_get_widget(xml, "c_program");
  c_prog_text =   gtk_text_view_get_buffer(text);
  initialisation();
  gtk_widget_show_all(window);
  
  /*############################################ GTK EVENT LOOP ###################################### */
  gtk_main();
  return EXIT_SUCCESS;
}
