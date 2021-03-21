################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AmpelTest.cpp \
../src/Test.cpp 

OBJS += \
./src/AmpelTest.o \
./src/Test.o 

CPP_DEPS += \
./src/AmpelTest.d \
./src/Test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -std=c++1y -I"D:\DevProjects\Cpp\DesignPatternWorkspace\AmpelTest\cute" -I"D:\DevProjects\Cpp\DesignPatternWorkspace\VS_KreuzungLib\include" -I"D:\DevProjects\Cpp\DesignPatternWorkspace\VS_DesignMain\include" -I"D:\DevProjects\Cpp\DesignPatternWorkspace\AmpelTest\boost" -O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Test.o: ../src/Test.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -std=c++1y -std=c++1y -I"D:\DevProjects\Cpp\DesignPatternWorkspace\AmpelTest\cute" -I"D:\DevProjects\Cpp\DesignPatternWorkspace\VS_KreuzungLib\include" -I"D:\DevProjects\Cpp\DesignPatternWorkspace\AmpelTest\boost" -O0 -g3 -Wall -c -fmessage-length=0 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/Test.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


