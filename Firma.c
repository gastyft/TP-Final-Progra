#include <stdio.h>
#include<stdlib.h>
#include"Firma.h"

void firma(){


    char firmaT[100][100] = {
    {"#######  #  #######  #     #######  #######  #     #  \n"},
    {"   #             #         #        #     #  #     #  \n"},
    {"   #     #      #    #     #        #     #  #     #  \n"},
    {"   #     #     #     #     #        #     #  #     #  \n"},
    {"   #     #    #      #     #        #     #  #     #  \n"},
    {"   #     #   #       #     #        #     #  #     #  \n"},
    {"   #     #  #######  #     #######  #######  #######  \n"}
  };
  // Imprimir la firma digital en grande
  for (int i = 0; i < 7; i++) {
            system("COLOR B");
    printf("%s", firmaT[i]);
  }
   printf("\n\n");
  char firma[100][100] = {
    {"#######    ###    #######  #######  #     #     #######  #######   \n"},
    {"#         #   #   #           #      #   #      #           #      \n"},
    {"#        #     #  #           #       # #       #           #      \n"},
    {"#   ###  #######  #######     #        #        #######     #      \n"},
    {"#     #  #     #        #     #        #        #           #      \n"},
    {"#     #  #     #        #     #        #        #           #      \n"},
    {"#######  #     #  #######     #        #        #           #      \n"}

  };

  // Imprimir la firma digital en grande
  for (int i = 0; i < 7; i++) {

    printf("%s", firma[i]);
  }

}
