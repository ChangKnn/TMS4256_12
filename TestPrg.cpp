//TMS4256_01���Գ���

#include "StdAfx.h"
#include "testdef.h"
#include "data.h"
#include "math.h"

void PASCAL TMS4256_01()
{

  CString str;

//CON-TEST

  SET_DPS(1,0,V,50,MA);
  PMU_CONDITIONS(FIMV,-0.1,MA,2,V);
  if (!PMU_MEASURE("1-9,39-40,42-44",20,"CON_",V,-0.1,-1.9)) {
    BIN(1);
  }

//VOH-TEST

  SET_PERIOD(50);
  SET_TIMING(5,10,25);
  FORMAT(NRZ0,"1,2,3,4,5,6,7,8,9,39,40,42,43,44");

  SET_DPS(1,5,V,200,MA);
  SET_INPUT_LEVEL(3,0);
  SET_OUTPUT_LEVEL(2.4,0.4);
  RUN_PATTERN(0,1,0,0);
  PMU_CONDITIONS(FIMV,-5,MA,5,V);
  if (!PMU_MEASURE("40",1,"VOH_",V,No_UpLimit,2.4)) {
    BIN(2);
  }

//VOl-TEST

  SET_DPS(1,5,V,200,MA);
  SET_INPUT_LEVEL(3,0);
  FORMAT(NRZ0,"1,2,3,4,5,6,7,8,9,39,41,42,43,44");
  RUN_PATTERN(1,1,0,0);
  PMU_CONDITIONS(FIMV,4.2,MA,0.5,V);
  if (!PMU_MEASURE("40",0,"VOL_",V,0.4,No_LoLimit)) {
    BIN(3);
  }

//II-TEST

  SET_DPS(1,5,V,200,MA);
  RUN_PATTERN(2,1,0,0);
  PMU_CONDITIONS(FVMI,5,V,1,MA);
  if (!PMU_MEASURE("1,2,3,4,5,6,7,8,9,39,42,43,44",5,"II/H_",UA,10,-10)) {
    BIN(4);
  }

  SET_DPS(1,5,V,200,MA);
  RUN_PATTERN(3,1,0,0);
  PMU_CONDITIONS(FVMI,0,V,1,MA);
  if (!PMU_MEASURE("1,2,3,4,5,6,7,8,9,39,42,43,44",5,"II/L_",UA,10,-10)) {
    BIN(4);
  }

//IO_TEST

  SET_PERIOD(50);
  SET_TIMING(10,30,40);
  FORMAT(NRZ0,"1,2,3,4,5,6,7,8,9,39,41,42,43,44");

  SET_DPS(1,5,V,200,MA);
  SET_INPUT_LEVEL(3,0);

  RUN_PATTERN(4,1,0,0);
  PMU_CONDITIONS(FVMI,5,V,1,MA);
  if (!PMU_MEASURE("40",1,"IOH_",UA,10,-10)) {
    BIN(5);
  }

  SET_DPS(1,5,V,200,MA);
  SET_INPUT_LEVEL(3,0);
  FORMAT(NRZ0,"1,2,3,4,5,6,7,8,9,39,41,42,43,44");
  RUN_PATTERN(5,1,0,0);
  PMU_CONDITIONS(FVMI,0,V,1,MA);
  if (!PMU_MEASURE("40",1,"IOL_",UA,10,-10)) {
    BIN(5);
  }


//IDD1_TEST
  SET_DPS(1,5,V,200,MA);
  RUN_PATTERN(11,1,0,0);
  if (!DPS_MEASURE(DPS1,R250MA,1,"IDD1",MA,70,No_LoLimit)) {
    BIN(6);
  }

//IDD2_TEST
  SET_DPS(1,5,V,200,MA);
  RUN_PATTERN(6,1,0,0);
  if (!DPS_MEASURE(DPS1,R20MA,1,"IDD2",MA,4.5,No_LoLimit)) {
    BIN(7);
  }

//IDD3_TEST
  SET_DPS(1,5,V,200,MA);
  RUN_PATTERN(13,1,0,0);
  if (!DPS_MEASURE(DPS1,R250MA,1,"IDD3",MA,70,No_LoLimit)) {
    BIN(8);
  }

//IDD4_TEST
  SET_DPS(1,5,V,200,MA);
  RUN_PATTERN(12,1,0,0);
  if (!DPS_MEASURE(DPS1,R250MA,1,"IDD4",MA,60,No_LoLimit)) {
    BIN(9);
  }

  //EARLY_WRITE TEST
  if(!RUN_PATTERN("FUN EW",7,1,0,100)){
    BIN(10);
  }
  if(!RUN_PATTERN("FUN EW READ",8,1,0,100)){
    BIN(10);
  }

//READ MODIFY WRITE TEST
  if(!RUN_PATTERN("FUN RMW",9,1,0,100)){
    BIN(11);
  }

//PAGE WRITE AND READ TEST
  if(!RUN_PATTERN("FUN PWR",10,1,0,100)){
    BIN(12);
  }

//REFRESH TEST
  RUN_PATTERN(14,1,0,0);
  Delay(3);
  RUN_PATTERN(15,1,0,0);
  Delay(2);
  if (!RUN_PATTERN("FUN FRESH",16,1,0,0))
  {
    BIN(13);
  }
  

//FUN TEST
  if(!RUN_PATTERN("FUN_TEST",17,1,0,0)){
	BIN(14);
  }
}
