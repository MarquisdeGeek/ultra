################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/config.cpp \
../src/configbase.cpp \
../src/database.cpp \
../src/fileset.cpp \
../src/service.cpp \
../src/ultra.cpp \
../src/ultra_request.cpp \
../src/utils.cpp \
../src/webserver.cpp 

OBJS += \
./src/config.o \
./src/configbase.o \
./src/database.o \
./src/fileset.o \
./src/service.o \
./src/ultra.o \
./src/ultra_request.o \
./src/utils.o \
./src/webserver.o 

CPP_DEPS += \
./src/config.d \
./src/configbase.d \
./src/database.d \
./src/fileset.d \
./src/service.d \
./src/ultra.d \
./src/ultra_request.d \
./src/utils.d \
./src/webserver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


