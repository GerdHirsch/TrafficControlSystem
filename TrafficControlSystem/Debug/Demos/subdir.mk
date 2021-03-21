################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Demos/DemoTrafficLight.cpp 

OBJS += \
./Demos/DemoTrafficLight.o 

CPP_DEPS += \
./Demos/DemoTrafficLight.d 


# Each subdirectory must supply rules for building sources it contributes
Demos/%.o: ../Demos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++0x -I"C:\Users\Gerd\git\RepositoriesNeon\SimplePeriodicTimer\SimplePeriodicTimer\include" -I"C:\Users\Gerd\git\RepositoriesNeon\TCS_CrossRoadLib\TCS_CrossRoadLib\include" -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


