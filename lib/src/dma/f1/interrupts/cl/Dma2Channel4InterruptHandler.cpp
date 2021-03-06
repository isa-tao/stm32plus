/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"

#if defined(STM32PLUS_F1_CL)

#include "config/dma.h"


using namespace stm32plus;


// static initialisers for the hack that forces the IRQ handlers to be linked

template<> DmaInterruptFeatureEnabler<2,4>::FPTR DmaInterruptFeatureEnabler<2,4>::_forceLinkage=nullptr;


extern "C" {

  /**
   * DMA2, channel 4
   */

  #if defined(USE_DMA2_4_INTERRUPT)
    void __attribute__ ((interrupt("IRQ"))) DMA2_Channel4_IRQHandler() {

      if(DMA_GetITStatus(DMA2_IT_TC4)!=RESET) {
        DmaInterruptFeature<2,4>::_dmaInstance->DmaInterruptEventSender.raiseEvent(DmaEventType::EVENT_COMPLETE);
        DMA_ClearITPendingBit(DMA2_IT_TC4);
      }
      else if(DMA_GetITStatus(DMA2_IT_HT4)!=RESET) {
        DmaInterruptFeature<2,4>::_dmaInstance->DmaInterruptEventSender.raiseEvent(DmaEventType::EVENT_HALF_COMPLETE);
        DMA_ClearITPendingBit(DMA2_IT_HT4);
      }
      else if(DMA_GetITStatus(DMA2_IT_TE4)!=RESET) {
        DmaInterruptFeature<2,4>::_dmaInstance->DmaInterruptEventSender.raiseEvent(DmaEventType::EVENT_TRANSFER_ERROR);
        DMA_ClearITPendingBit(DMA2_IT_TE4);
      }
      __DSB();      // prevent erroneous recall of this handler due to delayed memory write
    }
  #endif
}
#endif // STM32PLUS_F1

