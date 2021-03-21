################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp 

OBJS += \
./src/Test.o 

CPP_DEPS += \
./src/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++0x -I"C:\Users\Gerd\git\TrafficControlSystem\TrafficLightCUTE\cute" -I"C:\Users\Gerd\git\PeriodicTimer\SimplePeriodicTimer\include" -I"C:\Users\Gerd\git\TrafficControlSystem\CrossRoadLib\include" -I"C:\Users\Gerd\git\TrafficControlSystem\ResultManagerMock\include" -I"C:\Users\Gerd\git\TrafficControlSystem\TrafficControlSystem\include" -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


