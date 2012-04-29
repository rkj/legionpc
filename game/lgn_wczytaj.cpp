
#include "Amos.h"

#include "legion.h"
#include "lgn_wczytaj.h"
#include "utl_locale.h"

void WCZYTAJ_BRON(void) {
		//	Procedure WCZYTAJ_BRON
		//	   For I=1 To 19
		//	      Read A$
		//	      BRON2$(I)=A$
		//	   Next I
		//	   DANE1:
		//	   Data "axe","sword","shield","bow","arrows"
		//	   Data "armour","helmet","boots","spear","club"
		//	   Data "hammer","scroll","herb","treasure","catapult"
		//	   Data "stone","food","potion","skin"
		for( int i=1; i<=19; ++i )
			BRON2_S[i] = GS("B"+toString(i-1,"%3.3d"));

		//	   MX_WEAPON=120
		MX_WEAPON=120;

		//	   For I=1 To MX_WEAPON
		//	      Read A$
		//	      'Print I,A$ : Wait Key
		//	      BRON$(I)=A$
		//	      For J=1 To 11
		//	         Read A
		//	         BRON(I,J)=A
		//	      Next J
		//	   Next I
		//	   _MODULO=50+Rnd(130)
		_MODULO = 50 + Rnd(130);

		//	   DANE2:
		//	   'nazwa            s p s e t w g d mag,cena,bob
		//	   Data "light",5,1,0,0,2,2,4,1,0,100,28
		//	   Data "steel",7,2,0,0,2,6,4,2,0,150,2
		//	   Data "silver",12,3,0,0,2,5,4,5,0,500,2
		//	   Data "long",10,5,0,0,2,9,4,3,0,200,2
		//	   Data "fire",15,5,0,0,2,4,4,9,9,800,20
		//	   Data "Dragon fang",25,8,0,0,2,5,4,9,2,3000,20
		//	   Data "Szczerbiec",50,15,0,0,2,5,4,9,5,10000,20

		//	   '-topory          s p s e t w g d mag cena
		//	   Data "common",6,2,0,0,1,7,4,0,0,120,3
		//	   Data "storm",9,3,0,0,1,15,4,0,0,190,3
		//	   Data "chromic",12,5,0,0,1,15,4,8,0,350,3
		//	   '10
		//	   Data "golden",25,10,0,0,1,12,4,9,0,1100,3
		//	   '-mîoty            s p s e t  w  g d mag cena
		//	   Data "stone",7,2,0,0,11,16,4,0,0,150,4
		//	   Data "heavy",10,3,0,0,11,30,4,1,0,300,4
		//	   Data "diamond",25,5,0,0,11,25,4,2,0,1050,4
		//	   Data "goblins",30,5,0,0,11,20,4,5,0,1500,4
		//	   '-tarcze          s p s e t w g d mag cena
		//	   Data "wooden",0,8,0,0,3,3,4,0,0,50,1
		//	   Data "steel",0,15,0,0,3,8,4,0,0,150,15
		//	   Data "storm",0,19,0,0,3,15,4,0,0,300,15
		//	   Data "gremlin's",0,25,0,0,3,10,4,0,0,900,1
		//	   '-îuki            s p s e t w g d mag cena
		//	   Data "common",10,0,0,0,4,1,4,0,0,80,5
		//	   '20
		//	   Data "special",15,0,0,0,4,2,4,0,0,190,5
		//	   Data "elf",20,0,0,0,4,1,4,0,0,400,5
		//	   '-heîmy
		//	   Data "pointed",0,5,0,0,7,1,1,0,0,100,8
		//	   Data "horned",2,5,0,0,7,2,1,0,0,170,8
		//	   'buty            s p s e t w g d mag cena
		//	   Data "leather",0,0,6,0,8,1,3,0,0,80,9
		//	   Data "shoed",0,2,8,0,8,1,3,0,0,150,9
		//	   'zbroje            s p s e t w g d mag cena
		//	   Data "light",0,10,0,0,6,10,2,0,0,200,7
		//	   Data "coat of mail",0,18,0,0,6,12,2,0,0,400,7
		//	   Data "steel",0,13,0,0,6,20,2,0,0,300,7
		//	   Data "heavy",0,22,0,0,6,30,2,0,0,390,18
		//	   '30
		//	   Data "silver",0,28,0,0,6,15,2,0,0,900,18
		//	   'zioîa              s p s e t  w g d mag cena
		//	   Data "sterydius",0,2,0,2,13,0,1,0,0,300,12
		//	   Data "furialis",2,0,5,2,13,0,1,0,0,500,12
		//	   Data "mole's root",-5,0,0,-40,13,0,1,0,0,5000,12
		//	   Data "castor",0,0,8,-5,13,0,1,0,0,400,12
		//	   Data "spinach",3,0,0,0,13,0,1,0,0,300,12
		//	   Data "bay leaf",0,0,0,30,13,0,1,0,0,200,12
		//	   Data "black grass ",0,0,0,0,13,0,1,0,30,400,12
		//	   'strzaîy          s p s e t w g d mag cena
		//	   Data "common",15,0,0,0,5,0,4,0,0,50,6
		//	   Data "poisoned",20,0,0,0,5,0,4,10,0,100,6
		//	   '40
		//	   Data "magic",25,0,0,0,5,0,4,0,20,200,6
		//	   'czary               s p s e  t w g d mag cena
		//	   Data "MagicMissile(5)",25,0,0,0,12,0,4,1,5,200,14
		//	   Data "Fireball (8)",45,0,0,0,12,0,4,1,8,350,14
		//	   Data "ChaosBreath(12)",20,0,0,0,12,0,4,1,12,600,14
		//	   Data "Flames (15)",35,0,0,0,12,0,4,2,15,700,14
		//	   Data "Lighting (20)",55,0,0,0,12,0,4,2,20,900,14
		//	   Data "Mind Probe (3)",0,0,0,0,12,0,4,3,3,120,13
		//	   Data "Curing (5)",0,0,0,10,12,0,4,2,5,200,13
		//	   Data "Healing (20)",0,0,0,100,12,0,4,2,20,900,13
		//	   Data "Brightness(40)",10,0,0,0,12,0,4,5,40,500,13
		//	   '50
		//	   Data "Intuition (15)",0,0,0,0,12,0,4,6,15,450,13
		//	   Data "God's Wrath(50)",70,0,0,0,12,0,4,7,50,2500,14
		//	   Data "Slow down (10)",0,0,-20,0,12,0,4,2,10,350,14
		//	   'buty           s p s e t w g d mag cena
		//	   Data "light",0,0,9,0,8,1,3,0,0,100,9
		//	   Data "fighting",2,5,7,0,8,3,3,0,0,230,9
		//	   'maczuga             s p s e  t w g d mag cena
		//	   Data "ogre bone",7,2,0,0,10,4,4,0,0,50,11
		//	   Data "wooden",4,1,0,0,10,1,4,0,0,20,11
		//	   Data "prickly",9,2,0,0,10,4,4,0,0,80,11
		//	   Data "ruffianly",11,3,0,0,10,3,4,0,0,100,11
		//	   'katapulty         s p sz e t   w  g d mag cena bb
		//	   Data "siege",60,20,0,0,15,150,4,0,0,500,32
		//	   '60
		//	   Data "ruining",40,10,0,0,15,120,4,0,0,450,32
		//	   Data "light",30,6,0,0,15,50,4,0,0,600,32
		//	   Data "ogre",90,15,0,0,15,60,4,0,0,1150,32
		//	   'gîazy              s p sz e t   w g d mag cena bb
		//	   Data "small",10,0,0,0,16,10,4,0,0,2,33
		//	   Data "big",20,0,0,0,16,20,4,0,0,4,33
		//	   Data "medium",15,0,0,0,16,18,4,0,0,4,33
		//	   Data "granite",40,0,0,0,16,20,4,0,0,20,33
		//	   Data "marble",30,0,0,0,16,19,4,0,0,15,33
		//	   'heîmy            s p s e t w g d mag cena bb
		//	   Data "Klingon",2,6,0,0,7,2,1,0,0,600,19
		//	   Data "Magic",2,6,3,0,7,-40,1,0,0,870,8
		//	   '70
		//	   'mixtury             s p s e  t  w g d mag cena bb
		//	   Data "ple ple",0,0,0,20,18,1,1,0,0,150,16
		//	   Data "poison",-10,-10,0,-90,18,1,1,0,0,500,16
		//	   Data "sheep tongue",5,2,0,-5,18,1,1,0,0,300,16
		//	   Data "honey",4,0,0,30,18,1,1,0,0,490,16
		//	   Data "halucinum",0,0,0,0,18,1,1,0,50,450,16
		//	   Data "cure",0,0,0,70,18,1,1,0,0,350,16
		//	   'ûywnoôê              s p s e  t w g d mag cena bb
		//	   Data "hog meat",0,0,0,0,17,2,4,35,0,20,22
		//	   Data "gargoyl meat",0,0,0,0,17,2,4,85,0,50,22
		//	   Data "wolf meat",0,0,0,0,17,2,4,20,0,40,22
		//	   'kosztownoôci     s p s e  t w g d mag cena bb
		//	   Data "gold",0,0,0,0,14,0,4,0,0,2000,21
		//	   '80
		//	   Data "stones",0,0,0,0,14,0,4,0,0,1500,21
		//	   Data "coins",0,0,0,0,14,0,4,0,0,3000,21
		//	   Data "diamonds",0,0,0,0,14,0,4,0,0,5000,21
		//	   'skóry            s p s e  t w g d mag cena bb
		//	   Data "hog",0,5,0,0,19,0,2,0,0,200,24
		//	   Data "gargoyl",0,9,0,0,19,0,2,0,0,1450,24
		//	   Data "wolf",0,8,0,0,19,0,2,0,0,350,24
		//
		//	   Data "miraculous",1,3,20,0,8,2,3,0,0,500,9
		//	   'ubranie          s p s e t w g d mag cena bb
		//	   'czary2             s p s e t w g d mag cena bb
		//	   Data "Conversion(60)",0,0,0,0,12,0,4,8,60,2000,14
		//	   Data "Explosion (25)",40,0,0,0,12,0,4,9,25,998,14
		//
		//	   Data "carrion",0,0,0,0,17,2,4,20,0,20,22
		//	   '90
		//	   'zbroje2           s  p s e t w g d mag cena
		//	   Data "scaled",0,12,0,0,6,7,2,0,0,800,7
		//	   Data "lighting",10,30,0,0,6,12,2,0,0,2300,7
		//	   Data "ogre",0,43,0,0,6,70,2,0,0,1700,18
		//	   Data "Vingren's",12,32,0,0,6,30,2,0,0,2400,18
		//	   'oszczepy             s p s e t w g d mag cena
		//	   Data "whale",17,1,0,0,9,3,4,0,0,300,10
		//	   Data "long",10,1,0,0,9,4,4,0,0,200,10
		//	   Data "Wolf fang",20,2,0,0,9,5,4,0,0,1100,10
		//	   Data "Tusk",30,3,0,0,9,8,4,0,0,1700,10
		//	   'mixtury 2         s p s e   t  w g d mag cena bb
		//	   Data "wine",0,0,0,-10,18,1,1,0,10,70,16
		//	   Data "troll milk",0,1,12,-10,18,1,1,0,0,500,16
		//	   '100
		//	   Data "water",0,0,0,10,18,1,1,0,0,10,16
		//	   Data "motorolum",0,0,18,0,18,1,1,0,0,800,16
		//	   Data "blood",-20,0,-20,-20,18,1,1,0,0,300,16
		//	   Data "umkoum",3,0,0,0,18,1,1,0,0,80,16
		//	   'pterodon
		//	   Data "haunch",0,0,0,0,17,2,4,25,0,20,22
		//	   Data "fur",0,3,0,0,19,0,2,0,0,280,24
		//	   '-îuki            s p s e t w g d mag cena
		//	   Data "Falcon",38,0,0,0,4,1,4,0,0,1180,5
		//	   'strzaîy              s p s e t w g d mag cena
		//	   Data "Falcon talons",35,0,0,0,5,0,4,0,0,1150,6
		//	   'heîmy            s p s e t w g d mag cena bb
		//	   Data "Sorasil's",8,10,5,0,7,0,1,0,0,1220,19
		//	   'czary3                  s p s e  t w g  d mag cena bb
		//	   Data "Unsure (12)",20,0,0,0,12,0,4,10,12,200,14
		//	   '110
		//	   Data "Intimidate(20)",50,0,0,0,12,0,4,10,12,600,14
		//	   'dodatkowy stuff
		//	   'miecze            s p s e t w g d mag cena
		//	   Data "Barbarian",8,3,0,0,2,7,4,1,0,120,2
		//	   Data "Hornet",14,1,1,0,2,8,4,1,0,700,2
		//	   Data "Chaos",13,1,-2,0,2,9,4,1,0,650,28
		//	   'topory
		//	   Data "orks",10,7,0,0,1,37,4,0,0,120,3
		//	   Data "silver",14,5,0,0,1,27,4,0,0,620,3
		//	   Data "war",8,3,0,0,1,20,4,0,0,190,3
		//	   'mîoty
		//	   Data "battle",9,2,0,0,11,26,4,0,0,250,4
		//	   Data "steel",11,5,0,0,11,18,4,0,0,450,4
		//	   Data "granite",13,7,0,0,11,39,4,0,0,730,4

		int i = 1;
#define READBRON(N,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11)\
	BRON_S[i] = GS(N);\
	BRON[i][1] = A1;\
	BRON[i][2] = A2;\
	BRON[i][3] = A3;\
	BRON[i][4] = A4;\
	BRON[i][5] = A5;\
	BRON[i][6] = A6;\
	BRON[i][7] = A7;\
	BRON[i][8] = A8;\
	BRON[i][9] = A9;\
	BRON[i][10] = A10;\
	BRON[i][11] = A11;\
	i++;

		//	   DANE2:
		//	   'nazwa            s p s e t w g d mag,cena,bob
		READBRON("b000"/*"light"*/,5,1,0,0,2,2,4,1,0,100,28);
		READBRON("b001"/*"steel"*/,7,2,0,0,2,6,4,2,0,150,2);
		READBRON("b002"/*"silver"*/,12,3,0,0,2,5,4,5,0,500,2);
		READBRON("b003"/*"long"*/,10,5,0,0,2,9,4,3,0,200,2);
		READBRON("b004"/*"fire"*/,15,5,0,0,2,4,4,9,9,800,20);
		READBRON("b005"/*"Dragon fang"*/,25,8,0,0,2,5,4,9,2,3000,20);
		READBRON("b006"/*"Szczerbiec"*/,50,15,0,0,2,5,4,9,5,10000,20);

		//	   '-topory          s p s e t w g d mag cena
		READBRON("b007"/*"common"*/,6,2,0,0,1,7,4,0,0,120,3);
		READBRON("b008"/*"storm"*/,9,3,0,0,1,15,4,0,0,190,3);
		READBRON("b009"/*"chromic"*/,12,5,0,0,1,15,4,8,0,350,3);
		//	   '10
		READBRON("b010"/*"golden"*/,25,10,0,0,1,12,4,9,0,1100,3);
		//	   '-mîoty            s p s e t  w  g d mag cena
		READBRON("b011"/*"stone"*/,7,2,0,0,11,16,4,0,0,150,4);
		READBRON("b012"/*"heavy"*/,10,3,0,0,11,30,4,1,0,300,4);
		READBRON("b013"/*"diamond"*/,25,5,0,0,11,25,4,2,0,1050,4);
		READBRON("b014"/*"goblins"*/,30,5,0,0,11,20,4,5,0,1500,4);
		//	   '-tarcze          s p s e t w g d mag cena
		READBRON("b015"/*"wooden"*/,0,8,0,0,3,3,4,0,0,50,1);
		READBRON("b016"/*"steel"*/,0,15,0,0,3,8,4,0,0,150,15);
		READBRON("b017"/*"storm"*/,0,19,0,0,3,15,4,0,0,300,15);
		READBRON("b018"/*"gremlin's"*/,0,25,0,0,3,10,4,0,0,900,1);
		//	   '-îuki            s p s e t w g d mag cena
		READBRON("b019"/*"common"*/,10,0,0,0,4,1,4,0,0,80,5);
		//	   '20
		READBRON("b020"/*"special"*/,15,0,0,0,4,2,4,0,0,190,5);
		READBRON("b021"/*"elf"*/,20,0,0,0,4,1,4,0,0,400,5);
		//	   '-heîmy
		READBRON("b022"/*"pointed"*/,0,5,0,0,7,1,1,0,0,100,8);
		READBRON("b023"/*"horned"*/,2,5,0,0,7,2,1,0,0,170,8);
		//	   'buty            s p s e t w g d mag cena
		READBRON("b024"/*"leather"*/,0,0,6,0,8,1,3,0,0,80,9);
		READBRON("b025"/*"shoed"*/,0,2,8,0,8,1,3,0,0,150,9);
		//	   'zbroje            s p s e t w g d mag cena
		READBRON("b026"/*"light"*/,0,10,0,0,6,10,2,0,0,200,7);
		READBRON("b027"/*"coat of mail"*/,0,18,0,0,6,12,2,0,0,400,7);
		READBRON("b028"/*"steel"*/,0,13,0,0,6,20,2,0,0,300,7);
		READBRON("b029"/*"heavy"*/,0,22,0,0,6,30,2,0,0,390,18);
		//	   '30
		READBRON("b030"/*"silver"*/,0,28,0,0,6,15,2,0,0,900,18);
		//	   'zioîa              s p s e t  w g d mag cena
		READBRON("b031"/*"sterydius"*/,0,2,0,2,13,0,1,0,0,300,12);
		READBRON("b032"/*"furialis"*/,2,0,5,2,13,0,1,0,0,500,12);
		READBRON("b033"/*"mole's root"*/,-5,0,0,-40,13,0,1,0,0,5000,12);
		READBRON("b034"/*"castor"*/,0,0,8,-5,13,0,1,0,0,400,12);
		READBRON("b035"/*"spinach"*/,3,0,0,0,13,0,1,0,0,300,12);
		READBRON("b036"/*"bay leaf"*/,0,0,0,30,13,0,1,0,0,200,12);
		READBRON("b037"/*"black grass "*/,0,0,0,0,13,0,1,0,30,400,12);
		//	   'strzaîy          s p s e t w g d mag cena
		READBRON("b038"/*"common"*/,15,0,0,0,5,0,4,0,0,50,6);
		READBRON("b039"/*"poisoned"*/,20,0,0,0,5,0,4,10,0,100,6);
		//	   '40
		READBRON("b040"/*"magic"*/,25,0,0,0,5,0,4,0,20,200,6);
		//	   'czary               s p s e  t w g d mag cena
		READBRON("b041"/*"MagicMissile(5)"*/,25,0,0,0,12,0,4,1,5,200,14);
		READBRON("b042"/*"Fireball (8)"*/,45,0,0,0,12,0,4,1,8,350,14);
		READBRON("b043"/*"ChaosBreath(12)"*/,20,0,0,0,12,0,4,1,12,600,14);
		READBRON("b044"/*"Flames (15)"*/,35,0,0,0,12,0,4,2,15,700,14);
		READBRON("b045"/*"Lighting (20)"*/,55,0,0,0,12,0,4,2,20,900,14);
		READBRON("b046"/*"Mind Probe (3)"*/,0,0,0,0,12,0,4,3,3,120,13);
		READBRON("b047"/*"Curing (5)"*/,0,0,0,10,12,0,4,2,5,200,13);
		READBRON("b048"/*"Healing (20)"*/,0,0,0,100,12,0,4,2,20,900,13);
		READBRON("b049"/*"Brightness(40)"*/,10,0,0,0,12,0,4,5,40,500,13);
		//	   '50
		READBRON("b050"/*"Intuition (15)"*/,0,0,0,0,12,0,4,6,15,450,13);
		READBRON("b051"/*"God's Wrath(50)"*/,70,0,0,0,12,0,4,7,50,2500,14);
		READBRON("b052"/*"Slow down (10)"*/,0,0,-20,0,12,0,4,2,10,350,14);
		//	   'buty           s p s e t w g d mag cena
		READBRON("b053"/*"light"*/,0,0,9,0,8,1,3,0,0,100,9);
		READBRON("b054"/*"fighting"*/,2,5,7,0,8,3,3,0,0,230,9);
		//	   'maczuga             s p s e  t w g d mag cena
		READBRON("b055"/*"ogre bone"*/,7,2,0,0,10,4,4,0,0,50,11);
		READBRON("b056"/*"wooden"*/,4,1,0,0,10,1,4,0,0,20,11);
		READBRON("b057"/*"prickly"*/,9,2,0,0,10,4,4,0,0,80,11);
		READBRON("b058"/*"ruffianly"*/,11,3,0,0,10,3,4,0,0,100,11);
		//	   'katapulty         s p sz e t   w  g d mag cena bb
		READBRON("b059"/*"siege"*/,60,20,0,0,15,150,4,0,0,500,32);
		//	   '60
		READBRON("b060"/*"ruining"*/,40,10,0,0,15,120,4,0,0,450,32);
		READBRON("b061"/*"light"*/,30,6,0,0,15,50,4,0,0,600,32);
		READBRON("b062"/*"ogre"*/,90,15,0,0,15,60,4,0,0,1150,32);
		//	   'gîazy              s p sz e t   w g d mag cena bb
		READBRON("b063"/*"small"*/,10,0,0,0,16,10,4,0,0,2,33);
		READBRON("b064"/*"big"*/,20,0,0,0,16,20,4,0,0,4,33);
		READBRON("b065"/*"medium"*/,15,0,0,0,16,18,4,0,0,4,33);
		READBRON("b066"/*"granite"*/,40,0,0,0,16,20,4,0,0,20,33);
		READBRON("b067"/*"marble"*/,30,0,0,0,16,19,4,0,0,15,33);
		//	   'heîmy            s p s e t w g d mag cena bb
		READBRON("b068"/*"Klingon"*/,2,6,0,0,7,2,1,0,0,600,19);
		READBRON("b069"/*"Magic"*/,2,6,3,0,7,-40,1,0,0,870,8);
		//	   '70
		//	   'mixtury             s p s e  t  w g d mag cena bb
		READBRON("b070"/*"ple ple"*/,0,0,0,20,18,1,1,0,0,150,16);
		READBRON("b071"/*"poison"*/,-10,-10,0,-90,18,1,1,0,0,500,16);
		READBRON("b072"/*"sheep tongue"*/,5,2,0,-5,18,1,1,0,0,300,16);
		READBRON("b073"/*"honey"*/,4,0,0,30,18,1,1,0,0,490,16);
		READBRON("b074"/*"halucinum"*/,0,0,0,0,18,1,1,0,50,450,16);
		READBRON("b075"/*"cure"*/,0,0,0,70,18,1,1,0,0,350,16);
		//	   'ûywnoôê              s p s e  t w g d mag cena bb
		READBRON("b076"/*"hog meat"*/,0,0,0,0,17,2,4,35,0,20,22);
		READBRON("b077"/*"gargoyl meat"*/,0,0,0,0,17,2,4,85,0,50,22);
		READBRON("b078"/*"wolf meat"*/,0,0,0,0,17,2,4,20,0,40,22);
		//	   'kosztownoôci     s p s e  t w g d mag cena bb
		READBRON("b079"/*"gold"*/,0,0,0,0,14,0,4,0,0,2000,21);
		//	   '80
		READBRON("b080"/*"stones"*/,0,0,0,0,14,0,4,0,0,1500,21);
		READBRON("b081"/*"coins"*/,0,0,0,0,14,0,4,0,0,3000,21);
		READBRON("b082"/*"diamonds"*/,0,0,0,0,14,0,4,0,0,5000,21);
		//	   'skóry            s p s e  t w g d mag cena bb
		READBRON("b083"/*"hog"*/,0,5,0,0,19,0,2,0,0,200,24);
		READBRON("b084"/*"gargoyl"*/,0,9,0,0,19,0,2,0,0,1450,24);
		READBRON("b085"/*"wolf"*/,0,8,0,0,19,0,2,0,0,350,24);
		//
		READBRON("b086"/*"miraculous"*/,1,3,20,0,8,2,3,0,0,500,9);
		//	   'ubranie          s p s e t w g d mag cena bb
		//	   'czary2             s p s e t w g d mag cena bb
		READBRON("b087"/*"Conversion(60)"*/,0,0,0,0,12,0,4,8,60,2000,14);
		READBRON("b088"/*"Explosion (25)"*/,40,0,0,0,12,0,4,9,25,998,14);
		//
		READBRON("b089"/*"carrion"*/,0,0,0,0,17,2,4,20,0,20,22);
		//	   '90
		//	   'zbroje2           s  p s e t w g d mag cena
		READBRON("b090"/*"scaled"*/,0,12,0,0,6,7,2,0,0,800,7);
		READBRON("b091"/*"lighting"*/,10,30,0,0,6,12,2,0,0,2300,7);
		READBRON("b092"/*"ogre"*/,0,43,0,0,6,70,2,0,0,1700,18);
		READBRON("b093"/*"Vingren's"*/,12,32,0,0,6,30,2,0,0,2400,18);
		//	   'oszczepy             s p s e t w g d mag cena
		READBRON("b094"/*"whale"*/,17,1,0,0,9,3,4,0,0,300,10);
		READBRON("b095"/*"long"*/,10,1,0,0,9,4,4,0,0,200,10);
		READBRON("b096"/*"Wolf fang"*/,20,2,0,0,9,5,4,0,0,1100,10);
		READBRON("b097"/*"Tusk"*/,30,3,0,0,9,8,4,0,0,1700,10);
		//	   'mixtury 2         s p s e   t  w g d mag cena bb
		READBRON("b098"/*"wine"*/,0,0,0,-10,18,1,1,0,10,70,16);
		READBRON("b099"/*"troll milk"*/,0,1,12,-10,18,1,1,0,0,500,16);
		//	   '100
		READBRON("b100"/*"water"*/,0,0,0,10,18,1,1,0,0,10,16);
		READBRON("b101"/*"motorolum"*/,0,0,18,0,18,1,1,0,0,800,16);
		READBRON("b102"/*"blood"*/,-20,0,-20,-20,18,1,1,0,0,300,16);
		READBRON("b103"/*"umkoum"*/,3,0,0,0,18,1,1,0,0,80,16);
		//	   'pterodon
		READBRON("b104"/*"haunch"*/,0,0,0,0,17,2,4,25,0,20,22);
		READBRON("b105"/*"fur"*/,0,3,0,0,19,0,2,0,0,280,24);
		//	   '-îuki            s p s e t w g d mag cena
		READBRON("b106"/*"Falcon"*/,38,0,0,0,4,1,4,0,0,1180,5);
		//	   'strzaîy              s p s e t w g d mag cena
		READBRON("b107"/*"Falcon talons"*/,35,0,0,0,5,0,4,0,0,1150,6);
		//	   'heîmy            s p s e t w g d mag cena bb
		READBRON("b108"/*"Sorasil's"*/,8,10,5,0,7,0,1,0,0,1220,19);
		//	   'czary3                  s p s e  t w g  d mag cena bb
		READBRON("b109"/*"Unsure (12)"*/,20,0,0,0,12,0,4,10,12,200,14);
		//	   '110
		READBRON("b110"/*"Intimidate(20)"*/,50,0,0,0,12,0,4,10,12,600,14);
		//	   'dodatkowy stuff
		//	   'miecze            s p s e t w g d mag cena
		READBRON("b111"/*"Barbarian"*/,8,3,0,0,2,7,4,1,0,120,2);
		READBRON("b112"/*"Hornet"*/,14,1,1,0,2,8,4,1,0,700,2);
		READBRON("b113"/*"Chaos"*/,13,1,-2,0,2,9,4,1,0,650,28);
		//	   'topory
		READBRON("b114"/*"orks"*/,10,7,0,0,1,37,4,0,0,120,3);
		READBRON("b115"/*"silver"*/,14,5,0,0,1,27,4,0,0,620,3);
		READBRON("b116"/*"war"*/,8,3,0,0,1,20,4,0,0,190,3);
		//	   'mîoty
		READBRON("b117"/*"battle"*/,9,2,0,0,11,26,4,0,0,250,4);
		READBRON("b118"/*"steel"*/,11,5,0,0,11,18,4,0,0,450,4);
		READBRON("b119"/*"granite"*/,13,7,0,0,11,39,4,0,0,730,4);

		//	End Proc
}
void WCZYTAJ_RASY(void) {
		//	Procedure WCZYTAJ_RASY
		//	   For I=0 To 19
		//	      Read A$
		//	      RASY$(I)=A$
		//	      For J=0 To 7
		//	         Read A : RASY(I,J)=A
		//	      Next J
		//	   Next I

		int i = 0;
#define READ(N,A0,A1,A2,A3,A4,A5,A6,A7)\
	RASY_S[i] = GS(N);\
	RASY[i][0] = A0;\
	RASY[i][1] = A1;\
	RASY[i][2] = A2;\
	RASY[i][3] = A3;\
	RASY[i][4] = A4;\
	RASY[i][5] = A5;\
	RASY[i][6] = A6;\
	RASY[i][7] = A7;\
	i++;

			//	   DANE:
			//	   '                e  s sz m b1 b2 int bob
			//	   Data "barbarian",30,25,25,20,2,0,10,18+63+48
			//	   Data "orc",45,30,15,10,1,0,5,18+63+32
			//	   Data "elf",10,10,50,35,4,0,12,18+63+112+16
			//	   Data "dwarf",20,50,15,15,11,0,8,18+63+16
			//	   Data "amazon",20,20,40,20,9,0,7,18+63+96
			//	   Data "ogre",65,25,8,2,15,0,3,18+63+64
			//	   Data "troll",40,10,40,10,10,0,5,18+63
			//	   Data "knight",20,20,20,40,2,0,13,18+63+80
			//	   Data "sorcerer",10,10,10,70,0,0,13,18+63+112+32
			//	   Data "villager",10,10,10,10,0,0,3,18+63+112
			//	   'potworki       e  s  sz p1 p2 od czar bob
			//	   Data "gargoyl",100,80,25,78,85,50,0,18+63+128+32
			//	   Data "skeletor",60,70,30,0,0,45,44,18+63+128+32
			//	   Data "wolf    ",20,35,40,79,86,20,0,18+63+128+32
			//	   Data "hog     ",20,30,20,77,84,30,0,18+63+128+32
			//	   Data "gloom   ",30,15,20,0,0,80,0,18+63+128+32
			//	   Data "varpoon ",45,40,20,105,106,30,0,18+63+128+32
			//	   Data "skeerial",100,85,15,90,102,70,43,18+63+128+32
			//	   Data "humanoid",40,40,30,0,0,35,42,18+63+128+32
			//	   Data "spider  ",1,170,40,0,0,2,42,18+63+128+32
			//	   Data "boss",200,190,40,0,0,90,46,241
			//	   'smok,jaszczur,golem,upiór,kronk

	READ("RA00",30,25,25,20,2,0,10,18+63+48);
	READ("RA01",45,30,15,10,1,0,5,18+63+32);
	READ("RA02",10,10,50,35,4,0,12,18+63+112+16);
	READ("RA03",20,50,15,15,11,0,8,18+63+16);
	READ("RA04",20,20,40,20,9,0,7,18+63+96);
	READ("RA05",65,25,8,2,15,0,3,18+63+64);
	READ("RA06",40,10,40,10,10,0,5,18+63);
	READ("RA07",20,20,20,40,2,0,13,18+63+80);
	READ("RA08",10,10,10,70,0,0,13,18+63+112+32);
	READ("RA09",10,10,10,10,0,0,3,18+63+112);
	//	   'potworki       e  s  sz p1 p2 od czar bob
	READ("RA10",100,80,25,78,85,50,0,18+63+128+32);
	READ("RA11",60,70,30,0,0,45,44,18+63+128+32);
	READ("RA12",20,35,40,79,86,20,0,18+63+128+32);
	READ("RA13",20,30,20,77,84,30,0,18+63+128+32);
	READ("RA14",30,15,20,0,0,80,0,18+63+128+32);
	READ("RA15",45,40,20,105,106,30,0,18+63+128+32);
	READ("RA16",100,85,15,90,102,70,43,18+63+128+32);
	READ("RA17",40,40,30,0,0,35,42,18+63+128+32);
	READ("RA18",1,170,40,0,0,2,42,18+63+128+32);
	READ("RA19",200,190,40,0,0,90,46,241);

	//	   Restore ZNAKI : For I=1 To 24 : Read ZNAKI$(I) : Next I
	//
	//	   ZNAKI:
	//	   Data "a","b","c","d","e","f","g","h","i","j"
	//	   Data "k","l","m","n","o","p","r","s","t","u"
	//	   Data "w","û","ô","z"
	//
	const char* znaki[] = {
		"a","b","c","d","e","f","g","h","i","j",
		"k","l","m","n","o","p","r","s","t","u",
		"w","û","ô","z"
	};
	for(i=1;i<24;++i)
		ZNAKI_S[i]=znaki[i-1];

	//	End Proc
}
void WCZYTAJ_BUDYNKI(void) {
		//	Procedure WCZYTAJ_BUDYNKI
		//	   For I=1 To 9
		//	      Read A$
		//	      BUDYNKI$(I)=A$
		//	      For J=0 To 6
		//	         Read A
		//	         BUDYNKI(I,J)=A
		//	      Next J
		//	   Next I
		int i = 1;
#undef READ
#define READ(N,A0,A1,A2,A3,A4,A5,A6)\
	BUDYNKI_S[i] = GS(N);\
	BUDYNKI[i][0] = A0;\
	BUDYNKI[i][1] = A1;\
	BUDYNKI[i][2] = A2;\
	BUDYNKI[i][3] = A3;\
	BUDYNKI[i][4] = A4;\
	BUDYNKI[i][5] = A5;\
	BUDYNKI[i][6] = A6;\
	i++;


		//	   DANE:
		//	   '               szer wys cena czas b1 b2 drzwi
		//	   Data "?studnia   ",64,50,0,0,3,0,0
		//	   Data "szubienica",32,56,0,0,7,0,0
		//	   Data "beczka ",20,28,0,0,9,0,0
		//	   Data "shop ",112,80,7000,7,5,6,42
		//	   Data "armoury",112,100,10000,7,8,6,42
		//	   Data "temple ",104,103,9000,7,6,6,40
		//	   Data "hunter ",64,130,8000,7,2,6,20
		//	   Data "alchemist ",96,90,6000,7,4,6,40
		//	   Data "granary ",96,100,4000,7,1,6,30
		//	   Data "karczma"

	READ("BD00",64,50,0,0,3,0,0);
	READ("BD01",32,56,0,0,7,0,0);
	READ("BD02",20,28,0,0,9,0,0);
	READ("BD03",112,80,7000,7,5,6,42);
	READ("BD04",112,100,10000,7,8,6,42);
	READ("BD05",104,103,9000,7,6,6,40);
	READ("BD06",64,130,8000,7,2,6,20);
	READ("BD07",96,90,6000,7,4,6,40);
	READ("BD08",96,100,4000,7,1,6,30);


		//	   Restore LITERKI : For I=0 To 99 : Read LITERY#(I) : Next I
		//	   LITERKI:
		//	   Data -312.245,802.09,719.168,-943.121,181.207
		//	   Data 821.02,-366.233,897.157,350.117,429.129
		//	   Data 755.194,714.244,-280.242,283.178,433.212
		//	   Data 10.193,567.245,685.069,-145.175,-194.127
		//	   Data -380.053,-729.161,319.181,11.223,627.037
		//	   Data -402.159,-71.089,378.042,613.113,975.081
		//	   Data -389.089,860.027,286.05,868.137,554.031
		//	   Data 605.028,471.224,591.202,828.094,571.112
		//	   Data 157.231,46.092,-102.244,143.018,267.212
		//	   Data 152.175,2.104,-809.183,689.053,-120.126
		//	   Data -220.078,651.1,788.071,75.054,-53.014
		//	   Data -389.213,149.08,-728.081,70.034,258.15
		//	   Data 645.126,-762.111,-145.088,-852.124,217.225
		//	   Data -457.145,-519.135,653.125,628.19,866.021
		//	   Data 10.208,-965.074,-149.24,-700.078,-146.137
		//	   Data -751.191,682.029,409.169,-955.196,937.168
		//	   Data 58.184,-721.114,-31.147,-711.202,-941.24
		//	   Data -419.038,-493.025,668.179,-678.19,87.209
		//	   Data -550.071,534.148,449.043,472.111,547.089
		//	   Data 200.168,837.095,801.124,-58.026,473.21
	float literki[] = {
		-312.245,802.09,719.168,-943.121,181.207,
		821.02,-366.233,897.157,350.117,429.129,
		755.194,714.244,-280.242,283.178,433.212,
		10.193,567.245,685.069,-145.175,-194.127,
		-380.053,-729.161,319.181,11.223,627.037,
		-402.159,-71.089,378.042,613.113,975.081,
		-389.089,860.027,286.05,868.137,554.031,
		605.028,471.224,591.202,828.094,571.112,
		157.231,46.092,-102.244,143.018,267.212,
		152.175,2.104,-809.183,689.053,-120.126,
		-220.078,651.1,788.071,75.054,-53.014,
		-389.213,149.08,-728.081,70.034,258.15,
		645.126,-762.111,-145.088,-852.124,217.225,
		-457.145,-519.135,653.125,628.19,866.021,
		10.208,-965.074,-149.24,-700.078,-146.137,
		-751.191,682.029,409.169,-955.196,937.168,
		58.184,-721.114,-31.147,-711.202,-941.24,
		-419.038,-493.025,668.179,-678.19,87.209,
		-550.071,534.148,449.043,472.111,547.089,
		200.168,837.095,801.124,-58.026,473.21
	};
	for(i=0;i<=99;++i) {
		LITERY_F[i] = literki[i];
	}
	//
	//	End Proc
}
void WCZYTAJ_GULE(void) {
		//	Procedure WCZYTAJ_GULE
		//	   Restore DANE : For I=0 To 9 : Read A$ : GUL$(I)=A$ : Next I
		//	   DANE:
		//	   Data "rebelious"
		//	   Data "discontented"
		//	   Data "serf"
		//	   Data "loyal"
		//	   Data "fanatics"
		//	   Data "quiet"
		//	   Data "panic"
		//	   Data "defence"
		//	   Data "attack"
		//	   Data "psycho"
	int i=0;
#undef READ
#define READ(N)\
	GUL_S[i] = GS(N);\
	i++;
	READ("GU00");
	READ("GU01");
	READ("GU02");
	READ("GU03");
	READ("GU04");
	READ("GU05");
	READ("GU06");
	READ("GU07");
	READ("GU08");
	READ("GU09");



		//	   Restore STRONY : For I=0 To 125 : Read BOARD#(I) : Next I
		//	   STRONY:
		//	   Data -2.2251,-1.4863,-2.2865,-11.8208,2.3177
		//	   Data -2.8355,-1.8101,1.4151,3.0033,1.7852
		//	   Data 2.2563,3.0247,-8.4822,8.5085,-3.0459
		//	   Data 2.2948,-3.2609,-3.3391,-6.6071,-6.6851
		//	   Data 3.3713,-4.1044,-9.9679,10.0332,-3.2468
		//	   Data -4.1504,8.8136,-4.6185,-4.6779,5.2065
		//	   Data -5.6179,5.8254,-3.7766,-13.5236,-4.002
		//	   Data -5.8478,-5.9079,-6.0427,-6.2149,6.3284
		//	   Data -4.8143,-5.0654,-6.4222,-5.279,-5.3028
		//	   Data -6.5474,6.9696,7.0178,5.9298,6.0124
		//	   Data -7.0576,-7.5099,8.1425,8.3151,1.9012
		//	   Data -1.3469,-8.6186,7.0613,7.2355,9.0904
		//	   Data 11.257,7.7684,-8.0184,-11.4007,1.6727
		//	   Data -15.3125,-15.5,-10.6025,2.5389,2.6293
		//	   Data -10.6145,-10.9058,10.9473,11.0013,-11.1058
		//	   Data 11.5005,-9.1053,9.5282,-11.8316,11.908
		//	   Data -12.0151,-12.3473,-12.4031,13.2693,-13.3028
		//	   Data 13.6042,-14.0127,12.4537,12.5795,13.0138
		//	   Data -1.2381,-1.2558,13.1465,-13.2058,-14.1269
		//	   Data 14.3254,-1.5305,10.0574,14.6109,3.7264
		//	   Data 11.6689,-15.308,1.2106,-12.9105,-11.2366
		//	   Data 1.3946,11.678,-7.2272,-2.0941,1.6439
		//	   Data 14.6539,15.0115,-1.4262,2.9008,-11.6478
		//	   Data 7.3171,-1.4964,-7.4045,12.6318,8.4086
		//	   Data -8.4454,12.8209,-14.3441,-12.9514,-1.6517
		//	   Data -15.8021
	float strony[] = {
		-2.2251,-1.4863,-2.2865,-11.8208,2.3177,
		-2.8355,-1.8101,1.4151,3.0033,1.7852,
		2.2563,3.0247,-8.4822,8.5085,-3.0459,
		2.2948,-3.2609,-3.3391,-6.6071,-6.6851,
		3.3713,-4.1044,-9.9679,10.0332,-3.2468,
		-4.1504,8.8136,-4.6185,-4.6779,5.2065,
		-5.6179,5.8254,-3.7766,-13.5236,-4.002,
		-5.8478,-5.9079,-6.0427,-6.2149,6.3284,
		-4.8143,-5.0654,-6.4222,-5.279,-5.3028,
		-6.5474,6.9696,7.0178,5.9298,6.0124,
		-7.0576,-7.5099,8.1425,8.3151,1.9012,
		-1.3469,-8.6186,7.0613,7.2355,9.0904,
		11.257,7.7684,-8.0184,-11.4007,1.6727,
		-15.3125,-15.5,-10.6025,2.5389,2.6293,
		-10.6145,-10.9058,10.9473,11.0013,-11.1058,
		11.5005,-9.1053,9.5282,-11.8316,11.908,
		-12.0151,-12.3473,-12.4031,13.2693,-13.3028,
		13.6042,-14.0127,12.4537,12.5795,13.0138,
		-1.2381,-1.2558,13.1465,-13.2058,-14.1269,
		14.3254,-1.5305,10.0574,14.6109,3.7264,
		11.6689,-15.308,1.2106,-12.9105,-11.2366,
		1.3946,11.678,-7.2272,-2.0941,1.6439,
		14.6539,15.0115,-1.4262,2.9008,-11.6478,
		7.3171,-1.4964,-7.4045,12.6318,8.4086,
		-8.4454,12.8209,-14.3441,-12.9514,-1.6517,
		-15.8021
	};
	for(i=0;i<=125;++i)
		BOARD_F[i] = strony[i];
	//	End Proc
}
void WCZYTAJ_ROZMOWE(void) {
		//	Procedure WCZYTAJ_ROZMOWE
		//	   For I=0 To 33
		//	      Read A$ : ROZMOWA2$(I)=A$
		//	   Next I
		//	   For I=1 To 2
		//	      For J=0 To 4
		//	         Read A$
		//	         ROZMOWA$(I,J)=A$
		//	      Next J
		//	   Next I
		//	   DANE:
		//	   'atak
		//	   Data "Fight like a warrior !"
		//	   Data "My blade will answer you."
		//	   Data "Do they pay you more for abusing ?"
		//	   'defence
		//	   Data "I wonder how much I will get for your scalp ?"
		//	   Data "There is no good news for you."
		//	   Data "You stink of carrion man."
		//	   'PANIC
		//	   Data "I clubbed many curious."
		//	   Data "Don't be interested."
		//	   Data "Die you monster !"
		//	   'peace
		//	   Data "Everything as before."
		//	   Data "Nothing interesting."
		//	   Data "Nothing."
		//	   Data "Villagers are good decoy for animals."
		//	   Data "You'd better not go to swaps. Deuced beasts live there."
		//	   Data "A Shopkeeper will pay any price for mole's root. You can find it only in the swaps."
		//	   Data "You can find stones to catapults in the mountains."
		//	   Data "Caves are worth penetrating. Gold lies about everywhere."
		//	   Data "Avoid Chaos warriors. I saw them slaughtering selective squads."
		//	   Data "Mind your steps in the forest. You can find valuable herbs."
		//	   Data "Gargoyl's fell is worth fortune."
		//	   Data "Watch gargoyls. This little beast can cut a man with one snap of its teeth."
		//	   Data "A bottle of healing mixture can save your life during the a battle."
		//	   Data "Nothing heals wounds as well as bay leaves."
		//	   Data "Don't go to glociers without shoes or clothes."
		//	   Data "Elves are the best archers."
		//	   Data "Don't eat too much herbs. Their power is delusive."
		//	   Data "Many daredevils didn't come back from swamps."
		//	   Data "Castor-herbs are a bit poisonous but they add to speed."
		//	   Data "I recommend mole's root."
		//	   Data "Hog's meat is nutritious."
		//	   Data "It's getting worse, taxes go up, groups of skeletors ravage the area, infuriated wolves approach the houses and attack our herds."
		//	   Data "Great spiders can throw down with one bite even an ogre."
		//	   Data "You haven't seen much if you haven't seen skirial."
		//	   Data "It's useful to have about three villagers in the squad to find a way through swaps."
		//	   'join us !
		//	   Data "Never !"
		//	   Data "No way !"
		//	   Data "I don't speak to greenhorns."
		//	   Data "I'll do that but you have to pay me."
		//	   Data "It's a great honour to serve under your command, my Lord."
		//	   'gime ya monay meeeeen ?!
		//	   Data "You will die slowly."
		//	   Data "What about a crack on the sconce ?"
		//	   Data "And what else ?"
		//	   Data "I've got no gold."
		//	   Data "That's all I have Sir."
		//

		aint r=0;
		for(aint I=0; I<=33; ++I ) {
		  ROZMOWA2_S[I]=GS("R"+toString(r,"%3.3d"));
		  r++;
		}
		for(aint I=1; I<=2; ++I ) {
		  for(aint J=0; J<=4; ++J ) {
		     ROZMOWA_S[I][J]=GS("R"+toString(r,"%3.3d"));
		     r++;
			}
		}

		//	End Proc
}
void WCZYTAJ_PRZYGODY(void) {
		//	Procedure WCZYTAJ_PRZYGODY
		//	   For I=1 To 13
		//	      For J=0 To 8
		//	         Read A$ : PRZYGODY$(I,J)=A$
		//	      Next J
		//	   Next I
		//	   For I=0 To 3
		//	      PRZYGODY(I,P_TYP)=0
		//	   Next I
		//	   DANE:
		//
		//	   '1---------------------
		//	   Data "The Old Gold Mine"
		//	   Data "I've heard about very old gold mine from a wanderer. He said that kobolds guard big treasures there."
		//	   Data "I'm looking for the old mine."
		//	   Data "I'm sorry, I don't know its position."
		//	   Data "I suppose there was an old mine @."
		//	   Data "Ask in the # town."
		//	   Data "I will indicate it to you on the map."
		//	   Data "We have reached the old mine."
		//	   Data "Go away and leave us and our treasures."
		//	   '2--------------------
		//	   Data "The Tomb of the great warrior $."
		//	   Data "A long time ago a great warrior called $ was killed in the battle of *. His wonderful % is burried together with him."
		//	   Data "I'm looking for $'s grave."
		//	   Data "I can't help you."
		//	   Data "The old warriors say that he fell somewhere @."
		//	   Data "Lord, prey his soul. They should know sometihng in #."
		//	   Data "His grave is not far from here."
		//	   Data "We have found $'s grave."
		//	   Data "   betide him who disturbs his sleep."
		//	   '3------------------
		//	   Data "Bandit's camp."
		//	   Data "My lord. Three days ago a horde of plunderers attacked us. We will be very greatful for catching them."
		//	   Data "I'm looking for bandits."
		//	   Data "I don't know where they are now."
		//	   Data "I hear they did great mess somewhere @."
		//	   Data "They where seen near #. You be careful. They are not little rogues from a forest. This is a choice crew."
		//	   Data "I will show you their camp. But don't tell anybody that I betrayed them."
		//	   Data "We have surrounded the rascal band."
		//	   Data "He ! There were stronger fellows than you whom I torn to rags with my blade."
		//	   '4-----------------
		//	   Data "Here stays the king's daughter."
		//	   Data "We've heard that a few days ago a squad of choice warriors kidnapped a daughter of the king $. The king promised a town & for freeing her. Time presses !"
		//	   Data "I'm looking for the princess."
		//	   Data "I can't help you."
		//	   Data "She was seen on @."
		//	   Data "I hear that people in the # town saw the band which kidnapped her."
		//	   Data "I know where she is now."
		//	   Data "We've found the king's daughter."
		//	   Data "I'm the king's daughter. Thank you Brave Warrior, Your name will never be forgotten. Let me come back to my father."
		//	   '5-----------------
		//	   Data "Mountain $ "
		//	   Data "As the legend says on the top of the mountain $, the most powerful of all swords, Szczerbiec was hidden."
		//	   Data "Where is the mountain $."
		//	   Data "I don't know where it may be."
		//	   Data "The mountain you're asking about is somewhere @."
		//	   Data "The miners from # have to know something about it."
		//	   Data "I will show it to you on the map."
		//	   Data "We start searching of the Sword."
		//	   Data ""
		//	   '6----------------
		//	   Data "Imprisoned Sorcerer."
		//	   Data "Not a long time ago a great magic master, old $ was kidnapped from our village. If you free him from kidnappers' hands he will join your squad."
		//	   Data "I'm looking for the Sorcerer."
		//	   Data "I don't know where he is."
		//	   Data "Ask on @."
		//	   Data "$ is one of the most powerful sorcerers of the known world. I hear he was seen in the #."
		//	   Data "Poor old man. He must have lost his mind. He lives in the pack of wolves not far from here."
		//	   Data "We've found the sorcerer $."
		//	   Data "I am $, the last one of the powerful sorcerers. The king of chaos sent on me his servants changed into wolves."
		//	   '7---------------
		//	   Data "The cave of $."
		//	   Data "400 year ago in the wholy battle against powers of chaos many brave warriors lost their lives. One of those who survived was paladin $. The legend says that he is alive until today."
		//	   Data "I'm looking for $."
		//	   Data "I don't know where he is."
		//	   Data "I've heard about him. The old books say that demons imprisoned him in the underground cave somewhere @."
		//	   Data "The people who remember the oldest legends live in #."
		//	   Data "I don't know if I can trust you, but I will show you the entrance to the cave. But be careful. Nobody alive come back from there."
		//	   Data "We are entering the $'s cave."
		//	   Data "I am $, a remaining one from the great battle. Imprisoned for ages I'm looking for the revenge on the Chaos."
		//	   '8------------
		//	   Data "The old Tomb."
		//	   Data "All the Sorcerers claim that scrolls with sorceries are rewritten from one generation to another. But there exists the ancient source of these sorceries: The First Book."
		//	   Data "I'm looking for First Book ?"
		//	   Data "It's only an old legend."
		//	   Data "I have read in the old notes that it was burnt many centuries ago together with the whole library and the town * wich must have been somewhere @."
		//	   Data "The settlement # was built on the ruins of much more older, burnt town. As they say only few pages were saved from the whole collection."
		//	   Data "There is an old tomb not far from here. A haunted witch was raving that the Book was there. I think that there is only a herd of stinky humanoids."
		//	   Data "We've reached the old tomb."
		//	   Data "Only one page survived from the whole library."
		//	   '9--------------
		//	   Data "Ork's temple"
		//	   Data "I hear that some of the tribes of orks have stood on the dark side. They have a hidden temple where they bring robbed treasures."
		//	   Data "Where is the Ork's temple ?"
		//	   Data "I'm sorry, I don't know."
		//	   Data "Ask on @. The ork's troops were seen there. Be careful, they are no mean ruffians."
		//	   Data "I've heard about it. They say that orks bring there robbed treasures from the whole kingdom. Frightened inhabitants from # told me about it."
		//	   Data "Don't go there. It's a cursed place. Orks kill anyone who approaches the temple. They sacrifice them to the powers of darkness."
		//	   Data "We are entering the temple. It's the high time to stop their madness."
		//	   Data "You will join me to hell !"
		//	   '10----------
		//	   Data "$ the Barbarian."
		//	   Data "A great warrior $ lived in our village. He wield the sword as nobody else. When he went to the war more than a year ago there was no news of him."
		//	   Data "I'm looking for $."
		//	   Data "Search until you find."
		//	   Data "He was a brave barbarian. I don't believe anybody could beat him in an honest fight. I remember that he went to @ from our village."
		//	   Data "A tradesman from # told me that the powers of darkness imprisoned him on the spell-bound swaps wich make people mad."
		//	   Data "I hear he wanders about the swamps. I will show you on the map where they are."
		//	   Data "We are entering the swamps."
		//	   Data "There is no way out from this damned swaps !"
		//	   '11----------
		//	   Data "$'s band."
		//	   Data "A grim group appeared in the area. A psychodelic ¹ called $ is their leader. There is a reward for his head."
		//	   Data "I'm looking for $'s band."
		//	   Data "I would like to help you, but I don't know where it is."
		//	   Data "I hear he has trained gargoils at his service and great warriors. He fights very well although he lost his mind. He broke a chaser-squad on @."
		//	   Data "Let his name be cursed for ever. He killed many inhabitants from #."
		//	   Data "Chaos warps his servants' minds and $ is one of them. Avenge our wrongs."
		//	   Data "We've found $'s band."
		//	   Data "He hehe he"
		//	   '12-----------
		//	   Data "Knowledge Cave."
		//	   Data "I've heard a legend about magic cave. The one who enters it will obtain great wisdom. Its position has allways been a great secret."
		//	   Data "I'm looking for Magic Cave ?"
		//	   Data "I know that it exists but nothing more."
		//	   Data "Our young warriors used to go there befor the great war to get knowledge and experience in fight. I remeber that they always went to @."
		//	   Data "The wise man from # used to say that the cave is the oldest place in the known world."
		//	   Data "I heard about your heroic deeds and I belive that you use the knowledge from the cave in the right case."
		//	   Data "We've reached the Knowledge Cave."
		//	   Data "From now your experience is your greatest power. Use it against evil."
		//	   '13-----------
		//	   Data "The fortress of the ruler of Chaos is hidden here."
		//	   Data "Chaos grows in power. More and more skeletors crawl out from the ground every day. They attack all the living creatures and spread incurable diseases."
		//	   Data "How to defeat Chaos Knights ?"
		//	   Data "You cannot kill them because they are already dead. Two new legions will come in the place of defeated one."
		//	   Data "There is no sense fighting them. The source of the ill power has to be destroyed. Maybe they will know something on @."
		//	   Data "They can be destroyed. Four centuries ago, after a great battle their ruler was defeated. In # town lives an old wise man who rembers those times."
		//	   Data "Their ruler lives in a big fortress hidden among fogs. Great power is at his disposal. Only the most brave warriors armed in the wholy weapon will defeat him."
		//	   Data "We are standing at the gates of the fortress. Let the destination come true."
		//	   Data ""

		aint p=0;
		for(aint I=1; I<=13; ++I ) {
		  for(aint J=0; J<=8; ++J ) {
		  	PRZYGODY_S[I][J]=GS("P"+toString(p,"%3.3d"));
		  	p++;
			}
		}
		for(aint I=0; I<=3; ++I ) {
		  PRZYGODY[I][P_TYP]=0;
		}

		//	End Proc
}


