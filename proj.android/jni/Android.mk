LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes//AppDelegate.cpp \
../../Classes//Config/Config.cpp \
../../Classes//Contact/MyContact.cpp \
../../Classes//Entity/AdvanceSprite.cpp \
../../Classes//Entity/Bullet.cpp \
../../Classes//Entity/Enemy.cpp \
../../Classes//Entity/Hero.cpp \
../../Classes//Manager/GameManager.cpp \
../../Classes//Scene/AboutScene.cpp \
../../Classes//Scene/GameLayer.cpp \
../../Classes//Scene/GameOver.cpp \
../../Classes//Scene/MenuScene.cpp \
../../Classes//Scene/SceneManager.cpp \
../../Classes//Scene/SetScene.cpp \
../../Classes//Scene/UpgradeScene.cpp \
../../Classes//Test/HelloWorldScene.cpp \
../../Classes//Utilty/UILayer.cpp \
../../Classes//Utilty/Utilty.cpp \
../../Classes//Effect/Effect.cpp \
../../Classes//Layer/PopLayer.cpp \
../../Classes//Layer/PopDialog.cpp \
../../Classes//Layer/DialogLayer.cpp \
../../Classes//Layer/PassDialog.cpp \
../../Classes//Layer/PauseLayer.cpp \



                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static box2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) $(call import-module,external/Box2D)