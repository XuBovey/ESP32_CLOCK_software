/*
 * gpio_button.h
 *
 *  Created on: 2021��7��8��
 *      Author: Bovey
 */

#ifndef MAIN_GPIO_BUTTON_H_
#define MAIN_GPIO_BUTTON_H_

void gpio_button_init(void);
bool get_gpio_state(uint8_t num);

#endif /* MAIN_GPIO_BUTTON_H_ */
