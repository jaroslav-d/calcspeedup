# File: Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := example
LOCAL_SRC_FILES := example_wrap.c example.c

LOCAL_CFLAGS += -fopenmp
LOCAL_LDFLAGS += -fopenmp

include $(BUILD_SHARED_LIBRARY)