#ifndef __THERMO_CONTROLLER_PERIPH_H
#define __THERMO_CONTROLLER_PERIPH_H

void heater_on(void);
void heater_off(void);

void temp_stab_on(void);
void temp_stab_off(void);
void get_temp_on(void);
void get_temp_off(void);


unsigned int get_current_temp_raw(void);


#endif
