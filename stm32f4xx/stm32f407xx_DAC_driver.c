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




uint32_t Sin_Tab_P4000[] = { 1,
		1,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		3,
		3,
		3,
		3,
		3,
		3,
		3,
		3,
		3,
		3,
		3,
		3,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		4,
		5,
		5,
		5,
		5,
		5,
		5,
		5,
		5,
		5,
		6,
		6,
		6,
		6,
		6,
		6,
		6,
		6,
		7,
		7,
		7,
		7,
		7,
		7,
		7,
		7,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		9,
		9,
		9,
		9,
		9,
		9,
		9,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		11,
		11,
		11,
		11,
		11,
		11,
		12,
		12,
		12,
		12,
		12,
		12,
		13,
		13,
		13,
		13,
		13,
		14,
		14,
		14,
		14,
		14,
		14,
		15,
		15,
		15,
		15,
		15,
		16,
		16,
		16,
		16,
		16,
		17,
		17,
		17,
		17,
		17,
		18,
		18,
		18,
		18,
		18,
		19,
		19,
		19,
		19,
		19,
		20,
		20,
		20,
		20,
		21,
		21,
		21,
		21,
		21,
		22,
		22,
		22,
		22,
		23,
		23,
		23,
		23,
		24,
		24,
		24,
		24,
		25,
		25,
		25,
		25,
		26,
		26,
		26,
		26,
		27,
		27,
		27,
		27,
		28,
		28,
		28,
		28,
		29,
		29,
		29,
		29,
		30,
		30,
		30,
		30,
		31,
		31,
		31,
		32,
		32,
		32,
		32,
		33,
		33,
		33,
		33,
		34,
		34,
		34,
		35,
		35,
		35,
		35,
		36,
		36,
		36,
		37,
		37,
		37,
		38,
		38,
		38,
		38,
		39,
		39,
		39,
		40,
		40,
		40,
		41,
		41,
		41,
		42,
		42,
		42,
		42,
		43,
		43,
		43,
		44,
		44,
		44,
		45,
		45,
		45,
		46,
		46,
		46,
		47,
		47,
		47,
		48,
		48,
		48,
		49,
		49,
		49,
		50,
		50,
		50,
		51,
		51,
		51,
		52,
		52,
		53,
		53,
		53,
		54,
		54,
		54,
		55,
		55,
		55,
		56,
		56,
		57,
		57,
		57,
		58,
		58,
		58,
		59,
		59,
		59,
		60,
		60,
		61,
		61,
		61,
		62,
		62,
		63,
		63,
		63,
		64,
		64,
		64,
		65,
		65,
		66,
		66,
		66,
		67,
		67,
		68,
		68,
		68,
		69,
		69,
		70,
		70,
		70,
		71,
		71,
		72,
		72,
		73,
		73,
		73,
		74,
		74,
		75,
		75,
		75,
		76,
		76,
		77,
		77,
		78,
		78,
		78,
		79,
		79,
		80,
		80,
		81,
		81,
		81,
		82,
		82,
		83,
		83,
		84,
		84,
		85,
		85,
		85,
		86,
		86,
		87,
		87,
		88,
		88,
		89,
		89,
		90,
		90,
		90,
		91,
		91,
		92,
		92,
		93,
		93,
		94,
		94,
		95,
		95,
		96,
		96,
		97,
		97,
		98,
		98,
		98,
		99,
		99,
		100,
		100,
		101,
		101,
		102,
		102,
		103,
		103,
		104,
		104,
		105,
		105,
		106,
		106,
		107,
		107,
		108,
		108,
		109,
		109,
		110,
		110,
		111,
		111,
		112,
		112,
		113,
		113,
		114,
		114,
		115,
		116,
		116,
		117,
		117,
		118,
		118,
		119,
		119,
		120,
		120,
		121,
		121,
		122,
		122,
		123,
		123,
		124,
		125,
		125,
		126,
		126,
		127,
		127,
		128,
		128,
		129,
		129,
		130,
		131,
		131,
		132,
		132,
		133,
		133,
		134,
		134,
		135,
		136,
		136,
		137,
		137,
		138,
		138,
		139,
		140,
		140,
		141,
		141,
		142,
		142,
		143,
		144,
		144,
		145,
		145,
		146,
		146,
		147,
		148,
		148,
		149,
		149,
		150,
		151,
		151,
		152,
		152,
		153,
		153,
		154,
		155,
		155,
		156,
		156,
		157,
		158,
		158,
		159,
		160,
		160,
		161,
		161,
		162,
		163,
		163,
		164,
		164,
		165,
		166,
		166,
		167,
		168,
		168,
		169,
		169,
		170,
		171,
		171,
		172,
		173,
		173,
		174,
		174,
		175,
		176,
		176,
		177,
		178,
		178,
		179,
		180,
		180,
		181,
		181,
		182,
		183,
		183,
		184,
		185,
		185,
		186,
		187,
		187,
		188,
		189,
		189,
		190,
		191,
		191,
		192,
		193,
		193,
		194,
		195,
		195,
		196,
		197,
		197,
		198,
		199,
		199,
		200,
		201,
		201,
		202,
		203,
		203,
		204,
		205,
		205,
		206,
		207,
		208,
		208,
		209,
		210,
		210,
		211,
		212,
		212,
		213,
		214,
		214,
		215,
		216,
		217,
		217,
		218,
		219,
		219,
		220,
		221,
		222,
		222,
		223,
		224,
		224,
		225,
		226,
		227,
		227,
		228,
		229,
		229,
		230,
		231,
		232,
		232,
		233,
		234,
		234,
		235,
		236,
		237,
		237,
		238,
		239,
		240,
		240,
		241,
		242,
		243,
		243,
		244,
		245,
		246,
		246,
		247,
		248,
		249,
		249,
		250,
		251,
		252,
		252,
		253,
		254,
		255,
		255,
		256,
		257,
		258,
		258,
		259,
		260,
		261,
		261,
		262,
		263,
		264,
		265,
		265,
		266,
		267,
		268,
		268,
		269,
		270,
		271,
		272,
		272,
		273,
		274,
		275,
		275,
		276,
		277,
		278,
		279,
		279,
		280,
		281,
		282,
		283,
		283,
		284,
		285,
		286,
		287,
		287,
		288,
		289,
		290,
		291,
		291,
		292,
		293,
		294,
		295,
		295,
		296,
		297,
		298,
		299,
		299,
		300,
		301,
		302,
		303,
		304,
		304,
		305,
		306,
		307,
		308,
		309,
		309,
		310,
		311,
		312,
		313,
		314,
		314,
		315,
		316,
		317,
		318,
		319,
		319,
		320,
		321,
		322,
		323,
		324,
		324,
		325,
		326,
		327,
		328,
		329,
		330,
		330,
		331,
		332,
		333,
		334,
		335,
		336,
		336,
		337,
		338,
		339,
		340,
		341,
		342,
		343,
		343,
		344,
		345,
		346,
		347,
		348,
		349,
		350,
		350,
		351,
		352,
		353,
		354,
		355,
		356,
		357,
		357,
		358,
		359,
		360,
		361,
		362,
		363,
		364,
		365,
		365,
		366,
		367,
		368,
		369,
		370,
		371,
		372,
		373,
		374,
		374,
		375,
		376,
		377,
		378,
		379,
		380,
		381,
		382,
		383,
		384,
		385,
		385,
		386,
		387,
		388,
		389,
		390,
		391,
		392,
		393,
		394,
		395,
		396,
		397,
		397,
		398,
		399,
		400,
		401,
		402,
		403,
		404,
		405,
		406,
		407,
		408,
		409,
		410,
		411,
		411,
		412,
		413,
		414,
		415,
		416,
		417,
		418,
		419,
		420,
		421,
		422,
		423,
		424,
		425,
		426,
		427,
		428,
		429,
		430,
		431,
		432,
		433,
		433,
		434,
		435,
		436,
		437,
		438,
		439,
		440,
		441,
		442,
		443,
		444,
		445,
		446,
		447,
		448,
		449,
		450,
		451,
		452,
		453,
		454,
		455,
		456,
		457,
		458,
		459,
		460,
		461,
		462,
		463,
		464,
		465,
		466,
		467,
		468,
		469,
		470,
		471,
		472,
		473,
		474,
		475,
		476,
		477,
		478,
		479,
		480,
		481,
		482,
		483,
		484,
		485,
		486,
		487,
		488,
		489,
		490,
		491,
		492,
		493,
		494,
		495,
		496,
		497,
		498,
		499,
		500,
		501,
		502,
		503,
		504,
		505,
		507,
		508,
		509,
		510,
		511,
		512,
		513,
		514,
		515,
		516,
		517,
		518,
		519,
		520,
		521,
		522,
		523,
		524,
		525,
		526,
		527,
		528,
		529,
		531,
		532,
		533,
		534,
		535,
		536,
		537,
		538,
		539,
		540,
		541,
		542,
		543,
		544,
		545,
		546,
		548,
		549,
		550,
		551,
		552,
		553,
		554,
		555,
		556,
		557,
		558,
		559,
		560,
		561,
		563,
		564,
		565,
		566,
		567,
		568,
		569,
		570,
		571,
		572,
		573,
		575,
		576,
		577,
		578,
		579,
		580,
		581,
		582,
		583,
		584,
		585,
		587,
		588,
		589,
		590,
		591,
		592,
		593,
		594,
		595,
		597,
		598,
		599,
		600,
		601,
		602,
		603,
		604,
		605,
		607,
		608,
		609,
		610,
		611,
		612,
		613,
		614,
		615,
		617,
		618,
		619,
		620,
		621,
		622,
		623,
		624,
		626,
		627,
		628,
		629,
		630,
		631,
		632,
		634,
		635,
		636,
		637,
		638,
		639,
		640,
		642,
		643,
		644,
		645,
		646,
		647,
		648,
		650,
		651,
		652,
		653,
		654,
		655,
		656,
		658,
		659,
		660,
		661,
		662,
		663,
		665,
		666,
		667,
		668,
		669,
		670,
		671,
		673,
		674,
		675,
		676,
		677,
		678,
		680,
		681,
		682,
		683,
		684,
		685,
		687,
		688,
		689,
		690,
		691,
		693,
		694,
		695,
		696,
		697,
		698,
		700,
		701,
		702,
		703,
		704,
		706,
		707,
		708,
		709,
		710,
		711,
		713,
		714,
		715,
		716,
		717,
		719,
		720,
		721,
		722,
		723,
		725,
		726,
		727,
		728,
		729,
		731,
		732,
		733,
		734,
		735,
		737,
		738,
		739,
		740,
		741,
		743,
		744,
		745,
		746,
		748,
		749,
		750,
		751,
		752,
		754,
		755,
		756,
		757,
		759,
		760,
		761,
		762,
		763,
		765,
		766,
		767,
		768,
		770,
		771,
		772,
		773,
		774,
		776,
		777,
		778,
		779,
		781,
		782,
		783,
		784,
		786,
		787,
		788,
		789,
		790,
		792,
		793,
		794,
		795,
		797,
		798,
		799,
		800,
		802,
		803,
		804,
		805,
		807,
		808,
		809,
		810,
		812,
		813,
		814,
		815,
		817,
		818,
		819,
		820,
		822,
		823,
		824,
		825,
		827,
		828,
		829,
		831,
		832,
		833,
		834,
		836,
		837,
		838,
		839,
		841,
		842,
		843,
		844,
		846,
		847,
		848,
		850,
		851,
		852,
		853,
		855,
		856,
		857,
		858,
		860,
		861,
		862,
		864,
		865,
		866,
		867,
		869,
		870,
		871,
		873,
		874,
		875,
		876,
		878,
		879,
		880,
		882,
		883,
		884,
		885,
		887,
		888,
		889,
		891,
		892,
		893,
		895,
		896,
		897,
		898,
		900,
		901,
		902,
		904,
		905,
		906,
		908,
		909,
		910,
		911,
		913,
		914,
		915,
		917,
		918,
		919,
		921,
		922,
		923,
		925,
		926,
		927,
		929,
		930,
		931,
		932,
		934,
		935,
		936,
		938,
		939,
		940,
		942,
		943,
		944,
		946,
		947,
		948,
		950,
		951,
		952,
		954,
		955,
		956,
		958,
		959,
		960,
		962,
		963,
		964,
		966,
		967,
		968,
		970,
		971,
		972,
		974,
		975,
		976,
		978,
		979,
		980,
		982,
		983,
		984,
		986,
		987,
		988,
		990,
		991,
		992,
		994,
		995,
		996,
		998,
		999,
		1001,
		1002,
		1003,
		1005,
		1006,
		1007,
		1009,
		1010,
		1011,
		1013,
		1014,
		1015,
		1017,
		1018,
		1019,
		1021,
		1022,
		1024,
		1025,
		1026,
		1028,
		1029,
		1030,
		1032,
		1033,
		1034,
		1036,
		1037,
		1039,
		1040,
		1041,
		1043,
		1044,
		1045,
		1047,
		1048,
		1049,
		1051,
		1052,
		1054,
		1055,
		1056,
		1058,
		1059,
		1060,
		1062,
		1063,
		1065,
		1066,
		1067,
		1069,
		1070,
		1072,
		1073,
		1074,
		1076,
		1077,
		1078,
		1080,
		1081,
		1083,
		1084,
		1085,
		1087,
		1088,
		1090,
		1091,
		1092,
		1094,
		1095,
		1096,
		1098,
		1099,
		1101,
		1102,
		1103,
		1105,
		1106,
		1108,
		1109,
		1110,
		1112,
		1113,
		1115,
		1116,
		1117,
		1119,
		1120,
		1122,
		1123,
		1124,
		1126,
		1127,
		1129,
		1130,
		1131,
		1133,
		1134,
		1136,
		1137,
		1138,
		1140,
		1141,
		1143,
		1144,
		1145,
		1147,
		1148,
		1150,
		1151,
		1153,
		1154,
		1155,
		1157,
		1158,
		1160,
		1161,
		1162,
		1164,
		1165,
		1167,
		1168,
		1170,
		1171,
		1172,
		1174,
		1175,
		1177,
		1178,
		1179,
		1181,
		1182,
		1184,
		1185,
		1187,
		1188,
		1189,
		1191,
		1192,
		1194,
		1195,
		1197,
		1198,
		1199,
		1201,
		1202,
		1204,
		1205,
		1207,
		1208,
		1209,
		1211,
		1212,
		1214,
		1215,
		1217,
		1218,
		1220,
		1221,
		1222,
		1224,
		1225,
		1227,
		1228,
		1230,
		1231,
		1232,
		1234,
		1235,
		1237,
		1238,
		1240,
		1241,
		1243,
		1244,
		1245,
		1247,
		1248,
		1250,
		1251,
		1253,
		1254,
		1256,
		1257,
		1258,
		1260,
		1261,
		1263,
		1264,
		1266,
		1267,
		1269,
		1270,
		1272,
		1273,
		1274,
		1276,
		1277,
		1279,
		1280,
		1282,
		1283,
		1285,
		1286,
		1288,
		1289,
		1290,
		1292,
		1293,
		1295,
		1296,
		1298,
		1299,
		1301,
		1302,
		1304,
		1305,
		1307,
		1308,
		1309,
		1311,
		1312,
		1314,
		1315,
		1317,
		1318,
		1320,
		1321,
		1323,
		1324,
		1326,
		1327,
		1329,
		1330,
		1331,
		1333,
		1334,
		1336,
		1337,
		1339,
		1340,
		1342,
		1343,
		1345,
		1346,
		1348,
		1349,
		1351,
		1352,
		1354,
		1355,
		1357,
		1358,
		1360,
		1361,
		1362,
		1364,
		1365,
		1367,
		1368,
		1370,
		1371,
		1373,
		1374,
		1376,
		1377,
		1379,
		1380,
		1382,
		1383,
		1385,
		1386,
		1388,
		1389,
		1391,
		1392,
		1394,
		1395,
		1397,
		1398,
		1400,
		1401,
		1403,
		1404,
		1406,
		1407,
		1409,
		1410,
		1412,
		1413,
		1415,
		1416,
		1418,
		1419,
		1421,
		1422,
		1424,
		1425,
		1426,
		1428,
		1429,
		1431,
		1432,
		1434,
		1435,
		1437,
		1438,
		1440,
		1441,
		1443,
		1444,
		1446,
		1447,
		1449,
		1450,
		1452,
		1453,
		1455,
		1457,
		1458,
		1460,
		1461,
		1463,
		1464,
		1466,
		1467,
		1469,
		1470,
		1472,
		1473,
		1475,
		1476,
		1478,
		1479,
		1481,
		1482,
		1484,
		1485,
		1487,
		1488,
		1490,
		1491,
		1493,
		1494,
		1496,
		1497,
		1499,
		1500,
		1502,
		1503,
		1505,
		1506,
		1508,
		1509,
		1511,
		1512,
		1514,
		1515,
		1517,
		1518,
		1520,
		1521,
		1523,
		1525,
		1526,
		1528,
		1529,
		1531,
		1532,
		1534,
		1535,
		1537,
		1538,
		1540,
		1541,
		1543,
		1544,
		1546,
		1547,
		1549,
		1550,
		1552,
		1553,
		1555,
		1556,
		1558,
		1560,
		1561,
		1563,
		1564,
		1566,
		1567,
		1569,
		1570,
		1572,
		1573,
		1575,
		1576,
		1578,
		1579,
		1581,
		1582,
		1584,
		1585,
		1587,
		1589,
		1590,
		1592,
		1593,
		1595,
		1596,
		1598,
		1599,
		1601,
		1602,
		1604,
		1605,
		1607,
		1608,
		1610,
		1612,
		1613,
		1615,
		1616,
		1618,
		1619,
		1621,
		1622,
		1624,
		1625,
		1627,
		1628,
		1630,
		1632,
		1633,
		1635,
		1636,
		1638,
		1639,
		1641,
		1642,
		1644,
		1645,
		1647,
		1648,
		1650,
		1652,
		1653,
		1655,
		1656,
		1658,
		1659,
		1661,
		1662,
		1664,
		1665,
		1667,
		1669,
		1670,
		1672,
		1673,
		1675,
		1676,
		1678,
		1679,
		1681,
		1682,
		1684,
		1685,
		1687,
		1689,
		1690,
		1692,
		1693,
		1695,
		1696,
		1698,
		1699,
		1701,
		1703,
		1704,
		1706,
		1707,
		1709,
		1710,
		1712,
		1713,
		1715,
		1716,
		1718,
		1720,
		1721,
		1723,
		1724,
		1726,
		1727,
		1729,
		1730,
		1732,
		1734,
		1735,
		1737,
		1738,
		1740,
		1741,
		1743,
		1744,
		1746,
		1747,
		1749,
		1751,
		1752,
		1754,
		1755,
		1757,
		1758,
		1760,
		1761,
		1763,
		1765,
		1766,
		1768,
		1769,
		1771,
		1772,
		1774,
		1775,
		1777,
		1779,
		1780,
		1782,
		1783,
		1785,
		1786,
		1788,
		1790,
		1791,
		1793,
		1794,
		1796,
		1797,
		1799,
		1800,
		1802,
		1804,
		1805,
		1807,
		1808,
		1810,
		1811,
		1813,
		1814,
		1816,
		1818,
		1819,
		1821,
		1822,
		1824,
		1825,
		1827,
		1829,
		1830,
		1832,
		1833,
		1835,
		1836,
		1838,
		1839,
		1841,
		1843,
		1844,
		1846,
		1847,
		1849,
		1850,
		1852,
		1854,
		1855,
		1857,
		1858,
		1860,
		1861,
		1863,
		1864,
		1866,
		1868,
		1869,
		1871,
		1872,
		1874,
		1875,
		1877,
		1879,
		1880,
		1882,
		1883,
		1885,
		1886,
		1888,
		1890,
		1891,
		1893,
		1894,
		1896,
		1897,
		1899,
		1900,
		1902,
		1904,
		1905,
		1907,
		1908,
		1910,
		1911,
		1913,
		1915,
		1916,
		1918,
		1919,
		1921,
		1922,
		1924,
		1926,
		1927,
		1929,
		1930,
		1932,
		1933,
		1935,
		1937,
		1938,
		1940,
		1941,
		1943,
		1944,
		1946,
		1948,
		1949,
		1951,
		1952,
		1954,
		1955,
		1957,
		1958,
		1960,
		1962,
		1963,
		1965,
		1966,
		1968,
		1969,
		1971,
		1973,
		1974,
		1976,
		1977,
		1979,
		1980,
		1982,
		1984,
		1985,
		1987,
		1988,
		1990,
		1991,
		1993,
		1995,
		1996,
		1998,
		1999,
		2001,
		2002,
		2004,
		2006,
		2007,
		2009,
		2010,
		2012,
		2013,
		2015,
		2017,
		2018,
		2020,
		2021,
		2023,
		2024,
		2026,
		2028,
		2029,
		2031,
		2032,
		2034,
		2035,
		2037,
		2039,
		2040,
		2042,
		2043,
		2045,
		2046,
		2048,
		2050,
		2051,
		2053,
		2054,
		2056,
		2057,
		2059,
		2061,
		2062,
		2064,
		2065,
		2067,
		2068,
		2070,
		2072,
		2073,
		2075,
		2076,
		2078,
		2079,
		2081,
		2083,
		2084,
		2086,
		2087,
		2089,
		2090,
		2092,
		2094,
		2095,
		2097,
		2098,
		2100,
		2101,
		2103,
		2105,
		2106,
		2108,
		2109,
		2111,
		2112,
		2114,
		2116,
		2117,
		2119,
		2120,
		2122,
		2123,
		2125,
		2127,
		2128,
		2130,
		2131,
		2133,
		2134,
		2136,
		2138,
		2139,
		2141,
		2142,
		2144,
		2145,
		2147,
		2148,
		2150,
		2152,
		2153,
		2155,
		2156,
		2158,
		2159,
		2161,
		2163,
		2164,
		2166,
		2167,
		2169,
		2170,
		2172,
		2174,
		2175,
		2177,
		2178,
		2180,
		2181,
		2183,
		2185,
		2186,
		2188,
		2189,
		2191,
		2192,
		2194,
		2196,
		2197,
		2199,
		2200,
		2202,
		2203,
		2205,
		2206,
		2208,
		2210,
		2211,
		2213,
		2214,
		2216,
		2217,
		2219,
		2221,
		2222,
		2224,
		2225,
		2227,
		2228,
		2230,
		2232,
		2233,
		2235,
		2236,
		2238,
		2239,
		2241,
		2242,
		2244,
		2246,
		2247,
		2249,
		2250,
		2252,
		2253,
		2255,
		2257,
		2258,
		2260,
		2261,
		2263,
		2264,
		2266,
		2267,
		2269,
		2271,
		2272,
		2274,
		2275,
		2277,
		2278,
		2280,
		2282,
		2283,
		2285,
		2286,
		2288,
		2289,
		2291,
		2292,
		2294,
		2296,
		2297,
		2299,
		2300,
		2302,
		2303,
		2305,
		2306,
		2308,
		2310,
		2311,
		2313,
		2314,
		2316,
		2317,
		2319,
		2321,
		2322,
		2324,
		2325,
		2327,
		2328,
		2330,
		2331,
		2333,
		2335,
		2336,
		2338,
		2339,
		2341,
		2342,
		2344,
		2345,
		2347,
		2349,
		2350,
		2352,
		2353,
		2355,
		2356,
		2358,
		2359,
		2361,
		2362,
		2364,
		2366,
		2367,
		2369,
		2370,
		2372,
		2373,
		2375,
		2376,
		2378,
		2380,
		2381,
		2383,
		2384,
		2386,
		2387,
		2389,
		2390,
		2392,
		2393,
		2395,
		2397,
		2398,
		2400,
		2401,
		2403,
		2404,
		2406,
		2407,
		2409,
		2411,
		2412,
		2414,
		2415,
		2417,
		2418,
		2420,
		2421,
		2423,
		2424,
		2426,
		2427,
		2429,
		2431,
		2432,
		2434,
		2435,
		2437,
		2438,
		2440,
		2441,
		2443,
		2444,
		2446,
		2448,
		2449,
		2451,
		2452,
		2454,
		2455,
		2457,
		2458,
		2460,
		2461,
		2463,
		2464,
		2466,
		2468,
		2469,
		2471,
		2472,
		2474,
		2475,
		2477,
		2478,
		2480,
		2481,
		2483,
		2484,
		2486,
		2488,
		2489,
		2491,
		2492,
		2494,
		2495,
		2497,
		2498,
		2500,
		2501,
		2503,
		2504,
		2506,
		2507,
		2509,
		2511,
		2512,
		2514,
		2515,
		2517,
		2518,
		2520,
		2521,
		2523,
		2524,
		2526,
		2527,
		2529,
		2530,
		2532,
		2533,
		2535,
		2536,
		2538,
		2540,
		2541,
		2543,
		2544,
		2546,
		2547,
		2549,
		2550,
		2552,
		2553,
		2555,
		2556,
		2558,
		2559,
		2561,
		2562,
		2564,
		2565,
		2567,
		2568,
		2570,
		2571,
		2573,
		2575,
		2576,
		2578,
		2579,
		2581,
		2582,
		2584,
		2585,
		2587,
		2588,
		2590,
		2591,
		2593,
		2594,
		2596,
		2597,
		2599,
		2600,
		2602,
		2603,
		2605,
		2606,
		2608,
		2609,
		2611,
		2612,
		2614,
		2615,
		2617,
		2618,
		2620,
		2621,
		2623,
		2624,
		2626,
		2627,
		2629,
		2630,
		2632,
		2633,
		2635,
		2636,
		2638,
		2639,
		2641,
		2643,
		2644,
		2646,
		2647,
		2649,
		2650,
		2652,
		2653,
		2655,
		2656,
		2658,
		2659,
		2661,
		2662,
		2664,
		2665,
		2667,
		2668,
		2670,
		2671,
		2672,
		2674,
		2675,
		2677,
		2678,
		2680,
		2681,
		2683,
		2684,
		2686,
		2687,
		2689,
		2690,
		2692,
		2693,
		2695,
		2696,
		2698,
		2699,
		2701,
		2702,
		2704,
		2705,
		2707,
		2708,
		2710,
		2711,
		2713,
		2714,
		2716,
		2717,
		2719,
		2720,
		2722,
		2723,
		2725,
		2726,
		2728,
		2729,
		2731,
		2732,
		2734,
		2735,
		2736,
		2738,
		2739,
		2741,
		2742,
		2744,
		2745,
		2747,
		2748,
		2750,
		2751,
		2753,
		2754,
		2756,
		2757,
		2759,
		2760,
		2762,
		2763,
		2765,
		2766,
		2767,
		2769,
		2770,
		2772,
		2773,
		2775,
		2776,
		2778,
		2779,
		2781,
		2782,
		2784,
		2785,
		2787,
		2788,
		2789,
		2791,
		2792,
		2794,
		2795,
		2797,
		2798,
		2800,
		2801,
		2803,
		2804,
		2806,
		2807,
		2808,
		2810,
		2811,
		2813,
		2814,
		2816,
		2817,
		2819,
		2820,
		2822,
		2823,
		2824,
		2826,
		2827,
		2829,
		2830,
		2832,
		2833,
		2835,
		2836,
		2838,
		2839,
		2840,
		2842,
		2843,
		2845,
		2846,
		2848,
		2849,
		2851,
		2852,
		2853,
		2855,
		2856,
		2858,
		2859,
		2861,
		2862,
		2864,
		2865,
		2866,
		2868,
		2869,
		2871,
		2872,
		2874,
		2875,
		2876,
		2878,
		2879,
		2881,
		2882,
		2884,
		2885,
		2887,
		2888,
		2889,
		2891,
		2892,
		2894,
		2895,
		2897,
		2898,
		2899,
		2901,
		2902,
		2904,
		2905,
		2907,
		2908,
		2909,
		2911,
		2912,
		2914,
		2915,
		2917,
		2918,
		2919,
		2921,
		2922,
		2924,
		2925,
		2926,
		2928,
		2929,
		2931,
		2932,
		2934,
		2935,
		2936,
		2938,
		2939,
		2941,
		2942,
		2943,
		2945,
		2946,
		2948,
		2949,
		2951,
		2952,
		2953,
		2955,
		2956,
		2958,
		2959,
		2960,
		2962,
		2963,
		2965,
		2966,
		2967,
		2969,
		2970,
		2972,
		2973,
		2974,
		2976,
		2977,
		2979,
		2980,
		2981,
		2983,
		2984,
		2986,
		2987,
		2988,
		2990,
		2991,
		2993,
		2994,
		2995,
		2997,
		2998,
		3000,
		3001,
		3002,
		3004,
		3005,
		3006,
		3008,
		3009,
		3011,
		3012,
		3013,
		3015,
		3016,
		3018,
		3019,
		3020,
		3022,
		3023,
		3024,
		3026,
		3027,
		3029,
		3030,
		3031,
		3033,
		3034,
		3036,
		3037,
		3038,
		3040,
		3041,
		3042,
		3044,
		3045,
		3047,
		3048,
		3049,
		3051,
		3052,
		3053,
		3055,
		3056,
		3057,
		3059,
		3060,
		3062,
		3063,
		3064,
		3066,
		3067,
		3068,
		3070,
		3071,
		3072,
		3074,
		3075,
		3077,
		3078,
		3079,
		3081,
		3082,
		3083,
		3085,
		3086,
		3087,
		3089,
		3090,
		3091,
		3093,
		3094,
		3095,
		3097,
		3098,
		3100,
		3101,
		3102,
		3104,
		3105,
		3106,
		3108,
		3109,
		3110,
		3112,
		3113,
		3114,
		3116,
		3117,
		3118,
		3120,
		3121,
		3122,
		3124,
		3125,
		3126,
		3128,
		3129,
		3130,
		3132,
		3133,
		3134,
		3136,
		3137,
		3138,
		3140,
		3141,
		3142,
		3144,
		3145,
		3146,
		3148,
		3149,
		3150,
		3152,
		3153,
		3154,
		3156,
		3157,
		3158,
		3160,
		3161,
		3162,
		3164,
		3165,
		3166,
		3167,
		3169,
		3170,
		3171,
		3173,
		3174,
		3175,
		3177,
		3178,
		3179,
		3181,
		3182,
		3183,
		3185,
		3186,
		3187,
		3188,
		3190,
		3191,
		3192,
		3194,
		3195,
		3196,
		3198,
		3199,
		3200,
		3201,
		3203,
		3204,
		3205,
		3207,
		3208,
		3209,
		3211,
		3212,
		3213,
		3214,
		3216,
		3217,
		3218,
		3220,
		3221,
		3222,
		3223,
		3225,
		3226,
		3227,
		3229,
		3230,
		3231,
		3232,
		3234,
		3235,
		3236,
		3238,
		3239,
		3240,
		3241,
		3243,
		3244,
		3245,
		3246,
		3248,
		3249,
		3250,
		3252,
		3253,
		3254,
		3255,
		3257,
		3258,
		3259,
		3260,
		3262,
		3263,
		3264,
		3265,
		3267,
		3268,
		3269,
		3271,
		3272,
		3273,
		3274,
		3276,
		3277,
		3278,
		3279,
		3281,
		3282,
		3283,
		3284,
		3286,
		3287,
		3288,
		3289,
		3291,
		3292,
		3293,
		3294,
		3296,
		3297,
		3298,
		3299,
		3301,
		3302,
		3303,
		3304,
		3306,
		3307,
		3308,
		3309,
		3310,
		3312,
		3313,
		3314,
		3315,
		3317,
		3318,
		3319,
		3320,
		3322,
		3323,
		3324,
		3325,
		3326,
		3328,
		3329,
		3330,
		3331,
		3333,
		3334,
		3335,
		3336,
		3337,
		3339,
		3340,
		3341,
		3342,
		3344,
		3345,
		3346,
		3347,
		3348,
		3350,
		3351,
		3352,
		3353,
		3355,
		3356,
		3357,
		3358,
		3359,
		3361,
		3362,
		3363,
		3364,
		3365,
		3367,
		3368,
		3369,
		3370,
		3371,
		3373,
		3374,
		3375,
		3376,
		3377,
		3379,
		3380,
		3381,
		3382,
		3383,
		3385,
		3386,
		3387,
		3388,
		3389,
		3390,
		3392,
		3393,
		3394,
		3395,
		3396,
		3398,
		3399,
		3400,
		3401,
		3402,
		3403,
		3405,
		3406,
		3407,
		3408,
		3409,
		3411,
		3412,
		3413,
		3414,
		3415,
		3416,
		3418,
		3419,
		3420,
		3421,
		3422,
		3423,
		3425,
		3426,
		3427,
		3428,
		3429,
		3430,
		3431,
		3433,
		3434,
		3435,
		3436,
		3437,
		3438,
		3440,
		3441,
		3442,
		3443,
		3444,
		3445,
		3446,
		3448,
		3449,
		3450,
		3451,
		3452,
		3453,
		3454,
		3456,
		3457,
		3458,
		3459,
		3460,
		3461,
		3462,
		3464,
		3465,
		3466,
		3467,
		3468,
		3469,
		3470,
		3472,
		3473,
		3474,
		3475,
		3476,
		3477,
		3478,
		3479,
		3481,
		3482,
		3483,
		3484,
		3485,
		3486,
		3487,
		3488,
		3489,
		3491,
		3492,
		3493,
		3494,
		3495,
		3496,
		3497,
		3498,
		3499,
		3501,
		3502,
		3503,
		3504,
		3505,
		3506,
		3507,
		3508,
		3509,
		3511,
		3512,
		3513,
		3514,
		3515,
		3516,
		3517,
		3518,
		3519,
		3520,
		3521,
		3523,
		3524,
		3525,
		3526,
		3527,
		3528,
		3529,
		3530,
		3531,
		3532,
		3533,
		3535,
		3536,
		3537,
		3538,
		3539,
		3540,
		3541,
		3542,
		3543,
		3544,
		3545,
		3546,
		3547,
		3548,
		3550,
		3551,
		3552,
		3553,
		3554,
		3555,
		3556,
		3557,
		3558,
		3559,
		3560,
		3561,
		3562,
		3563,
		3564,
		3565,
		3567,
		3568,
		3569,
		3570,
		3571,
		3572,
		3573,
		3574,
		3575,
		3576,
		3577,
		3578,
		3579,
		3580,
		3581,
		3582,
		3583,
		3584,
		3585,
		3586,
		3587,
		3588,
		3589,
		3591,
		3592,
		3593,
		3594,
		3595,
		3596,
		3597,
		3598,
		3599,
		3600,
		3601,
		3602,
		3603,
		3604,
		3605,
		3606,
		3607,
		3608,
		3609,
		3610,
		3611,
		3612,
		3613,
		3614,
		3615,
		3616,
		3617,
		3618,
		3619,
		3620,
		3621,
		3622,
		3623,
		3624,
		3625,
		3626,
		3627,
		3628,
		3629,
		3630,
		3631,
		3632,
		3633,
		3634,
		3635,
		3636,
		3637,
		3638,
		3639,
		3640,
		3641,
		3642,
		3643,
		3644,
		3645,
		3646,
		3647,
		3648,
		3649,
		3650,
		3651,
		3652,
		3653,
		3654,
		3655,
		3656,
		3657,
		3658,
		3659,
		3660,
		3661,
		3662,
		3663,
		3663,
		3664,
		3665,
		3666,
		3667,
		3668,
		3669,
		3670,
		3671,
		3672,
		3673,
		3674,
		3675,
		3676,
		3677,
		3678,
		3679,
		3680,
		3681,
		3682,
		3683,
		3684,
		3685,
		3685,
		3686,
		3687,
		3688,
		3689,
		3690,
		3691,
		3692,
		3693,
		3694,
		3695,
		3696,
		3697,
		3698,
		3699,
		3699,
		3700,
		3701,
		3702,
		3703,
		3704,
		3705,
		3706,
		3707,
		3708,
		3709,
		3710,
		3711,
		3711,
		3712,
		3713,
		3714,
		3715,
		3716,
		3717,
		3718,
		3719,
		3720,
		3721,
		3722,
		3722,
		3723,
		3724,
		3725,
		3726,
		3727,
		3728,
		3729,
		3730,
		3731,
		3731,
		3732,
		3733,
		3734,
		3735,
		3736,
		3737,
		3738,
		3739,
		3739,
		3740,
		3741,
		3742,
		3743,
		3744,
		3745,
		3746,
		3746,
		3747,
		3748,
		3749,
		3750,
		3751,
		3752,
		3753,
		3753,
		3754,
		3755,
		3756,
		3757,
		3758,
		3759,
		3760,
		3760,
		3761,
		3762,
		3763,
		3764,
		3765,
		3766,
		3766,
		3767,
		3768,
		3769,
		3770,
		3771,
		3772,
		3772,
		3773,
		3774,
		3775,
		3776,
		3777,
		3777,
		3778,
		3779,
		3780,
		3781,
		3782,
		3782,
		3783,
		3784,
		3785,
		3786,
		3787,
		3787,
		3788,
		3789,
		3790,
		3791,
		3792,
		3792,
		3793,
		3794,
		3795,
		3796,
		3797,
		3797,
		3798,
		3799,
		3800,
		3801,
		3801,
		3802,
		3803,
		3804,
		3805,
		3805,
		3806,
		3807,
		3808,
		3809,
		3809,
		3810,
		3811,
		3812,
		3813,
		3813,
		3814,
		3815,
		3816,
		3817,
		3817,
		3818,
		3819,
		3820,
		3821,
		3821,
		3822,
		3823,
		3824,
		3824,
		3825,
		3826,
		3827,
		3828,
		3828,
		3829,
		3830,
		3831,
		3831,
		3832,
		3833,
		3834,
		3835,
		3835,
		3836,
		3837,
		3838,
		3838,
		3839,
		3840,
		3841,
		3841,
		3842,
		3843,
		3844,
		3844,
		3845,
		3846,
		3847,
		3847,
		3848,
		3849,
		3850,
		3850,
		3851,
		3852,
		3853,
		3853,
		3854,
		3855,
		3856,
		3856,
		3857,
		3858,
		3859,
		3859,
		3860,
		3861,
		3862,
		3862,
		3863,
		3864,
		3864,
		3865,
		3866,
		3867,
		3867,
		3868,
		3869,
		3869,
		3870,
		3871,
		3872,
		3872,
		3873,
		3874,
		3874,
		3875,
		3876,
		3877,
		3877,
		3878,
		3879,
		3879,
		3880,
		3881,
		3882,
		3882,
		3883,
		3884,
		3884,
		3885,
		3886,
		3886,
		3887,
		3888,
		3888,
		3889,
		3890,
		3891,
		3891,
		3892,
		3893,
		3893,
		3894,
		3895,
		3895,
		3896,
		3897,
		3897,
		3898,
		3899,
		3899,
		3900,
		3901,
		3901,
		3902,
		3903,
		3903,
		3904,
		3905,
		3905,
		3906,
		3907,
		3907,
		3908,
		3909,
		3909,
		3910,
		3911,
		3911,
		3912,
		3913,
		3913,
		3914,
		3915,
		3915,
		3916,
		3916,
		3917,
		3918,
		3918,
		3919,
		3920,
		3920,
		3921,
		3922,
		3922,
		3923,
		3923,
		3924,
		3925,
		3925,
		3926,
		3927,
		3927,
		3928,
		3928,
		3929,
		3930,
		3930,
		3931,
		3932,
		3932,
		3933,
		3933,
		3934,
		3935,
		3935,
		3936,
		3936,
		3937,
		3938,
		3938,
		3939,
		3940,
		3940,
		3941,
		3941,
		3942,
		3943,
		3943,
		3944,
		3944,
		3945,
		3945,
		3946,
		3947,
		3947,
		3948,
		3948,
		3949,
		3950,
		3950,
		3951,
		3951,
		3952,
		3952,
		3953,
		3954,
		3954,
		3955,
		3955,
		3956,
		3956,
		3957,
		3958,
		3958,
		3959,
		3959,
		3960,
		3960,
		3961,
		3962,
		3962,
		3963,
		3963,
		3964,
		3964,
		3965,
		3965,
		3966,
		3967,
		3967,
		3968,
		3968,
		3969,
		3969,
		3970,
		3970,
		3971,
		3971,
		3972,
		3973,
		3973,
		3974,
		3974,
		3975,
		3975,
		3976,
		3976,
		3977,
		3977,
		3978,
		3978,
		3979,
		3979,
		3980,
		3980,
		3981,
		3982,
		3982,
		3983,
		3983,
		3984,
		3984,
		3985,
		3985,
		3986,
		3986,
		3987,
		3987,
		3988,
		3988,
		3989,
		3989,
		3990,
		3990,
		3991,
		3991,
		3992,
		3992,
		3993,
		3993,
		3994,
		3994,
		3995,
		3995,
		3996,
		3996,
		3997,
		3997,
		3998,
		3998,
		3998,
		3999,
		3999,
		4000,
		4000,
		4001,
		4001,
		4002,
		4002,
		4003,
		4003,
		4004,
		4004,
		4005,
		4005,
		4006,
		4006,
		4006,
		4007,
		4007,
		4008,
		4008,
		4009,
		4009,
		4010,
		4010,
		4011,
		4011,
		4011,
		4012,
		4012,
		4013,
		4013,
		4014,
		4014,
		4015,
		4015,
		4015,
		4016,
		4016,
		4017,
		4017,
		4018,
		4018,
		4018,
		4019,
		4019,
		4020,
		4020,
		4021,
		4021,
		4021,
		4022,
		4022,
		4023,
		4023,
		4023,
		4024,
		4024,
		4025,
		4025,
		4026,
		4026,
		4026,
		4027,
		4027,
		4028,
		4028,
		4028,
		4029,
		4029,
		4030,
		4030,
		4030,
		4031,
		4031,
		4032,
		4032,
		4032,
		4033,
		4033,
		4033,
		4034,
		4034,
		4035,
		4035,
		4035,
		4036,
		4036,
		4037,
		4037,
		4037,
		4038,
		4038,
		4038,
		4039,
		4039,
		4039,
		4040,
		4040,
		4041,
		4041,
		4041,
		4042,
		4042,
		4042,
		4043,
		4043,
		4043,
		4044,
		4044,
		4045,
		4045,
		4045,
		4046,
		4046,
		4046,
		4047,
		4047,
		4047,
		4048,
		4048,
		4048,
		4049,
		4049,
		4049,
		4050,
		4050,
		4050,
		4051,
		4051,
		4051,
		4052,
		4052,
		4052,
		4053,
		4053,
		4053,
		4054,
		4054,
		4054,
		4054,
		4055,
		4055,
		4055,
		4056,
		4056,
		4056,
		4057,
		4057,
		4057,
		4058,
		4058,
		4058,
		4058,
		4059,
		4059,
		4059,
		4060,
		4060,
		4060,
		4061,
		4061,
		4061,
		4061,
		4062,
		4062,
		4062,
		4063,
		4063,
		4063,
		4063,
		4064,
		4064,
		4064,
		4064,
		4065,
		4065,
		4065,
		4066,
		4066,
		4066,
		4066,
		4067,
		4067,
		4067,
		4067,
		4068,
		4068,
		4068,
		4068,
		4069,
		4069,
		4069,
		4069,
		4070,
		4070,
		4070,
		4070,
		4071,
		4071,
		4071,
		4071,
		4072,
		4072,
		4072,
		4072,
		4073,
		4073,
		4073,
		4073,
		4074,
		4074,
		4074,
		4074,
		4075,
		4075,
		4075,
		4075,
		4075,
		4076,
		4076,
		4076,
		4076,
		4077,
		4077,
		4077,
		4077,
		4077,
		4078,
		4078,
		4078,
		4078,
		4078,
		4079,
		4079,
		4079,
		4079,
		4079,
		4080,
		4080,
		4080,
		4080,
		4080,
		4081,
		4081,
		4081,
		4081,
		4081,
		4082,
		4082,
		4082,
		4082,
		4082,
		4082,
		4083,
		4083,
		4083,
		4083,
		4083,
		4084,
		4084,
		4084,
		4084,
		4084,
		4084,
		4085,
		4085,
		4085,
		4085,
		4085,
		4085,
		4086,
		4086,
		4086,
		4086,
		4086,
		4086,
		4086,
		4087,
		4087,
		4087,
		4087,
		4087,
		4087,
		4087,
		4088,
		4088,
		4088,
		4088,
		4088,
		4088,
		4088,
		4089,
		4089,
		4089,
		4089,
		4089,
		4089,
		4089,
		4089,
		4090,
		4090,
		4090,
		4090,
		4090,
		4090,
		4090,
		4090,
		4091,
		4091,
		4091,
		4091,
		4091,
		4091,
		4091,
		4091,
		4091,
		4092,
		4092,
		4092,
		4092,
		4092,
		4092,
		4092,
		4092,
		4092,
		4092,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4093,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4094,
		4095,
		4095
};

void SineWaveGen(uint8_t Channel)
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
}

uint8_t Ch_1_Flg = 1;
uint8_t Ch_2_Flg = 1;
uint32_t Chan1=0;
uint32_t Chan2=0;
uint32_t delayer=0;

void DualOpposeSineWaveGen(uint32_t offset)
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
}