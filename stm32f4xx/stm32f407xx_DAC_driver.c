/*
 * stm32f407xx_DAC_driver.c
 *
 *  Created on: Mar 5, 2022
 *      Author: gianl
 */


#include "stm32f407xx_DAC_driver.h"

void DAC_Clk_EnorDi(uint8_t EnorDi)
{
	if(EnorDi)
	{
		DAC_CLK_EN();
	}else
	{
		DAC_CLK_DI();
	}
}


void DACInit(DAC_Handler_t *DAC_Handle)
{
	 uint32_t temp=0; //temp register
	 uint32_t offset=0;

	if(DAC_Handle->DAC_Config.Channel == 1)
	{
		temp |= (1 << 0);
		offset=0;
	}
	else if(DAC_Handle->DAC_Config.Channel == 2)
	{
		temp |= (1 << 16);
		offset=16;
	}

	//buffer
	temp |= (DAC_Handle->DAC_Config.Buffer << (offset+1)); //default enabled

	//trigger enable
	temp |= (DAC_Handle->DAC_Config.Trigger << (offset+2)); //default no

	//trigger selection
	temp |= (DAC_Handle->DAC_Config.TrigSelect << (offset+3));

	//wave enable noie or triangle
	temp |= (DAC_Handle->DAC_Config.WaveGen << (offset+6));

	//amplitude/mask stuff
	temp |= (DAC_Handle->DAC_Config.MaskAmpSelect << (offset+8));

	//DMA enable
	temp |= (DAC_Handle->DAC_Config.DMAEn << (offset+12));

	//DMA overrun enable
	temp |= (DAC_Handle->DAC_Config.DMAUnderRn << (offset+13));

	DAC_Handle->pDACx->CR |= temp;

}


void DAC_SoftwareTrigger(uint8_t Channel)
{
	Channel = Channel - 1;
	DAC->SWTTRIGR |= (1 << Channel);

}

void analogWrite(uint8_t Channel, uint32_t Val)
{
	if(Channel == 1)
	{
		DAC->DHR12R1 = Val;
	}
	else if(Channel == 2)
	{
		DAC->DHR12R2 = Val;
	}
}

void analogDualWrite(uint32_t Val_1, uint32_t Val_2)
{
	uint32_t temp=0;

	temp |= (Val_2 << 16);
	temp |= (Val_1 << 0);

	DAC->DHR12RD = temp;
}




