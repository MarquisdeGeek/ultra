################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/remap/comment.cpp \
../src/remap/database_delete.cpp \
../src/remap/database_fieldcount.cpp \
../src/remap/database_fields.cpp \
../src/remap/dumpdb.cpp \
../src/remap/dumplivedata.cpp \
../src/remap/execute.cpp \
../src/remap/get_arguments.cpp \
../src/remap/link.cpp \
../src/remap/op_add.cpp \
../src/remap/op_limit.cpp \
../src/remap/redirection.cpp \
../src/remap/serialize.cpp \
../src/remap/ssi.cpp \
../src/remap/static.cpp \
../src/remap/stats.cpp \
../src/remap/time.cpp 

OBJS += \
./src/remap/comment.o \
./src/remap/database_delete.o \
./src/remap/database_fieldcount.o \
./src/remap/database_fields.o \
./src/remap/dumpdb.o \
./src/remap/dumplivedata.o \
./src/remap/execute.o \
./src/remap/get_arguments.o \
./src/remap/link.o \
./src/remap/op_add.o \
./src/remap/op_limit.o \
./src/remap/redirection.o \
./src/remap/serialize.o \
./src/remap/ssi.o \
./src/remap/static.o \
./src/remap/stats.o \
./src/remap/time.o 

CPP_DEPS += \
./src/remap/comment.d \
./src/remap/database_delete.d \
./src/remap/database_fieldcount.d \
./src/remap/database_fields.d \
./src/remap/dumpdb.d \
./src/remap/dumplivedata.d \
./src/remap/execute.d \
./src/remap/get_arguments.d \
./src/remap/link.d \
./src/remap/op_add.d \
./src/remap/op_limit.d \
./src/remap/redirection.d \
./src/remap/serialize.d \
./src/remap/ssi.d \
./src/remap/static.d \
./src/remap/stats.d \
./src/remap/time.d 


# Each subdirectory must supply rules for building sources it contributes
src/remap/%.o: ../src/remap/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


