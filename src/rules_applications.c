#include "ichimanyen.h"
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <glade/glade.h>
#include "rules_applications.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>

int nb_lignes_coded=10;
int total_yens=0;

char *get_from_rule_code(char* rule);
char *get_for_rule_code(char* rule);
char *get_modulo_rule_code(char* rule);

void on_Apply_clicked(GtkBox* rules_box,GtkButton apply_bouton){
  /*printf("Apply...\n");*/
  total_yens=0;
  GList *list=  (GList*)gtk_container_get_children(GTK_CONTAINER(rules_box));
  if (list == NULL){
    /*error type: LIST NULL POINTER EXCEPTION*/  
    perror("Pas d'argument a implementer");
  GtkWidget* message = gtk_message_dialog_new_with_markup(NULL,GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE , "<span foreground=\"#000FF0\" font_desc=\"Tohoma 12\">Nothing to apply</span>");
  gtk_widget_show_all(message);

  }else{
    int compt = g_list_length(list);
    while (compt>0){
      compt-=1;
      
      GtkToggleButton *rule = (GtkToggleButton*)g_list_nth_data(list,compt);
      if (Applied_rule(gtk_button_get_label(GTK_BUTTON(rule)))){
	gtk_widget_destroy(GTK_WIDGET(rule));
      }
    }
    if(total_yens!=10000){
      //const gchar* warn;
      //g_sprintf(warn,"<span foreground=\"#000FF0\" font_desc=\"Tohoma 12\">Warning:\n</span>you try to creat an ichiman game client, but the sum of bet isn't equals to 10.000 (You've bet: %d)", total_yens);
      GtkWidget* message = gtk_message_dialog_new_with_markup(NULL,GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO ,GTK_BUTTONS_NONE ,(const gchar*)g_strdup_printf("<span foreground=\"#000FF0\" font_desc=\"Tohoma 12\">Warning:\n</span>you try to creat an ichiman game client, but the sum of bet isn't equals to 10.000 (you've bet %d)",total_yens));
      gtk_widget_show_all(message);
      
    }
  }
}
void Next_rule_position(GtkTextIter* begin,GtkTextIter* end){
  /*nothing*/

  //gboolean gtk_text_iter_backward_sentence_starts(begin,10);

}
  
gboolean verification(){
  return TRUE;
  
}

gboolean Applied_rule(const char * rule){
  char* temp = (char*) malloc (strlen(rule));
  temp = strcpy(temp,rule);
  temp+=2;
  if (*temp=='o'){
    /*From i to j Rule*/
    from_value_rule_apply(temp);
    /* printf("From value...\n"); */
  }else if(*temp=='r'){
    /*Value to i round Rule*/
    for_value_rule_apply(temp);
    /* printf("For Value... \n"); */
  }else{
     modulo_value_rule_apply(temp);
    /*Modulo Rule*/
    /* printf("modulo value... \n"); */
  }
  temp-=2;
  free(temp);
  return TRUE;
}
gboolean modulo_value_rule_apply(char * rule){
  GtkTextIter begin;
  GtkTextIter end;
  char* code =  get_modulo_rule_code(rule);
  nb_lignes_coded+=4;
  gtk_text_buffer_get_iter_at_line(c_prog_text, &begin, 10);
  gtk_text_buffer_insert(c_prog_text, &begin,code, -1);
  return TRUE;
}

char *get_modulo_rule_code(char* rule){
  int i =7;
  int round;
  int value;
  char * code = (char* )malloc (2000);
  char* temp = (char*) malloc(25);
  char* chiffre = (char*) calloc(5,5);
  int increment;
  int nb_rounds=0;
  rule-=1;
  
  temp = strcpy(temp,rule);
  temp+=6;
  increment=6;
  round  = atoi (temp);
  nb_rounds=round;
  printf("%d\n",round);
  /*Gift If condition : Round condition*/
  code = strcpy(code,"\tif (i%");
  g_sprintf(chiffre,"%d",round);
  code = strcat(code,chiffre);
  code = strcat(code , "){\n\tprintf(\"%d\\n\",");
  /*Gift value*/
  if (rule[18]=' '){
    temp+=10;
    increment+=10;
    value = atoi (temp);
  }else{
    temp+=9;
    increment+=9;
    value= atoi(temp);
  }
  //printf("total rounds : %d\n",nb_rounds);
  while (nb_rounds){
    total_yens += value;
    nb_rounds-=1;
  }
  /*############# TO CONTROL THE TOTAL NUMBERS OF YENS PLAYED ##############
    #################### AND DISPLAY WARNING IF >10.000 #################### 
    printf("total choisi:  %d\n",total_yens);
  */



  
  g_sprintf(chiffre,"%d",value);
  code = strcat(code,temp);
  /*flushing stdout memory*/
  code= strcat(code,");\n\tfflush(stdout);\n\t}\n\n");
  code[strlen(code)]='\0';
  printf("%s\n",code);
  temp-=increment;
  free(temp);
  free(chiffre);
  return code;

}




