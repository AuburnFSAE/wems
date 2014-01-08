#include "wems_rpm_alloc.h"
#include <malloc.h>
#include <Arduino.h>
#ifdef WEMS_RPM_ALLOC_H

wems_rpm_block wems_rpm_create(si16* rpm_pins, si16 pin_count){
	wems_rpm_block block;
	block.pins = rpm_pins;

	block.pin_count=pin_count;
	block.min_rpm=6000;
	block.max_rpm=13000;

	block.rpm_range = block.max_rpm - block.min_rpm;

	for( si16 i = 0; i < block.pin_count; pinMode(rpm_pins[i++], OUTPUT));
return block;}


wems_rpm_block wems_rpm_minmax_create(si16* rpm_pins, si16 pin_count, si16 min_rpm, si16 max_rpm){
	wems_rpm_block block;
	block.pins = rpm_pins;

	block.pin_count=pin_count;
	block.min_rpm=min_rpm;
	block.max_rpm=max_rpm;

	block.rpm_range = block.max_rpm - block.min_rpm;
	for( si16 i = 0; i < block.pin_count; pinMode(rpm_pins[i++], OUTPUT));	
return block;}

void wems_rpm_set_ligths479(const wems_rpm_block* rpm_blk, si16 rpm_val, ui8 direction){

// 	 struct wems_rpm_block{
// 	si16* pins;
// 	si16 pin_count;
// 	si16 min_rpm;
// 	si16 max_rpm;
// 	si16 rpm_range;
// };	
	si16* leds = rpm_blk->pins;

	si16 _x_ = ((si32)rpm_blk->pin_count * (rpm_val - rpm_blk->min_rpm))/rpm_blk->rpm_range;
	sflt eq_p = (rpm_blk->pin_count/8.999);

	if( direction ){
		  si16 n=0;
		 if( _x_ > (n=4*eq_p) ){
		    for( si16 i=0; i<n; digitalWrite(leds[i++], HIGH) ); 
		}if( _x_ > (n=7*eq_p, n) ){
		    for( si16 i=4*eq_p; i < n; digitalWrite(leds[i++], HIGH) );

		}if( _x_ == (n=9*eq_p)){
		    for( si16 i=7*eq_p; i < n; digitalWrite(leds[i++], HIGH) );
		}
	}else{

	  if( _x_ < 8*eq_p )
	    for( si16 i=rpm_blk->pin_count-1; i > 6*eq_p; digitalWrite(leds[i--], LOW) );

	  if( _x_ < 5*eq_p)
	    for( si16 i=6*eq_p; i > 3*eq_p; digitalWrite(leds[i--], LOW) );

	  if( _x_ < 1*eq_p )
	    for( si16 i=3*eq_p; i>-1; digitalWrite(leds[i--], LOW) );
	}
return;}
#endif
