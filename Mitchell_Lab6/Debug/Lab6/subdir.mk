################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Lab6/Mitchell_Lab6.cpp \
../Lab6/Timer.cpp 

OBJS += \
./Lab6/Mitchell_Lab6.o \
./Lab6/Timer.o 

CPP_DEPS += \
./Lab6/Mitchell_Lab6.d \
./Lab6/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Lab6/%.o: ../Lab6/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


