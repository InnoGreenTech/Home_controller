ISR (WDT_vect){



  wdt_reset();
  
  bitClear(MCUSR, WDRF);            // Reset du chien de garde

  asm volatile ("jmp 0"); 
  
  }
