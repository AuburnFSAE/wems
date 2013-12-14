#include "wems_rpm_alloc.h"
#include <malloc.h>
#ifdef WEMS_RPM_ALLOC_H

wems_rpm_block wems_rpm_create(si16* rpm_pins, si16 pin_count){
	wems_rpm_block block;
	block.pins = rpm_pins;

	block.pin_count=pin_count;
	block.min_rpm=6000;
	block.max_rpm=13000;

	block.rpm_range = block.max_rpm - block.min_rpm;	
return block;}


wems_rpm_block wems_rpm_minmax_create(si16* rpm_pins, si16 pin_count, si16 min_rpm, si16 max_rpm){
	wems_rpm_block block;
	block.pins = rpm_pins;

	block.pin_count=pin_count;
	block.min_rpm=min_rpm;
	block.max_rpm=max_rpm;

	block.rpm_range = block.max_rpm - block.min_rpm;	
return block;}


#endif
