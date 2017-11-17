#include <stdlib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <glib/gprintf.h>

#define WINDOW_HEIGTH 650
#define WINDOW_WEIGHT 800
#define MALLOC_SIZE 10000
int size_file =0;
int p1_score=0;
int p2_score=0;
int draw=0;


/* ########################## CUT ROUND FUNTION ######################## */
char* roundn(int i, char* result){
  char * round=(char*)malloc (size_file) ;
  char sText[10];
  g_sprintf(sText,"game %d",i);
  //  printf("%s\n",result);
  if (round == NULL){
    perror("Can not access memory map.");
  }
  if ((result = strstr(result,sText))!=NULL){
    round = strcpy(round, result);
    //  printf("le probleme est ici!\nsize : %d\n\n\n",strlen(round));
    
    round[339]='\0';
  }
  return round;
}


char* find_winner(char* file_buffer, int round_number, char ** argv){
  int compt=0;
  
  //printf("%s\n",file_buffer);
  char* temp = (char*) malloc (size_file);
  //char* winner;
  temp = strcpy(temp,file_buffer);
  /*  printf("erreur\n"); */
  /*  printf("%s\n",round); */
  while (compt<=round_number && temp!=NULL){
    temp = strstr(temp,"won");
    //printf("%d\n",compt);
    if (temp!=NULL){
      temp++;
      compt++;
    }
  }
  //printf("%d\n",compt);
  if (temp==NULL){
    // printf("Draw\n");
    draw+=1; 
    return "Draw";
  
  } 
  if (temp[5]=='0'){
    draw+=1;
    return "Draw";
  }
  temp-=strlen(argv[1])+3;
  if (*temp=='\n' || *temp=='/' ){
    temp++;
    temp[4+strlen(argv[1])]='\0';
    p2_score+=1;
    return temp;
  }else {
    
    //printf("graa\n");
    temp+=strlen(argv[1])+3;
    temp-=strlen(argv[2])+4;
    temp[5+strlen(argv[2])]='\0';
    //    printf("%s\n",temp);
      if(*temp=='\n' || *temp=='/' ){
	temp++;
	p1_score+=1;
	return temp;
      } else{
	draw+=1;
	return "Draw";
      }
  }
  return temp;
  // printf("%s\n",temp);
}


/* ##################### LOADING TEMPORARLY GAME FILE ################## */
char* lire_fichier(){
  int fd = open("result",O_RDONLY);
  int i=1;
  int charlu=0;
  int chartotal=0;
  char * retour= (char*) malloc(MALLOC_SIZE) ;
  if (fd == -1){
    perror ("File error.");
    exit(EXIT_FAILURE);
  }
  if (retour==NULL){
    perror("Can not access memory map.");
  }
  while ((charlu=read(fd,&retour[chartotal],MALLOC_SIZE))<=MALLOC_SIZE){
    i++;  
    if (charlu == 0){
      retour[chartotal] = '\0';
      size_file = chartotal+1;
      close(fd);
      return retour;
    }
    
    chartotal += charlu;
    if (charlu==-1){
      perror("can't read file...");
      close(fd);
      exit(EXIT_FAILURE);
    }
    if ((retour=(char*)realloc(retour,MALLOC_SIZE*i)) ==NULL){
      close(fd);
      exit(EXIT_FAILURE); 
    }
    
    //printf("char lu: %d\n\n\n\n %s\nsize retour: %d\n",charlu,retour,strlen(retour));
  }
  close(fd);
  return retour;
}

void end(GtkWidget *fenetre){
  gtk_widget_destroy(fenetre);
  exit(EXIT_SUCCESS);
  
}

