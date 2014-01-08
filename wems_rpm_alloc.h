#include "wems_typedef.h"

#ifndef WEMS_RPM_ALLOC_H
#define WEMS_RPM_ALLOC_H

#define WEMS_SHIFT_FLASH_DELAY_MS 10

struct wems_rpm_block{
	si16* pins;
	si16 pin_count;
	si16 min_rpm;
	si16 max_rpm;
	si16 rpm_range;
};

wems_rpm_block wems_rpm_create(si16* rpm_pins, si16 num_pins);

wems_rpm_block wems_rpm_minmax_create(	si16* rpm_pins,
										si16 num_pins,
										si16 min,
										si16 max);

void wems_rpm_set_ligths479(const wems_rpm_block* rpm_blk, si16 rpm_val, ui8 direction);
#endif

