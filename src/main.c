/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Bart Van Der Meerssche <bart@flukso.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <string.h>
#include <libopencmsis/core_cm3.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/crs.h>
#include <libopencm3/stm32/syscfg.h>
#include <libopencm3/stm32/rng.h>
#include "usb.h"
#include "cli.h"
#include "config.h"

static void clock_setup(void)
{
	rcc_osc_on(RCC_HSI16);
	rcc_wait_for_osc_ready(RCC_HSI16);
	rcc_set_sysclk_source(RCC_HSI16);
	rcc_periph_clock_enable(RCC_SYSCFG);
	/* HSI48 needs the vrefint turned on */
	SYSCFG_CFGR3 |= SYSCFG_CFGR3_ENREF_HSI48 | SYSCFG_CFGR3_EN_VREFINT;
	while (!(SYSCFG_CFGR3 & SYSCFG_CFGR3_REF_HSI48_RDYF));
	rcc_periph_clock_enable(RCC_CRS);
	crs_autotrim_usb_enable();
	rcc_osc_on(RCC_HSI48);
	rcc_wait_for_osc_ready(RCC_HSI48);
	rcc_set_hsi48_source_rc48();
}

static void rng_setup(void)
{
	rcc_periph_clock_enable(RCC_RNG);
	rng_enable();
}

int main(void)
{
	cm_disable_interrupts();
	clock_setup();
	usb_setup();
	cli_setup();
	rng_setup();
	cm_enable_interrupts();

	while (1) {
		usb_print_trng(rng_get_random_blocking());
	}
	return 0;
}
