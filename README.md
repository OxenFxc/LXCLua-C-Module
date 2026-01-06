# LXCLua-C-Module
本项目基于 Android NDK 构建，目标是为 **LXCLua** 环境编译可直接调用的 Lua C 扩展模块 `libmysample.so`。编译生成的动态库可在 LXCLua 中通过 `require` 函数加载，实现 Lua 层与原生 C 代码的高效交互。
# LXCLua C 模块编译项目说明

## 一、项目简介
本项目基于 Android NDK 构建，目标是为 **LXCLua** 环境编译可直接调用的 Lua C 扩展模块 `libmysample.so`。编译生成的动态库可在 LXCLua 中通过 `require` 函数加载，实现 Lua 层与原生 C 代码的高效交互。

## 二、项目目录结构
markdown
  
# LXCLua C 模块编译项目说明

## 一、项目简介
本项目基于 Android NDK 构建，目标是为 **LXCLua** 环境编译可直接调用的 Lua C 扩展模块 `libmysample.so`。编译生成的动态库可在 LXCLua 中通过 `require` 函数加载，实现 Lua 层与原生 C 代码的高效交互。

## 二、项目目录结构
 
 
luamodule/
└── jni/
└── new/
├── Android.mk          # NDK 编译核心配置文件
├── mysample.c          # 自定义 Lua C 模块源码
└── libs/
├── arm64-v8a/
│   └── libLXCLuaCore.so  # LXCLua 核心动态库
├── lua/            # Lua 核心头文件目录
│   ├── lua.h
│   ├── lauxlib.h
│   ├── lualib.h
│   └── ...
└── luajava/        # LXCLua 扩展头文件目录
└── luajava.h
 
plaintext
  

## 三、核心文件说明
### 1. 编译配置文件 `Android.mk`（精简版）
```makefile
LOCAL_PATH := $(call my-dir)

# 引入 LXCLua 核心动态库
include $(CLEAR_VARS)
LOCAL_MODULE := LXCLuaCore
LOCAL_SRC_FILES := libs/arm64-v8a/libLXCLuaCore.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libs/lua $(LOCAL_PATH)/libs/luajava
include $(PREBUILT_SHARED_LIBRARY)

# 编译自定义 Lua C 模块
include $(CLEAR_VARS)
LOCAL_MODULE     := mysample
LOCAL_SRC_FILES  := mysample.c
LOCAL_C_INCLUDES := $(LXCLuaCore_EXPORT_C_INCLUDES)

# 编译参数：无优化，降低内存占用
LOCAL_CFLAGS := -std=c17 -O0 -fomit-frame-pointer -ffunction-sections -fdata-sections
LOCAL_CFLAGS += -g0 -DNDEBUG -fno-exceptions

# 链接参数：剔除无用代码
LOCAL_LDFLAGS := -Wl,--gc-sections

# 依赖配置
LOCAL_SHARED_LIBRARIES := LXCLuaCore
LOCAL_LDLIBS += -llog -ldl -lz

include $(BUILD_SHARED_LIBRARY)
 
 
2. 自定义模块源码  mysample.c （示例框架）
 
c
  
#include "lua.h"
#include "lauxlib.h"

// 自定义 Lua 调用函数：示例 hello 方法
static int lxc_hello(lua_State *L) {
    const char *name = luaL_checkstring(L, 1);
    lua_pushfstring(L, "Hello, %s! (from LXCLua C module)", name);
    return 1;
}

// 自定义模块方法列表
static const struct luaL_Reg mysample_lib[] = {
    {"hello", lxc_hello},
    {NULL, NULL}
};

// 模块注册入口
int luaopen_mysample(lua_State *L) {
    luaL_newlib(L, mysample_lib);
    return 1;
}
 
 
四、编译命令
 
bash
  
cd /data/user/0/com.termux/files/home/luamodule
NDK_PROJECT_PATH=$(pwd) APP_BUILD_SCRIPT=$(pwd)/jni/new/Android.mk /data/user/0/com.termux/files/home/Android/android-sdk/ndk/28.2.13676358/ndk-build
 
 
五、使用说明
 
plaintext
  
1.  编译完成后，在 luamodule/obj/local/arm64-v8a/ 目录下找到生成的 libmysample.so
2.  将 libmysample.so 和 libLXCLuaCore.so 放入 LXCLua 的动态库加载路径
3.  在 Lua 代码中加载并调用模块：
    local mysample = require("mysample")
    print(mysample.hello("LXCLua"))


