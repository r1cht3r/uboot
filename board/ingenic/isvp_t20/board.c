/*
 * Ingenic isvp setup code
 *
 * Copyright (c) 2013 Ingenic Semiconductor Co.,Ltd
 * Author: Zoro <ykli@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <nand.h>
#include <net.h>
#include <netdev.h>
#include <asm/gpio.h>
#include <asm/arch/cpm.h>
#include <asm/arch/nand.h>
#include <asm/arch/mmc.h>
#include <asm/arch/clk.h>
#include <power/d2041_core.h>
#include <command.h>


extern int jz_net_initialize(bd_t *bis);
struct cgu_clk_src cgu_clk_src[] = {
	{VPU, VPLL},
	{MACPHY, MPLL},
	{MSC, APLL},
	{SSI, MPLL},
	{CIM, VPLL},
	{ISP, MPLL},
	{I2S, APLL},
	{SRC_EOF,SRC_EOF}
};

int board_early_init_f(void)
{
	return 0;
}

#ifdef CONFIG_USB_GADGET
int jz_udc_probe(void);
void board_usb_init(void)
{
	printf("USB_udc_probe\n");
	jz_udc_probe();
}
#endif /* CONFIG_USB_GADGET */

int misc_init_r(void)
{
#if 0 /* TO DO */
	uint8_t mac[6] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc };

	/* set MAC address */
	eth_setenv_enetaddr("ethaddr", mac);
#endif
	/* used for usb_dete */
	/*gpio_set_pull_dir(GPIO_PB(22), 1);*/

    printf("Setting yellow_gpio to off:\n");
    run_command("gpio set 38",0);
	printf("Setting blue_gpio to off:\n");
    run_command("gpio set 39",0);
    printf("Setting night_gpios:\n");
    run_command("gpio clear 81",0);
    run_command("gpio clear 49",0);
    run_command("gpio clear 25",0);
    printf("Setting USB enable:\n");
    run_command("gpio set 47",0);
    printf("Setting Speaker enable:\n");
    run_command("gpio set 63",0);

    printf("Setting Enable SDCARD:\n");
    run_command("gpio set 43",0);
    run_command("gpio clear 48",0);
    #ifdef CONFIG_BOARD_NAME_XIAOFANG
        printf("Sleep one second:\n");
        run_command("sleep 1",0);
        printf("Sleep done:\n");
        run_command("gpio clear 43",0);
    #endif



	printf("Running SDupdate....\n");
	run_command("sdupdate",0);




	return 0;
}



#ifdef CONFIG_MMC
int board_mmc_init(bd_t *bd)
{
	jz_mmc_init();
	return 0;
}
#endif

int board_eth_init(bd_t *bis)
{
	return jz_net_initialize(bis);
}

#ifdef CONFIG_SPL_NOR_SUPPORT
int spl_start_uboot(void)
{
	return 1;
}
#endif
/* U-Boot common routines */
int checkboard(void)
{


#if defined(CONFIG_BOARD_NAME_DAFANG64)
#define BOARD_NAME	"Dafang 64MB"
#elif defined(CONFIG_BOARD_NAME_DAFANG128)
#define BOARD_NAME	"Dafang 128MB"
#elif defined(CONFIG_BOARD_NAME_XIAOFANG)
#define BOARD_NAME	"Xiaofang 1S"
#else
#error "No board variant defined!"
#endif

    puts("Bootloader-Version: Dafanghacks v2\n");
	puts("Board: "BOARD_NAME" (Ingenic XBurst T20 SoC)\n");
	return 0;
}

#ifdef CONFIG_SPL_BUILD

void spl_board_init(void)
{
}

#endif /* CONFIG_SPL_BUILD */