/* ################### MAIN ENTRANCE PROGRAM  FUNCTION ################## */
int main(int argc,char **argv){
  GtkWidget * fenetre;
  GtkWidget * label1;
  //GtkWidget *label2;
  GtkWidget *pVBox;
  GtkWidget *pVBox2;
  GtkWidget *pHBox;
  GtkWidget *pHBox2;
  GtkWidget *pHBoxPrimary;
  GtkWidget* separateur;
  GtkWidget *pScrollbar;
  //FILE* game;
  /*#################### GTK MAIN FUNCTION'S BUILDING #################### */
  gtk_init(&argc, &argv);
  
  /* ########################## ARGUMENTS CONTROL ######################## */
  if (argc<2){
    errno = 8;
    perror("3 arguments required: 1st program Player, 2nd program Player, Integer");
    return EXIT_FAILURE;
  }
  if (atoi(argv[3])<1){
    perror ("Round number must be more than 0");
    exit(1);
  }
  
  //int ending =0;
  /*##################### MAIN WINDOW'S BUILDING ######################### */
  fenetre= gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(fenetre), "ICHIMAN YENS");
  gtk_window_set_default_size(GTK_WINDOW(fenetre),WINDOW_WEIGHT,WINDOW_HEIGTH);
  gtk_window_set_position(GTK_WINDOW(fenetre),GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(fenetre),"destroy", G_CALLBACK(end),NULL);

  /* ######################### LAYERS BUILDING ########################### */
  pHBoxPrimary =  gtk_hbox_new(FALSE,0);
  pVBox = gtk_vbox_new(FALSE, 0);
  pVBox2 = gtk_vbox_new(TRUE, 0);
  pHBox = gtk_hbox_new(FALSE,0);
  gtk_box_pack_start(GTK_BOX(pHBoxPrimary), pVBox, FALSE, TRUE, 0);
  separateur =gtk_vseparator_new();
  gtk_box_pack_start(GTK_BOX(pHBoxPrimary), separateur, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(pHBoxPrimary), pVBox2, TRUE, TRUE, 0);
  pScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(fenetre),pScrollbar);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pHBoxPrimary);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  gtk_box_pack_start(GTK_BOX(pVBox), pHBox, FALSE, TRUE, 0);
  
  
  /* ####################### PLAYERS LABEL BUILDING ###################### */
  int compt =1;
  char *nom_joueur[150]; 
  nom_joueur[0] = argv[1];
  nom_joueur[1] = argv[2];
  int d=0;
  
  while(d<2){
    //printf("BLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    int carset = strlen(argv[d+1]);
    while(nom_joueur[d][carset] != '/'){
      carset--;
    }
    
    carset++;
    nom_joueur[d]+=carset;
    //    printf("playser :   %s\n",nom_joueur[d]);
    d++;
  }
  
  
  for (compt=1;compt<=2;compt++){
    char player[256];
    GtkWidget *joueur1;
    g_sprintf(player,"<span font_desc=\"Times New Roman italic 12\" foreground=\"#0000FF\"> Player %d: %s </span>\n",compt,nom_joueur[compt-1]);
    joueur1 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(joueur1),player);
    gtk_box_pack_start(GTK_BOX(pHBox), joueur1, FALSE, TRUE, 50);
    if (compt == 1){
      separateur =gtk_vseparator_new();
      gtk_box_pack_start(GTK_BOX(pHBox), separateur, TRUE, FALSE, 0);
    }
  }
  separateur =gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(pVBox), separateur, FALSE, TRUE, 0);
  
  
  /*################### FINAL RESULT 'S LABEL BUILDING ################### */
  GtkWidget *lblResultat;
  lblResultat = gtk_label_new(NULL);
  GtkWidget * boxresultat;
  boxresultat= gtk_vbox_new(FALSE,0);
  gtk_box_pack_start(GTK_BOX(pVBox2), boxresultat, TRUE, TRUE, 0);
  gtk_label_set_markup(GTK_LABEL(lblResultat),"<span font_desc=\"Times New Roman italic 12\" foreground=\"#FF0000\"> Final Result </span>\n");
  gtk_box_pack_start(GTK_BOX(boxresultat), lblResultat, FALSE, FALSE, 0);
  separateur =gtk_vseparator_new();
  gtk_box_pack_start(GTK_BOX(pHBoxPrimary), separateur, FALSE, TRUE, 0);
  separateur =gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(boxresultat), separateur, FALSE, TRUE, 0);
  
  /* ##################### FORK() MAIN PROGRAM CALLING #################### */
  char *sText = (char*)malloc(2000);
  //printf("arguments ######################:\n\t argv1 : %s\n\targv2: %s\n\targv3",argv[1],argv[2]);
  
  //g_sprintf(sText,"./match %s %s %s > result",argv[1],argv[2],argv[3]);
  
  //fprintf(stderr,sText,"\n");
  int p[2];
  pipe(p);
  int descriptor= open("result",O_CREAT,0777);
  if (descriptor==-1) {
    printf("error result file descriptor.");
    exit(1);
  }
  if (fork()==0){
    
    if ((freopen("result", "w", stdout)) != NULL)
      {
        /* Exécuter le programme */
	execlp("./match","./match",argv[1],argv[2],argv[3],">result",NULL);
	fprintf(stderr,"Cannot execute match\n");
        fclose (stdout);
      }
    else
      {
        /* La redirection a échoué */
	fprintf(stderr,"Cannot redirect stdout match\n");
      }
    
  }else{
    waitpid(0,(int)NULL,(int)NULL);
  }
  
  
  
  
  /* ######################## ROUND LABEL BUILDING ######################## */
  char *label;
  label = lire_fichier();
  int i =1;
  for (i=1; i<=atoi(argv[3]);i+=1){  
    char *round;
    round = roundn(i,label);
    label1 = gtk_label_new(round);
    pHBox2 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(pVBox), pHBox2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox2), label1, FALSE, FALSE,150);
    separateur =gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(pVBox), separateur, FALSE, TRUE, 0);
    //separateur =gtk_vseparator_new();
    //gtk_box_pack_start(GTK_BOX(pHBox2), separateur, FALSE, FALSE, 0);
    //find_winner(label,i-2,argv);
    free(round);
    
    char* tampon= (char*)malloc(200) ;
    
    //g_sprintf(tampon, "game %d",i);

    g_sprintf(tampon,"<span font_desc=\"Times New Roman italic 12\" foreground=\"#0000FF\"> GAME %d</span>",i);
    label1 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label1),tampon);
    gtk_box_pack_start(GTK_BOX(boxresultat), label1, FALSE, FALSE,0);
  
    label1 = gtk_label_new(find_winner(label,i-1,nom_joueur));
    gtk_box_pack_start(GTK_BOX(boxresultat), label1, FALSE, FALSE,0);
    separateur =gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(boxresultat), separateur, FALSE, FALSE, 0);  
    free(tampon);
    
    
  }

    label1 = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label1),"<span font_desc=\"Times New Roman italic 12\" foreground=\"#0000FF\"> FINAL RESULT </span>\n");
    gtk_box_pack_start(GTK_BOX(boxresultat), label1, FALSE, TRUE,0);  
    
    g_sprintf(sText,"<span font_desc=\"Times New Roman italic 12\" foreground=\"#0F0040\">%s won: %d\n%s won: %d</span>\n<span font_desc=\"Times New Roman italic 12\" foreground=\"#EF0000\">Draw: %d</span>",nom_joueur[0],p1_score,nom_joueur[1],p2_score,draw);
    label1 =gtk_label_new(NULL) ;

    gtk_label_set_markup(GTK_LABEL(label1),sText);
/*gtk_label_new(strcat(find_winner(label,i,nom_joueur)," Final result"))*/
    gtk_box_pack_start(GTK_BOX(boxresultat), label1, FALSE, FALSE,0);
    separateur =gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(boxresultat), separateur, FALSE, FALSE, 0);  
    free(label);
    
    //    printf("p1 : %d\np2: %d\ndraw: %d\n",p1_score,p2_score,draw);
    /* ################## GRAPHICAL SYSTEM FUNCTION CALLING ################# */
    gtk_widget_show_all(fenetre);
    gtk_main();
    return EXIT_SUCCESS;
}
