//Maximilian Wendt programmierte:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
 struct Knoten{
        int wert;
        struct Knoten *folgenderKnoten;
    };

int ermittleGroesse(struct Knoten *ersterKnoten){
    struct Knoten *aktuellerKnoten = ersterKnoten;
    int anzKnoten = 0;

    for(;;){
        anzKnoten++;
        if((aktuellerKnoten -> folgenderKnoten) != aktuellerKnoten){ //Wenn der aktuelle Knoten nicht der letzte der Liste ist
           aktuellerKnoten = aktuellerKnoten -> folgenderKnoten;
        }
        else break; 
    }
    
    return anzKnoten;
} 

struct Knoten *neuerKopf(int daten){
	struct Knoten *kopf = (struct Knoten*) malloc(sizeof(struct Knoten)); //Es wird ein neuer Knoten erstellt, der ein Kopf, also der Beginn einer neuen LinkedList ist
	if(kopf == NULL){
        printf("Es ist kein RAM-Speicher mehr verfügbar! Bitte schließe ein paar Programme. \n");
        exit(1);
    }
    kopf -> wert = daten; //Daten werden im Kopf gespeichert
	kopf -> folgenderKnoten = kopf; //Da der Kopf erstmal das letzte Element seiner Liste ist, zeigt er auf sich selbst
	return kopf;
}


void ausgeben(struct Knoten *ersterKnoten){ // man gibt den Knoten mit, ab welchen die Liste bis zum Ende gedruckt werden soll
    struct Knoten *aktuellerKnoten = ersterKnoten;
    int anzZuDruckenderKnoten = ermittleGroesse(ersterKnoten);

    for(int i = 0; i < anzZuDruckenderKnoten; i++){
        
       if(i==(anzZuDruckenderKnoten-1)) printf("(%d)", aktuellerKnoten-> wert); //Wenn der letzte Wert der Liste gedruckt werden soll, muss nur der Inhalt des Knotens ohne Pfeil gedruckt werden
        else printf("(%d)-> ", aktuellerKnoten-> wert); //Wir drucken den Wert des aktuellen Knoten in Klammern mit Pfeil auf den naechsten
        
        aktuellerKnoten = aktuellerKnoten-> folgenderKnoten; //der neue aktuelle Knoten ist der folgendeKnoten des alten aktuellen Knotens

    }
    printf("\n");
}

void sortieren(struct Knoten *ersterKnoten){

    int zwischenspeicher = 0; 
    struct Knoten *linkerKnoten = ersterKnoten; //Da wir nicht wie bei einem Array einen Index zum navigieren in der Liste haben, brauchen wir ein neues Variablen Pärchen um durch die Liste zu gehen und um zu tauschen
    struct Knoten *rechterKnoten = ersterKnoten->folgenderKnoten;
    int anzZuSortierenderKnoten = ermittleGroesse(ersterKnoten);
    short einmalgetauscht = 0; //Für verbesserten Bubblesort


    for(int i=0;i<anzZuSortierenderKnoten-1;i++){ //-1 da der Rechte Knoten schon hinten angekommen ist, wenn man beim vorletzten "Index" ist
        for(int j=0;j<anzZuSortierenderKnoten-i-1;j++){ //-i da die Anzahl von i hinten am Array schon sortiert ist
            if((linkerKnoten->wert) > (rechterKnoten->wert)){//Wenn getauscht werden muss
                //Tausche nur die WERTE der Knoten und NICHT die Knoten an sich, da snst auch die nachfolgenden Elemente umgespeichert werden müssen... 
                zwischenspeicher = rechterKnoten->wert; //Wert des rechten Knotens wird zwischengespeichert, da er danach mit dem Wert des linken Knoten überschrieben wird
                rechterKnoten->wert = linkerKnoten->wert;
                linkerKnoten->wert = zwischenspeicher;
                if(einmalgetauscht==0)einmalgetauscht++;
            }
            //Da gleich nächste Iteration muss das Knotenpaar um eins erhöht werden
            linkerKnoten = linkerKnoten->folgenderKnoten;
            rechterKnoten = rechterKnoten->folgenderKnoten;
        }
        if(einmalgetauscht == 0) break; //optimierter Bubblesort, wenn Liste in einem Durchgang kein einziges mal getauscht, ist sie fertig sortiert
        //Knoten auf ersten Wert ruecksetzen
        linkerKnoten = ersterKnoten;
        rechterKnoten = ersterKnoten->folgenderKnoten;
    }


}

