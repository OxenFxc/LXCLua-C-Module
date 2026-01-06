LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := LXCLuaCore
LOCAL_SRC_FILES := libs/arm64-v8a/libLXCLuaCore.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libs/lua $(LOCAL_PATH)/libs/luajava
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE     := mysample
LOCAL_SRC_FILES  := mysample.c
LOCAL_C_INCLUDES := $(LXCLuaCore_EXPORT_C_INCLUDES)


LOCAL_CFLAGS := -std=c17 -O0 -fomit-frame-pointer -ffunction-sections -fdata-sections
LOCAL_CFLAGS += -g0 -DNDEBUG -fno-exceptions -fvisibility=default


LOCAL_LDFLAGS := -Wl,--gc-sections

LOCAL_SHARED_LIBRARIES := LXCLuaCore
LOCAL_LDLIBS += -llog -ldl -lz

include $(BUILD_SHARED_LIBRARY)
