
#ifndef FAUCET_CONTROLLER_H
#define FAUCET_CONTROLLER_H

void faucet_begin(void);

void faucet_open_faucet(void);

void faucet_close_faucet(void);

int faucet_lower_temperature_level(const int actuateValves);

int faucet_raise_temperature_level(const int actuateValves);

void faucet_set_valves_level(const int level);

void faucet_display_level(int level);

void faucet_display_actual_level(void);

void faucet_set_blue_led_high(void);

void faucet_level_display_clear(void);

void faucet_valves_state_clear(void);

void faucet_set_blue_led_low(void);

void faucet_set_led_level_high(const int ledPort);

void faucet_set_led_level_low(const int ledPort);

void faucet_reset_level(void);

#endif // FAUCET_CONTROLLER_H
