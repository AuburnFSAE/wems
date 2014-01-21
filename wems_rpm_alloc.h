#include <Arduino.h>
#include <stdlib.h>
#include "wems_typedef.h"

#ifndef WEMS_RPM_ALLOC_H
#define WEMS_RPM_ALLOC_H

/** wems_rpm_alloc defines the rpm block and shiftlights api.
This part of the api encapsulates a sets of pins that are used to
control led lights through the wems_rpm_block data type.
*/


/** @struct wems_rpm_block
 *  @brief This structure encapsulates rpm lights that are defined by the pins member
 *  @var wems_rpm_block::active_level 
 *  	Member 'active_level' defines whether the pins should be activated high or low.
 *  	For Arduino source it should be set by wems_rpm_block.active_level = HIGH
 *  	By default wems_rpm_block are create to be active HIGH
 */
struct wems_rpm_block{
	si16* pins;
	si16 count;
	si16 min_rpm;
	si16 max_rpm;
	si16 rpm_range;
	si16 active_level;
	si16 shift_pin;
	si16 shift_rpm;
	si16 shift_level;
};

#define LEVELFLIP(x) x==HIGH ? LOW : HIGH

void wems_rpm_alloc( wems_rpm_block* blk, si16* rpm_pins, si16 n_count);

void wems_rpm_minmax_alloc(	wems_rpm_block* blk,
										si16* rpm_pins,
										si16 num_pins,
										si16 min,
										si16 max);

void wems_rpm_set_shiftpoint(wems_rpm_block* blk, si16 shift_rpm, ui8 shift_pin);

void wems_rpm_set_ligths479(const wems_rpm_block* blk, si16 rpm_val, ui8 direction);

void wems_rpm_toggle_shift2(const wems_rpm_block* blk, si16 rpm_val, si16 ms_delay );

#endif

