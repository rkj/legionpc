
#include "Amos.h"

#include "legion.h"
#include "lgn_ekran1.h"
#include "lgn_util.h"

void *ekran1_buffer=0;
void _store_ekran1(void) {
	int scr=Screen();
	Screen(1);
	if( 0 == ekran1_buffer ) ekran1_buffer = ReserveBuffer(0,0,320,160);
	if( 0 != ekran1_buffer ) StoreBuffer(ekran1_buffer,0,0,320,24);
	Screen(scr);
}
void _store_ekran1_sklep(void) {
	int scr=Screen();
	Screen(1);
	if( 0 == ekran1_buffer ) ekran1_buffer = ReserveBuffer(0,0,320,160);
	if( 0 != ekran1_buffer ) StoreBuffer(ekran1_buffer,0,0,320,44);
	Screen(scr);
}
void _store_ekran1_wybor(void) {
	int scr=Screen();
	Screen(1);
	if( 0 == ekran1_buffer ) ekran1_buffer = ReserveBuffer(0,0,320,160);
	if( 0 != ekran1_buffer ) StoreBuffer(ekran1_buffer,0,0,320,138);
	Screen(scr);
}
void _store_ekran1_gadka(void) {
	int scr=Screen();
	Screen(1);
	if( 0 == ekran1_buffer ) ekran1_buffer = ReserveBuffer(0,0,320,160);
	if( 0 != ekran1_buffer ) StoreBuffer(ekran1_buffer,0,0,320,150);
	Screen(scr);
}
void _store_ekran1_rozbudowa(void) {
	int scr=Screen();
	Screen(1);
	if( 0 == ekran1_buffer ) ekran1_buffer = ReserveBuffer(0,0,320,160);
	if( 0 != ekran1_buffer ) StoreBuffer(ekran1_buffer,0,0,320,35);
	Screen(scr);
}
void _restore_ekran1(void) {
	if( 0 != ekran1_buffer ) {
		int scr=Screen();
		Screen(1);
		RestoreBuffer(ekran1_buffer);
		Screen(scr);
	}
}
void EKRAN1(void) {
	//	Procedure EKRAN1
	Screen(1);																//	   Screen 1
	Gfx::Cls(0,0,0);													//	   Cls 0 : Paste Bob 0,0,1
	PasteBob(0,0,1);
  GADGET(200,2,20,20,"bob3",2,0,19,5,1);		//	   GADGET[200,2,20,20,"bob3",2,0,19,5,1]
  GADGET(222,2,20,20,"bob4",2,0,19,5,2);		//	   GADGET[222,2,20,20,"bob4",2,0,19,5,2]
  GADGET(244,2,20,20,"bob5",2,0,19,5,3);		//	   GADGET[244,2,20,20,"bob5",2,0,19,5,3]
  GADGET(266,2,20,20,"bob6",2,0,19,5,4);		//	   GADGET[266,2,20,20,"bob6",2,0,19,5,4]
  GADGET(297,2,20,20,"bob7",2,0,19,5,10);		//	   GADGET[297,2,20,20,"bob7",2,0,19,5,10]
  GADGET(170,2,20,20,"bob2",2,0,19,5,5);		//	   GADGET[170,2,20,20,"bob2",2,0,19,5,5]
  GADGET(147,2,20,20,"bob8",2,0,19,5,9);		//	   GADGET[147,2,20,20,"bob8",2,0,19,5,9]
  GADGET(2,2,140,20,"",0,1,19,16,0);				//	   GADGET[2,2,140,20,"",0,1,19,16,0]

	_store_ekran1();
	//	End Proc
}