void hintenEinfuegen (struct Knoten *kopf, int daten){ //Der Kopf ist ein beliebiges Element in der Liste, in der ein Knoten mit Wert daten eingefügt werden soll
	struct Knoten *neuerKnoten = (struct Knoten*) malloc(sizeof(struct Knoten)); //Hier wird EIN neuer Knoten erstellt
	struct Knoten *aktuellerKnoten = kopf;

    if(neuerKnoten == NULL || aktuellerKnoten == NULL){
        printf("Es ist kein RAM-Speicher mehr verfügbar! Bitte schließe ein paar Programme. \n");
        exit(1);
    }


    neuerKnoten -> wert = daten;
    neuerKnoten -> folgenderKnoten = neuerKnoten; //der neue Knoten wird zu einem Schwanzknoten gemacht, da er ganz hinten in die Liste kommt

    while(aktuellerKnoten -> folgenderKnoten != aktuellerKnoten){ //solange der aktuelle Knoten noch nicht der letzte knoten in der Liste ist...
        aktuellerKnoten = aktuellerKnoten -> folgenderKnoten; //...ist der aktuelle Knoten der Knoten, der nach dem aktuellen Knoten kommt
    }
    
    aktuellerKnoten -> folgenderKnoten = neuerKnoten; //neuerKnoten wird hinten eingefügt

    

}   

float bubblesortZeitmessung(struct Knoten *liste){
    clock_t zeitInMs;
    zeitInMs = clock();

   sortieren(liste);//Liste wird sortiert

   zeitInMs = clock() - zeitInMs;
   return ((float)zeitInMs)/CLOCKS_PER_SEC;
}

void main(){
   
    srand(time(NULL)); //Sequenz für Random Nummer Generator soll immer unterschiedlich sein

//Es werden fünf neue Köpfe für fünf unterschiedliche Listen erstellt und mit einem Zufallswert gefüllt
   struct Knoten *kopf1 = neuerKopf((int)(rand()%100+1)); 
   struct Knoten *kopf2 = neuerKopf((int)(rand()%100+1));
   struct Knoten *kopf3 = neuerKopf((int)(rand()%100+1));
   struct Knoten *kopf4 = neuerKopf((int)(rand()%100+1));
   struct Knoten *kopf5 = neuerKopf((int)(rand()%100+1));

   for(int i=1; i < 100; i++){ //Es werden zu jeder Liste 99 zufällige Werte hinzugefügt
        hintenEinfuegen(kopf1, (int)(rand()%100+1));
        hintenEinfuegen(kopf2, (int)(rand()%100+1));
        hintenEinfuegen(kopf3, (int)(rand()%100+1));
        hintenEinfuegen(kopf4, (int)(rand()%100+1));
        hintenEinfuegen(kopf5, (int)(rand()%100+1));
   }

  

   printf("Zum Beweis das der Algorithmus funktioniert: \n");
   printf("Eine Liste von fünf Listen hat wie gewuenscht %d Elemente.\n", ermittleGroesse(kopf1));
   printf("Unsortierte erste Liste:\n");
   ausgeben(kopf1);
   sortieren(kopf1);
   printf("Sortierte erste Liste:\n");
   ausgeben(kopf1);


   printf("\nBubbleSort brauchte für Liste 1 nur %f Sekunden, da sie schonmal sortiert wurde und der Bubblesort-Algorithmus verbessert ist und den Best-case erkennt.\n\n" , bubblesortZeitmessung(kopf1));
   printf("\nBubbleSort brauchte für Liste 2: %f Sekunden \n\n" , bubblesortZeitmessung(kopf2));
   printf("\nBubbleSort brauchte für Liste 3: %f Sekunden \n\n" , bubblesortZeitmessung(kopf3));
   printf("\nBubbleSort brauchte für Liste 4: %f Sekunden \n\n" , bubblesortZeitmessung(kopf4));
   printf("\nBubbleSort brauchte für Liste 5: %f Sekunden \n\n" , bubblesortZeitmessung(kopf5));
 
   printf("Man erkennt wunderbar das man die Schneligkeit eines Algorithmus, wegen der hohen Ungenauigkeit NICHT in Zeit angeben sollte.\n");

}