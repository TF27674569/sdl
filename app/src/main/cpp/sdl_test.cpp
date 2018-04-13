#include <jni.h>
#include <android/log.h>
#include <string>
#include"SDL.h"
#include"SDL_main.h"

#define TAG "SDL"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGI类型

// 文件路径
#define VIDEO_PATH  "/storage/emulated/0/705x576.yuv"

#define WIDTH 704
#define HEIGHT 576


// 主函数
int main(int argc, char *argv[]) {
    // 1. 初始化库资源
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1) {
        // 失败log
        LOGE("SDL init error %s", SDL_GetError());
        // 退出
        return 0;
    }
    // 编写代码
    LOGE("SDL init success");

    // 2. 创建一个窗口
    /**
     * const char *title 窗口名称 U8编码
     * int x 左边
     * int y
     * int w 宽
     * int h
     * Uint32 flags 窗口状态
     */
    int width = WIDTH;
    int height = HEIGHT;
    SDL_Window * sdl_window = SDL_CreateWindow("SDL2Window",
                                               SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED,
                                               width,
                                               height,
                                               SDL_WINDOW_OPENGL);

    if (sdl_window == NULL)
    {
        LOGE("SDL init SDL_Window error!");
        return 0;
    }

    // 3. 创建渲染器 OpenGlEs
    /**
     * SDL_Window * window 渲染目标
     * int index 从哪里开始 （-1 表示从第一个位置开始渲染）
     * Uint32 flags 渲染器类型  SDL_RENDERER_SOFTWARE 软件渲染 0 默认渲染
     */
    SDL_Renderer * sdl_renderer = SDL_CreateRenderer(sdl_window,-1,0);


    // 4. 创建纹理
    /**
     * SDL_Renderer * renderer 渲染器
     * Uint32 format 渲染格式
     * int access 绘制方式 SDL_TEXTUREACCESS_STREAMING 循环绘制
     * int w 宽
     * int h 高
     */
    SDL_Texture * sdl_texture = SDL_CreateTexture(sdl_renderer,SDL_PIXELFORMAT_IYUV,SDL_TEXTUREACCESS_STREAMING,width,height);


    // 5. 设置纹理数据
    // 打开文件
    FILE* yuv_file = fopen(VIDEO_PATH,"rb+");

    if (yuv_file == NULL)
    {
        LOGE(" yuv_file open error!");
        return 0;
    }

    // 计算每一帧的像素点
    // YUV格式 Y:U:V = 4：1：1 = 1:0.25:0.25
    // Y+U+V = 1+0.25+0.25 = 1.5
    // Y+U+V = width * height * 1.5
    int buffer_length = width * height * 3/2;
    char buffer_pix_fram[buffer_length];

    // 定义渲染区域
    SDL_Rect sdl_rect;

    int current_fram = 1;
    // 循环读帧
    while (true)
    {
        fread(buffer_pix_fram,1,buffer_length,yuv_file);

        // 是否结束
        if (feof(yuv_file))
        {
            break;
        }

        // 6.设置纹理数据
        /**
         * SDL_Texture * texture 纹理对象
         * const SDL_Rect * rect 渲染区域（NULL：默认屏幕宽高）
         * const void *pixels 视频像素数据
         * int pitch 帧画面的宽
         */
        SDL_UpdateTexture(sdl_texture,NULL,buffer_pix_fram,width);

        // 将纹理数据拷贝到渲染器
        // 先清空
        SDL_RenderClear(sdl_renderer);

        sdl_rect.x = 0;
        sdl_rect.y = 0;
        sdl_rect.w = width;
        sdl_rect.h = height;

        // 再拷贝
        SDL_RenderCopy(sdl_renderer,sdl_texture,NULL,&sdl_rect);


        // 7. 显示帧
        SDL_RenderPresent(sdl_renderer);

        // 8. 延时渲染
        SDL_Delay(20);

        LOGE("当前帧%d",current_fram);
        current_fram++;
    }

    // 9. 释放资源
    fclose(yuv_file);
    SDL_DestroyTexture(sdl_texture);
    SDL_DestroyRenderer(sdl_renderer);

    // 退出
    SDL_Quit();
    return 0;
}


