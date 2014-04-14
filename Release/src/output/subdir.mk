################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/output/file.cpp \
../src/output/socket.cpp \
../src/output/stdout.cpp 

OBJS += \
./src/output/file.o \
./src/output/socket.o \
./src/output/stdout.o 

CPP_DEPS += \
./src/output/file.d \
./src/output/socket.d \
./src/output/stdout.d 


# Each subdirectory must supply rules for building sources it contributes
src/output/%.o: ../src/output/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


