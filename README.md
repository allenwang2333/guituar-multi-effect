# Haawking RISC-V DSP Guitar Multi-Effect

This repo is a guitar multi-effect based on Haawking HXS320F28034 DSP based on RISC-V RV32 architecture.  

## Effects include:  
* distortion
* reverb
* delay
* high pass
* low pass
* mid pass
* tuner implemented by fft (also implemented by dft) 

## Features and Usage
* The effects are based on ring-bus up to 1 second of sample buffer, which enables multiple effects working together.    
* After each ADC interrupt, the buffer will be refreshed and effects will take place to refresh the buffer.   
* The output is in the form of PWM signal. To produce normal sin waves, filter is required. A basic RC filter will suffice.   
* To turn on each effect, simply add the effect to the loop. It works the same as a normal multi-effect.   

## Note
* This project is a prototype, under development.  
* Tuner is not very accurate due to limited capacity of RAM.  
* This project will be updated when new generation of chips with larger ram and I2S output are available.

![](/IMG_0380.jpg)
