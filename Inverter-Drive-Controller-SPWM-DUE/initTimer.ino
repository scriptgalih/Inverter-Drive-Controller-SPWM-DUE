void TimerStart(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t freq)
{
   pmc_set_writeprotect(false);
   pmc_enable_periph_clk(irq);
   TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC |
                             TC_CMR_TCCLKS_TIMER_CLOCK3);
   uint32_t rc = VARIANT_MCK / 32 / freq;
   TC_SetRA(tc, channel, rc >> 1); // 50% duty cycle square wave
   TC_SetRC(tc, channel, rc);
   TC_Start(tc, channel);
   tc->TC_CHANNEL[channel].TC_IER=  TC_IER_CPCS | TC_IER_CPAS;
   tc->TC_CHANNEL[channel].TC_IDR=~(TC_IER_CPCS | TC_IER_CPAS);
   NVIC_EnableIRQ(irq);
}