uint32_t Sin_Tab_P1000[] = {2048,
		2060,
		2073,
		2086,
		2099,
		2112,
		2125,
		2138,
		2150,
		2163,
		2176,
		2189,
		2202,
		2215,
		2227,
		2240,
		2253,
		2266,
		2279,
		2291,
		2304,
		2317,
		2330,
		2342,
		2355,
		2368,
		2380,
		2393,
		2406,
		2419,
		2431,
		2444,
		2456,
		2469,
		2482,
		2494,
		2507,
		2519,
		2532,
		2544,
		2557,
		2569,
		2582,
		2594,
		2606,
		2619,
		2631,
		2643,
		2656,
		2668,
		2680,
		2692,
		2705,
		2717,
		2729,
		2741,
		2753,
		2765,
		2777,
		2789,
		2801,
		2813,
		2825,
		2837,
		2849,
		2861,
		2872,
		2884,
		2896,
		2908,
		2919,
		2931,
		2942,
		2954,
		2966,
		2977,
		2988,
		3000,
		3011,
		3023,
		3034,
		3045,
		3056,
		3068,
		3079,
		3090,
		3101,
		3112,
		3123,
		3134,
		3145,
		3155,
		3166,
		3177,
		3188,
		3198,
		3209,
		3220,
		3230,
		3241,
		3251,
		3261,
		3272,
		3282,
		3292,
		3302,
		3313,
		3323,
		3333,
		3343,
		3353,
		3363,
		3372,
		3382,
		3392,
		3402,
		3411,
		3421,
		3430,
		3440,
		3449,
		3458,
		3468,
		3477,
		3486,
		3495,
		3504,
		3513,
		3522,
		3531,
		3540,
		3549,
		3558,
		3566,
		3575,
		3583,
		3592,
		3600,
		3609,
		3617,
		3625,
		3633,
		3641,
		3649,
		3657,
		3665,
		3673,
		3681,
		3689,
		3696,
		3704,
		3711,
		3719,
		3726,
		3734,
		3741,
		3748,
		3755,
		3762,
		3769,
		3776,
		3783,
		3790,
		3797,
		3803,
		3810,
		3816,
		3823,
		3829,
		3836,
		3842,
		3848,
		3854,
		3860,
		3866,
		3872,
		3878,
		3883,
		3889,
		3895,
		3900,
		3906,
		3911,
		3916,
		3921,
		3927,
		3932,
		3937,
		3942,
		3946,
		3951,
		3956,
		3961,
		3965,
		3970,
		3974,
		3978,
		3983,
		3987,
		3991,
		3995,
		3999,
		4003,
		4006,
		4010,
		4014,
		4017,
		4021,
		4024,
		4027,
		4031,
		4034,
		4037,
		4040,
		4043,
		4046,
		4048,
		4051,
		4054,
		4056,
		4059,
		4061,
		4063,
		4066,
		4068,
		4070,
		4072,
		4074,
		4075,
		4077,
		4079,
		4080,
		4082,
		4083,
		4085,
		4086,
		4087,
		4088,
		4089,
		4090,
		4091,
		4092,
		4092,
		4093,
		4094,
		4094,
		4094,
		4095,
		4095,
		4095,
		4095,
		4095,
		4095,
		4095,
		4094,
		4094,
		4094,
		4093,
		4092,
		4092,
		4091,
		4090,
		4089,
		4088,
		4087,
		4086,
		4085,
		4083,
		4082,
		4080,
		4079,
		4077,
		4075,
		4074,
		4072,
		4070,
		4068,
		4066,
		4063,
		4061,
		4059,
		4056,
		4054,
		4051,
		4048,
		4046,
		4043,
		4040,
		4037,
		4034,
		4031,
		4027,
		4024,
		4021,
		4017,
		4014,
		4010,
		4006,
		4003,
		3999,
		3995,
		3991,
		3987,
		3983,
		3978,
		3974,
		3970,
		3965,
		3961,
		3956,
		3951,
		3946,
		3942,
		3937,
		3932,
		3927,
		3921,
		3916,
		3911,
		3906,
		3900,
		3895,
		3889,
		3883,
		3878,
		3872,
		3866,
		3860,
		3854,
		3848,
		3842,
		3836,
		3829,
		3823,
		3816,
		3810,
		3803,
		3797,
		3790,
		3783,
		3776,
		3769,
		3762,
		3755,
		3748,
		3741,
		3734,
		3726,
		3719,
		3711,
		3704,
		3696,
		3689,
		3681,
		3673,
		3665,
		3657,
		3649,
		3641,
		3633,
		3625,
		3617,
		3609,
		3600,
		3592,
		3583,
		3575,
		3566,
		3558,
		3549,
		3540,
		3531,
		3522,
		3513,
		3504,
		3495,
		3486,
		3477,
		3468,
		3458,
		3449,
		3440,
		3430,
		3421,
		3411,
		3402,
		3392,
		3382,
		3372,
		3363,
		3353,
		3343,
		3333,
		3323,
		3313,
		3302,
		3292,
		3282,
		3272,
		3261,
		3251,
		3241,
		3230,
		3220,
		3209,
		3198,
		3188,
		3177,
		3166,
		3155,
		3145,
		3134,
		3123,
		3112,
		3101,
		3090,
		3079,
		3068,
		3056,
		3045,
		3034,
		3023,
		3011,
		3000,
		2988,
		2977,
		2966,
		2954,
		2942,
		2931,
		2919,
		2908,
		2896,
		2884,
		2872,
		2861,
		2849,
		2837,
		2825,
		2813,
		2801,
		2789,
		2777,
		2765,
		2753,
		2741,
		2729,
		2717,
		2705,
		2692,
		2680,
		2668,
		2656,
		2643,
		2631,
		2619,
		2606,
		2594,
		2582,
		2569,
		2557,
		2544,
		2532,
		2519,
		2507,
		2494,
		2482,
		2469,
		2456,
		2444,
		2431,
		2419,
		2406,
		2393,
		2380,
		2368,
		2355,
		2342,
		2330,
		2317,
		2304,
		2291,
		2279,
		2266,
		2253,
		2240,
		2227,
		2215,
		2202,
		2189,
		2176,
		2163,
		2150,
		2138,
		2125,
		2112,
		2099,
		2086,
		2073,
		2060,
		2048,
		2035,
		2022,
		2009,
		1996,
		1983,
		1970,
		1957,
		1945,
		1932,
		1919,
		1906,
		1893,
		1880,
		1868,
		1855,
		1842,
		1829,
		1816,
		1804,
		1791,
		1778,
		1765,
		1753,
		1740,
		1727,
		1715,
		1702,
		1689,
		1676,
		1664,
		1651,
		1639,
		1626,
		1613,
		1601,
		1588,
		1576,
		1563,
		1551,
		1538,
		1526,
		1513,
		1501,
		1489,
		1476,
		1464,
		1452,
		1439,
		1427,
		1415,
		1403,
		1390,
		1378,
		1366,
		1354,
		1342,
		1330,
		1318,
		1306,
		1294,
		1282,
		1270,
		1258,
		1246,
		1234,
		1223,
		1211,
		1199,
		1187,
		1176,
		1164,
		1153,
		1141,
		1129,
		1118,
		1107,
		1095,
		1084,
		1072,
		1061,
		1050,
		1039,
		1027,
		1016,
		1005,
		994,
		983,
		972,
		961,
		950,
		940,
		929,
		918,
		907,
		897,
		886,
		875,
		865,
		854,
		844,
		834,
		823,
		813,
		803,
		793,
		782,
		772,
		762,
		752,
		742,
		732,
		723,
		713,
		703,
		693,
		684,
		674,
		665,
		655,
		646,
		637,
		627,
		618,
		609,
		600,
		591,
		582,
		573,
		564,
		555,
		546,
		537,
		529,
		520,
		512,
		503,
		495,
		486,
		478,
		470,
		462,
		454,
		446,
		438,
		430,
		422,
		414,
		406,
		399,
		391,
		384,
		376,
		369,
		361,
		354,
		347,
		340,
		333,
		326,
		319,
		312,
		305,
		298,
		292,
		285,
		279,
		272,
		266,
		259,
		253,
		247,
		241,
		235,
		229,
		223,
		217,
		212,
		206,
		200,
		195,
		189,
		184,
		179,
		174,
		168,
		163,
		158,
		153,
		149,
		144,
		139,
		134,
		130,
		125,
		121,
		117,
		112,
		108,
		104,
		100,
		96,
		92,
		89,
		85,
		81,
		78,
		74,
		71,
		68,
		64,
		61,
		58,
		55,
		52,
		49,
		47,
		44,
		41,
		39,
		36,
		34,
		32,
		29,
		27,
		25,
		23,
		21,
		20,
		18,
		16,
		15,
		13,
		12,
		10,
		9,
		8,
		7,
		6,
		5,
		4,
		3,
		3,
		2,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		2,
		3,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
		10,
		12,
		13,
		15,
		16,
		18,
		20,
		21,
		23,
		25,
		27,
		29,
		32,
		34,
		36,
		39,
		41,
		44,
		47,
		49,
		52,
		55,
		58,
		61,
		64,
		68,
		71,
		74,
		78,
		81,
		85,
		89,
		92,
		96,
		100,
		104,
		108,
		112,
		117,
		121,
		125,
		130,
		134,
		139,
		144,
		149,
		153,
		158,
		163,
		168,
		174,
		179,
		184,
		189,
		195,
		200,
		206,
		212,
		217,
		223,
		229,
		235,
		241,
		247,
		253,
		259,
		266,
		272,
		279,
		285,
		292,
		298,
		305,
		312,
		319,
		326,
		333,
		340,
		347,
		354,
		361,
		369,
		376,
		384,
		391,
		399,
		406,
		414,
		422,
		430,
		438,
		446,
		454,
		462,
		470,
		478,
		486,
		495,
		503,
		512,
		520,
		529,
		537,
		546,
		555,
		564,
		573,
		582,
		591,
		600,
		609,
		618,
		627,
		637,
		646,
		655,
		665,
		674,
		684,
		693,
		703,
		713,
		723,
		732,
		742,
		752,
		762,
		772,
		782,
		793,
		803,
		813,
		823,
		834,
		844,
		854,
		865,
		875,
		886,
		897,
		907,
		918,
		929,
		940,
		950,
		961,
		972,
		983,
		994,
		1005,
		1016,
		1027,
		1039,
		1050,
		1061,
		1072,
		1084,
		1095,
		1107,
		1118,
		1129,
		1141,
		1153,
		1164,
		1176,
		1187,
		1199,
		1211,
		1223,
		1234,
		1246,
		1258,
		1270,
		1282,
		1294,
		1306,
		1318,
		1330,
		1342,
		1354,
		1366,
		1378,
		1390,
		1403,
		1415,
		1427,
		1439,
		1452,
		1464,
		1476,
		1489,
		1501,
		1513,
		1526,
		1538,
		1551,
		1563,
		1576,
		1588,
		1601,
		1613,
		1626,
		1639,
		1651,
		1664,
		1676,
		1689,
		1702,
		1715,
		1727,
		1740,
		1753,
		1765,
		1778,
		1791,
		1804,
		1816,
		1829,
		1842,
		1855,
		1868,
		1880,
		1893,
		1906,
		1919,
		1932,
		1945,
		1957,
		1970,
		1983,
		1996,
		2009,
		2022,
		2035,
		2048
};

