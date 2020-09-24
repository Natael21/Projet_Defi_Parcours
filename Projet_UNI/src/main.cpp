#include <Arduino.h>
#include <LibRobus.h>
#include <stdio.h>

//#define nombre_tour

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  delay(1500);

  BoardInit();

  //"console": "integratedTerminal"
  }

void loop() {
  // put your main code here, to run repeatedly:
  //3200 pulses par tour
  //(0) = Left
  //(1) = right
  int nombre_commande = 0;

  //Serial.println("Rentrez le nombre de commande a effectuer :");
  //scanf("%d", &nombre_commande);
  nombre_commande = 3;

  float tableau_commande[nombre_commande][2];
  //tableau_test[0][0] = 1;

  //distance en po
  tableau_commande[0][0] = 15;
  //nombre de tour entre 0.0 et 1.0
  tableau_commande[0][1] = 0.0;

  //distance en po
  tableau_commande[1][0] = 0;
  //nombre de tour entre 0.0 et 1.0
  tableau_commande[1][1] = 0.5;

  //distance en po
  tableau_commande[2][0] = 15;
  //nombre de tour entre 0.0 et 1.0
  tableau_commande[2][1] = 0.0;

  //Faire deux tableaux à 2 colonnes et 15-20 lignes 
  //(vérifier si les commandes sont null et si c'est le cas arrêter le robot, car le parcours est finis)
  //on a juste besoin de rentré la vitesse du moteur 0 et 1 (tableau #1 float) 
  //saisir le nombre de tour et l'angle à effectuer (tableau #2 double)
  //faire une boucle qui lit les deux tableaux et effectue les bonnes commdandes





/*
  //On demande quelle sont les commandes à effectuer
  for(int i = 0; i < nombre_commande; i++)
  {
    //[i][0] = distance en po
    Serial.println("Rentrez la distance en po à faire :");
    scanf("%d", &tableau_commande[i][0]);

    //[i][1] = angle en degree
    Serial.println("Rentrez le nombre de tour (0.0-1.0) sur lui même a faire (0 si ligne droite, positif si l'angle est a droite, négatif si l'agle est a gauche):");
    scanf("%d", &tableau_commande[i][1]);
  }



  */

    //On met les encodeurs a 0
    ENCODER_Reset(0);
    ENCODER_Reset(1);

  int y = 0;
  //on effectue les commandes voulues
  for(int i = 0; i < nombre_commande; i++)
  {
    Serial.print(y);

    //On va tout droit
    if(tableau_commande[i][1] == 0.0)
    {
      while(ENCODER_Read(1) <= ((tableau_commande[i][0]/3)*3200))
      {
        MOTOR_SetSpeed(0, 0.5);
        MOTOR_SetSpeed(1, 0.47);
      }

      ENCODER_Reset(0);
      ENCODER_Reset(1);
    }
    //On doit tourner a droite
    else if(tableau_commande[i][1] >= 0.0)
    {
      while(ENCODER_Read(0) <= (tableau_commande[i][1]*12800))
      {
        MOTOR_SetSpeed(0, 0.49);
        MOTOR_SetSpeed(1, -0.1);
      }      

      ENCODER_Reset(0);
      ENCODER_Reset(1);
    }
    //On doit tourner a gauche
    else if (tableau_commande[i][1] <= 0.0)
    {
      while(ENCODER_Read(1) <= (-1*tableau_commande[i][1]*12800))
      {
        MOTOR_SetSpeed(0, -0.1);
        MOTOR_SetSpeed(1, 0.49);
      }
     
      ENCODER_Reset(0);
      ENCODER_Reset(1);
    }       
    y++;
  }


  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  //Le moteur tourne dans le vide
  for(;;);

/*
//avance 4 tour
  while(ENCODER_Read(1) <= 12800)
  {
    MOTOR_SetSpeed(0, 0.5);
    MOTOR_SetSpeed(1, 0.47);
  }

  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);



//tourne a gauche
  while(ENCODER_Read(1) <= 3200)
  {
    MOTOR_SetSpeed(0, -0.1);
    MOTOR_SetSpeed(1, 0.49);
  }

  //ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);




//Avance 2 tour
   while(ENCODER_Read(1) <= 6400)
  {
    MOTOR_SetSpeed(0, 0.5);
    MOTOR_SetSpeed(1, 0.47);
  }

  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);




  //Troune droite 90 degree
   while(ENCODER_Read(0) <= 3200)
  {
    MOTOR_SetSpeed(0, 0.49);
    MOTOR_SetSpeed(1, -0.1);
  }

  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);




  //Avance 5 tour
   while(ENCODER_Read(1) <= 16000)
  {
    MOTOR_SetSpeed(0, 0.5);
    MOTOR_SetSpeed(1, 0.47);
  }

  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);

    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
    for(;;);

    */









/*

//Test de boucle for pour des commandes
  for(int i =0 ; ENCODER_Read(0) <= 12800; i++)
  {
    MOTOR_SetSpeed(0, 0.5);
    MOTOR_SetSpeed(1, 0.5);
  }
*/









/*
  //Avance de 4 tours
if(ENCODER_Read(0) <= 12800 && ENCODER_Read(1) <= 12800)
{
  MOTOR_SetSpeed(0, 0.5);
  MOTOR_SetSpeed(1, 0.5);
}
//Tourne de 90 degrées
else if(ENCODER_Read(0) <= 16000)
{
  MOTOR_SetSpeed(0, -0.15);
  MOTOR_SetSpeed(1, 0.55);
}
else if (ENCODER_Read(0) >= 16000)
{
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  //ENCODER_ReadReset(0);
  //ENCODER_ReadReset(1);
  for(;;);
}
*/

  //for(;;);
}

