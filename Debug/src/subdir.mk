################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/config.cpp \
../src/configbase.cpp \
../src/database.cpp \
../src/fileset.cpp \
../src/request.cpp \
../src/response.cpp \
../src/response_binary.cpp \
../src/response_text.cpp \
../src/service.cpp \
../src/ultra.cpp \
../src/utils.cpp 

OBJS += \
./src/config.o \
./src/configbase.o \
./src/database.o \
./src/fileset.o \
./src/request.o \
./src/response.o \
./src/response_binary.o \
./src/response_text.o \
./src/service.o \
./src/ultra.o \
./src/utils.o 

CPP_DEPS += \
./src/config.d \
./src/configbase.d \
./src/database.d \
./src/fileset.d \
./src/request.d \
./src/response.d \
./src/response_binary.d \
./src/response_text.d \
./src/service.d \
./src/ultra.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