/*void SineWaveGen(uint8_t Channel)
{
	for(uint32_t tik=0; tik <= 4000; tik++)
	{
		analogWrite(Channel,Sin_Tab_P4000[tik]);
	}
	for(uint32_t tik=4000; tik >= 1; tik--)
	{
		analogWrite(Channel,Sin_Tab_P4000[tik]);
	}
}

void DualSineWaveGen(void)
{
	for(uint32_t tik=0; tik <= 4000; tik++)
	{
		analogDualWrite(Sin_Tab_P4000[tik+100],Sin_Tab_P4000[tik]);
	}
	for(uint32_t tik=4000; tik >= 1; tik--)
	{
		analogDualWrite(Sin_Tab_P4000[tik],Sin_Tab_P4000[tik]);
	}
}*/

uint8_t Ch_1_Flg = 1;
uint8_t Ch_2_Flg = 1;
uint32_t Chan1=0;
uint32_t Chan2=0;
uint32_t delayer=0;

/*void DualOpposeSineWaveGen(uint32_t offset)
{
	// Ch_1_Flg = 1 for inc and 0 for dec

	if(delayer < offset)
	{
		Chan2 =0;
		delayer++;
	}

	analogDualWrite(Sin_Tab_P4000[Chan1],Sin_Tab_P4000[Chan2]);

	if((Chan1 < 4000) && (Ch_1_Flg))
	{
		Chan1++;
	}
	else if((Chan1 > 0) && (!Ch_1_Flg))
	{
		Chan1--;
	}
	else if((Chan1 == 4000) && (Ch_1_Flg))
	{
		Ch_1_Flg=0;
		Chan1--;
	}
	else if((Chan1 == 0) && (!Ch_1_Flg))
	{
		Ch_1_Flg=1;
		Chan1++;
	}

	if((Chan2 < 4000) && (Ch_2_Flg))
	{
		Chan2++;
	}
	else if((Chan2 > 0) && (!Ch_2_Flg))
	{
		Chan2--;
	}
	else if((Chan2 == 4000) && (Ch_2_Flg))
	{
		Ch_2_Flg=0;
		Chan2--;
	}
	else if((Chan2 == 0) && (!Ch_2_Flg))
	{
		Ch_2_Flg=1;
		Chan2++;
	}
}*/

