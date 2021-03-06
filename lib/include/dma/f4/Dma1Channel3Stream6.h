/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once

// ensure the MCU series is correct
#ifndef STM32PLUS_F4
#error This class can only be used with the STM32F4 series
#endif


namespace stm32plus {

  /**
   * Feature collection for this DMA channel. Parameterise this class with the features
   * that you want to use on this channel.
   */

  template<class... Features>
  class Dma1Channel3Stream6 : public Dma,
                              public Features... {

    public:

      /**
       * Constructor
       */

      Dma1Channel3Stream6()
        : Dma(DMA1_Stream6,DMA_Channel_3,DMA_FLAG_TCIF6,DMA_FLAG_HTIF6,DMA_FLAG_TEIF6),
          Features(static_cast<Dma&>(*this))... {

        ClockControl<PERIPHERAL_DMA1>::On();
      }
  };


  /**
   * Types for the peripherals mapped to this channel
   */

  template<class... Features> using Timer2Channel2DmaChannel=Dma1Channel3Stream6<Features...>;
  template<class... Features> using Timer2Channel4DmaChannel=Dma1Channel3Stream6<Features...>;
}
