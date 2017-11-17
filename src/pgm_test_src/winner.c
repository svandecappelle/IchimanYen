#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
  int n,i,j;
  int num_game;

  num_game=atoi(argv[1]);

  for(j=1;j<=num_game;++j){
    int bet=0;
    int sum=0;
    int remain = 10000;
    printf("%d\n",bet); //1
    fflush(stdout);
    sum+=bet;
    scanf("%d",&n);
    
    for(i=2;i<=9;++i){
      if (i<8){
	bet=random()%(remain/4);
	if (bet>1000){
	  bet =999;
	  
	}
	remain -=bet;
      }else{
	bet = remain/2;
	remain -=bet;
      }
      printf("%d\n",bet); //2-9
      fflush(stdout);
      sum+=bet;
      scanf("%d",&n);
    }

    bet=10000-sum;
    printf("%d\n",bet); //10
    fflush(stdout);
    sum+=bet;
    scanf("%d",&n);
  }

  exit(EXIT_SUCCESS);
}