/*uint32_t Sin_Tab_P10000[]={
};

void BetterDualOpposeSineWaveGen(uint32_t offset)
{
	// Ch_1_Flg = 1 for inc and 0 for dec

	if(delayer < offset)
	{
		Chan2 =0;
		delayer++;
	}

	analogDualWrite(Sin_Tab_P10000[Chan1],Sin_Tab_P10000[Chan2]);

	Chan1=Chan1+1;
	Chan2=Chan2+1;

	if(Chan1 >= 10000){Chan1 = 0;}
	if(Chan2 >= 10000){Chan2 = 0;}

}

uint32_t b=0;
void single_checker(void)
{
	analogWrite(1, Sin_Tab_P10000[b]);

	b++;

	if(b >= 10000){b = 0;}
}*/

uint32_t phase_flg=0;
void TimerDualOpposeSineWaveGen(uint32_t offset, uint32_t offset_2, uint32_t phase_shift)
{
	// Ch_1_Flg = 1 for inc and 0 for dec

	if(delayer < 1)
	{
		TIM6->ARR = offset;
		TIM6->CR1 |= (1 << 0);
		TIM7->ARR = offset_2;
		TIM7->CR1 |= (1 << 0);
		delayer++;
	}

	if((Chan1 < phase_shift) && (phase_flg == 0))
	{
		Chan2=0;
	}
	else
	{
		phase_flg=1;
	}



	analogDualWrite(Sin_Tab_P1000[Chan1],Sin_Tab_P1000[Chan2]);

	if(TIM6->SR)
	{
		Chan1=Chan1+1;
		SR_clearer(6);
	}

	if(TIM7->SR)
	{
		Chan2=Chan2+1;
		SR_clearer(7);
	}

	if(Chan1 >= 1000){Chan1 = 0;}
	if(Chan2 >= 1000){Chan2 = 0;}

}

