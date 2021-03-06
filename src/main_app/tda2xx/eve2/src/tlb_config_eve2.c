/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file tlb_config_eve2.c
 *
 * \brief  This file implements the MMU configuration of EVE2
 *
 * \version 0.0 (Jul 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/ipc/Ipc.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */

/*******************************************************************************
 *  The macros to read and write from/to the memory
 *******************************************************************************
 */
#define WR_MEM_32(addr, data)    *(unsigned int*)(addr) =(unsigned int)(data)
#define RD_MEM_32(addr)          *(unsigned int*)(addr)

/*******************************************************************************
 *  MMU base address - Eve's view
 *******************************************************************************
 */
#define MMU_BASE 0x40081000

/*******************************************************************************
 *  MMU base address - IPU's view
 *******************************************************************************
 */
//#define MMU_BASE 0x42081000

/*******************************************************************************
 *  MMU address (base + offset) for various MMU settings
 *******************************************************************************
 */
#define TESLASS_MMU__MMU_CNTL    ( MMU_BASE + 0x44 )
#define TESLASS_MMU__MMU_CAM     ( MMU_BASE + 0x58 )
#define TESLASS_MMU__MMU_RAM     ( MMU_BASE + 0x5c )
#define TESLASS_MMU__MMU_LOCK    ( MMU_BASE + 0x50 )
#define TESLASS_MMU__MMU_LD_TLB  ( MMU_BASE + 0x54 )

/*******************************************************************************
 *  Defines for each register physical and virtual address base
 *******************************************************************************
 */
#define PHY_ADDR1   0x48030000
#define VIRT_ADDR1  0x68030000

#define PHY_ADDR2   0x40300000
#define VIRT_ADDR2  0x40300000

#define PHY_ADDR3   0x49000000
#define VIRT_ADDR3  0x49000000

#define PHY_ADDR4   0x4A000000
#define VIRT_ADDR4  0x4A000000

#define PHY_ADDR5   0x42000000
#define VIRT_ADDR5  0x42000000

//This is for mapping OCMC region
#define PHY_ADDR6   0x41800000
#define VIRT_ADDR6  0x41800000

#define PHY_ADDR7   0x49000000
#define VIRT_ADDR7  0x49000000

#ifdef TDA2XX_256MB_DDR
#define PHY_ADDR8   0xAF000000
#define VIRT_ADDR8  0xAF000000
#endif

#ifdef TDA2XX_1024MB_DDR
#define PHY_ADDR8   0xA0000000
#define VIRT_ADDR8  0xA0000000
#endif

#define PHY_ADDR30  0x85000000
#define VIRT_ADDR30 0x85000000

#define PHY_ADDR9   0x86000000
#define VIRT_ADDR9  0x86000000

#define PHY_ADDR10  0x87000000
#define VIRT_ADDR10 0x87000000

#define PHY_ADDR11  0x88000000
#define VIRT_ADDR11 0x88000000

#define PHY_ADDR12  0x89000000
#define VIRT_ADDR12 0x89000000

#define PHY_ADDR13  0x8A000000
#define VIRT_ADDR13 0x8A000000

#define PHY_ADDR14  0x8B000000
#define VIRT_ADDR14 0x8B000000

#ifdef TDA2XX_1024MB_DDR
#define PHY_ADDR15  0x8C000000
#define VIRT_ADDR15 0x8C000000

#define PHY_ADDR16  0x8D000000
#define VIRT_ADDR16 0x8D000000

#define PHY_ADDR17  0x8E000000
#define VIRT_ADDR17 0x8E000000

#define PHY_ADDR18  0x8F000000
#define VIRT_ADDR18 0x8F000000

#define PHY_ADDR19  0x90000000
#define VIRT_ADDR19 0x90000000

#define PHY_ADDR20  0x91000000
#define VIRT_ADDR20 0x91000000

#define PHY_ADDR21  0x92000000
#define VIRT_ADDR21 0x92000000

#define PHY_ADDR22  0x93000000
#define VIRT_ADDR22 0x93000000

#define PHY_ADDR23  0x94000000
#define VIRT_ADDR23 0x94000000

#define PHY_ADDR24  0x95000000
#define VIRT_ADDR24 0x95000000

#define PHY_ADDR25  0x96000000
#define VIRT_ADDR25 0x96000000

#define PHY_ADDR26  0x97000000
#define VIRT_ADDR26 0x97000000

#define PHY_ADDR27  0x98000000
#define VIRT_ADDR27 0x98000000

#define PHY_ADDR28  0x99000000
#define VIRT_ADDR28 0x99000000

#define PHY_ADDR29  0x9A000000
#define VIRT_ADDR29 0x9A000000
#endif


/**
 *******************************************************************************
 *
 * \brief This function implements the MMU configuration of EVE2
 *
 * \return  void
 *
 *******************************************************************************
 */
void eve2MmuConfig(void)
{
    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR1 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR1  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 3 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR2 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR2  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 4 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR3 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR3  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 5 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR4 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR4  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 6 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR5 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR5  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 7 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR6 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR6  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 8 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR7 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR7  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 9 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR8 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR8  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 10 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR9 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR9  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 11 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR10 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR10  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 12 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR11 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR11  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 13 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR12 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR12  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 14 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR13 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR13  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 15 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR14 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR14  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 16 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

#ifdef TDA2XX_1024MB_DDR
    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR15 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR15  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 17 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR16 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR16  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 18 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR17 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR17  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 19 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR18 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR18  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 20 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR19 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR19  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 21 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR20 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR20  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 22 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR21 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR21  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 23 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR22 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR22  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 24 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR23 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR23  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 25 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR24 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR24  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 26 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR25 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR25  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 27 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR26 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR26  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 28 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR27 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR27  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 29 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR28 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR28  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 30 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR29 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR29  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 31 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000f | (VIRT_ADDR30 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR30  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 32 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */
#endif

    /*Enable MMU*/
    WR_MEM_32(TESLASS_MMU__MMU_CNTL, ((RD_MEM_32(TESLASS_MMU__MMU_CNTL)) & 0xFFFFFFFD) | 0x2);

}

/* Nothing beyond this point */