gboolean from_value_rule_apply(char * rule){
  GtkTextIter begin;
  GtkTextIter end;
  char* code =  get_from_rule_code(rule);
  nb_lignes_coded+=4;
  gtk_text_buffer_get_iter_at_line(c_prog_text, &begin, 10);
  gtk_text_buffer_insert(c_prog_text, &begin,code, -1);
  return TRUE;
}

char *get_from_rule_code(char* rule){
 int i =10;
  int round;
  int value;
  char * code = (char* )malloc (2000);
  char* temp = (char*) malloc(25);
  char* chiffre = (char*) calloc(5,5);
  int increment;
  int nb_rounds=0;
  rule-=1;
  
  temp = strcpy(temp,rule);
  temp+=4;
  increment=4;
  round  = atoi (temp);
  nb_rounds=round;
  /*Gift If condition : Round condition*/
  code = strcpy(code,"\tif (i>=");
  g_sprintf(chiffre,"%d",round);
  code = strcat(code,chiffre);
  temp+=4;
  increment+=4;
  round  = atoi (temp);
  nb_rounds=(round+1)-nb_rounds;
  g_sprintf(chiffre,"%d",round);
  code = strcat(code," && i<=");
  code = strcat(code,chiffre);
  code = strcat(code , "){\n\tprintf(\"%d\\n\",");
  /*Gift value*/
  if (rule[17]=' '){
    temp+=11;
    increment+=11;
    value = atoi (temp);
  }else{
    temp+=10;
    increment+=10;
    value= atoi(temp);
  }
  //printf("total rounds : %d\n",nb_rounds);
  while (nb_rounds){
    total_yens += value;
    nb_rounds-=1;
  }
  /*############# TO CONTROL THE TOTAL NUMBERS OF YENS PLAYED ##############
    #################### AND DISPLAY WARNING IF >10.000 #################### 
    printf("total choisi:  %d\n",total_yens);
  */
  
  g_sprintf(chiffre,"%d",value);
  code = strcat(code,temp);
  /*flushing stdout memory*/
  code= strcat(code,");\n\tfflush(stdout);\n\t}\n\n");
  code[strlen(code)]='\0';
  temp-=increment;
  free(temp);
  free(chiffre);
  return code;
}

gboolean for_value_rule_apply(char * rule){
  GtkTextIter begin;
  GtkTextIter end;
  //  GtkTextBuffer program =  gtk_text_view_get_buffer(program_text_view);
  // Next_rule_position(&begin,&end);
  char* code =  get_for_rule_code(rule);
  
  gtk_text_buffer_get_iter_at_line(c_prog_text, &begin, nb_lignes_coded);
  gtk_text_buffer_insert(c_prog_text, &begin,code, -1);
  nb_lignes_coded+=4;
  return TRUE;
} 

char *get_for_rule_code(char* rule){
  int i =11;
  int round;
  int value;
  char * code = (char* )malloc (2000);
  char* temp = (char*) malloc(25);
  char* chiffre = (char*) calloc(5,5);
  int increment;
  rule-=1;
  
  temp = strcpy(temp,rule);
  temp+=3;
  increment=3;
  round  = atoi (temp);

  /*Gift If condition : Round condition*/
  code = strcpy(code,"if (i==");
  g_sprintf(chiffre,"%d",round);
  code = strcat(code,chiffre);
  code = strcat(code , "){\n\tprintf(\"%d\\n\",");

  /*Gift value*/
  if (rule[13]=' '){
    temp+=10;
    increment+=10;
    value = atoi (temp);
  }else{
    temp+=9;
    increment+=9;
    value= atoi(temp);
  }  
  total_yens+=value;
  /*############# TO CONTROL THE TOTAL NUMBERS OF YENS PLAYED ##############
    #################### AND DISPLAY WARNING IF >10.000 ####################    
    printf("total choisi:  %d\n",total_yens);
  */
  /*----------------------------------------------------------------------*/
  /*################### End Code Source creating ################*/
  g_sprintf(chiffre,"%d",value);
  code = strcat(code,temp);  
  /*flushing stdout memory*/
  code= strcat(code,");\n\tfflush(stdout);\n\t}\n\n");
  code[strlen(code)]='\0';
  //printf("%s\n",code);
  temp-=increment;
  free(temp);
  free(chiffre);

  return code;
}