uint32_t Half_Sin_Tab_P1000[]={0,
		13,
		26,
		39,
		51,
		64,
		77,
		90,
		103,
		116,
		129,
		141,
		154,
		167,
		180,
		193,
		205,
		218,
		231,
		244,
		257,
		269,
		282,
		295,
		308,
		320,
		333,
		346,
		358,
		371,
		384,
		396,
		409,
		422,
		434,
		447,
		459,
		472,
		484,
		497,
		509,
		522,
		534,
		546,
		559,
		571,
		584,
		596,
		608,
		620,
		633,
		645,
		657,
		669,
		681,
		694,
		706,
		718,
		730,
		742,
		754,
		766,
		778,
		789,
		801,
		813,
		825,
		837,
		848,
		860,
		872,
		883,
		895,
		907,
		918,
		930,
		941,
		952,
		964,
		975,
		986,
		998,
		1009,
		1020,
		1031,
		1042,
		1053,
		1064,
		1075,
		1086,
		1097,
		1108,
		1119,
		1129,
		1140,
		1151,
		1161,
		1172,
		1183,
		1193,
		1203,
		1214,
		1224,
		1234,
		1245,
		1255,
		1265,
		1275,
		1285,
		1295,
		1305,
		1315,
		1325,
		1335,
		1344,
		1354,
		1364,
		1373,
		1383,
		1392,
		1402,
		1411,
		1420,
		1429,
		1439,
		1448,
		1457,
		1466,
		1475,
		1484,
		1493,
		1501,
		1510,
		1519,
		1527,
		1536,
		1544,
		1553,
		1561,
		1569,
		1578,
		1586,
		1594,
		1602,
		1610,
		1618,
		1626,
		1633,
		1641,
		1649,
		1656,
		1664,
		1671,
		1679,
		1686,
		1693,
		1701,
		1708,
		1715,
		1722,
		1729,
		1736,
		1742,
		1749,
		1756,
		1762,
		1769,
		1775,
		1782,
		1788,
		1794,
		1800,
		1806,
		1813,
		1818,
		1824,
		1830,
		1836,
		1842,
		1847,
		1853,
		1858,
		1863,
		1869,
		1874,
		1879,
		1884,
		1889,
		1894,
		1899,
		1904,
		1908,
		1913,
		1918,
		1922,
		1926,
		1931,
		1935,
		1939,
		1943,
		1947,
		1951,
		1955,
		1959,
		1963,
		1966,
		1970,
		1973,
		1977,
		1980,
		1983,
		1986,
		1989,
		1992,
		1995,
		1998,
		2001,
		2004,
		2006,
		2009,
		2011,
		2014,
		2016,
		2018,
		2020,
		2022,
		2024,
		2026,
		2028,
		2030,
		2031,
		2033,
		2034,
		2036,
		2037,
		2038,
		2040,
		2041,
		2042,
		2043,
		2043,
		2044,
		2045,
		2046,
		2046,
		2046,
		2047,
		2047,
		2047,
		2047,
		2048,
		2047,
		2047,
		2047,
		2047,
		2046,
		2046,
		2046,
		2045,
		2044,
		2043,
		2043,
		2042,
		2041,
		2040,
		2038,
		2037,
		2036,
		2034,
		2033,
		2031,
		2030,
		2028,
		2026,
		2024,
		2022,
		2020,
		2018,
		2016,
		2014,
		2011,
		2009,
		2006,
		2004,
		2001,
		1998,
		1995,
		1992,
		1989,
		1986,
		1983,
		1980,
		1977,
		1973,
		1970,
		1966,
		1963,
		1959,
		1955,
		1951,
		1947,
		1943,
		1939,
		1935,
		1931,
		1926,
		1922,
		1918,
		1913,
		1908,
		1904,
		1899,
		1894,
		1889,
		1884,
		1879,
		1874,
		1869,
		1863,
		1858,
		1853,
		1847,
		1842,
		1836,
		1830,
		1824,
		1818,
		1813,
		1806,
		1800,
		1794,
		1788,
		1782,
		1775,
		1769,
		1762,
		1756,
		1749,
		1742,
		1736,
		1729,
		1722,
		1715,
		1708,
		1701,
		1693,
		1686,
		1679,
		1671,
		1664,
		1656,
		1649,
		1641,
		1633,
		1626,
		1618,
		1610,
		1602,
		1594,
		1586,
		1578,
		1569,
		1561,
		1553,
		1544,
		1536,
		1527,
		1519,
		1510,
		1501,
		1493,
		1484,
		1475,
		1466,
		1457,
		1448,
		1439,
		1429,
		1420,
		1411,
		1402,
		1392,
		1383,
		1373,
		1364,
		1354,
		1344,
		1335,
		1325,
		1315,
		1305,
		1295,
		1285,
		1275,
		1265,
		1255,
		1245,
		1234,
		1224,
		1214,
		1203,
		1193,
		1183,
		1172,
		1161,
		1151,
		1140,
		1129,
		1119,
		1108,
		1097,
		1086,
		1075,
		1064,
		1053,
		1042,
		1031,
		1020,
		1009,
		998,
		986,
		975,
		964,
		952,
		941,
		930,
		918,
		907,
		895,
		883,
		872,
		860,
		848,
		837,
		825,
		813,
		801,
		789,
		778,
		766,
		754,
		742,
		730,
		718,
		706,
		694,
		681,
		669,
		657,
		645,
		633,
		620,
		608,
		596,
		584,
		571,
		559,
		546,
		534,
		522,
		509,
		497,
		484,
		472,
		459,
		447,
		434,
		422,
		409,
		396,
		384,
		371,
		358,
		346,
		333,
		320,
		308,
		295,
		282,
		269,
		257,
		244,
		231,
		218,
		205,
		193,
		180,
		167,
		154,
		141,
		129,
		116,
		103,
		90,
		77,
		64,
		51,
		39,
		26,
		13,
		0
};

