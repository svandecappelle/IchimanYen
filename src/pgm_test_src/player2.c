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
      if(i%4==0){
	bet = 0;
	
      }else if (remain > 3000 && i%2 == 0){
	bet = 900;
	remain = remain-bet;
	
      } else{
	bet = remain/num_game;
	remain = remain-bet;
	
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
