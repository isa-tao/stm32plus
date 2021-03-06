/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"
#include "config/usart.h"

#if !defined(STM32PLUS_MD_VL)

using namespace stm32plus;


// static initialisers for the hack that forces the IRQ handlers to be linked

template<> UsartInterruptFeatureEnabler<5>::FPTR UsartInterruptFeatureEnabler<5>::_forceLinkage=nullptr;
template<> UsartEventSource *UsartInterruptFeature<5>::_usartInstance=nullptr;


extern "C" {

  #if defined(USE_UART5_INTERRUPT)

    void __attribute__ ((interrupt("IRQ"))) UART5_IRQHandler(void) {
      if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_RECEIVE);
        USART_ClearITPendingBit(UART5,USART_IT_RXNE);
      }
      else if(USART_GetITStatus(UART5,USART_IT_TXE)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_READY_TO_TRANSMIT);
        USART_ClearITPendingBit(UART5,USART_IT_TXE);
      }
      else if(USART_GetITStatus(UART5,USART_IT_TC)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_TRANSMIT_COMPLETE);
        USART_ClearITPendingBit(UART5,USART_IT_TC);
      }
      else if(USART_GetITStatus(UART5,USART_IT_PE)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_PARITY_ERROR);
        USART_ClearITPendingBit(UART5,USART_IT_PE);
      }
      else if(USART_GetITStatus(UART5,USART_IT_IDLE)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_IDLE);
        USART_ClearITPendingBit(UART5,USART_IT_IDLE);
      }
      else if(USART_GetITStatus(UART5,USART_IT_LBD)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_LINE_BREAK_DETECT);
        USART_ClearITPendingBit(UART5,USART_IT_LBD);
      }
      else if(USART_GetITStatus(UART5,USART_IT_ERR)!=RESET) {
        UsartInterruptFeature<5>::_usartInstance->UsartInterruptEventSender.raiseEvent(UsartEventType::EVENT_ERROR);
        USART_ClearITPendingBit(UART5,USART_IT_ERR);
      }
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }

  #endif
} // extern "C"


#endif