uint8_t Chan1_flg=1;
uint8_t Chan2_flg=0;

void TimerDualDACSineWaveGen(uint32_t offset)
{

	if(delayer < 1)
	{
		TIM6->ARR = offset;
		TIM6->CR1 |= (1 << 0);
		TIM7->ARR = offset;
		TIM7->CR1 |= (1 << 0);
		delayer++;
	}



	//analogDualWrite(Half_Sin_Tab_P1000[Chan1],Half_Sin_Tab_P1000[Chan2]);
	if(Chan1 < 500 && Chan1_flg)
	{
		if(TIM6->SR)
		{
			GPIO_DAC_Inits();
			GPIO_GRD_Inits();
			Chan1=Chan1+1;
			SR_clearer(6);
			analogWrite(1,Half_Sin_Tab_P1000[Chan1]);
		}

	}
	else if(Chan1 >= 500){Chan1 = 0; Chan1_flg=0; Chan2_flg=1;}

	if(Chan2 < 500 && Chan2_flg)
	{
		if(TIM7->SR)
		{
			GPIO_DAC_Inits();
			GPIO_GRD_Inits();
			Chan2=Chan2+1;
			SR_clearer(7);
			analogWrite(2,Half_Sin_Tab_P1000[Chan2]);
		}
	}
	else if(Chan2 >= 500){Chan2 = 0; Chan2_flg=0; Chan1_flg=1;}
}

void GPIO_DAC_Inits(void)
{
	GPIO_Handler_t ADCPins;

	ADCPins.pGPIOx = GPIOA;

	ADCPins.GPIO_PinConfig.GPIO_PinMode = ANALOG;
	ADCPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	ADCPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	ADCPins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	ADCPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;

	if(Chan1_flg)
	{
		ADCPins.GPIO_PinConfig.GPIO_PinNumber = 4;
		GPIO_Init(&ADCPins);
	}
	else if(Chan2_flg)
	{
		ADCPins.GPIO_PinConfig.GPIO_PinNumber = 5;
		GPIO_Init(&ADCPins);
	}
}

void GPIO_GRD_Inits(void)
{
	GPIO_Handler_t ADCPins;

	ADCPins.pGPIOx = GPIOA;

	ADCPins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	ADCPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	ADCPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	ADCPins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	ADCPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;

	if(Chan1_flg)
	{
		ADCPins.GPIO_PinConfig.GPIO_PinNumber = 5;
		GPIO_Init(&ADCPins);
	}
	else if(Chan2_flg)
	{
		ADCPins.GPIO_PinConfig.GPIO_PinNumber = 4;
		GPIO_Init(&ADCPins);
	}
}
