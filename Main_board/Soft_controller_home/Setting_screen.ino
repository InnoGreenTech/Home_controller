void setting_screen(){


/*********************************************************
*                  Background screen                           *
**********************************************************/


if (!bitRead(flag_first_screen,SETTING_SCREEN)){

  
      tft.fillScreen(FOND);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.setCursor(70,10);
      tft.print F("SETTING ");
  

/* Write Bottons */

    setting_buttons_design();

    choice_buttons_design();

    bitSet(flag_first_screen,SETTING_SCREEN);

    } 

/* read and adjust information */


char info_set[7][19]={"Temperature summer","Temperature winter","Humidity summer   ","Humidity winter   ","CO2               ","Altitude          ","Set zero co2      "};

int mem_address[7]={MEM_SETTING_SUMMER_TEMPERATURE,MEM_SETTING_WINTER_TEMPERATURE,MEM_SETTING_SUMMER_HUMIDITY,MEM_SETTING_WINTER_HUMIDITY,MEM_SETTING_CO2,MEM_SETTING_ALTITUDE,999};
                       
if (!(new_index==index_setting)){
      index_setting=new_index;                      
      tft.setTextColor(WHITE,FOND);
      tft.setTextSize(2);
      tft.setCursor(30,40);
      String infos=info_set[index_setting];
      tft.print(infos);
      if(mem_address[index_setting]==999){setting=0;}
      else{
        byte read_mem[2];
        for (int a=0;a<2;a++){read_mem[a]=EEPROM.read (mem_address[index_setting]+a);}
        setting= read_mem[0] | read_mem[1] << 8;
      }
      tft.setTextColor(CYAN,FOND);
      tft.setTextSize(3);
      new_setting=1;
      }

if (new_setting==1){
  
      tft.setCursor(85,100);
      tft.print("   ");
      tft.setCursor(85,100);
      tft.print(setting);
      new_setting=0;
      }
    
/***********************************************************************************************************************************  
* Adjust values buttons
*/
  
  if(four_buttons[ESC].contains(x,y))
    { 
      if (reset_demand==1){resetFunc();}
      flag_screen=0;  
      flag_first_screen=0;
      bitSet(flag_screen,MAIN_SCREEN); 
     }

  if(four_buttons[MORE].contains(x,y))
    { 
      new_setting=1;
      setting++;
     }

  
  if(four_buttons[LESS].contains(x,y))
    { 
      new_setting=1;
      setting--;
     }

  if(four_buttons[OK].contains(x,y))
    { 
      tft.setTextColor(GREEN,FOND);
      new_setting=1;
      int data=setting;
      if(mem_address[index_setting]==999){rf_request(setting,CODE_SET_ZERO_CO2);}     //Zero to automatic mode, 1 to manual mode
      else{
        for (int a=0;a<2;a++){EEPROM.write(mem_address[index_setting]+a,data);data=data>>8;}
        reset_demand=1;
      }

     }


/**************************************************************************************************************************************  
*  Found parameter button
*/
 
  if (two_buttons[UP].contains(x,y))
    {   
        if (index_setting<29){new_index=index_setting+1;}
        else{new_index=1;}
    }
   if (two_buttons[DOWN].contains(x,y))
    {   
        if (index_setting>0){new_index=index_setting-1;}
        else{new_index=29;}
    }

   y=0;
   x=0;  
 
}
